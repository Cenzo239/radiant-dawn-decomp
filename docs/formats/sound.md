# Sound: NW4R archive, streams and the game's sound tables

Covers `Sound/sound_us.brsar`, `Sound/strm/*.brstm`, `Sound/sound_data*.cms` and
`soundroom.bin`. FE10 uses the stock NintendoWare for Revolution sound library
(`nw4r::snd`, decompiled in `lib/ogws/src/nw4r/snd`, FE10-specific header
changes in `lib/ogws/include/nw4r/snd`, see [../LIB.md](../LIB.md)) plus a thin
game-side manager at 0x8024C000-0x80258000 that maps game labels to archive
sounds.

Readers (Python 3.9, stdlib only):

| Tool | Does |
|---|---|
| `tools/formats/nwsnd.py` | Library: common NW4R header, RSTM, RWSD, RBNK, RSEQ (+ RWAR, RWAV), DSP-ADPCM decoder, WAV writer |
| `tools/formats/brsar.py` | Archive: summary, sound/bank/player/group/file tables as JSON, extract sub-files, wave sounds to `.wav` |
| `tools/formats/brstm.py` | Streams: info, decode to `.wav` (whole file or per track), scan a directory; dump `.brwsd/.brbnk/.brseq` |
| `tools/formats/sound_data.py` | Game tables in `sound_data*.cms` (label records, chapter/battle BGM rules, env sounds, numeric SFX ids) and `soundroom.bin` |

```bash
F=orig/RFEE01/files
python3 tools/formats/brsar.py $F/Sound/sound_us.brsar summary
python3 tools/formats/brsar.py $F/Sound/sound_us.brsar sounds --type strm | head
python3 tools/formats/brsar.py $F/Sound/sound_us.brsar wav /tmp/se --sound SE1_SYS_TITLE_LOGO1
python3 tools/formats/brstm.py wav $F/Sound/strm/fe10_bgm_btl_boss1_32k.brstm /tmp/boss1.wav
python3 tools/formats/sound_data.py $F/Sound/sound_data_en.cms resolve BGM_BTL_BOSS1 --brsar $F/Sound/sound_us.brsar
python3 tools/formats/sound_data.py $F/Sound/sound_data_en.cms dump map_bgm
python3 tools/formats/sound_data.py soundroom $F/soundroom.bin
```

Confidence marks: **[v]** verified against the data (round trip, checksum-like
cross check or exhaustive consistency over all files), **[c]** read from code
(function named), **[g]** guessed from value patterns.

## 1. What is on the disc

| File | Size | Used by the US game | Content |
|---|---|---|---|
| `Sound/sound_us.brsar` | 46.4 MB | yes, opened by `fn_8024CF54` (string at 0x803610C1) **[c]** | RSAR 1.4: 2024 sounds, 82 banks, 4 players, 1009 files, 201 groups |
| `Sound/sound.brsar` | 46.4 MB | no (no reference in main.dol) | older build of the same archive: 2021 sounds, 3 voice clips fewer; not the Japanese archive |
| `Sound/strm/*.brstm` | 1186 files, 612 MB | 633 of them (636 referenced, 3 missing, see below) | RSTM 1.0 streams: all music and all voice clips |
| `Sound/sound_data_en.cms` | 142 KB | yes (language table `lbl_80378918`, index `*(sys+0x1BC8)`) **[c]** | game label → archive label tables |
| `Sound/sound_data.cms` | 142 KB | Japanese language slot; on this disc only a leftover | same tables, its voice labels point to `STRM_VOICE_GMAP*_05_*` sounds that are not in `sound_us.brsar` |
| `soundroom.bin` | 4.5 KB | yes, Sound Room screen init `fn_8026F630` (`fn_80075D78("soundroom.bin")`) **[c]** | Sound Room track list and background images |

main.dol also names `sound_data_{de,fr,sp,it}.cms` (European builds), which are
not on this disc.

### Unreferenced streams (leftovers)

553 of the 1186 `.brstm` are not referenced by `sound_us.brsar` **[v]**:
265 `h_voice_*_22k` and the `FE_<chapter>_*` voice clips (Japanese voice
acting, 22.05/32 kHz), 24 `fe10_bgm_*`, 3 `fe10_map_*` and others. A port can
skip them; a mod could use them.

