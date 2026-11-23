# FE10 (Radiant Dawn, RFEE01 Rev 1) game file formats

Documentation of the data files on the disc, written so that a native port
(Mac/iOS) can load the original game data. Every format here has a reader in
`tools/formats/` (Python 3.9, standard library only, usable as CLI and as a
library). Game data is never committed; point the tools at your own extracted
disc (`orig/RFEE01/files/`).

All integers are big-endian unless noted. Function names (`fn_8xxxxxxx`) refer
to the Ghidra pseudo-C in `build/ghidra_c/` and the symbols in
`config/RFEE01/symbols.txt`. Each document marks fields as verified, read from
code, or guessed.

| Document | Covers | Readers |
|---|---|---|
| [formats/containers.md](formats/containers.md) | Disc inventory, LZ10 (`.cms`/`.cmp`), IS binary container, `pack` archive, `s/` backgrounds + `s/rect.bin`, portrait table `Face/facedata.bin`, label lists of the remaining tables | `lz10.py`, `isbin.py`, `pack.py` |
| [formats/fe10data.md](formats/fe10data.md) | `FE10Data.cms`: characters, classes, items, skills, chapters, terrain, supports, weapon triangle, groups; `FE10Growth.cms`; shop lists | `fe10data.py` |
| [formats/maps_events.md](formats/maps_events.md) | Map grid `map.bin` incl. prop placement, lights and fog, unit placement `dispos_{n,h,c}.bin`, event script VM `.cmb` (all 72 opcodes, 656 native builtins), world-map curves/rects, base conversations | `mapdata.py`, `dispos.py`, `cmb.py` |
| [formats/graphics.md](formats/graphics.md) | TPL textures (all GX formats), `.g` skeletons, `.gs` meshes, rigid and envelope (weighted, up to 4 bones) skinning, `.ga` animations; OBJ export | `tpl.py`, `gmodel.py` |
| [formats/materials.md](formats/materials.md) | Material render state: TEV per blend mode, render lists, blend/z/cull/fog, lighting channels, terrain shader; shader pseudocode and the 193 state combinations that occur | `gmaterial.py` |
| [formats/text.md](formats/text.md) | Messages `Mess/*.m` with all control codes, inline `#` formatting, bitmap fonts | `mess.py`, `font.py` |
| [formats/sound.md](formats/sound.md) | NW4R sound archive `sound_us.brsar` (RSAR/RSEQ/RBNK/RWSD), streams `strm/*.brstm`, DSP-ADPCM, game sound tables `sound_data*.cms` (label records, chapter/battle music rules, ambient sounds, numeric SE ids), `soundroom.bin` | `nwsnd.py`, `brsar.py`, `brstm.py`, `sound_data.py` |
| [formats/save.md](formats/save.md) | Save data on the Wii NAND: files, checksum, layout | `savegame.py` |

## Quick start

```bash
F=orig/RFEE01/files
python3 tools/formats/pack.py $F/zmap/bmap0101/map.cmp                # list a pack
python3 tools/formats/fe10data.py $F/FE10Data.cms --table persons     # characters as JSON lines
python3 tools/formats/mess.py $F/Mess/e_c0101.m                       # English script of 1-P
python3 tools/formats/cmb.py $F/Scripts/C0101.cmb                     # event script as pseudo-C
python3 tools/formats/dispos.py $F/zmap/bmap0101/dispos_n.bin         # unit placement
python3 tools/formats/mapdata.py $F/zmap/bmap0101 --terrain $F/FE10Data.cms
python3 tools/formats/tpl.py $F/Face/IKE.cms /tmp/ike                 # portrait to PNG
python3 tools/formats/gmodel.py obj $F/ymu/archer1/pack.cmp /tmp/archer --anim $F/ymu/archer1/atk_1.ga --frame 5
python3 tools/formats/brstm.py wav $F/Sound/strm/fe10_bgm_btl_boss1_32k.brstm /tmp/boss1.wav
python3 tools/formats/sound_data.py $F/Sound/sound_data_en.cms resolve BGM_BTL_BOSS1 --brsar $F/Sound/sound_us.brsar
```

## Not covered (standard formats)

Movies (`.thp`) and the HOME-button menu (`system/HomeButton`, U8 archives).
Open-source decoders exist for both (ffmpeg, wszst).

## Biggest open points

* Stage-by-stage TEV of the special callbacks (water, haze), the terrain mask projection, refraction
  and glow composite; which light set lights units vs props.
* `mapshader` consumers, a few map descriptor flags, 6 old-layout `zbg` test maps.
* Several unknown bytes in character/class/chapter records and unit placement
  (listed in each document), `GameData`, `BioData`.
* Which US difficulty loads `dispos_n` vs `dispos_h` (needs a runtime check).
* `FE10Anim.cms`, `FE10Battle.cms`, `FE10Effect.cms`, `Cp/cp_data.cms` (AI)
  are only listed by label.
