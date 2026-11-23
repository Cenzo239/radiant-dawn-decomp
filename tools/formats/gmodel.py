"""Readers for FE10's (Intelligent Systems) 3D formats.

  .g   node hierarchy / skeleton ("scene graph")       -> GScene
  .gs  geometry: vertex arrays, materials, display lists -> GModel
  .ga  node animation (keyframed transform channels)  -> GAnim

See docs/formats/graphics.md for the full field tables and the Ghidra functions
each structure was taken from. Everything is big-endian. Python 3.9, stdlib only.

Library sketch for a port:
    scene = GScene.from_bytes(pack.get("skeleton.g"))
    model = GModel.from_bytes(pack.get("body.gs"))
    anim  = GAnim.from_bytes(pack.get("wait_1.ga"))
    pose  = anim.sample(frame)            # {node_index: {channel: value}}
    world = scene.world_matrices(pose)    # list of 3x4 row-major matrices
    for mesh in model.meshes:
        for prim, verts in mesh.primitives:   # GX primitive + decoded indices
            ...

CLI:
    gmodel.py info FILE.g|FILE.gs|FILE.ga        print structure
    gmodel.py info PACK.cmp                      every .g/.gs/.ga inside
    gmodel.py obj PACK.cmp OUTDIR [--gs NAME] [--tpl F.tpl] [--anim A.ga|ARC.pak:A.ga --frame N]
                                                 export meshes (rest pose, or posed by
                                                 an animation) + MTL + PNG textures
    gmodel.py obj FILE.gs OUTDIR [--g F.g] [--tpl F.tpl]
"""
import math
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))


def _cstr(buf, off):
    end = buf.index(b"\0", off)
    return buf[off:end].decode("ascii", "replace")


# =========================================================================== math
def mat_identity():
    return [[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0]]


def mat_mul(a, b):
    """3x4 affine a*b (row-major, column vectors, like PSMTXConcat)."""
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


def mat_trans(x, y, z):
    return [[1.0, 0.0, 0.0, x], [0.0, 1.0, 0.0, y], [0.0, 0.0, 1.0, z]]


def mat_scale(x, y, z):
    return [[x, 0.0, 0.0, 0.0], [0.0, y, 0.0, 0.0], [0.0, 0.0, z, 0.0]]


def mat_rot_axis(axis, deg):
    c, s = math.cos(math.radians(deg)), math.sin(math.radians(deg))
    if axis == "x":
        return [[1.0, 0.0, 0.0, 0.0], [0.0, c, -s, 0.0], [0.0, s, c, 0.0]]
    if axis == "y":
        return [[c, 0.0, s, 0.0], [0.0, 1.0, 0.0, 0.0], [-s, 0.0, c, 0.0]]
    return [[c, -s, 0.0, 0.0], [s, c, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0]]


# rotation order codes (node+0xEC & 0xF), from fn_8001D748: the first axis
# listed is applied first (M = R_last * ... * R_first). 1..3 verified from
# code, 4..6 assumed to follow Maya's xyz,yzx,zxy,xzy,yxz,zyx enum.
ROT_ORDERS = {1: "xyz", 2: "yzx", 3: "zxy", 4: "xzy", 5: "yxz", 6: "zyx",
              7: "xyz", 8: "yzx", 9: "zxy", 10: "xzy", 11: "yxz", 12: "zyx"}


def mat_euler(rx, ry, rz, order=1):
    vals = {"x": rx, "y": ry, "z": rz}
    m = mat_identity()
    for ax in ROT_ORDERS.get(order, "xyz"):
        if vals[ax] != 0.0:
            m = mat_mul(mat_rot_axis(ax, vals[ax]), m)
    return m


def mat_apply(m, v):
    return tuple(m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2] + m[i][3] for i in range(3))


def mat_apply_dir(m, v):
    r = [m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2] for i in range(3)]
    n = math.sqrt(sum(c * c for c in r)) or 1.0
    return tuple(c / n for c in r)


# =========================================================================== .g
# node transform flags (node+0x0C). Channel = index into the 31-float transform
# record built by fn_8000DD0C; offset = location of the rest value in the node.
NODE_FLAGS = {
    0x1: "?visible/has-xform",
    0x2: "HAS_INV_BIND (node+0x10 used for skinning)",
    0x4: "?",
    0x8: "SCALE",
    0x10: "ROTATE",
    0x20: "TRANSLATE",
    0x40: "JOINT_ORIENT",
    0x80: "ROTATE_PIVOT",
    0x100: "SCALE_PIVOT",
    0x200: "ROTATE_PIVOT_TRANSLATE",
    0x400: "SCALE_PIVOT_TRANSLATE",
    0x800: "ROTATE_AXIS",
}

# channel index -> (name, node offset of rest value)
CHANNELS = {}
for _base, _name, _off in ((0, "scale", 0x40), (3, "rotate", 0x4C), (6, "translate", 0x58),
                           (9, "jointOrient", 0x64), (12, "rotatePivot", 0x70),
                           (15, "scalePivot", 0x7C), (18, "rotatePivotTranslate", 0x88),
                           (21, "scalePivotTranslate", 0x94), (24, "rotateAxis", 0xA0)):
    for _k, _ax in enumerate("XYZ"):
        CHANNELS[_base + _k] = (_name + _ax, _off + 4 * _k)
for _k, _ax in enumerate("XYZW"):
    CHANNELS[27 + _k] = ("quat" + _ax, 0xAC + 4 * _k)


