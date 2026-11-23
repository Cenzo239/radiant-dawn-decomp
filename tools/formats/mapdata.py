"""Reader for FE10 map data: map.bin inside zmap/<map>/map.cmp (also map.pak,
and zbg/<bg>/bf.cmp|bf.pak battle backgrounds, which use the same format).

See docs/formats/maps_events.md, section 2 "Map grid and scenery (map.bin)".

map.bin is an IS binary container (isbin.py) with labels "<map>:<section>".
Loader: fn_80139xxx (80138000.c ~l.1170) -> fn_80136164 (mapdata),
fn_80136348 (maplight), fn_8013677C (mapfog), fn_801369BC (mapshader),
fn_801C9FC4 (mapdesc), fn_801CBA60 (mapinst), fn_80137BC8 (panels),
fn_801379F8 / fn_80138000 (roof), fn_80136C34 (maplink*).
Instance matrix: fn_801CC5CC.  Lights: fn_801364AC -> fn_800110F4 /
fn_80011280 (GX light objects).  Fog: fn_801368DC.

Coordinate systems (all verified, see the doc):
  model units   : what .gs vertices use. 1 tile = 5 model units.
  map space     : engine units before the map root matrix. X = tile column,
                  Z = tile row, Y = up. 1 tile = 1 unit for battle maps
                  (k = map+0xD0 = 0.2, U = 5k = 1). Panel heights h are s16
                  with h/2000 tiles, NEGATIVE = UP: y = -h / 2000 * U.
  engine world  : map space * root E4 = Rx(+270 deg) [* mirror * Ry * T];
                  for the port, map space is the useful frame.
"""
import math
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from isbin import ISBin, open_file as _open_isbin  # noqa: E402

TERRAIN_COUNT = 199
TILE_MODEL_UNITS = 5.0          # lbl_804CDE7C / lbl_804CF72C
K_BATTLE = 0.2                  # lbl_804CDEC0 (zmap/*/map.*)
K_BACKGROUND = 3.0              # lbl_804CDEC4 (zbg/*/bf.*)


def _sc(v):
    return v - 256 if v > 127 else v


def _f32(d, o):
    return struct.unpack_from(">f", d, o)[0]


# ------------------------------------------------------------------ terrain
def terrain_hash(name_bytes):
    h = 0
    for c in name_bytes:
        h = ((h + c) * 16) & 0xFFFFFFFF
    return h


def load_terrain_table(fe10data_path):
    """[(index, name)] from FE10Data.cms TerrainData (16-byte entries,
    name pointer first; the table starts 4 bytes after the label)."""
    b = _open_isbin(fe10data_path)
    base = b.labels["TerrainData"] + 4
    return [(i, b.str_at_ptr(base + 16 * i)) for i in range(TERRAIN_COUNT)]


def terrain_lookup(table):
    """name -> terrain id, replicating fn_8011D1E4 (first hash match wins)."""
    out = {}
    for i, name in table:
        h = terrain_hash(name.encode("shift_jis"))
        idx = 0xB6 if i in (0xB0, 0xB6) else i
        out.setdefault(h, idx)
    return lambda n: out.get(terrain_hash(n.encode("shift_jis")), 0)


# ------------------------------------------------------------------ matrices
# 3x4 row-major affine matrices, column vectors (PSMTX convention).
def m_identity():
    return [[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0]]


def m_mul(a, b):
    r = []
    for i in range(3):
        row = []
        for j in range(4):
            v = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j]
            if j == 3:
                v += a[i][3]
            row.append(v)
        r.append(row)
    return r


def m_trans(x, y, z):
    return [[1.0, 0.0, 0.0, x], [0.0, 1.0, 0.0, y], [0.0, 0.0, 1.0, z]]


def m_scale(x, y, z):
    return [[x, 0.0, 0.0, 0.0], [0.0, y, 0.0, 0.0], [0.0, 0.0, z, 0.0]]


def m_rot(axis, rad):
    """PSMTXRotRad (fn_80312654): axis 'x' / 'y' / 'z'."""
    c, s = math.cos(rad), math.sin(rad)
    if axis == "x":
        return [[1.0, 0.0, 0.0, 0.0], [0.0, c, -s, 0.0], [0.0, s, c, 0.0]]
    if axis == "y":
        return [[c, 0.0, s, 0.0], [0.0, 1.0, 0.0, 0.0], [-s, 0.0, c, 0.0]]
    return [[c, -s, 0.0, 0.0], [s, c, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0]]


