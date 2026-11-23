# Region rO (0x80065D64..0x8006C19C, 0x8006C2D0..0x800772EC)

211 of 238 functions match, 0xDFE4 of 0x11454 bytes (81%). Each file below prints MATCH with
`python3 -I tools/check_func.py <file> -v`. All names are proposed, from behaviour. Prototypes of
functions outside the region are guessed from call sites.

| File | Contents |
|---|---|
| `fn_80065D64.cpp` | Map object list: add, find, remove, save and load |
| `fn_80067168.cpp` | Move and attack range display for a unit |
| `fn_800677E4.cpp` | Cursor unit, next usable unit, chapter checks, BGM tables, music fade process |
| `fn_80068EC4.cpp` | Menu windows: scale-in, layout, frames, unit info panel |
| `fn_8006AA70.cpp` | Choice boxes and multi-line text boxes |
| `fn_8006C2D0.cpp` | Small menu getters, battle experience, level-up, window texture sets |
| `fn_8006E098.cpp` | Sprite drawing from the window texture sets |
| `fn_80075AC0.cpp` | Named data files (tag, relocation, symbols) and the global name hash |
| `fn_8006E278.cpp` | Round 11: window parts, unit panels and battle stat text (19 functions) |
| `fn_8006E610.cpp` | Round 11: main window frame, bar, range cursor, pulsing arrow (4 functions) |
| `fn_800739A4.cpp` | Round 11: weapon triangle icons with animated arrows |
| `fn_80069CE4.cpp`, `fn_8006AA70_cursor.cpp`, `fn_8006B870.cpp`, `fn_8006C794.cpp`, `fn_80066AC0.cpp` | Round 11: former near misses, each keeping the context of its neighbour file. They belong with `fn_80068EC4.cpp`, `fn_8006AA70.cpp`, `fn_8006C2D0.cpp` and `fn_80065D64.cpp` when the files are merged |
| `wip/near.cpp` | Round 4 near misses, not compiled. Stale: `fn_80069CE4`, `fn_8006AA70`, `fn_8006B870`, `fn_8006C794`, `fn_80066AC0` and `fn_80066B84` are now solved |
| `wip/near2.cpp` | Round 11 near misses: `fn_80075714` (4 to 6 of 88 words), `fn_8006D790` (blocked like `fn_8006D380`) |

Headers: `types.h`, `unit.h`, `map.h` (copied from rH; `cost` is s16, `g5` is bytes here), `trap.h`, `menu.h`.

## Subsystems and layouts

- **Map objects** (`TrapList` at `lbl_803CB770`): `traps`, 8-byte `Trap` array of 0x80; `n` at 4; string pool of
  0x200 bytes at 8, used length at 0xC. `Trap` is x, y, type, ext, then 4 bytes of type data. Bytes 2 and 3 of the
  data hold an actor handle for types 0xC (`EID_SHINEBARRIER`) and 0x15 (`EID_MASTERCROWN`). Type 7 holds an item id
  and a count, 0xA a string pool offset, 0xF a turn countdown. The add routine clears `d[6]`, which is byte 2 of the
  next entry: it looks like an original bug.
- **Menus** (`menu.h`): `MenuBase` has its vptr at +4, cols at 8, rows at 0xA, line offsets at 0x10. `Widget` (a
  process): parent 0x18, 0x2D/0x2E input locks, x/y/w/h at 0x30..0x36, cursor x/y 0x38/0x3A, menu 0x3C, child process
  ids at 0x40, count 0xA4, current 0xA6, previous 0xA7. `fn_80085EF8` turns an id into a process. Item widgets keep
  their `ItemObj` at 0x34 (same offset as w/h in the window, hence the union).
- **Battle** (`fn_8006C2D0.cpp`): `BU` is a 0x4A0-byte battle copy of a `Unit`, real unit at 0x3F0, exp gain at 0x47F,
  level-up deltas at 0x493. `Battle` holds two, then a log at 0xDE0 and flags at 0x15EC. `lbl_803C8E80` is the global
  battle. Stat deltas are logged with ids 0x32..0x3B.
- **BGM tables:** `SND_CHAPTER_GROUP_DATA`, `SND_MAP_BGM_DATA`, `SND_BATTLE_BGM_DATA`, each a count then 0x10, 0x34
  and 0x1C-byte entries, found with `fn_80077064`.
