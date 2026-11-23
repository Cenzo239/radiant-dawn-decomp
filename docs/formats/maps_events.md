# Chapter maps and events (FE10 / RFEE01 Rev1)

Covers the battle map grid (`zmap/*/map.cmp` → `map.bin`), unit placement
(`zmap/*/dispos_{n,h,c}.bin`), and the event script VM (`Scripts/*.cmb`).
It also gives short notes on `gmap/rect`, `gmap/curve` and `FE10Conversation.cms`.

Tools (Python 3.9, stdlib only, in `tools/formats/`):

| tool | input | output |
|---|---|---|
| `mapdata.py` | `zmap/<map>` dir, `map.cmp`/`.pak`, `zbg/*/bf.*`, or raw `map.bin` | ASCII terrain grid (`--terrain FE10Data.cms` resolves ids), `--props`, `--env`, `--json`, `--obj OUTDIR [--tex]` |
| `dispos.py` | `dispos_*.bin` | groups and units as text or `--json` |
| `cmb.py` | `Scripts/*.cmb` | pseudo-C listing (default), `--asm`, `--strings`, `--json` |

Each tool can also be used as a library: `mapdata.open_file()` returns a `MapData` with `.to_dict()`, `dispos.parse()` returns a dict, and `cmb.open_file()` returns a `Script` with `.functions`, `.decode()`, `.pseudo()` and `.to_dict()`.

Confidence tags: **[V]** verified against code or data across all files,
**[C]** read from the Ghidra code but not fully exercised, **[G]** a guess.

All `fn_*`/`lbl_*` names refer to `fe10-decomp/build/ghidra_c`.

---

## 1. Map ids ↔ chapters

`ChapterData` in FE10Data.cms (entries of 0xB4 bytes) links each chapter id
(CID) to its map and script, for example `C0101 / MCT0101 / bmap0101 / C0101`.
The scripts are `Scripts/<CID>.cmb`, loaded by `fn_80092A00` through
`"Scripts/%s.cmb"`. **[V]**

| map dir | chapter |
|---|---|
| bmap0101 … bmap0111 | Part 1: 1-P, 1-1 … 1-9, 1-E (bmap01NN = chapter NN-1, last one = Endgame) |
| bmap0201 … bmap0205 | Part 2: 2-P, 2-1, 2-2, 2-3, 2-E |
| bmap0301 … bmap0315 | Part 3: 3-P, 3-1 … 3-13, 3-E |
| bmap0401 … bmap0406 | Part 4: 4-P, 4-1 … 4-5 |
| bmap0407a … e | 4-E-1 … 4-E-5 (scripts C0407a…e) |
| lmap01 … lmap12 | maps of the sub-chapters C0401a/b, C0402a/b, C0403a/b, C0404a/b, C0405a/b, C0406a/b (ChapterData). They have no dispos files. **[G]** they are the side maps of the Part 4 multi-army chapters |
| emapXXXXy | event-only stages for cutscenes (only `dispos_c.bin`) |
| tutorial01…04 | tutorial maps (scripts T01…T04.cmb) |
| bmap0000 / C0000 | trial or debug chapter (CID C0000) |
| always | `dispos_c.bin` with globally used units, read by fn_80044000 |
| test*, debug | development leftovers |

Data checks:
- bmap0101 = 1-P **[V]**. Micaiah (Light Mage) and Edward (`PID_EDDIE`, JID_BLADE) are in `mikata`. Leonardo joins in group `z01`. The boss is `PID_PUGO`, with Goon bandits.
- bmap0102 = 1-1 **[V]**. Nolan (`PID_NOYCE`, Fighter Lv7) joins. The boss is Isaiya (Myrmidon, wind affinity).
- bmap0201 is Elincia and Marcia against Zeffren. bmap0407e is Ike, Micaiah and Tibarn against `PID_ASTARTE`.

---

## 2. Map grid and scenery: `map.bin`

`map.bin` lives inside an LZ10 `pack` archive: `zmap/<map>/map.cmp` (one map,
`emap0201a`, ships an uncompressed `map.pak`). Battle backgrounds
`zbg/<bg>/bf.cmp|.pak` use the **same** format; 6 zbg test files use an older
layout (`mapbuilddescB`, `mapbuildinstB`, `mapcapacityB`, `mapextraB`, `mapfogB`, `maplightB`)
that is not decoded. The pack also holds the prop models `<name>.g/.gs[/.ga]` and one
shared `texpack.tpl` (see graphics.md). `map.bin` is an **IS binary container** with
labels `<map>:<section>`. **[V]**

