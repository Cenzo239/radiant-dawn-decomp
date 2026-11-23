# Round 9, part b: 0x801A0000..0x801D09F8

## New matches

| file | functions |
|---|---|
| fn_801BE4E4.cpp | 801BE4E4 |
| fn_801B8DB4.cpp | 801B8DB4 801B9454 801B9CEC |
| fn_801B3B3C.cpp | 801B3B3C 801B4280 801B3E68 |
| fn_801C7898.cpp, fn_801C864C.cpp, fn_801C9E98.cpp | one registrar each |
| fn_801CBA0C.cpp | 801CBA0C |
| fn_801CBA60.cpp | 801CBA60 |
| fn_801CC06C.cpp | 801CC06C 801CC2BC |
| fn_801B9F30.cpp | 801B9F30 801BA20C |
| fn_801B7644.cpp | 801B6EBC 801B7644 801BA814 801B739C |

## Near misses

- wip/fn_801B78F0.cpp: unit list window init, 4,624 bytes, 6 words off. Only the rect copy schedules differently; see the file comment. Worth the most of what is left here.
- wip/fn_801BDF20.cpp: fn_801BFB58 (2: `m` wants r29). Colours look like "lowest free register among those used so far", so `m` must be coloured before the Bar `arch`; temps and inline boundaries around `m` did not change it. fn_801C5874 (17: the counter wants r5 and the 0x4330 constant r6; the source order is x, y, then the store, and `(u8)(i == 2 ? 1 : 0)` is right for the colour index).
- wip/fn_801CE800.cpp: fn_801CEC98 (13). Alternate Find1 forms, a wrapper around the switch and a named key changed nothing.
- wip/fn_801CC5CC.cpp (16: float temps only, saved registers all right), wip/fn_801B3D3C.cpp (three list merges, 9 words each on two of them), wip/fn_801A2F14.cpp (fn_801A2F14 2, fn_801A3898 17, fn_801A3104 35), wip/fn_801B6B18.cpp, wip/fn_801B7004.cpp.

## What unlocked these

- **A nested struct stops scalar replacement of its sibling fields.** A `struct W2 { u32 a, b; }` as the first member made `LEnt t(x)` keep the stack stores and pair the two words as `lwz; lwz; stw; stw` (fn_801B9454). That is where a run of dead stack stores with forwarded registers comes from.
- **A hidden virtual argument:** `lbz r4` that looks like noise before `bctrl` was the index argument of `help(k)` (fn_801B9454).
- **`fmuls` then `fadds` with no `fmadds`** means a named intermediate; `a * b + c` as one expression is contracted (fn_801CC5CC).
- **`std::swap` through references** keeps the reloads where a hand swap forwards the known value, once a branchy comparator splits the blocks (fn_801B3E68).
- **Moving a nested loop into an inline taking `int& any`** gave the loop counters the register ranks no declaration order could (fn_801CBA60).
- **`/ 1024.0f` versus `* 0.0009765625f`** has the same constant and different operand order (fn_801CC2BC).
- **`x |= a, x |= b` as a comma expression** gives one load and store with `ori` before `oris` (fn_801CBA60).
- **`d = (q = p->x62) - v;`** puts `extsb` after the division when `q = ...; d = q - v;` puts it before (fn_801B9F30).
- **Two zero-valued floats:** `f32 ox0 = 0.0f; f32 ox = ox0;` fixes prologue scheduling; the source probably had separate x and y (fn_801BE4E4).
- **`u8` multi-return inlines** for `*ls ? f() : 0` fixed the last three registers of fn_801BE4E4.
- **Registrars:** the table base `addi r4, r30, 0x0` is pooled file statics, and with statics the string base takes r31 first.

## Caveats

- fn_801C7898, fn_801C864C, fn_801C9E98 and fn_801CBA0C use empty `static u8` arrays as stand-ins for the class tables (`lbl_8038A990`, `lbl_8038AA20`, `lbl_8038AB70`, `lbl_8038ACF8`). The checker reports these as `...bss.0` and does not verify them, and the original objects are initialised `.data`. The code bytes match but the data is not reproduced, so each file must stay a separate object until those tables are written.
- fn_801BE4E4.cpp repeats the header of fn_801BDF20.cpp, including the dummy `StringPool`. `ox0` and the `s16 ix, iy` temps there are guesses.
- fn_801B3B3C.cpp expands the sort with a text substitution of the comparator (one copy per comparison). The original is presumably one `std::list::sort` template, not reproduced as a template here.
- fn_801CBA60's comma `|=` is unlikely source. fn_801B9CEC's `Set21`/`Set28` and fn_801CBA60's `L4` are guesses at inline boundaries. Declaration orders in fn_801B3B3C and fn_801B739C came from `sw.py`.
- Strings are `lbl + offset`, matched by address, except fn_801BE4E4.cpp, which uses pooled literals. All prototypes outside the region are guessed from call sites.
- wip/fn_801BDF20.cpp still holds the old fn_801BE4E4 and old forms of the others, because only new files were allowed this round.
