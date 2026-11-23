# Save data (Wii NAND): `banner.bin`, `FE10_US.dat`

Fire Emblem: Radiant Dawn (RFEE01 Rev 1). Reader: `tools/formats/savegame.py`
(library and CLI, Python 3.9 stdlib). It prints the parsed structure as JSON,
checks every CRC, can write a copy with the CRCs recomputed (`--fix-checksum`)
and has a `--selftest` that builds a synthetic save from the layout below and
round-trips it byte for byte.

**Checked against a real save (2026-11-14):** a freshly created US save from
Dolphin (`FE10_US.dat` + `banner.bin`, no game progress yet) confirms the file
names and sizes (0x124000 / 0xF0A0), the system block magic/revision, its
CRC-32 (computed = stored), the banner CRC-32 at system block +0x3B0, the
banner title, the serialized system block length (last non-0xFF byte at
0x3B3) and that all 12 empty slots are 0xFF. The slot layout (section 4) is
still unconfirmed because that save has no slot data yet.

**Second real save (2026-11-14 evening, Normal mode, after the prologue and
part of 1-1):** two save slots and one suspend slot. All three CRCs match, and
`savegame.py` parses every slot through the whole tag stream (`ITBL` ...
`DEBU`) with the 0xFF tail exactly where the stream ends, so the slot header,
`ITBL`, `BMST`, `UNIP`, `SOKO`, `FGPT`, `T  T`, `RELD`, `KZND` and `DEBU` layouts
are confirmed structurally. The decoded content matches the game: Micaiah
(Light Mage Lv 1, Light 37 uses, 2 Herbs), Edward (Blade Lv 4, Iron Sword 44),
Leonardo (Archer Lv 5, Iron Bow 46, Dragonshield), Nolan (Fighter Lv 9, Steel
Axe 40) and the 1-1 enemies (boss Isaiya, Begnion soldiers/fighters/archer)
with their weapons, skills and plausible HP. Confirmed by this data:

* header 0x1C save counter (1, 2, 3 across the three writes), 0x28 play time
  (243.7 s and 262.5 s), 0x35 difficulty, 0x36 chapter, 0x38 turn;
* unit force: 0 = player army on a map, 1 = enemy; between chapters the player
  units of a normal save have force 5 and position (0, 0) (not deployed);
* unit x/y (0x0D/0x0E) are map grid coordinates;
* stat gains: Leonardo, who levelled up, has +1 gains while some generic
  enemies show -1 gains (stat variance);
* weapon EXP per type (Nolan axe 71, Edward sword, Leonardo bow);
* chapter history entry 0: chapter 1, 5 turns, 196 seconds.

**Third real save (GameFAQs "100% extras" upload by ChopperJPL, imported in
Dolphin; probably edited with save tools, but written with valid CRCs):** five
used slots (a Part 4 endgame, a 4-Endgame Hard file at 49 hours, three
Prologue files with Path of Radiance transfer data) and system clear records
for two playthroughs. Every slot parses to the end with the 0xFF tail in
place, and `--fix-checksum` reproduces the file byte for byte. This confirms:

* gold (3 × u32 per army) and bonus EXP (3 × f32) at game state 0x18/0x24,
  gold gained/spent totals at 0xb0/0xb4, units defeated per force at
  0xc0/0xc8 (see section 4);
* convoy (`SOKO`) with forged weapons (name, might/hit/crit/weight bonus,
  colour), class-changed units (Nolan as JID_AXBRAVE/JID_WARRIOR, Laura as
  JID_SAINT_F/JID_BISHOP_F) with large stat gains;
* support pairs (`RELD`, e.g. Ike-Titania level 3) and bonds (`KZND`);
* the system block clear records (difficulty, turns, seconds, MVP) and the
  Path of Radiance transfer flag.

Otherwise everything here comes from the Ghidra
pseudo-C (`build/ghidra_c/`) and the DOL data. Confidence labels:

- **verified**: read directly from the code. The offset, size, type and (where
  given) meaning follow from the write *and* read functions, or from a direct
  use of the field.
- **inferred**: layout from code, meaning deduced from how the value is used.
  Likely, but not proven.
- **unknown**: layout from code, meaning not known.

All integers are **big-endian**. The serializer writes byte by byte
(`fn_8008A5AC` u8, `fn_8008A5C0` u16, `fn_8008A5E4` u32, `fn_8008A628` u64,
`fn_8008A780` raw copy, `fn_8008A71C` C string, `fn_8008A820` 4-byte tag). The
readers are `fn_8008A1A0`/`1B4`/`1DC`/`22C`/`43C`/`37C` and `fn_8008A518` for
tags. The stream object is `{u8 *start; u8 *cursor; u32 capacity; ...}`
(`fn_8008A48C`). The stream has **no padding and no alignment**. Raw copies
(`fn_8008A780`) dump in-memory bytes, which are big-endian on the Wii.