Loader (80138000.c ~l.1170): `fn_8010DB48` (dispos preload) → `fn_80136164` mapdata →
`fn_80136348` maplight → `fn_8013677C` mapfog → `fn_801369BC` mapshader →
`fn_801C9FC4` ×N mapdesc → `fn_8013608C` / `fn_801CBA60` ×N mapinst → `fn_801379F8`
(panels `fn_80137BC8`, roof `fn_80138000`, links `fn_80136C34`). The zmap path sets
`k = map+0xD0 = 0.2` (`lbl_804CDEC0`); the zbg path sets `k = 3.0` (`lbl_804CDEC4`). **[V]**

Tools: `mapdata.py` (ASCII grid), `--props` (descriptors and placed instances
with matrices), `--env` (light, fog, shader, links), `--json` (everything),
`--obj OUTDIR [--tex]` (one OBJ scene with panel surface and every prop placed through
gmodel.py, map space).

### 2.0 Coordinate systems **[V]**

| frame | definition |
|---|---|
| model units | what `.gs` vertices use. **1 tile = 5 model units** (`lbl_804CDE7C` = `lbl_804CF72C` = 5.0). House models are e.g. 15×10 for a 3×2 footprint |
| map space | engine units before the root matrix: X = tile column, Z = tile row, **Y = up**. Model → map scale is `k` (0.2), so 1 tile = `U = 5k` = 1.0 on battle maps |
| panel height | s16 `h`; `y = -h / 2000 · U`. **Negative h = up.** The divisor is header f32 @0x08 (always 2000.0; runtime keeps `1/2000` at `lbl_803EC898+0x1D424`) |
| engine world | `E4 · map space`, with `E4` (map+0xE4, built at 80138000.c l.2108) = `R0 · [S(-1,1,1) if map+0xCC] · Ry(map+0xE0 deg) · T(map+0xD4..DC)`. `R0 = Rx(+3π/2)` (`lbl_804CDEE0`) for battle maps (map+0xB1 == 0), identity for backgrounds. Translation, rotation and mirror are 0 by default |

Checks:
- Placed prop heights equal the panel ground under them: 82% exactly and 95% within
  0.5 tile, out of 7232 single-tile props on 128 maps.
- The big ground model (e.g. `bmap0101.gs`, 400×360 model units) is placed at tile
  (−23, −19), i.e. `-bg_origin`. Its surface matches −h/400 at the tile centres.
- The placed bbox centre of 98% of 15230 props falls inside its `rect`.
  The remainder are fences that sit on tile edges.

### 2.1 `mapdata` header (fn_80136164)

| off | type | meaning | conf |
|---|---|---|---|
| 0x00 | u8 | version: 4 (241 files), 3 (lmap06/09/10/11 + 4 zbg), 2 (test_taisen*, 1 zbg). Header is 0x20 / 0x24 / 0x28 bytes | V |
| 0x01 | u8 | skipped | V |
| 0x02 | u8 | width (tiles), → map+0x4C | V |
| 0x03 | u8 | height (tiles), → map+0x4D | V |
| 0x04 | u16 | mapdesc count | V |
| 0x06 | u16 | mapinst count | V |
| 0x08 | f32 | height divisor (2000.0). Runtime: map+0xC4 = 1/value | V |
| 0x0C | s8,s8 | `bg_origin` → map+0xAB/AC. Equals −(x,y) of the big ground instance in 94/128 maps. Used as `(64 − v)·5k` in the shadow projection (`fn_80141650`) | C |
| 0x0E | s8,s8 | `shadow_center` → map+0xAD/AE, about (w/2, h/2) | C |
| 0x10 | u8 | `shadow_size` → map+0xAF (32 or 64); half of it is the ortho extent (`fn_80141DCC`) | C |
| 0x11 | u8 | → map+0xB0, 0..20, unknown | – |
| 0x12 | u8 | `fow_fill` → `lbl_804CA734`: fill byte of the fog/shadow tile texture (`fn_80144xxx` l.2871) | C |
| 0x13 | u8 | skipped | V |
| 0x14 | u32 | flags, see below | C |
| 0x18 | u8 | grid overlay alpha (→ map+0xBB; replaced at draw time by the option value, fn_80134000.c l.2307) | G |
| 0x19 | u8[3] | grid overlay RGB (→ map+0xB8..BA): white or black | G |
| 0x1C | u8 | scroll enable (`lbl_804CB84C`). Only bmap0201 (2-P, the sea flight) sets it. Tile lookups then wrap (80118000.c) | V |
| 0x1D | s8,s8 | scroll step x,y (`lbl_804CB84F/50`; bmap0201: −1, 0) | C |
| 0x1F | u8 | scroll period (`lbl_804CB851`, 64) | C |
| 0x20 | ptr | (v≥3) affinity/effect name → `fn_801194FC` → map+0x4E (`invalid`, `fire`, `thunder`, `wind`, `water`, …) | C |
| 0x24 | f32 | (v≥4) `depth_clamp` → map+0xC8 = grid+0x1D428. Tile heights (+down) are clamped to it in `fn_8011843C` (10.0 typical) | C |

