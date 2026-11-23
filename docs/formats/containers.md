# Containers: LZ10, IS binary, pack, misc tables

All multi-byte integers on the disc are **big-endian** unless stated otherwise
(the only little-endian field is the LZ10 size). Strings are ASCII or
Shift-JIS; English text is plain ASCII inside Shift-JIS.

Readers: `tools/formats/lz10.py`, `isbin.py`, `pack.py`, plus the misc readers
mentioned below. All are Python 3.9, stdlib only, and work as CLI and library.

## Disc inventory (RFEE01 Rev 1, `files/`)

Survey of every file by extension and leading magic (after LZ10 where it applies):

| Count | Kind | Where |
|---|---|---|
| 1686 | `.cmp` = LZ10 + `pack` archive | `zmap/*/map.cmp`, `ymu/*/pack.cmp`, `xwp/`, `yme/`, `sky/`, `zbg/`, `zu/` |
| 758 | `.pak` = uncompressed `pack` | `zmap/*/map.pak`, `zu/*/*.pak` |
| 1075 | `.cms` = LZ10 + TPL | `Face/`, `illust/`, `intro/`, `gmap/tpl/`, `window/` |
| 874 + 467 | TPL (`00 20 AF 30`) | `*.tpl`; `s/xxx` (no extension, hashed names) |
| 7 | `.cms` = LZ10 + IS binary | `FE10Data`, `FE10Anim`, `FE10Battle`, `FE10Conversation`, `FE10Effect`, `FE10Growth`, `Cp/cp_data`, `Sound/sound_data*` |
| 239 | `.bin` = IS binary | `zmap/*/dispos_*.bin`, `Shop/`, `Tutorial/`, `gmap/rect/`, `window/Rect*`, `s/rect.bin`, `dictionary*.bin`, `FE8Data.bin`, ... |
| 214 | `.m` = IS binary (messages) | `Mess/` |
| 50 | `.cmb` event scripts (`cmb\0`) | `Scripts/` |
| ~4970 | `.ga` animations, `.g`/`.gs` models | `ymu/`, `xcam/`, inside packs |
| 10 + 2 | LZ10 bitmap fonts | `Fonts/` |
| 1186 / 2 | `.brstm` streams / `.brsar` sound archive (NW4R, see [sound.md](sound.md)) | `Sound/` |
| 20 | `.thp` movies (standard Nintendo THP: MJPEG + ADPCM) | `Movie/` |
| misc | `system/HomeButton/*` (Nintendo HOME menu, U8 `.arc`), `opening.bnr`, `client.bin` (GBA-style ROM header, unused leftover), `zzzzzzzz.zzz` (padding) | |

Sound (BRSAR/BRSTM/BRWSD) and THP are standard Nintendo SDK formats with
existing open-source decoders (e.g. vgmstream, ffmpeg for THP) and are not
re-documented here. `Sound/sound_data*.cms` is the game's own IS table that maps
game sound labels (`BGM_*`, `SND_GROUP_*`, voice labels) to BRSAR entries.

## LZ10 (`.cms`, `.cmp`)

Nintendo "LZ77 type 0x10" — the same scheme as the GBA/DS BIOS. Every
`.cms`/`.cmp` on the disc (2796 files) uses it; there is no LZ11/Huffman.

```
0x00 u8   0x10
0x01 u24  decompressed size, LITTLE-endian (if 0: u32 LE size follows; unused)
0x04      groups: 1 flag byte (MSB first), then 8 tokens
          flag bit 0: copy 1 literal byte
          flag bit 1: 2 bytes b0 b1: len = (b0 >> 4) + 3,
                      disp = ((b0 & 0xF) << 8 | b1) + 1, copy from out[-disp]
```

Extension convention: `.cms` usually wraps a single file (TPL or IS binary),
`.cmp` wraps a `pack` archive. The game picks the loader by the format strings
in main.dol (`%s%s/pack.cmp`, `face/minipack.cms`, ...). Confidence: verified
(round-trips all 2796 files).

## IS binary container

Intelligent Systems' relocatable data blob, used since FE9. It is a flat data
region plus a relocation table and a symbol table, essentially a tiny linker
object. Reader: `isbin.py`.

