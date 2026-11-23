# Region rM_8014C9F8 (0x8014C9F8..0x80163164)

254 of 302 functions match byte for byte: 0x11AF4 of 0x1676C bytes (78.8%). Each of the 10 files below, and the 20 files listed under Round 13, prints `MATCH` with `python3 -I tools/check_func.py <file>`. The region has no real paired-single math, so every `psq_st`/`psq_l` here is an FP save or restore.

Shared headers: `types.h` (basic types, `Proc`, process API), `win.h` (talk window), `ai.h` (`Unit`, `Map`, AI state).

| File | Matches | Contents |
|---|---|---|
| `fn_8014C9F8` | 24 | Bit-flag helpers, banner process, fade process |
| `fn_8014D370` | 5 | Snow particles (three flakes per process) |
| `fn_8014EABC` | 20 | Fog layers, message log text ring and drawing |
| `fn_80150AC0` | 33 | Talk window: text lines, fades, page advance, GX setup, dissolve effect |
| `fn_80152274` | 9 | AI: top-level action wrappers |
| `fn_80152C20` | 13 | AI: best attack search (three variants), range helpers, terrain value, neighbour and stat bonuses |
| `fn_80158C8C` | 64 | AI script command handlers |
| `fn_8015F2DC` | 25 | AI: move bonus commands, phase procs, sub-script runners |
| `fn_80160728` | 15 | Boss script commands (`CP_*`) and their registrar `fn_80161BA4` |
| `fn_80161E04` | 19 | Target filter functors, save and restore of AI state |

`wip/near.cpp` holds 44 functions that compile but don't match yet. It isn't compiled and needs the helpers from the file named in each `from` comment. Search markers (`/*P*/`, `/*E*/`) in it are left in place for `sw.py`. Several helpers the near misses need (`ActAt`, `ActS`, `ActFlag16`, `InvRange`, `ABS`) stay defined in `fn_80158C8C.cpp`, unused for now.

## Subsystems and struct layouts (names guessed)

- **Flags:** `lbl_804CB700` is global state: bits 0..1 mean skipping, 0x800 disables the log. `lbl_804CB878` is talk state, a u32 plus a u16 at +4. `fn_8014CA64`..`fn_8014CA90` are generic clear, test, set and toggle on a u32.
- **Banner** (`lbl_80386C80` script): `str` 0x30, `id` 0x50, `x`/`y` 0x54/0x56, fade from/to/cur/len 0x58..0x5B, `alpha` 0x5C, `width` 0x5D.
- **Snow:** process with three 0x18-byte `Flake`s at 0x30: `life`, `size`, `alpha`, `x`, `y`, `vx`, `vy` (16.16 fixed), `tint`. Parameters are in `lbl_804CB88C`..`lbl_804CB8A1`.
- **Msg** (`lbl_80413F10`, 0x424C bytes): 16 0x20-byte names, a ring of 256 0x40-byte lines at 0x200 indexed by `(line + 0x100) & 0xFF`, `who` 0x4200, `cnt` 0x422C, `line` 0x4230, `col` 0x4234, `fresh` 0x4238, scroll fields 0x423A..0x423F, `alpha` 0x4240, `obj` 0x4244.
- **Win** (`win.h`): 8 `TLine*` at 0x30, each line 0x40 chars plus an end pointer. `lineH`, `rows`, `head`, `tail` at 0x50..0x53, `reveal` 0x54, rectangle 0x58..0x5E, colour 0x78, `alpha` 0x80, `bright` 0x81.
- **AI state:** `lbl_803CA870` (`AiAct`) is the chosen action: unit at 0, target at 4, action at 0xC, x/y at 0x11/0x12, script arguments at 0x18. `lbl_804183F0` (`AiCfg`) has `flags` at 2 (bit 1 means ignore the move range, bit 2 means skip AI), the result array at 0x10 and `done` at 0x22C.
- **AI commands:** `lbl_804CB8B8` points at the current 0x28-byte `AiCmd`. `a` is often a percent chance, `fl` holds options and `x` a target name. Opcodes dispatch through a binary search of the 0x52 12-byte entries in `lbl_8036A780` (`FindOp`).
- **Filters:** objects with a vtable at 0 and a unit at 4, called through +8. Commands build three and pick one: `lbl_80387308` (no name), `lbl_803872C8` and `lbl_803872B8` (name, side). `lbl_80387338` is the second filter passed to the search.
- **Map and Unit:** the layouts come from `rH_80112B48`, with AI fields added at Unit +0x390..0x3D0. `ai.h` has `costS` and `b5S`, signed views of `cost` and `g5` as in `rQ_80163178`.
- **Driver list:** `AiCfg.res[0x85]` (0x224) is the unit list cursor, `res[0x86]` (0x228) the pass number, and the list itself starts at `res[5]` (0x24).
- **Battle preview:** `lbl_803C8E80` holds two battle units, the second at +0x4A0 (`lbl_803C9320`). `fn_800269E4` takes two 16-byte argument blocks made from the templates `lbl_8036B040`/`lbl_8036B050` and, in the attack search, `lbl_80386EE0..F18`.

