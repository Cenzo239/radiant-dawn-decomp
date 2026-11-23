# Round 19 (rF_8017F400)

Checks: exact files with `python3 -I tools/check_func.py <file> --strict-references`; equiv files with
`python3 -I tools/check_regs.py equiv/<file> --extra "-i src/game/rF_8017F400 -i src/game/rF_8017F400/wip"`.

## Exact (3 functions, 3,152 bytes)

| file | function | bytes | notes |
|---|---|---|---|
| fn_801DCE18.cpp | 801DCE18 | 2,492 | static initialiser of 110 `Rect16` globals (lbl_804CBA88..); hand-named, see caveats |
| fn_801D5BB0.cpp | 801D5BB0 | 420 | help window text setup (MSL string assign) |
| fn_801D2AC0.cpp | 801D2AC0 | 240 | rR fragment + helpers of rR's fn_801D0A40.cpp; three checks as one `\|\|` early return |

## `regs` (2 functions, 2,352 bytes), in equiv/

| file | function | bytes | notes |
|---|---|---|---|
| equiv/fn_801805E0.c | 801805E0 | 1,712 | path trail update (Catmull-Rom resample, normals); new, compiled as C |
| equiv/fn_801B0B58.cpp | 801B0B58 | 640 | reverse-iterator find + distance; new |

## `sched` (13 functions, 20,736 bytes), in equiv/

Same instructions per basic block as the original, order differs. Each diff was read with tools/equiv/dd.py.

| file | function | bytes | what moved |
|---|---|---|---|
| equiv/fn_801B2150.cpp | 801B2150 | 5,432 | field loads and the y sum in the first block of the row loop |
| equiv/fn_801B78F0.cpp | 801B78F0 | 4,624 | rect halves: two `lhz` and a `sth`/`li` pair (the known rect order) |
| equiv/fn_801A8E20.cpp | 801A8E20 | 3,980 | one block of int-to-float conversions through the shared stack slots (see caveats) |
| equiv/fn_801C336C.cpp | 801C336C | 1,864 | one `fadds` against one `lfd` |
| equiv/fn_801951BC.cpp | 801951BC | 928 | two `lha`, a `mulli`, an `addi` |
| equiv/fn_801D2744.cpp | 801D2744 | 892 | new this round; two `li` and the vtable store in the first widget constructor |
| equiv/fn_8018524C.cpp | 8018524C | 616 | one `li` |
| equiv/fn_801B05F8.cpp | 801B05F8 | 600 | `li`, `lis`, one store |
| equiv/fn_80182B48.cpp | 80182B48 | 476 | float loads around one `fnmsubs`/`fsubs` |
| equiv/fn_80183944.cpp | 80183944 | 460 | one `stb` to the stack |
| equiv/fn_8019F3A8.cpp | 8019F3A8 | 356 | one prologue `stw` |
| equiv/fn_801A2268.cpp | 801A2268 | 284 | one `addi` |
| equiv/fn_8019F108.cpp | 8019F108 | 224 | one `li` |

## What fixed the new ones

- **fn_801DCE18:** the real source is 110 global definitions `Rect16 lbl(x, y, w, h);`. Compiled that way (with
  `#pragma use_lmw_stmw on`) the generated `__sinit_...` is byte-identical, but the checker matches by name, so the
  file holds one hand-named function with plain member stores over externs. Values were extracted by interpreting
  the `li`/`sth` stream.
- **fn_801D5BB0:** `Tag t;` as a named local of the assign inline (temp at the lower slot, by-value copy above it) and
  `strlen` wrapped in an inline (`traits::length`), which gives the `mr r7,r6; add r7,r7,r0` form.
- **fn_801805E0:** only C keeps the dead stack copy of the default colour (same code as fn_8017FDC8.c; C++ drops the
  four `stb`). `MkVec()` returns a zero-initialised aggregate (int zero stores, word copy into the named local).
  The easing call goes through an inline whose parameters are in reverse order (`Ease(t, to, from)`): inline arguments
  are evaluated last to first, which fixes the float load order and the place of `li r3,2`.
- **fn_801B0B58:** MSL-style reverse iterator with a scratch copy (`tmp = base(); --tmp`), `!=` through `base()`, and
  `distance` as a reference-taking inline that calls a by-value one.
- **fn_801D2AC0:** `if (!a || !b || !c) return;` gives `bne next; b end`.
- **fn_801D2744:** rI's types.h declares `lbl_804CB700` volatile; a non-volatile declaration fixes the epilogue order
  (`lwz r31; lwz r30; lwz r0`).
- **fn_801B2150:** `for (row = 0; row < 9; row++, n++)` fixes the loop tail. The sdata2 externs `lbl_804CF21C` and
  `lbl_804CF218` are written as the literals 8.0f and 291.0f (see tool notes).

## Still open (in wip/)

- wip/fn_801AC084_r19.cpp (1,832): self-contained; one scheduling line (the third text width is sign-extended before
  `w1*2` and `w1+w0`; the original reuses r25 and does it after). Classified `other` only because of the
  `@stringBase0` problem below. Fixed this round: the tile-kind switch runs before `fn_8007E154()`.