- **Data files** (`Hdr`, 0x20 bytes): body size at 4, relocation count at 8, symbol count at 0xC, a third count at 0x10,
  7-byte tag at 0x18 (`lbl_804CA3A8`, written once relocated), registered flag at 0x1F. After the body: relocation
  offsets, 8-byte symbols, a second table, strings. Relocation adds the body address to each listed word.
- **Name hash** (`lbl_803CB870`, lock at `lbl_803CD828`): 0x7EB buckets at 0xC. The bucket comes from `h*37+c`, the node
  compares `h*31+c`. Add `fn_80076D48`, find `fn_80077064`/`fn_80076F54`, remove `fn_80077174`.
- **Textures:** `Tex` is 0x24 bytes, width at 0x20, height at 0x22. Four sets at `lbl_804CB580`..`lbl_804CB58C`
  (`window/route.tpl`, `window/tut.tpl`, `window/xinfo/xinfo`, `window/always/always`).

## Caveats: matches that may not reflect the source

- `fn_8006E098` takes an explicit `Tex*`. The original almost certainly returns `Tex` by value: its callers copy the
  result (`copy = ret`), and that copy is reproduced by hand.
- All virtual slots return `int` with `(s16)` casts at the call. The real return types are probably `s16`.
- `(s8)*(u8*)&w->n` in `fn_8006ABFC`, and the `u8 cur` with `(s8)` casts everywhere, are guesses about
  signedness.
- `fn_8006D2C8` is `int` but is probably `s8` in the source.
- Declaration orders were chosen to fix registers, for example the x and y declared in reverse in `ShowMove2`.
- `const` on `fn_800682C4` exists only to move a load above the stack stores.
- `ChapterHas`, `TagOk`, `GetHdr`, `TexLoad`, `At`, `ClampY` and the rest are inferred inlines. `At` is well supported (it
  alone fixes a register swap across the whole list code), the others only reproduce the code.
- `lbl_` data is reached through invented structs (`MsgTab`, `Pos16`, `MoveState`).

- **Round 11, invented to reproduce the code:** the `f32 dead = x;` in `fn_8006F1B4`, `fn_8006F6A4` and the `q0`/`q2` in `fn_800712E8` are dead conversions that only change temp slots and hoisting. The original probably has real expressions there. The dead `d` in `fn_80073688` and the `fx`/`fy` temporaries in `fn_80069CE4` are similar.
- `Spr3Z` in `fn_8007309C` assigns a caller local inside an argument (`z = 0`), and `Spr3R` in `fn_800739A4` returns width and height through references. Both exist only to place a value or rank a register; the real source likely has one sprite inline.
- `fn_8006E098` is declared returning `Tex` by value in the new files, while `fn_8006E098.cpp` defines it with an explicit `Tex*`. The ABI is the same.
- `Spr` and `Spr3` are inferred inlines: `-1` means natural size, as `fn_8006E098` callers show. Names and parameter meanings throughout these files are proposed.
- The tables in `fn_800739A4` are written as three file statics with values copied from the game. They replace `lbl_80362250`, which the checker verifies by value.
- Declaration orders in the P blocks came from `sw.py`, `rr.py` and a grid search, and say nothing about the original.

## Skipped

Nothing was skipped as paired-single: no function in the region uses `ps_` or indexed `psq` instructions.

Nothing is left unattempted. The 27 open functions are all near misses in `wip/near.cpp` and `wip/near2.cpp`.

## Resume point

1. `fn_8006D380` and `fn_8006D790` (0x970 bytes): only the eight growth sums at the start differ. The original loads into target registers and delays the sums of 0x123, 0x126, 0x127 and 0x128. Reordering statements, `const`, and `t = p + u` against `t += u` did not reproduce it.
2. `fn_80069F14`, `fn_8006A434` (5 words each): the hoisted `0x43300000` double must get f30 and the named `f` f31. Declaration order and a loop-body inline don't move it.
3. `fn_80069220` (2 words): the `extsh` order and the registers of `dy` and `x0` work only one at a time.
4. `fn_800679EC` (2 words), `fn_80067EE8`, `fn_80067FE8` (4 words), `fn_80075714` (4 to 6 words), `fn_80076D48` (7 words).
5. `fn_8006BDCC` family and `fn_80069428`, unchanged from round 4.

## Lessons

- **A trivial accessor inline changes colouring.** `Trap* t = At(l, i)` with `At` returning `&l->traps[i]` fixed a register swap in
  every list loop that no declaration order could fix.