## 1. Files in the NAND data directory

Home directory: `NANDGetHomeDir` (`fn_80315C6C`) + `NANDChangeDir`
(`fn_80315A5C`), i.e. `/title/00010000/52464545/data/`. In Dolphin this is
`Wii/title/00010000/52464545/data/`. Paths are built with
`sprintf("%s%s", "./", name)` (`DAT_80372bbc`, `lbl_804CAAB0`).

| File | Size | Created by | NANDCreate perm | Content |
|---|---|---|---|---|
| `banner.bin` (`lbl_804CAAB4`) | 0xF0A0 (61 600) | `fn_802465E0` | 0x30 (owner RW) | standard Wii save banner |
| `FE10_US.dat` (`lbl_804CAAB8`) | 0x124000 (1 196 032) | `fn_80246E68` | 0x3c (owner RW, group RW) | system block + 6 save slots + 6 suspend slots |

Both are verified. No other file is created. The `_US` suffix is a string
constant, so other regions probably use other names (unknown). Before the files
are created, `fn_80246568` calls `NANDCheck(0x4d blocks, 2 inodes)`
(`fn_803164E0`). 77 × 16 KiB covers both files.

Creation (`fn_80246E68`, "create save data"):
1. A fresh system block is built in memory and serialized into a
   0x124000-byte buffer filled with 0xFF.
2. The CRC is computed, and the old `FE10_US.dat` is deleted (`NANDDelete`;
   -12/NOEXISTS is accepted).
3. `NANDCreate`, `NANDSafeOpen` and a single `NANDWrite` of 0x124000 bytes
   follow, then `NANDSafeClose`.
4. Then `fn_802465E0` writes `banner.bin` the same way, and `fn_80247D88`
   rewrites the system block so it can store the banner CRC.

`fn_80247578` deletes both files.

### banner.bin (verified, `fn_802465E0`)

Built with the SDK's `NANDInitBanner` (`fn_803162AC`). The layout is the SDK
`NANDBanner` struct (`lib/ogws/include/revolution/NAND/nand.h`):

| Off | Size | Field | Value |
|---|---|---|---|
| 0x00 | 4 | magic | `WIBN` |
| 0x04 | 4 | flags | 0 |
| 0x08 | 2 | iconSpeed, 2 bits per frame | frame 0 = 3, frames 1 and 7 = 2, frames 2..6 = 1 (8 frames) |
| 0x0A | 22 | reserved | 0 |
| 0x20 | 64 | title, UTF-16BE | from `lbl_80372968[lang]` (7 × 0x40): JP `ファイアーエムブレム　暁の女神`, all other languages `Fire Emblem: Radiant Dawn` |
| 0x60 | 64 | subtitle | empty, so the SDK writes `" "` |
| 0xA0 | 0x6000 | banner texture 192×64 RGB5A3 | TPL image 0 |
| 0x60A0 | 8 × 0x1200 | icon frames 48×48 RGB5A3 | TPL images 1..8 |

The language is `SCGetLanguage` (`fn_80325918`). The TPL is
`lbl_80391118[lang]`: `etc/banner.tpl` for Japanese (0), `etc/banner_en.tpl` for
all others. Both are on the disc (61 856 bytes, 9 images). The TPL image data
is copied raw (`fn_8032DBEC` + memcpy), so the TPL texture format must already
be RGB5A3.

After writing, the game computes `CRC32(banner.bin[0:0xF0A0])` and stores it in
the system block (offset 0x3B0, see below). `fn_80246ADC` re-reads the banner
and compares the two. A mismatch returns error -0x100. The check runs at boot
(`fn_8024B4D4` → `fn_80246E0C`) and at the start of every slot write.

## 2. FE10_US.dat layout

| Offset | Size | Content | Evidence |
|---|---|---|---|
| 0x000000 | 0x4000 | system block `FE10ASYS` | `fn_802479A8` (read), `fn_80247D88` (write) |
| 0x004000 + i·0x18000, i = 0..5 | 0x18000 | save slot i, `FE10ADAT` | `fn_80248154`, `fn_80248CCC`, `fn_802488B8` |
| 0x094000 + i·0x18000, i = 0..5 | 0x18000 | suspend ("battle save") slot i, `FE10ADAT` | `fn_8024A410` (write), `fn_80249FF4` (read) |

All offsets and sizes are verified. 0x4000 + 12·0x18000 = 0x124000. The
file-select menu iterates 6 slots (`80198000.c`, `while (iVar5 < 6)`, index
0..5). A suspend save is written to the suspend slot with the same index as
its save slot (`fn_8024BA84(header+0x30)`). Unused space and unused slots are
0xFF (`fn_8017F44C(buf, 0xffffffff, size)` before serializing). Erasing a slot
(`fn_802493B4` save, `fn_8024AB04` suspend) writes 0x18000 bytes of 0xFF.