class GNode:
    SIZE = 0xF4

    def __init__(self, buf, off, strtab, index):
        self.index = index
        self.parent, self.next, self.child, self.flags = struct.unpack_from(">iiiI", buf, off)
        self.file_flags = self.flags
        if self.flags & 0x40:       # fn_8000E9DC: JOINT_ORIENT implies ROTATE
            self.flags |= 0x10
        m = struct.unpack_from(">12f", buf, off + 0x10)
        self.inv_bind = [list(m[0:4]), list(m[4:8]), list(m[8:12])]
        self.values = list(struct.unpack_from(">31f", buf, off + 0x40))  # channels 0..30
        m2 = struct.unpack_from(">12f", buf, off + 0xBC)
        self.matrix_bc = [list(m2[0:4]), list(m2[4:8]), list(m2[8:12])]
        self.packed, name_off = struct.unpack_from(">II", buf, off + 0xEC)
        self.rot_order = self.packed & 0xF
        self.name = _cstr(buf, strtab + name_off)

    def flag_names(self):
        return [v.split(" ")[0] for k, v in NODE_FLAGS.items() if self.flags & k]

    def local_matrix(self, values=None, extra_flags=0):
        """Rebuild of fn_8000E510: Maya-style
        M = T * Rpt * Rp * JO * R * Ra * Rp^-1 * Spt * Sp * S * Sp^-1."""
        v = values if values is not None else self.values
        f = self.flags | extra_flags
        m = mat_identity()
        if f & 0x10:
            m = mat_euler(v[3], v[4], v[5], self.rot_order)
            if f & 0x40:
                m = mat_mul(mat_euler(v[9], v[10], v[11], self.rot_order), m)
            if f & 0x800:
                m = mat_mul(m, mat_euler(v[24], v[25], v[26], self.rot_order))
            if f & 0x80:
                m = mat_mul(m, mat_trans(-v[12], -v[13], -v[14]))
                m = mat_mul(mat_trans(v[12], v[13], v[14]), m)
                if f & 0x200:
                    m = mat_mul(mat_trans(v[18], v[19], v[20]), m)
        if f & 0x8:
            s = mat_scale(v[0], v[1], v[2])
            if f & 0x100:
                s = mat_mul(s, mat_trans(-v[15], -v[16], -v[17]))
                s = mat_mul(mat_trans(v[15], v[16], v[17]), s)
                if f & 0x400:
                    s = mat_mul(mat_trans(v[21], v[22], v[23]), s)
            m = mat_mul(m, s)
        if f & 0x20:
            m = mat_mul(mat_trans(v[6], v[7], v[8]), m)
        return m


class GScene:
    """.g file: u32 runtime_flags, u32 strtab_off, u32 node_count, u32 nodes_off,
    nodes[node_count] (0xF4 each), string table. Relocated in place by
    fn_8000E9DC (parent/next/child indices -> pointers, name offset -> pointer)."""

    def __init__(self, raw):
        self.raw = raw
        self.runtime_flags, self.strtab, count, nodes_off = struct.unpack_from(">4I", raw, 0)
        if nodes_off != 0x10 or self.strtab > len(raw) or nodes_off + count * GNode.SIZE != self.strtab:
            raise ValueError("not a .g scene file")
        self.nodes = [GNode(raw, nodes_off + i * GNode.SIZE, self.strtab, i) for i in range(count)]

    @classmethod
    def from_bytes(cls, raw):
        return cls(raw)

    @staticmethod
    def check(raw):
        if len(raw) < 16:
            return False
        _, st, cnt, no = struct.unpack_from(">4I", raw, 0)
        return no == 0x10 and no + cnt * GNode.SIZE == st and st < len(raw)

    def find(self, name):
        for n in self.nodes:
            if n.name == name:
                return n
        return None

    def world_matrices(self, pose=None):
        """pose: {node_index: {channel: value}} (from GAnim.sample) or None for rest pose."""
        out = [None] * len(self.nodes)

        def rec(i, parent_m):
            while i >= 0:
                n = self.nodes[i]
                vals = n.values
                extra = 0
                if pose and i in pose:
                    vals = list(n.values)
                    for ch, v in pose[i]["values"].items():
                        vals[ch] = v
                    extra = pose[i]["flags"]
                m = mat_mul(parent_m, n.local_matrix(vals, extra))
                out[i] = m
                if n.child >= 0:
                    rec(n.child, m)
                i = n.next
        for i, n in enumerate(self.nodes):
            if n.parent < 0 and out[i] is None:
                rec(i, mat_identity())
        return out

    def skin_matrices(self, world):
        """Matrix that maps bind-pose model-space vertices to posed space
        (fn_80018F74: world * inv_bind when node flag 0x2)."""
        return [mat_mul(world[i], n.inv_bind) if n.flags & 2 else world[i]
                for i, n in enumerate(self.nodes)]

    def dump(self, out=sys.stdout):
        print("GScene: %d nodes" % len(self.nodes), file=out)

        def rec(i, depth):
            while i >= 0:
                n = self.nodes[i]
                v = n.values
                extra = []
                if n.flags & 0x20:
                    extra.append("T(%.3f %.3f %.3f)" % tuple(v[6:9]))
                if n.flags & 0x10 and any(v[3:6]):
                    extra.append("R(%.1f %.1f %.1f)" % tuple(v[3:6]))
                if n.flags & 0x40 and any(v[9:12]):
                    extra.append("JO(%.1f %.1f %.1f)" % tuple(v[9:12]))
                if n.flags & 0x80 and any(v[12:15]):
                    extra.append("Rp(%.2f %.2f %.2f)" % tuple(v[12:15]))
                print("%s[%d] %s  flags=%x order=%d %s" % ("  " * depth, i, n.name, n.flags,
                                                         n.rot_order, " ".join(extra)), file=out)
                if n.child >= 0:
                    rec(n.child, depth + 1)
                i = n.next
        for i, n in enumerate(self.nodes):
            if n.parent < 0:
                # only start from roots that are not someone's "next"
                if not any(m.next == i for m in self.nodes):
                    rec(i, 0)