## Caveats: matches that may not reflect the source

- `fn_80151AA0` reads `lbl_804CB878` through a `volatile` cast to force a reload. The original almost certainly has no volatile. The cause is unknown (see the first resume item).
- `AiBest::operator=` is hand-written because it reproduces a member-wise copy with a reload. The original may be a compiler-generated copy of a class with different members.
- `(s8)*(u8*)&u->y`-style casts appear on `x` and `y` in some functions and not others. They reproduce `lbz r0; extsb r5,r0`. The real field type is unclear.
- `MapOutU`, `SideTest`/`SideB`, `Fn2Set`/`Fn4Set`, `NameIn`, `Rect4` and similar inlines reproduce register patterns. Only the behaviour is checked, not that these inlines existed. `SideTest` and `SideB` are the same code with their arguments in a different order to set the load order.
- Declaration orders and `const` on functor parameters were picked because they match. They say nothing about the source.
- `fn_8015E750` writes `f32 v = c->b; v /= 65536.0f;` to get the register. `fn_8015F524` declares `s8 v` but reads it through a `(s8)*(u8*)` cast. `fn_80155B20` calls through `(Filter*)p` because `Vis` is declared with a fake `vt` member. These reproduce the code, not necessarily the source.
- `fn_8015D290`, `fn_8015C8B8` and `fn_8015CA98` use a `cfg` local and function-level `fl` chosen by search or by target register. `fn_80158208` takes an unused fourth `int` because `fn_8015804C` passes one.
- All prototypes of functions outside the region are guessed from call sites, and all field names are guesses.
- **`fn_801534C0`** really tests the item the opposite way from its siblings: it stops at the first slot with a non-null item, where `fn_80152C20` and `fn_80153070` stop at the first empty one. This is in the machine code, and may be a bug in the original. Keep it in mind for the port.

## Skipped or not attempted

- Not attempted: `fn_80158354` (0x374, float heavy: clamps and two power calls).
- Attempted, see `wip/near3.cpp`: `fn_8014DC50`, `fn_801554B4`, `fn_8015897C`.
- To list what's missing, subtract the checker's `OK` names from the `.fn` names in `build/RFEE01/asm/auto_03_8014C9F8_text.s`.

## Resume point

Word counts are the differing words in the current `wip/near.cpp` form.