### Checksum (verified)

Every block (system 0x4000, slot 0x18000) has a u32 at **+0x18**. It holds the
standard CRC-32 (reflected polynomial 0xEDB88320, init 0xFFFFFFFF, final
XOR 0xFFFFFFFF, the same as `zlib.crc32`), computed over the **whole block**
(0x4000 or 0x18000 bytes, padding included) with the 4 CRC bytes set to
zero. The table is built inline each time. Writers: `fn_80247D88`,
`fn_80248154`, `fn_80248CCC`, `fn_8024A410`, `fn_8024953C` (loop counts 0x800
and 0x3000 × 8 bytes). Readers: `fn_802479A8`, `fn_802488B8`, `fn_80249BDC`,
`fn_80249FF4`, `fn_8024AC94`, `fn_8024B0B4`.
`savegame.crc32_block()` implements it.

There is no encryption or obfuscation. The data is plain (verified: the
serialized buffer goes straight to `NANDWrite`).

### Validation and error handling (verified)

On load, the game checks:
1. The read returns the full size. A short read gives -8.
2. The magic matches (`FE10` + `ASYS`/`ADAT` + version date). Otherwise the
   result is -12 (NAND "no exists").
3. The CRC matches. Otherwise the result is -0x100.

The result goes to `lbl_804CBFCC`. -3 (NAND busy) is retried in a loop. The
format revision (+0x0C) is *not* rejected: readers branch on it to load older
layouts (see below). Section tags inside a slot are read with `fn_8008A518`,
but the result is ignored, so a wrong tag is not detected. Writes always go
through `NANDSafeOpen`/`NANDSafeClose` (`fn_8031490C`/`fn_80314C40`), so a
power loss cannot leave a half-written file. Every slot write (new game, save,
suspend) rewrites the system block at offset 0 in the same session.

| Code | Meaning |
|---|---|
| 0 | ok |
| -3 | NAND busy, retried |
| -8 | short read or write |
| -12 | file missing or magic wrong |
| -0x100 | CRC mismatch (also banner CRC mismatch) |

## 3. System block `FE10ASYS` (0x4000, serialized 0x3B4 bytes)

In memory it is `lbl_80427820`. Serializer `fn_80245888`, deserializer
`fn_80245A74`, init `fn_80244D90` / `fn_80246E68`. Current revision 7.

| Off | Size | Field | Conf. |
|---|---|---|---|
| 0x000 | 8 | magic `FE10ASYS` (written as u64 0x46453130_41535953) | verified (`fn_802450BC`) |
| 0x008 | 4 | version date 0x20061002 | verified |
| 0x00C | 4 | revision 7 (the writer always stores 7) | verified |
| 0x010 | 8 | OSGetTime when the save data was created | verified (`fn_80246E68`) |
| 0x018 | 4 | CRC-32 (read only if rev > 5) | verified |
| 0x01C | 8 | bit-set object (+0x1c, vtable `lbl_80391160` = 8 raw bytes). u32 at 0x1C: bits 1/2/3/0 are set by `fn_80245614` when a game is cleared on difficulty 0/1/2/3. Bit 4 is set when Path of Radiance data was imported (`fn_80248154`) | layout verified, meaning inferred |
| 0x024 | 16 | bit-set object (+0x28, vtable `lbl_8037F7E0` = 16 raw bytes) | unknown |
| 0x034 | 0x60 | 768 "named flags", 1 bit each (+0x183c) | verified layout, see below |
| 0x094 | 16 | bit-set +0x189c (read only if rev > 4) | unknown |
| 0x0A4 | 16 | bit-set +0x18b0 | unknown |
| 0x0B4 | 8 | bit-set +0x18c4 | unknown |
| 0x0BC | 8 | bit-set +0x18d0 | unknown |
| 0x0C4 | 8 | bit-set +0x18dc | unknown |
| 0x0CC | 8 × u16 | +0x18e8..0x18f6. Defaults 0xffff ×3, then 4 values from `lbl_804D0018..1E`, then 0xffff | unknown |
| 0x0DC | 30 × 0x18 | clear records (+0x18f8), see below | layout verified |
| 0x3AC | 1 | +0x1bc8, always 1 (`fn_80244D88`) | unknown |
| 0x3AD | 1 | last used save slot (`DAT_804293e9`, set from slot header +0x30) | inferred |
| 0x3AE | 2 | +0x1bca (rev ≥ 7, else 0xffff) | unknown |
| 0x3B0 | 4 | CRC-32 of `banner.bin` (rev ≥ 7) | verified (`fn_802465E0`, `fn_80246ADC`) |
| 0x3B4 | … | 0xFF up to 0x4000 | verified |

