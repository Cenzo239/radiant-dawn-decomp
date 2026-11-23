# Region rC2_8005259C (0x8005259C..0x80063BB8)

338 of 377 functions match byte for byte, in 146 files (`fn_*.cpp`, one per run of neighbouring matched functions).
Every file prints `MATCH` with `python3 -I tools/check_func.py <file>`. The files are C++, with `extern "C"` so `fn_` names stay.

Shared headers:
- `types.h` includes the rC types and adds `u64`/`s64`.
- `decls.h` holds the structs, globals and prototypes. Prototypes are guessed from the call sites, so treat their types as provisional.
- `more.h` adds types from the second pass (`UFull`, `GetU`, `GD3`, `U5`).
- `labels.h` is generated from `symbols.txt` and declares every string label the region uses.

Near misses are in `wip/`.

## Subsystems (guessed)

- **Script-command handlers** (`ScriptCtx*`, for example `fn_80053AEC`): +4 is the command pointer, and they advance it and return 1.
- **Main-menu entries** (0x8005DB34..0x8005F9E4): each entry has a help-string getter, a name getter, a usability callback and an effect callback. The current choice is in `lbl_804CB550`, and `lbl_8037E248` is a process class whose state is at +0x40.
- **`GameData` (`lbl_803CAB38`)**: region rC calls this `FlagTable`. It has the chapter id at +0x10, play timers at +0xA0/+0xA8 (u64) and the cursor at +0x934/+0x938 (f32).
- **`Spr`** (0x68 bytes): a screen object with an inline constructor after `fn_80079150` (probably `operator new`). Base vtable `lbl_8038CB1C`, derived `lbl_8038C1C0`.

## Compiler lessons from this region

- `extrwi r3, r0, 8, 19` after `cntlzw` is `u8 f() { return x == N; }`.
- `(x & 0x8000)` on a **u64** gives `lis`/`addi` for the mask and `and.`, reading only the low word. The u32 form gives `rlwinm.`.
- `if (fn() == 0) r = 2; else r = ...; return r;` gives a different block layout from early returns (`fn_8005E9E0`).
- `switch` with `case A: break; default: return 3;` and with `default: return 3; case A: return ...;` give different layouts. Try both.
- A chain of `li r5,N; cmp; bgt end` ending in `mr r3,r5` matches a nested `int r = N; if (v <= t) { r = N-1; ... }` in an inline.
- `fn_801E6B64` takes the menu as a second argument. It looked like allocator noise because r4 just stays live.
- A `|=` with a large constant gives `oris`/`ori` when the constant is `u32`, but `or` with a hoisted `lis`/`addi` register when it is written `ULL` (`u->flags |= 0x10000dcULL`, `fn_80058094`).
- `((T*)&global)->f` and `global.member` get different registers for the hoisted base (`fn_80054194` needs `*(s16*)lbl_803CAB38.pad12`).
- `fn_8005DA9C` matches only when it is not the first function in its file, so it lives in `fn_8005DA04.cpp`.
- `if (a && b) {} else { return; }` gives the `bne ok; b end` shape (`fn_8005556C`).
- An empty functor passed by value (`Sort1 s; fn(a, b, s);`) gives the `lbz r5,0xc(r1); stb r5,8(r1)` copy (`fn_80055DE8`).
- Two loads of the same global before either test (`fn_80057CBC`) only matched with a volatile access. This may stand in for something else in the original.

## Round 11 lessons (this region)

- **Two flag lookups in a row:** the first keeps string above index in register order, the second the reverse. The second must go through a one-line by-value wrapper (`c1(g, s)`, `at1(s)`) while `flagFind`/`flagGet` take `const char* const&`. It solved `fn_80053F34`, `fn_800610F4`, and `fn_8006247C` uses the wrapper alone.
- **Inline flag test:** the rC `flagFind`/`flagGet` inlines apply here too, written with `t->hashes[i]` rather than a stepped pointer.
- **`u8 unitAt(u8 id)`** keeps the unit in the lowest saved register, where `GetU` with an int index does not.
- **`lbz r0; extsb rN,r0` next to `lbz r4; extsb r4,r4`:** the first is a `u8` field with an `(s8)` cast, the second an `s8` field. Mixed reads of one byte use `*(s8*)&u->y`.
- **`beq next; b found`** in a search loop came from `switch (flag) { case 0: break; default: goto found; }` (`fn_8005449C`).
- **Aggregate descriptors built on the stack:** `Desc d = {u, u->x, u->y, f(u), 1, 0, 1};` reproduces the `lwzu` template copy; putting both in one inline gives the right stack order (`fn_80055FB8`).
- **`s16` local for an int value:** `s16 top = (0x1f - h) >> 1;` fixed a register swap in `fn_8005D8BC`.
- **`inputBlocked`** needs two real reads of `lbl_804CB700` here, written through `volatile`.

