# FE10Data.cms, FE10Growth.cms and Shop/shopitem_*.bin

Fire Emblem: Radiant Dawn (RFEE01 Rev1). The decoder is `tools/formats/fe10data.py`
(library and CLI). All three files are IS relocatable containers (see `isbin.py`).
`.cms` files are LZ10-compressed first. Integers are big-endian. "ptr" means a
relocated u32 pointer field: it is listed in the container's pointer table and holds
a data-relative offset, usually to a NUL-terminated Shift-JIS/ASCII ID string.
Offsets below are relative to the record start unless stated otherwise.

Confidence labels:
- **verified**: field meaning checked against known in-game values and/or the
  loader code in the DOL.
- **code**: offset, size and type taken from the Ghidra pseudo-C, but the meaning
  is not fully confirmed.
- **guessed**: inferred from data patterns only.

## Loader overview (main.dol)

`fn_80109B18` (0x80109B18) looks up each table label with `fn_80077064(name)` and
either keeps a pointer into the file or expands the records into heap structs:

| Table | Loader | Runtime struct | Lookup |
|---|---|---|---|
| PersonData | `fn_80109DF8` | 0xfc bytes, array `lbl_804CB794` | `fn_8010B1B4(id)` (1-based), by PID string `fn_8010B1D8` |
| JobData | `fn_8010A2FC` (+ `fn_801192F0` fixup) | 0x11c, `lbl_804CB79C` | `fn_8010B1DC(id)`, `fn_8010B200(JID)` |
| ItemData | `fn_8010A958` | 0x50, `lbl_804CB7A4` | `fn_8010B204(id)`, `fn_8010B228(IID)` |
| SkillData | kept in file, `lbl_804CB7AC` | 0x2c raw | `fn_8010B22C(idx)`, `fn_8010B23C(SID)` |
| TerrainData | kept in file, `lbl_804CB7B0` | 0x10 raw | `fn_8010B240(idx & 0xff)` |
| DivineData | kept in file, `lbl_804CB7D8` | 0xc raw | `fn_8010B250(idx)` |
| ChapterData | stream copy, `lbl_804CB7D4` | 0xb4 (same as file) | `fn_8010B0CC(idx)`, `fn_8010B094(chapter_no)`, `fn_8010B100(CID)` |
| GroupData | kept in file, `lbl_804CB7E0` | 0xc raw | `fn_8010B180(idx)` |
| KiznaData | kept in file, `lbl_804CB7E4` | 0xc raw, scanned until null PID | functions around 0x80111A00 |
| RelianceData | `fn_801198C8` | in place, PIDs resolved to person structs | person+0xdc → record |
| RelianceParam | `fn_801198C8` → `lbl_804CB808` | 16 bytes | |
| 3SukumiData | `fn_80110000` area (line ~1704 of 80110000.c) | | |
| BioData | `80104000.c`, `80124000.c` | | |
| NOBTL_* | `fn_8011C000` area, label built with `strcpy("NOBTL_")` + name | | |
| FE10PersonGrowth | `fn_8011F9xx` (8011C000.c line ~2820) | | |

Table counts in the file header are read as `u32`. The game assembles them from
bytes (`b0<<24 | b1<<16 | u16`), which gives the same value. FE10PersonGrowth is
the exception: it uses a u16 count.

Common string enums (taken from DOL string compares):
- Weapon-rank strings: 12 chars, one per weapon type in the order sword, lance, axe,
  bow, knife, strike, fire, thunder, wind, light, dark, staff (`fn_801115A8`).
  The letters map to weapon EXP thresholds: `-`=0, E=1, D=31, C=71, B=121, A=181,
  S=251, `*`/SS=331. In an item's rank string, `N` means no rank (`fn_801112A8`).
- Item type (`fn_8010F73C`): sword 0, lance 1, axe 2, bow 3, knife 4, blow 5,
  fang 5, flame 6, thunder 7, wind 8, light 9, dark 10, rod 11, ballista 13,
  item 14, acc 15, card 16, elemental 17, neutral 18.
