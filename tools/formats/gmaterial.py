"""FE10 model material -> GX render state (TEV, texgen, lighting channels,
blend, alpha compare, z, cull, fog), resolved exactly the way main.dol does it.

See docs/formats/materials.md for the derivation (Ghidra function per item).
This module re-runs the game's state setup symbolically, with the default
per-object state (object colour 0x80/0x80/0x80, alpha 0xFF, no object flags,
no material animation), and records every GX call it would make:

    fn_8001444C  material setup driver (per draw batch)
      fn_80012F00  one TEV stage per texture layer, switch on layer blend mode 0..7
      fn_80014158  material flag 0x40: screen-copy refraction (indirect)
      fn_800125A8  material colour -> GXSetChanMatColor (+ extra TEV stages)
      fn_80013CF0  lighting channels (+ specular stage, material flag 0x1)
      fn_800140A0  cull mode from mesh flags 0x1800
      fn_8001393C  emboss layers (mode 6), multi-layer RAS stage, env map (flag 0x80)
    fn_80011838  per-pass state (mesh list 1/2/3 -> opaque / alpha test / translucent)
    fn_800186C8  material blend / z / fog overrides (flags 0xE000, 0x30, 0x8)

Library:
    from gmaterial import resolve_model
    desc = resolve_model(model, tpl=None, context="zmap")  # list of plain dicts
CLI:
    gmaterial.py FILE.gs|PACK.cmp [--gs NAME] [--json] [--tpl F.tpl]
    gmaterial.py --survey DIR [--json OUT.json]
Python 3.9 standard library only.
"""
import json
import os
import struct
import sys
from collections import Counter, OrderedDict, defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gmodel import GModel  # noqa: E402

# ------------------------------------------------------------------ GX enums
TEV_CIN = ["CPREV", "APREV", "C0", "A0", "C1", "A1", "C2", "A2",
           "TEXC", "TEXA", "RASC", "RASA", "ONE", "HALF", "KONST", "ZERO"]
TEV_AIN = ["APREV", "A0", "A1", "A2", "TEXA", "RASA", "KONST", "ZERO"]
TEV_OP = {0: "ADD", 1: "SUB"}
TEV_BIAS = ["ZERO", "ADDHALF", "SUBHALF"]
TEV_SCALE = ["1", "2", "4", "1/2"]
TEV_REG = ["PREV", "REG0", "REG1", "REG2"]
CHANNEL = {0: "COLOR0", 1: "COLOR1", 2: "ALPHA0", 3: "ALPHA1", 4: "COLOR0A0",
           5: "COLOR1A1", 0xFF: "NULL"}
TG_TYPE = {0: "MTX3x4", 1: "MTX2x4", 2: "BUMP0", 10: "SRTG"}
TG_SRC = {0: "POS", 1: "NRM", 2: "BINRM", 3: "TANGENT", 19: "COLOR0", 20: "COLOR1"}
TG_SRC.update({4 + i: "TEX%d" % i for i in range(8)})
TG_SRC.update({12 + i: "TEXCOORD%d" % i for i in range(7)})
BL_TYPE = ["NONE", "BLEND", "LOGIC", "SUBTRACT"]
BL_SRC = ["ZERO", "ONE", "DSTCLR", "INVDSTCLR", "SRCALPHA", "INVSRCALPHA", "DSTALPHA", "INVDSTALPHA"]
BL_DST = ["ZERO", "ONE", "SRCCLR", "INVSRCCLR", "SRCALPHA", "INVSRCALPHA", "DSTALPHA", "INVDSTALPHA"]
COMPARE = ["NEVER", "LESS", "EQUAL", "LEQUAL", "GREATER", "NEQUAL", "GEQUAL", "ALWAYS"]
AOP = ["AND", "OR", "XOR", "XNOR"]
CULL = ["NONE", "FRONT", "BACK", "ALL"]
DIFF_FN = ["NONE", "SIGN", "CLAMP"]
ATTN_FN = ["SPEC", "SPOT", "NONE"]
SRC = ["REG", "VTX"]
WRAP = ["CLAMP", "REPEAT", "MIRROR"]
FILTER = ["NEAR", "LINEAR", "NEAR_MIP_NEAR", "LIN_MIP_NEAR", "NEAR_MIP_LIN", "LIN_MIP_LIN"]
TPL_FMT = {0: "I4", 1: "I8", 2: "IA4", 3: "IA8", 4: "RGB565", 5: "RGB5A3", 6: "RGBA8",
           8: "CI4", 9: "CI8", 10: "CI14X2", 14: "CMPR"}

MODE_NAMES = {
    0: "modulate (GXSetTevOp MODULATE); ends the layer chain",
    1: "decal: lerp(prev, tex, tex.a)  (stage 0: MODULATE)",
    2: "multiply prev*tex (colour), alpha pass",
    3: "multiply prev*tex (colour), alpha pass",
    4: "subtract prev-tex (colour), alpha pass",
    5: "store tex colour in a TEV register, pass prev",
    6: "emboss bump (2 stages, BUMP0 texgen), deferred",
    7: "alpha mask: colour pass, alpha = tex.a * prev.a",
}

# Material callbacks registered by material name (fn_80014E24 / fn_80135F90 / fn_801CA138).
# type 1 replaces the whole TEV/channel setup, type 2 runs after it, type 4 after the draw.
NAME_CALLBACKS = {
    "map_base": ("fn_80141650", 1, "battle-map terrain shader (two UV sets + projected blend mask)"),
    "map_wall": ("fn_80141650", 1, "battle-map terrain shader (same as map_base)"),
    "map_water": ("fn_801420B0", 1, "battle-map water (projected scrolling texture, 2-3 stages)"),
    "map_move": ("fn_80143374", 2, "scrolls layer 0 UV translate (movement-range overlay)"),
    "map_trans": ("fn_80142C44", 2, "see-through occluder: alpha -= K * screen-projected mask"),
    "kbground": ("fn_80142D90", 2, "appends PREV*texture(last layer) projected from above (baked shadow)"),
    "kbwater": ("fn_80143054", 1, "map variant water"),
    "kbref": ("fn_80143180", 2, "map water reflection"),
    "m_haze1": ("fn_800FBC90", 1, "heat haze effect"),
    "m_haze2": ("fn_800FBC90", 1, "heat haze effect"),
    "m_light1": ("fn_800FBC90", 1, "heat haze effect"),
    "eyema": ("fn_800B0340", 2, "unit eye material"),
    "waveB": ("fn_8017D84C", 2, "wave effect"),
    "mat_jp": ("fn_8026A724", 2, "title logo language"),
    "mat_en": ("fn_8026A7C4", 2, "title logo language"),
    "mat_ml": ("fn_8026A864", 2, "title logo language"),
}

