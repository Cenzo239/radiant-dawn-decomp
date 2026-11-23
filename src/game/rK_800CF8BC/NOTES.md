# Region rK_800CF8BC (0x800CF8BC..0x800E1DDC)

330 of 381 functions match byte for byte: 0xD42C of 0x12520 bytes (72%). Each `.cpp` file here prints `MATCH` with `python3 -I tools/check_func.py <file> -v`.

| File | Matches | Bytes | Contents |
|---|---|---|---|
| `fn_800CF8BC.cpp` | 53 | 0x1A40 | Target-select menu, tile list, message variables and `@` expansion, movie captions |
| `fn_800D1818.cpp` | 9 | 0x7B8 | THP movie process, chapter title card |
| `fn_800D2560.cpp` | 38 | 0x19AC | Window layout parts and their parameter tweens |
| `fn_800D4528.cpp` | 36 | 0x10D8 | Menu core: draw, cursor, input, create, item list |
| `fn_800D5B4C.cpp` | 28 | 0xE78 | Battle voice lookup, unit position helpers, camera save, ring effect |
| `fn_800D7D74.cpp` | 164 | 0x6BA4 | Event script commands (see `commands.txt`) |
| `fn_800E1048.cpp` | 2 | 0xD94 | The command registrar and reset |

Shared headers: `types.h` (`Pad`, `TileList`, `Menu`, `MapSelProc`) and `menu.h` (`MenuDef`, `MenuItem`, `MenuProc`, `ItemProc`). Basic types, `Map` and `Unit` come from `rH_80112B48`.

`commands.txt` lists the 168 script commands from `fn_800E1048` with their real names and argument counts, which name most of `fn_800D7D74.cpp`. It's also the input the registrar was generated from.

## Subsystems and struct layouts (names guessed unless they come from `commands.txt`)

- **Tile list** (`TileList`, global at `lbl_803E7320`): `n`, `cur`, then 0x24-byte `TileEntry` {x, y, 1-based unit id, four pointers, left/right links}. An x of -1 ends the list.
- **Target-select process** (`MapSelProc`): +0x30 `Menu*` (vptr at +4, because of a plain base holding a counter), +0x34 float x/y, +0x3C previous and current s8 tile, +0x40/+0x44 entry under the cursor and last entry.
- **Message variables** (`lbl_803E8D28`): 0x44-byte {len, char[0x40]}. `fn_800D0BFC` expands `@@`, `@{n}` (variable) and `@[c]` (`fn_800D0B90`, 16 code-to-string getters) into a 0x800-byte ring at `lbl_803E8528`, handling Shift-JIS pairs.
- **Movie captions** (`CapProc`): +0x38 texture handle, +0x3C `Cap*` (0x14-byte entries: id and four durations in ms), +0x40 frame count. A duration is compared as `ms / 16.666666f`.
- **Window parts:** `PartH`/`PicPart` etc. {u8 type, u8 size, s16 z, vptr at +4}. Types 1 to 7 get vtables in `fn_800D43B8`. A picture has path, texture, flags (0x80 loaded, 2 has TLUT), source and destination rects, and four colours at +0x24.
- **Window process** (`WinProc`): +0x30 `Layout*`, +0x34.. animation frames/rate/current, +0x40 x, y, z, w, h, sx, sy, rot, +0x60 fence texture, +0x64 alpha, +0x65 blend. `fn_800D3D00` and `fn_800D3DA8` set and get those by a key from 0 to 10, and `fn_800D3EE0` tweens them.
- **Menu** (`MenuProc`, 0xA9 bytes): +0x30 rect, +0x3A smoothed cursor y, +0x3C `MenuDef*` (vptr at +4), +0x40 item process indices, +0xA4 count, +0xA5 state (0 live, 1 opening, 2 closing), +0xA6 cursor, +0xA7 previous, +0xA8 visible. Items are `ItemProc` with a `MenuItem*` at +0x34 (vptr at +0).
- **Option process** (`OptProc`, script `lbl_80384018`): created on demand by almost every setter through the `OptGet` inline. +0x30 is a u16 of walk flags, default 0x2C0. +0x48 is the event camera precision.
- **Wait process** `lbl_80384030`: the parent every animated command attaches to (`Get30`). Its parent is `fn_800A237C()`, or `fn_8009E898()` if that's null.
- **Colours:** `GXColor`-style 4-byte structs pass by value through a hidden pointer, including `fn_80080940`, `fn_80080508` and `fn_8023721C`.

