# Round 18 (rF_8017F400): functionally-equal level

No new exact matches. 14 functions, 35,480 bytes, at `regs` level (same instructions, order and references;
registers differ), each as a self-contained file in `equiv/`. Checked with
`python3 -I tools/check_regs.py equiv/<file> --extra "-i src/game/rF_8017F400 -i src/game/rF_8017F400/wip"`.

| file | function | bytes | how it got there |
|---|---|---|---|
| equiv/fn_8019AEA8.cpp (+ .symbols.json) | 8019AEA8 | 16,972 | file menu main state machine; old wip was one word short |
| equiv/fn_801959A0.cpp | 801959A0 | 5,160 | r17 wip with the Stream stores in the original order |
| equiv/fn_801A6220.cpp | 801A6220 | 2,524 | old wip; pi literal was one bit off (3.14159265f) |
| equiv/fn_801C4F0C.cpp | 801C4F0C | 2,408 | fragment + helpers; `18.0f + ly` moved into the bar loop |
| equiv/fn_801BFB58.cpp | 801BFB58 | 1,736 | fragment + helpers; rank-letter table under `pool_strings off` |
| equiv/fn_801DA800.cpp | 801DA800 | 1,596 | rR wip; one statement moved |
| equiv/fn_801CC5CC.cpp | 801CC5CC | 1,132 | fragment + helpers of ../fn_801CC06C.cpp |
| equiv/fn_801D7D38.cpp | 801D7D38 | 948 | rR fragment + helpers of rR's fn_801D772C.cpp |
| equiv/fn_801CEC98.cpp | 801CEC98 | 936 | fragment + helpers |
| equiv/fn_801CF040.cpp | 801CF040 | 560 | fragment + helpers |
| equiv/fn_801BC88C.cpp | 801BC88C, 801C62D8 | 464, 280 | fragment + helpers |
| equiv/fn_801CCCBC.cpp | 801CCE8C (and 801CCCBC, already listed) | 464 | copy of the r17 body walking `x0` instead of `x8` |
| equiv/fn_801CB1A0.cpp | 801CB1A0 | 300 | fragment + helpers |

## What fixed them

- **fn_8019AEA8:** `lbl_804CB944` (current slot) as a function-local `static int`. The original hoists its load over
  the store to `G->st` and shares one `lbz` of `G->x16` across the store to it (two `extsb`), i.e. it knows the
  variable does not alias. An extern or a file-level static does not do this; a function-local static does.
  `ErrSt` is a macro (`G->st = s; f(g(lbl_804CB944));`). Strict check: `--symbol-map equiv/fn_8019AEA8.symbols.json`.
- **fn_801959A0:** r17 searched store orders for an exact match; at `regs` level the plain original order
  (vt2, vt, own, p, q, n, z) is enough.
- **fn_801C4F0C:** two float constant loads were swapped (invisible in a register-masked diff, caught by the
  reference check). Written as a pre-loop local, `by = 18.0f + ly` came after the loop's hoisted `3.0f + x`; written
  inside the loop it is hoisted first, like the original.
- **fn_801BFB58:** the table of four 2-byte strings must point at separate `.sdata2` strings (lbl_804CF380..38C), not
  into the pool: put the table in an inline between `#pragma pool_strings off/on`.
- Fragments: `equiv/` files are the parent's helpers (its exported functions removed) plus the one function.

## Still `other` (left in wip/, not copied)

- fn_801B78F0 (4,624): rect aggregate; original loads w, h, x and stores w, x, h, y. Pos/size pairs, nested structs and
  `Mk()` inlines (12 forms) did not give it.
- fn_8019FFE4 (6,812, one instruction over and 134 lines), fn_801B2150 (14 lines), fn_801A8E20 (30), fn_801C0638 (68),
  fn_801C336C (4: one `fadds`/`lfd` order), fn_8018E6B0, fn_801951BC, fn_80182B48, fn_801CD05C.
- One or two scheduling lines each: fn_80183944, fn_8018524C, fn_801A2268, fn_8019F3A8, fn_8019F108, fn_801B05F8,
  fn_80184324, fn_8017F4C8, fn_801CE174, fn_801C6114, fn_801BB334, fn_801BB530, fn_801C63F0, fn_801CF270, fn_801B3D3C,
  fn_801B4480, fn_801B40B0, fn_801B7004, fn_801C7110, fn_801BD420, fn_801CE2F4.
- rR wip fragments in this range with wrong sizes: fn_801D820C, fn_801D65EC, fn_801D5914, fn_801D2AC0, fn_801D0D58.
- wip fragments whose parent no longer compiles with them: fn_801ACD98 (fn_801AC084), fn_801B0E88, fn_801B6B18.

## Not written (no draft yet)

fn_80182D24 (3,104), fn_801DCE18 (2,492), fn_801A4744 (2,432), fn_801C3AB4 (1,972), fn_801805E0 (1,712),
fn_801D2744 (892), fn_801B0B58 (640), fn_801D5BB0 (420). fn_801875CC stays at its listed `regs` wip.

## Caveats

- fn_8019AEA8: the function-local static stands for the global `lbl_804CB944`, which other functions also use; a port
  must make it one shared variable. `StringPool` is the documented pool dump.
- fn_801959A0: `s_c1..s_b2` file statics stand for lbl_8041C9F8 and `__div2i` for fn_8028C418; check_regs does not
  verify those two references (they are "not in symbols.txt").
- fn_801BFB58: the `RankStr` inline exists only to scope the pragma.
- fn_801C4F0C: the local `by` is now unused.
- fn_801D7D38 and fn_801DA800 include rR headers (`game/rR_80175E5C/...`); they sit here because their addresses are
  in this region's range. fn_801D7D38's file drops the parent's `ONE(...)`/`WAVE(...)` macro instances.
- `regs` is not a proof of equivalence. Every file here has structurally identical instructions; none is `renamed`.

## Lessons not in MATCHING.md

- **A register-masked diff hides swapped constant loads.** Two `lfs` of different sdata2 constants in swapped order
  look identical once registers and `@N` names are masked; check_regs reports `other` through the reference check.
  Read `check_func.py -v` reference lines ("constant X but original has Y") before assuming a reference problem.
- **Function-local static for non-aliasing also explains missing CSE:** `lbz; extsb r0; extsb r3` (one load, two
  extensions) around a store to an sda variable is the same signal as a load hoisted over a store.
- **Pre-loop local vs in-loop expression decides hoist order:** a value computed before a loop is placed after the
  loop's hoisted invariants in our build; the same expression written in the loop body is hoisted in body order
  (fn_801C4F0C, and `tx = x + 0xC` in rN's fn_8027970C, which must come after the hoisted pool base).
- **Short strings referenced from a data table:** with `pool_strings on` they go into the pool; the original had them
  as separate sdata2 objects. Scope `pool_strings off` around an inline holding the table.
- **At `regs` level, try the plain original statement/store order first.** Several wip files carried orders that had
  been tuned for register scores and were `other` only because of that.
- Tool notes: `check_regs.py --extra` paths must be relative (a root path with a space breaks the flag split). A
  fragment assembler needs to drop macro-generated exports (`SETCOL(fn_..., ...)`, `ONE(...)`) as well as plain
  definitions, or the equiv file re-emits exact functions.
