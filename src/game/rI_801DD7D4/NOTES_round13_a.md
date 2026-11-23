# Round 13 a: 0x801DD7D4..0x80213000

30 new matches, 0x4FE4 bytes (20,452). The 25 KB aim was not reached. Files hold batches, not translation units. Everything below prints MATCH from `python3 -I tools/check_func.py <file>`.

| file | matched |
|---|---|
| fn_802125CC.cpp | 802125CC |
| fn_801E9914.cpp | 801E9914 801E999C 801E9A30 801E9B58 |
| fn_801FA508.cpp | 801FA508 801FAC44 |
| fn_801F8394.cpp | 801F8394 801E7C10 801DE160 |
| fn_801E8A84.cpp | 801E8A84 |
| fn_801EACE8.cpp | 801EACE8 |
| fn_801EAF64.cpp | 801EAF64 |
| fn_802016AC.cpp | 802016AC |
| fn_801F1FB0.cpp | 801F1FB0 801F37BC |
| fn_801F3A3C.cpp | 801F3A3C 801F41E4 |
| fn_801F6490.cpp | 801F6490 801F654C |
| fn_801F56C4.cpp | 801F56C4 |
| fn_801DEE70.cpp | 801DEE70 |
| fn_801DF530.cpp | 801DF530 801E0B68 |
| fn_801DFA2C.cpp | 801DFA2C |
| fn_801DE85C.cpp | 801DE85C |
| fn_801FA670.cpp | 801FA670 801FA160 |
| fn_801FFCBC.cpp | 801FFCBC |
| fn_801F69A4.cpp | 801F69A4 |

## Near misses (attempts are not in the tree)

Word counts are from the local position scorer.

| function | diff | state |
|---|---|---|
| fn_801EB490 | 2 | Only `lwz r23,0x40(r3)` before `mr r19,r4`. Same shape as fn_801EAF64, which schedules the other way round. |
| fn_801EA5E4 | 11 | Third colour channel: `o->x4c` loads above the min compare, so the pointer takes r6, not r3. |
| fn_802007E4, fn_80200B18 | 11, 8 | `xr` and `w` swap (r26, r29). fn_802016AC, the same shape, is solved. |
| fn_801E2204 | 9 | Stack and registers exact. Loads at entry want to move above `stw r0`. Blocks fn_801E2424 and fn_801E2924. |
| fn_801E1D0C | 8 | `p` and `d` swap (r6, r7) before the two compares. |
| fn_801E8680 | 9 | `x52` and second input read swap (r5, r6); temps around `(rows - 1) * cols`. |
| fn_801DE450 | 9 | The `s16 h` web wants r28 and gets r24. |
| fn_801FE8BC, fn_801EEFA4, fn_801EDF9C, fn_801ECF94 | 9 | Volatile temps only. |
| fn_80204EB4 | 20 | Parameter and switch offset swap (r30, r31). |
| fn_801FA9BC, fn_801F43E0 | about 40 | The `mr rZ,rI` zero idiom, then ranks. |
| fn_801FEA10, fn_80204A08 | large | The stack vector is scalar-replaced and its constants fold. It needs a real memory-held class. |
| fn_801E1894 | 67 | Colour address `addi r25,r31,8` is hoisted out of the loop under `__alloca`. |
| fn_801FB050 | 18 | `li r0,0; srawi r0,r0,31; or.` on a u64 test. |

## Skipped

- **Constructor-heavy (`lbl_8038CB1C`, the -1/0x190 problem):** fn_801F4850, fn_801F2954, fn_801F8798, fn_801F9030, fn_801F19A0, fn_8020B8C8, fn_80206310, fn_801F17C4.
- **Left alone as asked:** the retry-loop family (fn_801EC928, fn_801E8E88, fn_801E941C), the `lbl_8038C1C0` constructor and the fn_801EBF00 family.
- **Not attempted:** fn_801F5A44, fn_801F99A0, fn_80202FF4, fn_8020291C, fn_80202344, fn_801E7E1C, fn_801F243C, fn_801EA17C, fn_802020AC.
- **Blocked:** fn_802038BC, fn_801F3D28, fn_801F6C54 by the zero idiom.

## Caveats on matches

- **Stand-ins:** struct, field and helper names are guesses, and virtual slots come from offsets. Several classes declare virtual slots with the signature one caller needs, so the same slot differs between files.
- **fn_802125CC:** `bon` and `s8 vv` shape register rank. `vv` exists only to push the parameter down to r22. x + w is written out at each use so CSE makes it a temp.
- **Volatile reads:** several files declare `lbl_804CB700` non-volatile and read it through `*(volatile u32*)` to force two loads. The original probably had neither.
- **fn_801E9914 family:** the `ind` stepped offset and `e[(u32)(k - 1)]` exist for register and `mulli` shape.
- **Scale chains:** the fn_801F1FB0 and fn_802016AC scale chains use function-level `v1..v4` for float rank, probably inlines in the source.
- **fn_801F1FB0.cpp:** `fetchA` exists only for rank, and `FETCH` does the same job as a macro elsewhere.
- **fn_801E8A84:** the `-` / `C` / `B` / `A` table is a compiler-made template, so the checker can't tie it to `lbl_8036EED0` by name. Its strings are literals.
- **fn_801FFCBC:** the jump table is compiler-made; the case order came from the code and table contents were checked by the checker only.
- **Declaration orders** came from `sw.py` and say nothing about the source.

## Lessons not in MATCHING.md

- **The parameter can be pushed down by adding one real local.** `s8 vv = b.v[i];` moved `this` from r31 to r22 in fn_802125CC, and `int y = y0 - 2;` did the same in fn_801EB490. Locals that get forwarded don't count.
- **The parameter can be raised the same way.** Assigning the first local from an inline (`a = fetchA(o);`) gave the parameter r31 and fixed the 33-word rotation of fn_801F1FB0.
- **`int` locals rank high, `s16` locals low.** Toggling types (scratch script `ty.py`) took fn_801EB490 from 50 to 2 and fn_801DF530 from 12 to 1.
- **A short-lived value in the lowest register:** the allocator seems to reuse the lowest register that doesn't interfere, so a low-degree web lands at the bottom whatever its declaration order.
- **A small struct stops constant folding:** `C3 k; k.r = 0x80;` keeps `li r0,0x80; stw; lfd` for a u8-to-float conversion.
- **`if (!b->x40) b->x40 = z;`** right after storing `z` keeps a compare against the saved register and a store behind the branch. Testing `z` itself folds.
- **A float compare in f1 is often a hidden argument:** `lfs f1,K; fcmpu f1,f28` then a call meant `if (k != K) f(o, a, 0, K)`.
- **Slots for a returned point:** to get the return temp below the copy, return through a one-line inline (`Pu r = getP(w); Fl2 q = *(Fl2*)&r;`).
- **`f32 x = q.x; f32 y = q.y;`** before a call fixed the swap of the `0x4330` and string `lis` registers.
- **`y -= 2` is forward-substituted** into every later use. Inside an inline, `int y = y0 - 2;` keeps `subi r20,r20,2`.
- **Three clamped channels in ascending slots:** write them all in one inline, with each channel's locals declared in order.
- **A truly empty struct** (`struct EC {}; f(x, EC());`) gives `li; stb` for the sort functor, but still not `mr rZ,rI`.
- **Flatten before searching:** nested section inlines hid registers in fn_802016AC (72 words). Function-level locals and `sw.py` took it to 15, then 0.