## Round 14 lessons (this region)

- **`fn_80061AB8` is `fn_80061DD0` plus a reset,** and only matches with the shared body in an inline (`fill`), so the zero store doesn't change the loop's registers.
- **`fn_8005474C`:** `fn_80089CF4(0, n)` has a hidden second argument, the list size left in r4.
- **Explicit `fn_8028C418(t, d)`:** a plain u64 `/` emits `__div2u`, which the checker rejects by name.

## Source that may differ from the original

- **`fn_80057E2C`:** every intermediate float is a named local in a searched order, and `half` is a named 0.5f, only to get the float registers. The original was probably a few vector inlines.
- **`*(u8*)&best->y` in `fn_8005474C`** is there for the load order.

## Unmatched

Skipped as paired-single: `fn_800620A8`, `fn_80062230`.

Biggest prize: **`fn_8005B508` and its 14 copies**, plus `fn_8005D474` and `fn_80058944`, which inline the same constructor. It is still 25 of 98 words off, on the registers of -1 and 0x190. `wip/fn_8005B508.cpp` has the current best and everything tried; rounds 3 and 11 together make this expensive.

Other near misses in `wip/`: `fn_800578FC`/`fn_80057B7C` (4 words), `fn_80063A80` (7), `fn_8005586C` (10), `fn_800581F4`/`fn_8005840C` (12, 10), `fn_8005260C` (11), `fn_80054378` (14, `wip/fn_80054378_b.cpp`), `fn_80055A64` (14), `fn_80060D68` (18), `fn_80059B18` (28 of 551). `fn_8005A428` (0xAB8 bytes) looks like `fn_80059B18`. `fn_80056338`/`fn_80056B70` and `fn_800573A8` are inlined `std::sort` code on 0x24-byte elements and are likely register-only work.

`base.h` holds plain integer types for files whose local structs would clash with the shared region declarations.

`fn_80056338`, `fn_80056B70`, `fn_800573A8` and `fn_8005A428` were not attempted in round 14. The rest (mostly over 50 instructions) were not attempted. To continue, list what is missing by running the checker over every file and comparing the `OK` names against `symbols.txt`. Reading `.fn` names against the source misses functions defined through macros.

## Round 16

New matches (all pass `check_func.py --strict-references`):
- `fn_80059B18.cpp` (0x89C), deployment cursor handler. The unit-panel block is the inline `panel(fn_800677E4())`: as a plain local the unit took r31, as an inline parameter it gets r23 like the original. The `deployTile` loop compares `(s8)x == s->x` directly; named `tx`/`ty` locals swapped the y and table-base registers at every inlined copy.
- `fn_8005A428.cpp` (0xAB8), the swap-units variant, written fresh with the same helpers; `u0` comes from a ternary on the tile id (not `idUnit`), and the cancel path is a label inside the `m & 0x10` branch.
- `fn_80056338.cpp`: `fn_80056338`, `fn_80056B70` (two instantiations of one quicksort, each with its own pivot-jitter counter `lbl_804CA340`/`lbl_804CA344`) and `fn_800573A8` (median of three). The entry is `{s8 x, y; u8 c, d; int k[4]; int e, f, g, h}`: the `int k[4]` array is what gives the paired `lwz; lwz; stw; stw` copies. The comparator goes by reference to the helpers. The body is a macro rather than an inline (an inline put the parameters in the wrong ranks), with `goto end` instead of `return` for the block layout, and `#pragma auto_inline off` around `fn_80056B70` so it does not inline into itself.
- `fn_80060D68.cpp` (0x330): `x = y = c; x += 0.5f; y += 0.5f;` keeps the two sums apart (the original computes both from f30); direct `lbl_803620E4 + n` instead of a string-base local; a block-scoped second loop counter.