**Named flags.** `fn_8024519C` / `fn_802452B4` / `fn_80245368` keep a table
of up to 0x300 (string pointer, hash `fn_80076D18`) pairs at +0x3c and +0xc3c.
A flag is registered and set by **name**. Example: when Path of Radiance
data is imported, `fn_8026D0F8` sets `FLG_8_%s_%s_C/B/A` support flags. Only
the bit array is saved, not the names, so bit *n* means "the n-th name
registered in this boot". Where the names are registered (and whether the
order is stable) is an open point. A port must reproduce the same
registration order or it will misread these bits.

**Clear record** (0x18 bytes, written by `fn_80245614`, called from
`fn_800434A0`, inferred to run at game end). Up to 30 records. When the list is full, the oldest record is
dropped (memmove).

| Off | Type | Field | Conf. |
|---|---|---|---|
| 0x00 | u64 | playthrough id (slot header +0x10) | verified |
| 0x08 | s8 | difficulty (slot header +0x35); < 0 = empty record | verified |
| 0x09 | u8 | playthrough number (slot header +0x34) | verified |
| 0x0A | u16 | PersonData index from `fn_80287358()` (+0x1c) | unknown (MVP?) |
| 0x0C | u32 | sum of the chapter-history turn counts | inferred |
| 0x10 | u64 | sum of the chapter-history seconds | inferred |

## 4. Slot `FE10ADAT` (0x18000)

The in-memory header is `lbl_80429400` (`fn_8024BCA0()`).

Writers:
- `fn_80248154`: new game into slot. Sets the playthrough id and difficulty.
- `fn_80248CCC`: normal save.
- `fn_8024A410`: suspend save.
- `fn_8024953C`: copy slot (re-CRC; changes +0x30 and +0x1C).

Readers:
- `fn_802488B8`: load save.
- `fn_80249FF4`: load suspend.
- `fn_80249BDC` / `fn_8024AC94`: read the header only, for the file menu.

The slot body serializer is `fn_8024BD18`; the deserializer is `fn_8024BED8`.
Current revision 0x11. Each part ends in a 4-byte tag before the next part.

```
0x0000  header           0x60 bytes
0x0060  PoR transfer     0x1000 bytes
0x1060  "ITBL" ID string tables
        "BMST" game state
        "MDST" map/mode state (51 bytes)
        "UNIP" 254 unit records (variable)
        "SOKO" convoy 300 + 16 items (variable)
        "FGPT" 12 bytes
        "T  T" tile table 0x408 bytes
        "RELD" support list
        "KZND" bond list
        "DEBU" 8 bytes ("DEBUG" string, only 4 bytes are written)
        0xFF padding up to 0x18000
```

### 4.1 Header (`fn_80245E44` / `fn_80245F9C`)

| Off | Size | Field | Conf. |
|---|---|---|---|
| 0x00 | 8 | `FE10ADAT` | verified (`fn_80245DFC`) |
| 0x08 | 4 | version date 0x20060920 | verified |
| 0x0C | 4 | revision, always written as 0x11 | verified |
| 0x10 | 8 | playthrough id = OSGetTime at new game (`fn_80248154`), kept by later saves | verified |
| 0x18 | 4 | CRC-32 | verified |
| 0x1C | 4 | save counter, +1 on every save and on copy | verified |
| 0x20 | 8 | OSGetTime of this save (`fn_8024BD18`) | verified |
| 0x28 | 8 | total play time in OSGetTime ticks (game state +0xa0). Seconds = ticks / 60 750 000 (bus clock / 4) | verified layout, unit inferred |
| 0x30 | 1 | slot index | verified |
| 0x31 | 1 | 1 = suspend save, 0 = normal (`DAT_80429431`) | verified |
| 0x32 | 1 | suspend: slot it belongs to; 0xff from new game | inferred |
| 0x33 | 1 | ? | unknown |
| 0x34 | 1 | game state +0x9f: the new-game parameter, capped at 99 (the reader turns 0 into 1) | inferred: playthrough number / NG+ count |
| 0x35 | 1 | difficulty, chosen in the new-game menu (0..2); mirrored at options +0x11 | verified |
| 0x36 | 1 | chapter = game state +0x10 (ChapterData index, `fn_8006074C` → `fn_8010B094`) | verified |
| 0x37 | 1 | game state +0x9c (initial value 3); written as 8 for suspend saves | unknown |
| 0x38 | 2 | game state +0x12: turn number | inferred |
| 0x3A | 2 | ? | unknown |
| 0x3C | 4 | bit-set (vtable `lbl_80391150`, 4 bytes); bit 0 = PoR transfer block present | verified |
| 0x40 | 0x20 | options/config (`fn_8010940C`, defaults `fn_801095FC`): 8 bytes of option bits, u8 ×10 (defaults 1, 20, 0x40, 0, 0, 100, 100, 100, 100, difficulty), u16, u32 ×3 | layout verified, meanings unknown (+0x11 = difficulty verified) |
| 0x60 | 0x1000 | Path of Radiance transfer data (zero if absent). Copied from the new-game parameter and parsed by `fn_8026D0F8`: u32 coin count (adds `IID_COIN` items), u32 n, n × 0x24-byte character records (support levels become `FLG_8_*` flags) | inferred |