Flags @0x14:

| bits | meaning | conf |
|---|---|---|
| 0x10000000 | roof layer active. Set in exactly the 33 maps that have `roofpanel`/`roofindex` and roof props | V |
| 0x40000000 | props drawn in 3 extra passes (`fn_80134ECC`) | C |
| 0x000C0000 | `lbl_804CB830`: 0x80000 → 1, 0xC0000 → 2, 0x40000 → 3. Value 1 appears on the night maps 2-2, 3-P, 3-1, 3-6, 4-1 and is excluded by several systems (`!= 1 && != 2`), so it is probably fog of war. Value 3 builds a darkened tile texture with `fow_fill` | G |
| 0x01F00000 | `lbl_804CB834` enum (0..0x15, `fn_8013A35C`), copied into the battle struct +0x15FC (battle background set?) | G |
| 0x20000000, low bits 0x01..0x80 | set on almost all maps, meaning unknown | – |

### 2.2 Terrain panels: `uniquepanel` + `panelindex` **[V]**

- `panelindex`: one u16 per tile (`width*height`, padded to 4 bytes), indexing `uniquepanel`.
- `uniquepanel` entries are 0x0C bytes: s16 h[4] corner heights, ptr terrain name.
  - Corner order (from the edge vectors in `fn_80137BC8` and the quad order 0,1,3,2 in `fn_80136E74`):
    0 = (x0,z0), 1 = (x1,z0), 2 = (x0,z1), 3 = (x1,z1). **[V]**
  - The terrain name is hashed to a TerrainData id (`fn_8011D17C` / `fn_8011D1E4`), as before. The result goes to `DAT_803ed8a5[y*64+x]`.
- Runtime: `fn_80137BC8` copies the panel corners to grid+0x15422 ("top" heights) and the
  base corners to grid+0x1D42C. It then marks planar tiles (both triangle normals
  within 0.999..1.001) in the bit set grid+0x2542C. Planar tiles are interpolated as one plane,
  other tiles as two triangles (`fn_801142F0`). **[C]**

### 2.3 Layers: main / base / roof

- **base** (`basepanel`/`baseindex`, all maps): corner heights only (terrain still comes
  from `uniquepanel`). This is the ground used for units, cursor and tile overlays: `fn_80114728`,
  `fn_801146A8`, `fn_80136E74`. Where a house stands, `uniquepanel` gives the roof top
  (e.g. −12199 = 6.1 tiles) and base gives the street level (−6000 = 3.0). Without a base
  layer, both arrays come from `uniquepanel`. **[V]** (prop heights match base)
- **roof** (`roofpanel`/`roofindex`, 33 maps): if header flag 0x10000000 is set,
  `fn_801379F8` walks every prop whose descriptor is a roof object (`fn_801CA1E8`:
  desc flag 0x800 or 0x1000, not 0x10) and that is still present (instance
  state bits 0x0C clear, `fn_801CA260`). For those props it calls `fn_80138000(map, rect clamped to the map, desc&2)`,
  which overwrites terrain and "top" heights in the rect with roof panels. With desc flag 2 it also overwrites the base heights.
  When the object is removed (bits 0x0C set, e.g. a broken wall), the tiles revert to the main layer. **[C]**

### 2.4 `mapdesc`: model descriptors (0x24 bytes, fn_801C9FC4 → 0xC0 runtime)

| off | type | meaning | conf |
|---|---|---|---|
| 0x00 | f32[6] | model-space bbox min xyz, max xyz (equals the .gs vertex bounds). Runtime +0xA0; used for culling (`fn_801CCA38`) | V |
| 0x18 | u32 | flags (runtime +0xB8), see below | C |
| 0x1C | ptr | model name. Loads `<name>.g` (`fn_8000EB68`), `<name>.gs` (`fn_80017F10`), `texpack.tpl`, and `<name>.ga` if flag 0x200 | V |
| 0x20 | u8,u8 | footprint w (x) and d (z) in tiles (runtime +0xBC/BD). Pivot for scaling and mirroring | V |
| 0x22 | u16 | skipped | V |

Descriptor flags. Draw-pass ids go to `fn_80008F54`; their materials are documented in materials.md.

