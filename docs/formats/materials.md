# FE10 materials: how a `.gs` material is drawn (GX TEV / blend / alpha / z / lighting)

Fire Emblem: Radiant Dawn (RFEE01 Rev 1). Companion to `graphics.md` (file layouts) and
`maps_events.md` (map lights / fog / draw passes). Tool: `tools/formats/gmaterial.py`.

Tags: **[V]** verified in code and against data (disc survey and/or software render),
**[D]** read from the decompiled code (Ghidra C cross-checked against the dtk assembly
where Ghidra dropped arguments), **[G]** guess. Every item names its function.

GX enum names below are the Revolution SDK ones (`GX_CC_TEXC`, `GX_BL_SRCALPHA`, ...),
abbreviated without the prefix. "RAS" = the rasterised colour of the TEV stage's colour
channel (`COLOR0A0` unless stated).

## 0. Summary for a port

* Only **four** layer blend modes occur on the disc: 0 (15,660 layers), 1 (685), 5 (111), 7 (385).
  Modes 2, 3, 4, 6 exist in the code but are unused. [V]
* A mode-0 layer **ends the layer chain** (fn_80012F00 returns 0, fn_8001444C breaks). So the
  chains `(0,1)`, `(0,0)`, `(0,0,1)` (379 materials) draw only their first layer. [V code, asm `li r3,0`]
* The multi-layer chains `(1,5,1,1)` and `(1,5,1,1,1)` are only on `map_base` / `map_wall`
  materials of map terrain (zmap, zbg), whose TEV is replaced by a hard-coded shader (fn_80141650, section 7).
* So **ordinary models are a single TEV stage**: `tex * RAS` (mode 0), or `RAS` with alpha
  `tex.a * RAS.a` (mode 7), or just `RAS` (no layer). On top of that the game may append:
  one `PREV * matColour` stage (vertex-coloured meshes, section 4), one `PREV + specular`
  stage (material flag 0x1), a refraction stage (flag 0x40). 193 distinct full states on the disc (section 9).
* The render pass comes from the mesh list: list 1 opaque, list 2 alpha-test `a > 128`,
  list 3 alpha-blend `a > 0`, no z write. Material flags override blend (additive / subtract / multiply),
  z and fog. Cull comes from the mesh flags. Lighting is per-vertex GX lighting
  (`mat * clamp(amb + Σ diffuse)`) or unlit.

## 1. Pipeline per draw batch

`fn_80018888(obj, pass)` walks the mesh list of the pass (`header+0x3C/0x40/0x44` for pass 1/2/3).
For each mesh (`fn_80018888`) [D]:

1. skip if material runtime flag 0x10 (hidden by a pass filter, fn_80015070) or mesh flags & 0x30;
2. matrices (rigid fn_80019504 / skinned fn_80018F74), vertex format fn_80019AB0 when the
   descriptor changes;
3. if the mesh has flag 0x4 and a previous batch exists, **reuse the previous material state**;
   otherwise `fn_8001444C(obj, anim, mesh, material, tpl)` then `fn_800186C8(material)`;
4. `GXCallDisplayList` if fn_8001444C returned non-zero (it returns 0 when the material alpha is 0);
5. type-4 material callbacks (fn_80014818).

`fn_8001444C` (material setup) [D]:

| Step | Function | What |
|---|---|---|
| reset | – | allocation counters: TEV stage, texmap, texcoord, texmtx, TEV register (`lbl_804CB098..9E`); indirect stages back to direct |
| callbacks type 1 | fn_800146A8 | if the material has a type-1 callback (runtime flag 0x1, registered by material name, section 7): it does **all** TEV and channel setup; jump to the end |
| layers | fn_80012F00 | if object flag 0x800 is clear and layer count > 0: one TEV stage per layer in order, skipping mode-6 layers, **stopping after the first mode-0 layer**. Else one stage `TevOrder(NULL,NULL,COLOR0A0)`, `GXSetTevOp(PASSCLR)` |
| refraction | fn_80014158 | material flag 0x40 (section 5.3) |
| material colour | fn_800125A8 | `GXSetChanMatColor(COLOR0A0)`, optional extra stages (section 4); returns 0 → batch not drawn |
| lighting | fn_80013CF0 | channels (section 3), optional specular stage |
| cull | fn_800140A0 | section 6 |
| callbacks type 2 | fn_80014760 | append stages (map_trans, kbground, eyema, ...) |
| post | fn_8001393C | if object flag 0x800 clear: mode-6 layers, multi-layer RAS stage, env map (section 5.2) |
| counts | fn_80021BF4/C34/C74 | `GXSetNumTevStages(stages)`, `GXSetNumTexGens(texcoords)`, `GXSetNumIndStages(ind)` |