```
0x00 u32 file_size
0x04 u32 data_size            data = file[0x20 : 0x20 + data_size]
0x08 u32 pointer_count
0x0C u32 label_count          symbol table A (named tables / labels)
0x10 u32 label2_count         symbol table B; 0 except in 56 particle .gs files
0x14 u8[12] zero              (runtime writes a magic into 0x18..0x1E)
0x20 data[data_size]
     u32 pointer_offsets[pointer_count]   data-relative offsets of u32 fields
                                          that contain data-relative pointers
     {u32 data_offset, u32 name_offset}[label_count + label2_count]
     char names[]                          name_offset is relative to here
```

* At load time the game adds the data's base address to every field listed in
  the pointer table, then finds tables by label name (e.g. `PersonData`,
  `MESS_*`, `RID_*`). A pointer field with value 0 that is *not* in the table
  is a null pointer.
* The model loader fn_80075874 treats table A as imports (resolved by name,
  fn_80076D48) and B as exports; plain data files only use A, and the game
  looks tables up by name there. See [graphics.md](graphics.md).
* Labels are Shift-JIS (many are Japanese, e.g.
  `CONV_INFO_DATA_C0105_クルト`).
* Files with `label_count = 0` (`dictionary.bin`, `conversationroom.bin`,
  `soundroom.bin`, `Face/facedata.bin`) are addressed from data offset 0.
* Porting note: a native loader can keep the blob as-is and relocate pointers
  (64-bit hosts must widen them or translate to offsets), or convert each table
  to native structs once at build time with the Python readers.

Confidence: verified for all 239 `.bin`, 214 `.m` and 7 `.cms` instances
(sizes and tables add up exactly).

### Known IS files and their labels

| File | Labels / contents | Documented in |
|---|---|---|
| `FE10Data.cms` | `PersonData`, `JobData`, `ItemData`, `SkillData`, `ChapterData`, `TerrainData`, supports, ... | [fe10data.md](fe10data.md) |
| `FE10Growth.cms` | `FE10PersonGrowth` | [fe10data.md](fe10data.md) |
| `FE10Anim.cms` | `FE10AnimHeader`, `FE10AnimData`, `FE10AnimMotion`, `FE10AnimWeapon` (map/battle animation tables) | label list only |
| `FE10Battle.cms` | `FE10BUnit`, `FE10BWeapon`, `FE10BMotion`, `FE10BCam*`, `FE10BSFX*`, `FE10BMapData`, `FE10BTex`, ... (battle scene setup) | label list only |
| `FE10Effect.cms` | `EffectData`, `EIDTable` | label list only |
| `FE10Conversation.cms` | `CONV_INFO_DATA*` (base conversations), `CONVERSATION_*_YELL_DATA` | [maps_events.md](maps_events.md) |
| `FE8Data.bin` | `PersonData8`, `JobData8`, `ItemData8`, `ChapterData8`, ... — a second, smaller database with the same table names suffixed `8` (likely the Part 4 / endgame or transfer data set; unverified) | same layout family as FE10Data |
| `Cp/cp_data.cms` | AI ("CP" = computer player): `CP_ATKSEQ_LIST`, `CP_MOVSEQ_LIST`, `CP_HEALSEQ_LIST`, `MTYPE_*` | label list only |
| `Sound/sound_data_*.cms` | 3548 labels: `BGM_*`, `SND_GROUP_*`, voices; groups list `SND_GROUP_x`/`GROUP_x` name pairs | [sound.md](sound.md) |
| `Mess/*.m` | one label per message | [text.md](text.md) |
| `zmap/*/dispos_*.bin` | unit placement | [maps_events.md](maps_events.md) |
| `s/rect.bin`, `window/Rect*.bin` | `RID_*` image resources | below |
| `Face/facedata.bin` | portrait table | below |
| `Tutorial/tut_data_*.bin` | `TutDataHead`, `TUT_CHAPTER`, `TUT_CATEGORY`, `TUT_INITIAL`, `TUT_DATA` | label list only |
| `StaffRollData.bin` | `LBL_STAFFROLL_*` (credits timing, lyric) | label list only |
| `FE10Epilogue.bin`, `FE10Intro.bin`, `Movie/caption_data.bin` | `EPILOGUE_DATA`, `FE10Intro`, `CAPTION_DATA` | label list only |
| `Shop/shopitem_{n,h,m}.bin` | shop inventories per difficulty | [fe10data.md](fe10data.md) if covered |