| bit | meaning | conf |
|---|---|---|
| 0x2 | roof also rewrites base heights | C |
| 0x10 | pass 0x80; never a roof | C |
| 0x20 / 0x40 / 0x80 | passes 0x95 / 0x8C / 0x8B. 0x40 also sets object flags 0x30000 and enables ground snapping (`fn_8012FCD0`) | C |
| 0x200 | animated, `.ga` loaded | V |
| 0x800 / 0x1000 | roof object (0x800 also pass 0x94) | C |
| 0x2000 | translucent (pass 0x93 when a material named `map_trans` exists) | C |
| 0x4000 | animation loop end from node info 0x37 | C |
| 0x20000 | pass 0x8A. With 0x40000000 the instance gets flag 4 (not drawn) | C |
| 0x40000 | hidden while a unit stands on or next to the rect | C |
| 0x800000 | random animation start frame | C |
| 0x1000000 | door-like open animation (`fn_801CA688`, 8013C000 l.192) | G |
| 0x4000000 | sand pass on backgrounds | C |
| 0x8000000 | culling bbox min.y lerped by mapshader+0x58 | C |
| 0x10000000 | y scale = `fn_8001ECE4(0,1,1,s,2)` instead of s (curve not decoded; mapdata.py uses s) | C |
| 0x100, 0x1, 0x100000 | common, meaning unknown | – |

### 2.5 `mapinst`: placed props (0x14 bytes, fn_801CBA60 → 0xD0 runtime)

| off | type | meaning | conf |
|---|---|---|---|
| 0x00 | u8 | flags. Bit 0 = mirror X (150 props) | C |
| 0x01 | s8,s8 | tile x, y (map grid frame; may be negative or outside the map) | V |
| 0x03 | u8 | rotation: `deg = 360 − (rot·360 >> 8)`, stored as s16 1/64 deg at +0x0A | V |
| 0x04 | s8,s8 | sub-tile offset x, z in 1/64 tile (multiples of 8, ±32) | C |
| 0x06 | u16 | mapdesc index | V |
| 0x08 | s8[4] | rect x0, y0, x1, y1 (tiles). Used for roofs, hide-near-units and blocking (`fn_8013818C`) | V |
| 0x0C | f32 | height in tiles, **negative = up** (equals −ground) | V |
| 0x10 | u8 | uniform scale × 64 (64 = 1.0; 40..112 seen) | C |
| 0x11 | u8[3] | skipped (always 0) | V |

Instance matrix (`fn_801CC5CC`, animation offsets 0), map space, column vectors.
`U = 5k`, `h = U/2`, `w,d = footprint·h`:

```
M = T(px·U, −height·U, pz·U)                     px = x + sub.x/64, pz = y + sub.z/64
  · T(h,0,h) · Ry(deg) · T(−h,0,−h)               rotate about the tile centre
  · [T(fw·U,0,0) · S(−1,1,1)]                     if flags & 1
  · [T(w,0,d) · S(s,sy,s) · T(−w,0,−d)]           if scale ≠ 1, about the footprint centre
  · S(k)                                          model → map units
world = E4 · M
```

`Ry` is PSMTXRotRad 'Y' (`[c 0 s; 0 1 0; −s 0 c]`). `mapdata.py` stores this matrix in `inst["matrix"]`.
Missing asset: bmap0312, zbg/bmap0312 and zbg/bmap0314 reference `ｌid_day01`
(full-width ｌ), which is not in the pack, so the prop is not drawn in the game either.

### 2.6 `maplight` (32 bytes, fn_80136348 / fn_801364AC) **[C]**, data **[V]**

| off | type | meaning |
|---|---|---|
| 0x00 | u8[2] | skipped (0) |
| 0x02 | s16[3] | light rotation a, b, c in **degrees** (`lbl_804CB840..44`). Not a vector |
| 0x08 | 4 × {u8 ambient RGB, u8 light RGB} | colour sets 0..3 (`lbl_80413BF8[i]` ambient, `lbl_80413BE8[i]` light). Scripts can change them (800DC000.c l.84) |

`fn_801364AC` fills the light environment ("GCamera.c" light sets at
`lbl_803B6710`, 9 × 0x128 bytes; `fn_80010BB0(i)`):
- Light set 0: ambient = set 0 ambient, plus one type-1 light (directional) with colour = set 0 light and angles (a,b,c).
- Light set 1: the same with colour set 1. Light set 2 is a copy of set 1.
- Light set 3: ambient only (`lbl_804CDE88`, white).
- Colour sets 2 and 3 are unused at load time.

Which models use set 0 versus set 1 (map versus units?) is still open.

Direction (`fn_800110F4`): `dir = Rz(c)·Ry(b)·Rx(a)·(0,0,−1)` in map space, then through
the view and E4. All 252 files give a unit vector; 251 point down (indoor bg0103rom points up).
bmap0101: (−30, −150, −40)° → (0.010, −0.661, 0.750).

GX upload in `fn_80011280` (per light slot 0..7, `GXLoadLightObjImm(1<<i)`):
- type 1/2 directional: `GXInitLightPos(dir·−10000)` in view space, `GXInitLightDistAttn(0,0,GX_DA_OFF)`, `GXInitLightSpot(0,GX_SP_OFF)`.
- type 3/4 specular: `GXInitSpecularDir`, `GXInitLightAttn`.
- types 5/7 point and 6 spot: `GXInitLightPos`, `GXInitLightDistAttn(ref, 0.5, GX_DA_STEEP)`, `GXInitLightSpot(30)`.
- Every type also calls `GXInitLightColor`, with colour scaled by an optional percentage byte.