def m_apply(m, v):
    return tuple(m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2] + m[i][3] for i in range(3))


def m_apply_dir(m, v):
    return tuple(m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2] for i in range(3))


# root matrix of a battle map (fn_80138000.c l.2108: map+0xB1 == 0, no
# mirror, map+0xD4..0xE0 = 0): engine_world = ROOT_BATTLE * map_space
ROOT_BATTLE = m_rot("x", 4.71238899230957)

# ------------------------------------------------------------------ flags
HEADER_FLAG_BITS = {
    0x10000000: "roof_rects",       # fn_801379F8: roof panels over mapinst rects
    0x40000000: "multipass_props",  # fn_80134ECC: props drawn in 3 extra passes
}
DESC_FLAG_BITS = {
    0x00000002: "roof_sets_base",   # fn_801379F8: roof panels also overwrite base heights
    0x00000010: "pass_80/no_roof",  # draw pass 0x80; excludes roof logic (fn_801CA1E8)
    0x00000020: "pass_95",
    0x00000040: "pass_8C/shadow?",  # also object flags 0x30000; fn_8012FCD0 snapping
    0x00000080: "pass_8B",
    0x00000100: "common",           # set on almost every prop (meaning unknown)
    0x00000200: "animated",         # loads <model>.ga (fn_801C9FC4)
    0x00000400: "",
    0x00000800: "pass_94/roof",     # fn_801CA1E8: object owns a roof rect
    0x00001000: "roof",             # fn_801CA1E8
    0x00002000: "translucent",      # pass 0x93, material "map_trans"
    0x00004000: "anim_range_node",  # anim length from node 0x37 info
    0x00010000: "",
    0x00020000: "pass_8A/hidden",   # with 0x40000000 -> instance flag 4 (not drawn)
    0x00040000: "hide_near_units",  # hidden while a unit is on/next to its rect
    0x00100000: "",                 # fn_801CA228
    0x00800000: "anim_random_phase",
    0x01000000: "door_like",        # fn_801CA688 / 8013C000 l.192
    0x04000000: "pass_93_bg",       # backgrounds (map+0xB1 != 0)
    0x08000000: "bbox_squash",      # fn_801CCA38: min.y lerp by mapshader+0x58
    0x10000000: "scale_y_curve",    # fn_801CC5CC: y scale = fn_8001ECE4(s)
    0x20000000: "",
    0x40000000: "hidden",
}


def flag_names(value, table):
    return [table.get(1 << i) or "bit%d" % i for i in range(32) if value >> i & 1]


# ------------------------------------------------------------------ header
def parse_header(b, o):
    """mapdata (fn_80136164). 0x20/0x24/0x28 bytes for version 2/3/4."""
    d = b.data
    flags = struct.unpack_from(">I", d, o + 0x14)[0]
    h = {
        "version": d[o],
        "width": d[o + 2],
        "height": d[o + 3],
        "mapdesc_count": struct.unpack_from(">H", d, o + 4)[0],
        "mapinst_count": struct.unpack_from(">H", d, o + 6)[0],
        "height_div": _f32(d, o + 8),            # 2000.0: tile = h / height_div
        # 0x0C..0x11 -> map+0xAB..0xB0, used by the shadow projection
        # (fn_80141650 / fn_80141DCC)
        "bg_origin": (_sc(d[o + 0x0C]), _sc(d[o + 0x0D])),   # = -(x,y) of the big ground model
        "shadow_center": (_sc(d[o + 0x0E]), _sc(d[o + 0x0F])),  # ~ (w/2, h/2) tiles
        "shadow_size": d[o + 0x10],              # projection extent, tiles (/2 = half)
        "unk_11": d[o + 0x11],
        "fow_fill": d[o + 0x12],                 # lbl_804CA734: fog-of-war texture fill
        "flags": flags,
        "flag_names": flag_names(flags & 0xF003FFFF, HEADER_FLAG_BITS),
        "fow_mode": {0: 0, 0x80000: 1, 0xC0000: 2, 0x40000: 3}[flags & 0xC0000],  # lbl_804CB830
        "env_type": (flags >> 20) & 0x1F,        # -> lbl_804CB834 (fn_8013A35C), battle bg set?
        "grid_rgba": (d[o + 0x19], d[o + 0x1A], d[o + 0x1B], d[o + 0x18]),  # map+0xB8..0xBB
        "scroll": {"enable": d[o + 0x1C], "dx": _sc(d[o + 0x1D]), "dy": _sc(d[o + 0x1E]),
                   "period": d[o + 0x1F]},      # lbl_804CB84C/4F/50/51 (wrapping maps)
    }
    if h["version"] > 2:
        h["effect"] = b.str_at_ptr(o + 0x20)   # fn_801194FC: invalid/thunder/water/... -> map+0x4E
    if h["version"] > 3:
        h["depth_clamp"] = _f32(d, o + 0x24)   # map+0xC8: max height (tiles, +down), fn_8011843C
    return h


