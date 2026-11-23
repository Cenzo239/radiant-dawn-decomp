# Round 15 (b): 0x801A0000..0x801D09F8

8 functions, 6,060 bytes.

| file | function | bytes | what it is |
|---|---|---|---|
| fn_801C5874.cpp | 801C5874 | 1,984 | biorhythm page draw (unit info) |
| fn_801BD780.cpp | 801BD780 | 1,952 | window frame with optional tab, tiled from fn_801BD170/fn_801BD2EC |
| fn_801A39AC.cpp | 801A39AC | 1,520 | illustration room grid: page up/down input |
| fn_801AEB78.cpp | 801AEB78 801AEDC4 | 192, 216 | trial menu title sprintf (two modes) |
| fn_801D087C.cpp | 801D087C 801D08E4 | 104, 92 | push/pop under an interrupt guard |

fn_801C5874 passes `--strict-references` only with `--symbol-map fn_801C5874.symbols.json`
(the map `cnt$765 -> lbl_804CB9EC` was added by someone else during the pause, and the file was edited after I filed it; it still matches).

## What unlocked these

- **A function-local `static int` instead of an extern global fixes scheduling.** fn_801C5874's frame counter `lbl_804CB9EC` as an `extern int` kept the load after the register saves and the `lfs` loads ahead of it. As `static int cnt;` inside the function, the scheduler treats it as non-aliasing and the prologue order matched at once. `if (cnt == 30) cnt = 0; else cnt++;` then gave the right registers (the ternary swapped r5/r6).
- **Real string literals under `pool_strings` fixed the sprintf pair.** fn_801AEB78/fn_801AEDC4 had stalled for rounds with `lbl_8036D68C + off`; with the pool (dumped from the DOL in order into a `StringPool` dummy) and the nested-call form `f(buf, fmt, g1(), s("A"), g2(), s("B"), ...)` both matched on the first compile.
- **Expanded inlines with caller-level locals for volatile registers too.** fn_801A39AC's scroll loops matched only after `ScrollTo` was a macro whose `o`, `a`, `v` are function-level locals of the enclosing inline, searched with `sw.py file fn Clamp` (the third argument picks the function holding the `/*P*/` block).
- **`while ((o = lbl)->sel / 3 - d->scroll <= 0.0f && ...)`** keeps one global load per test reused by the body. The comma form `while (o = lbl, ...)` materialises a flag.
- **Loop-condition variable for a later CSE:** `while ((sl = lbl->sel) / 3 ...)` with `p = lbl;` in the body, and `k = sl - ...` after the loop, reproduces a value kept in a register across the loop exit while the global itself is reloaded.
- **Interrupt guard:** a struct with a constructor storing the vtable `lbl_80380F00` then `OSDisableInterrupts()`, and a destructor storing it again before `OSRestoreInterrupts`, matched fn_801D087C/fn_801D08E4 directly (same as `IGuard` in fn_8018ED90.cpp).
- **fn_801BD780:** written straight from the asm with every subexpression in source order (`32.0f + (32.0f + x + a)` etc.), then a function-level `/*P*/` block and `sw.py` fixed all float ranks in 4 rounds; one statement swap fixed the last volatile pair.

## Near misses filed in wip/

- wip/fn_801C93A0.cpp (228 bytes, 25 lines): saved registers rotated; the parameter wants r31 above the hoisted `lbl_803CA870`/`lbl_803EC898` address temporaries. No spelling of the globals, named pointers or wrapper moved it.
- wip/fn_801CABAC.cpp (140 bytes, 10 lines): f1/f2 swap between `x38` and the 1/64 constant only.
- wip/fn_801C0638.cpp (2,140 bytes, 89 lines): float ranks of the GaugeBg arguments and two colour slots; down from 102 by hoisting the block locals. Changing GaugeBg's parameter order or passing by reference did nothing.
- wip/fn_801A32BC_r15.cpp (1,500 bytes, 27 lines, was 44): `d->scroll` read directly instead of a local `s`, and `GD* o` for the column block. The rest is volatile registers in the first ScrollTo; the macro form that solved fn_801A39AC reached 29 here, and declaration order had no effect at all on those volatiles.

## Tried without success

- fn_801BFB58 (2 words, `m` wants r29): bisection shows that any one Bar sprite before the block makes `m` take r28; with no sprite it takes r29. Inline boundaries, by-reference parameters and named alphas changed nothing.
- fn_801AF2A8 (53 words): real pooled literals changed nothing (65 lines in the masked scorer, same registers). Dead uses of `r` after the join (`(void)r`, inline sinks, `if (r) {}` and so on) all compile away before allocation.
- fn_801B78F0 (6 words): the rect copy load order. A copy constructor `w = o.w; h = o.h; x = o.x;` gives the right load order but a base register instead of direct `lhz lbl@sda21`; aggregates, `Mk()` constructors in all parameter and store orders, and nested `{P2 pos; P2 size}` forms didn't help.
- fn_801C4F0C (73 words): float ranks; moving the rows loop into an inline or flattening Hdr made it worse.
- fn_801B4480 (9 words): an MSL-style `iterator`/`do_splice` rewrite reaches the same 9 words (last2 wants r11, next r8); declaration order and `const` have no effect.
- fn_801CEC98 (13), fn_801BC88C (2, prologue `mr` order): a dozen variants each, no change.

## Caveats

- fn_801C5874: `cnt` stands in for the global `lbl_804CB9EC` (checked only through the symbol map). The original may have used a real function-static or a file static.
- fn_801A39AC: the `ST` macro and the per-loop locals (`o`, `p`, `sl`, `a`, `v`, `a2`, `v2`, `q`, `z`) and their order were found by search; `z` is unused. The original was probably an inline `ScrollTo(f32, s16)` like the one in fn_801A32BC.
- fn_801AEB78.cpp has a `StringPool` dummy holding the 0x8036D68C pool; it is not game code.
- fn_801D087C: `Lock` is a stand-in for the real guard class; its destructor is emitted out of line as `__dt__4LockFv` (skipped by the checker) but is inlined at both call sites.
- Prototypes outside the region are guessed from call sites.