All GX calls go through state-caching wrappers (fn_80021784..fn_800221BC, `lbl_803BF878..`).
Wrappers: fn_80021CB4 TevOrder(stage, coord, map, chan), fn_80021E20/E8C TevColorIn/AlphaIn(stage, a, b, c, d),
fn_80021D18/D9C TevColorOp/AlphaOp(stage, op, bias, scale, clamp, out), fn_80021EF8 TevOp,
fn_80021F7C TexCoordGen2(coord, type, src, mtx), fn_80021A08 ChanCtrl(chan, enable, amb, mat, mask, diff, attn),
fn_800218A8 ChanAmbColor, fn_80021958 ChanMatColor, fn_80021BA4 BlendMode, fn_80021808 AlphaCompare,
fn_80021860 ZMode, fn_800217CC ZCompLoc, fn_80021B68 CullMode, fn_80021FE8 AlphaUpdate,
fn_80021FEC ColorUpdate (both are inline `0xCC008000` writes of the cmode0 BP register, bits 4 and 3),
fn_80021FF0/fn_80022050 KColorSel/KAlphaSel. Allocation pools: stages 0..15, texmaps 0..7,
texcoords 0..7, texmtx `GX_TEXMTX0..9` (30+3i), TEV registers in the order REG0, REG1, REG2, PREV (`lbl_80378838`),
konst colours K3, K2, K1, K0 (`lbl_80378848`). The 62 inline FIFO writes found in the render code
are these two cmode0 writes plus SDK-internal register pokes; no material state is
written behind the wrappers' back. [D]

## 2. Layer → TEV stage (fn_80012F00) [D, data V]

For layer *i* the function allocates stage *s*, texcoord *c*, texmap *m*:

* **Texture**: `fn_80006A64(tpl, &texobj, layer.texture)` builds the GXTexObj from the **TPL
  image header** (wrap S/T, min/mag filter, LOD bias, min/max LOD; mipmapped when min_lod != max_lod;
  an out-of-range index uses image 0). The layer's own wrap bytes (+0x06/+0x07) are **not read**
  (they hold junk such as 51/5 or 176/46 in some files). CI8 textures load their TLUT into TLUT0.
  Layer flag 0x20 re-inits the object with REPEAT/REPEAT and default LOD (never set on the disc).
* **Texcoord source**: `GX_TG_TEX(layer_index)` (the loader fn_80012430 overwrites the file byte
  with `index + 4` unless layer flag 0x80); if the mesh's vertex descriptor lacks that TEXn,
  TEX0 is used. So map terrain (TEX0 + TEX1, descriptor 0xC600) has layer 1 on UV1, all other layers on UV0.
* **Texgen**: `GXSetTexCoordGen2(c, GX_TG_MTX2x4, src, mtx)`. `mtx = GX_IDENTITY` when the layer
  has flag 0x1 and the object has no animation; otherwise a 2x4 matrix is loaded into the next
  `GX_TEXMTXn`:
  `M = T(tu, -tv) · [T(0,1) · S(su, sv) · T(0,-1)] · [T(.5,.5) · Rz(-rot°) · T(-.5,-.5)]`
  (each factor only if non-identity; values can be overridden per frame by .ga material
  blocks 8..12: fn_8000AE38 U, fn_8000B100 V, fn_8000B3C8 rotate, fn_8000B690/B958 scale).
  `gmaterial.py` prints the matrix. t = 0 is the first texel row.