- wip/fn_801B2150_r19.cpp: same code as equiv/fn_801B2150.cpp with the named float externs.
- Not written: fn_80182D24 (3,104), fn_801A4744 (2,432), fn_801C3AB4 (1,972). The last two were read in full: all of
  f14..f31 or f23..f31 are in use, with spills.
- Not attempted or unchanged: fn_8019FFE4, fn_801C0638, fn_8018E6B0, fn_801CD05C, fn_801CE174, fn_8017F4C8,
  fn_80184324, fn_801B6B18 and fn_801B0E88 (parents still do not compile with them), fn_801B7004 and
  fn_801B3D3C/fn_801B4480/fn_801B40B0 (self-contained now, but sizes differ), and the "one or two lines" list not
  named above (fn_801BB334, fn_801BB530, fn_801C63F0, fn_801CF270, fn_801C7110, fn_801BD420, fn_801CE2F4, fn_801C6114:
  no compiling draft found in wip).
- rR-range fragments: fn_801D5914 (4 instructions short: the switch needs a distinct `case 0`; the float argument of
  fn_800CA3DC must be the first parameter so that it loads before the ternary), fn_801D0D58 (store addressing:
  original uses `stwx` for the first push and `0(rN)` for the rest), fn_801D820C (89 lines), fn_801D65EC (does not
  compile with either parent).

## Caveats (things a port must undo or check)

- fn_801DCE18.cpp is not how the source looked: use the 110 global constructor definitions quoted in its header.
- equiv/fn_801805E0.c is C, and `Track2` adds `pts[514]`/`nrm[514]` to the `Track` of types.h (same size). `MkVec`,
  `Ease`, `KeyPos`, `Reset` are inferred inlines; `Reset` repeats fn_8017FDC8.
- equiv/fn_801B0B58.cpp: `It`/`RI` are hand-written stand-ins for the MSL list iterators.
- fn_801D5BB0.cpp: `Str` is the hand-written small-string layout used elsewhere; strings come from the file's pool.
- equiv/fn_801B2150.cpp: 8.0f and 291.0f replace two named sdata2 constants (same values, verified by value).
- equiv/fn_801A8E20.cpp: the moved instructions include stores and loads of the two shared conversion slots. Both
  versions are compiler output for the same operations per block, but the pairing of each conversion with its use was
  not proven by the tool.
- fn_801D2AC0.cpp and equiv/fn_801D2744.cpp include rR/rI headers; equiv/fn_801D2744.cpp redefines `lbl_804CB700`
  as non-volatile through a macro around the include.
- `sched` and `regs` are not proofs of equivalence.

## Tool notes (not fixed: tools are outside this agent's scope)

- `check_regs.py` `sched_equal` links our `@stringBase0` to the single `@stringBase0` entry of symbols.txt
  (0x803747D0), so any function that uses pooled string literals fails the `sched` test (fn_801AC084).
- The same function resolves sda21 relocations by trying r13 first; every sdata2 address is also within 32 KB of the
  r13 base, so a named sdata2 extern (`lbl_804CF21C`) is linked as r13-relative and never equals the original
  r2-relative word (fn_801B2150 before the literals). Unnamed float literals are not affected.
- A draft with placeholder constant values can pass as `sched` when its constants are file statics (rN fn_802818FC had
  eight all-0xFF colours); with the real bytes it became `regs`.

## Lessons not in MATCHING.md

- **A static initialiser can be credited as a hand-named function**: plain member stores over externs plus
  `#pragma use_lmw_stmw on` gave the same bytes as the real `__sinit`. Check the real form once with a manual diff.
- **C and C++ differ in dead-store removal**: a local struct filled field by field and then assigned
  (`p->color = c`) keeps its stack stores in C only.
- **Inline arguments are evaluated last to first.** When float loads of a call come in the "wrong" order and nothing
  else moves them, wrap the call in an inline with the parameters reversed.
- **Float-first prototypes matter**: if the callee is `f(f32, const char*, int)`, the float loads before a ternary in
  the pointer argument; declared `f(const char*, int, f32)` it loads after.
- **`bne next; b end`** after two `beq end` is `if (!a || !b || !c) return;`.
- **Epilogue order `lwz r31; lwz r30; lwz r0`** can come from a global that is wrongly declared volatile.
- **By-value empty tag arguments**: a named local in the inline puts the temp below the outgoing copy; `Tag()` in
  the call puts it above.
- **`Vec r = { 0, 0, 0 }; r.x = x; r.y = y; return r;`** in an inline gives integer zero stores followed by a word
  copy into the caller's local.
- **Reverse iterators:** `operator*` as `tmp = base(); --tmp;` avoids a second load of `current`; `distance` through
  a `const&` wrapper orders the two argument copies (last, then first).
- **Variable reuse does not force register reuse**: the compiler splits the webs (fn_801AC084 `w1`).
