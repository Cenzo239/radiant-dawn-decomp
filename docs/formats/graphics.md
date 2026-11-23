# FE10 graphics assets: textures (.tpl), models (.g / .gs), animations (.ga)

Fire Emblem: Radiant Dawn (RFEE01 Rev 1). All integers and floats are big-endian.
Tools: `tools/formats/tpl.py` (textures) and `tools/formats/gmodel.py` (models and animations).
Both use only the Python 3.9 standard library and can be imported as libraries.

Confidence tags: **[V]** verified (read in the code and/or checked against data by rendering);
**[D]** taken from the decompiled code but not checked against data; **[G]** guessed.

## 1. Where the files are

| Location | Contents |
|---|---|
| `ymu/<unit>/pack.cmp` | Battle unit pack: `body.gs`, `skeleton.g`, `wait_N.ga`, `move_N.ga`, `twait_N.ga` |
| `ymu/<unit>/*.ga` | The remaining battle motions (`atk_1.ga`, `damage_1.ga`, ...); `_1`/`_2` are two variants |
| `ymu/<unit>/<unit>*.tpl` | Unit textures; colour variants are separate TPLs (`_b`, `_r`, `_c`, ...) |
| `zmap/bmapXXXX/map.cmp` | Map pack: `bmapXXXX.g/.gs` (terrain), props as `<name>.g/.gs[/.ga]`, `texpack.tpl` shared by all, `map.bin` |
| `xwp/<weapon>/<weapon>.cmp` | Weapon pack: `<w>.g`, `<w>.gs`, `<w>.tpl` |
| `Face/*.cms` | LZ10-compressed TPL: portrait plus eye and mouth sprites |
| `etc/`, `window/`, ... | Plain TPLs for UI |
| `xcam/*.ga` | Camera animations, in the same .ga format |

Loader format strings in the DOL: `%s%s/pack.cmp`, `%s%s/body.gs`, `%s%s/skeleton.g`,
`%s%s/%s_%d.ga`, `%s%s/%s.tpl` (fn_800F0B08 .. fn_800F0C68, battle units), and `%s%s.gs`/`.g`/`.ga`/`.tpl`
(fn_800E1FE0 and fn_800E2D8C, map objects). Generic loaders, each with a refcounted resource cache:

| Ext | Loader | Post-load fixup |
|---|---|---|
| .gs | fn_80017FD0 -> fn_80075FB4 | fn_80075874 (IS relocation), fn_80012430 per material, fn_800150F4 |
| .g  | fn_8000EBCC / fn_8000EB68 | fn_8000E9DC |
| .ga | fn_8000BDB0 | fn_8000BC20 |
| .tpl| fn_8001D3EC -> fn_800068EC | TPLBind-style (texture objects built in fn_80006A64 / fn_80006B84) |

Object slots on the draw object: `+0x40` .g, `+0x44` .ga, `+0x48` .gs, `+0x4C` .tpl (fn_80009150..fn_800092D4).

---

## 2. TPL (textures) [V]

Standard Revolution SDK TPL (magic `00 20 AF 30`). `tpl.py` decodes every format FE10 uses into RGBA PNG.

```
0x00 u32 magic 0x0020AF30
0x04 u32 image_count
0x08 u32 image_table_off (=0x0C)
table[image_count]: u32 image_header_off, u32 palette_header_off (0 = none)
image header (0x24): u16 height, u16 width, u32 format, u32 data_off,
                     u32 wrap_s, u32 wrap_t, u32 min_filter, u32 mag_filter,
                     f32 lod_bias, u8 edge_lod, u8 min_lod, u8 max_lod, u8 unpacked
palette header (0x0C): u16 count, u8 unpacked, u8 pad, u32 format (0 IA8, 1 RGB565, 2 RGB5A3), u32 data_off
```

Mipmaps follow the base level directly; `max_lod + 1` levels (`TPLImage.decode(level)`).

**Formats on the disc** (survey of 3,339 TPLs, loose files plus the contents of every pack and .cms):

| Format | Images |
|---|---|
| CI8 (palette RGB5A3: 8,797; RGB565: 20) | 8,817 |
| CMPR (S3TC/DXT1 in 8x8 blocks of four 4x4 sub-blocks) | 6,915 |
| RGB5A3 | 1,951 |
| RGB565 | 970 |
| I8 | 799 |
| I4 | 430 |
| IA4 | 284 |
| IA8 | 282 |
| RGBA8 | 256 |