### 4.2 ITBL: ID string tables (`fn_80242920` / `fn_80242BB0`), verified

The ITBL is the key to portability. All later records store small integer
indices, and these tables map them back to ID strings.

On load, the game builds a remap object (`lbl_804CBFC8`, 9 vectors). Each
saved index is turned into `prefix + name` and resolved by name in the
*current* FE10Data (`fn_8010B1D8` PID, `fn_8010B200` JID, `fn_8010B228` IID,
`fn_8010B23C` SID). A port should do the same: look up IDs by name, never by
raw index.

Eight tables, each written as `u32 n` followed by `n` NUL-terminated strings:

| # | Content | Stored as | Index base in records | Name rebuilt by |
|---|---|---|---|---|
| 0 | PersonData IDs | PID without the `PID_` prefix (`fn_80118DE8` = str+4) | 1-based (0 = none) | `fn_80244470` |
| 1 | JobData IDs | JID without `JID_` (`fn_8011927C`) | 1-based | `fn_80244580` |
| 2 | ItemData IDs | IID without `IID_` (`fn_8010F5B4`) | 1-based | `fn_80244690` |
| 3 | SkillData IDs | SID after the first `_` (`fn_8011A028`) | 0-based | `fn_802447A0` |
| 4 | `CP_ATKSEQ_LIST` entries (+4) | AI sequence names | 0-based | `fn_802448AC` (`SEQ_`) |
| 5 | `CP_MOVSEQ_LIST` | | 0-based | `fn_802449B8` |
| 6 | `CP_HEALSEQ_LIST` | | 0-based | `fn_80244AC4` |
| 7 | `CP_MTYPE_LIST` (+6) | | 0-based | `fn_80244BD0` (`MTYPE_`) |

Strings are Shift-JIS/ASCII. The counts equal the FE10Data table sizes at save
time (persons 461, jobs 171, items 296, skills 142 in this build).

### 4.3 BMST: game state `lbl_803CAB38` (`fn_80062AE8` / `fn_80062DE0`)

The stream offsets below are relative to the end of the `BMST` tag. "+mem" is
the offset in the in-memory struct.

| Stream | +mem | Size | Field | Conf. |
|---|---|---|---|---|
| 0x00 | 0x00 | 16 | raw | unknown |
| 0x10 | 0x10 | 1 | chapter (ChapterData index) | verified |
| 0x11 | 0x11 | 1 | ? (used very often) | unknown |
| 0x12 | 0x12 | 2 | turn | inferred (chapter history stores it as "turns") |
| 0x14 | 0x14 | 4 × u8 | ? | unknown |
| 0x18 | 0x18 | 3 × u32 | gold per army (index = chapter record +0x89: 0 Dawn Brigade / 1 / 2), cap 9,999,999; set `fn_800615DC`, get `fn_800626E0` | verified (code + real saves: 5000 after the prologue) |
| 0x24 | 0x24 | 3 × f32 | bonus EXP per army, same army selection; get `fn_80062780`/`fn_80062850` (rev < 12: converted by `fn_800615DC`) | verified by code pattern + real saves (60.0 after the prologue) |
| 0x30 | 0x30 | 0x24 | raw | unknown |
| 0x54 | 0x54 | 0x3c | raw (rev < 14: 0x24) | unknown |
| 0x90 | 0x90 | 3 × u8 | ? | unknown |
| 0x93 | 0x94 | 6 | 3 × u16 (rev < 9: `fn_80089ED0` defaults) | unknown |
| 0x99 | 0x934/0x938 → 0x9a/0x9b | 2 | two floats stored as u8 | unknown |
| 0x9B | 0x9c..0x9e | 3 | 0x9c is mirrored to header 0x37 | unknown |
| 0x9E | 0x9f | 1 | playthrough number (header 0x34) | inferred |
| 0x9F | 0xa0 | 8 | total play time, OSGetTime ticks (header 0x28) | verified |
| 0xA7 | 0xa8 | 8 | play time of the current chapter, ticks (converted to seconds into the chapter history) | verified |
| 0xAF | 0xb0 | 4 + 4 | total gold gained / total gold spent (`fn_800615DC` adds every change) | verified |
| 0xB7 | 0xb8 | 2 + 2 | ? | unknown |
| 0xBB | 0xbc | 4 | per-chapter score, recomputed at chapter end (`8008C000.c`) and stored in the history (rev < 16: u16) | unknown |
| 0xBF | 0xc0 | 4 × u16 | units defeated this chapter, per force 0-3 (incremented at unit death, `0x80028000` battle code) | verified |
| 0xC7 | 0xc8 | 4 × u32 | units defeated in the whole game, per force 0-3 (1944 enemies in a late real save) | verified |
| 0xD7 | 0xd8 | 16 | bit-set (vtable `lbl_8037F7E0`): event flags? | inferred |
| 0xE7 | 0xec | 16 | bit-set: event flags? | inferred |
| 0xF7 | 0x134 | 5 | unit ref (u8 unit number, 1-based, 0 = none) + 4 × u8 (`fn_8010E890`) | layout verified |
| 0xFC | 0x13c | 5 | unit ref | layout verified |
| 0x101 | 0x544 | 16 | 128-bit set (rev < 15 converted) | unknown |
| 0x111 | 0x554 | 60 × 0x10 | chapter history, see below | layout verified |
| 0x4D1 | 0x914 | 0x18 | raw | unknown |
| 0x4E9 | 0x954 | 1 + 2n | u8 n, then n × (u8, u8) | unknown |
| … | 0x100 | 0x30 | 384-bit set (vtable `lbl_8037F7F0`): event flags? | inferred |