## Round 12 (0x800CCF84..0x800CF890, 0x800E1DEC..0x800E5DE0, and leftovers)

86 more functions match, 0x691C bytes (26.3 KB). All of the region's second half is here apart from `fn_800E24F8` and `fn_800E28E4`.

| File | Matches | Bytes | Contents |
|---|---|---|---|
| `fn_800CCF84.cpp` | 12 | 0x62C | Startup and shutdown: archive load lists, reset state |
| `fn_800CE04C.cpp` | 7 | 0xA60 | Sprite sheet object: file load, palette tint, blink, three draws |
| `fn_800CEB4C.cpp` | 16 | 0xD44 | Button prompt strings per controller type |
| `fn_800D3218.cpp` | 1 | 0x184 | Layout part fade |
| `fn_800D5448.cpp` | 1 | 0x23C | Menu create |
| `fn_800D5798.cpp` | 1 | 0x164 | Menu item list build |
| `fn_800D9AC8.cpp` | 2 | 0x388 | UnitMovePos and UnitMoveRoute, with the unit lookup in place |
| `fn_800D9C80.cpp` | 3 | 0x1F4 | Number parser, camera move, map tint |
| `fn_800DC770.cpp` | 9 | 0xAEC | Hide point, UnitRescue, UnitDropOff, UnitChildSend, PostEffectColor, tile highlight |
| `fn_800E1E00.cpp` | 34 | 0x35C0 | Model process: files, language suffixes, create variants, per-frame update, matrices |

Near misses from this round: `wip/fn_800CCF84.cpp`, `wip/fn_800DC770.cpp`, `wip/fn_800E1E00.cpp`, and `wip/round12.cpp`, which holds better versions of functions in the older wip files. `fn_800D3218`, `fn_800D5448`, `fn_800D5798`, `fn_800D9AC8`, `fn_800D9C80`, `fn_800D9CE8`, `fn_800DC114` and `fn_800DC680` now match, so ignore their entries in the older wip files and the table below. `fn_800DF368` was already matched in `src/game/auto`, so it shouldn't have been listed as a near miss.

**Model process** (`ModelProc`, script `lbl_80384278`): +0x30 `ModelData*`, 0xC8 bytes: +0 `AnimHost*`, +8 s16 z, +0xB loop count, +0xE/+0xF scale and alpha percent, +0x11..+0x13 fade current, length and step, +0x18 flags, +0x1C pos, +0x40 rot, +0x4C scale, +0x58 velocity, +0x64 colour, +0x68 base matrix, +0x98/+0x9C callbacks, +0xC4 `ModelDef*`. `ModelDef`: +4 name, +8 flags (low 3 bits are the projection mode, 0x10/0x20/0x40 random rotation per axis), +0x10/+0x12 child model ids, +0x14 sound group.

**Caveats, round 12:**
- `poolOrder()` in `fn_800CCF84.cpp` and `fn_800E1E00.cpp` is not original code. It exists to set the string pool order, because some of the pool's strings belong to unmatched neighbours.
- The inline wrappers `fn_800D5798_i` and `kInl` (in `fn_800E46C4`) exist only to rank parameter registers.
- `extern lbl_804CD7D0` in `fn_800D3218` stands in for a 0.0f literal, because the literal flips the `fcmpu` operands. `lbl_804CD8F8` and `lbl_804CD91C` are externs for the same kind of reason.
- `fn_800E1EC0` writes its voice search in place with a `goto`, and `fn_800E2D8C` does the same with `subName`. The original almost certainly used inlines there.
- `setRx`/`setRy`/`setRz` declare `d` before `def` and assign separately only for register order. `fn_800E4674` needs the opposite order, because it isn't inlined.
- `holderPos` in `fn_800E5884`, `spawnRot` in `fn_800E5CA8` and `blinkDraw` in `fn_800CE240` are inline splits chosen for stack slots.
- The new files reuse whole header blocks of their parent files, so they declare more than they use.

**Next leads:** `fn_800D70F4` (2 words), `fn_800CD5F4` and `fn_800DC770` (10 and 5), `fn_800DE534` (9), `fn_800DA430` (8), then `fn_800D6EE4`, `fn_800D724C` and `fn_800D7778`, which are still not attempted. `fn_800D724C` is `fn_800D6EE4`'s loop inlined several times, so it should follow once that one matches. It needs the pool at `lbl_8036651C`.