CI4 and CI14X2 never occur; the decoder handles CI4 anyway. CI8 is used mostly by portraits and UI,
CMPR by the 3D models (unit, map and weapon textures).

Port note: CMPR maps to BC1 (DXT1) with only a block reorder, so it can be uploaded to Metal
on macOS as BC1. iOS has no BC support (A-series GPUs), so convert to ASTC or RGBA8 there.

---

## 3. `.g`: node hierarchy / skeleton

Plain self-relative file (not the IS container). One per model: `skeleton.g` for units,
`<name>.g` next to every map or weapon `.gs`.

```
0x00 u32 runtime_flags   0 in the file; bits 0x20000000/0x40000000/0x80000000 set by fn_8000E9DC
0x04 u32 strtab_off      string table (names); first string is usually "[unknown]"
0x08 u32 node_count
0x0C u32 nodes_off       always 0x10
0x10 node[node_count]    0xF4 bytes each
...  strings
```

**Node (0xF4 bytes)**: fn_8000E9DC (relocation), fn_8000DD0C / fn_8000E510 (transform):

| Off | Type | Meaning | Conf |
|---|---|---|---|
| 0x00 | s32 | parent node index (-1 none) | V |
| 0x04 | s32 | next sibling index (-1) | V |
| 0x08 | s32 | first child index (-1) | V |
| 0x0C | u32 | flags, see below | V |
| 0x10 | f32[3][4] | inverse bind matrix (model to node), used when flag 0x2 | V (world * this = I for every joint) |
| 0x40 | f32[3] | scale (channels 0-2) | V |
| 0x4C | f32[3] | rotate, degrees (ch 3-5) | V |
| 0x58 | f32[3] | translate (ch 6-8) | V |
| 0x64 | f32[3] | joint orient, degrees (ch 9-11) | V |
| 0x70 | f32[3] | rotate pivot (ch 12-14) | V |
| 0x7C | f32[3] | scale pivot (ch 15-17) | D |
| 0x88 | f32[3] | rotate pivot translate (ch 18-20) | D |
| 0x94 | f32[3] | scale pivot translate (ch 21-23) | D |
| 0xA0 | f32[3] | rotate axis, degrees (ch 24-26) | D |
| 0xAC | f32[4] | quaternion x,y,z,w (ch 27-30), used if the anim's flag 0x2 | D |
| 0xBC | f32[3][4] | rest local matrix, precomputed (identical to the rebuilt TRS) | V |
| 0xEC | u32 | `index << 20` (written at load) and rotation order in the low 4 bits | V |
| 0xF0 | u32 | name offset into the string table (pointer after load) | V |

Node flags (0x0C): `0x8` scale, `0x10` rotate, `0x20` translate, `0x40` joint orient,
`0x80` rotate pivot, `0x100` scale pivot, `0x200` rotate pivot translate, `0x400` scale pivot translate,
`0x800` rotate axis, `0x2` has inverse bind matrix (skinning joint). Joints in unit skeletons are
`0x67`, plain Maya transforms `0x180`. The loader forces `0x10` when `0x40` is set. `0x1` and `0x4`
are unknown. Runtime-only: `0x80000000` (fn_8001E548 name match), `0x4000000`, and the
`0x1F0000` billboard/special-matrix modes handled in fn_80018F74 (0x10000, 0x20000, 0x40000,
0x80000, 0xC0000, 0x100000). These come from the file too (`0x10000`/`0x20000` set header
bits 0x40000000/0x80000000) [D].