* **Layer flags** (survey of 16,841 layers) [V]: 0x1 = identity transform (14,281), 0x2 = has
  translate (166), 0x4 = has scale (2,042), 0x8 = has rotate (45); combinations 0x6, 0xC. They are
  exporter hints: the runtime only tests 0x1 (and 0x20 / 0x80). No env/sphere-map meaning.
* `TevOrder(s, c, m, COLOR0A0)`, then the mode switch:

| Mode | Colour (a, b, c, d → out) | Alpha | Return | Count |
|---|---|---|---|---|
| 0 | `GXSetTevOp(MODULATE)`: stage 0 `TEXC*RASC`, `TEXA*RASA`; later stages `TEXC*CPREV`, `TEXA*APREV` | (same) | **0 = stop chain** | 15,660 |
| 1 | stage 0: `GXSetTevOp(MODULATE)`. Else `(CPREV, TEXC, TEXA, ZERO)` = `lerp(prev, tex, tex.a)` | `APREV` | 1 | 685 |
| 2 | `(ZERO, TEXC, CPREV, ZERO)` = `tex*prev` | `APREV` | 1 | 0 |
| 3 | `(ZERO, CPREV, TEXC, ZERO)` = `prev*tex` | `APREV` | 1 | 0 |
| 4 | op SUB `(ZERO, ONE, TEXC, CPREV)` = `prev - tex` | `APREV` | 1 | 0 |
| 5 | `(ZERO, ZERO, ZERO, TEXC)` → **REG0** (first TEV register; reused if already allocated) | `APREV` → PREV | 1 | 111 |
| 6 | stage A `(ZERO,TEXC,ONE,CPREV)` = `prev+tex`, no clamp; stage B with a new texcoord `GX_TG_BUMP0` from the previous texcoord, same texmap, no channel: op SUB `prev - tex` (emboss bump) | `APREV` | 1 | 0 |
| 7 | stage 0: `(ZERO,ZERO,ZERO,RASC)` = `RAS`, alpha `TEXA*RASA` (no clamp). Else `CPREV`, alpha `TEXA*APREV` | see colour | 1 | 385 |

All ops: ADD, bias ZERO, scale 1, clamp on, output PREV unless stated. Mode-6 layers are
skipped in the main loop and appended later by fn_8001393C (only if runtime flag 0x80).
fn_80012430 sets runtime flags +0x07: 0x20 = more than one layer and no mode-0 layer, 0x40 = has a
mode-5 layer, 0x80 = has a mode-6 layer.

**Mode 5 register** [D]: nothing in the generic path reads REG0 afterwards; mode 5 only occurs
in `map_base`, whose TEV is replaced (section 7.1), where layer 1's texture is the projected
mask. Treat mode 5 as "no visible effect" outside maps.

## 3. Lighting channels (fn_80013CF0) [D, channel choice V by data]

Skipped when mesh flag 0x8 is set and this is not the first batch of the draw (runtime flag 0x8
marks the first batch). Material flags `& 0x1800`:

| 0x1800 bits | Meaning |
|---|---|
| 0 | lit (unless object flag 0x10000) |
| 0x800 | lit |
| 0x1000 | **unlit** (6,318 materials, mostly effects) |
| 0x1800 | lit with light mask 0, ambient = (set ambient + colour of the set's first directional light) / 2 |

Vertex colour (descriptor 0x1000 = CLR0) makes the colour channel's material source VTX
(unless object flag 0x400). Descriptor bit **0x400000** (not a texcoord; graphics.md 4.4 calls it TEX4)
means "vertex colour carries alpha": the alpha channel's material source becomes VTX. Verified:
`kage` shadow quads (0x405600) have vertex alpha 98 and draw as soft translucent shadows.

Lit:
```
GXSetNumChans(1)
GXSetChanCtrl(COLOR0, enable=1, amb=REG, mat=VTX if CLR0 else REG, mask=set.diffuse_mask, CLAMP, SPOT)
GXSetChanCtrl(ALPHA0, enable=0, amb=REG, mat=VTX if CLR0 & 0x400000 else REG, 0, NONE, NONE)
GXSetChanAmbColor(COLOR0A0, set.ambient)
```
Unlit: same with `COLOR0 enable=0, attn NONE`, ambient white. So
`RAS.rgb = matSrc.rgb * clamp(amb + Σ_lights max(N·L,0) * lightColour)` (lit) or `matSrc.rgb`
(unlit); `RAS.a = matSrc.a` always (alpha lighting is off). Lighting is per vertex (GX).
`matSrc` = material colour register (section 4) or the vertex colour.

**Specular** (material flag 0x1, 186 materials, Maya blinn) unless object flag 0x400 [D]:
`NumChans(2)`, `ChanCtrl(COLOR1, enable, amb REG, mat REG, mask = set.specular_mask, diff NONE, attn SPEC)`,
`ChanCtrl(ALPHA1, off)`, ambient colour (0,0,0,255) and one extra stage
`TevOrder(NULL,NULL,COLOR1A1)`, colour `CPREV + RASC`, alpha `APREV`.
Game bug: the material colour for COLOR1A1 is "set" through fn_80021958(5, ...), which for
channels other than 0/2/4 calls `GXSetChanAmbColor` (assembly 0x800219F0). The COLOR1 material
colour therefore keeps its previous value, the GX default white. A port should use white.

**Light sets** (fn_80011280; 9 sets of 0x128 bytes at `lbl_803B6710`, picked by object byte
+0x81 through fn_80010BB0, negative = current default) [D]:
`+0 u8 diffuse light mask (built), +1 u8 specular mask (built), +2 RGBA ambient,
+8 light[8] × 0x24: +1 type, +2 intensity % (scales RGB), +3 copy-from index, +4 RGBA colour,
+8 vec3 direction/position, +0x14 spot cutoff, +0x20 distance`. Types: 1/2 directional (point light
at `-10000·dir` in view space, no attenuation), 3/4 specular direction (`GXInitSpecularDir`,
shininess attn a=(0,0,1) k=(64,0,-63), goes into the specular mask), 5/7 point (dist attn
`GX_DA_MEDIUM`, ref distance +0x20, 0.5), 6 spot (`GX_SP_COS`). Map lights come from
`map.bin` `maplight` and fill sets 0 and 1 (maps_events.md 2.6). fn_800AB310 sets byte +0x81 = 1
for models whose descriptor has flag 0x10, else 0. Which objects (units vs props) use set 1 is
not resolved [G].

## 4. Material colour (fn_800125A8) [D, V for the ×1.25]

At load (fn_80012430): colour0 RGB ×1.25 (clamped; Maya's 0.8 grey `cccccc` becomes white),
colour1 RGB = 0, colour2 alpha = 0. Colours 1 and 2 are therefore only animation targets.

Per batch (static object: colour bytes +8..+0xA = 0x80, alpha +0xB = 0xFF, no animation):
1. `col = colour0`; alpha from .ga type 6 (fn_8000AB6C), then `alpha = alpha * obj.alpha / 255`.
2. material flag 0x4000 (subtract or multiply blend): `col = (a, a, a, a)`.
3. **alpha == 0 → batch not drawn.** 4,099 materials (mostly effects) have file alpha 0 and are
   faded in by animation.
4. .ga types 7 (colour0), 0xE (colour1), 0xF (colour2) override (fn_8000A838).
5. object colour < 0x80: channel × v/128.
6. If object flag 0x400 is clear and ((CLR0 and col.rgb != white) or (0x400000 and col.a != 255)):
   new stage, register Rn = col, `TevOrder(NULL,NULL,COLOR0A0)`,
   colour `CPREV * Cn` if CLR0 else `CPREV`; alpha `APREV * An` if 0x400000 else `APREV`.
   (The channel takes VTX as material source, so the material colour must be applied here.)
   1,868 material variants on the disc.
7. object colour > 0x80 (flash): stage `CPREV + reg`, reg = (v-128)*255/128.
8. animated colour1 != 0: stage `(CPREV * reg) * 2` with reg = 0.5 + 0.5·c (brighten).
9. animated colour2 != 0: stage `CPREV + reg` (additive tint).
10. object flag 0x2000 and full alpha: alpha = object byte +0x80.
11. `GXSetChanMatColor(COLOR0A0, col)`.

## 5. Post stages and special flags

### 5.1 Multi-layer RAS stage (fn_8001393C, runtime flag 0x20) [D]
`TevOrder(NULL,NULL,COLOR0A0)`, colour `RASC * CPREV`, alpha `RASA * APREV`. Only reachable
for `(1,5,1,1)` chains outside the map callback, i.e. never on the disc.

### 5.2 Env map (material flag 0x80) [D, unused]
The **last** texcoord is regenerated: `GXSetTexCoordGen2(last, MTX3x4, NRM, TEXMTXn = invTranspose(view*model),
normalize, PTTEXMTX0 = T(.5,.5,1)·S(.5,-.5,0))` (sphere map). No material has 0x80.

### 5.3 Refraction (material flag 0x40, fn_80014158) [D]
121 materials (yme effects, all unlit/additive). fn_800150F4 reserves a 608x448 RGB565 buffer at
load. When the material is set up, the EFB is copied to it (fn_8001F4D8). If the material has
layers, indirect stage 0 uses the last layer's texcoord/texmap
(`GXSetIndTexOrder`, `GXSetIndTexCoordScale(1,1)`, `GXSetIndTexMtx(IND_MTX0, fn_8001E51C, scale_exp -4)`,
`GXSetTevIndWarp(last stage, ind 0, signed, no replace, IND_MTX0)`). A new texcoord gets
`MTX3x4(POS, projection·modelview)` (screen UV), and the **last layer stage** is re-bound to the
screen copy with `GXSetTevOp(MODULATE)`. Result: `screen(uv_screen + warp(layer tex)) * RAS`.

### 5.4 Other material flags [D, counts V]

| Flag | Count | Effect |
|---|---|---|
| 0x0001 | 186 | specular (section 3) |
| 0x0004 | 264 | hidden in normal passes (fn_80015070 filter, runtime 0x10); drawn only by fn_8001B040 in render queue 5 (after the glow pass) |
| 0x0008 | 5,394 incl. forced | fog off (fn_80010980). fn_80012430 forces it when any of 0x6000 is set |
| 0x0010/0x0020/0x0030 | 237/1,995/29 | z mode, section 6 |
| 0x0040 | 121 | refraction (5.3) |
| 0x0080 | 0 | sphere env map (5.2) |
| 0x0100 | 0 | planar shadow caster (fn_8001A644, flattened, black) |
| 0x0200 | 64 | special sub-draw for objects with a `+0x7C` list (fn_8001A4E8) |
| 0x0400 | 2,101 | **glow**: also drawn into the bloom buffer (render queue 4: fn_8001AB10 EFB copy, fn_8001AEEC draws only 0x400 materials, fn_8001AC30 blurs 304x224 and composites). Normal pass unchanged |
| 0x0800/0x1000/0x1800 | 26/6,318/26 | lighting, section 3 |
| 0xE000 | | blend, section 6 |

## 6. Pass state, blend, alpha test, z, cull, fog

**Mesh lists** [V]: mesh flags 0x6000 encode the list: 0x2000 list 1, 0x4000 list 2,
0x6000 list 3 (100% of 51,934 meshes). fn_800180F0 queues list 1 in render queue 1, list 2 in
queue 2, list 3 in queue 3 (object flag 0x40 moves list 1 to queue 2; 0x180 moves both to 3).
An object with alpha byte != 0xFF draws all lists with pass-3 state (fn_8001A218).

**Pass state** (fn_80011838) [D]:

| Pass (list) | Blend | ZCompLoc | Alpha compare | Z |
|---|---|---|---|---|
| 0, 1 (list 1, opaque) | NONE (ONE, ZERO) | before tex | `NEVER 0 OR ALWAYS 0` (always) | LEQUAL, write |
| 2 (list 2, cutout) | NONE | after tex | `GREATER 128 OR NEVER` → **a > 128** | LEQUAL, write |
| 3, 4, 5 (list 3, translucent) | BLEND (SRCALPHA, INVSRCALPHA) | after tex | **a > 0** | LEQUAL, **no write** |
| 6 (end) | unchanged | | always | LEQUAL, no write |

Every pass also sets ColorUpdate on, AlphaUpdate off, cull BACK, swap tables and konst
selections reset to 0 (KCSEL/KASEL 0 = 1.0), fog from the global fog record (fn_800109B8;
maps_events.md 2.7).

**Material overrides** (fn_800186C8, if flags & 0xE038; the pass state is restored by
fn_80011838(-1) after the batch) [D, counts V]:

| flags & 0xE000 | Blend | Materials |
|---|---|---|
| 0x2000 | BLEND(SRCALPHA, ONE) additive | 4,908 |
| 0x4000 | SUBTRACT (dst − src) | 96 |
| 0x6000 | BLEND(DSTCLR, ZERO) multiply | 2 |
| 0x8000 | BLEND(DSTCLR, SRCCLR) 2× multiply | 2 |
| 0xA000 | BLEND(INVDSTCLR, INVSRCCLR) | 0 |

| flags & 0x30 | Z |
|---|---|
| 0x10 | test LEQUAL, write |
| 0x20 | **no test**, no write |
| 0x30 | test GEQUAL, no write |

Note that alpha compare stays at the pass value: an additive material in list 1 (2 cases)
gets no alpha test.

**Cull** (fn_800140A0, mesh flags & 0x1800, object flags & 0x18000000 = 0) [D, V by render]:
0x1000 or 0 → BACK; 0x800 → FRONT; 0x1800 → NONE (double-sided). GX front faces are clockwise
in window space (the y-down screen), with `gmodel.GMesh.triangles()` strip parity. Object flags
0x08000000 swap FRONT/BACK (mirrored objects), 0x10000000 forces BACK, 0x18000000 forces FRONT.

**Per-object overrides** (fn_800184BC, object flags & 0xE00273C0, runtime only) [D]: 0x1000
colour writes off, 0x2000 alpha writes on (passes 1/2), 0x200 additive, 0x4000 blend off,
0x20000 fog off, bits 0xE0000000 select z: 0x2 → off, 0x4 → GREATER, 0x6 → EQUAL, 0x8 → NEQUAL,
0xC → LEQUAL no write, 0xE → LEQUAL write.

**Draw order** [D]: render queues 0..5 are drawn in order (fn_800119BC, `+0x128..+0x13C` of the
camera); each queue is a FIFO in submission order (fn_80010788 appends); **there is no depth
sort** of translucent objects. Within a model the list order is the file order. The pass byte
(0x80, 0x8A, ...) stored with each queue entry comes from the object (+0x82); see
maps_events.md for the map descriptor passes.

## 7. Material callbacks (by name) [D]

Registered with fn_80014E24 (name compare stops at the end of either string, i.e. prefix match,
`kbground1` → `kbground`); type 1 replaces sections 2-4, type 2 appends after the channel setup,
type 4 runs after the draw.

| Material | Function | Type | What |
|---|---|---|---|
| `map_base`, `map_wall` | fn_80141650 | 1 | terrain shader, 7.1 |
| `map_water` | fn_801420B0 | 1 | water: COLOR0 lit mask 1 (CLAMP, attn NONE); stage 1 = layer-0 texture projected from above with scroll (.ga type 8 on 4 values) × RAS, alpha = konst (map +0x54, pulsing); stage 2 = same texture, second scroll, `(prev + tex·RAS)/2`; optional stage 3 with the second texture (map +0x55 mode 1-4) |
| `map_move` | fn_80143374 | 2 | sets layer 0 UV translate (movement-range scroll) |
| `map_trans` | fn_80142C44 | 2 | screen-projected mask: alpha = `APREV − K·tex.a`, alpha compare `> 0` (see-through occluders near the cursor) |
| `kbground` | fn_80142D90 | 2 | battle bg: appends `CPREV * tex(last layer)` projected from above (baked shadow map) |
| `kbwater` / `kbref` | fn_80143054 / fn_80143180 | 1 / 2 | battle bg water / reflection |
| `m_haze1`, `m_haze2`, `m_light1` | fn_800FBC90 | 1 | heat haze |
| `eyema` | fn_800B0340 | 2 | unit eyes |
| `waveB` | fn_8017D84C | 2 | wave effect |
| `mat_jp`, `mat_en`, `mat_ml` | fn_8026A724 / A7C4 / A864 | 2 | title logo language |

### 7.1 Map terrain (fn_80141650) [D, render V for UV0]
```
ChanMatColor(COLOR0A0) = object colour * 255/128;  t = layers[0].texture (atlas, CLAMP)
stage 0: coord MTX3x4(TEX0, identity), map tex[t]   : REG0.rgb = tex·RAS, REG0.a = 0
stage 1: coord MTX3x4(TEX1, identity), map tex[t]   : REG1.rgb = tex·RAS, REG1.a = 0
[pulse: stage with K = map highlight colour: REG1 = REG1 ± REG1·K]   (map +100 == 1)
stage 2: coord MTX3x4(POS, ortho(top view, map +0xE4)), map tex[t+1] (I4 mask)
         PREV.rgb = lerp(REG0, REG1, mask), PREV.a = KONST (1.0)
then cull + lighting (section 3)
```
`map_base` layers are `(t, mode 1), (t+1, mode 5), (t, 1), (overlay, 1)`; the shader only uses
layer 0's texture index and `index + 1`. In bmap0101 UV0 and UV1 are identical, so the lerp is a
no-op there; the mask (texpack image 1) looks like baked prop shadows. The rendered cobblestone
from UV0 is plausible; the exact projection of the mask was not checked [G].

## 8. Porting: fragment shaders

Vertex stage (all programs): GX per-vertex lighting
```
matSrc   = CLR0 ? vtxColor : matColor          // matColor = colour0*1.25 (+anim, obj tint)
matSrc.a = (CLR0 && vtx&0x400000) ? vtxColor.a : matColor.a
ras.rgb  = lit ? matSrc.rgb * saturate(amb + Σ max(dot(N,L_i),0) * lightCol_i) : matSrc.rgb
ras.a    = matSrc.a
spec     = flag 0x1 ? saturate(Σ specular_i)  (GX SPEC attn, shininess 128, mat colour white) : 0
uv_i     = (texMtx_i * float4(TEX_k, 0, 1)).xy           // section 2
```
Fragment programs that actually occur (with `sat = saturate`):
```
// P0  mode 0 (also chains (0,1) (0,0) (0,0,1))                    44,214 meshes
c = tex0(uv0) * ras;                    // rgb and a
// P1  no layer                                                       374
c = ras;
// P7  mode 7 (alpha mask)                                            377
c = float4(ras.rgb, tex0(uv0).a * ras.a);
// + V  vertex-coloured mesh with non-white material colour (appended)
c.rgb = sat(c.rgb * matColor.rgb);  if (vtxAlpha) c.a = sat(c.a * matColor.a);
// + S  specular (flag 0x1, appended)
c.rgb = sat(c.rgb + spec.rgb);
// + R  refraction (flag 0x40): the last layer stage becomes
c = screenCopy(screenUV + (tex_last(uv).rg - 0.5)*indScale) * ras;  // indirect warp, details 5.3
// generic multi-layer (unused on the disc, kept for completeness)
mode1: c.rgb = lerp(c.rgb, t.rgb, t.a);           mode2/3: c.rgb *= t.rgb;
mode4: c.rgb = sat(c.rgb - t.rgb);                mode5: reg0 = t.rgb;
mode7: c.a  *= t.a;                               then *ras if runtime 0x20
// map terrain (7.1)
c.rgb = lerp(atlas(uv0)*ras.rgb, atlas(uv1)*ras.rgb, mask(projXZ(pos)).r); c.a = 1;
```
Output state: alpha test (list 2: `a > 128/255`; list 3: `a > 0`; GX compares the 8-bit
alpha), blend and depth from section 6, then fog (GX fog on the projected depth, range-adjusted)
unless flag 0x8. Because lighting is per vertex and clamped before the multiply, a per-pixel
port should still light per vertex to match.

## 9. What is on the disc (gmaterial.py --survey)

6,997 models, 16,762 materials, 22,325 (material, mesh configuration) variants, 51,934 meshes,
193 distinct full states. Grouped by TEV program (variants / meshes):

| TEV program | Variants | Meshes |
|---|---|---|
| P0 `tex·ras` | 18,362 | 44,214 |
| P0 + V (×matColour, alpha pass) | 998 | 3,768 |
| P0 + V (×matColour incl. alpha) | 476 | 654 |
| P0 + S (specular) | 228 | 396 |
| P0 + V + S | 32 | 32 |
| P7 (alpha mask) | 377 (+16 with V, +14 haze CB) | 407 |
| P1 (ras only) | 313 (+275 with V incl. alpha, +42 with V) | 711 |
| P1 + V + S | 3 | 3 |
| map terrain fn_80141650 | 137 | 137 |
| type-1 water / haze callbacks (generic shown, replaced) | 23 + 57 + 6 + 17 | |
| type-2 callbacks on P0 (kbground 654, map_trans 107, eyema 173, title, waveB, map_move) | ~950 | |

Channels: lit REG 6,549; lit VTX 7,435; lit VTX+vertex alpha 885; unlit REG 6,016;
unlit VTX+alpha 1,052; unlit VTX 124; specular 264.

States (variant counts):

| List | Blend | Z | Alpha test | Variants |
|---|---|---|---|---|
| 1 | none | LEQUAL write | – | 8,560 (cull BACK 4,718, NONE 3,818, FRONT 24) |
| 1 | none, fog off / z off / multiply / additive | | – | 28 |
| 2 | none | LEQUAL write | a > 128 | 5,148 (cull NONE 4,035, BACK 1,113) |
| 3 | additive | LEQUAL no write | a > 0 | 3,689 |
| 3 | additive | LEQUAL write (flag 0x10) | a > 0 | 31 |
| 3 | additive | **off** | a > 0 | 2,129 |
| 3 | additive | GEQUAL no write | a > 0 | 10 |
| 3 | alpha | LEQUAL no write | a > 0 | 2,189 |
| 3 | alpha | LEQUAL write (flag 0x10) | a > 0 | 300 |
| 3 | alpha | off | a > 0 | 116 |
| 3 | subtract | LEQUAL no write / off | a > 0 | 123 |
| 3 | 2× multiply | LEQUAL no write | a > 0 | 2 |

So a port needs: three TEV programs (P0, P1, P7) with optional V / S suffixes, the map terrain
and water shaders, refraction, and the blend set {opaque, cutout, alpha, additive, subtract,
multiply, 2× multiply} with z {LEQUAL write, LEQUAL read-only, GEQUAL, off}.

### 9.1 Spot checks (scratch software rasteriser driven by gmaterial.py) [V]
Rendered with per-vertex lighting, the resolved TEV and the pass state: unit `ymu/archer1`
(front and back, BACK culling correct), weapon `xwp/alondite` (list 2), tree `zbg/bg0001grd tree00`
(alpha-tested foliage a>128, vertex-colour × material stage on the trunk, `kage` shadow quad
with vertex alpha in list 3), battle background `bg0311grd` (rock/sand, kbground), terrain
`bmap0101` through the map-terrain shader (cobblestone atlas cell), effect `yme/EID_FIRE`
posed with its .ga at frame 40 and alpha forced (additive fire ring, unlit, no z write). All plausible.

## 10. Open questions

* Map terrain mask projection (map +0xE4 matrix, ortho size from map +0xD0) and what UV1 is used for in maps where it differs from UV0.
* Water / haze / kbwater callbacks are summarised, not decoded stage by stage.
* Which light set (0 or 1, object byte +0x81) lights units vs props; actual light values come from `maplight`.
* Refraction indirect matrix (fn_8001E51C) values.
* .ga material blocks: value scaling of types 6/7/0xE/0xF and 8-12 (graphics.md 5.3).
* Glow (queue 4) blur kernel and composite blend (fn_8001AC30).
* Object flag semantics (0x400, 0x800, 0x2000, 0x10000, ...) per object type.
* Descriptor bit 0x800000 (only on envelope meshes; not a vertex attribute in fn_80019AB0).