Three US voice sounds point to files that are not on the disc **[v]**:
`STRM_VOICE_KAISOU_FUU3_1_07_US`, `..._1_20_US`, `..._1_21_2_US`
(`strm/STRM_VOICE_KAISOU_FUU3_1_*_US.brstm`). A port must treat a missing stream
as silence, like the Wii does (nw4r fails the DVD open and drops the sound).

## 2. NW4R common structure **[v]**

All big-endian. Every file: `char magic[4]`, `u16 BOM 0xFEFF`,
`u16 version (major<<8|minor)`, `u32 file_size`, `u16 header_size`,
`u16 block_count`, then `(u32 offset, u32 size)` per block. Every block starts
with `char magic[4]`, `u32 size`; its payload begins at block + 8.

* **block_count is not reliable**: RSTM files say 2 but have HEAD, ADPC and DATA.
  Read pairs up to `header_size` instead (as nw4r does: fixed header structs).
* A **DataRef** is 8 bytes: `u8 refType` (0 = address, 1 = offset), `u8 dataType`
  (selects the pointed-to struct for unions), `u16 pad`, `u32 value`. Offsets
  are relative to the payload of the block that contains the table (RSAR INFO:
  relative to INFO + 8).
* A **Table** is `u32 count` followed by `count` items.

## 3. RSAR sound archive (`sound_us.brsar`, version 1.4) **[v]**

Header after the common part: `u32 symb_off, symb_size, info_off, info_size,
file_off, file_size` (0x10..0x27).

### SYMB (labels)

Payload: `u32 string_table, sound_tree, player_tree, group_tree, bank_tree`
(offsets into the payload). String table = `u32 n; u32 offset[n]`, NUL-terminated
ASCII. The four trees are Patricia tries (`{u16 flags, u16 bit, u32 left,
u32 right, u32 string, u32 id}` nodes) used by `ConvertLabelStringToSoundId`
(`fn_802AD3B0`) and `...GroupId` (`fn_802AD3C0`). 2310 strings.

### INFO

Payload starts with 6 DataRefs: sound table, bank table, player table, file
table, group table, player info.

**Sound** (`SoundCommonInfo`, 0x2C + sub info), 2024 entries:

| Off | Type | Field |
|---|---|---|
| 0x00 | u32 | string id (label) |
| 0x04 | u32 | file id |
| 0x08 | u32 | player id (0 BGM, 1 ENV, 2 SE, 3 VOICE_US) |
| 0x0C | DataRef | Sound3DParam `{u32 flags, u8 decayCurve, u8 decayRatio, u8 doppler}` |
| 0x14 | u8 | volume (0-127) |
| 0x15 | u8 | player priority |
| 0x16 | u8 | type: 1 SEQ, 2 STRM, 3 WAVE |
| 0x17 | u8 | remote (Wii Remote speaker) filter |
| 0x18 | DataRef | type-specific info (below) |
| 0x20 | u32[2] | user params (all 0 in FE10) |
| 0x28 | u8 | pan mode |
| 0x29 | u8 | pan curve |
| 0x2A | u8 | actor player id |

* SEQ info: `u32 data_offset` (label offset inside the RSEQ), `u32 bank id`,
  `u32 alloc_track` (bit mask), `u8 channel_priority`, `u8 release_priority_fix`.
* STRM info (1.4 layout): `u32 start_position`, `u16 alloc_channel_count`,
  `u16 alloc_track_flag`.
* WAVE info: `s32 sub_no` (index of the sound inside the RWSD), `u32 alloc_track`,
  `u8 channel_priority`, `u8 release_priority_fix`.

FE10 uses 376 SEQ sounds (all SE: footsteps, menus, magic), 637 STRM (all
music and voices; `STRM_DUMMY1` included) and 1011 WAVE sounds (SE).

**Bank**: `u32 string id, u32 file id` (82). **Player**: `u32 string id,
u8 max playable sounds, u32 heap size` (4 players: BGM 4, ENV 16, SE 16,
VOICE_US 4; heap size 0, the game owns the heaps).