## Near misses in `wip/`

One file per source file, each function with a comment giving the words that differ. They were cut from the compiled files by script, so they aren't compiled and use the declarations of the matching `.cpp`.

| Words | Functions | What's left |
|---|---|---|
| 1 | fn_800D5448 | `add` operands of the height sum |
| 1 | fn_800D3218 | `fcmpu` operand order against 0.0f |
| 2 | fn_800D0BFC, fn_800D9C80 | `li`/`addi` schedule; one temporary register |
| 4 to 10 | fn_800DC680, fn_800DC114, fn_800D68C0, fn_800D70F4, fn_800D194C, fn_800DE534, fn_800DADA0 | store schedule, stack slot order of by-value temporaries, or a register swap |
| 13 to 21 | fn_800DE794, fn_800D9AC8, fn_800D9CE8, fn_800DF368, fn_800DE044, fn_800DE1B8, fn_800DA430, fn_800D1D14, fn_800D1EDC, fn_800D4864, fn_800DA1FC, fn_800DF0B8, fn_800D042C | register rotation only, or close to it |
| 28 and up | fn_800D363C, fn_800D5798, fn_800D5C44, fn_800D5DC4, fn_800D306C, fn_800D9FA8, fn_800D6D10 | see below |

- fn_800D5C44 and fn_800D5DC4 need fn_800D5B4C inlined. It's too big for auto-inline, and a `static inline` copy gives the wrong stack order and registers.
- fn_800D363C has the right instructions, but the colour locals must sit below the by-value temporaries. No declaration spelling tried did that.
- fn_800D5798 is register rotation only (33 words).
- fn_800D306C builds colours as u32s stored through a local array. It's 0x10 bytes short.

## Resume point

Not attempted (20 functions, 0x1FD4 bytes). `fn_800D7778`, `fn_800D724C` and `fn_800D6EE4` are large and repetitive. Start with the commands, which have names in `commands.txt`:

`fn_800DC770` CopyMapCamera, `fn_800DC824` PastMapCamera, `fn_800DC9D4` InstantPastMapCamera, `fn_800E0394` HidePoint, `fn_800E0604` UnitRescue, `fn_800E07B0` UnitDropOff, `fn_800E0A40` UnitChildSend, `fn_800E0CDC` PostEffectColor. Then the helpers `fn_800DEF6C`, `fn_800DF250`, `fn_800DFD3C`, `fn_800E000C`, `fn_800E0024`, `fn_800E01A0`, `fn_800E02FC`, `fn_800E05BC`, `fn_800E0A08`.

## What may not reflect the original source

- All prototypes outside the region are guessed from call sites. Field and class names are mine, apart from command names.
- `BITSET`, `GLOBSET`, `TINT` and `UNIT_CHECK` are my macros for repeated code. The original probably used inlines or copies.
- `(Layout*)((u8*)q + 4)` in fn_800D339C, fn_800D40F4 and fn_800D433C is a hand-made walker that produces the right induction register. The source almost certainly indexes an array.
- `(s8)*(u8*)&x` reads in fn_800CFB4C, fn_800DBB58, fn_800DE604 and the DD/DE tile commands only force the `lbz r0; extsb` pattern. The field's signedness is unclear.
- `switch ((int)ptr)` in fn_800D7EBC exists only for the `beq; b` layout, and casts a pointer to int.
- `ItemProc::sel` is `s8` only because `(s8)(a == b)` gives `srwi` rather than `extrwi`.
- Statics `k1`, `k2`, `k0a`.. are separate 4-byte constants in place of whatever produced the original's 8- and 16-byte groups. Their values are checked. `BarTop`, `BarBottom` and `Bars`, `FenceDraw`, `MapTint`, `CamV`, `MenuH` and `OutSet` are inline splits chosen to get registers or stack slots, so they don't prove such inlines existed.
- Declaration orders in the matched functions were found by trial and say nothing about the source.
- `#pragma inline_max_size(1000)` around fn_800D5B4C in `fn_800D5B4C.cpp` is left over from an attempt and has no known basis in the original.
- fn_800DCF5C calls `fn_80290DDC(buf, fmt)` with no varargs. The format has no conversions, and the original's r5 is whatever was left there.