# =========================================================================== .gs
GX_PRIMS = {0x80: "quads", 0x88: "quads2", 0x90: "triangles", 0x98: "tristrip",
            0xA0: "trifan", 0xA8: "lines", 0xB0: "linestrip", 0xB8: "points"}

# mesh vertex-descriptor bits (mesh+0x10), decoded by fn_80019AB0
VTX_PNMTXIDX = 0x1
VTX_POS = 0x200
VTX_NRM = 0x400
VTX_NBT = 0x800
VTX_CLR0 = 0x1000
VTX_TEX0 = 0x4000  # TEXn = 0x4000 << n, n = 0..7


class GMaterial:
    SIZE = 0x20

    def __init__(self, isb, off):
        d = isb.data
        name_ptr = struct.unpack_from(">I", d, off)[0]
        self.name = _cstr(d, name_ptr)
        self.flags, self.layer_count, self.flags2 = struct.unpack_from(">HBB", d, off + 4)
        self.color0 = tuple(d[off + 8:off + 12])     # RGBA, RGB scaled at load (fn_80012430)
        self.color1 = tuple(d[off + 12:off + 16])
        self.color2 = tuple(d[off + 16:off + 20])
        layers_ptr, self.unk18, self.unk1c = struct.unpack_from(">III", d, off + 0x14)
        self.layers = [GLayer(d, layers_ptr + 0x1C * i) for i in range(self.layer_count)]


class GLayer:
    """Texture layer (0x1C bytes), consumed by fn_80012F00."""
    SIZE = 0x1C

    def __init__(self, d, off):
        (self.flags, self.texcoord, self.blend, self.texture, self.wrap_s, self.wrap_t,
         self.trans_u, self.trans_v, self.scale_u, self.scale_v, self.rotate) = \
            struct.unpack_from(">HBBHBB5f", d, off)


class GGroup:
    """0x24-byte bounding group referenced by each mesh (header+0x38)."""
    SIZE = 0x24

    def __init__(self, d, off):
        self.offset = off
        self.name = _cstr(d, struct.unpack_from(">I", d, off)[0])
        v = struct.unpack_from(">6f", d, off + 4)
        self.bbox_min, self.bbox_max = v[0:3], v[3:6]
        self.node, self.unk1e, self.unk20 = struct.unpack_from(">hHI", d, off + 0x1C)


class GMesh:
    """0x20-byte draw batch, linked list (header+0x3C/0x40/0x44)."""

    def __init__(self, model, off):
        d = model.isb.data
        self.offset = off
        (grp, self.next_off, self.flags, self.material, self.node, self.slot,
         self.vtx_flags, dl, self.dl_size, pal) = struct.unpack_from(">IIHhhhIIII", d, off)
        self.group = model.group_by_off.get(grp)
        self.dl = d[dl:dl + self.dl_size]
        self.palette = []          # matrix palette: node indices, slot i <-> PNMTXIDX 3*i
        if pal:
            tag, cnt = d[pal], d[pal + 1]
            self.palette_tag = tag  # always 0x10
            self.palette = list(d[pal + 2:pal + 2 + cnt])
        self.model = model
        self._prims = None
        # mesh flag 0x1: POS/NRM come from the CPU-skinned envelope buffer built
        # from header+0x48 (stride 16: f32 pos[3] + s8 nrm[3]), not from header+0x24
        self.uses_envelope = bool(self.flags & 1)

    @property
    def tex_count(self):
        return sum(1 for i in range(8) if self.vtx_flags & (VTX_TEX0 << i))

    def vertex_layout(self):
        """List of (attr, size) in GX order, as set up by fn_80019AB0."""
        f = self.vtx_flags
        lay = []
        if f & VTX_PNMTXIDX:
            lay.append(("pnmtx", 1))
        if f & VTX_POS:
            lay.append(("pos", 2))
        if f & VTX_NRM:
            lay.append(("nrm", 2))
        if f & VTX_NBT:
            lay.append(("nbt", 6))  # GX_NRM_NBT3, indexed -> 3 indices (guess, not seen yet)
        if f & VTX_CLR0:
            lay.append(("clr0", 2))
        for i in range(8):
            if f & (VTX_TEX0 << i):
                lay.append(("tex%d" % i, 2))
        return lay

    @property
    def primitives(self):
        """[(prim_name, [vertex dict, ...])] decoded from the display list."""
        if self._prims is None:
            self._prims = list(decode_display_list(self.dl, self.vertex_layout()))
        return self._prims

    def triangles(self):
        """Yield vertex-dict triples (CCW as in GX)."""
        for prim, vs in self.primitives:
            if prim == "triangles":
                for i in range(0, len(vs) - 2, 3):
                    yield vs[i], vs[i + 1], vs[i + 2]
            elif prim == "tristrip":
                for i in range(len(vs) - 2):
                    if i & 1:
                        yield vs[i + 1], vs[i], vs[i + 2]
                    else:
                        yield vs[i], vs[i + 1], vs[i + 2]
            elif prim == "trifan":
                for i in range(1, len(vs) - 1):
                    yield vs[0], vs[i], vs[i + 1]
            elif prim in ("quads", "quads2"):
                for i in range(0, len(vs) - 3, 4):
                    yield vs[i], vs[i + 1], vs[i + 2]
                    yield vs[i], vs[i + 2], vs[i + 3]