**File** (1009): `u32 file_size, u32 wave_data_size, s32 entry, DataRef ext_path,
DataRef FilePos table`. External files (636 streams) have a path such as
`strm/fe10_bgm_btl_boss1_32k.brstm`, relative to `Sound/`. Internal files list
`(u32 group id, u32 index)` positions; the first one is enough to read the data.

**Group** (201): `u32 string id, s32 entry, DataRef ext_path, u32 offset, u32 size,
u32 wave_offset, u32 wave_size, DataRef item table`; item = `u32 file id,
u32 offset, u32 size, u32 wave_offset, u32 wave_size`.

* File bytes: `brsar[group.offset + item.offset : + item.size]`.
* Sample data: `brsar[group.wave_offset + item.wave_offset : + item.wave_size]`.
  This is a **raw DSP-ADPCM sample pool**, not an RWAR file; the RWSD/RBNK
  `WaveInfo.dataOffset + channel.dataOffset` are offsets into it (this is the
  `pWaveAddr` that `WaveFileReader::ReadWaveParam` adds). Verified for all 1553
  channels: the first byte at each computed offset equals the channel's
  `pred_scale` **[v]**.
* Groups: `GROUP_STATIC` (0.4 MB, always resident: system SE),
  `GROUP_FE10SOUND_ALL` (10.3 MB), `GROUP_FE10SOUND_BTL` (6.0 MB), one
  `GROUP_Cxxxx` per chapter (median 52 KB, max 2.4 MB), and an unnamed last group
  holding everything. The game loads the chapter group from
  `SND_CHAPTER_GROUP_DATA` (section 6).

**Player info**: `u16 seq sounds 64, seq tracks 96, strm sounds 4, strm tracks 4,
strm channels 8, wave sounds 64, wave tracks 64` — the maximum concurrency a
port's mixer must support.

### Sub-files inside the archive

| Kind | Count | Version | Layout |
|---|---|---|---|
| RSEQ | 111 | 1.0 | DATA: `u32 offset` (from block start) to MML byte code; LABL: `u32 n; u32 off[n]` → `{u32 code_offset, u32 len, char name[]}` (`SMF_<name>_Begin/_Start/_Track_n/_LoopStart/_End`). Sounds start at `SeqSoundInfo.data_offset`. |
| RBNK | 82 | 1.1 | DATA: Table of DataRegion per program; dataType 1 = InstParam `{s32 wave, u8 attack, decay, sustain, release, hold, pad, noteOffType, alternateAssign, originalKey, volume, pan, pad, f32 tune}`, 2 = RangeTable `{u8 n, u8 key[n], DataRegion[n] at round_up(n+1,4)}`, 3 = IndexTable `{u8 min, u8 max, u16 pad, DataRegion[]}`. WAVE: Table of DataRef → WaveInfo. |
| RWSD | 180 | 1.2 | DATA: `u32 n; DataRef<Wsd>[n]`; Wsd = DataRefs to WsdInfo `{f32 pitch, u8 pan, surroundPan, fxSendA/B/C, mainSend, ...}`, track table (note events `{f32 pos, f32 length, u32 note}`), note table (`{s32 wave, u8 attack, decay, sustain, release, hold, pad[3], u8 key, volume, pan, surroundPan, f32 pitch, ...}`). WAVE: `u32 n; u32 offset[n]` (from block start) → WaveInfo. |

**WaveInfo** (shared by RWSD, RBNK, RWAV): `u8 format (0 PCM8, 1 PCM16, 2 ADPCM),
u8 loop, u8 channels, u8 rate_hi, u16 rate, u16 pad, u32 loop_start, u32 loop_end,
u32 channel_table_offset, u32 data_offset, u32 reserved`; channel table =
`u32 offset[channels]` → `{u32 data_offset, u32 adpcm_offset, u32 volFL, volFR,
volRL, volRR, u32 reserved}`; offsets relative to the WaveInfo. For ADPCM the
loop fields are DSP nibble addresses: `sample = addr/16*14 + addr%16 - 2`, and
`samples = sample(loop_end) + 1`. All 1375 wave infos in FE10 are mono or stereo
ADPCM **[v]**.

## 4. RSTM streams (`Sound/strm/*.brstm`, version 1.0) **[v]**