## Compiler lessons from this region

- **Colours pass by value.** `lbz`/`stb` runs into a stack slot followed by `addi rN,r1,slot` at a call mean a 4-byte struct passed by value. A by-value *parameter* also arrives as a pointer: `fn_800D1B4C(p, Color c, ...)` matched at once, where every pointer-parameter spelling failed.
- **Eight loads then eight stores** from a `static const` struct come from passing it by value. Assigning to a local instead gets a base register.
- **`f32 d = c->x / k; if (d <= (f32)(p->t = p->t + 1))`:** a float local before the compare fixes which of the 0x4330 constant and the pointer gets the lower register.
- **Single-case switch on a call result** gives `beq L; b end`, also for a pointer tested once.
- **`(-v | v) >> 31` with `(u8)`** gives `srawi; clrlwi` for a signed flag.
- **`fl = (v & 0xF) | (fl & 0xFFF0)`** gives `rlwinm` then `rlwimi`. A bitfield store drops the `rlwinm`.
- **`const` 8-bit mask:** `x & 0xFE` gives `rlwinm 24,30` while `x & ~1` gives `clrrwi`.
- **Struct-wide registrars:** generating the call list from the asm matched 0xD4C bytes first try.

## Round 15

3 more functions match (0xD38 bytes): `fn_800D6EE4.cpp` (`fn_800D6EE4` and `fn_800D724C`, battle effect pops for triangle attacks, guardian and support) and `fn_800D7778.cpp` (per-unit visual reset command, 0x5FC).

Caveats: `W1`/`W2`/`W3` and `X` are wrapper inlines whose only job is stack-slot depth. The colour `k` in `Sup` is a by-value copy inside the inline, and the word copy `C4 t = k` sits in the loop. `fn_800D724C_i` takes `g` and `g2` as parameters only to rank registers. `fn_800D70F4` is still 2 words off (one `li` scheduled after `addi r31`); see `wip/fn_800D70F4.cpp`. `wip/fn_800DFD3C.cpp` (tile quad draw) is registers only: the FIFO base should be r6.

Lesson: when a by-value colour copy must sit below a block-local copy on the stack, declare the byte copy as a local of the inline (`C4 k = src;`) and put the word copy in the loop (`C4 t = k;`). Later declarations in an inline get higher slots, block locals included.

## Round 17 (4 functions, 1,004 bytes)

| File | Functions |
|---|---|
| `fn_800D68C0.cpp` | 800D68C0 (camera step, zero velocity) |
| `fn_800DE534.cpp` | 800DE534 (flag every flagged map-control tile) |
| `fn_800DADA0.cpp` | 800DADA0 (unit animation by name, scale, duration) |
| `fn_800DE794.cpp` | 800DE794 (open the map event at x, y) |

What fixed them:
- 800D68C0: the zero vector built inside an inline (`CamZ2(c)`) that calls the virtual setter directly; that puts
  the vector below its by-value copy.
- 800DE534, 800DADA0: a new local for the value that the old source reassigned into a parameter (`f`, `d`).
- 800DE794: the opposite: a search over which value reuses which parameter (78 variants) found y for the flag and
  new locals for the event's x/y.

Caveats: these role choices and `CamZ2` were found by search and only reproduce the registers and slots.

Near misses: `wip/fn_800D042C_r17.cpp` (15 of 215, was 21; pv/nx locals fix the modulo order, the loop counter,
base and count rotate among r9..r11). The turn family fn_800DA430/fn_800D9FA8/fn_800DA1FC did not move with
parameter-role searches, by-reference TurnFrames or wrappers. fn_800DFD3C: union, pointer and struct-colour FIFO
spellings all keep the FIFO base in r5. The fn_800D1818 trio (18 words each) wants the name string lowest; passing it
as const& or re-reading p->name did not help.

## Round 18 (goal changed: exact, or functionally equal in `equiv/`)

From this round a function is done at one of two levels: exact (`check_func.py --strict-references` prints MATCH, file in this folder) or functionally equal (`check_regs.py <file> --extra "-i src/game/rK_800CF8BC -i src/game/rK_800CF8BC/wip"` prints `renamed` or `regs`, file in `equiv/`). Every `equiv/` file compiles on its own: it is the parent file's helper block with the exported bodies turned into prototypes, plus the function.

