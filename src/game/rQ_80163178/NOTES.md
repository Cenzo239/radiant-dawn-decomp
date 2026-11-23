# Region rQ_80163178 (0x80163178..0x8016CAEC, 0x8016CB18..0x80175E40)

89 functions match byte for byte here (0x52A0 bytes). The script pass in `src/game/auto` had already matched 72 of the region's 224, so 63 functions (0xCBE4 bytes) are left. Each file below prints `MATCH` with `python3 -I tools/check_func.py <file>`.

Shared headers: `base.h` (basic types, `Proc`, copied from rM), `types.h` (`Unit`, `Map`, `AiAct`, `AiCfg`), `common.h` (filter classes, `UnitGet`, `MapOutU`).

| File | Matches | Bytes | Contents |
|---|---|---|---|
| `fn_80163178` | 11 | 0x9E8 | Heal and retreat decisions, skill table init, phase starters |
| `fn_801658E4` | 10 | 0x850 | Fog/trap tile test, skill item dispatch, timers, small process steps |
| `fn_80165B48` | 20 | 0x1548 | Move range setup family, range marks, turn order scoring, item action dispatch |
| `fn_8016A9BC` | 1 | 0x234 | Count of enemies in a ring around a tile |
| `fn_8016D070` | 31 | 0x101C | Mode predicates, weapon table lookups, tile functors, distance helpers |
| `fn_80170F50` | 4 | 0x78C | Per-unit AI flag setup, reachable-tile marking |
| `fn_80174C2C` | 12 | 0x1144 | Nearest-target searches, whole-army AI runners |

Functions are grouped by how they were worked on, not strictly in address order, so sort them before splitting into real translation units. `wip/near.cpp` holds 26 attempts that compile but don't match. It isn't compiled.

## Subsystems and struct layouts (names guessed)

- **AI action search:** the region is the AI's "what do I do" layer. `lbl_803CA870` (`AiAct`) is the chosen action: unit 0x0, target 0x4, action 0xC, from x/y 0xF/0x10, to x/y 0x11/0x12, target tile 0x13/0x14, 0x16 is a no-move flag.
- **`lbl_804183F0` (`AiCfg`):** `flags` 0x2 (1 normal phase, 2 skip range check, 4 skip weapon pick, 8 and 0x10 are alternate phases started by `fn_80165764`..`fn_801657DC`), `op` 0x8, `res` 0x10, sorted turn order `order` 0x24 (0x80 pointers), `cursor` 0x224, `done` 0x22C.
- **Map grids are one-dimensional.** `cost` 0x710E, `cost2` 0x918E, `g4` 0xD18E, a byte view `b5S` at 0xF18E, `cur` pointer at 0x15190, `ter[0]` unit id, `ter[2]` fog, `ter[3]` flags, `ter[4]` trap. Index with `(s8)x + (s8)y * 0x40`.
- **Unit additions:** `tid` 0xFC, `flags` u64 0x108, `b117`, `w3A0` AI data id, `w3B4` AI flags (1 retreat, 4 has heal item, 0x20000/0x40000/0x80000 terrain limits, 0x7000000 skip range), `b3BC`, `h3BE` action score, `w3C0`, `m3D0` destination string (0x40 means none).
- **Items:** `item+0x12` kind, `+0x14` weapon type (0x81 heal), `+0x18` s16 power, `+0x3C` flags. An inlined null check gives 0x13 for no item.
- **Functors:** plain structs with a `lbl_` vtable at 0, unit at 4. `lbl_80387308` is "enemy", `lbl_80387338` the second filter for the search, `lbl_80387790`/`lbl_80387800` are tile visitors passed to `fn_800398E0`/`fn_80039708`. Virtual calls go through a cast to `Filter*`, slot 8 is `check(Unit*)`, slot 0xC is `at(int, x, y)`.
- **Skill tables:** `lbl_80387380` and `lbl_80387690` are `{name, item, func}` rows filled by `fn_80164CD0` and `fn_80169510`.
- **Port note:** `fn_801688D0`, `fn_801681E0` and `fn_80168558` are the MSL-style introsort used to order units, comparing `Unit+0x3AC`, and it keeps a median index in `lbl_804CA7B8`.

## Caveats: matches that may not reflect the source