### 2.7 `mapfog` (12 bytes, fn_8013677C / fn_801368DC / fn_800109B8) **[C]**, data **[V]**

| off | type | meaning |
|---|---|---|
| 0x00 | u8 | skipped |
| 0x01 | u8 | enable |
| 0x02 | u8 | type − 1. Engine type = `enable ? t+1 : 0` (`lbl_804CB839`) |
| 0x03 | u8 | start |
| 0x04 | u8 | end. Distances = value · 5k (map units = tiles on battle maps; ×15 on backgrounds) |
| 0x05 | u8[3] | RGB |
| 0x08 | u8[4] | unused |

`GXSetFog(table[type], start, end, cam_near, cam_far, rgb+alpha)` with the type
table `{0, GX_FOG_PERSP_LIN, PERSP_EXP, PERSP_EXP2, PERSP_REVEXP, PERSP_REVEXP2}`.
After it come `GXInitFogAdjTable(width 608)` and `GXSetFogRangeAdj(1, 304)`. The fog colour is also
copied to `lbl_804CB0B4` (`fn_80021754`, clear colour).
Sweep: 205 files have fog enabled, all with start < end. Battle maps typically use 30..85 tiles.

### 2.8 `mapshader` (fn_801369BC) **[C]**

| off | type | → map+ | meaning |
|---|---|---|---|
| 0x00 | u8 | – | version (0: 11 files, 1: 121, 2: 120) |
| 0x01 | u8[4] | 0x54..57 | 0x56 enables the bbox lerp of desc flag 0x8000000. The others are unknown |
| 0x05 | u8 | 0x58 | value/100, lerp factor |
| 0x06 | s16 | 0x5C | value/100 |
| 0x08 | u8, u8 | 0x64, 0x65 | |
| 0x0A | u8[4] | 0x66..69 | RGBA (usually ffffffff) |
| 0x0E | u8[4] | 0x60..63 | (v≥1) |
| 0x12 | u8 desc+1, u8, u8, u8[3] | – | (v≥2) material override on model `desc` (0 = none): material+0x25, +0x28, +0x2B..2D (+0x2E = `lbl_804CDE8F`) |

The rest of the section is the container's string pool (model names and so on). The consumers of
+0x54..0x69 are not traced yet (they go through `fn_8013B9A8()` = the current map). **[–]**

### 2.9 `maplink` / `maplinkAt` / `maplinkAbs` (fn_80136C34) **[C]**

Each is: u8[2] skipped, u16 count, count × {s8 x, s8 y, u8 v}. They write the per-tile
link word `DAT_803f1926[y*64+x]`:
- `maplink` sets the low byte = v.
- `maplinkAt` sets bits 8..11 = v.
- `maplinkAbs` sets `v + (~v & 0xF)·16`.

The bits are neighbour connections, read by `fn_800392FC` / `fn_800394E0`:
1 = −x, 2 = +x, 4 = +y, 8 = −y. The `At` copy is tested together (0x101 …).
24 maps use maplink, 19 use maplinkAt, none use maplinkAbs. They probably mark walls and cliffs between tiles. **[G]**

### 2.10 Sweep

`mapdata.py` parses 252 of 258 files: all 128 zmap `map.cmp`, `emap0201a/map.pak`,
and 123 zbg `bf.cmp/.pak`. The 6 failures are the old-layout zbg test files.
`--obj` was spot-checked on bmap0101, bmap0404, emap0102a and lmap01 (≤1 s each, rest pose).

## 3. Unit placement: `dispos_{n,h,c}.bin`

`dispos.py`. These are IS binary containers, LZ10-optional. Path built by `fn_8010DD58` /
`fn_8010DE10`: `zmap/<map>/dispos_<x>.bin`.

### 3.1 Which file **[C]**

The selector is the byte at `fn_80060728(lbl_803CAB38)+0x11` (save/game settings,
probably difficulty):

| value | file | label suffix |
|---|---|---|
| 0 | dispos_n | `_n` |
| 1, 2 | dispos_h | `_h` |
| 3 | dispos_n | `_n` |
| 4 | dispos_c | `_c` |
| other | dispos.cmp | (none on disc) |

The data supports this reading:
- **c** = *common*. It holds the cutscene and event groups (`ev00`, `op01`, `ed00`, `first`, `C0101…`), shared by all
  difficulties. Event-only maps (emap*, always, tutorial*) have only `_c`. **[V]**
- **n** = normal and **h** = hard. Most maps have both, with fewer or weaker enemies in n
  (1-P: 4 enemies in n, 8 in h). **[V]**

