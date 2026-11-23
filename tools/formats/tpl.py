"""Nintendo TPL texture container reader + GX texture decoder (stdlib only).

FE10 uses plain Revolution-SDK TPL files (magic 00 20 AF 30): loose *.tpl,
inside pack archives (unit / map / weapon packs) and LZ10-compressed as
Face/*.cms. See docs/formats/graphics.md, section "TPL".

All integers big-endian.

  0x00 u32 magic 0x0020AF30
  0x04 u32 image_count
  0x08 u32 image_table_offset (always 0x0C)
  table: image_count x {u32 image_header_off, u32 palette_header_off (0 = none)}
  image header (0x24 bytes):
    0x00 u16 height, 0x02 u16 width, 0x04 u32 format, 0x08 u32 data_off,
    0x0C u32 wrap_s, 0x10 u32 wrap_t, 0x14 u32 min_filter, 0x18 u32 mag_filter,
    0x1C f32 lod_bias, 0x20 u8 edge_lod, 0x21 u8 min_lod, 0x22 u8 max_lod,
    0x23 u8 unpacked
  palette header (0x0C bytes):
    0x00 u16 entry_count, 0x02 u8 unpacked, 0x03 u8 pad,
    0x04 u32 palette_format (0 IA8, 1 RGB565, 2 RGB5A3), 0x08 u32 data_off

Library use:
    tex = TPL.from_file(path)          # .tpl, or LZ10 .cms/.cmp
    for img in tex.images: img.width, img.height, img.format, img.decode()
    -> decode() returns RGBA bytes (row-major, 4 bytes/pixel)
    write_png(path, w, h, rgba)

CLI:  tpl.py IN.tpl|.cms OUTDIR      -> OUTDIR/<stem>_<i>.png
      tpl.py --survey DIR             -> format histogram over all TPLs under DIR
                                         (also looks inside pack archives)
"""
import os
import struct
import sys
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from lz10 import load  # noqa: E402

MAGIC = 0x0020AF30

# format id -> (name, block_w, block_h, bits_per_pixel)
FORMATS = {
    0x0: ("I4", 8, 8, 4),
    0x1: ("I8", 8, 4, 8),
    0x2: ("IA4", 8, 4, 8),
    0x3: ("IA8", 4, 4, 16),
    0x4: ("RGB565", 4, 4, 16),
    0x5: ("RGB5A3", 4, 4, 16),
    0x6: ("RGBA8", 4, 4, 32),
    0x8: ("CI4", 8, 8, 4),
    0x9: ("CI8", 8, 4, 8),
    0xA: ("CI14X2", 4, 4, 16),
    0xE: ("CMPR", 8, 8, 4),
}
PALETTE_FORMATS = {0: "IA8", 1: "RGB565", 2: "RGB5A3"}


def image_size(fmt, w, h):
    _, bw, bh, bpp = FORMATS[fmt]
    bx = (w + bw - 1) // bw
    by = (h + bh - 1) // bh
    return bx * by * bw * bh * bpp // 8


# ---------------------------------------------------------------- pixel helpers
def _rgb565(v):
    r = (v >> 11) & 0x1F
    g = (v >> 5) & 0x3F
    b = v & 0x1F
    return ((r << 3) | (r >> 2), (g << 2) | (g >> 4), (b << 3) | (b >> 2), 255)


def _rgb5a3(v):
    if v & 0x8000:
        r = (v >> 10) & 0x1F
        g = (v >> 5) & 0x1F
        b = v & 0x1F
        return ((r << 3) | (r >> 2), (g << 3) | (g >> 2), (b << 3) | (b >> 2), 255)
    a = (v >> 12) & 0x7
    r = (v >> 8) & 0xF
    g = (v >> 4) & 0xF
    b = v & 0xF
    return (r * 0x11, g * 0x11, b * 0x11, (a << 5) | (a << 2) | (a >> 1))


def _ia8(v):
    a = v >> 8
    i = v & 0xFF
    return (i, i, i, a)


_PAL_CONV = {0: _ia8, 1: _rgb565, 2: _rgb5a3}


def decode_palette(data, off, count, pfmt):
    conv = _PAL_CONV[pfmt]
    return [conv(struct.unpack_from(">H", data, off + 2 * i)[0]) for i in range(count)]