**Local matrix** (fn_8000E510; Maya's transform stack) [V]:
```
M = T(t) * [Rpt * Rp * JO * R * Ra * Rp^-1] * [Spt * Sp * S * Sp^-1]
```
Every factor is gated by its flag. `R` = Euler(rotate, order), built by fn_8001D748 from
`PSMTXRotRad` with degree input. Rotation order (`+0xEC & 0xF`): 1 = xyz (X applied first,
M = Rz*Ry*Rx), 2 = yzx, 3 = zxy are verified from code; 4..6 are assumed xzy, yxz, zyx
(Maya enum); 7..12 share code with 1..6 [G]. Order 1 is the only one seen in the units checked.
World = parent world * local.

Matrix per drawn node (fn_80018F74): `world * inv_bind` if flag 0x2, else `world`.

Units: one skeleton.g holds both the joint chain (`body`, `chest`, `shoulder_l`, ...) and
helper/attachment nodes (`_l_hand_`, `_bw_`, `BWU`, `face1`, `hair1`, `_root_`, ...).
Weapons use `_flash_`, `_tr1_`, `_tr2_` (trail/effect points) plus mesh nodes. Map terrain `.g`
files have a single node.

---

## 4. `.gs`: geometry, materials, display lists

The `.gs` is an **IS relocatable container**: u32 file_size, u32 data_size, u32 pointer_count,
u32 import_count, u32 export_count, 12 reserved bytes, data, u32 pointer offsets, then
{u32 data_off, u32 name_off} for imports and exports, then names. fn_80075874 relocates it,
resolves imports by name (fn_80076D48) and writes a 7-byte runtime magic into header bytes
0x18-0x1E. Almost all .gs files have no imports or exports. 56 particle "shape" models
(`smok02.gs`, ...) export one label `shape` and have only a material (no geometry). That is why
`gmodel.py` uses its own lenient container reader; older versions of `isbin.ISBin.check` rejected those files (fixed). Offsets below are relative to the data start
(file offset 0x20).

### 4.1 Model header (0x64 bytes) [V unless noted]

| Off | Type | Meaning |
|---|---|---|
| 0x00 | ptr | name string (always "unknown") |
| 0x04 | u32 | `0x20040723`: version/date stamp, identical in all files |
| 0x08 | u32 | unknown, varies (looks like a hash/id) [G] |
| 0x0C | f32[3] | bbox min (maps: 10000,10000,10000 placeholder) |
| 0x18 | f32[3] | bbox max |
| 0x24 | ptr | positions: s16 x,y,z (6 B), scaled by 2^-pos_frac -> GX_VA_POS |
| 0x28 | ptr | normals: s8 x,y,z (3 B), scaled by 2^-nrm_frac -> GX_VA_NRM / NBT |
| 0x2C | ptr | texcoords: s16 s,t (4 B), scaled by 2^-tex_frac -> GX_VA_TEX0..7 (shared array) |
| 0x30 | ptr | vertex colours RGBA8 (4 B) -> GX_VA_CLR0/1 |
| 0x34 | ptr | materials[mat_count] (0x20 each) |
| 0x38 | ptr | groups[grp_count] (0x24 each) |
| 0x3C | ptr | mesh list, pass 1 (linked list) |
| 0x40 | ptr | mesh list, pass 2 |
| 0x44 | ptr | mesh list, pass 3 (fn_80018888 picks the list by its pass argument: 1 -> +0x3C, 2 -> +0x40, 3 -> +0x44) |
| 0x48 | ptr | optional **envelope block** (298 of 6,997 models: 266 `zu/` cutscene models incl. the cutscene dragons; battle-unit `ymu/` dragons are rigid, 26 `xwp/` weapons, 6 `yme/` effects): weighted CPU skinning, see 4.5 |
| 0x4C | u16 | position count |
| 0x4E | u16 | normal count |
| 0x50 | u16 | texcoord count |
| 0x52 | u16 | colour count |
| 0x54 | u16 | material count |
| 0x56 | u16 | group count |
| 0x58 | u16 | mesh count (total) |
| 0x5A | u16 | 0 |
| 0x5C | u8 | pos_frac (GX VAT frac bits) |
| 0x5D | u8 | nrm_frac (6) |
| 0x5E | u8 | tex_frac (14 in all files seen) |
| 0x5F | u8 | 0 |
| 0x60 | u32 | 0 [G] |

Arrays and display lists follow; strings go at the end of the data.

### 4.2 Material (0x20) [V layout / D semantics]

| Off | Type | Meaning |
|---|---|---|
| 0x00 | ptr | name (Maya shader name: `lambert2`, `blinn1`, `map_base`, ...) |
| 0x04 | u16 | flags: 0x1 specular (blinn), 0x4 drawn only in queue 5, 0x8 fog off, 0x10/0x20/0x30 z mode (LEQUAL+write / off / GEQUAL), 0x40 screen-copy refraction (fn_80014158), 0x80 sphere env map (unused), 0x400 glow/bloom, 0x1800 lighting mode, 0x2000/0x4000/0x6000/0x8000 blend additive/subtract/multiply/2x multiply (any of these forces 0x8). Details: [materials.md](materials.md) [D/V] |
| 0x06 | u8 | layer count |
| 0x07 | u8 | runtime flags set by fn_80012430: 0x1/0x2/0x4 callback type, 0x8 first batch, 0x10 hidden, 0x20 multi-layer (cleared by any mode-0 layer), 0x40 has blend 5, 0x80 has blend 6 |
| 0x08 | u8[4] | colour 0 RGBA (material colour; RGB x1.25 at load, so Maya 0.8 grey becomes white; alpha 0 = not drawn until animated) |
| 0x0C | u8[4] | colour 1 RGBA: RGB zeroed at load, only an animation target |
| 0x10 | u8[4] | colour 2 RGBA: alpha zeroed at load, only an animation target |
| 0x14 | ptr | layers[layer count] (0x1C each) |
| 0x18 | u32 | 0 |
| 0x1C | u32 | 0 |

**Texture layer (0x1C)**, consumed by fn_80012F00 (one TEV stage per layer; full render state in [materials.md](materials.md)):

| Off | Type | Meaning |
|---|---|---|
| 0x00 | u16 | flags: 0x1 identity UV transform, 0x2/0x4/0x8 = translate/scale/rotate present (informational; runtime tests only 0x1), 0x20 force REPEAT wrap, 0x80 keep the texcoord byte from the file [V by data] |
| 0x02 | u8 | texcoord generator source; at load becomes `layer_index + 4` (GX_TG_TEX0 + i). If the mesh lacks that TEXn attribute, TEX0 is used |
| 0x03 | u8 | TEV blend mode 0..7, see [materials.md](materials.md). Mode 0 = MODULATE and **ends the layer chain**; 1 = lerp(prev, tex, tex.a); 5 = tex to REG0 (map terrain only); 6 = emboss bump appended later; 7 = ras colour, tex.a x ras.a. Seen: 0 (15,660), 1 (685), 7 (385), 5 (111) |
| 0x04 | u16 | **texture index into the TPL** (unit: `<unit>.tpl`; weapon: `<w>.tpl`; map: `texpack.tpl`) [V] |
| 0x06 | u8 | wrap S: unused by the game (wrap and filter come from the TPL header) |
| 0x07 | u8 | wrap T: unused |
| 0x08 | f32 | UV translate U |
| 0x0C | f32 | UV translate V |
| 0x10 | f32 | UV scale U |
| 0x14 | f32 | UV scale V |
| 0x18 | f32 | UV rotate (degrees) |

The UV transform is built in fn_80012F00: rotate about (0.5, 0.5), scale about V=1, then translate
(U, -V). The .ga material sub-blocks types 8-12 animate it (section 5.3).

### 4.3 Group (0x24): culling/bounds [V layout]

`ptr name ("none"), f32 bbox_min[3], f32 bbox_max[3], s16 node, u16 0, u32 0`.
Every mesh points to one group. For rigid meshes `node` is the mesh's node.

### 4.4 Mesh / draw batch (0x20), linked list [V]

| Off | Type | Meaning |
|---|---|---|
| 0x00 | ptr | group |
| 0x04 | ptr | next mesh (0 = end) |
| 0x08 | u16 | flags: 0x2 skinned (matrix palette path, fn_80018F74); 0x1 envelope mesh (POS/NRM from the CPU-skinned buffer, section 4.5); 0x4 reuse the previous batch's material/TEV state; 0x8 skip lighting-channel setup; 0x10/0x20 hidden; 0x1800 cull (0x1000 back, 0x800 front, 0x1800 none); 0x6000 render list 1/2/3 = opaque / alpha-test / translucent (fn_80011838). Common values 0x580C, 0x780C, 0x7800, 0x300C, 0x3000 [V] |
| 0x0A | s16 | material index |
| 0x0C | s16 | node index into the .g (rigid meshes and envelope meshes) |
| 0x0E | s16 | runtime: matrix slot |
| 0x10 | u32 | vertex descriptor bits (below); low 28 bits passed to fn_80019AB0 |
| 0x14 | ptr | display list (32-byte aligned) |
| 0x18 | u32 | display list size |
| 0x1C | ptr | matrix palette or 0: `u8 0x10, u8 count (<=10), u8 node_index[count]` |

**Vertex descriptor** (fn_80019AB0, all attributes `GX_INDEX16` except PNMTXIDX):

| Bit | GX attribute | Array / format |
|---|---|---|
| 0x1 | GX_VA_PNMTXIDX (direct u8) | value = palette slot * 3 |
| 0x200 | GX_VA_POS | +0x24, XYZ S16, frac = header 0x5C |
| 0x400 | GX_VA_NRM | +0x28, XYZ S8, frac = header 0x5D |
| 0x800 | GX_VA_NBT (NBT3) | +0x28, S8 [D, not seen in the data checked] |
| 0x1000 | GX_VA_CLR0 | +0x30, RGBA8 |
| 0x4000 << n | GX_VA_TEXn (n = 0..7) | +0x2C, ST S16, frac = header 0x5E |

Vertex byte order in the display list follows GX attribute order: `[pnmtx u8] pos u16 [nrm u16] [clr u16] [texN u16 ...]`.
Display lists are plain GX FIFO streams: `0x98 | vat` tristrip, `0x90` triangles, `0xA0` fan,
`0x80` quads, then u16 vertex count, then vertices. 0x00 bytes pad to 32. Only VAT 0 occurs.
**Every one of the 1.6 million primitives on the disc is a triangle strip (0x98).**
Descriptors seen (count of meshes): 0x5600 20,360; 0x4600 15,917; 0x4601 4,196; 0x5601 2,587;
0x405600 2,300; 0x804600 315; 0x405601 145; 0xC600 98 (TEX0 + TEX1, map terrain); 0xD600 39;
0x805600 11. NBT and CLR1 never occur. Bits 0x400000 and 0x800000 are **not** vertex
attributes: fn_80019AB0 only tests TEX0..TEX7 (0x4000..0x200000). 0x400000 = the vertex colour
carries alpha (lighting setup, e.g. `kage` shadow quads) [V]; 0x800000 is unknown (only on
envelope meshes). (An earlier version of this document called them TEX4/TEX5, which was wrong.) Vertex
colours (0x1000) are in 4,689 models, mostly map props (baked lighting).

### 4.5 Envelope block (header+0x48): weighted skinning [V]

Used by 298 models: every `zu/` cutscene model (`zu/<name>/pack.cmp:body.gs`, including the
dragons `ddra*`/`dra*`, laguz, Tibarn, ...), 26 `xwp/` weapons and 6 `yme/` effects. In these
models header 0x24 (positions) is 0, and the meshes with **mesh flag 0x1** take POS and NRM from
the skinned buffer below. Their display-list POS index always equals their NRM index (sweep).

Code: fn_8001CD78 is the driver. It double-buffers each batch's records through the locked L1 cache
(LCLoadBlocks to 0xE0000000) and sets GQR6 = `((frac << 8) | 7) << 16` (load s16 * 2^-frac,
store f32) and GQR7 = 0x08040606 (load u8 * 2^-8, store s8 * 2^6). fn_8001D2FC builds the
batch's blend matrix and fn_8001D024 / fn_8001D144 transform the records (paired-single asm;
read from `build/RFEE01/asm`, because Ghidra's C for these is meaningless). The output buffer is
object+0x68 (fn_80007FC0). The bone matrices are the object's array at +0x64
(fn_800080E4), 0x30 bytes per **node index**.

Block header:

| Off | Type | Meaning |
|---|---|---|
| 0x00 | u32 | batch table offset (relative to the block) |
| 0x04 | u32 | record data offset (relative to the block) |
| 0x08 | s16 | batch count |
| 0x0A | u16 | unknown, not read by the skinning code [G: total size or count] |
| 0x0C | u8 | `frac`: input scale 2^-frac (7..14; 11 in 212 models) |

Batch (0x18 bytes). Every vertex in a batch shares the same bone set and weights:

| Off | Type | Meaning |
|---|---|---|
| 0x00 | u16[4] | node indices into the `.g` (0xFFFF = unused slot) |
| 0x08 | u8[4] | weights, w = u8 / 256 |
| 0x0C | u32 | record offset into the data (32-byte aligned) |
| 0x10 | u16 | bytes to DMA (covers skip + records) |
| 0x12 | u8 | skip: byte offset of the first record within the DMA |
| 0x13 | u8 | bone count 1..4. With 1 the weight is ignored (the matrix is used as is) |
| 0x14 | u16 | count A: plain vertices, 1 record each (fn_8001D024) |
| 0x16 | u16 | count B: NBT vertices, in records (2 per vertex; fn_8001D144 gets B >> 1) |

Record (12 bytes): `s16 x, y, z, nx, ny, nz`, all scaled by 2^-frac (normals too).
An NBT vertex is two records: (pos, N) then (B, T). Count B is 0 everywhere on the disc, so the
NBT path is [D] only. Both kernels get the same source and destination, so a batch uses A or B, never both.

Skinning per batch (fn_8001D2FC): `M = sum_i w_i * Bone[node_i]` with no renormalisation
(only `Bone[node_0]` when count = 1), `Bone[n] = world(n) * inv_bind(n)` for every node,
whatever its flag 0x2. Then for each record `pos' = M * pos`, `nrm' = M3x3 * nrm`.

Output buffer and indexing: the record at data byte offset `o` (= batch offset + skip + 12k)
goes to **slot o / 12**, stored at buffer + 16 * slot as `f32 pos[3]`, `s8 nrm[3]` (*64), 1 pad
byte. An NBT vertex fills 32 bytes: pos, N at +0x0C, B at +0x0F, T at +0x12. The game computes
the destination as `(o * 0xAAAAAAAB >> 32) * 2` (= o * 4/3). Alignment padding between batches
leaves unused slots. Mesh display lists index slots with their POS and NRM indices
(GXSetArray stride 0x10, NRM at +0x0C). The mesh is then drawn through the rigid path with
`world(mesh.node)`, so the skinned buffer is in model space.

Data facts (sweep of all 298 models; 1,186,084 vertices, 241,736 batches, 6,289 meshes):
bones per batch 1: 20,331, 2: 73,799, 3: 58,803, 4: 88,803. The weights of every multi-bone
batch sum to 1 ± 1/64 (175 batches are off by quantisation, e.g. 260/256). Up to 260 distinct
bone nodes per model. All DL indices hit a decoded slot. No NaNs in bind pose or posed
(257 `zu` models posed with their first animation). Bind pose = stored records. In 33 models,
some attachment/prop bones (e.g. `BW001`, `_r_hand_`, `Shield`, `Hips` in `ddraW`) have a `.g`
rest pose that differs from their inverse bind, so posing with the rest transforms is **not**
the bind pose. `GEnvelope.skinned(scene, None)` therefore returns the stored data.

Library: `GModel.envelope` (`GEnvelope`: `.batches`, `.vertices{slot: pos, nrm, influences}`,
`.skinned(scene, pose)`, `.summary()`), and `envelope_vertices(model)`. The latter returns
`[{slot, position, normal, influences: [(node, weight), ...]}]` for building a GPU vertex buffer.
`gmodel.py obj` exports envelope meshes in bind pose or posed with
`--anim ARC.pak:NAME.ga --frame N`. `zu` animations live in `zu/<name>/{cr,no,br}.pak`.

Rendered and checked (rest and posed): `zu/tibar_sky` (Tibarn, `cr.pak:att1_cr.ga`),
`zu/ddraW` (white dragon, `br.pak:att1_br.ga`), `zu/draR`, `zu/cat`.

**Porting notes (GPU skinning).** Turn each envelope vertex into a standard skinned vertex:
position, normal, `uint8 bone[4]`, `float/unorm8 weight[4]` (pad unused slots with weight 0).
Renormalise the weights if you want, since the game doesn't. Max 4 bones per vertex. The bone
palette is the model's distinct node set (at most 260 on the disc; tibar_sky uses 104), which fits in one
Metal buffer of float3x4 (12 KB). Upload `world(n) * inv_bind(n)` per frame. A vertex buffer
indexed by slot keeps the original display-list indices valid. Unused padding slots can be
zero. Rigid-skinned unit meshes (section 4.4, PNMTXIDX, <= 10 matrices per draw) map to the
same shader with one bone at weight 1.

**Skinning** [V]: rigid per vertex (one matrix, no weights). For each palette slot i the game
loads `PNMTX(3i) = view * world(node) * inv_bind(node)` (inv_bind only for flag-0x2 nodes).
Vertices and normals are stored in bind-pose model space. Rigid meshes (no PNMTXIDX) use
`world(mesh.node)` (fn_80019504, which batches up to 10 node matrices per draw).

---

## 5. `.ga`: animation

Plain self-relative file. Relocated by fn_8000BC20, sampled by fn_8000DD0C (node channels);
material channels by fn_8000A838..fn_8000B958.

### 5.1 Header (0x30) [V]

| Off | Type | Meaning |
|---|---|---|
| 0x00 | u32 | sub-block list head offset (0 = none) |
| 0x04 | u32 | offset (relocated), use unknown [G] |
| 0x08 | u8 | non-zero = sub-block list present |
| 0x0C | u32 | flags: 0x10 = s16 keys, 0x20 = packed 32-bit keys, neither = float keys; 0x8 asserts; 0x2 = use quaternion channel; 0x1 = ? (all files have 0x11) |
| 0x10 | u32 | 0/1 [G loop?] |
| 0x14 | s32 | start frame (the code uses +0x14 or +0x18 as the initial frame depending on play direction, fn_80009150) |
| 0x18 | s32 | end frame (60 fps) |
| 0x1C | u32 | track count |
| 0x20 | u32 | tracks offset (= 0x30) |
| 0x24 | u32 | curves offset |
| 0x28 | u32 | frame->key lookup table offset (float mode only) |
| 0x2C | u32 | keys offset |

**Track (16 B)**: `u32 node_index, u32 extra_node_flags (ORed onto the node flags, e.g. 0x30 = R+T), u32 first_curve, u32 curve_count`.

### 5.2 Curves and keys

`channel` indexes the 31-float transform record of section 3 (0-2 S, 3-5 R in degrees, 6-8 T,
9-11 JO, 12-14 Rp, 15-17 Sp, 18-20 Rpt, 21-23 Spt, 24-26 Ra, 27-30 quaternion).
Channels used on the disc: 0-8 (S, R, T) and 12-14 (rotate pivot, a few hundred curves); nothing else.

* **s16 mode (flag 0x10): all 16,797 .ga files on the disc use it** [V]: curve = 12 B
  `u16 channel, u8 shift, u8 0, u16 last_frame(?), u16 key_count, u32 key_index`;
  key = `s16 frame, s16 value` at `keys_off + 4*key_index`; value = raw * 2^-shift.
  Linear interpolation; clamp before the first and after the last key. Verified by posing a unit with `wait_1.ga`.
* **packed32 mode (0x20)** [D]: same curve header; key = u32, frame = bits 31..20,
  value = signed 20-bit (bits 19..0) * 2^-shift. Linear.
* **float mode** [D]: curve = 20 B `s32 channel, s32 key_count, s32 lut_index, s32 key_index,
  f32 constant`; key = 16 B `s32 frame, f32 value, f32 in_tan, f32 out_tan`;
  `s16 lut[lut_index + frame]` gives the active key (-1 = before the first). Linear, except that
  channels 27-30 use a Hermite curve with the tangents when `key.out_tan < const`.

`GAnim.sample(frame)` in gmodel.py implements the s16/packed/float linear paths and returns
`{node: {"flags", "values": {channel: value}}}` for `GScene.world_matrices(pose)`.

### 5.3 Sub-blocks (list at header+0x00) [D, partial]

List node: `u32 type, u32 block_off, u32 next_off`. At load, for every type except 0xD,
`block+4` is set to `block+8` (a self-pointer to a u16 offset table). Lookup by type:

| Type | Reader | Meaning |
|---|---|---|
| 0 | ? | 3,566 files, e.g. unit `wait_1.ga`: frame-tagged entries [G: hit/sound timing] |
| 1 | fn_8000BF68 | ? (196 files) |
| 2, 3 | ? | one file each |
| 5 | fn_8000A0A8 / A168 / A22C | event table: per entry `u16 id, u16 value` lists; 12,587 files (most unit motions) |
| 6 | fn_8000AB6C | per-material byte value (alpha?) |
| 7, 0xE, 0xF | fn_8000A838 | per-material colour component bytes (R, G, B?) |
| 8, 9 | fn_8000AE38, fn_8000B100 | UV translate U, V |
| 10 | fn_8000B3C8 | UV rotate |
| 0xB, 0xC | fn_8000B690, fn_8000B958 | UV scale U, V |
| 0xD | ? | raw block (no relocation), 429 files |

Material curve layout (types 6-12): `u16 ?; u16 ?; u32 table_ptr (runtime)`, then
`u16 offset[material_count]` (0xFFFF = none, offset relative to the block). Each curve:
`u16 key_count, u16 interp (0 linear, 1 step), {u16 frame, s16 value}[key_count]`.
Example: map water `bmap0101_water0.ga` has 0 tracks and one type-8 block (scrolling UVs).
Value scaling per type is not confirmed.

---

## 6. Tools

```
python3 tools/formats/tpl.py IN.tpl|IN.cms OUTDIR       # every image -> PNG
python3 tools/formats/tpl.py --survey orig/RFEE01/files  # format histogram
python3 tools/formats/gmodel.py info FILE.g|.gs|.ga|PACK.cmp
python3 tools/formats/gmodel.py info X.ga --g skeleton.g # names in the anim dump
python3 tools/formats/gmodel.py obj ymu/archer1/pack.cmp OUT [--anim wait_1.ga --frame 0]
python3 tools/formats/gmodel.py obj zmap/bmap0101/map.cmp OUT [--gs house_day01.gs]
python3 tools/formats/gmodel.py obj xwp/alondite/alondite.cmp OUT
```
`obj` writes `<stem>.obj/.mtl` and decodes the TPL to `<stem>_tex<i>.png`. For units it picks
`<unit>.tpl` next to `pack.cmp`; use `--tpl` for colour variants. MTL uses layer 0's texture only.
Library classes: `TPL`, `GScene`, `GNode`, `GModel`, `GMesh`, `GMaterial`, `GLayer`, `GAnim`,
`GEnvelope` (+ `envelope_vertices()`). `--anim` also accepts `ARCHIVE.pak:NAME.ga`. When no
`<unit>.tpl` exists (zu `_sky` variants), the first `.tpl` in the pack's directory is used.

Verified by rendering the OBJ output (scratch software rasteriser): archer1 in rest pose and
posed with `wait_1.ga` frame 0 (bow in hand, textures correct), map prop `house_day01`,
terrain `bmap0101`, weapon `alondite`.

**Whole-disc sweep**: loose files plus every pack: 6,997 .g, 6,997 .gs (incl. 56 material-only shape models) and 16,797 .ga parse with no errors.
All display lists decode with no leftover bytes and every index is in range, including the
6,289 envelope meshes of the 298 envelope models (section 4.5).

## 7. Open questions

* Header 0x08 and the mesh flag bits 0x0800/0x1000/0x2000/0x4000 (render pass / culling / lighting?).
* Envelope block: field 0x0A of the block header; the NBT (count B) path is unused on the disc
  and documented from asm only. Exactly which nodes the game writes into object+0x64 for nodes
  without flag 0x2 was not traced. world * inv_bind is assumed, and it reproduces correct
  poses in every render.
* Vertex-descriptor bit 0x800000 (not a GX attribute; 0x400000 = vertex colour alpha).
* Rotation orders 4-12; the scale/rotate pivot translate and rotate-axis channels are not seen in data.
* TEV/blend/z/lighting per material: now in [materials.md](materials.md) (remaining gaps listed there:
  water/haze stages, terrain mask projection, refraction matrix, glow composite).
* .ga sub-block types 0, 1, 5, 0xD, and the value scaling of the material channels.
* Map prop placement: decoded in [maps_events.md](maps_events.md) (`mapdesc`/`mapinst`, `mapdata.py --props/--obj`).
* Float and packed32 .ga modes do not occur on the disc (sweep); their code paths are documented from the decompiled code only.
