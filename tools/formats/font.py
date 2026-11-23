"""Reader for FE10 bitmap fonts (Fonts/*.cms, LZ10-compressed).

Layout after decompression (big-endian; field names partly guessed, see
docs/formats/text.md):
  0x00 u16 0
  0x02 u16 first_code         lowest character code (0x20)
  0x04 u16 last_code          highest character code (Shift-JIS, e.g. 0xEA74)
  0x06 u16 0
  0x08 u16 line_height        e.g. 24 for talk.cms
  0x0A u16 unk_0A
  0x0C u16 baseline/ascent?   e.g. 19
  0x0E u8[8] 0
  0x16 u16 sheet_bytes        bytes per texture sheet (0x8000)
  0x18 u32 sheet_count
  0x1C u32 sheet_width        texels
  0x20 u16 sheet_height       texels
  0x22 u16 glyph_table_offset (0x30)
  0x24 u32 texture_offset     start of sheet data; also end of glyph table
  0x28 u32 texture_size       sheet_count * sheet_bytes
  0x30 glyph[(texture_offset - 0x30) / 16], sorted by code:
         u16 code (ASCII or Shift-JIS), u16 sheet, u16 x, u16 y,
         u8 width, u8 height, u8 x_offset, u8 y_offset?, u8 advance, u8[3] 0
  texture_offset: sheets, GX I4 (4-bit intensity, 8x8 tiles)

CLI: font.py Fonts/talk.cms [OUTDIR]   (prints header/glyph count; with
OUTDIR writes sheet_NN.png and glyphs.json)
"""
import json
import os
import struct
import sys
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from lz10 import load  # noqa: E402


class Font:
    def __init__(self, raw: bytes):
        h = struct.unpack_from(">7H", raw, 0)
        self.first_code, self.last_code = h[1], h[2]
        self.line_height, self.unk_0a, self.ascent = h[4], h[5], h[6]
        (self.sheet_bytes,) = struct.unpack_from(">H", raw, 0x16)
        (self.sheet_count, self.sheet_width) = struct.unpack_from(">2I", raw, 0x18)
        (self.sheet_height, self.glyph_off) = struct.unpack_from(">2H", raw, 0x20)
        (self.tex_off, self.tex_size) = struct.unpack_from(">2I", raw, 0x24)
        self.raw = raw
        self.glyphs = {}
        for o in range(self.glyph_off, self.tex_off, 16):
            code, sheet, x, y = struct.unpack_from(">4H", raw, o)
            w, hgt, xo, yo, adv = raw[o + 8:o + 13]
            self.glyphs[code] = dict(code=code, sheet=sheet, x=x, y=y, w=w,
                                     h=hgt, x_off=xo, y_off=yo, advance=adv)

    def char(self, ch: str):
        b = ch.encode("shift_jis")
        code = b[0] if len(b) == 1 else b[0] << 8 | b[1]
        return self.glyphs.get(code)

    def sheet_pixels(self, i):
        """Decode sheet i (GX I4) to a list of rows of 0..255 values."""
        w, h = self.sheet_width, self.sheet_height
        d = self.raw[self.tex_off + i * self.sheet_bytes:]
        px = [[0] * w for _ in range(h)]
        p = 0
        for ty in range(0, h, 8):
            for tx in range(0, w, 8):
                for y in range(8):
                    for x in range(0, 8, 2):
                        b = d[p]
                        p += 1
                        px[ty + y][tx + x] = (b >> 4) * 17
                        px[ty + y][tx + x + 1] = (b & 15) * 17
        return px


def write_gray_png(path, rows):
    h, w = len(rows), len(rows[0])
    raw = b"".join(b"\0" + bytes(r) for r in rows)

    def chunk(t, d):
        c = struct.pack(">I", len(d)) + t + d
        return c + struct.pack(">I", zlib.crc32(t + d) & 0xFFFFFFFF)
    with open(path, "wb") as f:
        f.write(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">2I5B", w, h, 8, 0, 0, 0, 0))
                + chunk(b"IDAT", zlib.compress(raw, 9)) + chunk(b"IEND", b""))


if __name__ == "__main__":
    f = Font(load(sys.argv[1]))
    print("codes 0x%04X-0x%04X, %d glyphs, line_height %d, %d sheets %dx%d" % (
        f.first_code, f.last_code, len(f.glyphs), f.line_height,
        f.sheet_count, f.sheet_width, f.sheet_height))
    if len(sys.argv) > 2:
        out = sys.argv[2]
        os.makedirs(out, exist_ok=True)
        for i in range(f.sheet_count):
            write_gray_png(os.path.join(out, "sheet_%02d.png" % i), f.sheet_pixels(i))
        with open(os.path.join(out, "glyphs.json"), "w") as fp:
            json.dump(list(f.glyphs.values()), fp)