The mapping to the US menu names Easy, Normal and Hard is unproven. The settings byte
0/1/2/3 sends JP "Normal" (US Easy?) to n, and the two harder settings both to h. **[G]**
US Hard therefore seems to share placements with Normal, with the difference coming from code (stat bonuses). This should be checked at runtime.

### 3.2 Layout **[C]** (loader fn_8010BED8, unit reader fn_8010BCBC)

Labels: `<map>_date_<x>` holds a pointer to a build-date string. Every other label is a group,
named `<map>_mikata_<x>` (player), `_teki_` (enemy), `_midori_` (green/ally),
`_ki_` (yellow/other), `_zNN_` (reinforcement or joining units), `_evNN_`, `_opNN_`, `_edNN_`, and so on.
Scripts use the name without the suffix, for example `DisposRank("bmap0101_teki")` or
`InstantDispos("bmap0101_ev00_c")`.

Group:

| off | type | meaning |
|---|---|---|
| 0 | u8 | unit count |
| 1 | u8 | record version. Always 7; the reader only handles 7 |
| 2 | u8 | gtype (0..2). The loader turns 1/2/3 into runtime flags 2/4/8 (4 = units sorted first) **[C]** |
| 3 | u8 | group param. Copied into each unit (runtime +0x0D, +0x67). Values seen: 1, 9, 10, 14, 28, 40 (40 = event groups) **[G]** |
| 4 | unit[count] | 0x68 bytes each |

Unit (0x68 bytes):

| off | type | meaning | conf |
|---|---|---|---|
| 0x00 | u16 | serial, unique in the file (c: 2000+, n: 4000+, h: 6000+) | V |
| 0x02 | u16 | flags. The loader tests 0x0008 and 0x0800. Players usually have 0x0440 or 0x184C, enemies 0x0049 | C |
| 0x04 | ptr | PID_* | V |
| 0x08 | ptr | JID_* | V |
| 0x0C | u8,u8 | start x, y | V |
| 0x0E | u8,u8 | end x, y (unit appears at start, then moves or warps to end; often equal) | V/G |
| 0x10 | u8 | level | V |
| 0x11 | u8 | army: 0 player, 1 enemy, 2 ally, 3 other. Values 5, 7, 8, 9, 10 also occur (bit flags?) | G |
| 0x12 | u8 | initial laguz gauge (0..30). Only laguz JIDs have values other than 0 | V |
| 0x13 | u8 | small id (1..50), probably the AI team or group (`SEQ_TEAMCOMMANDERMOVE`) | G |
| 0x14 | s8[8] | per-unit stat modifiers (HP Str Mag Skl Spd Lck Def Res?) | G |
| 0x1C | u8 | unknown (0..32) | – |
| 0x1D | u8 | start facing. Values are {1,2,4,8,5,6,9,10}, which looks like an 8-direction bitmask | G |
| 0x1E | u8 | end facing (same value set) | G |
| 0x1F | u8 | unused (always 0) | V |
| 0x20 | ptr | affinity name (`invalid`, `fire`, `thunder`, `wind`, …) | C |
| 0x24 | ptr[7] | items IID_* (`/D` suffix = droppable) | V |
| 0x40 | ptr[5] | skills SID_* (`SID_FIXEDBEAST`, `SID_BOSS`, …) | V |
| 0x54 | ptr[5] | AI: attack sequence, move sequence, heal sequence, movement type `MTYPE_*`, last sequence (null becomes `SEQ_SAFETYMOVE`) | C |

---

## 4. Event scripts: `Scripts/*.cmb`

`cmb.py`. Files are not compressed. **Header and table integers are little-endian.**
Bytecode operands are big-endian. Loading is done by `fn_800C3840`, which byte-swaps the header
when the platform needs it, then `fn_800C358C` (relocation, symbol registration). Scripts form a linked list
`lbl_804CB6A0`; `startup.cmb` is always loaded. **[V]**

### 4.1 Container **[V]**

| off | type | meaning |
|---|---|---|
| 0x00 | char[4] | `cmb\0` |
| 0x04 | char[20] | own file name |
| 0x18 | u32 | date as hex digits, `0x20061024` |
| 0x1C | u32 | runtime: next script |
| 0x20 | u16 | runtime: base slot of this script's static variables |
| 0x22 | u16 | number of static variables (startup.cmb has 3, chapters have 0) |
| 0x24 | u32 | string table offset (0x2C). String operands are relative to it |
| 0x28 | u32 | function table: u32 header offsets, terminated by 0 |

Function / event header (0x14 + 2n bytes, followed by code):