- Affinity (`fn_801194FC`): invalid -1, fire 1, thunder 2, wind 3, water 4,
  dark 5, light 6, heaven 7, telius 8 (= Earth).

## DatabaseHead (0x0)

u32 0, ptr build date string ("2007/08/22 15:25:05"), ptr author string.

## PersonData (0xc): characters, 461 records (verified)

The table is a u32 count followed by variable-length records, laid out exactly as
the loader `fn_80109DF8` walks them:

| Off | Size | Type | Field | Runtime | Conf. |
|---|---|---|---|---|---|
| 0x00 | 1 | u8 | skill count `n` | | verified |
| 0x01 | 1 | u8 | unused (always 0, the loader ignores it) | | code |
| 0x02 | 1 | u8 | base level | +0x1e | verified (Ike 11, Micaiah 1, Edward 4, Sothe 1) |
| 0x03 | 1 | u8 | female flag: if nonzero, the loader adds `SID_FEMALE` (`lbl_804CA4DC`) | | verified (code + data) |
| 0x04 | 4 | ptr | PID | +0x00 | verified |
| 0x08 | 4 | ptr | MPID (name message) | +0x04 | verified |
| 0x0c | 4 | ptr | MNPID (description message) | +0x08 | verified |
| 0x10 | 4 | ptr | FID (portrait) | +0x10 | verified |
| 0x14 | 4 | ptr | JID (default class) | +0x14 | verified |
| 0x18 | 4 | ptr | affinity string | idx at +0xe1 | verified |
| 0x1c | 4 | ptr | weapon-rank string | u16[12] at +0x32 | verified |
| 0x20 | 4·n | ptr[] | SID skills | skill list +0x4c | verified |
| +0 | 4 | ptr | extra skill (null in every record) | | code |
| +4 | 16 | ptr[4] | AID animation sets | +0xec..+0xf8 | verified (IDs) |
| +0x14 | 27 | bytes | stat block, see below | | |

The record ends at `(stat_block + 0x1e) & ~3`.

Stat block (offsets inside the 27-byte block):

| b | Type | Field | Runtime | Conf. |
|---|---|---|---|---|
| 0 | u8 | biorhythm type (0..9, 0xff for generic units) | +0xe4 | guessed |
| 1 | u8 | unknown, 0xff for generics, mostly 3 | +0xe5 | guessed |
| 2 | u8 | unknown, 0xff for generics, mostly 8 | +0xe3 | guessed |
| 3 | u8 | unknown bitmask (0/3/7/15/31) | +0xe0 | unknown |
| 4 | u8 | authority stars (Ike 3, Sanaki 4, Caineghis 5, Dheginsea 5) | +0x21 | guessed (strong) |
| 5..8 | s8×4 | laguz gauge: gain per turn, gain per battle, loss per turn, loss per battle (Tibarn 8,15,-4,-3) | +0xe8..0xeb (`fn_80119258`) | guessed (strong) |
| 9..16 | s8×8 | personal base modifiers HP Str Mag Skl Spd Lck Def Res, added to the class bases | +0x22..0x29 | verified |
| 17 | s8 | con modifier, added to class con | +0x1f | verified (Edward -3 → 7, Sothe -2 → 8) |
| 18 | s8 | unknown (always 0) | +0x20 | unknown |
| 19..26 | u8×8 | growth rates, same stat order | +0x2a..0x31 | verified |

How this was verified:
- Ike's growths 65/55/10/60/35/30/40/15 match the published RD figures.
- Ike's bases are class (Brave) bases plus personal modifiers: 38+6=44, 9+15=24,
  1+1=2, 13+15=28, 11+12=23, 0+14=14, 9+12=21, 2+5=7. This matches his RD join
  stats.
- The same holds for Micaiah (Light Mage) and Edward (Myrmidon).

## JobData (0x924c): classes, 171 records (verified)

The table is a u32 count followed by variable-length records, walked by `fn_8010A2FC`:

| Off | Size | Type | Field | Runtime | Conf. |
|---|---|---|---|---|---|
| 0x00 | 4 | ptr | JID | +0x00 | verified |
| 0x04 | 4 | ptr | MJID (name message) | +0x04 | verified |
| 0x08 | 4 | ptr | Japanese internal name (half-width kana) | +0x08 | verified |
| 0x0c | 4 | ptr | MH_J (help message) | +0x0c | verified |
| 0x10 | 4 | ptr | previous class JID (promotes from); resolved to a pointer by `fn_801192F0` | +0x10 | verified |
| 0x14 | 4 | ptr | next class JID (promotion) | +0x14 | verified |
| 0x18 | 4 | ptr | alternate class JID (laguz transformed/untransformed) | +0x18 | guessed (strong) |
| 0x1c | 4 | ptr | natural weapon IID (IID_NAIL1, IID_BEAK1, ...) | +0x1c | guessed (strong) |
| 0x20 | 4 | ptr | AID animation | +0x20 | verified (ID) |
| 0x24 | 4 | ptr | base weapon ranks (12-char) | u16[12] +0xb8, raw ptr +0xe8 | verified |
| 0x28 | 4 | ptr | max weapon ranks | u16[12] +0xd0 | verified |
| 0x2c | 1 | u8 | con | +0xf0 | verified (Brave 12, Myrmidon 10, Light Mage 5) |
| 0x2d | 2 | u8,s8 | unknown pair #0 | +0xf1/0xf2 (`fn_80119358`) | code |
| 0x2f | 2 | u8,s8 | unknown pair #1 | +0xf3/0xf4 | code |
| 0x31 | 1 | u8 | skill count `n` | | verified |
| 0x32 | 1 | u8 | class-type (SFXC) count `m` | | verified |
| 0x33 | 1 | u8 | unknown (0 or 21) | +0xfa | unknown |
| 0x34 | 1 | u8 | unknown (Thief 11, Rogue 12, armours 4, ...) | +0xf9 | unknown |
| 0x35 | 1 | u8 | movement | +0xf5 | verified (Hero 7, Myrmidon 6, Light Mage 5) |
| 0x36 | 1 | u8 | skill capacity (15/20/30/50/60) | +0xf7 | guessed |
| 0x37 | 1 | u8 | unknown (0..5, 20) | +0xf8 | unknown |
| 0x38 | 1 | u8 | unknown (always 0) | +0xf6 | code |
| 0x39 | 3 | | padding | | code |
| 0x3c | 4·n | ptr[] | SID class skills | skill list +0x24 | verified |
| +0 | 4 | ptr | extra skill (SID_SOARING, SID_ROAR, ...) | +0xb4 | code |
| +4 | 4·m | ptr[] | SFXC_* class types (used for effectiveness) | flags u16 at +0xee | verified |
| +4m+4 | 32 | u8 | caps[8], bases[8] (s8), class growths[8], promotion gains[8] (s8) | caps +0x104, bases +0xfc, growths +0x10c, promo +0x114 | verified |

The record ends at `(stat_block + 0x23) & ~3`. The loader forces the runtime Luck
base (+0x101) to 0, so the class Luck base byte is ignored. Runtime +0xfb (max
level) is computed, not stored: 40 if the class has `SID_ANIMALIZE` (laguz),
otherwise 20.

How this was verified: the caps of Myrmidon (30/20/10/20/20/30/20/10), Hero (Brave),
Vanguard (65/37/15/40/37/30/32/23), Rogue and Light Mage match the published RD
maximum-stat tables exactly. The bases were checked through the person sums above.
Class growths are not the player growths; the game presumably uses them for
generic units (guessed).

## ItemData (0xdf24): items and weapons, 296 records

The table is a u32 count followed by variable-length records (`fn_8010A958`):