def _panels(b, off, count):
    d = b.data
    out = []
    for i in range(count):
        p = off + 12 * i
        out.append({"heights": list(struct.unpack_from(">4h", d, p)),
                    "terrain": b.str_at_ptr(p + 8)})
    return out


class MapData:
    def __init__(self, b: ISBin, k=K_BATTLE, pack=None):
        self.bin = b
        self.k = k                       # map+0xD0
        self.unit = TILE_MODEL_UNITS * k  # map-space units per tile (1.0 for battle maps)
        self.pack = pack
        self.sections = {}
        self.prefix = None
        for name, off in b.labels.items():
            pre, colon, sec = name.partition(":")
            if not colon:
                pre, sec = None, name
            self.prefix = pre
            self.sections[sec] = off
        ends = sorted(self.sections.values()) + [b.data_size]
        self.section_size = {k_: min(e for e in ends if e > v) - v for k_, v in self.sections.items()}
        if "mapdata" not in self.sections:
            # 6 zbg test backgrounds use an older layout (mapbuilddescB,
            # mapbuildinstB, mapcapacityB, mapextraB, mapfogB, maplightB)
            raise ValueError("no mapdata section (old 'B' layout: %s)" % sorted(self.sections))
        self.header = parse_header(b, self.sections["mapdata"])
        self.width, self.height = self.header["width"], self.header["height"]
        self.layers = {}
        for layer, pan, idx in (("main", "uniquepanel", "panelindex"),
                                ("roof", "roofpanel", "roofindex"),
                                ("base", "basepanel", "baseindex")):
            if pan in self.sections and idx in self.sections:
                n = self.section_size[pan] // 12
                panels = _panels(b, self.sections[pan], n)
                grid = list(struct.unpack_from(">%dH" % (self.width * self.height),
                                               b.data, self.sections[idx]))
                self.layers[layer] = (panels, grid)
        self._desc = None
        self._inst = None

    # -------------------------------------------------------------- grid
    def tile(self, x, y, layer="main"):
        panels, grid = self.layers[layer]
        return panels[grid[y * self.width + x]]

    def terrain_grid(self, layer="main"):
        panels, grid = self.layers[layer]
        return [[panels[grid[y * self.width + x]]["terrain"] for x in range(self.width)]
                for y in range(self.height)]

    def corner_heights(self, x, y, layer="base"):
        """Map-space Y (up) of the 4 corners (x0z0, x1z0, x0z1, x1z1).
        'base' = ground used for units (fn_80114728 etc.), falls back to main."""
        if layer not in self.layers:
            layer = "main"
        h = self.tile(x, y, layer)["heights"]
        return [-v / self.header["height_div"] * self.unit for v in h]

    def ground_height(self, x, y, layer="base"):
        return sum(self.corner_heights(x, y, layer)) / 4.0

    def terrain_mesh(self, layer="base"):
        """(vertices, quads) of the panel surface in map space, 4 verts per tile."""
        verts, quads = [], []
        u = self.unit
        for y in range(self.height):
            for x in range(self.width):
                c = self.corner_heights(x, y, layer)
                i = len(verts)
                verts += [(x * u, c[0], y * u), ((x + 1) * u, c[1], y * u),
                          (x * u, c[2], (y + 1) * u), ((x + 1) * u, c[3], (y + 1) * u)]
                quads.append((i, i + 2, i + 3, i + 1))
        return verts, quads

    # -------------------------------------------------------------- scenery
    def mapdesc(self):
        """Model descriptors (fn_801C9FC4, runtime 0xC0 bytes)."""
        if self._desc is None:
            d, o = self.bin.data, self.sections.get("mapdesc")
            out = []
            for i in range(self.header["mapdesc_count"]):
                p = o + 0x24 * i
                fl = struct.unpack_from(">I", d, p + 0x18)[0]
                name = self.bin.str_at_ptr(p + 0x1C)
                out.append({"index": i, "model": name,
                            "files": {"g": name + ".g", "gs": name + ".gs",
                                      "ga": name + ".ga" if fl & 0x200 else None},
                            "bbox": [round(v, 4) for v in struct.unpack_from(">6f", d, p)],
                            "flags": fl, "flag_names": flag_names(fl, DESC_FLAG_BITS),
                            "footprint": (d[p + 0x20], d[p + 0x21]),   # tiles w (x), d (z)
                            "unk_22": struct.unpack_from(">H", d, p + 0x22)[0]})
            self._desc = out
        return self._desc

    def instance_matrix(self, inst, desc=None):
        """Map-space 3x4 matrix of a prop, per fn_801CC5CC (anim offsets = 0)."""
        desc = desc or self.mapdesc()[inst["desc"]]
        k, u = self.k, self.unit
        half = 0.5 * u
        m = m_scale(k, k, k)
        s = inst["scale"]
        if s != 1.0:
            sy = s    # desc flag 0x10000000: fn_8001ECE4(0, 1, 1, s, 2) instead (approximated)
            w, dd = desc["footprint"][0] * half, desc["footprint"][1] * half
            m = m_mul(m_mul(m_trans(w, 0, dd), m_mul(m_scale(s, sy, s), m_trans(-w, 0, -dd))), m)
        if inst["mirror"]:
            m = m_mul(m_mul(m_trans(desc["footprint"][0] * u, 0, 0), m_scale(-1, 1, 1)), m)
        rot = m_mul(m_trans(half, 0, half),
                    m_mul(m_rot("y", math.radians(inst["rot_deg"])), m_trans(-half, 0, -half)))
        m = m_mul(rot, m)
        m = m_mul(m_trans(inst["pos"][0] * u, -inst["height"] * u, inst["pos"][1] * u), m)
        return m

    def mapinst(self):
        """Placed props (fn_801CBA60, runtime 0xD0 bytes each)."""
        if self._inst is None:
            d, o = self.bin.data, self.sections.get("mapinst")
            descs = self.mapdesc()
            out = []
            for i in range(self.header["mapinst_count"]):
                p = o + 0x14 * i
                rot = d[p + 3]
                rot16 = int(64.0 * (360 - ((rot * 360) >> 8)))   # runtime +0x0A, 1/64 deg
                ce, cf = struct.unpack_from(">bb", d, p + 4)
                inst = {"index": i, "flags": d[p], "mirror": bool(d[p] & 1),
                        "x": _sc(d[p + 1]), "y": _sc(d[p + 2]),
                        "rot": rot, "rot_deg": (rot16 / 64.0) % 360.0,
                        "sub": (ce, cf),                      # 1/64 tile offsets
                        "desc": struct.unpack_from(">H", d, p + 6)[0],
                        "rect": [_sc(v) for v in d[p + 8:p + 12]],   # x0, y0, x1, y1
                        "height": _f32(d, p + 12),            # tiles, NEGATIVE = up
                        "scale": d[p + 16] / 64.0,
                        "pad": d[p + 17:p + 20].hex()}
                inst["pos"] = (inst["x"] + ce / 64.0, inst["y"] + cf / 64.0)
                inst["model"] = descs[inst["desc"]]["model"]
                inst["matrix"] = [[round(v, 6) for v in row]
                                  for row in self.instance_matrix(inst, descs[inst["desc"]])]
                out.append(inst)
            self._inst = out
        return self._inst

    # -------------------------------------------------------------- lighting
    def maplight(self):
        """fn_80136348 + fn_801364AC. Angles are Euler degrees; the light
        direction is Rz(c)*Ry(b)*Rx(a)*(0,0,-1) (fn_800110F4) in map space."""
        if "maplight" not in self.sections:
            return None
        d, o = self.bin.data, self.sections["maplight"]
        a, b_, c = struct.unpack_from(">3h", d, o + 2)
        r = m_mul(m_rot("z", math.radians(c)), m_mul(m_rot("y", math.radians(b_)),
                                                     m_rot("x", math.radians(a))))
        dv = m_apply_dir(r, (0.0, 0.0, -1.0))
        sets = []
        for i in range(4):
            q = o + 8 + 6 * i
            sets.append({"ambient": tuple(d[q:q + 3]), "light": tuple(d[q + 3:q + 6])})
        return {"unk": list(d[o:o + 2]), "angles_deg": (a, b_, c),
                "direction": tuple(round(v, 6) for v in dv),
                "direction_world": tuple(round(v, 6) for v in m_apply_dir(ROOT_BATTLE, dv)),
                "sets": sets}

    def mapfog(self):
        """fn_8013677C / fn_801368DC. Distances in map-space units (= tiles)."""
        if "mapfog" not in self.sections:
            return None
        d, o = self.bin.data, self.sections["mapfog"]
        enabled = d[o + 1]
        scale = TILE_MODEL_UNITS * self.k
        return {"unk0": d[o], "enabled": enabled, "type_raw": d[o + 2],
                "type": (d[o + 2] + 1) if enabled else 0,   # lbl_804CB839
                "start": d[o + 3] * scale, "end": d[o + 4] * scale,
                "color": tuple(d[o + 5:o + 8]), "unk8": d[o + 8],
                "rest": d[o + 9:o + 12].hex()}

    def mapshader(self):
        """fn_801369BC; fields named by their runtime map-struct offsets."""
        if "mapshader" not in self.sections:
            return None
        d, o = self.bin.data, self.sections["mapshader"]
        v = d[o]
        s = {"version": v, "m54": list(d[o + 1:o + 5]),
             "m58_bbox_lerp": d[o + 5] / 100.0,        # used if m54[2] (+0x56) != 0
             "m5C": struct.unpack_from(">h", d, o + 6)[0] / 100.0,
             "m64": d[o + 8], "m65": d[o + 9], "m66_rgba": tuple(d[o + 10:o + 14])}
        p = o + 14
        if v >= 1:
            s["m60_rgba"] = tuple(d[p:p + 4])
            p += 4
        if v >= 2:
            s["material_override"] = {"desc": d[p] - 1, "m25": d[p + 1], "m28": d[p + 2],
                                      "m2B_rgb": tuple(d[p + 3:p + 6])}
            p += 6
        s["size"] = p - o
        return s

    def maplinks(self):
        """maplink / maplinkAt / maplinkAbs (fn_80136C34): per-tile u16 link
        word at DAT_803f1926[y*64+x]; bits 1/2/4/8 = W/E/S/N neighbour, bits
        8..11 = same set for maplinkAt (fn_800392FC/800395F4)."""
        out = {}
        for name in ("maplink", "maplinkAt", "maplinkAbs"):
            if name in self.sections:
                d, o = self.bin.data, self.sections[name]
                n = struct.unpack_from(">H", d, o + 2)[0]
                out[name] = [(_sc(d[o + 4 + 3 * i]), _sc(d[o + 5 + 3 * i]), d[o + 6 + 3 * i])
                             for i in range(n)]
        return out

    def raw_section(self, name):
        o = self.sections[name]
        return self.bin.data[o:o + self.section_size[name]]

    def to_dict(self, lookup=None):
        out = {"name": self.prefix, "k": self.k, "unit": self.unit, "header": self.header,
               "sections": {k: {"offset": v, "size": self.section_size[k]}
                            for k, v in sorted(self.sections.items(), key=lambda kv: kv[1])},
               "layers": {}, "mapdesc": self.mapdesc(), "mapinst": self.mapinst(),
               "maplight": self.maplight(), "mapfog": self.mapfog(),
               "mapshader": self.mapshader(), "maplinks": self.maplinks()}
        for layer, (panels, grid) in self.layers.items():
            if lookup:
                for p in panels:
                    p["terrain_id"] = lookup(p["terrain"])
            out["layers"][layer] = {"panels": panels, "index": grid}
        return out