1. **`fn_8015CE40`, 3 words.** `fl` should stay in r29 in both branches, but it takes c's r31 as soon as c dies. Declaration order and block scoping don't change it.
2. **`fn_8015804C`, 3 words.** `h` should sit in u's old r29 next to `b` in r28, and it merges with `b`.
3. **`fn_80150F0C`, 9 words.** Now only the stack slots of the first colour pair differ. Wanted, low to high: arg1 copy, arg1 temp, arg2 copy, arg2 temp. See the lesson below. `fn_8014EAC4` should follow.
4. **`fn_8015897C`, 11 words:** `tx`, `ty` and `out` want r6, r5, r4. All orders of those three were tried, so try an out-of-range inline. **`fn_8015BD44`, 15 words:** the map base wants r19 and the row-plus-x temp r20. The same loop shape is in `fn_8015F07C` (38), `fn_8015B1C4` and `fn_8015FDA4`.
5. **`fn_8015F680`, 29 words:** the `PickUnit` inline fixes u's register. Left: `side` and the hoisted base swap, and a reload of `res[0x86]` in the tail. **`fn_801586C8`, about 30:** the shape is right, the ranks are wrong. **`fn_8015CC24`:** the shape is right, but `k` and `mv` should share a path (`extsh r23,r0`). **`fn_80162B54`:** the template shape works, the two blocks want swapped slots, and `f->u` should load before the second template.
6. **Six dispatchers,** `fn_80158CA0` family (0x6C0 bytes, 4 words each): the binary-search key wants r8 and `m` r6. About 36 more inline shapes for `FindOp` were tried this round, and none beat the existing form. Leave these unless a new idea turns up.
7. **Reloads with no CSE:** `fn_8015D59C` and `fn_8015DC64` reload `lbl_803CA870` where mine keeps a base register. Block-local pointers and small inlines did not stop the CSE. `fn_80151DE8`, `fn_801507EC` and the `old` read in `RunCmd` look related.
8. **Small register swaps:** `fn_8014CFEC`, `fn_8015EC54`, `fn_8015D768`, `fn_801596C0` (also wants `extsb` at the final call), `fn_8015F2DC` (10), `fn_8015F408`, `fn_8015FAF8`, `fn_80161A54`, `fn_80162F88`. `fn_80150B20` is at 5 after trying all 576 declaration and load orders, so it needs another idea.

## Round 13

27 more functions match (0x7840 bytes). Each file prints `MATCH`.

| File | Matches | Contents |
|---|---|---|
| `fn_8014CBC8` | 1 | Banner draw |
| `fn_8014E314` | 1 | Particle emitter creation with a 500-step warm-up |
| `fn_8014F288` | 1 | Load a script into the message log |
| `fn_8014FF44` | 1 | Message log draw with portraits |
| `fn_80153A74`, `fn_801540B0`, `fn_80154678`, `fn_80154C44` | 4 | Trap and map-object action searches |
| `fn_80155090` | 1 | Attack search with a named item |
| `fn_801557D0` | 1 | Lowest-level target next to a blocked tile |
| `fn_80155D2C` | 3 | Best attack tile: `fn_80155D2C`, `fn_8015639C`, `fn_80156A18` |
| `fn_80157094`, `fn_80157548`, `fn_8015797C` | 3 | Attack tile scoring variants |
| `fn_8015A6B0` | 1 | Follow-the-leader command |
| `fn_8015C018` | 2 | Best tile and item over the inventory: `fn_8015C018`, `fn_8015C468` |
| `fn_8015DE48` | 2 | Tile pick from a list: `fn_8015DE48`, `fn_8015E238` |
| `fn_8015FDA4` | 1 | Walk toward a trap tile |
| `fn_80160508` | 3 | `fn_80160508`, `fn_80160610`, `fn_801610E8` |
| `fn_801612B4` | 2 | Lowest HP target by name: `fn_801612B4`, `fn_80161684` |

**Caveats, matches that may not reflect the source:**