| Off | Size | Type | Field | Runtime | Conf. |
|---|---|---|---|---|---|
| 0x00 | 4 | ptr | IID | +0x00 | verified |
| 0x04 | 4 | ptr | MIID (name) | +0x04 | verified |
| 0x08 | 4 | ptr | MH_I (help) | +0x08 | verified |
| 0x0c | 4 | ptr | weapon type string | idx +0x12 | verified |
| 0x10 | 4 | ptr | second type string (usually the same) | idx +0x13 | code |
| 0x14 | 4 | ptr | rank string (E..S, `*`, N) | u16 wexp +0x18 | verified |
| 0x18 | 4·3 | ptr[3] | EID effect IDs | +0x40..0x48 | verified (IDs) |
| 0x24 | 2 | u16 | icon index | +0x16 | guessed |
| 0x26 | 2 | u16 | price per use (total price = value × uses?) | +0x10 | guessed |
| 0x28 | 1 | u8 | might | +0x1c | verified (Ragnell 18) |
| 0x29 | 1 | u8 | hit | +0x1d | verified (Ragnell 80, Iron Sword 90) |
| 0x2a | 1 | u8 | crit | +0x1f | verified (Killing Edge 30, Ragnell 5) |
| 0x2b | 1 | u8 | weight | +0x1e | verified (Ragnell 20) |
| 0x2c | 1 | u8 | uses | +0x1b | verified |
| 0x2d | 1 | u8 | weapon EXP gained | +0x1a | guessed |
| 0x2e | 1 | u8 | min range | +0x20 | verified |
| 0x2f | 1 | u8 | max range | +0x21 | verified (Ragnell/Thunder 2) |
| 0x30 | 1 | u8 | unknown (1, 2, 0xff for legendary weapons) | +0x15 | unknown |
| 0x31 | 3 | | padding | | code |
| 0x34 | 1 | u8 | unknown (always 4) | +0x2c | code |
| 0x35 | 1 | u8 | attribute count `a` | | verified |
| 0x36 | 1 | u8 | effectiveness count `e` | | verified |
| 0x37 | 1 | u8 | flags: bit0 stat bonus present, bit1 growth bonus present | | verified |
| 0x38 | 4·a | ptr[] | attribute strings, turned into flag bits at +0x38/+0x3c by `fn_8010FFFC` (infinity, valuable, healing, twice, longfar, magsw, eqA, sealsteal, stormsw, ...) | | verified |
| +0 | 4·e | ptr[] | SFXC_* effective-against classes | flags at +0x0c | verified |
| +0 | 10 | s8 | (if flag bit0) bonus to HP Str Mag Skl Spd Lck Def Res Mov Con | +0x22..0x2b | verified |
| +0 | 8 | s8 | (if flag bit1) growth bonus (unused in this file) | +0x2d..0x34 | code |

The record ends at `(end + 3) & ~3`. The stat-bonus order was verified with the
stat boosters: Seraph Robe HP+7, Energy Drop Str, Spirit Dust Mag, Secret Book Skl,
Speedwing Spd, Ashera Icon Lck, Dracoshield Def, Talisman Res, Boots Mov+2, and
Statue Frag Con. Ragnell gives Def+5.

## SkillData (0x127f0): 142 records × 0x2c (fixed)

| Off | Type | Field | Conf. |
|---|---|---|---|
| 0x00 | ptr | SID | verified |
| 0x04 | ptr | MSID (name) | verified |
| 0x08 | ptr | MH_SKILL help | verified |
| 0x0c | ptr | MH2_SKILL help 2 | verified |
| 0x10 | ptr | EID effect 1 | verified (ID) |
| 0x14 | ptr | EID effect 2 | verified (ID) |
| 0x18 | ptr | IID of the skill's item (scroll/icon) | guessed |
| 0x1c | u8 | skill index (equals the record index) | verified |
| 0x1d | u8 | category? (1 normal, 2 Astra/Adept/Cure, 3 internal: HERO/FEMALE/HIGHER, Tempest/Serenity) | guessed |
| 0x1e | u8 | capacity cost | guessed |
| 0x1f | u8 | icon index (increases with record index) | guessed |
| 0x20 | u8 | entry count of list A | verified (structure) |
| 0x21 | u8 | entry count of list B | verified (structure) |
| 0x22 | u16 | unknown (always 0) | |
| 0x24 | ptr | list A: `{u8 flag, pad[3], ptr ID}`×count | verified (structure) |
| 0x28 | ptr | list B: same format | verified (structure) |