# fn_80011838: render state per pass. Mesh list 1/2/3 is drawn with pass 1/2/3
# (fn_8001A218 / fn_800180F0); an object whose alpha byte != 0xFF draws all
# three lists with pass 3.
PASS_STATE = {
    1: dict(blend=(0, 1, 0, 7), zcomploc=1, acomp=(0, 0, 1, 7, 0), zmode=(1, 3, 1)),
    2: dict(blend=(0, 4, 5, 7), zcomploc=0, acomp=(4, 0x80, 1, 0, 0), zmode=(1, 3, 1)),
    3: dict(blend=(1, 4, 5, 7), zcomploc=0, acomp=(4, 0, 1, 0, 0), zmode=(1, 3, 0)),
}
PASS_NAMES = {1: "opaque", 2: "alpha-test (cutout)", 3: "translucent"}

# fn_800186C8: material flag overrides
MAT_BLEND = {0x2000: (1, 4, 1, 0), 0x4000: (3, 0, 0, 0), 0x6000: (1, 2, 0, 0),
             0x8000: (1, 2, 2, 0), 0xA000: (1, 3, 3, 7)}
MAT_BLEND_NAMES = {0x2000: "additive (SRCALPHA, ONE)", 0x4000: "subtract (dst - src)",
                   0x6000: "multiply (DSTCLR, ZERO)", 0x8000: "2x multiply (DSTCLR, SRCCLR)",
                   0xA000: "screen-like (INVDSTCLR, INVSRCCLR)"}
MAT_Z = {0x10: (1, 3, 1), 0x20: (0, 3, 0), 0x30: (1, 6, 0)}

# fn_800140A0 with object flags 0: mesh flags & 0x1800 -> cull
MESH_CULL = {0x0000: 2, 0x0800: 1, 0x1000: 2, 0x1800: 0}

# pools (lbl_80378780 ...): stage i, texmap i, texcoord i, texmtx 30+3i, ind i, reg order
TEXMTX = [30 + 3 * i for i in range(10)]
REG_POOL = [1, 2, 3, 0]          # lbl_80378838: REG0, REG1, REG2, PREV
REG_CIN = {0: 0, 1: 2, 2: 4, 3: 6}  # reg -> colour input C0/C1/C2 (switch in fn_800125A8)
KCOLOR_POOL = [3, 2, 1, 0]       # lbl_80378848

VTX_CLR0 = 0x1000
VTX_CLR_ALPHA = 0x400000         # vertex colour carries alpha (alpha channel material src = VTX)


def _tex_matrix(L):
    """2x4 texture matrix exactly as fn_80012F00 builds it (row-major)."""
    import math

    def mul(a, b):
        return [[sum(a[i][k] * b[k][j] for k in range(3)) + (a[i][3] if j == 3 else 0.0)
                 for j in range(4)] for i in range(3)]

    def T(x, y):
        return [[1, 0, 0, x], [0, 1, 0, y], [0, 0, 1, 0]]

    def S(x, y):
        return [[x, 0, 0, 0], [0, y, 0, 0], [0, 0, 1, 0]]

    def R(rad):
        c, s = math.cos(rad), math.sin(rad)
        return [[c, -s, 0, 0], [s, c, 0, 0], [0, 0, 1, 0]]
    m = T(0, 0)
    if L.rotate != 0.0:
        m = mul(T(0.5, 0.5), mul(R(-L.rotate * 0.017453292), T(-0.5, -0.5)))
    if L.scale_u != 1.0 or L.scale_v != 1.0:
        m = mul(mul(T(0, 1), mul(S(L.scale_u, L.scale_v), T(0, -1))), m)
    if L.trans_u != 0.0 or L.trans_v != 0.0:
        m = mul(T(L.trans_u, -L.trans_v), m)
    return [[round(v, 6) for v in row] for row in m[:2]]