def decode_display_list(dl, layout):
    vsize = sum(s for _, s in layout)
    p = 0
    n = len(dl)
    while p < n:
        op = dl[p]
        if op == 0x00:          # NOP / padding
            p += 1
            continue
        if op & 0xF8 in GX_PRIMS:
            cnt = struct.unpack_from(">H", dl, p + 1)[0]
            p += 3
            verts = []
            for _ in range(cnt):
                v = {}
                q = p
                for name, sz in layout:
                    if sz == 1:
                        v[name] = dl[q]
                    elif sz == 2:
                        v[name] = struct.unpack_from(">H", dl, q)[0]
                    else:
                        v[name] = struct.unpack_from(">3H", dl, q)
                    q += sz
                verts.append(v)
                p += vsize
            yield GX_PRIMS[op & 0xF8], verts
        elif op == 0x08:        # load CP reg
            p += 6
        elif op == 0x10:        # load XF regs
            cnt = (struct.unpack_from(">H", dl, p + 1)[0] & 0xF) + 1
            p += 5 + 4 * cnt
        elif op in (0x20, 0x28, 0x30, 0x38):  # load indexed XF
            p += 5
        elif op == 0x48:
            p += 1
        elif op == 0x61:        # BP
            p += 5
        else:
            raise ValueError("unknown display list opcode 0x%02x at 0x%x" % (op, p))


class _GSContainer:
    """IS relocatable container as used by .gs (see isbin.py). fn_80075874:
    0x08 = pointer count, 0x0C = import count (resolved by name through
    fn_80076D48), 0x10 = export/label count (e.g. "shape" in particle models).
    isbin.ISBin assumes 0x10..0x1F are zero, so .gs files with exports need
    this lenient reader."""

    def __init__(self, raw):
        (self.file_size, self.data_size, self.pointer_count, self.import_count,
         self.export_count) = struct.unpack_from(">5I", raw, 0)
        self.data = raw[0x20:0x20 + self.data_size]
        p = 0x20 + self.data_size
        self.pointers = list(struct.unpack_from(">%dI" % self.pointer_count, raw, p))
        p += 4 * self.pointer_count
        n = self.import_count + self.export_count
        tab = [struct.unpack_from(">II", raw, p + 8 * i) for i in range(n)]
        strtab = p + 8 * n
        self.symbols = [(off, _cstr(raw, strtab + noff)) for off, noff in tab]