The ID lists mix SID, PID, JID and SFXC entries. For example, Adept's list A holds
SID_ADEPT plus three herons, and its list B holds SFXC_HUMAN and SFXC_ALIZE. This
looks like a "cannot learn" list (A) and a "can learn" list (B), with flag 1 for
specific IDs and 0 for class types. The meaning is guessed. Every skill also has
its own label `SID_*` in the container.

## TerrainData (0x14f20): 199 records × 0x10

The table starts with u32 0 instead of a count. The game hard-codes 199 entries
(`fn_8011D17C`).

| Off | Type | Field | Conf. |
|---|---|---|---|
| 0x00 | ptr | Japanese name (hashed by `fn_8011D17C`) | verified |
| 0x04 | ptr | MT_ message | verified |
| 0x08 | ptr | parameter block (0x2c bytes, shared between variants) | verified |
| 0x0c | u8 | terrain id | guessed |
| 0x0d | 3 | padding / unknown | |

Parameter block: [0..2] avoid, def and res bonus for set A; [3..5] the same for
set B (set B is probably fliers, since bushes give only set A); [6] heal %;
[7] flags; [8,12,16] ptr EID and two SFX IDs; [20..42] 23 move costs per movement
type (0xff = impassable). All of this is guessed except the pointers.

## BattleTerrIndex / BattleTerrName

BattleTerrIndex is a u16 terrain count (199), a u16 map count (44), then per map:
a ptr map name (`bmap00`, ...) followed by 199 × u16 indices into BattleTerrName,
where 0xffff means none. The record is padded to 404 bytes. BattleTerrName is an
array of ptrs to background names (`bg0101街`, ...). Guessed but consistent: the
records end exactly at BattleTerrName.

## ChapterData (0x24278): 60 records × 0xb4 (fixed)

The loader copies each record unchanged into a 0xb4-byte runtime struct.

| Off | Type | Field | Conf. |
|---|---|---|---|
| 0x00 | ptr | CID (`C0101`, `CFINAL`, `T01`) | verified |
| 0x04 | ptr | MCT name message | verified |
| 0x08 | ptr | map file (`bmap0101`, `lmap11`, `tutorial01`) | verified |
| 0x0c | ptr | script / dispos name | guessed |
| 0x10 | ptr | message file name (`C0406` for 0406a/b) | guessed |
| 0x14 | ptr×4 | always null | |
| 0x24 | 3 × 0x20 | per-difficulty conditions: ptr[3] MW_* win conditions, ptr[5] ML_* lose conditions. The order is probably Easy/Normal/Hard in JP terms (Normal/Hard/Maniac in the US release) | guessed |
| 0x84 | u8 | chapter number (lookup key in `fn_8010B094`), 0x50+ for tutorials | verified (code) |
| 0x85 | 3 | unknown | |
| 0x88..0x8f | u8×8 | unknown; 0x89 and 0x8a look like small counts, 0x8b is s8 (-2), 0x8c..0x8f flags | unknown |
| 0x90 | ptr | affinity string (chapter biorhythm/affinity?) | guessed |
| 0x94 | ptr | RID base room | guessed |
| 0x98 | ptr | battle background name | guessed |
| 0x9c | ptr | weather (晴れ, 曇り, 室内, 夜, ...) | guessed |
| 0xa0 | ptr | RID second room | guessed |
| 0xa4 | ptr | PID leader (Micaiah or Ike) | guessed |
| 0xa8 | 12 | unknown (always 0) | |

## Small tables