Blocks HEAD, ADPC, DATA. HEAD payload: three DataRefs → stream info, track table,
channel table.

Stream info: `u8 format, u8 loop, u8 channels, u8 rate_hi, u16 rate,
u16 block_header_offset, u32 loop_start, u32 total_samples, u32 data_offset,
u32 block_count, u32 block_size, u32 block_samples, u32 last_block_size,
u32 last_block_samples, u32 last_block_padded_size, u32 adpcm_interval,
u32 adpcm_entry_size`.

Track table: `u8 count, u8 type, u16 pad, DataRef[count]`; type 0 =
`{u8 channels, u8 index[]}`, type 1 = `{u8 volume, u8 pan, u16 pad, u32 pad,
u8 channels, u8 index[]}`. Channel table: `u8 count, pad, DataRef[count]` →
`{DataRef → AdpcmInfo}`. AdpcmInfo (0x30): `s16 coef[16], u16 gain,
u16 pred_scale, s16 yn1, s16 yn2, u16 loop_pred_scale, s16 loop_yn1,
s16 loop_yn2, u16 pad`.

DATA payload: `u32 offset` (always 0x18) to the samples, then blocks
interleaved by channel: block 0 ch 0, block 0 ch 1, block 1 ch 0, ... Every block
is `block_size` bytes per channel except the last, which is
`last_block_padded_size`. The files end exactly after the last block.

ADPC: one `{s16 yn1, s16 yn2}` per block per channel = decoder history at the
start of each block, used by nw4r to start decoding mid-stream (seek, loop).
These values are the *encoder's* history (from the original PCM), so they are
close to but not identical with the decoder's own running history; when
decoding a whole file, carry the decoder history across blocks.

FE10 streams **[v]**: all DSP-ADPCM; 746 mono 32 kHz (voices), 265 mono
22.05 kHz (Japanese voices), 173 stereo 32 kHz (music), 2 mono 44.1 kHz;
`block_size` 8192 bytes = 14336 samples in every file; 144 loop. Total 5.4 hours.
Music is single-track stereo, no multi-track layering.

Decoder check: for every looping stream and wave the decoded samples at
`loop_start-1` / `loop_start-2` equal the stored `loop_yn1` / `loop_yn2`
(188/188 wave channels, 288/288 channels of the 144 looping streams) **[v]**.

### DSP-ADPCM

8-byte frames of 14 samples. Byte 0: `pred = ps >> 4`, `scale = 1 << (ps & 15)`.
Then 7 bytes of signed 4-bit nibbles, high nibble first.
`s = ((nibble * scale) << 11) + 1024 + coef[2*pred]*h1 + coef[2*pred+1]*h2;
s >>= 11` (arithmetic), clamp to int16, `h2 = h1, h1 = s`.

## 5. Game-side sound manager **[c]**

* Init `fn_8024CF54` (called from the main init at 0x80020000): opens
  `Sound/sound_us.brsar` as a DVD archive, allocates a 0x180000-byte sound heap
  (`fn_8030ECD8(lbl_8041F080, 0x180000)`) for archive tables, players and
  sound objects, sets up AXFX reverb/chorus (`fn_802A6534`, `fn_802A610C`),
  allocates a 0x1800000-byte (24 MB) heap for group data (`fn_802B16E0`), and
  starts a sound thread (`fn_8024CCF8`, priority 0x12).
* `fn_8024CF4C` loads `sound_data*.cms` (the file name comes from the language
  table) through the generic file loader with flags 0x880.
* Game sounds live in four slot arrays matching the archive players: BGM
  4 slots (`lbl_8042ED88`), ENV 16 (`lbl_8042ED98`), SE 16 (`lbl_8042EDD8`),
  VOICE 4 (`lbl_8042EE18`). `fn_8024DEF0` / `fn_8024E3AC` pause / resume all.
* Play SE: `fn_80253848(label, ...)`: `fn_80076F54(label)` → 0x24 record;
  enforces `max_instances` (stops the oldest when exceeded), computes random
  pitch/volume from the record, resolves `record.sound` with
  `ConvertLabelStringToSoundId` and starts it. `fn_802549C4` is the same for
  another category.