# ------------------------------------------------------------------ loading
def _k_for(path):
    return K_BACKGROUND if os.path.basename(path).startswith("bf.") else K_BATTLE


def open_file(path):
    """Accepts map.cmp / map.pak / bf.cmp / bf.pak, a raw map.bin, or a
    zmap/<map> (or zbg/<bg>) directory."""
    if os.path.isdir(path):
        for n in ("map.cmp", "map.pak", "bf.cmp", "bf.pak"):
            if os.path.exists(os.path.join(path, n)):
                path = os.path.join(path, n)
                break
    if path.endswith((".cmp", ".pak")):
        from pack import open_file as open_pack
        pk = open_pack(path)
        return MapData(ISBin(pk.get("map.bin")), _k_for(path), pk)
    with open(path, "rb") as f:
        raw = f.read()
    return MapData(ISBin(raw))


# ------------------------------------------------------------------ output
def ascii_grid(m, lookup=None, layer="main"):
    grid = m.terrain_grid(layer)
    names = sorted({n for row in grid for n in row})
    sym = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    key = {n: sym[i % len(sym)] for i, n in enumerate(names)}
    lines = ["     " + "".join(str(x // 10) if x % 10 == 0 else " " for x in range(m.width))]
    for y, row in enumerate(grid):
        lines.append("%3d  %s" % (y, "".join(key[n] for n in row)))
    lines.append("")
    for n in names:
        tid = (" id %3d" % lookup(n)) if lookup else ""
        cnt = sum(row.count(n) for row in grid)
        lines.append("  %s = %s%s  (%d tiles)" % (key[n], n, tid, cnt))
    return "\n".join(lines)


def props_text(m):
    lines = ["#    model                 tile(x,y)   pos(x,z)          height  rot    scale mir  rect"]
    for i in m.mapinst():
        t = i["matrix"]
        lines.append("%-4d %-20s %4d,%-4d  %7.3f,%-8.3f  %6.2f  %6.1f %5.2f %-3s  %s  T=(%.3f, %.3f, %.3f)" % (
            i["index"], i["model"], i["x"], i["y"], i["pos"][0], i["pos"][1], -i["height"],
            i["rot_deg"], i["scale"], "M" if i["mirror"] else "", i["rect"], t[0][3], t[1][3], t[2][3]))
    return "\n".join(lines)


def export_obj(m, outdir, terrain=True, tex=False, stem=None):
    """One OBJ scene (map space) with every prop placed through gmodel.py.
    Static rest pose; envelope-skinned meshes are skipped (gmodel limitation)."""
    import gmodel
    if m.pack is None:
        raise ValueError("need the pack (map.cmp) to read models")
    stem = stem or m.prefix
    os.makedirs(outdir, exist_ok=True)
    cache, mtl, texfiles = {}, [], {}
    tpl = None
    if tex and "texpack.tpl" in m.pack.names():
        from tpl import TPL
        tpl = TPL(m.pack.get("texpack.tpl"))
    vl, tl, fl = [], [], []
    names = set(m.pack.names())

    def load(model):
        if model not in cache:
            if model + ".gs" not in names:
                cache[model] = None
            else:
                gm = gmodel.GModel.from_bytes(m.pack.get(model + ".gs"))
                skin = None
                if model + ".g" in names:
                    sc = gmodel.GScene.from_bytes(m.pack.get(model + ".g"))
                    skin = sc.skin_matrices(sc.world_matrices())
                cache[model] = (gm, skin)
                for mi, mat in enumerate(gm.materials):
                    mtl.append("newmtl %s_m%d\nKd %.3f %.3f %.3f\n" % (
                        model, mi, mat.color0[0] / 255.0, mat.color0[1] / 255.0, mat.color0[2] / 255.0))
                    if tpl and mat.layers and mat.layers[0].texture < len(tpl.images):
                        ti = mat.layers[0].texture
                        if ti not in texfiles:
                            from tpl import write_png
                            w, h, rgba = tpl.images[ti].decode()
                            texfiles[ti] = "%s_tex%d.png" % (stem, ti)
                            write_png(os.path.join(outdir, texfiles[ti]), w, h, rgba)
                        mtl.append("map_Kd %s\n" % texfiles[ti])
        return cache[model]

    if terrain:
        verts, quads = m.terrain_mesh()
        fl.append("g terrain_panels\nusemtl terrain\n")
        mtl.append("newmtl terrain\nKd 0.4 0.6 0.4\n")
        base = len(vl)
        vl += ["v %.4f %.4f %.4f\n" % v for v in verts]
        fl += ["f %d %d %d %d\n" % tuple(base + i + 1 for i in q) for q in quads]
    skipped = 0
    for inst in m.mapinst():
        got = load(inst["model"])
        if got is None:
            skipped += 1
            continue
        gm, skin = got
        im = inst["matrix"]
        fl.append("g inst%d_%s\n" % (inst["index"], inst["model"]))
        for mesh in gm.meshes:
            if mesh.uses_envelope:
                continue
            fl.append("usemtl %s_m%d\n" % (inst["model"], mesh.material))
            for tri in mesh.triangles():
                idx = []
                for v in tri:
                    pos = gm.positions[v["pos"]]
                    if skin:
                        node = mesh.palette[v.get("pnmtx", 0) // 3] if mesh.palette else mesh.node
                        if 0 <= node < len(skin):
                            pos = gmodel.mat_apply(skin[node], pos)
                    vl.append("v %.4f %.4f %.4f\n" % m_apply(im, pos))
                    ti = ""
                    if "tex0" in v and gm.texcoords:
                        uu, tt = gm.texcoords[v["tex0"]]
                        tl.append("vt %.5f %.5f\n" % (uu, 1.0 - tt))
                        ti = len(tl)
                    idx.append("%d/%s" % (len(vl), ti))
                fl.append("f %s\n" % " ".join(idx))
    with open(os.path.join(outdir, stem + ".mtl"), "w") as f:
        f.writelines(mtl)
    with open(os.path.join(outdir, stem + ".obj"), "w") as f:
        f.write("mtllib %s.mtl\n# map space: 1 tile = %.3f, +Y up\n" % (stem, m.unit))
        f.writelines(vl)
        f.writelines(tl)
        f.writelines(fl)
    return os.path.join(outdir, stem + ".obj"), skipped


if __name__ == "__main__":
    import argparse
    import json
    ap = argparse.ArgumentParser(description="FE10 map.bin (battle map grid + scenery) dump")
    ap.add_argument("file", help="zmap/<map>/map.cmp|.pak, zbg/<bg>/bf.*, a map.bin, or the directory")
    ap.add_argument("--terrain", metavar="FE10Data.cms", help="resolve terrain ids")
    ap.add_argument("--layer", default="main", choices=("main", "roof", "base"))
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--props", action="store_true", help="list placed props with transforms")
    ap.add_argument("--env", action="store_true", help="light / fog / shader / links")
    ap.add_argument("--obj", metavar="OUTDIR", help="write terrain panels + placed props as one OBJ")
    ap.add_argument("--tex", action="store_true", help="with --obj: also decode texpack textures")
    a = ap.parse_args()
    m = open_file(a.file)
    lookup = terrain_lookup(load_terrain_table(a.terrain)) if a.terrain else None
    if a.json:
        print(json.dumps(m.to_dict(lookup), ensure_ascii=False, indent=1))
    elif a.props:
        for d in m.mapdesc():
            print("desc %-3d %-20s fp=%dx%d flags=%08x %s bbox=%s" % (
                d["index"], d["model"], d["footprint"][0], d["footprint"][1], d["flags"],
                ",".join(d["flag_names"]), d["bbox"]))
        print()
        print(props_text(m))
    elif a.obj:
        path, skipped = export_obj(m, a.obj, tex=a.tex)
        print("wrote %s (%d instances, %d without model)" % (path, len(m.mapinst()), skipped))
    elif a.env:
        print(json.dumps({"header": m.header, "maplight": m.maplight(), "mapfog": m.mapfog(),
                          "mapshader": m.mapshader(), "maplinks": m.maplinks()},
                         ensure_ascii=False, indent=1))
    else:
        h = m.header
        print("%s  %dx%d  version %d  mapdesc %d  mapinst %d  flags %08x  effect %s" % (
            m.prefix, m.width, m.height, h["version"], h["mapdesc_count"],
            h["mapinst_count"], h["flags"], h.get("effect")))
        print("sections: " + ", ".join("%s@%x(%d)" % (k, v, m.section_size[k]) for k, v in
                                       sorted(m.sections.items(), key=lambda kv: kv[1])))
        print("layers: " + ", ".join(m.layers))
        print()
        print(ascii_grid(m, lookup, a.layer))