| Label | Layout | Conf. |
|---|---|---|
| DivineData (0x146c4) | u32 count 9, then {ptr affinity, u8 atk, u8 def, u8 hit, u8 avoid, u8[4]}. Fire = Atk+1 Hit+5, Earth = Avoid+15, ... | guessed (strong) |
| DivineParam (0x270fc) | u32 count 64 (8×8 affinity pairs), then {ptr aff_a, ptr aff_b, u8, u8, u16} | layout verified, meaning unknown |
| RelianceData (0x1a2b4) | supports: u32 count 71, then {ptr PID, u32 n, n×{ptr partner PID, s8 unk (0/-1), u8 unk (0..4), u16 0}}. Each person lists itself first. `fn_801198C8` stores the record pointer in person+0xdc | layout verified (ends exactly at ChapterData); field meanings guessed |
| RelianceParam (0x146b4) | 16 bytes, `32 64 96 97 0f 1e 03 05 04 01 02 02 01 00 ff fe` (C/B/A thresholds 50/100/150?) | guessed |
| GroupData (0x26cac) | u32 count 45, then {u32 id, ptr JP name, ptr MG_ message} (armies such as 暁の団) | verified |
| KiznaData (0x26ecc) | bonds: u32 count 46, then {ptr PID a, ptr PID b, u8 unk (1), u8 value (10, 5), u16 0}. The runtime iterates until a null PID | layout verified |
| 3SukumiData (0x27400) | weapon triangle: u32 count 27, then {ptr attacker type, ptr defender type, s8 damage, s8 hit, u16 0}. Sword vs axe = +1/+10, sword vs lance = -1/-10 | verified |
| GameData (0x14734) | 0x88 bytes, read as u16[68] (pairs such as 40/28, 15/15, 100/100). Probably global constants | unknown |
| BioData (0x27548) | 10 × float[4] (biorhythm curves?) | guessed |
| BioParam (0x275e8) | 5 × {float, s8[8]}, e.g. 0.8 / +10 +10 0 +10 +20 | guessed |
| NOBTL_TABLE (0x27624) | u32 22. Each `NOBTL_<NAME>` label holds {ptr owner PID}, then {ptr PID, u32 0} pairs until a null PID: characters that will not fight each other | layout verified |

## FE10Growth.cms (label FE10PersonGrowth)

The file is u16 count (375), u16 0, then 0xc-byte records {ptr PID, u8
abs_level_first, u8 abs_level_last, u16 0, ptr rows}. `rows` holds
`last-first+1` rows of 8 bytes (HP..Res), giving the absolute stats at each
absolute level (tier×20 + level). For example, Ike's first row (abs level 31 =
Hero lv 11) is 44/24/2/28/23/14/21/7.

The reader at 8011C000.c (~line 2820) indexes rows by `absolute level - first`,
clamped to `last - first`. It compares each row with person bases plus class
bases, so it is probably used for fixed/average stats, for example auto-leveled
units or FE9 save-transfer adjustment (purpose guessed; layout verified).

## Shop/shopitem_{n,h,m}.bin

These are uncompressed IS containers, one per difficulty. The labels are suffixed
with a chapter ID:
- `SHOP_PERSON_<CID>`: 4 bytes (often 01 02 03 04 or 06 06 06 00). Unknown;
  possibly a shopkeeper or portrait selection.
- `WSHOP_ITEMS_<CID>` (weapon shop) and `ISHOP_ITEMS_<CID>` (item shop):
  {ptr IID, u32 unk} pairs, terminated by a null IID. In the item shops, unk is
  often `01 nn 00 00`, which may mark limited or bargain stock (guessed).
- `FSHOP_ITEMS_<CID>` (forge): 60 × {ptr MIK_* weapon kind, ptr MDV_* material,
  ptr optional third ID}.
- `FSHOP_CARD_DATA`: u32 count 12, then {ptr MESS_FSHOP_CARDnn, 8 unknown bytes}.

## Open questions

- Person block bytes 1, 2 and 3, and the exact semantics of the biorhythm byte.
- Job bytes 0x2d..0x30 (two u8/s8 pairs), 0x33, 0x34 and 0x37.
- Item byte 0x30, whether 0x26 really is price per use, and the second type string.
- Skill list A/B semantics (flag meaning) and skill byte 0x1d.
- Chapter bytes 0x85..0x8f and the difficulty order.
- Terrain set A vs set B, and the meaning of the 23 movement-type columns.
- GameData, BioData and BioParam semantics.