Exact (1 function, 512 bytes): `fn_800D194C.cpp` (movie process draw). The old 10-word miss was the stack order of the two bar colours; a wrapper around `BarTop` (`BarTopW`) fixed it.

Functionally equal (14 functions, 6,608 bytes):

| File | Class | Bytes | Source |
|---|---|---|---|
| `equiv/fn_800D042C.cpp` | regs | 0x35C | `wip/fn_800D042C_r17.cpp` plus a local inline copy of fn_800CFCB4 |
| `equiv/fn_800DA1FC.cpp` | regs | 0x234 | `wip/fn_800D7D74.cpp` |
| `equiv/fn_800E24F8.cpp` | renamed | 0x234 | `wip/fn_800E1E00.cpp` with the two name buffers declared in the other order |
| `equiv/fn_800CD5F4.cpp` | regs | 0x200 | `wip/fn_800CCF84.cpp` |
| `equiv/fn_800DA430.cpp` | regs | 0x1EC | `wip/round12.cpp` |
| `equiv/fn_800D1D14.cpp`, `fn_800D1EDC.cpp` | regs | 0x1C8 each | `wip/fn_800D1818.cpp` |
| `equiv/fn_800D4864.cpp` | regs | 0x1AC | `wip/fn_800D4528.cpp` |
| `equiv/fn_800DF0B8.cpp` | renamed | 0x198 | `wip/fn_800D7D74.cpp` |
| `equiv/fn_800E28E4.cpp` | regs | 0x194 | `wip/fn_800E1E00.cpp`, shake copy declared first and copied as words |
| `equiv/fn_800D5C44.cpp` | regs | 0x180 | `wip/fn_800D5B4C.cpp` plus a local inline copy of fn_800D5B4C |
| `equiv/fn_800DE044.cpp`, `fn_800DE1B8.cpp` | regs | 0x174, 0x16C | `wip/fn_800D7D74.cpp` |
| `equiv/fn_800D70F4.cpp` | renamed | 0x158 | `wip/fn_800D5B4C.cpp` |

Still class `other`: 800D9FA8 (one prologue `mr` placed differently; both wip versions and all six wrapper parameter orders), 800D0BFC (`li r28,0x40` scheduled one instruction late), 800D363C (the two fence colours must sit below the argument copies; in-place body, parameters and function-level locals all tried), 800DC770 (`fctiwz` order), 800DC824 and 800DC9D4 (missing `frsp`, 12 bytes short), 800D5DC4 (right size with inline copies of fn_800D5B4C and fn_800D5C44, but the block order differs), 800D306C, 800D6D10, 800DFD3C (`li r3,-1` scheduled late), `wip/r18_fn_800CF890.cpp` (11-instruction static initialiser; the two address loads come out in the other order).

Caveats for a port:
- `fn_800CFCB4_i` and `fn_800D5B4C_i` are local `static inline` copies of matched functions that the original inlines. A port should call the real ones.
- `fn_800E28E4`: `*(VW3*)&t = *(VW3*)&v` and the early declaration of `t` only reproduce a word copy at the original stack slot; the source most likely has `Vec t = v;`.
- `BarTopW` in `fn_800D194C.cpp` and the buffer order in `fn_800E24F8` are stack-slot fixes.

Lessons:
- A fragment that comes out much shorter than the original usually calls a neighbour the original inlined. Removing the exported bodies from the parent removes that inlining; put the callee back as a `static inline` copy (three functions, 1.5 KB).
- Stack slot swaps are cheap at this level: swap two declarations (name buffers), wrap the earlier sibling inline once more (bar colours), or declare the later copy first.

## Round 20 (small leftovers; `sched` and `slots` now count)

Levels as printed by `python3 -I tools/check_regs.py <file> --extra "-i src/game/rK_800CF8BC -i src/game/rK_800CF8BC/wip"`. `sched` files were looked at with `tools/equiv/dd.py` (moved instructions are listed in each file header) and run through `tools/equiv/symcheck.py --anon`.

Totals: sched 2 functions / 628 bytes.

| Function | Class | Bytes | File | symcheck |
|---|---|---|---|---|
| 800DC770 | sched | 0xB4 | `equiv/fn_800DC770.cpp` | clean |
| 800D0BFC | sched | 0x1C0 | `equiv/fn_800D0BFC.cpp` | clean |

Complete self-contained drafts still at `other` (new `wip/*_r20.*` files; the header of each says what differs):