- `fn_8014CBC8` is a one-line wrapper around an inline copy of its body, only to rank the parameter above a local.
- Inlines passing locals by reference (`Scan` and `Sq`, `Ls`, the `Score` argument `int& ha`) exist to set register ranks. `Score` in `fn_80155D2C`, `fn_80157094` and `fn_8015797C` differs only in declaration order, so the original likely has one helper.
- `fn_8014E314` reads `40.743664f` through `extern const f32 lbl_804CE1D8` to get the operand order, and its `Find2` returns through a reference. A local `arg` computed before the `vx` divide exists only to set float registers.
- Declaration orders came from search. `fn_8012A088` is declared with an `int` argument in `fn_8015DE48.cpp` through a `#define` around the `ai.h` include, because `ai.h` says `u16`. One of the two is wrong.
- `fn_8015A6B0`, `fn_8015C018` and others name fields by offset macros or `padFC[0]` (the unit's id), since `ai.h` was left unchanged.

**Resume:** `wip/near3.cpp` has `fn_8014DC50` (12 words), `fn_801554B4` (29), `fn_8015897C` (13). The near misses in `wip/near.cpp`, resume items 1 to 8 above, were not retried with the Round 13 lessons below, except `fn_8015897C`.

## Compiler lessons from this region

- **A named local holding a global's address ranks differently from using the global directly.** Using `lbl_803C8E80` directly makes a compiler temp, and that fixed the whole `fn_80155D2C` family, including registers far earlier in the function.
- **The allocator sees pre-schedule order.** Computing a later-scheduled value earlier (`arg` before the `vx` divide) changes registers while the final instruction order stays the same.
- **Caller locals passed by reference into an inline rank below compiler temps from that inline; inline locals rank above them.** This decides most big map loops. `fn_8015C018` went from 119 to 0 with it and a block-scoped `Inv* p = &u->inv[k]`.
- **`m->x` versus `lbl.x` separates CSE.** `m->costS` with `lbl.g4` gives `add; lha` and `addis; subi; lhzx` forms. Grid all three spellings per access.
- **`s16 y = u->y;`** on an `s8` field gives `sth r0; extsh; extsb; sth`.
- **`fn_a() < (int)fn_b()` inline keeps the first result in a lower register** than a named `cost` local.
- **Float dump:** constants can be negative. Check signs with the `.float` line itself.


- **Aggregate init with one non-constant member** (`Color c = {255, 255, 255, a};`) makes an sdata2 template with 0 in that slot (`ffffff00`), copied byte by byte, with the alpha byte's load dropped. If you see `lbz` from a `lbl_` constant whose last byte is 00 or whose bytes look like colours, write the literal. Don't extern the `lbl_`.
- **A user-defined `operator=` copies member by member and reloads.** It unlocked `fn_80152C20`: the compare read `score`, and the copy read it again.
- **`u->array` versus `(u8*)u + N`:** a member array recomputes `addi rX, u, N` at each use, and the cast expression is CSE'd into a callee-saved register.
- **`__abs(x)`** emits `srawi; xor; subf`. Unlike calls, its operands evaluate left to right, so `dx + dy` with `dy` first needs temporaries.
- **`for (;;) { if (x) break; ... }`** keeps the test at the loop top. `while (!x)` moves it to the bottom.
- **Linear `add` chains:** `a = s[3] + s[4]; a += s[5]; a += s[6];` avoids the rebalancing of `a + b + c + d`.
- **`const` on a functor parameter** moves its field loads above the callee-save stores, which explains `lwz` or `lbz` right after `mflr`.
- **A `li r3,0; bnelr; ...; li r3,1` shape** comes from `r = 0; if (a && b) r = 1; return r;`, not early returns.
- **Inlined `fn(x, y)` with reversed field loads:** try swapping the inline's parameters. Loads follow argument evaluation order, last first.
- **Replacing a local in a family:** generating 20+ handlers from one template is quick once one matches, because the remaining differences are usually the order of `s` and `c`. Declaring `void* s` before `AiCmd* c` fixes every handler where `s` lives across a call.
- **Add a `cfg` local first.** `AiCfg* cfg = &lbl_804183F0;` declared first takes r31 and pushes the parameter to r30. A block-local `AiAct* act = &lbl_803CA870; Unit* u = act->unit;` gives `lis; lwz lbl@l; addi` at entry. Together these solved several handlers on the first compile.
- **`stmw` per function:** drafts without the pragma look far worse than they are. Set it from the original before reading a diff.
- **Static colours:** a `static const` pair passed by value gave the direct `lbz` loads, and moving the whole colour block into an inline fixed the second pair's slots. `extern u8` byte symbols (`lbl_804CA7A0`, `lbl_804CA7A1`, ...) give the same loads with the reference still checked.
- **Hoisted constant:** `lis r31,1; subi r0,r31,1; clrlwi r4,r0,16` at each call comes from `int k = 0x10000; f(u, k - 1);`.
- **Comparison values:** `srawi; subfc; adde` at the top of a function, tested later with `cmpwi`, means `BOOL ka = sa >= sd + 4;` computed before the first call.
- **Map grids:** use the signed members (`lbl_803EC898.costS[(s8)x + (s8)y * 0x40]`, `b5S`). Casting `(s8*)lbl.g5` hoists the wrong base.
- **Stack order across branches:** when two branches have separate frames in one order, declare all their locals at function level from the highest offset down.

## Round 17 (6 functions, 3,892 bytes)

| File | Functions |
|---|---|
| `fn_8014DC50.cpp` | 8014DC50 (particle emitter step) |
| `fn_8015CE40.cpp` | 8015CE40 (move toward a filtered target) |
| `fn_801554B4.cpp` | 801554B4 (enemy in item range from a free tile) |
| `fn_8014CFEC.cpp` | 8014CFEC (stop the banner, keep talk state) |
| `fn_8015EC54.cpp` | 8015EC54 (HP and HP percent into result slots) |
| `fn_8015F2DC_r17.cpp` | 8015F2DC (clamped move bonus; `_r17` because fn_8015F2DC.cpp holds its neighbours) |

What fixed them:
- 8014DC50: the heading as an inline `Heading(p)` with `dx` inside it (dx moved from f22 to f23), and `fa2` computed
  after the x store.
- 8015CE40: split `fl` into `fl`/`fl2`, one per branch (3 words to 0).
- 801554B4: the map read directly as `lbl_803EC898.` instead of a `Map* m` local (29 to 2), then the distance as an
  inline `Dist(u, v)` returning the sum.
- 8014CFEC, 8015EC54: one trivial accessor (`gh()` for the saved u16, `hpOf(u)`).
- 8015F2DC: `((u8*)u)[0x116] = v + ((u8*)u)[0x116];` before the `t` sum.

Caveats: the accessors, `Heading`, `Dist` and the split flag exist for register ranks. The new files copy their
parent file's declarations and inlines (from fn_80158C8C.cpp, fn_8015F2DC.cpp and near3.cpp).

Not solved: the `fn_80158CA0` dispatchers (4 words; a std::lower_bound form gave 8, 240 declaration orders and an
accessor key had no effect), fn_8015804C (3), fn_8015897C (11-13), fn_80150F0C (by-value W1 colour wrappers did not
reproduce the slot order), fn_801596C0 (64 accessor/order variants all identical), fn_80162F88 and fn_80161A54.

## Round 18 (functionally-equal level)

The goal changed: a function also counts when `tools/check_regs.py` prints `renamed` or `regs` (same instructions,
order, constants and references; only registers differ). Those live in `equiv/` as self-contained files. No new exact
matches here. 14 functions, 5,212 bytes:

| File (`equiv/`) | Function | Class | Bytes |
|---|---|---|---|
| `fn_8014D808.cpp` | 8014D808 (snow flake step) | regs | 0x1F4 |
| `fn_801516AC.cpp` | 801516AC (window fade) | regs | 0x16C |
| `fn_801520C0.cpp` | 801520C0 | regs | 0x1B4 |
| `fn_80158354.cpp` | 80158354 (expected damage of one attack; new, no earlier draft) | regs | 0x374 |
| `fn_80158CA0.cpp` .. `fn_80159244.cpp` (6 files) | 80158CA0, 80158DB8, 80158EE0, 80159008, 80159124, 80159244 (AI script dispatchers) | regs | 0x6C0 |
| `fn_8015BD44.cpp` | 8015BD44 | renamed | 0x244 |
| `fn_8015D768.cpp` | 8015D768 | regs | 0x100 |
| `fn_8015F680.cpp` | 8015F680 (AI phase: next unit) | regs | 0x178 |
| `fn_80162F88.cpp` | 80162F88 | regs | 0x54 |

Check each with `python3 -I tools/check_regs.py <file> --extra "-i src/game/rM_8014C9F8 -i src/game/rM_8014C9F8/wip"`.

How they were made: each file is its parent with every exported `fn_` body replaced by its prototype, an explicit
`#pragma use_lmw_stmw on/off` taken from the original function, then the fragment from `wip/near.cpp` unchanged
(except 8015F680 and 80158354).

- **80158354** was written from the asm. Facts a port can use: the map flags word tested with 0x100 is the low half
  of a `u64` (`rlwinm; subic; subfe`), the clamps are in place (a macro, not a by-value inline), the two `pow`
  branches for the hit rate are byte-identical in the original (both 1.5), written here as one call through a `Powf`
  inline and one direct call so the compiler does not merge them. The order of the temporaries in the two-strike
  branch came from a search and means nothing.
- **8015F680** reads the pass counter in the `switch` through a `volatile` cast. That reproduces the original's
  reload of `res[0x86]` after the test; the original source almost certainly has no volatile (same open question as
  `fn_80151AA0`).

Still `other` (left in `wip/near.cpp` and `wip/near3.cpp`): 8014D9FC, 8014EAC4, 801507EC, 80150B20, 80150F0C,
80151DE8, 8015804C, 801586C8, 8015897C, 801596C0, 8015B1C4, 8015CC24, 8015D59C, 8015DC64, 8015F07C, 8015F408,
8015F914, 8015FCAC, 80160018, 80161A54, 80161F14, 801626D4, 8016281C, 801629B4, 80162B54, 80162F04. Most are one
to three instructions scheduled a slot apart because a volatile register is reused differently (8014D9FC, 8015804C,
8015B1C4, 8015DC64, 8015F408, 801596C0, 801626D4), which the checker counts as `other`. Real shape differences:
8015F914 (`beq; blr` where every form tried gives `bnelr`), 8016281C/801629B4 (one saved register too many, so
`_savegpr` instead of four `stw`), 8014EAC4/80150F0C (colour stack slots), 801507EC/80151DE8/8015D59C (a global
reloaded where this source keeps it in a register; the volatile trick of 8015F680 is the obvious next thing to try).
8015897C has the right instructions and registers but two `addi` of different globals are swapped in the prologue.

Lessons:
- **A fragment pasted out of its parent loses the parent's `#pragma use_lmw_stmw` state.** Set it from the original
  function before judging a near miss.
- **`rlwinm; subic; subfe` on a single-bit test is a `u64` flags field**, also when the value comes from a call.
- **Dependent temporaries can be searched like declarations.** Write one `f32 t = expr;` per line and permute the
  lines; orders that use a value before its declaration fail to compile and are skipped, so only valid schedules are
  scored. 80158354 went from 18 instruction slots off to `regs` in about 900 compiles.

## Round 20 (small leftovers; `sched` and `slots` now count)

Levels as printed by `python3 -I tools/check_regs.py <file> --extra "-i src/game/rM_8014C9F8 -i src/game/rM_8014C9F8/wip"`. `sched` files were looked at with `tools/equiv/dd.py` (moved instructions are listed in each file header) and run through `tools/equiv/symcheck.py --anon`.

Totals: exact 1 functions / 144 bytes, regs 4 functions / 1380 bytes, sched 10 functions / 4328 bytes, slots 1 functions / 1052 bytes.

| Function | Class | Bytes | File | symcheck |
|---|---|---|---|---|
| 8014D9FC | sched | 0x20C | `equiv/fn_8014D9FC.cpp` | flags block 17 (instruction order there is identical; looks like a tool artefact) |
| 80161A54 | sched | 0x150 | `equiv/fn_80161A54.cpp` | clean |
| 8015804C | sched | 0x100 | `equiv/fn_8015804C.cpp` | clean |
| 8015F408 | sched | 0x11C | `equiv/fn_8015F408.cpp` | clean |
| 8015897C | sched | 0x1A0 | `equiv/fn_8015897C.cpp` | clean |
| 8015B1C4 | sched | 0x2C4 | `equiv/fn_8015B1C4.cpp` | clean |
| 8015DC64 | sched | 0x1E4 | `equiv/fn_8015DC64.cpp` | clean |
| 801626D4 | sched | 0x148 | `equiv/fn_801626D4.cpp` | clean |
| 801507EC | regs | 0x1A4 | `equiv/fn_801507EC.cpp` |  |
| 80151DE8 | regs | 0xDC | `equiv/fn_80151DE8.cpp` |  |
| 80161F14 | exact | 0x90 | `fn_80161F14.cpp` |  |
| 80162F04 | regs | 0x84 | `equiv/fn_80162F04.cpp` |  |
| 80150F0C | slots | 0x41C | `equiv/fn_80150F0C.cpp` | flags the swapped colour slots |
| 8014EAC4 | sched | 0x210 | `equiv/fn_8014EAC4.cpp` | clean |
| 8015F07C | regs | 0x260 | `equiv/fn_8015F07C.cpp` |  |
| 80162B54 | sched | 0x1D0 | `equiv/fn_80162B54.cpp` | flags the template names (kAtk/kDef vs lbl_8036B040/50) |

Complete self-contained drafts still at `other` (new `wip/*_r20.*` files; the header of each says what differs):

- `wip/fn_8015D59C_r20.cpp` (0x1CC): the original builds the address of lbl_803CA870 again (lis/addi into r3) after the fn_80152C20 call; here it is kept in a saved register across the call (2 instructions short). Direct global access, accessor inlines and differently typed second reads all keep the shared address.
- `wip/fn_801596C0_r20.cpp` (0xF8): at the fn_80160508 call the original sign-extends x and y again (extsb r5,r28; extsb r6,r27) although both reaching definitions are already extsb results; here the compiler folds them to mr. Types s8/s16/int, u8 sources, an s8-parameter inline and opt_propagation off were tried.
- `wip/fn_8015CC24_r20.cpp` (0x21C): one instruction short: after 'k = (s16)cmd->c; if (k < 0) k = fn_8012408C(u);' the original has extsh r23,r0 at the join and extsh again at the use; here only the one at the use. Same phenomenon as fn_801596C0.
- `wip/fn_8015F914_r20.cpp` (0xD4): the (flags10C & 0x18) test compiles to bnelr here; the original has beq L; blr.
- `wip/fn_8015FCAC_r20.cpp` (0xF8): the original saves one more register (r28); 2 instructions short.
- `wip/fn_80160018_r20.cpp` (0x114): different block structure around the (flags & 2) test and the fn_80163080 call (ours 71 instructions, original 69); the draft's logic there needs re-reading against the asm before a port relies on it.
- `wip/fn_801586C8_r20.cpp` (0x158): 34 words; not examined this round.
- `wip/fn_8016281C_r20.cpp` (0x198): rewritten with one running result (r = SideB; if (r) r = NameIn; if (r) r = NearT; return r), which removes the extra saved register of the old draft; left: the final 'dx + dy <= f->r' uses another compare idiom (subf/orc/srwi/subf instead of srwi/subfc/adde) and one lbz is scheduled a slot apart (103 vs 102 instructions).
- `wip/fn_801629B4_r20.cpp` (0x1A0): same as fn_8016281C with the name test negated (105 vs 104 instructions).

Port caveats to undo: `equiv/fn_801507EC.cpp` and `equiv/fn_80151DE8.cpp` read `lbl_804CB700`/`lbl_804CB878` a second time through a volatile cast (the original loads them twice back to back; the plain source is in `wip/near.cpp`). `equiv/fn_80162B54.cpp` fills the two battle-side records by word copies from two file-static templates (`kAtk`, `kDef`) declared for stack layout only. `equiv/fn_80150F0C.cpp` declares the six window colour bytes `lbl_804CA7A0..A6` as separate `u8` globals (that is what the original accesses) while `fn_80150AC0.cpp` still declares two `Color` objects there.

Real differences found in old drafts: 80162F04 had `s8 ox, oy` where the original widens in both branches (`int`); 8015F07C read the result slot index after the compare; 8016281C/801629B4 used three flags where the original threads one result through the three tests (still `other`).

Lessons:
- **A value read again after an inlined test:** let the inline take the owner (`Kind(const F* f)` reading `f->u->team`) instead of the already loaded pointer; the caller's own `me->team` is then loaded again (80161F14 exact).
- **Compound literals as arguments** (`fn((Color){0xFF,0xFF,0xFF,a}, ...)`) give one 3-byte `.sdata2` constant per argument and build-then-copy per argument, last argument first (8014EAC4). Four named locals save seven registers instead.
- **Back-to-back double loads of one sda global** (`lwz r3,g; lwz r0,g`) were only reproduced with a volatile second read; `const`, struct copies, bitfields and a `switch` do not give it.
- **Still open:** a redundant sign extension at a join (`extsb r5,r28` after both definitions were already `extsb`; 801596C0, 8015CC24). Types, casts, inline parameters and `opt_propagation off` all fold it.

## Round 21 (small functions)

Totals: renamed 1 function / 344 bytes, sched 1 / 276.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 801586C8 | renamed | 0x158 | `equiv/fn_801586C8.cpp` | the r20 draft with the two final tests written `<= 0` instead of `< 1` |
| 80160018 | sched | 0x114 | `equiv/fn_80160018.cpp` | re-read against the asm: the logic of the r20 draft was right, the shape was not; returns `u8` (the draft returned `char`, which added an extsb); the config pointer is not a local (compiler hoisting), the "decided" branch is an inline that uses the global directly; symcheck clean |

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`; symcheck `--anon --xargs` clean):

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_80151DE8.cpp` | fn_80151DE8 | 0xDC | `u32 f, s;` instead of `u32 s, f;` (a multi-name declaration is invisible to line-move searches; split it first) |

Tried in round 23 without an exact result: fn_8015804C (15 spellings incl. Bon/Pen/Half inlines and a Unit copy),
fn_80150B20 (struct copy and plain-read forms, 6-8 words vs 3).

## Round 24

Targets: the functions that keep build units from linking (docs/tu_units.tsv).

- `fn_8015F914.cpp` exact (0xD4). The original's `beq L; blr` (instead of `bnelr`) for the `flags10C & 0x18` test comes from an `||` chain: `if (u->hp == 0 || (u->flags10C & 0x18)) return;`. The last term of the `||` keeps the branch-over-blr form; a separate `if`, a `goto`, a switch or bool inlines all give `bnelr`.
- fn_8015F680 (its unit partner, 9 words, r4/r5 swapped between `side` and the hoisted `&lbl_804183F0`): side/act/u declaration orders, side read in the loop, a local `AiCfg*` base, `for(;;)`/`while(1)`/comma loop heads, no volatile: no gain.
- fn_801507EC (5): volatile `fl` read after MsgPutc, `fl` declared first, the volatile read as the call argument, a masked `fl`: no gain.
- fn_80150B20 (3 of 11): plain field copies, struct assignment, a temporary struct, Set inlines by value and by pointer, int temporaries, `__restrict`: 7-9 words (the stores through `o` serialise the loads unless they are volatile).
- fn_80158CA0 family: not retried.
- fn_8015FCAC (draft, 2 instructions short: the original keeps the base, `a`, `d` and the loop counter in four saved registers, ours lets `d` share `a`'s): an `AiCfg*` local (two positions), the counter declared at the top, `d`/`a` order, `s8 d`, Diff inlines, `d = a; d -= f()`: no change.