- **Where a value is computed affects colouring even after LICM.** Moving `x0 + ox` into the inner loop of `fn_80069220` changed the
  allocation although the code is hoisted back out. It didn't solve that function, but it's worth trying.
- **Two reads of `*s`:** `while (*s) { h = *s + h * 37; g = *s + g * 31; s++; }` gives `lbz r5; extsb. r0, r5; ...; extsb r5, r5`.
  `while ((c = *s) != 0)` gives `lbz r0; extsb. r5, r0`.
- **A constant-count byte compare written as a loop** unrolls to a chain of `li r0,0; b` exits. Written out by hand, the last test
  folds to `cntlzw`.
- **Calls nested in arguments:** a field read in an argument next to a call (`w->s3A + f() / 2`) is loaded into a saved register
  before later calls. A local copy of the field is forwarded past the calls instead.
- **Dead values can survive through a struct member:** a local `struct { u32 g; }` keeps an otherwise dead hash computed. A plain local is removed.
- **Round 11, conversion hoisting:** `lis 0x4330` at function entry appears once a function has enough int-to-float conversions, dead ones included. One dead conversion fixed the whole frame of `fn_8006F1B4`. If later slots use the same temp twice in a row, a dead conversion sits between them.
- **Round 11, stack order of paired sprites:** `Tex t0` and `Tex t` in one inline place `t0` below `t`, with the return temp above both, across many sprites.
- **Round 11, repeated sums:** `Spr3(x + mw + 8, ...)` written out each time and CSE'd by the compiler keeps the computation late. A named local computes it early. But `ix += 0x10; f(ix); ix += mw;` is needed when the register walks.
- **Round 11, `cx = x; cx += 0x20;`** schedules after an argument setup, where `cx = x + 0x20` schedules before it.
- **Round 11, return temps count as stack:** an inline that discards a by-value result still needs to return it, or all later slots shift.
- **Round 11, `Trap* const& t`** on an inline parameter swapped pointer and counter registers (`fn_80066AC0`, `fn_80066B84`).
- **Round 11, named values solve old near misses:** `Widget* it0 = ...; int c = m->cols >> 1;` in `fn_8006AA70`, `void* p = f(); u16* q = *(u16**)p;` in `fn_8006C794`, and named float arguments in `fn_80069CE4`.
- **Round 11, trust the checker:** `lib.score` masks float constants, so a score of 0 hid swapped values in `fn_80073374`, and it counts jump table labels in `fn_800739A4` as 4 false differences.

## Round 16

No new matches. Near misses saved in `wip/`:
- `r16_fn_8006CE30.cpp`: 4 of 219 words (was 156). Use `lbl_803C8DA0.x[i]` etc. directly in the clear loop (two walking pointers), then a `/*P*/` block of the ten deltas searched with `sw.py`/`rr.py`; only d2/d6 stay swapped.
- `r16_fn_8006D19C.cpp`: 14 of 75 (was 22); parameter copies plus `u8 g = ugauge + 1` fix everything but u/log.
- `r16_fn_8006BDCC.cpp`: 7 of 25; `*t++ = e++` keeps the e base, but the t base still folds.
- `fn_8006D380`/`fn_8006D790`: no `GrowOf` spelling (direct sums, loop, per-element inline, MakeG) changed the sum schedule.
- `fn_800665E4` (18 words), `fn_80066E24` (29 with the `lbl_80362198` template copied through an extern struct), `fn_80069428` (79, not sensitive to declaration order): no progress.
`fn_800776F8`/`fn_80077A58`/`fn_80077D44`/`fn_800785FC`/`fn_800787E4` sit in `rJ_800799AC/wip` and were not attempted here.

## Round 17

