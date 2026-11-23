# Round 9, agent a (0x8017F400..0x8019FFFF)

11 functions, 6,400 bytes.

| file | functions |
|---|---|
| fn_80183FE8.cpp | 80183FE8 |
| fn_80186FA4.cpp | 80186FA4 8018708C |
| fn_8018732C.cpp | 8018732C 8018F394 8018F3AC |
| fn_8018EB3C.cpp | 8018EB3C 8018F19C |
| fn_8018ED90.cpp | 8018ED90 |
| fn_80196E14.cpp | 80196E14 801972FC |

## Near misses

- wip/fn_801875CC.cpp (unchanged): still 6 words. The first slider is the odd one because it comes first in code order, not because of its text. Moving case 4 after case 22 makes case 22 the odd one, and a live `if (c->x48 == 99) Slider(...)` in case 3 takes the oddity and fixes case 4. A prior instance removed as dead code (`if (0)`, `int z = 0; if (z)`, code after `break`) has no effect. Tried without effect: all 720 orders of w, h, arch, t, t2, pp; 10 parameter orders (keeping c, e, hl and x0, y in sequence); function-level arch, w, h in every order with px, s, u; sharing arch, w, h with s and u; dead temporaries; a dummy earlier function using the inline; a separate Dr2; arch as an inline parameter; accessor and reference forms for w and h.
- wip/fn_8019AEA8.cpp: 4242 of 4243 words, about 180 differ. All case bodies and the dispatch are right; what's left is saved registers. Temporaries such as `void* e` in the cursor code get r26 where the original has r28, and grouping them in one function-level variable changes nothing, because the compiler colours each def-use web separately. Keeping `held` and `trig` live past the switch didn't move them either. The original looks as if r29..r31 are blocked up to the last use of `held` and `trig` in case 0x2724, since only cases after that point reuse r30 and r31. One word is missing in case 0x1b76 (`extsb r0,r3; extsb r3,r3` from one `lbz`); about 20 spellings were tried.
- wip/fn_8018524C.cpp: 2 words, the order of `li r0,0` and `li r3,1` in case 0.
- wip/fn_8018E6B0.cpp: about 43 words, quad scheduling.

Not attempted: fn_8018F4F4 (read as far as the 0x8FF10 case, long float scroll math then one input block per option), fn_80185D0C (battle unit constructor inlined three times), fn_80181470 (64-bit byte swaps inlined). Paired-single candidates were left alone.

## Caveats

- `StringPool` in fn_80183FE8.cpp, fn_80186FA4.cpp, fn_8018732C.cpp, fn_8018EB3C.cpp and fn_8018ED90.cpp is scaffolding.
- fn_80183FE8 writes its zero stores one by one; the source probably used loops or member constructors.
- fn_80196E14.cpp uses file statics for lbl_8041C9F8 and neighbours, so the checker compares offsets only. The same objects are externs in fn_801945C0.cpp, which would clash once the two are one translation unit. `Fill` and `P2` are guessed inline boundaries.
- `IGuard` in fn_8018ED90.cpp stands in for the guard class with vtable lbl_80380F00. It emits an extra `__dt__6IGuardFv`, and it stores the vtable symbol as a plain array address.
- fn_8018732C's prototype of fn_801875CC has the floats before `hl`, unlike the wip file. Both give the same registers, and the bytes of fn_801875CC don't depend on it.