| off | type | meaning |
|---|---|---|
| 0x00 | u32 | name offset (0 = anonymous). Named functions go into the global symbol table (`fn_80076D48`), so they can be called by name from any script |
| 0x04 | u32 | code offset |
| 0x08 | u32 | runtime: owning script |
| 0x0C | u8 | trigger kind (0 = plain function) |
| 0x0D | s8 | argument count |
| 0x0E | s8 | trigger parameter count n |
| 0x0F | u8 | unused. Holds uninitialised compiler garbage, as do the 1–4 padding bytes after code |
| 0x10 | u16 | own index in the function table |
| 0x12 | u16 | frame size in slots (args + locals) |
| 0x14 | u16[n] | trigger parameters (integers, or string-table offsets) |

The code starts at the next 4-byte boundary and runs up to the next header.

### 4.2 Trigger kinds

The game scans all loaded functions by kind. The checks live in 8009C000.c and 800A0000.c, for example
`fn_8009EB54` (kinds 3 and 6), `fn_8009EDEC`, `fn_8009F768`, `fn_8009FC94`, `fn_8009FFE4`, `fn_800A0330`.
String parameters named "flag/cond" are looked up first as a script function; if one exists, it is
called as the condition (`fn_801D0C88`). Otherwise the parameter is treated as a flag name, and the event fires only while that flag is **not** set.

| kind | name in cmb.py | params | conf |
|---|---|---|---|
| 1 | flag_set | flag (fires when the flag is set, for example `gf_complete`) | C |
| 3 | turn | turn_min, turn_max (0 = any), phase (−1 = any; compared to `lbl_803CAB38[0x11]`, turn = `+0x12`) | C |
| 4 | area | x0, y0, x1, y1 (≤0 = measured from the far edge), army (−1 = any), flag/cond | C |
| 5 | location | x, y, command/type id, flag/cond (villages, chests, doors, escape points) | C/G |
| 6 | turn_end | same as 3, different hook | C/G |
| 7 | after_action | none. Win/lose checks run after actions | G |
| 8 | talk | pid_a, pid_b, int, flag/cond (Talk command) | C/G |
| 9 | battle_talk | pid_a, pid_b, int, flag/cond (boss quotes) | C |
| 10 | unit_retreat | pid (startup.cmb, player units) | G |
| 11 | unit_defeat | pid | C/G |
| 12 | clear_bonus | one string. Bodies call `Achieve_CLEAR_BONUS` and similar | G |
| 14 | base_conversation | title, flag/function (`拠点会話_*`) | G |
| 15 | unit_action | none. Bodies use `MindGetMe()` (tutorial hints) | G |
| 17/18/19 | – | 4/5/4 strings (C0000, C0110, C0314, C0404) | – |
| 20 | epilogue | pid, condition function (CFINAL.cmb) | G |

### 4.3 VM and opcodes **[V]**

The interpreter is `fn_801D0EC0`, a switch on the opcode byte. The VM state has:
+0x08 the current function header, +0x0C the PC, +0x14 the frame base (locals), +0x18 the stack pointer.
Global variables live at `lbl_804CB6A8` (absolute slot numbers). All values are 32-bit.
Function calls go through `fn_801D0D58`: the args become the first locals, the rest of the frame is
zeroed, and four slots of saved state are pushed. Return values are pushed to the caller.

Operands: B = u8, H = u16 BE, b = s8, I = u32 BE.

| op | mnemonic | operand | effect |
|---|---|---|---|
| 00 | nop | – | (any unknown opcode is also a no-op) |
| 01/02 | ldL | B/H n | push local[n] |
| 03/04 | ldidxL | B/H n | i=pop; push local[n+i] |
| 05/06 | ldptrL | B/H n | i=pop; push ((int*)local[n])[i] |
| 07/08 | leaL | B/H n | push &local[n] |
| 09/0A | leaidxL | B/H n | i=pop; push &local[n+i] |
| 0B/0C | leaptrL | B/H n | i=pop; push (int*)local[n]+i |
| 0D–18 | ldG … leaptrG | B/H n | same six forms on global slots |
| 19 | push | b | push sign-extended byte |
| 1A | push | H | push u16 (negative numbers are written as push + neg) |
| 1B | push | I | push u32 |
| 1C/1D/1E | pushs | b/H/I | push string_table + offset |
| 1F | deref | – | push *(top) (top is kept) |
| 20 | pop | – | discard |
| 21 | assign | – | v=pop, a=pop, *a=v, push v |
| 22–2E | add sub mul div mod neg bnot lnot or and xor shl shr | – | integer arithmetic (neg/bnot/lnot are unary) |
| 2F–34 | eq ne lt le gt ge | – | signed compare, a = second, b = top: `a OP b` |
| 35/36 | streq/strne | – | strcmp of two string pointers |
| 37 | call | B, or (B&0x7F)<<8 \| B2 when B&0x80 | call function #idx of the same script |
| 38 | callname | H str, B argc | resolve name in the global symbol table. Native builtin (entry+8 == 0) → `fn_801D20D4`, otherwise a script function. Unknown name → pop args, push 0 |
| 39 | retv | – | return pop() |
| 3A | jmp | H | pc = (address of operand) + s16 |
| 3B | jnz | H | jump if pop() ≠ 0 |
| 3C | orjmp | H | `\|\|` short-circuit: if top ≠ 0 then top=1 and jump, else pop |
| 3D | jz | H | jump if pop() == 0 |
| 3E | andjmp | H | `&&` short-circuit: if top == 0 then keep 0 and jump, else pop |
| 3F | yield | – | suspend the script (resumes later; `fn_800C3584(6)`) |
| 40 | nop4 | I | skipped |
| 41 | popn | b | drop n values. Used for compiled-out debug `printf(fmt, …)` arguments |
| 42/43 | inc/dec | – | a=pop; (*a)++ / (*a)-- |
| 44 | dup | – | push top |
| 45/46 | ret0/ret1 | – | return 0 / 1 |
| 47 | store | – | v=pop, a=pop, *a=v |

