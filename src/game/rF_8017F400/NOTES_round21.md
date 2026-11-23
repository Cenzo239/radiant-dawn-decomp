# Round 21 (rF_8017F400): the three large functions without a draft

Checks: `python3 -I tools/check_regs.py src/game/rF_8017F400/<file> --extra "-i src/game/rF_8017F400 -i src/game/rF_8017F400/wip"`,
and `python3 -I tools/equiv/symcheck.py <file> <fn> rF_8017F400 --anon -v` for the `slots` files. All three files
are self-contained and were written from the disassembly (m2c draft first).

| file | function | bytes | class | notes |
|---|---|---|---|---|
| equiv/fn_801A4744.cpp | 801A4744 | 2,432 | slots | minimap panel. Two pairs of 4-byte colour locals sit in each other's slots; symcheck flags 3 of 80 blocks, exactly those |
| equiv/fn_801C3AB4.cpp | 801C3AB4 | 1,972 | slots | circular "cur / max" gauge. The two int-to-float scratch doubles are used in the opposite order; symcheck flags 8 of 64 blocks, all those slots |
| wip/r21_fn_80182D24.cpp | 80182D24 | 3,104 | other | world map route lines. 776 of 776 instructions, same frame |

## fn_80182D24: what is left

1. The arrow-head size 32.0f: the original keeps it as an unnamed hoisted constant spilled as a double
   (`stfd` before the loop, `lfd` at both uses) and does not fold `0.5f * 32.0f`. A named block local gives the
   same instructions with a float spill, which shifts five neighbouring spill slots. Inline parameters, `const`,
   file statics, an extern constant, int/u8/f64 sizes and `hh = 32.0f; hh *= 0.5f` were tried (see the header).
2. Two argument set-ups are scheduled differently (before the first `fn_80182B48` call, and `frsp f14,f1`
   before the `fcmpo` after the atan call).
3. Saved registers are numbered differently.
None of this changes behaviour; the header lists what the dead colour copies mean for a port.

## Caveats for a port

- fn_801A4744: `lum` is a `u8` parameter (fn_801A3068.cpp declares it int); `MMap`/`MUnit` are local views of
  the objects at lbl_804CB964 / lbl_804CB810; fn_8007E174 gets a pointer here where other files declare int;
  colour temporaries only reproduce stack copies.
- fn_801C3AB4: lbl_804CB9E8 (pulse) and lbl_804CA8F8 (step, 0.02f) are almost certainly function-local statics,
  written as externs; the two 9-float offset tables are local templates (the original reads lbl_8036E0D0 /
  lbl_8036E0F4, values compared by hand); `pi` is a local only to stop folding.
- fn_80182D24: per-case `C4 a, b` locals and six `u8` copies reproduce dead stack stores (a 4x2 colour table by
  `kind` is what it means); with n <= 1 the arrow-head block would read dx/dy uninitialised, as in the original
  (it requires n > 3, so it cannot happen); lbl_8041C9D8 is a table of doubles here, `void*[8]` in fn_80181788.cpp.

## Lessons

- A float constant that is hoisted and spilled as a *double* (`stfd`/`lfd`) is an unnamed compiler temporary; any
  named local spills as a float (`stfs`/`lfs`) and moves the neighbouring spill slots.
- This session was cut by a usage limit while fork notes were unwritten: write the NOTES file when the first
  function is saved, not at the end.