Tried without success: `fn_800578FC` (4 words; statement and abs orders), `fn_80063A80` (7; by-ref counter made it worse), `fn_8005260C` (11; the `&lbl_803CAB38` materialisation), `fn_800581F4`/`fn_8005840C` (11/9 with a `get2` wrapper and by-ref `mkProc`, see the wip comment; by-ref flag locals made it worse), the `fn_8005B508` family (one attempt, `wip/r16_fn_8005B508.cpp`: storing `y0` before `id = -1` gives the right `li` order, 36 words left, size still 4 bytes long).
Left: widget-constructor family (`fn_8005B508` x15, `fn_8005D474`, `fn_80058944`), `fn_80054378`, `fn_8005586C`, `fn_80055A64`, `fn_800578FC`/`fn_80057B7C`, `fn_8005260C`, `fn_80063A80`, `fn_800581F4`/`fn_8005840C`, paired-single `fn_800620A8`.

## Round 17

No new matches here. Tried:
- `fn_800578FC`: grids over accessor inlines and types (s8/int/s16/u8) for both y loads, every statement order of the four setup lines with seven abs forms, and the exact mirror of the matched `fn_800577BC` (16, worse). It stays at 4 words.
- `fn_80063A80`: accessor inlines for `a`/`k`, a `markX(a)` inline and a flattened form with `sweep(k, buf, int& i, UX*& u)` plus a full 5040-order declaration search (best 9). The wip at 7 is still the best.
- `fn_8005586C`: a named `CS* cs` for `lbl_803CA870`, declared in two places (16/12), and cast-member reads (9, wip not updated). Still 9 to 10.

## Round 19

Three functions newly at `renamed`/`regs` level (1,392 bytes), in `equiv/` (check with
`--extra "-i src/game/rC2_8005259C -i src/game/rC2_8005259C/wip"`):

| File | Function | Class | Bytes | What changed |
|---|---|---|---|---|
| `equiv/fn_8005586C.cpp` | fn_8005586C | renamed | 352 | the command state address is an explicit local pointer set before the loop (`lis r31; addi r31,r31` in one register; the compiler-hoisted form is `lis r3; addi r29,r3`) |
| `equiv/fn_800581F4.cpp` | fn_800581F4, fn_8005840C | regs | 536 + 504 | `flagGet(&lbl_803CAB38, lbl_80361F9C)` called directly (gives `lis; lbzu`), and the two flag tests as nested `if`s: with `&&` the first test branches into the second one, the original branches past it |

Looked at and left: the `fn_8005B508` family (15 x 392 bytes; `near_misses.cpp` has the right length, two pairs of
instructions are swapped with the registers of -1/0x190), `fn_8005260C` (the `&lbl_803CAB38` `addi` is still placed
before the saves; five `slotGet` shapes tried). Not attempted: `fn_80058944`, `fn_8005D474`, `fn_80063C30` to
`fn_800659B0`, `fn_80057B7C`, `fn_800620A8`.

## Round 19b (sched class, new functions)

22 functions added to `equiv/` (13,068 bytes; check with `--extra "-i src/game/rC2_8005259C -i src/game/rC2_8005259C/wip"`):

| File | Function | Class | Bytes | Notes |
|---|---|---|---|---|
| `equiv/fn_8005B508.cpp` | the fn_8005B508 family (15) | sched | 15 x 392 | `near_misses.cpp` constructor, all 15 through one macro; three constant loads (`li 0x190`, `li -1`, second vtable `addi`) a slot apart |
| `equiv/fn_8005D474.cpp` | fn_8005D474 | sched | 432 | new: same object unless the command context byte +0xC is 0x81 (one-case `switch`) |
| `equiv/fn_80058944.cpp` | fn_80058944 | sched | 948 | new: start of the sortie menu (same inlined constructor, same three moved loads) |
| `equiv/fn_80057B7C.cpp` | fn_80057B7C | regs | 320 | new: mirror of fn_800578FC (`<=`, tie-break reversed, link at +0x14) |
| `equiv/fn_80063DFC.cpp` | fn_80063DFC | regs | 1,208 | new: draw routine of the item exchange screen |
| `equiv/fn_8006436C.cpp` | fn_8006436C | regs | 1,600 | new: its input handler (first pick) |
| `equiv/fn_80064AF4.cpp` | fn_80064AF4 | sched | 1,512 | new: input handler (second pick); `subi`/`mulli` swap in the up-key block |
| `equiv/fn_800650DC.cpp` | fn_800650DC | regs | 1,168 | new: swap the two items, close gaps, recompute usable slots |

