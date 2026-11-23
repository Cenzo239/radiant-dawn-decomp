# Round 13 (b): 0x801A0000..0x801D09F8

14 functions, 11,352 bytes.

| file | function | bytes | what it is |
|---|---|---|---|
| fn_801AA1CC.cpp | 801AA1CC | 3,396 | movie room window draw (MMR_*) |
| fn_801A4068.cpp | 801A4068 | 1,452 | status screen main draw |
| fn_801A88A4.cpp | 801A88A4 | 1,404 | overlay panel draw |
| fn_801A1DCC.cpp | 801A1DCC 801A1F64 | 408, 704 | help window layout (text, item) |
| fn_801CDD5C.cpp | 801CDD5C | 692 | render a text label into a texture |
| fn_801AD7D8.cpp | 801AD7D8 | 636 | caption bar |
| fn_801B378C.cpp | 801B378C | 568 | picture list window draw |
| fn_801A1AC4.cpp | 801A1AC4 801A1BE0 | 284, 284 | open help window |
| fn_801A6F54.cpp | 801A6F54 | 508 | status screen setup |
| fn_801A3104.cpp | 801A3104 801A3898 | 440, 276 | illustration room modes |
| fn_801C846C.cpp | 801C846C | 300 | unit placement and effect (purpose guessed) |

## Near misses in wip/, all register-only unless noted

- fn_801A2588.cpp (2,444 bytes, 12 words): `x` is r23 and `0xff`/`0x5555` r22; the original has them the other way round. No declaration order, type or inline boundary moved them.
- fn_801A8E20.cpp (3,980 bytes, 34 words): volatile registers in the `lbl_804CB980` stores and one block of the last loop. Saved registers are right.
- fn_801A6220.cpp (2,524 bytes, 37 words): yi wants r27, below sel, u and the compiler temporaries. Everything else is right.
- fn_801B2150.cpp (5,432 bytes, about 180 words): shape, stack and scheduling are right. Induction variables want r27/r29 and land at r21/r22.
- fn_801C336C.cpp (1,864 bytes, 67 words): saved integer and float ranks.
- fn_801BE154.cpp (312 bytes, 15 words): x1 and y1 want f31 and f30 and come out swapped.

Tried again without success: fn_801A2F14 (2 words, xoris r4 wanted), fn_801B3D3C (9 words, e2 and j swapped; End(b) by name, inline scans and `rr` change nothing). Read but not written: fn_801C3AB4, fn_801A4744, fn_801CD05C. Not attempted: fn_801B05F8, fn_801AF2A8, fn_801B40B0, fn_801B4480.

## What unlocked these

- **Nested calls in argument lists:** `f(buf, fmt, g1(), s("A"), g2(), s("B"))` makes the results compiler temporaries, so the string base ranks above them. Named locals put the base at the bottom (fn_801AA1CC). Arguments evaluate right to left.
- **A by-value 4-byte struct arrives as a pointer:** `addi r3,r1,N` over four stack words is a call with four by-value structs. Two `static const` colours plus a `struct W { u32 v; }` give the direct `lbz lbl+N@sda21` loads (fn_801AD7D8, fn_801CDD5C).
- **Anchored sprite:** `x1 = ax * (0.5f * w) + x; x2 = w * sx + x1`, with `ax`, `sx` as inline parameters so the constants aren't folded, and new names `x1`, `y1` so an expression argument like `x - 98.0f` is forwarded past the calls. The word copy between `x1` and `y1` fixes the volatile registers.
- **Register-kept struct local:** `lwz r30,8(r1)` before a loop and `stw r30,8(r1)` after each search is a one-pointer struct held in memory. A nested struct or a union stops scalar replacement; a plain struct, a constructor and `const&` parameters don't (wip/fn_801B2150.cpp).
- **`find_if` shape:** `while (first != last && !P(first->val, v)) first = first->next;` with a `P` that returns an `int` flag gives `b test`, the materialised flag and the loop exit.
- **Moving a large block into an inline can lift a parameter from the lowest register to r31** (fn_801A8E20, p r22 to r31). The caller's remaining locals then respond to order again, and the inline's locals respond when passed by reference.
- **`Fx* f = &p->fx[i]`** makes an induction variable at base+offset; `p->fx[i].on` makes one at base with the offset in the load.
- **Constants held in an `int`:** `int w = 0x18A; F(..., w, h)` keeps `li; xoris; lfd`, while a literal passed to an `int` inline parameter folds to a float constant.
- **`SetR`-style inline parameters** give the base the first volatile register but change the conversion slots, so they did not finish fn_801A8E20.

## Caveats

- fn_801AA1CC, fn_801A4068, fn_801A6F54 and fn_801A3104.cpp have a `StringPool` dummy first, which only fixes pool offsets. It is not game code and the checker skips it.
- fn_801AD7D8: `W` is a stand-in for a colour type, and the second and fourth arguments may be zero-initialised colours in the source.
- fn_801CDD5C: `TevA`, `TevB` exist only to set stack slots, and `cw` stands in for a copy of the colour.
- fn_801A88A4, fn_801AA1CC: the copy of `c` through `*(u32*)` stands in for a by-value parameter in the original inline.
- fn_801A4068's `Mode()` inline exists only to get `cmpwi` on a byte.
- fn_801C846C: `V3` is a guess at a by-value Vec helper. `(s8)*(u8*)&` on `xE` mixes s8 and u8 reads of the same field.
- fn_801A3104's `z2` and `z` are guesses at how a shared zero was written.
- Prototypes outside the region are guessed from call sites. `fn_8007E7DC` is `u8` in fn_801A4068 and `int` elsewhere, so the files can't merge as they stand.