- `fn_80164D18` and `fn_80164F90` read `u->w3B4` through a `volatile` cast to force two loads. The original almost certainly has no volatile.
- `SideOn`/`IsNz` and `bool x` in `fn_801739D0` reproduce a `neg; or; srwi` chain. The real source may be a different boolean helper.
- `Filt`, `F3`, `Sk0`, `Sk1`, `Lp1`, `FindSk`, `TblFind`, `InvIdx`-style inlines reproduce register patterns. Only the behaviour is checked, not that these inlines existed.
- Mixed `Map* m` and direct `lbl_803EC898.` access in one function (for example `fn_801663E0`) was chosen because it matches. It probably means an inline in the original.
- Declaration orders were picked because they match. All names are guesses, and prototypes of functions outside the region are guessed from call sites.
- `fn_80163178` calls the compiler helper as `__cvt_fp2unsigned`. The original calls `fn_8028C1A0`. That name isn't in `symbols.txt`, so the checker can't verify that one call target.
- `fn_8016CB60` uses a static-inline search that `fn_8016CC18` also inlines, so the real helper may have a different shape.

## Skipped or not attempted

- **No real paired-single math in this region:** `fn_80166720` (0xFB8), `fn_80169E30`, `fn_8016A4C8`, `fn_8017335C` and `fn_80173D10` use `psq_st`/`psq_l` only to save and restore f30 and f31, which I checked by listing every `psq`/`ps_` instruction. They are ordinary C that I did not attempt.
- **Not attempted, large:** `fn_80175444` (87 calls), `fn_8017450C`, `fn_80167704`, `fn_8016FEE8`, `fn_80171E5C`, `fn_8016B3F4`, `fn_80174014`, `fn_8016B90C`, `fn_8016F488`, `fn_8016EFC8`, `fn_8016FA34`, `fn_80171494`, `fn_8016ABF0`, `fn_80171A30`, `fn_8016BE04`, `fn_8016C21C`, `fn_8016B038`, `fn_8016C620`, `fn_80168D88`, `fn_801681E0`, `fn_80168558`, `fn_801645D8`, `fn_80165240`, `fn_80174CAC`, `fn_8016D5D4`, `fn_8016D944`, `fn_8016E9A8`, `fn_8016EBD8`, `fn_8016DF74`, `fn_80163C8C`, `fn_80169118`, `fn_80169558`.

## Resume point