# ---------------------------------------------------------------- decoder
def _decode_raw(data, off, w, h, fmt, palette=None):
    """8/16/32 bpp formats and CMPR."""
    if fmt not in FORMATS:
        raise ValueError("unsupported GX texture format 0x%x" % fmt)
    name, bw, bh, bpp = FORMATS[fmt]
    out = bytearray(w * h * 4)
    bxn = (w + bw - 1) // bw
    byn = (h + bh - 1) // bh
    pos = off

    def put(x, y, px):
        if x < w and y < h:
            i = (y * w + x) * 4
            out[i:i + 4] = bytes(px)

    if name == "CMPR":
        for by in range(byn):
            for bx in range(bxn):
                for sub in range(4):  # 2x2 sub-blocks of 4x4 DXT1
                    sx = bx * 8 + (sub & 1) * 4
                    sy = by * 8 + (sub >> 1) * 4
                    c0, c1, bits = struct.unpack_from(">HHI", data, pos)
                    pos += 8
                    p0 = _rgb565(c0)
                    p1 = _rgb565(c1)
                    if c0 > c1:
                        p2 = tuple((2 * a + b) // 3 for a, b in zip(p0[:3], p1[:3])) + (255,)
                        p3 = tuple((a + 2 * b) // 3 for a, b in zip(p0[:3], p1[:3])) + (255,)
                    else:
                        p2 = tuple((a + b) // 2 for a, b in zip(p0[:3], p1[:3])) + (255,)
                        p3 = (0, 0, 0, 0)
                    pal = (p0, p1, p2, p3)
                    for py in range(4):
                        for px in range(4):
                            idx = (bits >> (30 - 2 * (py * 4 + px))) & 3
                            put(sx + px, sy + py, pal[idx])
        return bytes(out)

    for by in range(byn):
        for bx in range(bxn):
            x0, y0 = bx * bw, by * bh
            if name == "RGBA8":
                # 64 bytes: 16 AR pairs then 16 GB pairs
                for i in range(16):
                    a, r = data[pos + 2 * i], data[pos + 2 * i + 1]
                    g, b = data[pos + 32 + 2 * i], data[pos + 33 + 2 * i]
                    put(x0 + (i & 3), y0 + (i >> 2), (r, g, b, a))
                pos += 64
                continue
            for py in range(bh):
                for px in range(bw):
                    if bpp == 8:
                        v = data[pos]
                        pos += 1
                    else:
                        v = (data[pos] << 8) | data[pos + 1]
                        pos += 2
                    if name == "I8":
                        px_ = (v, v, v, v)
                    elif name == "IA4":
                        i = (v & 0xF) * 0x11
                        px_ = (i, i, i, (v >> 4) * 0x11)
                    elif name == "IA8":
                        px_ = _ia8(v)
                    elif name == "RGB565":
                        px_ = _rgb565(v)
                    elif name == "RGB5A3":
                        px_ = _rgb5a3(v)
                    else:  # CI4 / CI8 / CI14X2
                        if name == "CI14X2":
                            v &= 0x3FFF
                        px_ = palette[v] if palette and v < len(palette) else (255, 0, 255, 255)
                    put(x0 + px, y0 + py, px_)
    return bytes(out)


def decode(data, off, w, h, fmt, palette=None):
    """Decode one GX texture level. Returns RGBA bytes (w*h*4)."""
    if fmt not in FORMATS:
        raise ValueError("unsupported GX texture format 0x%x" % fmt)
    if fmt in FORMATS and FORMATS[fmt][3] == 4 and FORMATS[fmt][0] != "CMPR":
        return _decode_nibbles(data, off, w, h, fmt, palette)
    return _decode_raw(data, off, w, h, fmt, palette)


def _decode_nibbles(data, off, w, h, fmt, palette):
    name, bw, bh, _ = FORMATS[fmt]
    out = bytearray(w * h * 4)
    bxn = (w + bw - 1) // bw
    byn = (h + bh - 1) // bh
    pos = off
    for by in range(byn):
        for bx in range(bxn):
            for py in range(bh):
                y = by * bh + py
                for pxp in range(bw // 2):
                    byte = data[pos]
                    pos += 1
                    for k, v in enumerate((byte >> 4, byte & 0xF)):
                        x = bx * bw + pxp * 2 + k
                        if x >= w or y >= h:
                            continue
                        if name == "I4":
                            i = v * 0x11
                            px_ = (i, i, i, i)
                        else:
                            px_ = palette[v] if palette and v < len(palette) else (255, 0, 255, 255)
                        j = (y * w + x) * 4
                        out[j:j + 4] = bytes(px_)
    return bytes(out)


# ---------------------------------------------------------------- container
class TPLImage:
    def __init__(self, raw, hoff, poff):
        self.raw = raw
        (self.height, self.width, self.format, self.data_off, self.wrap_s,
         self.wrap_t, self.min_filter, self.mag_filter) = struct.unpack_from(">HHIIIIII", raw, hoff)
        (self.lod_bias,) = struct.unpack_from(">f", raw, hoff + 0x1C)
        self.edge_lod, self.min_lod, self.max_lod, self.unpacked = raw[hoff + 0x20:hoff + 0x24]
        self.palette = None
        self.palette_format = None
        if poff:
            cnt, _unp, _pad, pfmt, pdata = struct.unpack_from(">HBBII", raw, poff)
            self.palette_format = pfmt
            self.palette = decode_palette(raw, pdata, cnt, pfmt)

    @property
    def format_name(self):
        return FORMATS.get(self.format, ("0x%x" % self.format,))[0]

    @property
    def mip_count(self):
        return self.max_lod + 1 if self.max_lod >= self.min_lod else 1

    def decode(self, level=0):
        w, h, off = self.width, self.height, self.data_off
        for _ in range(level):
            off += image_size(self.format, w, h)
            w, h = max(1, w // 2), max(1, h // 2)
        return w, h, decode(self.raw, off, w, h, self.format, self.palette)


class TPL:
    def __init__(self, raw: bytes):
        if len(raw) < 12 or struct.unpack_from(">I", raw, 0)[0] != MAGIC:
            raise ValueError("not a TPL file")
        self.raw = raw
        count, table = struct.unpack_from(">II", raw, 4)
        self.images = []
        for i in range(count):
            hoff, poff = struct.unpack_from(">II", raw, table + 8 * i)
            self.images.append(TPLImage(raw, hoff, poff))

    @classmethod
    def from_file(cls, path):
        return cls(load(path))

    @staticmethod
    def check(raw):
        return len(raw) >= 12 and struct.unpack_from(">I", raw, 0)[0] == MAGIC


# ---------------------------------------------------------------- PNG writer
def write_png(path, w, h, rgba):
    def chunk(t, d):
        return struct.pack(">I", len(d)) + t + d + struct.pack(">I", zlib.crc32(t + d) & 0xFFFFFFFF)
    rows = b"".join(b"\0" + rgba[y * w * 4:(y + 1) * w * 4] for y in range(h))
    png = (b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
           + chunk(b"IDAT", zlib.compress(rows, 6)) + chunk(b"IEND", b""))
    with open(path, "wb") as f:
        f.write(png)


def export(tpl, outdir, stem):
    os.makedirs(outdir, exist_ok=True)
    paths = []
    for i, img in enumerate(tpl.images):
        w, h, rgba = img.decode()
        p = os.path.join(outdir, "%s_%d.png" % (stem, i))
        write_png(p, w, h, rgba)
        paths.append(p)
    return paths


def _iter_tpls(root):
    """Yield (label, raw) for every TPL under root, including inside packs."""
    from pack import Pack
    for dp, _, fns in os.walk(root):
        for fn in sorted(fns):
            p = os.path.join(dp, fn)
            if not fn.endswith((".tpl", ".cms", ".cmp")):
                continue
            try:
                raw = load(p)
            except Exception:
                continue
            if TPL.check(raw):
                yield p, raw
            elif raw[:4] == b"pack":
                try:
                    pk = Pack(raw)
                except Exception:
                    continue
                for n, d in pk.items():
                    if TPL.check(d):
                        yield p + ":" + n, d


def survey(root):
    hist = {}
    pal = {}
    nfiles = 0
    for label, raw in _iter_tpls(root):
        nfiles += 1
        try:
            t = TPL(raw)
        except Exception as e:
            print("ERR", label, e)
            continue
        for img in t.images:
            hist[img.format_name] = hist.get(img.format_name, 0) + 1
            if img.palette_format is not None:
                k = PALETTE_FORMATS.get(img.palette_format, str(img.palette_format))
                pal[k] = pal.get(k, 0) + 1
    print("%d TPL files" % nfiles)
    for k, v in sorted(hist.items(), key=lambda kv: -kv[1]):
        print("  %-8s %6d images" % (k, v))
    for k, v in sorted(pal.items()):
        print("  palette %-6s %d" % (k, v))


if __name__ == "__main__":
    if len(sys.argv) == 3 and sys.argv[1] == "--survey":
        survey(sys.argv[2])
    elif len(sys.argv) == 3:
        src = sys.argv[1]
        t = TPL.from_file(src)
        stem = os.path.splitext(os.path.basename(src))[0]
        for i, (img, p) in enumerate(zip(t.images, export(t, sys.argv[2], stem))):
            print("%2d %-7s %4dx%-4d mips=%d -> %s" % (i, img.format_name, img.width, img.height,
                                                    img.mip_count, p))
    else:
        sys.exit("usage: tpl.py IN.tpl|.cms OUTDIR   |   tpl.py --survey DIR")