* Group loading: `fn_80257340(group_label, ...)` resolves a `SND_GROUP_*`
  record's archive group and queues the load (16-byte request ring at
  `lbl_80430568`, worker thread).
* Sound Room unlock: `fn_8024F3C8(label)` returns the record's `room_index`
  (+0x22); `fn_802454C8(sys, idx)` tests bit `idx` (0..127) of a 128-bit
  "BGM heard" set at system-data + 0x18A0. That bit set is part of the save
  data (see [save.md](save.md)).

## 6. Game sound tables (`Sound/sound_data_en.cms`)

LZ10 + IS binary container ([containers.md](containers.md)), 3548 labels.
Every BGM/SFX/VOICE record is itself labelled with its game name, so the
runtime lookup is a plain label search (`fn_80076F54`, hash `c + h*0x25` /
`c + h*0x1F`). The `SND_*_DATA` labels mark tables of the form
`u32 count; record[count]`.

| Table | Count | Record | Meaning |
|---|---|---|---|
| `SND_GROUP_DATA` | 203 | 8 | `{char* game group label, char* archive group label}` |
| `SND_BGM_DATA` | 604 | 0x24 | music records |
| `SND_SFX_DATA` | 2187 | 0x24 | sound effects |
| `SND_VOICE_DATA` | 546 | 0x24 | voice clips |
| `SND_ENV_DATA` | 305 | 0x18 | ambient sounds per map |
| `SND_MAP_DATA` | 201 | 0x14 | 3D/listener settings per map |
| `SND_SFX_MAYA_DATA` | 1208 | 8 | numeric SE id → SFX label |
| `SND_MAP_BGM_DATA` | 68 | 0x34 | music per chapter |
| `SND_BATTLE_BGM_DATA` | 150 | 0x1C | special battle themes |
| `SND_CHAPTER_GROUP_DATA` | 67 | 0x10 | archive group to load per chapter |

### Sound record (0x24), BGM/SFX/VOICE

| Off | Type | Field | Mark |
|---|---|---|---|
| 0x00 | char* | game label (`BGM_BTL_BOSS1`) | [v] |
| 0x04 | char* | archive sound label (`STRM_BGM_BTL_BOSS4`); several game labels may share one | [v][c] |
| 0x08 | u8 | kind 0 seq, 1 strm, 2 wave (matches the archive type for 98 % of records; 55 SFX differ) | [g] |
| 0x09 | u8 | volume 0-127 | [g] |
| 0x0A | s16 | pitch offset; its sign selects the divisor in the pitch formula | [c] |
| 0x0C | u8 | pitch range (2 for music/voice, 12 for SE) | [c][g] |
| 0x0D | u8 | pan (64 = centre) | [g] |
| 0x0F | u8 | priority (0/18/20/...) | [g] |
| 0x10..0x14 | u8 | 0, 127, 0, 255, flag (unknown) | |
| 0x15 | s8 | max simultaneous instances (-1 = no limit, SE default 8) | [c] |
| 0x16 | s16 | random pitch min | [c] |
| 0x18 | s16 | random pitch max | [c] |
| 0x1A | s8 | random volume min | [c] |
| 0x1B | s8 | random volume max | [c] |
| 0x1C | u16 | copied to the sound object (+0x58), unknown (often 100/150/200) | [c] |
| 0x1E | u16 | unknown | |
| 0x20 | s16 | unknown (SE only) | |
| 0x22 | s16 | Sound Room index, -1 = none (music only) | [c] |

Only two records point to archive labels that do not exist
(`BGM_OPENING1 → STRM_BGM_MOV_GOP1`, `VOICE_GMAP_1_5`); both are unused debug
entries **[v]**.

### Chapter music `SND_MAP_BGM_DATA` (13 words) **[c]**

`char* chapter ("C0101"), u8 condition (+3 pad), char* map[4], char* phase[4],
char* prologue, char* base, char* preparation`.

* Matching (`fn_800682C4`): chapter equal, then `condition` 0 = always,
  1..4 = game-state tests `fn_80060914/60960/60988/609B0` (routes/difficulty;
  not identified yet). First match wins.
