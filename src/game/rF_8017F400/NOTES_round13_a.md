# Round 13, agent a (0x8017F400..0x801A0000)

22 functions, 24,384 bytes.

| file | functions | what it is |
|---|---|---|
| fn_80198CC0.cpp | 80198CC0 | save slot entry draw (7,020 bytes) |
| fn_80185D0C.cpp | 80185D0C | class change event setup, battle unit ctor inlined three times |
| fn_801818E0.cpp | 801818E0 | world map per-frame update |
| fn_801820CC.cpp | 801820CC | world map draw, one label per country |
| fn_8017FE30.cpp | 8017FE30 | trail ribbon and arrow head (GX FIFO) |
| fn_801986C4.cpp | 801986C4 | save slot header draw |
| fn_8019A82C.cpp | 8019A82C | difficulty select draw |
| fn_801846D0.cpp, fn_80184BEC.cpp | 801846D0, 80184BEC | achievement window pieces |
| fn_8018508C.cpp | 8018508C, 801854B4 | achievement window draw and init |
| fn_8018587C.cpp | 8018587C, 80185A10 | sparkle sprite draw and placement |
| fn_80186768.cpp | 80186768 | class change event teardown |
| fn_80193774.cpp | 80193774 | gauge bar draw |
| fn_8019467C.cpp, fn_8019846C.cpp | 8019467C, 8019846C | tile draw |
| fn_8019F5E8.cpp | 8019F5E8, 8019FD1C, 8019FF0C | sound fade, buffer destructor, scissor callback |
| fn_801813D0.cpp | 801813D0 | map x to widescreen x |
| fn_80181788.cpp | 80181788 | gmap: release resources |

## Near misses

- wip/fn_8019FFE4.cpp (6,812 bytes): help window draw. Shape, stack and nearly all registers are right. Left: FP scheduling in frame draws 4 to 13, and r25..r28 ranks in the item block. A two-round greedy over 69 spellings per draw only went from 296 to 261 masked lines. In the target the `x + w` `fadds` comes after the conversions.
- wip/fn_8019555C.cpp (868 bytes): 2 words, `sel` wants r9, ours r0. About 30 spellings tried.
- wip/fn_801951BC_r13.cpp (928 bytes): 17 words, the same body as above; `g` wants r6 with `lis 0x4330` in r7, and the move-rect block order.
- wip/fn_80183944.cpp (460 bytes): 3 words, store order of the halved colour bytes.
- wip/fn_8018524C.cpp: still 2 words. About 30 case 0 spellings, none move `li r0,0` above `li r3,1`.
- wip/fn_8019F108.cpp: moving the stores gets the right `li` registers but then the wrong store order, about 100 forms tried, not changed.
- wip/fn_8019F3A8.cpp: unchanged, the one-line wrapper, a `z` local and local parameter copies all leave the entry in r31.
- wip/fn_8017F4C8.c: unchanged. `s16 len` with `int i` gets the unrolled shape, but the compiler adds a `n <= 0` guard the original lacks. Not filed.

Not attempted: fn_801875CC, fn_8019AEA8, fn_8018E6B0, fn_8018F4F4, fn_801959A0 (read part, a save state machine using _savegpr_14), fn_80182D24 (read start, f14..f31 and GX), fn_801805E0 (read most, spline build), fn_80182B48, fn_80181470, fn_8017F68C, fn_80194D58.

## Caveats

- `StringPool` in fn_801846D0.cpp, fn_8018508C.cpp and fn_80185D0C.cpp is scaffolding.
- fn_80198CC0 uses inline wrappers `S0`..`S8`, `A0`..`A9`, `B0`..`B9` only to set stack order, under `inline_depth(30)`. They are not source. Its statics `s_c1` to `s_b2` stand in for lbl_8041C9F8 and neighbours, as in fn_80196E14.cpp, and clash with the externs in fn_801945C0.cpp once merged.
- fn_801818E0's `Wr1`, `Wr2` are also depth-only, and the `SetA`/`PutC2` split is a guess.
- fn_8019FFE4's two template colours are separate 4-byte aggregates, where the original data is one 8-byte block at lbl_804CE9B8. Same value, different symbols.
- fn_80185D0C's `m->x15ec = (int)Ctor(u3) * 0` is a hack to keep the call and store 0. The original almost certainly stores a zero constant.
- fn_80181788's `z` is an otherwise pointless local. All `/*P*/` orders came from search.
- fn_801986C4, fn_80184BEC and others keep `Sprite`/`Tile` copies per file; these are probably one header in the source. Prototypes outside the region are guessed from call sites (fn_800804D4 is `u8` in fn_8018587C.cpp and `int` elsewhere).

## Lessons not yet in MATCHING.md

- **Ascending stack slots across sibling inlines:** siblings at one depth descend. To ascend, nest the first deepest, one wrapper per draw, with `#pragma inline_depth(30)`. Later siblings then sit above earlier ones. A count of 11 levels solved fn_80198CC0.
- **Aggregates with an address taken are placed above temporaries.** An 8-byte `GXColor c[2]` went to the top of the frame. Two separate 4-byte `GXColor` locals sat next to the argument copy, as in the original.
- **Slot groups per loop:** when each loop's [temp, copy, dead copy] group must stay together, call the second loop's inline through two extra wrappers (fn_801818E0).
- **Keeping a sign-extended value out of r0:** `s16 n = f->x; n -= 5;` gives `subi r0; extsh. r3,r0` where `(s16)(x - 5)` gives `extsh. r0,r0`.
- **Int constants across calls:** `s16 w = 0x13a, h = 0x42;` in an inline gives `li rSaved; xoris; stw; lfd; fsubs`, including derived `w - 2` folded to `li 0x138`. An inline `int` parameter folds to `lfs`.
- **Same-register loops:** two loops with identical registers and a free higher register are solved by split function-level counters and a named zero, then `sw.py` (fn_80181788, fn_8019555C).
- **Loop-invariant `clrlwi` with a guard:** `col4(r, g, b, C8(a))` with `C8` an inline returning `u8` hoists the mask and adds the `cmpwi; ble` loop guard, where a plain `(u8)a` is dropped.
- **Named struct kept in memory:** `struct { u8 tex[0x20]; s16 w, h; }` keeps `sth; lhz` for the size, and a forwarded `lha`/`r3` for the second field.
- **`if (--left >= 0) goto again; goto next;`** gives `blt next; b again`.
- **Mid-loop `f32 m = tw / 2; ... k + i * 0x73 - m`** orders the `i` conversion before the width conversion; naming both puts a temp in f3.
- **Masked scoring:** a `difflib` score with registers masked and a positional check together show when only colouring is left; the positional count alone jumps on any one extra instruction.
