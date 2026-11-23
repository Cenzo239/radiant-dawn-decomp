# Round 15, agent a (0x8017F400..0x801A0000)

3 functions, 8,928 bytes, all MATCH with `--strict-references`.

| file | function | what it is |
|---|---|---|
| fn_8018F4F4.cpp | 8018F4F4 (7,232) | config menu input handler (scroll, per-option left/right, volumes, reset) |
| fn_8017F68C.cpp | 8017F68C (772) | easing function `ease(mode, from, to, t, d)` with 13 curves |
| fn_80194D58.cpp | 80194D58 (924) | file menu three-choice cursor input |

## Near misses (in wip/)

- fn_801959A0.cpp (5,160 bytes): save-data inherit state machine, 13 of 1290 words. Left: one `addi` order in the slot loop step and the stack `Stream` init (vt2/vt/zero/buf/FM pointer take r3..r7 in the wrong order; ~60 init orders, named zeros, ctor inlines and aggregate init all tried). Its "4 wrong references" are the `s_c1..s_b2` statics standing in for lbl_8041C9F8 (as in fn_80196E14.cpp) and `__div2i` for fn_8028C418.
- fn_80181470.cpp (792): gmap resource load with two in-place u64 byte swaps, 4 words; the second swap's high result wants r4 (ours r5). The swap expression order matters a lot (reverse of the obvious order).
- fn_8018E6B0.cpp (1,164): config cursor draw, 31 words; register order of the second texture-size loads in draws 1 and 3, and `y + 32` operand order.
- fn_80182B48.cpp (476): curve Hermite evaluation, 32 words, float register colouring only.
- fn_8018524C, fn_8019555C: unchanged (another ~20 spellings each).

Not attempted: fn_801805E0 (read Ghidra: spline build with three saved floats), fn_80182D24, fn_8019FFE4, fn_801951BC, fn_80183944, fn_801875CC, fn_8019AEA8 (no time for the 15-minute tries).

## Caveats

- fn_8018F4F4: `StringPool` is scaffolding copied from fn_8018732C.cpp for the pool offsets. The option cases are macros (`TG`, `CY`, `VOL`, `STEP`) that probably were inlines or repeated code. Reads like `(s8)*(u8*)&c->f`, `(s8)(u8)c->x75` and separate `o70`/`o1a` locals exist only to get registers; the original fields are probably u8 read with casts.
- fn_8017F68C: case 10/12 use `lbl_804CE54C` (1.0f) as an extern instead of a literal, and expression forms came from search.
- fn_80194D58: `HelpBar`/`FMCursor` types copied from wip/fn_8019555C.cpp; the inner `FMCursor* hc` vs outer `HelpBar* g` split came from search.

## Lessons not in MATCHING.md

- **`FMCursor* hc = &lbl->cur; hc->x` vs `HelpBar* h = lbl; h->cur.x`** rank the reloaded global differently; the member-pointer form fixed a whole-function r6/r7 swap in fn_80194D58 (60 lines to 0).
- **Bad register for an `extsb` value:** `v = (s8)*(u8*)&c->f` put a value in the rank of a declared local where `int v = c->f` with an s8 field made it the lowest saved register; `o = (s8)(u8)c->f` into an `s8` local did the same for another case (fn_8018F4F4).
- **A raw byte reused for a store** (`lbz r3; extsb r26,r3; stb r3`) came from `c->x71 = *(s8*)&c->f` after the cast read.
- **Easing / float sums:** `(1.0f - s)` written with an extern 1.0f fixed f0/f1 swaps that every literal spelling missed.
- **Multiplying a sum's operands:** CW evaluates the right-hand product of `a*b + c*d` first (fmuls), then fmadds the left one, so write the first-computed product last.
- **Hermite terms through an inline with the difference as an argument** (`H(p0, p1 - p0, m0, m1, u)`) loads the key fields before the weight maths, as in the original.
- **Per-case greedy spelling search** (one key per case, each with ~5 alternatives, keep strictly better) found 7 fixes in one run on fn_8017F68C. Script: a `G = {old: [alts]}` dict, applied greedily key by key.
- **Big menu handlers written from Ghidra plus the asm order of case bodies match in a few passes**: fn_8018F4F4 (7 KB) took about 15 compiles; fn_801959A0 (5 KB) reached 13 words the same way, reusing the `Fill` inline from fn_80196E14.cpp.
- Scorer: masking `...bss.0`/`lbl_8041C9F8` and `__div2i`/`fn_8028C418` in `lib.parse` removes false diffs from file statics and runtime helper names.