Codegen notes from the exchange screen (object `O`, table `lbl_803CB4D0[2][7]` of 0x30-byte slots):
- `1.0f / 5 * n` with the 5 converted at run time: `int total = 5;` as a local of the inline (a parameter folds to a constant).
- Search loops with the test at the top and a `b` back are `for (;; p--, i--) { if (i < 0) break; if (p->enabled) break; }`;
  `while (i >= 0 && !p->enabled)` is rotated by the compiler.
- A fixed column folds the row offset into the load (`lbz 0x17c(r6)`) only with `p = &T[0][i]; p[row * 7].enabled`;
  the current column needs `&T[row][i]` and `p->enabled`. Both spellings are in `fn_8006436C.cpp`.
- `li 1; test; bne; test; bne; li 0` kept apart from the outer flag needs nested `if`s in an inline
  (`if (!(a)) { if (!b) c = 0; }`); `&&`, `||` and early returns all merge the two flags.
- `fn(T[side][index].x, T[side][index].y + 0x28, fn_800D0864(key), o)` as one call inside an inline taking `(o, index, side, key)`
  computes the scaled indices before the inner call and loads after it.
- Unrolled constructor calls on a stack array (`ItemL t[7]` with an inline constructor that calls fn_80111B34) are a plain array of a
  class; a struct of seven members addresses them off a base register. `&t[n++]` as the call argument gives the separate byte offset.
- `li r30,0` after the first of three accessor calls: a named zero local set after the first call.

Caveats for a port:
- The item exchange files each define their own `O`, `Slot`, `Item`, `Win`, `Pad` views (as does `auto/80060000/`). `Item` has a
  constructor (fn_80111B34), destructor (fn_80111C24(this, -1)), assignment (fn_80111C78) and clear (fn_80110D38); bit 0x80 of byte +5 is a mark.
- `prevOn`/`nextOn` and `prevIn`/`nextIn` in the two input handlers are one search written two ways for addressing only.
- `equiv/fn_80058944.cpp` writes the options block through a local view `SOpt` instead of `Opt44`, and it and `fn_8005D474.cpp` copy the
  sprite constructor of `fn_8005B508.cpp`. `fn_801E5448` may take a third argument (`wip/wb.h`); the `equiv` files call it with two.
- Strings in the input handlers are real literals; they are the pool `lbl_80362168` ("MW_IPTR", "MW_ISTR", "SFX_SYS_SELECT1", "SFX_SYS_CANCEL1").

Not done: `fn_80054378`, `fn_80055A64`, `fn_800578FC`, `fn_80063A80` are already listed (wip, `regs`/`renamed`); `fn_800656BC`, `fn_800649AC`,
`fn_800642B4` are listed from `auto/80060000/wip`. `fn_8005260C`, `fn_80060D68`: unchanged (`other`).

## Round 22

| function | level | bytes | file |
|---|---|---|---|
| fn_800620A8 | exact | 164 | `fn_800620A8.cpp` |
| fn_80063C30 | exact | 460 | `fn_80063C30.cpp` |
| fn_800659B0 | regs (21 words), symcheck clean | 860 | `equiv/fn_800659B0.cpp` |

- fn_800620A8 is not paired-single code: the `psq_st`/`psq_l` only save f30/f31. It is the camera-centring tail of
  fn_80060D68 on its own.
- fn_80063C30: two flag-set loops written plainly; the original's 4x and 2x unrolling comes out by itself.
- fn_800659B0: sibling of fn_800656BC (auto/80060000/wip). `lbl_803CA870` must be declared with its real size
  (0x130), or the compiler addresses it through r13. The slot-refresh loop appears twice and is an inline;
  local declaration orders were searched (21 words left, register choice only).
- fn_80078CCC (allocator, `operator new(size, file, line)`) is called with three arguments; the m2c definition in
  auto/80070000 reads only one. CATALOG lists it as I(I).

## Round 23 (r23b)

No exact result. Tried: the fn_8005B508 family constructor with a dead base vtable store (`p->vt = 0;` first, the trick
that fixed rK fn_800CF890), all 720 orders of the first six stores (best 7 of lib score 26 but not exact), sw.py over all
33 base stores (8); fn_80063A80 with a by-reference loop counter and with the sweep inline flattened (worse);
fn_800578FC/fn_80057B7C declaration permutations (no change). Plus r23b's automatic searches (see rE NOTES).