These checks pass over all 50 scripts (≈137k instructions):
- Every jump target lands on an instruction boundary.
- Every function ends in a return.
- Every `callname` argc matches the builtin registration table, except `VOICEAllStop`, `StaffRoll` and `WarRecord`, which are registered with 0 args but called with 1.

`fn_8009D958` is a separate operand-length scanner used to find strings in code.

**Builtins.** There are 656 natives, registered with `fn_800C3C3C(name, fn, argc)`. The registry is
`lbl_804CB6B0`, 16-byte entries {name, fn, 0, u8 0, u8 argc}. cmb.py embeds the table
(`cmb.BUILTINS[name] = (argc, address)`), which was extracted from the Ghidra C and main.dol.
Script-defined helpers such as `UnitCheckLive` and `DisposUnitGetByPID` live in `startup.cmb`
(586 functions) and C0000.cmb.

The pseudo-C listing comes from a symbolic stack. Arguments are named `aN`, locals `vN`, globals `GN`.
`discard(...)` marks values dropped by `popn`. The switch selector is kept in temporaries `tN`.
Control flow stays as `if (...) goto loc_XXXX`.

---

## 5. Brief: other files

- **gmap/rect/RectGmapNNNN*.bin** are IS containers. Each label `RID_GMAPNNNN<name>` has a 0x3C-byte
  record: ptr name, u32 0x01000384, …, ptr texture `gmap/tpl/gmap_NNNN.cms` (+0x20),
  then position and size data (for example `00f0 0150`). These are world-map sprite rectangles, the same
  "RID" rect format as `window/Rect*.bin` and `s/rect.bin`. **[G]**
- **gmap/curve/curveNNNN_k.bin** are raw big-endian, 0x30-byte header: u32 0, char name[0x18]
  (@4), u32 duration (frames?) @0x1C, u32 point count n @0x20, u32 ? @0x24, u32 ? @0x28,
  u32 0 @0x2C. Then n × {f32 pos[3], f32 tangent[3]} (z = 0), so file size = 0x30 + 24n.
  This is likely a world-map army movement path (Hermite spline). 20-byte files are stubs. **[V]** size rule, **[G]** meaning.
- **FE10Conversation.cms** (LZ10 + IS container): `CONV_INFO_DATA` = u32 count (101)
  followed by 0x30-byte entries {ptr CID, ptr MID title, ptr MID text, ptr FLG_ flag,
  ptr PID[7], u32 value (2/3…)}. These are base conversations, each also labelled
  `CONV_INFO_DATA_<CID>_<title>`. The file also has `CONVERSATION_FE8_YELL_DATA` and
  `CONVERSATION_MINI_YELL_DATA` (not decoded). **[C]** layout from data, no parser written.

---

## 6. Open questions

- Which US difficulty uses which dispos file. Read the settings byte +0x11 at runtime.
- Unit bytes 0x11 (high values), 0x13, 0x14..0x1B (stat modifiers?), 0x1C, and the 0x1D/0x1E facing encoding. Also group byte 3.
- map.bin: header byte 0x11 and the low flag bits; what the `lbl_804CB834` enum (flags 0x1F00000) selects; whether fow_mode 1 really is fog of war.
- map.bin: which light set (0 or 1) lights props versus units; consumers of mapshader +0x54..0x69 and the shader version-2 material override fields.
- map.bin: the `fn_8001ECE4` y-scale curve (desc flag 0x10000000), several descriptor flag bits, the exact meaning of the maplink bits, and the old 'B' layout of 6 zbg files.
- Trigger kinds 2, 13, 17, 18, 19 and the int parameter of talk/battle_talk. Exact hook points of kinds 3 vs 6 and 7 vs 15.
- Which runtime pointer is used for global variable slots (`lbl_804CB6A8`) versus the per-script static base (+0x10 of the VM state is set but not used by any opcode seen).
- The meaning of lmap01..12 for the Part 4 sub-chapters.