class GEnvelope:
    """Envelope (weighted, CPU-skinned) vertex block at .gs header+0x48.

    Decoded from fn_8001CD78 (driver), fn_8001D2FC (blend matrix),
    fn_8001D024 / fn_8001D144 (paired-single transform kernels):

      block+0x00 u32 batch_table_off   (relative to the block)
      block+0x04 u32 data_off          (relative to the block)
      block+0x08 s16 batch_count
      block+0x0A u16 ?                 (unused by the skinning code)
      block+0x0C u8  frac              (GQR6 load scale for the s16 input)
      batch (0x18 bytes):
        +0x00 u16 node[4]   (0xFFFF = unused)
        +0x08 u8  weight[4] (weight = u8 / 256; ignored when bone_count == 1)
        +0x0C u32 offset    (into data, 32-byte aligned)
        +0x10 u16 size      (bytes DMA'd into the locked cache)
        +0x12 u8  skip      (byte offset of the first record inside the DMA)
        +0x13 u8  bone_count (1..4)
        +0x14 u16 count_a   plain vertices: 1 record each
        +0x16 u16 count_b   NBT vertices: 2 records each (count_b is in records)
      record (12 bytes): s16 x,y,z, s16 nx,ny,nz, all * 2^-frac
      NBT vertex = record(pos, N) + record(B, T)

    All vertices of a batch share ONE blended matrix sum(w_i * M[node_i]),
    M = world(node) * inv_bind(node). Output slot of a vertex = byte offset
    of its record in data / 12, i.e. (offset + skip) / 12 + k; the runtime
    buffer (object+0x68, fn_80007FC0) stores slot k at 16*k as
    f32 pos[3] + s8 nrm[3] (*64) [+ for NBT: s8 B[3] at +0xF, s8 T[3] at +0x12,
    32 bytes = 2 slots]. Flag-0x1 meshes index that buffer with their POS and
    NRM indices (stride 16)."""

    def __init__(self, d, off):
        self.offset = off
        bt, dt, n, self.unk0a, self.frac = struct.unpack_from(">IIhHB", d, off)
        sc = 1.0 / (1 << self.frac)
        base = off + dt
        self.batches = []
        self.vertices = {}   # slot -> dict(pos, nrm, [b, t], influences, batch)
        for i in range(n):
            b = off + bt + 0x18 * i
            nodes = struct.unpack_from(">4H", d, b)
            w = d[b + 8:b + 12]
            doff, size, skip, nb, ca, cb = struct.unpack_from(">IHBBHH", d, b + 12)
            if nb == 1:
                infl = [(nodes[0], 1.0)]
            else:
                infl = [(nodes[k], w[k] / 256.0) for k in range(nb)]
            first = (doff + skip) // 12
            batch = {"index": i, "influences": infl, "offset": doff, "size": size, "skip": skip,
                     "count_a": ca, "count_b": cb, "first_slot": first}
            self.batches.append(batch)
            rec = base + doff + skip
            for k in range(ca):
                v = struct.unpack_from(">6h", d, rec + 12 * k)
                self.vertices[first + k] = {"pos": tuple(c * sc for c in v[:3]),
                                            "nrm": tuple(c * sc for c in v[3:]),
                                            "influences": infl, "batch": i}
            # fn_8001D144 is called with the same src/dst as fn_8001D024, so a
            # batch has either count_a or count_b vertices (never both on disc).
            for k in range(cb // 2):
                v = struct.unpack_from(">12h", d, rec + 24 * k)
                self.vertices[first + 2 * k] = {"pos": tuple(c * sc for c in v[0:3]),
                                                "nrm": tuple(c * sc for c in v[3:6]),
                                                "binormal": tuple(c * sc for c in v[6:9]),
                                                "tangent": tuple(c * sc for c in v[9:12]),
                                                "influences": infl, "batch": i}

    @property
    def max_bones(self):
        return max((len(b["influences"]) for b in self.batches), default=0)

    def bone_nodes(self):
        return sorted({n for b in self.batches for n, _ in b["influences"]})

    def blend_matrix(self, influences, bone_mats):
        """sum(w_i * M[node_i]) exactly like fn_8001D2FC (no renormalisation)."""
        if len(influences) == 1:
            return bone_mats[influences[0][0]]
        out = [[0.0] * 4 for _ in range(3)]
        for node, w in influences:
            m = bone_mats[node]
            for r in range(3):
                for c in range(4):
                    out[r][c] += w * m[r][c]
        return out

    def skinned(self, scene, pose=None):
        """Return {slot: (pos, nrm)} posed in model space. pose=None returns the
        stored bind-pose data: the rest transforms in the .g are NOT always the
        bind pose (33 of 298 envelope models have attachment/prop bones such as
        BW001, _r_hand_, Shield whose rest pose differs from inv_bind)."""
        if pose is None:
            return {k: (v["pos"], v["nrm"]) for k, v in self.vertices.items()}
        world = scene.world_matrices(pose)
        mats = {n: mat_mul(world[n], scene.nodes[n].inv_bind) for n in self.bone_nodes()}
        out = {}
        cache = {}
        for slot, v in self.vertices.items():
            m = cache.get(v["batch"])
            if m is None:
                m = cache[v["batch"]] = self.blend_matrix(v["influences"], mats)
            out[slot] = (mat_apply(m, v["pos"]), mat_apply_dir(m, v["nrm"]))
        return out

    def summary(self):
        from collections import Counter
        nb = Counter(len(b["influences"]) for b in self.batches)
        return ("envelope @0x%x: %d batches, %d vertices (%d NBT batches), frac %d, bones/vertex %s, "
                "%d distinct bone nodes" % (
                    self.offset, len(self.batches), len(self.vertices),
                    sum(1 for b in self.batches if b["count_b"]), self.frac,
                    dict(sorted(nb.items())), len(self.bone_nodes())))


def envelope_vertices(model):
    """Library helper for GPU skinning: list of
    {"slot", "position", "normal", "influences": [(node, weight), ...]} in bind
    pose (model space). Weights sum to 1.0. Meshes with flag 0x1 index these
    slots with both their POS and NRM display-list indices."""
    if not model.envelope:
        return []
    return [{"slot": s, "position": v["pos"], "normal": v["nrm"], "influences": list(v["influences"])}
            for s, v in sorted(model.envelope.vertices.items())]


class GModel:
    """.gs file = IS relocatable container (see isbin.py) whose data starts with
    the model header (0x60 bytes); loaded by fn_80017FD0 / fn_80075FB4."""

    def __init__(self, raw):
        self.raw = raw
        self.isb = isb = _GSContainer(raw)
        d = isb.data
        self.name = _cstr(d, struct.unpack_from(">I", d, 0)[0])
        self.version = struct.unpack_from(">I", d, 4)[0]            # 0x20040723
        self.unk08 = struct.unpack_from(">I", d, 8)[0]
        v = struct.unpack_from(">6f", d, 0x0C)
        self.bbox_min, self.bbox_max = v[0:3], v[3:6]
        (self.pos_off, self.nrm_off, self.tex_off, self.clr_off, self.mat_off, self.grp_off,
         self.list1_off, self.list2_off, self.list3_off, self.skin_off) = \
            struct.unpack_from(">10I", d, 0x24)
        (self.pos_count, self.nrm_count, self.tex_count, self.clr_count, self.mat_count,
         self.grp_count, self.mesh_count, self.unk5a) = struct.unpack_from(">8H", d, 0x4C)
        self.pos_frac, self.nrm_frac, self.tex_frac, self.unk5f = d[0x5C:0x60]
        self.unk60 = struct.unpack_from(">I", d, 0x60)[0]

        ps = 1.0 / (1 << self.pos_frac)
        self.positions = [tuple(c * ps for c in struct.unpack_from(">3h", d, self.pos_off + 6 * i))
                          for i in range(self.pos_count)] if self.pos_off else []
        ns = 1.0 / (1 << self.nrm_frac)
        self.normals = [tuple(c * ns for c in struct.unpack_from(">3b", d, self.nrm_off + 3 * i))
                        for i in range(self.nrm_count)] if self.nrm_off else []
        ts = 1.0 / (1 << self.tex_frac)
        self.texcoords = [tuple(c * ts for c in struct.unpack_from(">2h", d, self.tex_off + 4 * i))
                          for i in range(self.tex_count)] if self.tex_off else []
        self.colors = [tuple(d[self.clr_off + 4 * i:self.clr_off + 4 * i + 4])
                       for i in range(self.clr_count)] if self.clr_off else []
        self.materials = [GMaterial(isb, self.mat_off + GMaterial.SIZE * i)
                          for i in range(self.mat_count)]
        self.groups = [GGroup(d, self.grp_off + GGroup.SIZE * i) for i in range(self.grp_count)] \
            if self.grp_off not in (0, 0xFFFFFFFF) else []
        self.group_by_off = {g.offset: g for g in self.groups}
        self.mesh_lists = []
        for head in (self.list1_off, self.list2_off, self.list3_off):
            lst = []
            o = head
            while o:
                m = GMesh(self, o)
                lst.append(m)
                o = m.next_off
            self.mesh_lists.append(lst)
        self.meshes = [m for lst in self.mesh_lists for m in lst]
        self.envelope = GEnvelope(d, self.skin_off) if self.skin_off else None

    @classmethod
    def from_bytes(cls, raw):
        return cls(raw)

    @staticmethod
    def check(raw):
        return len(raw) >= 0x84 and raw[0x24:0x28] == b"\x20\x04\x07\x23"

    def dump(self, out=sys.stdout):
        p = lambda *a: print(*a, file=out)  # noqa: E731
        p("GModel '%s' version %08x unk08 %08x" % (self.name, self.version, self.unk08))
        p("  bbox (%.2f %.2f %.2f)-(%.2f %.2f %.2f)" % (self.bbox_min + self.bbox_max))
        p("  pos %d (frac %d)  nrm %d (frac %d)  uv %d (frac %d)  clr %d  mats %d  groups %d  meshes %d"
          % (self.pos_count, self.pos_frac, self.nrm_count, self.nrm_frac, self.tex_count,
             self.tex_frac, self.clr_count, self.mat_count, self.grp_count, self.mesh_count))
        if self.envelope:
            p("  " + self.envelope.summary())
        for i, m in enumerate(self.materials):
            p("  mat[%d] %-16s flags=%04x layers=%d c0=%s c1=%s c2=%s" % (
                i, m.name, m.flags, m.layer_count, bytes(m.color0).hex(), bytes(m.color1).hex(),
                bytes(m.color2).hex()))
            for L in m.layers:
                p("      layer tex=%d flags=%04x blend=%d wrap=%d/%d uvT=(%g,%g) uvS=(%g,%g) rot=%g"
                  % (L.texture, L.flags, L.blend, L.wrap_s, L.wrap_t, L.trans_u, L.trans_v,
                     L.scale_u, L.scale_v, L.rotate))
        for li, lst in enumerate(self.mesh_lists):
            for m in lst:
                ntri = sum(1 for _ in m.triangles())
                p("  list%d mesh@%x flags=%04x mat=%d node=%d vtx=%x dl=%d bytes tris=%d%s%s" % (
                    li + 1, m.offset, m.flags, m.material, m.node, m.vtx_flags, m.dl_size, ntri,
                    " ENVELOPE" if m.uses_envelope else "",
                    (" palette=%s" % m.palette) if m.palette else ""))


# =========================================================================== .ga
class GAnim:
    """.ga = plain (non-IS) self-relative file, relocated by fn_8000BC20,
    evaluated by fn_8000DD0C.

    header (0x30):
      0x00 u32 event_list_off (0 = none)     0x04 u32 off (relocated, unknown use)
      0x08 u8  has_events                      0x0C u32 flags (0x10/0x20 = key encoding)
      0x10 u32 ?  (1)                          0x14 s32 start_frame?  0x18 s32 end_frame
      0x1C u32 track_count                     0x20 u32 tracks_off  (16 B each)
      0x24 u32 curves_off                      0x28 u32 frame_lut_off (float mode)
      0x2C u32 keys_off
    """

    def __init__(self, raw):
        self.raw = raw
        (self.event_off, self.unk04, self.has_events, self.flags, self.unk10, self.start_frame,
         self.end_frame, ntracks, self.tracks_off, self.curves_off, self.lut_off,
         self.keys_off) = struct.unpack_from(">IIB3xIIiiIIIII", raw, 0)
        if self.tracks_off != 0x30:
            raise ValueError("not a .ga animation")
        self.mode = "s16" if self.flags & 0x10 else ("packed32" if self.flags & 0x20 else "float")
        self.tracks = []
        for i in range(ntracks):
            node, extra_flags, first, count = struct.unpack_from(">IIII", raw, self.tracks_off + 16 * i)
            curves = [self._curve(first + k) for k in range(count)]
            self.tracks.append({"node": node, "flags": extra_flags, "curves": curves})
        self.events = []
        o = self.event_off if self.has_events else 0
        while o:
            typ, ptr, nxt = struct.unpack_from(">III", raw, o)
            self.events.append((typ, ptr))
            o = nxt

    def _curve(self, ci):
        r = self.raw
        if self.mode == "float":
            ch, nkeys, lut, koff, const = struct.unpack_from(">iiiif", r, self.curves_off + 0x14 * ci)
            keys = [struct.unpack_from(">ifff", r, self.keys_off + 16 * (koff + k)) for k in range(nkeys)]
            return {"channel": ch, "const": const, "lut": lut,
                    "keys": [(f, v, a, b) for f, v, a, b in keys]}
        ch, shift, unk3, unk4, nkeys, koff = struct.unpack_from(">HBBHHI", r, self.curves_off + 12 * ci)
        keys = []
        for k in range(nkeys):
            if self.mode == "s16":
                f, v = struct.unpack_from(">hh", r, self.keys_off + 4 * (koff + k))
                keys.append((f, v / float(1 << (shift & 0x3F))))
            else:
                w = struct.unpack_from(">I", r, self.keys_off + 4 * (koff + k))[0]
                v = (w & 0x7FFFF) - (w & 0x80000)
                keys.append((w >> 20, v / float(1 << shift)))
        return {"channel": ch, "shift": shift, "unk3": unk3, "unk4": unk4, "keys": keys}

    @classmethod
    def from_bytes(cls, raw):
        return cls(raw)

    @staticmethod
    def check(raw):
        return len(raw) >= 0x30 and struct.unpack_from(">I", raw, 0x20)[0] == 0x30

    def sample(self, frame):
        """Evaluate every curve (linear interpolation; float-mode hermite for
        channels 27..30 is not reproduced). Returns {node: {"flags", "values"}}."""
        pose = {}
        for t in self.tracks:
            vals = {}
            for c in t["curves"]:
                keys = c["keys"]
                if not keys:
                    vals[c["channel"]] = c.get("const", 0.0)
                    continue
                if frame <= keys[0][0]:
                    v = keys[0][1]
                elif frame >= keys[-1][0]:
                    v = keys[-1][1]
                else:
                    for a, b in zip(keys, keys[1:]):
                        if a[0] <= frame <= b[0]:
                            t_ = (frame - a[0]) / float(b[0] - a[0]) if b[0] != a[0] else 0.0
                            v = a[1] + (b[1] - a[1]) * t_
                            break
                vals[c["channel"]] = v
            pose[t["node"]] = {"flags": t["flags"], "values": vals}
        return pose

    def dump(self, out=sys.stdout, scene=None, max_keys=6):
        p = lambda *a: print(*a, file=out)  # noqa: E731
        p("GAnim mode=%s flags=%x frames %d..%d tracks=%d events=%d" % (
            self.mode, self.flags, self.start_frame, self.end_frame, len(self.tracks), len(self.events)))
        for t in self.tracks:
            nm = scene.nodes[t["node"]].name if scene and t["node"] < len(scene.nodes) else ""
            p("  node %d %s (+flags %x)" % (t["node"], nm, t["flags"]))
            for c in t["curves"]:
                ks = " ".join("%d:%.3f" % (k[0], k[1]) for k in c["keys"][:max_keys])
                p("     %-22s %3d keys  %s%s" % (CHANNELS.get(c["channel"], ("ch%d" % c["channel"],))[0],
                                              len(c["keys"]), ks, " ..." if len(c["keys"]) > max_keys else ""))


# =========================================================================== OBJ
def export_obj(model, outdir, stem, scene=None, tpl=None, pose=None):
    """Write <stem>.obj/.mtl (+ <stem>_tex<i>.png when a TPL is given).

    Every vertex is transformed by the skin matrix of its node, exactly like
    the game (fn_80018F74 / fn_80019504): world(node) * inv_bind(node) for
    joints (node flag 0x2), world(node) otherwise. Skinned meshes pick the
    node per vertex from their matrix palette (PNMTXIDX / 3). pose = result of
    GAnim.sample(frame), None = rest pose."""
    os.makedirs(outdir, exist_ok=True)
    texfiles = {}
    if tpl is not None:
        from tpl import write_png
        for i, img in enumerate(tpl.images):
            w, h, rgba = img.decode()
            fn = "%s_tex%d.png" % (stem, i)
            write_png(os.path.join(outdir, fn), w, h, rgba)
            texfiles[i] = fn
    skin = scene.skin_matrices(scene.world_matrices(pose)) if scene else None
    envv = None
    if model.envelope is not None:
        envv = model.envelope.skinned(scene, pose) if scene is not None else \
            model.envelope.skinned(None, None)
    with open(os.path.join(outdir, stem + ".mtl"), "w") as f:
        for i, m in enumerate(model.materials):
            f.write("newmtl m%d_%s\nKd %.3f %.3f %.3f\n" % (i, m.name, m.color0[0] / 255.0,
                                                           m.color0[1] / 255.0, m.color0[2] / 255.0))
            if m.layers and m.layers[0].texture in texfiles:
                f.write("map_Kd %s\n" % texfiles[m.layers[0].texture])
            f.write("\n")
    vlines, tlines, nlines, flines = [], [], [], []
    for mi, mesh in enumerate(model.meshes):
        if mesh.uses_envelope and envv is None:
            flines.append("# mesh%d skipped: envelope mesh without envelope block\n" % mi)
            continue
        flines.append("g mesh%d_node%d\nusemtl m%d_%s\n" % (
            mi, mesh.node, mesh.material,
            model.materials[mesh.material].name if 0 <= mesh.material < len(model.materials) else ""))

        def xform(v):
            if skin is None:
                return None
            if mesh.palette:
                return skin[mesh.palette[v.get("pnmtx", 0) // 3]]
            if 0 <= mesh.node < len(skin):
                return skin[mesh.node]
            return None
        for tri in mesh.triangles():
            idx = []
            for v in tri:
                m = xform(v)
                if mesh.uses_envelope:
                    # already skinned to model space by the envelope; the game
                    # then draws it with the mesh node's matrix (rigid path)
                    pos, envn = envv[v["pos"]]
                else:
                    pos = model.positions[v["pos"]]
                if m:
                    pos = mat_apply(m, pos)
                vlines.append("v %.5f %.5f %.5f\n" % pos)
                vi = len(vlines)
                ti = ni = ""
                if "tex0" in v and model.texcoords:
                    u, t = model.texcoords[v["tex0"]]
                    tlines.append("vt %.5f %.5f\n" % (u, 1.0 - t))
                    ti = len(tlines)
                if "nrm" in v and (model.normals or mesh.uses_envelope):
                    nv = envv[v["nrm"]][1] if mesh.uses_envelope else model.normals[v["nrm"]]
                    if m:
                        nv = mat_apply_dir(m, nv)
                    nlines.append("vn %.4f %.4f %.4f\n" % nv)
                    ni = len(nlines)
                idx.append("%d/%s/%s" % (vi, ti, ni))
            flines.append("f %s\n" % " ".join(idx))
    with open(os.path.join(outdir, stem + ".obj"), "w") as f:
        f.write("mtllib %s.mtl\n" % stem)
        f.writelines(vlines)
        f.writelines(tlines)
        f.writelines(nlines)
        f.writelines(flines)
    return os.path.join(outdir, stem + ".obj")


# =========================================================================== CLI
def _load_any(path):
    from lz10 import load
    return load(path)


def _info_blob(name, raw, scene=None):
    if name.endswith(".gs") and GModel.check(raw):
        GModel(raw).dump()
    elif name.endswith(".g") and GScene.check(raw):
        GScene(raw).dump()
    elif name.endswith(".ga") and GAnim.check(raw):
        GAnim(raw).dump(scene=scene)
    else:
        print("  (unrecognised)")


def main(argv):
    if len(argv) < 2:
        sys.exit(__doc__)
    cmd, path = argv[0], argv[1]
    raw = _load_any(path)
    if cmd == "info":
        if raw[:4] == b"pack":
            from pack import Pack
            pk = Pack(raw)
            scene = None
            for n, d in pk.items():
                if n.endswith(".g") and GScene.check(d):
                    scene = GScene(d)
                    break
            for n, d in pk.items():
                if n.endswith((".g", ".gs", ".ga")):
                    print("==== %s" % n)
                    _info_blob(n, d, scene)
        else:
            scene = None
            if path.endswith(".ga") and "--g" in argv:
                scene = GScene(_load_any(argv[argv.index("--g") + 1]))
            _info_blob(path, raw, scene)
    elif cmd == "obj":
        from tpl import TPL
        outdir = argv[2]
        if raw[:4] == b"pack":
            from pack import Pack
            pk = Pack(raw)
            names = pk.names()
            tpls = [n for n in names if n.endswith(".tpl")]
            tpl = TPL(pk.get(tpls[0])) if tpls else None
            if tpl is None:   # battle units keep <unit>.tpl next to pack.cmp
                unit = os.path.basename(os.path.dirname(os.path.abspath(path)))
                cand = os.path.join(os.path.dirname(path), unit + ".tpl")
                if not os.path.exists(cand):   # zu/<x>_sky/ keeps <x>.tpl
                    loose = sorted(f for f in os.listdir(os.path.dirname(os.path.abspath(path)))
                                   if f.endswith(".tpl"))
                    cand = os.path.join(os.path.dirname(path), loose[0]) if loose else cand
                if os.path.exists(cand):
                    tpl = TPL.from_file(cand)
            if "--tpl" in argv:
                tpl = TPL.from_file(argv[argv.index("--tpl") + 1])
            only = argv[argv.index("--gs") + 1] if "--gs" in argv else None
            for n in names:
                if not n.endswith(".gs") or (only and n != only):
                    continue
                stem = os.path.splitext(os.path.basename(n))[0]
                gname = stem + ".g" if stem + ".g" in names else ("skeleton.g" if "skeleton.g" in names else None)
                scene = GScene(pk.get(gname)) if gname else None
                pose = None
                if "--anim" in argv:
                    an = argv[argv.index("--anim") + 1]
                    if an in names:
                        adata = pk.get(an)
                    elif ":" in an:   # ARCHIVE.pak:NAME.ga (zu/<x>/cr.pak, no.pak)
                        arc, member = an.rsplit(":", 1)
                        adata = Pack(_load_any(arc)).get(member)
                    else:
                        adata = _load_any(an)
                    frame = float(argv[argv.index("--frame") + 1]) if "--frame" in argv else 0.0
                    pose = GAnim(adata).sample(frame)
                p = export_obj(GModel(pk.get(n)), outdir, stem, scene, tpl, pose)
                print(p)
        else:
            scene = GScene(_load_any(argv[argv.index("--g") + 1])) if "--g" in argv else None
            tpl = TPL.from_file(argv[argv.index("--tpl") + 1]) if "--tpl" in argv else None
            stem = os.path.splitext(os.path.basename(path))[0]
            print(export_obj(GModel(raw), outdir, stem, scene, tpl))
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main(sys.argv[1:])