* `fn_80068398(chapter, i)`: map BGM variant i, falls back to `map[0]`.
* `fn_80068424(chapter, i)`: phase BGM; i = 0 player, 1 enemy, 2 third army,
  3 fourth army (e.g. `BGM_PHASE_AKATUKI1`, `BGM_PHASE_EMPIRE1`).
* `fn_800684A0`, `fn_80068528`, `fn_800685B0`: prologue, base, preparation.

### Battle themes `SND_BATTLE_BGM_DATA` (7 words) **[c]**

`char* bgm, char* chapter, char* unit_a (PID), char* unit_b (PID), char* flag,
s8 a_14, s8 b_15, s8 a_16, s8 b_17, u8 flag_value, u8 symmetric, u16 pad`.
`fn_800689D4(a, b)` returns `bgm` of the first entry where every non-null /
non-negative field matches: chapter = current chapter, unit_a/unit_b = person
label of the two combatants (`unit+0xEC → +0`), `a_14/b_15` compare a byte at
`unit+0xF4 → +8`, `a_16/b_17` compare `unit+0xFD` (army/affiliation bytes, not yet
named), `flag` = event flag that must equal `flag_value`; `symmetric` allows
swapped roles. A null `bgm` means "no special theme".

### Other tables

* `SND_CHAPTER_GROUP_DATA` (`fn_800680D0`): `{char* chapter, char* flag,
  u8 flag_value, char* group}`; first entry whose chapter and optional flag match
  gives the `SND_GROUP_*` to load.
* `SND_ENV_DATA` (`fn_8013A8D8`): `{char* map, char* sfx, u8 type,
  u8 b9, u16 pad, f32 pos[3]}`; every entry whose map equals the current map is
  started as an ambient source; `SFX_ENV_FIRE_*` sounds are attached to fire
  objects instead of `pos`.
* `SND_MAP_DATA`: `{char* map, u8 b4 (127), u8 b5, u16 pad, f32 a, f32 b, f32 c}`
  (1.0/15.0/1.0 on maps, 0.5/8.5/1.0 for battle); first two entries are the
  Japanese defaults "マップ" (map) and "バトル" (battle). Probably 3D attenuation
  parameters **[g]**.
* `SND_SFX_MAYA_DATA`: `{u32 id, char* sfx}`, sorted by id, ids from 1000.
  `fn_800F14B4(id)` maps a numeric sound id (ids < 1000 and 0xFFFF mean none) to
  its SFX label by binary search; the numeric ids come from battle/effect
  animation data. Needed to play sounds from `FE10Anim`/`FE10Effect` data.

## 7. `soundroom.bin` **[c]**

IS container without labels. `u32 n (50); {char* image RID, s16 x, s16 y,
s16 scale %, u16 pad}[n]` (background pictures, `RID_...` names from
`window/` rect tables), then `u32 m (85); {char* bgm label, u32 number}[m]`
(`BGM_ROOM_*`). A track is listed as unlocked when its record's `room_index`
bit is set in the system save data (section 5).

## 8. Notes for the port

* Keep `nw4r::snd` and feed it the original files; only AX/AI below it needs a
  host implementation.
  Requirements from the data: DSP-ADPCM only (no PCM8/16 on the disc), mono and
  stereo, 22.05/32/44.1 kHz sources resampled to the output rate, loops with
  `loop_pred_scale/yn` context, at least 64 seq + 64 wave + 8 stream channels.
* Streams are read through DVD in 8 KB/channel blocks; on the host they can be
  memory-mapped. Missing streams must fail softly (three are missing).
* `brstm.py wav` / `brsar.py wav` give reference PCM for checking a host AX
  implementation sample-exactly.
* For "better than original" audio a port can swap streams for higher-quality
  files by archive label (file table `external` path), without touching the
  game tables.

## Open points

* MML byte code of the 111 RSEQ files is not disassembled (nw4r `MmlParser`
  in `lib/` is the reference); SE sequences cannot be rendered to WAV yet.
* Unknown record fields 0x10-0x14, 0x1C-0x20; the four map-BGM conditions.
* `SND_MAP_DATA` float meanings; `SND_ENV_DATA.type` values (1, 3, 4).
* Unit fields compared by battle-theme rules (`+0xF4→+8`, `+0xFD`).