Not worked on this round (the session's time went to region R). The round 16 near misses in `wip/` are unchanged.

## Round 18 (functionally-equal level)

The goal changed: a function also counts when `tools/check_regs.py` prints `renamed` or `regs` (same instructions,
order, constants and references; only registers differ). Those live in `equiv/` as self-contained files. No new exact
matches here. 11 functions, 5,640 bytes:

| File (`equiv/`) | Function | Class | Bytes |
|---|---|---|---|
| `fn_800665E4.cpp` | 800665E4 (map object add) | regs | 0x384 |
| `fn_8006746C.cpp` | 8006746C | renamed | 0x120 |
| `fn_800679EC.cpp` | 800679EC | regs | 0x18C |
| `fn_80068638.cpp` | 80068638 (battle BGM entry test) | regs | 0x39C |
| `fn_80069220.cpp` | 80069220 | renamed | 0x208 |
| `fn_80069F14.cpp`, `fn_8006A434.cpp` | 80069F14, 8006A434 | regs | 0x214 each |
| `fn_8006A834.cpp` | 8006A834 | regs | 0x11C |
| `fn_8006B528.cpp` | 8006B528 | renamed | 0x214 |
| `fn_80075AC0.cpp` | 80075AC0 (data file relocate) | regs | 0xD0 |
| `fn_80076D48.cpp` | 80076D48 (name hash add) | regs | 0x20C |

Check each with `python3 -I tools/check_regs.py <file> --extra "-i src/game/rO_80065D64 -i src/game/rO_80065D64/wip"`.

How they were made: each file is its parent (`fn_80065D64.cpp`, `fn_80067168.cpp`, `fn_800677E4.cpp`,
`fn_80068EC4.cpp`, `fn_8006AA70.cpp`, `fn_80075AC0.cpp`) with every exported `fn_` body replaced by its prototype,
then `#pragma use_lmw_stmw on/off` set from the original function, then the fragment from `wip/near.cpp` unchanged.
Five of them (800665E4, 8006746C, 80069220, 80068638, 80076D48) were `other` only because the fragment had lost its
`use_lmw_stmw` pragma. The source text is the round 4/11 near miss, so the caveats above still apply to them.
`fn_8006A834` needed one change: the row y is stored through a `setY(Widget*, int)` inline; a direct `->y = h`
makes the compiler sign-extend `h` at its definition, which the original does not do.

Still `other` (left in `wip/near.cpp`, `wip/near2.cpp`, not copied):
- `fn_8006D380`, `fn_8006D790` (0x970): only the schedule of the eight growth sums differs (the original keeps the
  eighth person byte in r14 and delays four of the unit loads). A search over every order of the 16 load/add
  statements stayed at 15 instruction slots off.
- `fn_80066E24`: one branch pair is inverted (`bgt next; b ret` in the original, `ble ret; b next` here); `continue`,
  early return, a flag and a BOOL inline all gave the same or worse.
- `fn_80067EE8`, `fn_80067FE8` (a `li r29,0` three slots early), `fn_800769D0` (one `slwi` one slot early),
  `fn_80066C48`, `fn_8006758C`, `fn_80069428`, `fn_80075714`, the `fn_8006BDCC` family.
- `fn_8006C19C` is a static initialiser (`__sinit`), not attempted. `fn_800776F8`..`fn_800787E4` are being handled
  in `rJ_800799AC` (it already has `equiv/` files for three of them), so they were skipped here.
- `fn_8006CE30` and `fn_8006D19C` were already listed in `docs/EQUIVALENT.tsv` (the `wip/r16_*` files) and were not
  touched.

## Round 20 (small leftovers; `sched` and `slots` now count)

Levels as printed by `python3 -I tools/check_regs.py <file> --extra "-i src/game/rO_80065D64 -i src/game/rO_80065D64/wip"`. `sched` files were looked at with `tools/equiv/dd.py` (moved instructions are listed in each file header) and run through `tools/equiv/symcheck.py --anon`.

Totals: exact 4 functions / 532 bytes, regs 3 functions / 1152 bytes, sched 7 functions / 4924 bytes.

| Function | Class | Bytes | File | symcheck |
|---|---|---|---|---|
| 80066C48 | sched | 0xD0 | `equiv/fn_80066C48.cpp` | clean |
| 80069428 | sched | 0x40C | `equiv/fn_80069428.cpp` | clean |
| 8006D380 | sched | 0x410 | `equiv/fn_8006D380.cpp` | clean |
| 800769D0 | sched | 0x258 | `equiv/fn_800769D0.cpp` | clean |
| 8006BDCC | exact | 0x64 | `fn_8006BDCC.cpp` |  |
| 8006BE30 | exact | 0x70 | `fn_8006BDCC.cpp` |  |
| 8006BEA0 | exact | 0xC4 | `fn_8006BDCC.cpp` |  |
| 8006BF64 | exact | 0x7C | `fn_8006BDCC.cpp` |  |
| 80067EE8 | regs | 0x100 | `equiv/fn_80067EE8.cpp` |  |
| 80067FE8 | regs | 0xE8 | `equiv/fn_80067FE8.cpp` |  |
| 8006758C | sched | 0x138 | `equiv/fn_8006758C.cpp` | clean |
| 80066E24 | regs | 0x298 | `equiv/fn_80066E24.cpp` |  |
| 8006D790 | sched | 0x560 | `equiv/fn_8006D790.cpp` | flags the jump-table blocks |
| 80075714 | sched | 0x160 | `equiv/fn_80075714.cpp` | clean |

Key fact: inside `lbl_803CB7B8` the message entries (+0x50) and the entry pointer table (+0x70) are separate pooled file statics, filled through a walking pointer (`*t++ = &e[i]`). `fn_8006BDCC.cpp` (+ `.symbols.json`) matches 8006BDCC, 8006BE30, 8006BEA0 and 8006BF64 exactly. Port caveat: `sHead[0x50]` in that file stands for the statics in front of them (the widget state `fn_8006AA70.cpp` reaches through `lbl_803CB7B8`).

Shape fixes over the old drafts (same behaviour, different statement shape): 80066E24 writes the height tests as `if (!(b > h)) goto found;` (the old `if (b > h) goto next;` compiled to the inverted branch pair); 8006758C initialises `mx` and `i` after the terrain byte is cleared; 80067EE8/80067FE8 initialise the flags of `ChapterOk` after the lookup call (`ChapterOk2` in those files). No behavioural bug was found in this region's drafts.

Lessons:
- **`u8 a0 = *(u8*)&t;` instead of `t.v[0]`** made the compiler hold the first byte of a returned struct in a saved register instead of reloading it from the stack at every use (8006D790, `other` to `sched`).
- **`bgt next; b found` vs `ble found; b next`:** the first is `if (!(cond)) goto found;` falling through to `next`; the second is `if (cond) goto next;`.

Not attempted (no draft): 8006C19C, 800776F8.

## Round 21 (small functions without a draft)

Totals: sched 1 function / 432 bytes; one complete draft at `other`.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 800776F8 | sched | 0x1B0 | `equiv/fn_800776F8.cpp` | glyph advance; same lookup as fn_80077524/fn_800778A8 (rJ `fn_80077360.cpp`, same source file); symcheck clean; the two byte loads of the two-byte branch are swapped |

`wip/fn_8006C19C.cpp` (+ `.symbols.json`), `other`: static initialiser of the choice/text box unit, hand-written with pooled statics; 76 instructions against 77. All stores and the __construct_array call are right; the missing instruction is `addi r27,r29,0`: the pointer list at `lbl_8037FA70` (`{&lbl_804CB570, &lbl_804CB578, 0, 0}`) is addressed as pool base + 0 because the unit's .data pool also holds five vtables (+0x118, +0x1ac, +0x2dc, +0x370, +0x404). Getting that needs the real classes with their virtual functions so that the compiler emits the vtables; the header lists the global definitions the initialiser stands for.

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`; symcheck `--anon --xargs` clean):

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_80067FE8.cpp` | fn_80067FE8 | 0xE8 | ChapterOk2: `BOOL h = (r = 0);` puts `li r29,0` (result) before `li r4,0` (flag). Writing `r = 0;` first instead merges the branches. |
| `fn_80067EE8.cpp` | fn_80067EE8 | 0x100 | same ChapterOk2 change |
| `fn_8006746C.cpp` | fn_8006746C | 0x120 | fn_80115DEC declared with its CATALOG prototype `(Map*, s8, s8, u8, u16)` |

Tried in round 23 without an exact result (besides r23b's automatic searches, see rE NOTES):
- fn_800679EC: v as u8/s8/int, accessor, `MoveState* m` local at top or in block.
- fn_80069220: statement-move search gets 2 words (extsh r26/r27 order); permutations and placements of the three
  `(s16)` truncations don't fix it.
- fn_8006758C: declarations in a /*P*/ block + sw.py and `idx = y << 6; idx += x;` get 6 words (only the idx
  temporaries); 10 more spellings of idx.
- fn_80075714: case 1/3 statement permutations get 4 words: the `li id` always schedules first.
- fn_80069F14, fn_8006A434: magic-constant FPR rank (f31 vs f30): decl orders, conversion helper, line orders.
- fn_8006D19C: type search gets 5 (`int v`); the `clrlwi.` of v needs another shape (Lim inlines, u8 copies tried).
- fn_80069428: type search: `s16 n` + `u16 rows` reaches 7 words but u16 gives lhz/cmplwi; accessors for rows don't
  reproduce the rank.
- fn_8006CE30: all 78 pair swaps and 572 3-cycles of the 13 declarations: no change.