## `pack` archive (`.cmp` after LZ10, `.pak` raw)

Reader: `pack.py` (`pack.py FILE [OUTDIR]` lists / extracts).

```
0x00 char[4] "pack"
0x04 u16     file_count
0x06 u16     0
0x08 entry[file_count], 16 bytes:
       u32 0            runtime slot (the game writes a pointer here)
       u32 name_offset  absolute; NUL-terminated ASCII
       u32 data_offset  absolute; 32-byte aligned
       u32 size
     names, then data
```

Typical contents: a map pack (`zmap/bmap0109/map.cmp`) holds `bmap0109.g`,
`bmap0109.gs`, prop models (`tree_day01.g/.gs`, `reed01.g/.ga/.gs`),
`texpack.tpl` and `map.bin`; a unit pack (`ymu/<unit>/pack.cmp`) holds
`body.gs`, `skeleton.g`, `<unit>.tpl` and the idle/move `.ga` motions (the rest
of the motions are loose `ymu/<unit>/<motion>_<n>.ga` files). Confidence:
verified on all 2444 pack files.

## TPL (`.tpl`, `s/*`, LZ10-wrapped `.cms`)

Standard Nintendo/Dolphin TPL (magic `00 20 AF 30`); see
[graphics.md](graphics.md).

## `s/` directory and `s/rect.bin` (conversation backgrounds and CGs)

`s/` contains 467 TPL images with obfuscated 3-character names (`s/9s0`,
`s/1w8`, ...). They are never referenced by name from code; instead
`s/rect.bin` (IS binary, 471 labels) maps resource IDs to them:

* Labels are `RID_<Japanese description>`, e.g. `RID_クリミア-宮廷-玉座`
  ("Crimea – palace – throne room") or `RID_472-涙のミカヤ02` (numbered event
  CG).
* The message command `\x04R<name>|` / `\x04B<name>|` builds `"RID_" + name`
  and looks it up here (fn_8014A5A8 / fn_8014A63C, string `RID_` at
  0x804CA790; fallback `RID_ダミー`).

Record layout (partly guessed):

```
+0x00 ptr   name (the label string itself)
+0x04 u8    layer_count (1 or 3)       +0x05 u8 ?   +0x06 u16 0x0384 (900)
+0x08 f32   1.0 (scale)
+0x0C u16   ? (varies per image)        +0x0E u16 0x0081
+0x10 u32   0
+0x14 ptr[layer_count]  -> layer records (0x24 bytes each)
layer: +0x00 u8 1, +0x04 u32 0, +0x08 ptr TPL path ("s/9s0"), +0x0C u32 0,
       +0x10 u8 alpha?/flags (01 00 00 FF or 01 6D 00 FF),
       +0x20 u16, u16  (e.g. 0x0260, 0x0128: size or position; unverified)
```

`window/RectBase_en.bin` etc. use the same RID record type for UI panels.

## `Face/facedata.bin` (portrait table)

IS binary without labels:

```
0x00 u32 count (316)
0x04 ptr records
record (0x30 bytes):
  +0x00 ptr FID     ("FID_NOYCE")          message/face ID used by \x05FL
  +0x04 ptr FID_L   ("FID_L_NOYCE")        large / alternate variant
  +0x08 ptr MPID    ("MPID_NOYCE")         name message ID
  +0x0C ptr file    ("NOYCE.cms")          LZ10 TPL in Face/ (or Face/wide/)
  +0x10 s16[6]      3 (x, y) anchor points in the portrait (eyes / mouth
                    overlay positions; -1 = none)       guessed
  +0x1C s16[8]      layout parameters (overlay size, crop, offsets)  guessed
  +0x2C u16 index, u16 0
```

`Face/wide/` holds 16:9 variants with the same names, and `face/minipack.cms`
the small map-UI portraits. Each `Face/*.cms` is an LZ10 TPL with several
images (full portrait plus eye/mouth animation frames).

## Other single-purpose `.bin`

`dictionary.bin` / `dictionaryF.bin` (glossary entries), `conversationroom.bin`
and `soundroom.bin` (extras menus) are label-less IS tables of pointer-rich
records; dump them with `isbin.py` and inspect. Not yet decoded.