1. **One or two lines away (`wip/near.cpp`):** `fn_8016CF78`, `fn_8017293C` (one `cmplw` operand order), `fn_80172494` (a `mr r3` before the branch), `fn_8016EDE8` (one temp register), `fn_80167F5C` (`lbz` before `mr r30,r3`).
2. **Register swaps only:** `fn_80172E70` (0x318, `y` and `v` swapped), `fn_80171188` (second loop's `p` and `i` swapped), `fn_80175C3C`, `fn_80167E08`, `fn_801689C8`, `fn_80168A90`, `fn_801662AC`.
3. **Same style, not tuned:** `fn_8016CDEC`, `fn_801729C0`, `fn_8016A280`, `fn_8016D27C` and its copies `fn_8016D5D4`, `fn_8016D944`, `fn_80164064`, `fn_80164330`, `fn_80169B20`, `fn_80168098`, `fn_80168BF0`, `fn_801633C0`, `fn_801635B8`, `fn_80163808`, `fn_80170664`.
4. **Spilled map pointer:** `fn_8016DC30` and `fn_8016DF74` spill `&lbl_803EC898` to the stack (`lis r0,0x803f; stw r0,0x20(r1)`). They need 18 live registers, so the local set has to be exactly right.
5. To list what's missing, subtract `build/m2c/matched_names.txt` and the checker's `OK` names from the `.fn` names in the two asm files.

## Round 12

25 more functions match (0x51F4 bytes), one file per family, each printing `MATCH`. The counts at the top of this file and the resume point above predate this round. `wip/near.cpp` still lists attempts that are now solved, so check `grep` before using it. `wip/near2.cpp` holds this round's unsolved attempts, each under `#if 0`.

| File | Matches | Contents |
|---|---|---|
| `fn_80175444` | 1 | Fullscreen image draw with cross-fade (GX setup, quad written to the FIFO) |
| `fn_8017335C` | 2 | Highest-score unit runners, `fn_8017335C`, `fn_80173D10` |
| `fn_8016CF78` | 3 | `fn_8016CF78`, `fn_8017293C`, `fn_80172494` |
| `fn_8016B038` | 1 | Attack target search in a range box |
| `fn_8016C21C` | 2 | `fn_8016C620`, `fn_8016C21C`, same search with other scores |
| `fn_80169E30`, `fn_8016A4C8` | 2 | Same search scored by HP percent |
| `fn_8016ABF0` | 1 | Best tile by `fn_8016A9BC` count |
| `fn_8016EFC8`, `fn_8016F488`, `fn_8016FA34` | 3 | Move-toward-tile family |
| `fn_8016DC30`, `fn_8016DF74` | 2 | Best tile in move range, spilled map pointer |
| `fn_8016E9A8` | 2 | `fn_8016E9A8`, `fn_8016EBD8` |
| `fn_8016D27C`, `fn_8016D5D4`, `fn_8016D944` | 3 | Safe tile search with neighbour count |
| `fn_80171A30` | 1 | Same search with a saved and restored grid |
| `fn_80172E70`, `fn_80171188` | 2 | Former register-swap near misses |

**Caveats, matches that may not reflect the source:**

- `Clr`, `Fog`, `A1`, `A2`, `SetA` and `CaseA` in `fn_80175444` exist to set stack slots. Only case 0/1 is an inline, while case 2 is written in place, which is unlikely to be how the source looked. The shared 0 is an `int z` written into colours through `*(int*)&c`. `kC0`..`kC3` are four statics where the original symbol is one 16-byte object.
- `y = Not(x)` in `fn_80172E70`, `InvAt`-style helpers, `Score`, `Tie`, `Cnt` and `CostAt` were chosen because they colour correctly.
- Mixed `Map* m` with `((Map*)&lbl_803EC898)->` and `lbl_803EC898.` access in one function controls CSE and hoisting. It probably stands for accessors in the original.
- `(s8)*(u8*)&bv->y` forces a `lbz r0` read. In `fn_8016EFC8` and its copies, `(s16)` on a `u16` grid read with an `int` local keeps a late `extsh`.
- `fn_8016ABF0` takes an unused third parameter, and `fn_8017335C` leaves `kind` uninitialised as the asm does.
- Declaration orders came from search and say nothing about the source. Names and prototypes outside the region are guesses.

**Left in this region:** `fn_80166720`, `fn_8017450C`, `fn_80174014`, `fn_80171E5C`, `fn_8016FEE8`, `fn_80167704`, `fn_8016B3F4`, `fn_8016B90C`, `fn_80171494`, `fn_8016BE04`, `fn_80163C8C`, `fn_80168D88`, `fn_801681E0`, `fn_80168558`, `fn_801645D8`, `fn_80165240`, `fn_80174CAC`, `fn_80169118`, `fn_80169558` and the smaller near misses. `fn_80174014` should be next: it is the same style with spills.

## Compiler lessons from this region

- **Manhattan distance is a macro.** `#define ABS(a) ((a) < 0 ? -(a) : (a))` with `r >= ABS(x - xx) + ABS(y - yy)`. Inside a loop, the invariant term has its negation hoisted and keeps the branch form, while the varying term becomes `srawi; xor; subf`. Mixed output like that doesn't mean two spellings. This solved about seven loops at once.
- **Grids are 1-D.** `slwi r3,r0,6` before `slwi r0,r0,7` in a preheader, with rows hoisted, comes from `a[x + y * 0x40]` on both u16 and u8 grids. Declaring 2-D arrays gives the same code except for that swap. Ghidra's `x*2 + y*0x80` is misleading.
- **Direct globals versus a local pointer.** `lbl.field` everywhere gave the original's hoisted `r31` where `Map* m = &lbl` lost the colouring fight. When the asm has `mr r3,rN` at calls and `lis`/`addi` reloads for fields, use `m` for calls and the global for fields.
- **Small `for` loops unroll in unexpected places.** A chain of `addi r3,r3,0x28; li rN,k; cmplw; beq` is `for (i = 0; i < 7; i++, q++) if (best == q) break;`.
- **`neg; or; srwi` on an already 0/1 value** survives only through `bool` conversion from an inline (`bool x = IsNz(v); x = x | w;`). A direct `x != 0` gets folded away.
- **`u32 v = *(volatile u32*)&f; f |= k;`** reproduces two loads of one field, when struct copies and plain reads get CSE'd.
- **Single-case switch:** `cmpwi r30,-1; beq L; b M` on an int parameter is `switch (x) { case -1: ...; }`. An `if` on a `u32` gives `addis; cmplwi`.
- **Inline arguments passed through:** `clrlwi. r4,r3,24; ...; bl f` with no `li r4` means `(k = g()) == 0 || f(u, k)`.

## Round 15

5 more functions match (0xB18 bytes), one file each, all `MATCH` with `--strict-references`:

| File | Bytes | Contents |
|---|---|---|
| `fn_80165240.cpp` | 0x2E8 | Staff use toward the best reachable target, with a temporary map buffer |
| `fn_801645D8.cpp` | 0x360 | Best item/staff target from a tile, scored by `fn_80157094` |
| `fn_80168D88.cpp` | 0x390 | Move toward the unit's named destination (`m3D0`) |
| `fn_80169118.cpp` | 0x13C | Spawn the cursor marker process at the chosen tile |
| `fn_80167E08.cpp` | 0x8C | Build and sort the turn order list |

Near misses added to `wip/` (new files): `fn_80174CAC.cpp` (`&lbl_803CA870` gets CSE'd into a saved register where the original rematerialises it at each call), `fn_80169558.cpp` (registers only: the Inv walker outranks the parameters; sibling of `fn_80169718`), `fn_801689C8.cpp` (one register; also `fn_80168A90`, fctiwz f0/f1 swap).

Caveats: `TmpBuf` in `fn_80165240` is a guessed RAII guard (`fn_80079150`/`fn_80079210` alloc/free). The `while (n > 0) { c = get(0); break; }` loop in the same function only reproduces the original branch shape. `u32 n` in `fn_80167E08` keeps `n` instead of `n*4` live; the real type is unknown.

**Lesson:** an allocation freed on every exit path, with the buffer handle ranked oddly low, is a guard object with a destructor. Writing it as a small struct with a constructor and destructor took `fn_80165240` from 23 lines to 0 where no declaration order helped.

## Round 17

No new matches here this round (the session went to region R). Finding for `fn_8016B3F4`/`fn_8016B90C` (near2.cpp): the two battle-side structs are copies of the templates `lbl_8036B238` (target) and `lbl_8036B228` (attacker), as in `fn_80157094`. Declared `extern const`, the copies are hoisted out of the loop and the frame grows by 0x10; plain non-const `extern Bs` keeps them in the loop with the `r30`/`r31` base registers and the right frame (0xB0), which took the copy-construction version to 51 of 326 words (registers plus the order of the two stack structs: b must be at 0x20, a at 0x30; copy construction gives the reverse, assignment gives byte copies).

## Round 18

The goal changed: a function is done when it is exact, or when `tools/check_regs.py` classes it `renamed`/`regs` (same instructions, order and references; registers differ). Functionally-equal files are in `equiv/`, one self-contained file per function (`equiv/fn_801681E0.cpp` holds the two sort instantiations).

**Exact (2, 0x54C bytes), `MATCH` with `--strict-references`:** `fn_8016BE04.cpp` (0x418), `fn_801662AC.cpp` (0x134).

**Functionally equal (16 functions, 0x26C4 bytes), all `regs` or `renamed`:**

| File in `equiv/` | Bytes | Class | Contents |
|---|---|---|---|
| `fn_80167704` | 0x704 | regs | Threat grid: strongest melee and ranged weapon of every hostile unit spread over reachable tiles, added into `g3` |
| `fn_801681E0` (+ `fn_80168558`) | 2 x 0x378 | regs | MSL-style `std::sort` over the turn-order list (by-value and by-reference comparator), one macro body |
| `fn_80163808` | 0x2E8 | regs | Healing staff on the best ally |
| `fn_80164064` | 0x2CC | regs | Move toward a unit that needs help |
| `fn_80164330` | 0x2A8 | regs | Move toward a unit carrying a healing staff |
| `fn_801635B8` | 0x250 | regs | Use the best healing item |
| `fn_8016A280` | 0x248 | regs (1 word) | Best tile to use an item on a target |
| `fn_801633C0` | 0x1F8 | regs | Better of two healing items |
| `fn_8016EDE8` | 0x1E0 | regs (3 words) | from `wip/near2.cpp` |
| `fn_80169558` | 0x1C0 | renamed | from `wip/fn_80169558.cpp` |
| `fn_8016CDEC` | 0x18C | regs (2 words) | Steal-type skill action |
| `fn_801729C0` | 0x158 | regs | Shove tile visitor |
| `fn_80169B20` | 0x150 | regs | Best of the four neighbour tiles |
| `fn_80168098` | 0x12C | renamed | Collect units for the order list |
| `fn_80175C3C` | 0xE4 | regs | from `wip/near.cpp` |

Most `equiv/` files start with the declarations of their old parent file (function bodies stripped by script), so they carry unused inlines and prototypes. Trim them when the functions move into real translation units.

**Not done (other), saved in `wip/r18/`:** `fn_80171494` (logic complete, 262 vs 282 instructions: the original has no free saved register, so it rematerialises `&lbl_803EC898` per use and spills both vtable addresses), `fn_80168BF0` (one instruction: `li r0,1` before `addi r9`).

**Not attempted or dropped:** `fn_80166720` (0xFB8), `fn_8017450C`, `fn_80174014`, `fn_80171E5C`, `fn_80163C8C`, `fn_8016B3F4`/`fn_8016B90C`, `fn_8016FEE8`, `fn_80174CAC`: all use r14..r31 with stack spills, where the spill and rematerialisation pattern depends on the exact register pressure, so "same instructions" needs nearly the same allocation. `fn_80167F5C` (argument load order), `fn_801689C8`/`fn_80168A90`, `fn_80170664` (five saved registers here, four in the original) stay as in `wip/near.cpp` and `wip/fn_801689C8.cpp`.

**Caveats:** names and prototypes are guesses. `Max` in `fn_80167704` is a guessed `std::max`. `SORT_BODY` is one macro for two template instantiations with their own statics (`lbl_804CA7B4`, `lbl_804CA7B8`); the `{ int q = 3 * len / 4; ... }` temporary only fixes scheduling. `fn_8016BE04` passes `&lbl_803EC898` to `MapOutU` while keeping a local `m`, which is what produces the original's separate `lis` register. In the `equiv/` files the mix of `m->`, `lbl_803EC898.` and `((Map*)&lbl_803EC898)->` was chosen per access to reproduce row-pointer hoisting; it has no meaning.

**Lessons:**
- **Separate `lis` register** (`lis r7,sym@ha` in the prologue, `addi r21,r7,sym@l` later): a local `Map* m = &lbl` plus `&lbl` passed directly as a pointer argument of an inline (`MapOutU(&lbl_803EC898, w)`). Solved `fn_8016BE04` and `fn_801662AC`, both open since round 12.
- **`lbzx row,(x + K)` vs `add; addis; lbz`** for the byte grid: the first comes from the cast form `((Map*)&lbl)->b5S[...]`, the second from `m->b5S[...]`; pick per function from the asm.
- **Rematerialised addresses are spills.** When a function uses all of r14..r31, the allocator rematerialises `lis/addi` at each use instead of keeping a base; with a free register the same source gives one CSE'd base. Such functions cannot reach `regs` level without the right pressure.
- **`int d = f()` for a `u16`/`u8` return** puts the `clrlwi` at the definition; a `u16 d` local leaves `mr` and extends at the use.
- **`off = off + sizeof(T)`** keeps a separate byte offset register next to a base (`add r3,base,off; stw 0x24(r3)`); `off += 4` is folded into one walking pointer.
- **sw.py can break `regs` level:** it minimises the raw word score and may change scheduling. Re-run `check_regs.py` after it and keep a backup.

## Round 20

Levels as in `docs/MATCHING.md` (`exact`, `renamed`/`regs`, `sched`); all files below are self-contained and were re-checked with `tools/check_regs.py <file> --extra "-i src/game/rQ_80163178 -i src/game/rQ_80163178/wip"`.

**New at a counted level (7 functions, 0x12F4 bytes), in `equiv/`:**

| File | Bytes | Class | Notes |
|---|---|---|---|
| `fn_80171E5C` | 0x54C | regs | New, from the disassembly. Counts filter-accepted units reachable with move plus weapon range. Uses r14..r31 with one spill, reproduced |
| `fn_8016B3F4` | 0x518 | regs | Round 12 draft fixed: the target side's struct is filled and `fn_80127520` called before the actor side's template is copied |
| `fn_8016B90C` | 0x4F4 | regs | Sibling of `fn_8016B3F4`, by text substitution after diffing the two originals |
| `fn_80167F5C` | 0x13C | sched | `wip/near.cpp` body made self-contained |
| `fn_80170664` | 0xD4 | sched | Three inlines (`Dist`, `Rng`, `Reach`) give the original's four saved registers |
| `fn_801689C8` (+ `fn_80168A90`) | 0xC8 + 0xC4 | regs + sched | `wip/fn_801689C8.cpp` with its stray `}` removed |

**Copied from `wip/` (already listed in `docs/EQUIVALENT.tsv`):** `equiv/fn_80168BF0.cpp` (0x198, sched).

The moved instructions of every `sched` file are listed in its header (looked at with `tools/equiv/dd.py`).

**Complete draft left at `other`:** `wip/r20_fn_80163C8C.cpp` (0x3D8, 242 of 246 instructions: the original spills `ux`, `uy`, `bx`, `by` as s16 slots and stores/reloads `ux`/`uy` once more around the sign extension).

**Checked, still `other`:** `wip/fn_80174CAC.cpp` (184 of 185: the original rematerialises `&lbl_803CA870` at every use and spills `x0`; ours keeps the `lis` in r16 and spills `y1`. An accessor inline, block-local pointers, `opt_propagation off`, `opt_common_subs off` and a 700-compile declaration-order search with `ps.py` changed nothing), `wip/near2.cpp` `fn_8016FEE8` (430 of 432, 76 masked lines), `wip/r18/fn_80171494.cpp` (unchanged).

**Not written:** `fn_80166720` (0xFB8), `fn_8017450C` (0x720), `fn_80174014` (0x4F8). No draft exists for these three.

**Real bugs in old drafts:** `wip/fn_801689C8.cpp` did not compile (stray closing brace). `wip/near2.cpp` `fn_8016B3F4` built both battle-side structs before `fn_80127520(v)`; the original calls it between them (order of side effects, not only registers).

**Caveats:** `fn_8016B3F4`/`fn_8016B90C` write the two templates as aggregate initialisers (the originals read `lbl_8036B238`/`lbl_8036B228` and `lbl_8036B258`/`lbl_8036B248`; values checked, `.rodata` order not reproduced), and `Do` takes `ox`/`oy` by reference only to force the reload. `fn_8016B90C` casts `fn_80108F68`'s result to unsigned. `fn_80171E5C`: `FindWpn` is faithful but odd (see the file header); the one-case `switch` and the late `Map* m` are codegen devices.

**Lessons:**
- **A struct copy scheduled after a call** means the second local is declared after the call. To keep the first-declared struct in the lower stack slot, put both in an inline (locals of an inline are laid out last-declared highest).
- **`if (x == 0) continue;` gives `bne`; a one-case `switch (x) { case 0: continue; }` gives `beq; b`.** Same for `if (m) return m;` inside an inline against `if (m == 0) {...}` in the caller.
- **A pointer local declared at the top of a function that fills r14..r31 costs a register for the whole function.** Declaring `Map* m` just before the loop that uses it gave the original's spill set at once (`fn_80171E5C`).
- **s16 spill slots (`sth`/`lha` on r1) are spilled s16 locals,** not memory variables; volatile or address-taken forms give the right loads but another frame.

## Round 21 (large functions without a draft)

Levels as in `docs/MATCHING.md`; every file below is self-contained and was re-checked with `tools/check_regs.py <file> --extra "-i src/game/rQ_80163178 -i src/game/rQ_80163178/wip"`.

**New at a counted level (1 function, 0x4F8 bytes):**

| File | Bytes | Class | Notes |
|---|---|---|---|
| `equiv/fn_80174014.cpp` | 0x4F8 | regs | New, from the disassembly. Skill-driven attack choice over all AI units; 30 words differ in registers |

**Complete drafts left at `other` (all three functions now have a full, compiling source):**

| File | Bytes | Instructions | What differs |
|---|---|---|---|
| `wip/r21_fn_80166720.cpp` | 0xFB8 | 1004 of 1006 | New. The danger grid builder. The original re-extends the damage (`clrlwi r0,rD,16`) before the `> 0xff` clamp in both write loops, adds `buf + (xx + yy * w)` in the other operand order, and spills eleven values in other slots |
| `wip/r21_fn_8017450C.cpp` | 0x720 | 458 of 456 | New. Phase fallback move. The original keeps the count table pointer `lbl_803CB860` in r30 and spills one more loop bound; ours spills the pointer and reloads it four times |
| `wip/r21_fn_8016FEE8.cpp` | 0x6C0 | 430 of 432 | The round 12 section of `wip/near2.cpp` as a self-contained file (76 masked lines, spill placement only) |

**Checked, unchanged:** `wip/r18/fn_80171494.cpp` (262 of 282). Two cheap forms tried (an accessor inline for the map height, explicit `fl & 1/2/4` locals) changed nothing: the original rematerialises `&lbl_803EC898` per use and spills both vtable addresses, the three flag tests and the two out-pointers, which needs the original's register pressure.

**What the functions do (for the port):**
- `fn_80166720(Unit* u)` rebuilds grid 8, allocates a byte buffer of map size and a saved copy of the path grid, and for every enemy that can act against `u` simulates its best melee and best ranged weapon against `u` (`fn_800269E4`, `fn_8002742C(…, 0xF)`, `fn_801586C8`). The damage is written as a per-tile maximum on the tiles within `u`'s move that the enemy can attack, then added to grid `g3` saturating at 0xFF; a last pass adds trap damage (kind 0xE objects) saturating at 0xFFFF. `fn_801658E4` is inlined five times in the original.
- `fn_8017450C` and `fn_80174014` share their frame with matched `fn_80172E70`: per-unit set-up (`m3D0[0] = 0x40`, `fn_80163010`, clear `res`, `fn_80045120`, `fn_80166720`), a score, `fn_80045548`, and the same set-up again for the winner.
- Faithful oddity in `fn_80174014`: when all four target pickers return 0 with `mode` 3 or 4 the original still reads `t->h3BE` through the null pointer; a port must skip that comparison.

**Caveats:** `fn_80166720` reads the two battle-side templates through externs `lbl_8036B0F0`/`lbl_8036B0E0` (both `{0, 0, 0, 0, 1, 0, 0}`; they must be non-const or the copies are hoisted) and the allocation tag `lbl_8036B100` (empty string) as an unsized extern; `SIM`/`OPEN` are macros only for stack layout and branch shape; `Blk` is a copy of `fn_801658E4`. `fn_80174014`: `Filt* fp` and the `u8 tx, ty` are codegen devices. `fn_8016FEE8`: the hand-stepped `xe`/`ye` are `x + r`/`y + r`.

**Lessons:**
- **A pointer local to a stack object (`Filt* fp = &f;` before the loop)** gives the original's `addi r29,r1,N` held in a saved register and took `fn_80174014` from 314 instructions to `regs` together with `u8` coordinates read late (`lbz` early, `extsb` at the call).
- **`subi r0,r3,1; cntlzw; srwi.` on a call result** is a bool-valued inline (`return (u8)f() == 1;`) tested by the caller; the test written inline gives `cmplwi; bne`.
- **`a > b` evaluates `b`'s call first:** the original's order "second weapon, then this one" with `bgt` is `Rng(p) > Rng(p2)`.
- **Battle-side structs at function level:** in a macro with block-scoped locals the first-declared struct gets the higher slot (0x50, 0x40); the same code as an inline reverses them (compare `Do` in `fn_8016B3F4`).
- **`lbl.b5S[...]` vs `m->b5S[...]`:** the direct global spelling gives the shared `add rT,rRow,rX; addis; lbz -0xe72` address that the inlined `fn_801658E4` then reuses for `ter[4]`; through the local pointer it becomes `lbzx` with a separate index.
- **A comment containing `/*P*/` ends the header comment early** and the compiler reports only "Usage Warning"; run `check_func.py` to see the real error.

## Round 24

- fn_80168BF0 (2 words): Map*/AiAct* declaration orders, assignments after the `p[0x34]` store or after IsM, direct globals instead of the locals: no gain. The one-instruction `li`/`addi` scheduling misses (fn_8008D75C, fn_80168BF0, fn_800D0BFC, fn_8018524C: the original finishes an address `addi`, or materialises a constant, one slot later or earlier than ours) are not a compiler setting: `#pragma scheduling 601/603/604/750/7400/8240/off`, `-proc 750/603e/604/7400/generic`, the GC 3.0a3..3.0a5 compilers and `-O3,p`/`-O4,s` leave them or make things worse; a same-file definition of the address target (fn_8008D91C) does not move it either.