- `wip/fn_800DC824_r20.cpp` (0x1B0): incomplete: the camera look-at copy block (22 instructions, lwz/stw into a stack Vec then stfs to +0x38..0x4c with frsp) is missing; camSet is empty in the old draft. Not a usable source for that part.
- `wip/fn_800DC9D4_r20.cpp` (0x100): incomplete, same missing look-at copy block as fn_800DC824.
- `wip/fn_800D306C_r20.cpp` (0x1AC): the original stores the four packed colours to four locals (0x18..0x24, dead stores) and then to the argument copies; here only the argument copies (frame 0x50 vs 0x60, 103 vs 107 instructions).
- `wip/fn_800D5DC4_r20.cpp` (0x1A8): incomplete: 28 vs 106 instructions, the old fragment does not contain the body.
- `wip/fn_800D6D10_r20.cpp` (0x168): 91 vs 90 instructions; the original saves r25 and up (two more registers), a few loads are scheduled differently.

Not attempted: 800D363C and 800D9FA8 (old fragments no longer compile against their parents).
`wip/fn_800DC824_r20.cpp`, `wip/fn_800DC9D4_r20.cpp` and `wip/fn_800D5DC4_r20.cpp` are incomplete sources (missing blocks, see their headers); a port must not use them as they are.

## Round 21 (small functions and the incomplete sources)

Checked with `python3 -I tools/check_regs.py <file> --extra "-i src/game/rK_800CF8BC -i src/game/rK_800CF8BC/wip"`.

Totals: exact 1 function / 596 bytes, slots 2 / 1172.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 800D9FA8 | exact | 0x254 | `fn_800D9FA8.cpp` | locals declared `fl, a, u` with a separate flag variable; only matches as an inline called from a one-line wrapper |
| 800D363C | slots | 0x2EC | `equiv/fn_800D363C.cpp` | the two colour locals and the by-value temporaries sit in other slots; symcheck flags 3 blocks, explained in the header |
| 800D5DC4 | slots | 0x1A8 | `equiv/fn_800D5DC4.cpp` | now complete: fn_800D5C44 and fn_800D5B4C as inline copies; four Vec temporaries rotated; symcheck flags 9 blocks, explained in the header |

The incomplete sources are complete now, still `other`:
- `wip/fn_800DC824_r21.cpp`, `wip/fn_800DC9D4_r21.cpp`: the camera look-at block is `cam->v44 = v;` followed by the same point stored to `cam->v38` through a double-typed path. The original has three `frsp` there (105 against 108 instructions in DC824, 61 against 64 in DC9D4); this compiler removes the float-double-float round trip for double parameters, long double, a double-returning inline, `opt_propagation off` and a double temporary struct. Behaviour is the same (frsp of a single is the identity). The `_r20` files are superseded.

The same declaration order (`fl, a/d2, u`) probably takes `equiv/fn_800DA430.cpp` and `equiv/fn_800DA1FC.cpp` from regs to exact; not tried (outside this round's list).

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`; symcheck `--anon --xargs` clean):

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_800DA430.cpp` | fn_800DA430 | 0x1EC | the turn duration `d2` typed `u32` instead of `int` (type search over locals) |
| `fn_800CF890.cpp` | fn_800CF890 | 0x2C | static initialiser: inline base constructor with the dead vtable store `o->vt = 0;` before the derived store (the round-22 `__sinit` lesson) |

Tried in round 23 without an exact result: fn_800DC770 (tx/ty locals and 60 orders, worse), fn_800D0BFC (24 case orders,
MsgVar spellings, `'@'` vs `0x40`).

## Round 24

- fn_800D0BFC (2 words): an explicit `MsgVar*` table local (four positions, worse), `'@'` as a char/int local, split `start`, `for(;;)`: no change. The one-instruction `li`/`addi` scheduling misses (fn_8008D75C, fn_80168BF0, fn_800D0BFC, fn_8018524C: the original finishes an address `addi`, or materialises a constant, one slot later or earlier than ours) are not a compiler setting: `#pragma scheduling 601/603/604/750/7400/8240/off`, `-proc 750/603e/604/7400/generic`, the GC 3.0a3..3.0a5 compilers and `-O3,p`/`-O4,s` leave them or make things worse; a same-file definition of the address target (fn_8008D91C) does not move it either.