class GXState:
    """Records the GX calls the game would issue for one material/mesh."""

    def __init__(self):
        self.n_stage = self.n_texmap = self.n_texcoord = self.n_texmtx = 0
        self.n_ind = self.n_reg = self.n_kcolor = 0
        self.stages = OrderedDict()     # stage -> dict
        self.texgens = OrderedDict()
        self.texmaps = OrderedDict()    # texmap -> description
        self.texmtx = OrderedDict()
        self.ind = []
        self.regs = OrderedDict()       # reg -> colour description
        self.chan = OrderedDict()
        self.num_chans = 0
        self.amb = {}
        self.mat = {}
        self.notes = []

    # allocators (fn_80011E28 ...)
    def stage(self):
        s = self.n_stage
        self.n_stage += 1
        self.stages[s] = {"stage": s}
        return s

    def texmap(self):
        t = self.n_texmap
        self.n_texmap += 1
        return t

    def texcoord(self):
        t = self.n_texcoord
        self.n_texcoord += 1
        return t

    def mtx(self):
        t = TEXMTX[self.n_texmtx]
        self.n_texmtx += 1
        return t

    def reg(self):
        r = REG_POOL[self.n_reg]
        self.n_reg += 1
        return r

    # wrappers (fn_80021CB4 ...)
    def order(self, s, coord, tmap, chan):
        self.stages.setdefault(s, {"stage": s})["order"] = {
            "texcoord": None if coord == 0xFF else coord,
            "texmap": None if tmap == 0xFF else tmap, "channel": CHANNEL.get(chan, chan)}

    def cin(self, s, a, b, c, d):
        self.stages[s]["color_in"] = [TEV_CIN[a], TEV_CIN[b], TEV_CIN[c], TEV_CIN[d]]

    def ain(self, s, a, b, c, d):
        self.stages[s]["alpha_in"] = [TEV_AIN[a], TEV_AIN[b], TEV_AIN[c], TEV_AIN[d]]

    def cop(self, s, op, bias, scale, clamp, out):
        self.stages[s]["color_op"] = {"op": TEV_OP[op], "bias": TEV_BIAS[bias],
                                      "scale": TEV_SCALE[scale], "clamp": bool(clamp),
                                      "out": TEV_REG[out]}

    def aop(self, s, op, bias, scale, clamp, out):
        self.stages[s]["alpha_op"] = {"op": TEV_OP[op], "bias": TEV_BIAS[bias],
                                      "scale": TEV_SCALE[scale], "clamp": bool(clamp),
                                      "out": TEV_REG[out]}

    def tevop(self, s, mode):
        """GXSetTevOp expanded (stage 0 uses RAS instead of PREV)."""
        c = 10 if s == 0 else 0
        a = 5 if s == 0 else 0
        if mode == 0:      # MODULATE
            self.cin(s, 15, 8, c, 15)
            self.ain(s, 7, 4, a, 7)
        elif mode == 1:    # DECAL
            self.cin(s, c, 8, 9, 15)
            self.ain(s, 7, 7, 7, a)
        elif mode == 2:    # BLEND
            self.cin(s, c, 12, 8, 15)
            self.ain(s, 7, 4, a, 7)
        elif mode == 3:    # REPLACE
            self.cin(s, 15, 15, 15, 8)
            self.ain(s, 7, 7, 7, 4)
        else:              # PASSCLR
            self.cin(s, 15, 15, 15, c)
            self.ain(s, 7, 7, 7, a)
        self.cop(s, 0, 0, 0, 1, 0)
        self.aop(s, 0, 0, 0, 1, 0)
        self.stages[s]["tevop"] = ["MODULATE", "DECAL", "BLEND", "REPLACE", "PASSCLR"][mode]

    def texgen(self, dst, func, src, mtx, normalize=False, postmtx=None):
        self.texgens[dst] = {"texcoord": dst, "type": TG_TYPE.get(func, func),
                             "src": TG_SRC.get(src, src),
                             "mtx": "IDENTITY" if mtx == 60 else ("TEXMTX%d" % ((mtx - 30) // 3)),
                             "normalize": normalize,
                             "postmtx": postmtx}

    def chanctrl(self, chan, enable, amb, mat, mask, diff, attn):
        self.chan[CHANNEL[chan]] = {"enable": bool(enable), "amb_src": SRC[amb],
                                    "mat_src": SRC[mat], "light_mask": mask,
                                    "diff_fn": DIFF_FN[diff], "attn_fn": ATTN_FN[attn]}


def _rgba(v):
    return [(v >> 24) & 0xFF, (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF]


def _load_colors(mat):
    """fn_80012430: colour0 RGB *= 1.25 (clamped), colour1 RGB = 0, colour2 A = 0."""
    c0 = [min(255, int(1.25 * c)) for c in mat.color0[:3]] + [mat.color0[3]]
    c1 = [0, 0, 0, mat.color1[3]]
    c2 = list(mat.color2[:3]) + [0]
    return c0, c1, c2


def _runtime_flags(mat):
    """fn_80012430: material +0x07 runtime bits and the 0x8 (no fog) promotion."""
    f7 = 0
    if mat.layer_count > 1:
        f7 |= 0x20
    for L in mat.layers:
        if L.blend == 5:
            f7 |= 0x40
        if L.blend == 6:
            f7 |= 0x80
        if L.blend == 0:
            f7 &= ~0x20
    flags = mat.flags
    if flags & 0x6000:
        flags |= 0x8
    return flags, f7


def _texcoord_src(L, li, vtx):
    src = L.texcoord if (L.flags & 0x80) else li + 4
    if not vtx & (0x4000 << (src - 4)):
        src = 4
    return src


def _layer_stage(g, model, mesh_vtx, mat, L, li, out_layers):
    """fn_80012F00. Returns False when the chain must stop (mode 0)."""
    s = g.stage()
    coord = g.texcoord()
    tmap = g.texmap()
    src = _texcoord_src(L, li, mesh_vtx)
    if L.flags & 1:
        g.texgen(coord, 1, src, 60)
        mtx = 60
        texmtx = None
    else:
        mtx = g.mtx()
        texmtx = _tex_matrix(L)
        g.texmtx["TEXMTX%d" % ((mtx - 30) // 3)] = texmtx
        g.texgen(coord, 1, src, mtx)
    g.texmaps[tmap] = {"texmap": tmap, "layer": li, "tpl_index": L.texture,
                       "force_repeat": bool(L.flags & 0x20)}
    g.order(s, coord, tmap, 4)
    out_layers.append({"layer": li, "stage": s, "texcoord": coord, "texmap": tmap,
                       "uv_src": TG_SRC[src], "texmtx": texmtx})
    m = L.blend
    st = g.stages[s]
    st["layer"] = li
    st["mode"] = m
    if m == 0:
        g.tevop(s, 0)
        return False
    if m == 1:
        if s == 0:
            g.tevop(0, 0)
        else:
            g.cop(s, 0, 0, 0, 1, 0)
            g.cin(s, 0, 8, 9, 15)
            g.aop(s, 0, 0, 0, 1, 0)
            g.ain(s, 7, 7, 7, 0)
    elif m == 2:
        g.cop(s, 0, 0, 0, 1, 0)
        g.cin(s, 15, 8, 0, 15)
        g.aop(s, 0, 0, 0, 1, 0)
        g.ain(s, 7, 7, 7, 0)
    elif m == 3:
        g.cop(s, 0, 0, 0, 1, 0)
        g.cin(s, 15, 0, 8, 15)
        g.aop(s, 0, 0, 0, 1, 0)
        g.ain(s, 7, 7, 7, 0)
    elif m == 4:
        g.cop(s, 1, 0, 0, 1, 0)
        g.cin(s, 15, 12, 8, 0)
        g.aop(s, 0, 0, 0, 1, 0)
        g.ain(s, 7, 7, 7, 0)
    elif m == 5:
        if g.n_reg == 0:
            r = g.reg()
        else:
            r = REG_POOL[g.n_reg - 1]
        g.cop(s, 0, 0, 0, 1, r)
        g.cin(s, 15, 15, 15, 8)
        g.aop(s, 0, 0, 0, 1, 0)
        g.ain(s, 7, 7, 7, 0)
        g.regs[TEV_REG[r]] = "texture colour of layer %d (mode 5)" % li
    elif m == 6:
        g.cin(s, 15, 8, 12, 0)
        g.cop(s, 0, 0, 0, 0, 0)
        g.ain(s, 7, 7, 7, 0)
        g.aop(s, 0, 0, 0, 0, 0)
        c2 = g.texcoord()
        s2 = g.stage()
        g.texgen(c2, 2, c2 + 11, mtx)
        g.order(s2, c2, tmap, 0xFF)
        g.cin(s2, 15, 8, 12, 0)
        g.cop(s2, 1, 0, 0, 1, 0)
        g.ain(s2, 7, 7, 7, 0)
        g.aop(s2, 0, 0, 0, 0, 0)
        g.stages[s2]["layer"] = li
        g.stages[s2]["mode"] = 6
    elif m == 7:
        if s == 0:
            g.cin(0, 15, 15, 15, 10)
            g.cop(0, 0, 0, 0, 1, 0)
            g.ain(0, 7, 4, 5, 7)
            g.aop(0, 0, 0, 0, 0, 0)
        else:
            g.cin(s, 15, 15, 15, 0)
            g.cop(s, 0, 0, 0, 1, 0)
            g.ain(s, 7, 4, 0, 7)
            g.aop(s, 0, 0, 0, 0, 0)
    return True


def _material_colour(g, mat, flags, mesh_vtx, c0, obj_rgb=(0x80, 0x80, 0x80), obj_a=0xFF):
    """fn_800125A8 with no animation. Returns (drawn, chan_mat_color)."""
    col = list(c0)
    col[3] = (col[3] * obj_a) // 255
    if flags & 0x4000:
        col = [col[3]] * 4
    if col[3] == 0:
        return False, col
    for i in range(3):
        if obj_rgb[i] < 0x80:
            col[i] = (obj_rgb[i] * col[i]) >> 7
    need_c = (mesh_vtx & VTX_CLR0) and sum(col[:3]) != 0x2FD
    need_a = (mesh_vtx & VTX_CLR_ALPHA) and col[3] != 0xFF
    if need_c or need_a:
        s = g.stage()
        r = g.reg()
        g.regs[TEV_REG[r]] = "material colour %s (fn_800125A8)" % bytes(col).hex()
        g.order(s, 0xFF, 0xFF, 4)
        if not mesh_vtx & VTX_CLR0:
            g.cin(s, 15, 15, 15, 0)
        else:
            g.cin(s, 15, 0, REG_CIN[r], 15)
        g.cop(s, 0, 0, 0, 1, 0)
        if not mesh_vtx & VTX_CLR_ALPHA:
            g.ain(s, 7, 7, 7, 0)
        else:
            g.ain(s, 7, 0, {1: 1, 2: 2, 3: 3, 0: 0}[r], 7)
        g.aop(s, 0, 0, 0, 1, 0)
        g.stages[s]["purpose"] = "vertex colour x material colour"
    # obj colour > 0x80 (brighten) and animated colour1/colour2 stages: runtime only
    g.mat["COLOR0A0"] = col
    return True, col


def _lighting(g, flags, mesh_vtx, obj_flags=0):
    """fn_80013CF0 (first batch of a draw; light set from fn_80010BB0)."""
    lit = True
    ambient_mix = False
    sel = flags & 0x1800
    if sel == 0x1000:
        lit = False
    elif sel == 0x1800:
        ambient_mix = True
    elif sel == 0 and obj_flags & 0x10000:
        lit = False
    vtx_mat = bool(mesh_vtx & VTX_CLR0) and not obj_flags & 0x400
    vtx_alpha = bool(mesh_vtx & VTX_CLR0) and bool(mesh_vtx & VTX_CLR_ALPHA)
    if lit:
        g.num_chans = 1
        g.chanctrl(0, 1, 0, int(vtx_mat), 0, 2, 1)
        g.chan["COLOR0"]["light_mask"] = "none (ambient only)" if ambient_mix else "light set diffuse mask"
        g.chanctrl(2, 0, 0, int(vtx_alpha), 0, 0, 2)
        g.amb["COLOR0A0"] = ("(set ambient + directional light colour) / 2" if ambient_mix
                             else "light set ambient")
        if flags & 1 and not obj_flags & 0x400:
            g.num_chans = 2
            g.chanctrl(1, 1, 0, 0, 0, 0, 0)
            g.chan["COLOR1"]["light_mask"] = "light set specular mask"
            g.chanctrl(3, 0, 0, 0, 0, 0, 2)
            g.amb["COLOR1A1"] = [0, 0, 0, 255]
            g.mat["COLOR1A1"] = "not set (game bug: fn_80021958(5) calls GXSetChanAmbColor) -> GX default white"
            s = g.stage()
            g.order(s, 0xFF, 0xFF, 5)
            g.cin(s, 15, 10, 12, 0)
            g.cop(s, 0, 0, 0, 1, 0)
            g.ain(s, 7, 7, 7, 0)
            g.aop(s, 0, 0, 0, 1, 0)
            g.stages[s]["purpose"] = "add specular (COLOR1)"
    else:
        g.num_chans = 1
        g.chanctrl(0, 0, 0, int(vtx_mat), 0, 2, 2)
        g.chanctrl(2, 0, 0, int(vtx_alpha), 0, 0, 2)
        g.amb["COLOR0A0"] = [255, 255, 255, 255]
    return lit


def _post(g, mat, flags, f7, model, mesh_vtx, out_layers):
    """fn_8001393C (object flag 0x800 clear)."""
    if f7 & 0x80:
        for li, L in enumerate(mat.layers):
            if L.blend == 6:
                _layer_stage(g, model, mesh_vtx, mat, L, li, out_layers)
    if f7 & 0x20:
        s = g.stage()
        g.order(s, 0xFF, 0xFF, 4)
        g.cop(s, 0, 0, 0, 1, 0)
        g.cin(s, 15, 10, 0, 15)
        g.aop(s, 0, 0, 0, 1, 0)
        g.ain(s, 7, 5, 0, 7)
        g.stages[s]["purpose"] = "multi-layer: multiply by lit colour"
    if flags & 0x80:
        coord = g.n_texcoord - 1 if g.n_texcoord else 0xFF
        mtx = g.mtx()
        g.texgen(coord, 0, 1, mtx, True, "PTTEXMTX0 = T(0.5,0.5,1)*S(0.5,-0.5,0)")
        g.texmtx["TEXMTX%d" % ((mtx - 30) // 3)] = "inverse-transpose(view*model) (normal -> eye space)"
        g.notes.append("material flag 0x80: last texcoord replaced by sphere env map (normal)")


def _map_terrain(g, mat):
    """fn_80141650 (type-1 callback for map_base / map_wall in battle maps)."""
    t0 = mat.layers[0].texture if mat.layers else 0
    g.mat["COLOR0A0"] = "object colour * 2 (0x80 = 1.0)"
    for uv in (4, 5):
        s, c, m = g.stage(), g.texcoord(), g.texmap()
        r = g.reg()
        g.texmaps[m] = {"texmap": m, "tpl_index": t0, "layer": 0}
        g.order(s, c, m, 4)
        g.texgen(c, 0, uv, 60)
        g.cop(s, 0, 0, 0, 1, r)
        g.cin(s, 15, 8, 10, 15)
        g.aop(s, 0, 0, 0, 1, r)
        g.ain(s, 7, 7, 7, 7)
        g.regs[TEV_REG[r]] = "texture[%d](%s) * RAS" % (t0, TG_SRC[uv])
    mtx = g.mtx()
    c, s, m = g.texcoord(), g.stage(), g.texmap()
    g.texmtx["TEXMTX%d" % ((mtx - 30) // 3)] = "light-ortho projection from above the map (map +0xE4)"
    g.texgen(c, 0, 0, mtx)
    g.texmaps[m] = {"texmap": m, "tpl_index": t0 + 1, "layer": None}
    g.order(s, c, m, 4)
    g.cop(s, 0, 0, 0, 1, 0)
    g.cin(s, 2, 4, 8, 15)
    g.aop(s, 0, 0, 0, 1, 0)
    g.ain(s, 7, 7, 7, 6)
    g.stages[s]["purpose"] = "lerp(UV0 terrain, UV1 terrain, projected mask texture[%d])" % (t0 + 1)
    g.notes.append("optional extra stage when the map highlight pulse is active (map +100 == 1)")


def callback_key(name):
    """Callback lookup compares names like fn_80014E24: character by character until
    either string ends, i.e. a prefix match ("kbground1" -> "kbground"). Callbacks
    are registered per model by the owning module (map / battle bg / title / unit
    eyes), so this global table is only right for models of that kind."""
    for k in NAME_CALLBACKS:
        if name and name.startswith(k):   # (a shorter material name would match too)
            return k
    return None


def _blend_state(flags, lst):
    p = PASS_STATE[lst]
    blend = p["blend"]
    z = p["zmode"]
    if flags & 0xE038:
        b = flags & 0xE000
        if b in MAT_BLEND:
            blend = MAT_BLEND[b]
        zz = flags & 0x30
        if zz in MAT_Z:
            z = MAT_Z[zz]
    ac = p["acomp"]
    return {
        "pass": lst, "pass_name": PASS_NAMES[lst],
        "blend": {"type": BL_TYPE[blend[0]], "src": BL_SRC[blend[1]], "dst": BL_DST[blend[2]]},
        "alpha_compare": {"comp0": COMPARE[ac[0]], "ref0": ac[1], "op": AOP[ac[2]],
                          "comp1": COMPARE[ac[3]], "ref1": ac[4]},
        "zmode": {"test": bool(z[0]), "func": COMPARE[z[1]], "write": bool(z[2])},
        "zcomploc_before_tex": bool(p["zcomploc"]),
        "fog": not flags & 0x8,
        "color_update": True, "alpha_update": False,
    }


def resolve_variant(model, mi, mesh_vtx, mesh_flags, lst, context=None, first_batch=True):
    """Resolve the GX state of material mi drawn by a mesh with these vertex/mesh flags."""
    mat = model.materials[mi]
    flags, f7 = _runtime_flags(mat)
    c0, c1, c2 = _load_colors(mat)
    g = GXState()
    layers_out = []
    key = callback_key(mat.name)
    cb = NAME_CALLBACKS.get(key)
    callback = None
    if cb:
        callback = {"function": cb[0], "type": cb[1], "matched": key, "what": cb[2]}
    drawn = True
    if callback and key in ("map_base", "map_wall") and context in ("zmap", "zbg", None):
        _map_terrain(g, mat)
        lit = _lighting(g, flags, mesh_vtx)
    else:
        if mat.layer_count == 0:
            s = g.stage()
            g.order(s, 0xFF, 0xFF, 4)
            g.tevop(s, 4)
            g.stages[s]["purpose"] = "no layers: lit colour only"
        else:
            for li, L in enumerate(mat.layers):
                if L.blend == 6:
                    continue
                if not _layer_stage(g, model, mesh_vtx, mat, L, li, layers_out):
                    break
        if flags & 0x40:
            s_prev = g.n_stage - 1
            if mat.layer_count:
                g.ind.append({"ind_stage": 0, "ind_texcoord": g.n_texcoord - 1,
                              "ind_texmap": g.n_texmap - 1, "ind_mtx": "IND_MTX0 (fn_8001E51C, scale_exp -4)",
                              "warp_stage": s_prev, "signed_offsets": True, "replace": False})
            s, c, m, mtx = g.n_stage - 1, g.texcoord(), g.texmap(), g.mtx()
            g.texmaps[m] = {"texmap": m, "tpl_index": None,
                            "screen_copy": "EFB 608x448 RGB565 copied now (fn_8001F4D8)"}
            g.texgen(c, 0, 0, mtx)
            g.texmtx["TEXMTX%d" % ((mtx - 30) // 3)] = "projection * modelview (screen-space UV)"
            g.order(s, c, m, 4)
            g.tevop(s, 0)
            g.stages[s]["purpose"] = "refraction: (re)programs the last layer stage to MODULATE screen copy"
        drawn, col = _material_colour(g, mat, flags, mesh_vtx, c0)
        lit = _lighting(g, flags, mesh_vtx) if (first_batch or not mesh_flags & 8) else None
        _post(g, mat, flags, f7, model, mesh_vtx, layers_out)
    state = _blend_state(flags, lst)
    state["cull"] = CULL[MESH_CULL[mesh_flags & 0x1800]]
    v = OrderedDict()
    v["list"] = lst
    v["mesh_flags"] = "0x%04x" % mesh_flags
    v["vtx_flags"] = "0x%x" % mesh_vtx
    v["drawn"] = drawn and not mesh_flags & 0x30 and not flags & 0x4
    why = []
    if not drawn:
        why.append("material alpha 0 (fn_800125A8 skips the batch; effects animate it with .ga type 6)")
    if mesh_flags & 0x30:
        why.append("mesh flag 0x10/0x20 (skipped by fn_80018888)")
    if flags & 0x4:
        why.append("material flag 0x4: only drawn in render queue 5 (fn_8001B040)")
    if why:
        v["hidden_reason"] = why
    v["lit"] = lit
    v["num_tev_stages"] = g.n_stage
    v["num_texgens"] = g.n_texcoord
    v["num_ind_stages"] = len(g.ind)
    v["num_chans"] = g.num_chans
    v["chan_ctrl"] = g.chan
    v["chan_amb_color"] = g.amb
    v["chan_mat_color"] = g.mat
    v["tev_stages"] = list(g.stages.values())
    v["tev_regs"] = g.regs
    v["texgens"] = list(g.texgens.values())
    v["tex_matrices"] = g.texmtx
    v["texmaps"] = list(g.texmaps.values())
    v["indirect"] = g.ind
    v["layers_applied"] = layers_out
    v["state"] = state
    v["callback"] = callback
    if callback and callback["type"] == 1 and key not in ("map_base", "map_wall"):
        g.notes.append("generic TEV/channel state above is REPLACED at runtime by %s" % callback["function"])
    if any("KONST" in (st.get("color_in", []) + st.get("alpha_in", [])) for st in g.stages.values()):
        g.notes.append("KONST uses the reset selection KCSEL/KASEL 0 = 1.0 (fn_800220B0)")
    if g.notes:
        v["notes"] = g.notes
    return v


def decode_material_flags(flags):
    d = OrderedDict()
    if flags & 0x1:
        d["0x1"] = "specular (COLOR1 channel + add stage)"
    if flags & 0x4:
        d["0x4"] = "hidden in normal passes; drawn in render queue 5 (after glow)"
    if flags & 0x8 or flags & 0x6000:
        d["0x8"] = "fog off" + (" (forced by blend 0x6000 bits)" if not flags & 0x8 else "")
    if flags & 0x30:
        z = MAT_Z[flags & 0x30]
        d["0x%02x" % (flags & 0x30)] = "zmode test=%d func=%s write=%d" % (z[0], COMPARE[z[1]], z[2])
    if flags & 0x40:
        d["0x40"] = "refraction (screen copy + indirect warp)"
    if flags & 0x80:
        d["0x80"] = "sphere env map on last texcoord"
    if flags & 0x100:
        d["0x100"] = "planar shadow caster (queue 3, fn_8001A644)"
    if flags & 0x200:
        d["0x200"] = "special sub-draw (fn_8001A4E8)"
    if flags & 0x400:
        d["0x400"] = "glow: also drawn into the bloom buffer (queue 4)"
    sel = flags & 0x1800
    if sel:
        d["0x%04x" % sel] = {0x800: "lit", 0x1000: "unlit", 0x1800: "ambient only (lit, no lights)"}[sel]
    b = flags & 0xE000
    if b:
        d["0x%04x" % b] = MAT_BLEND_NAMES.get(b, "unknown blend %x" % b)
    return d


def resolve_material(model, mi, tpl=None, context=None):
    """Plain dict for one material: static fields + one variant per mesh configuration."""
    mat = model.materials[mi]
    c0, c1, c2 = _load_colors(mat)
    flags, f7 = _runtime_flags(mat)
    d = OrderedDict()
    d["index"] = mi
    d["name"] = mat.name
    d["flags"] = "0x%04x" % mat.flags
    d["flags_decoded"] = decode_material_flags(mat.flags)
    d["runtime_flags"] = "0x%02x" % f7
    d["color0_file"] = list(mat.color0)
    d["color0_runtime"] = c0
    d["color1_runtime"] = c1
    d["color2_runtime"] = c2
    layers = []
    for li, L in enumerate(mat.layers):
        e = OrderedDict()
        e["layer"] = li
        e["mode"] = L.blend
        e["mode_name"] = MODE_NAMES.get(L.blend, "?")
        e["flags"] = "0x%04x" % L.flags
        e["tpl_index"] = L.texture
        e["wrap_file"] = [L.wrap_s, L.wrap_t]
        e["srt"] = {"translate": [L.trans_u, L.trans_v], "scale": [L.scale_u, L.scale_v],
                    "rotate_deg": L.rotate}
        e["texmtx"] = None if L.flags & 1 else _tex_matrix(L)
        if tpl is not None:
            img = tpl.images[L.texture] if L.texture < len(tpl.images) else tpl.images[0]
            e["texture"] = {"width": img.width, "height": img.height,
                            "format": img.format_name,
                            "wrap": [WRAP[img.wrap_s] if img.wrap_s < 3 else img.wrap_s,
                                     WRAP[img.wrap_t] if img.wrap_t < 3 else img.wrap_t],
                            "filter": [FILTER[img.min_filter] if img.min_filter < 6 else img.min_filter,
                                       FILTER[img.mag_filter] if img.mag_filter < 6 else img.mag_filter],
                            "mip_levels": img.mip_count}
        layers.append(e)
    d["layers"] = layers
    configs = Counter()
    for lst_i, lst in enumerate(model.mesh_lists):
        for m in lst:
            if m.material == mi:
                configs[(m.vtx_flags & 0xFFFFFFF, m.flags & 0x183F, lst_i + 1)] += 1
    variants = []
    for (vtx, mf, lst), n in sorted(configs.items()):
        v = resolve_variant(model, mi, vtx, mf, lst, context)
        v["mesh_count"] = n
        variants.append(v)
    d["variants"] = variants
    return d


def resolve_model(model, tpl=None, context=None):
    return [resolve_material(model, i, tpl, context) for i in range(len(model.materials))]


# ---------------------------------------------------------------- formatting
def _lerp_expr(a, b, c):
    Z = ("ZERO",)
    if c in Z:
        return a if a not in Z else None
    if c == "ONE":
        return b if b not in Z else None
    if a in Z and b in Z:
        return None
    if a in Z:
        return "%s*%s" % (b, c)
    if b in Z:
        return "%s*(1-%s)" % (a, c)
    return "lerp(%s,%s,%s)" % (a, b, c)


def stage_expr(ins, op):
    if not ins or not op:
        return "?"
    a, b, c, d = ins
    l = _lerp_expr(a, b, c)
    if op["op"] == "SUB":
        e = "%s - %s" % (d if d != "ZERO" else "0", l or "0")
    else:
        parts = [p for p in (d if d != "ZERO" else None, l) if p]
        e = " + ".join(parts) if parts else "0"
    if op["bias"] != "ZERO":
        e = "(%s %s)" % (e, "+0.5" if op["bias"] == "ADDHALF" else "-0.5")
    if op["scale"] != "1":
        e = "(%s)*%s" % (e, op["scale"])
    if op["clamp"]:
        e = "sat(%s)" % e
    return "%s = %s" % (op["out"], e)


def stage_lines(st):
    o = st.get("order", {})
    head = "stage %d [coord %s map %s chan %s]" % (st["stage"], o.get("texcoord"), o.get("texmap"),
                                                   o.get("channel"))
    tag = []
    if "layer" in st:
        tag.append("layer %d mode %d" % (st["layer"], st["mode"]))
    if "purpose" in st:
        tag.append(st["purpose"])
    if tag:
        head += "  (" + "; ".join(tag) + ")"
    return [head, "      C: " + stage_expr(st.get("color_in"), st.get("color_op")),
            "      A: " + stage_expr(st.get("alpha_in"), st.get("alpha_op"))]


def variant_signature(v):
    """Compact, model-independent key for the survey histogram."""
    stg = []
    for st in v["tev_stages"]:
        stg.append("%s|%s" % (stage_expr(st.get("color_in"), st.get("color_op")),
                              stage_expr(st.get("alpha_in"), st.get("alpha_op"))))
    s = v["state"]
    ch = v["chan_ctrl"].get("COLOR0", {})
    return ("L%d " % v["list"] + " ; ".join(stg) +
            " || chan:%s mat=%s a=%s%s" % ("lit" if ch.get("enable") else "unlit", ch.get("mat_src"),
                                           v["chan_ctrl"].get("ALPHA0", {}).get("mat_src"),
                                           " +spec" if "COLOR1" in v["chan_ctrl"] else "") +
            " || blend:%s(%s,%s) z:%s%s%s fog:%d cull:%s" % (
                s["blend"]["type"], s["blend"]["src"], s["blend"]["dst"],
                s["zmode"]["func"] if s["zmode"]["test"] else "off", "/w" if s["zmode"]["write"] else "",
                " ac>%d" % s["alpha_compare"]["ref0"] if s["alpha_compare"]["comp0"] == "GREATER" else "",
                s["fog"], s["cull"]) + (" CB:" + v["callback"]["function"] if v["callback"] else "") +
            (" +refract" if v["indirect"] or any(t.get("screen_copy") for t in v["texmaps"]) else ""))


def print_material(d, out=sys.stdout):
    p = lambda *a: print(*a, file=out)  # noqa: E731
    p("mat[%d] %s flags=%s runtime=%s c0=%s -> %s" % (
        d["index"], d["name"], d["flags"], d["runtime_flags"], bytes(d["color0_file"]).hex(),
        bytes(d["color0_runtime"]).hex()))
    for k, v in d["flags_decoded"].items():
        p("    flag %s: %s" % (k, v))
    for L in d["layers"]:
        t = L.get("texture")
        p("    layer %d mode %d (%s) flags=%s tex=%d%s uv: T%s S%s R%g%s" % (
            L["layer"], L["mode"], L["mode_name"], L["flags"], L["tpl_index"],
            (" [%dx%d %s wrap %s/%s filt %s/%s mips %d]" % (t["width"], t["height"], t["format"],
                                                            t["wrap"][0], t["wrap"][1], t["filter"][0],
                                                            t["filter"][1], t["mip_levels"])) if t else "",
            L["srt"]["translate"], L["srt"]["scale"], L["srt"]["rotate_deg"],
            "" if L["texmtx"] is None else " mtx=%s" % L["texmtx"]))
    for v in d["variants"]:
        s = v["state"]
        p("  variant: list %d (%s) mesh_flags %s vtx %s x%d meshes%s" % (
            v["list"], s["pass_name"], v["mesh_flags"], v["vtx_flags"], v["mesh_count"],
            "" if v["drawn"] else "  [hidden: %s]" % "; ".join(v.get("hidden_reason", []))))
        if v["callback"]:
            p("    callback %s type %d: %s" % (v["callback"]["function"], v["callback"]["type"],
                                              v["callback"]["what"]))
        p("    stages %d texgens %d ind %d chans %d" % (v["num_tev_stages"], v["num_texgens"],
                                                       v["num_ind_stages"], v["num_chans"]))
        for st in v["tev_stages"]:
            for line in stage_lines(st):
                p("    " + line)
        for r, what in v["tev_regs"].items():
            p("    %s <- %s" % (r, what))
        for tg in v["texgens"]:
            p("    texgen %d: %s %s mtx %s%s" % (tg["texcoord"], tg["type"], tg["src"], tg["mtx"],
                                                 " post %s" % tg["postmtx"] if tg["postmtx"] else ""))
        for k, ch in v["chan_ctrl"].items():
            p("    chan %s: enable=%d amb=%s mat=%s lights=%s diff=%s attn=%s" % (
                k, ch["enable"], ch["amb_src"], ch["mat_src"], ch["light_mask"], ch["diff_fn"],
                ch["attn_fn"]))
        for k, c in v["chan_mat_color"].items():
            p("    matcolor %s = %s" % (k, c if isinstance(c, str) else bytes(c).hex()))
        for k, c in v["chan_amb_color"].items():
            p("    ambcolor %s = %s" % (k, c if isinstance(c, str) else bytes(c).hex()))
        p("    blend %s(%s, %s)  alpha %s %d %s %s %d  z test=%d %s write=%d  zcomploc=%s  cull %s  fog %s" % (
            s["blend"]["type"], s["blend"]["src"], s["blend"]["dst"],
            s["alpha_compare"]["comp0"], s["alpha_compare"]["ref0"], s["alpha_compare"]["op"],
            s["alpha_compare"]["comp1"], s["alpha_compare"]["ref1"],
            s["zmode"]["test"], s["zmode"]["func"], s["zmode"]["write"],
            "before-tex" if s["zcomploc_before_tex"] else "after-tex", s["cull"],
            "on" if s["fog"] else "off"))
        for n in v.get("notes", []):
            p("    note: " + n)


# ------------------------------------------------------------------- loading
def _load(path):
    from lz10 import load
    return load(path)


def context_of(path):
    p = path.replace("\\", "/")
    for c in ("zmap", "zbg", "ymu", "zu", "xwp", "yme", "sky"):
        if "/%s/" % c in "/" + p:
            return c
    return None


def models_in(path, only=None):
    """Yield (name, GModel, TPL or None) for a .gs or a pack (with its TPL)."""
    from pack import Pack
    from tpl import TPL
    raw = _load(path)
    if raw[:4] == b"pack":
        pk = Pack(raw)
        names = pk.names()
        tpls = [n for n in names if n.endswith(".tpl")]
        tpl = None
        if tpls:
            tpl = TPL(pk.get(tpls[0]))
        else:
            unit = os.path.basename(os.path.dirname(os.path.abspath(path)))
            cand = os.path.join(os.path.dirname(path), unit + ".tpl")
            if os.path.exists(cand):
                tpl = TPL.from_file(cand)
        for n in names:
            if n.endswith(".gs") and (only is None or n == only):
                d = pk.get(n)
                if GModel.check(d):
                    yield n, GModel(d), tpl
    elif GModel.check(raw):
        yield os.path.basename(path), GModel(raw), None


def iter_disc(root):
    for dp, dn, fn in os.walk(root):
        dn.sort()
        for f in sorted(fn):
            if f.endswith((".gs", ".cmp", ".pak")):
                p = os.path.join(dp, f)
                try:
                    for n, m, t in models_in(p):
                        yield os.path.relpath(p, root) + (":" + n if not p.endswith(".gs") else ""), m, t
                except Exception as e:  # not a pack, or not a model pack
                    if f.endswith(".gs"):
                        print("ERR %s: %s" % (p, e), file=sys.stderr)


def survey(root, out_json=None):
    sig = Counter()
    sig_meshes = Counter()
    sig_ex = {}
    modes = Counter()
    chains = Counter()
    mflags = Counter()
    lflags = Counter()
    lflag_fmt = Counter()
    per_ctx = defaultdict(Counter)
    nmat = nmod = 0
    for name, model, tpl in iter_disc(root):
        nmod += 1
        ctx = context_of(name)
        for d in resolve_model(model, tpl, ctx):
            nmat += 1
            mflags[d["flags"]] += 1
            chains[tuple(L["mode"] for L in d["layers"])] += 1
            for L in d["layers"]:
                modes[L["mode"]] += 1
                lflags[L["flags"]] += 1
                if "texture" in L:
                    lflag_fmt[(L["flags"], L["texture"]["format"])] += 1
            for v in d["variants"]:
                k = variant_signature(v)
                sig[k] += 1
                sig_meshes[k] += v["mesh_count"]
                per_ctx[ctx][k] += 1
                sig_ex.setdefault(k, "%s mat[%d] %s" % (name, d["index"], d["name"]))
    res = OrderedDict()
    res["models"] = nmod
    res["materials"] = nmat
    res["layer_modes"] = {str(k): v for k, v in sorted(modes.items())}
    res["layer_chains"] = {str(k): v for k, v in chains.most_common()}
    res["material_flags"] = dict(sorted(mflags.items()))
    res["layer_flags"] = dict(sorted(lflags.items()))
    res["layer_flags_x_format"] = {"%s %s" % k: v for k, v in sorted(lflag_fmt.items())}
    res["signatures"] = [{"count": n, "meshes": sig_meshes[k], "example": sig_ex[k], "signature": k}
                         for k, n in sig.most_common()]
    res["per_context"] = {str(c): len(cnt) for c, cnt in per_ctx.items()}
    if out_json:
        with open(out_json, "w") as f:
            json.dump(res, f, indent=1)
    return res


def main(argv):
    if not argv:
        sys.exit(__doc__)
    if argv[0] == "--survey":
        out = argv[argv.index("--json") + 1] if "--json" in argv else None
        res = survey(argv[1], out)
        print("models %d materials %d" % (res["models"], res["materials"]))
        print("layer modes:", res["layer_modes"])
        print("layer chains:", res["layer_chains"])
        print("material flags:", res["material_flags"])
        print("layer flags:", res["layer_flags"])
        print("layer flags x texture format:", res["layer_flags_x_format"])
        print("variant signatures (%d distinct):" % len(res["signatures"]))
        for e in res["signatures"]:
            print("%6d mats %7d meshes  %s\n         e.g. %s" % (e["count"], e["meshes"], e["signature"],
                                                                e["example"]))
        return
    path = argv[0]
    only = argv[argv.index("--gs") + 1] if "--gs" in argv else None
    as_json = "--json" in argv
    tpl_override = None
    if "--tpl" in argv:
        from tpl import TPL
        tpl_override = TPL.from_file(argv[argv.index("--tpl") + 1])
    ctx = context_of(os.path.abspath(path))
    allres = OrderedDict()
    for name, model, tpl in models_in(path, only):
        res = resolve_model(model, tpl_override or tpl, ctx)
        if as_json:
            allres[name] = res
        else:
            print("==== %s (context %s)" % (name, ctx))
            for d in res:
                print_material(d)
    if as_json:
        json.dump(allres, sys.stdout, indent=1)
        print()


if __name__ == "__main__":
    main(sys.argv[1:])