Chapter history record (`fn_80060580`, one per cleared chapter, 60 entries):

| Off | Type | Field | Conf. |
|---|---|---|---|
| 0x0 | u8 | chapter | verified |
| 0x1 | u8 | parameter | unknown |
| 0x2 | u16 | turns | inferred |
| 0x4 | u32 | chapter time in seconds (+0xa8 ticks / (bus/4)) | verified |
| 0x8 | u16 | PersonData index (ITBL PID) from `fn_80062914` | unknown (MVP?) |
| 0xA | u16 | unused since rev 16 | verified |
| 0xC | u32 | game state +0xbc | verified layout |

Gold and bonus EXP are per army at 0x18 / 0x24 (see table); `savegame.py`
prints them as `gold`, `bonus_exp`, `gold_gained_total`, `gold_spent_total`,
`defeated_chapter`, `defeated_total`.

### 4.4 MDST (`fn_8013498C` / `fn_80134B80`), 51 bytes

Layout:
- u8 sub-version = 4.
- u8 `lbl_804CB830`: phase. 1/2 are tested together with force 1 in
  `fn_801220A0` (inferred).
- 6 × u8, then 4 × u8.
- 4 × (3 u8 + 3 u8) from `lbl_80413BE8`/`lbl_80413BF8`.
- 3 × u16.
- s8 + 2 × u16: index of a map object and its position × a scale factor
  (`fn_8012FCD0`). This is probably the cursor or camera.
- 1 + 3 × u8.

The layout is verified; the meanings are unknown.

### 4.5 UNIP: 254 unit records (`fn_8012D38C`, `fn_80121700` / `fn_80121A28`)

The runtime unit array is `lbl_804CB810`: 254 × 0x3f0 bytes (`fn_8012E264`
ctor, `fn_801221E8` reset). Records are written for every one of the 254
slots, in order. Slot *k* is "unit number" *k+1*, the 1-based value that other
records use to point at units. An empty slot is just `u16 0`.

Revision < 11 saves had 0x9f slots. Record layout:

| Off | Size | Field | +mem | Conf. |
|---|---|---|---|---|
| 0x00 | 2 | PID index (ITBL 1-based); 0 = empty, record ends | person +0x1c | verified |
| 0x02 | 2 | JID index (ITBL 1-based) | job +0xec | verified |
| 0x04 | 1 | force: list index 0..10 (`lbl_804CB814` + i·0xc). 0 = player, 1..3 get no EXP (`fn_80126B0C`) | +0xf4 → +8 | layout verified, meaning inferred |
| 0x05 | 1 | linked unit number (rescued/carried?) | +0xe4 | inferred |
| 0x06 | 1 | linked unit number | +0xe8 | unknown |
| 0x07 | 1 | linked unit number | +0xf8 | unknown |
| 0x08 | 1 | GroupData index (`fn_8010B180`): affiliation | +0xfd | inferred |
| 0x09 | s8 | level. The display level adds 20/40 for tier-2/3 skills (`fn_80126BA4`) | +0xfe | verified |
| 0x0A | u8 | EXP 0..100, 0xff = cannot gain EXP (`fn_80126B80`) | +0xff | verified |
| 0x0B | u8 | ? (default person+0xe2 or 30): laguz gauge? | +0x100 | unknown |
| 0x0C | u8 | ? | +0x101 | unknown |
| 0x0D | u8 | x on the map | +0x102 | inferred (`fn_801220A0` grid x + y·0x40) |
| 0x0E | u8 | y on the map | +0x103 | inferred |
| 0x0F | 8 | 2 × u32 state flags | +0x108/+0x10c | unknown bits |
| 0x17 | 4 | raw (`fn_80109078` init) | +0x110 | unknown |
| 0x1B | u8 | current HP (clamped to max HP in `fn_80126D9C`) | +0x114 | verified |
| 0x1C | u8 | ? | +0x115 | unknown |
| 0x1D | s8 | movement bonus (added to class move, max 20) | +0x116 | verified |
| 0x1E | 8 × s8 | stat gains HP Str Mag Skl Spd Lck Def Res. Actual stat = person modifier (PersonData +0x22..) + this + class base (JobData +0xfc..), capped at the class max | +0x119 | verified (`fn_80126D9C`) |
| 0x26 | 8 | raw | +0x121 | unknown |
| 0x2E | 1 + 4n | skills: u8 n (non-empty of 18 slots), then n × {u16 SID index (0-based), u8, u8} (`fn_8011BAC8` / `fn_8011A298`) | +0x12c (18 × 8) | verified layout; the two bytes are unknown (rev < 13 clears bit 1 of the 2nd when the 1st is 1) |
| … | 7 × item | inventory, see item record | +0x1bc (7 × 0x28) | verified |
| … | 24 | weapon EXP, 12 × u16 in weapon-rank order (sword lance axe bow knife strike fire thunder wind light dark staff). Thresholds E=1 D=31 C=71 B=121 A=181 S=251 SS=331 | +0x2d4 | inferred (12 × u16 matches PersonData's u16[12] ranks) |
| … | 14 | 6 × u16 + 2 × u8 (`fn_80106CA8`): battle statistics? | +0x382 | unknown |
| … | (support block) | only if the character has a RelianceData record (see below) | | verified |
| … | 1+1+2+2 | u8, u8, u16, u16 (defaults ff ff ffff 0) | +0x378..+0x37c | unknown |
| … | 22 | AI block (`fn_80129650`): u8 ATKSEQ, u8 MOVSEQ, u8 MOVSEQ, u8 HEALSEQ, u8 MTYPE (ITBL 0-based), u8 ×4 (+0x3b0), u32 (+0x3b4), u16 (+0x3b8), u8 (+0x3ba), u8 (+0x3bc), u8 (+0x3a8), u16 (+0x3be), u16 0 | +0x394.. | layout verified |
| … | 4 | u16 (+0xc4), u8 0, u8 0 (`fn_800FB2B8`) | | unknown |
| … | 1+1+2+1 | u8 (+0x117), u8 (+0x118, default 0xff), u16 (+0x37e), u8 (+0x380, default 0xff) | | unknown |

**Support block** (present iff `fn_8012E830(unit)` ≠ 0, i.e. the person has
a RelianceData record):

| Size | Field |
|---|---|
| 12 | bit-set (+0x2ec, vtable `lbl_80379438` = 12 raw bytes) |
| 2 | PID index (ITBL), from `fn_8012E390`. Inferred: current support partner |
| 1 | n = number of RelianceData partner entries (record u32 at +4, low byte) |
| n | support points per partner, in RelianceData order (+0x300, max 0x48) |
| 3 × 12 | bit-sets (+0x348/+0x358/+0x368) |

The writer and the reader both decide whether this block exists from the
**current FE10Data**, not from a flag in the save. A port must use the same
RelianceData. `savegame.py --fe10data` does exactly this; without it, it
backtracks over both variants.

**Item record** (`fn_80111D68` / `fn_80111E48`), used in inventories and the
convoy:

| Size | Field | Conf. |
|---|---|---|
| 2 | IID index (ITBL 1-based). 0 = empty slot; the record is then 4 bytes in total | verified |
| 1 | uses left (+4, initialised from ItemData uses) | verified |
| 1 | flags (+5). Bit 5 (0x20) = forged weapon | verified |
| if forged: C string | forge name (buffer 0x18 incl. NUL) | verified |
| 4 × s8 | forge bonus might, hit, crit, weight (+0x1e..+0x21, added to ItemData +0x1c/+0x1d/+0x1f/+0x1e) | verified |
| 4 | name colour RGBA? (+0x22..+0x25, default 80 80 80 FF) | inferred |

### 4.6 SOKO: convoy (`fn_801058B4` + `fn_80105768`)

- 300 item records (`lbl_804CB750 = 300`, buffer `lbl_803E92A0`). The runtime
  splits it into three convoys of 100 (`fn_801059EC`), probably one per army
  (inferred).
- 16 item records from `lbl_803E9000`: items waiting to be put into the convoy
  (`fn_8004357C` moves them in) (inferred).

No count is stored; the slot counts are fixed.

### 4.7 FGPT, "T  T", RELD, KZND, DEBU

| Tag | Content | Conf. |
|---|---|---|
| FGPT | 12 bytes `lbl_803E9288` = 6 × s16. `fn_8008F968(i)` adds 50, capped at 4950 | layout verified, meaning unknown |
| `T  T` | 128 × {u8 x, u8 y, u8 kind, u8, u8[4]}, then u32 used-count, 0x200 raw, u32 (`fn_80066AC0`). Looked up by (x, y, kind) in `fn_80066130`: per-tile map state (opened chests/doors, visited villages?) | layout verified, meaning inferred |
| RELD | u32 n, n × {u16 PID, u16 PID, u8 level} (`fn_80119C48`): active support pairs | layout verified, meaning inferred |
| KZND | u32 n, n × {u16 PID, u16 PID, u8, u8} (`fn_801131D8`): bonds (KiznaData) | layout verified |
| DEBU | 8 raw bytes `lbl_804CB8D0` | unknown |

The reader skips RELD and KZND for rev < 9.

### 4.8 Not on disk: RAM checkpoint

`fn_8024C2B4` / `fn_8024C434` (called from `fn_8009999C` / `fn_80099A90`)
serialize the same sections without the header's ITBL, plus a `MIND` section
(`fn_8004A424(lbl_803CA870)`), into a 0x18000 heap buffer. This is a
memory-only snapshot (restart/retry). It is never written to NAND. Without an
ITBL, indices there are used directly.

## 5. Notes for a port

- **Endianness**: every field is explicitly big-endian, and raw blocks are
  copies of big-endian memory. A little-endian port must byte-swap when it
  copies them; the multi-byte raw blobs are listed above.
- **No pointers** are stored. Units refer to each other by 1-based unit
  number, and data records are referenced by ITBL index. Resolve them by ID
  string through the ITBL.
- **Version handling**: slot revision 0x11 and system revision 7 are current.
  The readers accept older revisions (branches at 5, 6, 7 for the system
  block and 9, 11, 12, 13, 14, 15, 16, 17 for slots). Release saves should
  always be 0x11 / 7.
- **Corruption**: the CRC catches it per block, and each slot is checked
  on its own, so the other slots stay usable (verified). How the menu reacts
  to a bad system block (re-create?) was not traced (open point).
- The named-flag bits in the system block depend on runtime registration
  order (section 3).
- Time values are raw OSGetTime ticks (60.75 MHz, epoch 2000-01-01).

## 6. Function index

| Function | Role |
|---|---|
| `fn_8024B450`..`fn_8024BC14` | public API: queue a NAND task on the thread `lbl_8042A470` (`fn_8031FC48`), arguments in `lbl_8042A470+0x4318..` |
| `fn_80246568` | NANDCheck free space |
| `fn_80246E68` / `fn_802465E0` | create FE10_US.dat / banner.bin |
| `fn_80246ADC` | verify the banner CRC |
| `fn_80247578` | delete both files |
| `fn_802479A8` / `fn_80247D88` / `fn_8024B0B4` | system block read / write / verify |
| `fn_80248154` | new game into slot |
| `fn_80248CCC` / `fn_802488B8` | save / load slot |
| `fn_8024A410` / `fn_80249FF4` | suspend save / load |
| `fn_8024953C` | copy slot |
| `fn_802493B4` / `fn_8024AB04` | erase save / suspend slot |
| `fn_80249BDC` / `fn_8024AC94` | read the slot header only (file menu) |
| `fn_8024BD18` / `fn_8024BED8` | slot body serializer / deserializer |
| `fn_80245888` / `fn_80245A74` | system block serializer / deserializer |
| `fn_80245E44` / `fn_80245F9C` | slot header serializer / deserializer |
| `fn_80242920` / `fn_80242BB0` | ITBL |
| `fn_80062AE8` / `fn_80062DE0` | BMST |
| `fn_80121700` / `fn_80121A28` | unit record |
| `fn_80111D68` / `fn_80111E48` | item record |
| `fn_8008A1A0`..`fn_8008A820` | byte stream primitives |

## Open points

1. Meaning of the remaining game-state (BMST) fields (0x14, 0x30, 0x54,
   0x90.., 0xb8) and the part number.
2. Named-flag registration (system 0x034, 768 bits): where the names are
   registered, and whether the order is deterministic.
3. Unit fields +0x100, +0x101, +0x115, +0x121 (8 bytes), +0x110, +0x117,
   +0x118, +0x378..+0x380, the battle-statistic block +0x382, both skill
   bytes, and the meaning of the three extra unit links.
4. MDST, FGPT, `T  T` semantics. Header bytes 0x33, 0x37, 0x3A and the options
   block.
5. Exact format of the 0x1000-byte Path of Radiance transfer block and where
   it is read from (GameCube memory card via the CARD library? `etc/memcard.tpl`
   and the string `暁の女神　セーブデータ` sit next to the save code).
6. File names in other regions (`FE10_US.dat` is a constant here).
7. Whether all 6 slots are visible in the menu; the code iterates 0..5.
8. Everything here is unchecked against a real save. Dumping one from
   Dolphin and running `savegame.py` (CRC check plus a clean parse to `DEBU`
   with `tail_is_ff`) would confirm the stream layout immediately.
