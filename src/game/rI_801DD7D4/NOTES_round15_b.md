# Round 15, part b: 0x80213000..0x8023FC24

12 new matches in 11 files, 0x15B8 bytes (5,560). The 25 KB aim was not reached. Every file below prints MATCH from `python3 -I tools/check_func.py --strict-references <file>`.

| file | functions | bytes |
|---|---|---|
| fn_8021DAD4.cpp | 8021DAD4 | 1336 |
| fn_80226410.cpp | 80226410 | 968 |
| fn_80216A8C.cpp | 80216A8C, 8021D7E0 | 744 + 192 |
| fn_8022776C.cpp | 8022776C | 484 |
| fn_80223998.cpp | 80223998 | 408 |
| fn_8021EA80.cpp | 8021EA80 | 368 |
| fn_8022291C.cpp | 8022291C | 244 |
| fn_80223708.cpp | 80223708 | 244 |
| fn_80228900.cpp | 80228900 | 236 |
| fn_8021D964.cpp | 8021D964 | 172 |
| fn_8021C278.cpp | 8021C278 | 164 |

## Near misses, saved in wip/r15b/

Word counts are `difflib` mismatches (the checker's positional count is higher when lengths differ).

| function | words | state |
|---|---|---|
| fn_802225E8 | 1 | Only `mr r5,r4` is scheduled after `li r6,0` instead of before. Shares the `nth` slot-search inline with the matched fn_8022291C. |
| fn_8022A7CC | 1 | Only the `lha r30,0x4c(r3)` position in the prologue. |
| fn_80227DFC | 2 | The zero: one `li r31,0` is hoisted and shared by the `a4c` store. The original keeps `li r0,0` for the store and a separate `li r31,0` in the else arm. The fn_80228900 fix (below) did not carry over. |
| fn_8021E23C | 6 | Only float registers: the cost result of the two top-level `canUp` tests wants f31 and gets f30. Everything else, including the reloads of `a48`, is right. |
| fn_80223900 | 12 | Instructions right, volatile registers in the row/column arithmetic wrong. |
| fn_802267D8 | 19 | List constructor plus a pointer-to-member filter loop. The 16-byte functor copy loads its last word first in the original. The two list-sentinel registers are swapped. |
| fn_8021C31C | 32 | Card table pick and a 5-widget build loop. Structure is right. Ranks of `n`/`sum` and the walker are off, and so is the inlined size-setter at the top (the same prologue as fn_8021D17C). |

From earlier rounds, still open: fn_8022130C (6 words: id 0x80 wants r5 and 8 wants r0. About 30,000 orders and types of the constant locals, plus inline parameter orders, all stay at 6), fn_80217DF8 (1 word: `clrlwi` against `mr` for `sel`. Return types and local types for `sel` were tried, with sw.py after each, and the best is 4 words when `mr` appears), fn_8021F0E0 (2 words: no spelling of the by-value colour reproduces `addi r4; mr r3,r4`. fn_801E163C has the same shape and is also unmatched).

## Skipped

- fn_80221050 uses the `lbl_8038C1C0` constructor, as told.
- The retry-loop family (fn_8021F5C4, fn_8022516C, fn_80213B4C).
- fn_8022A174 (known puzzle from rounds 9 and 10), fn_80223CF4 and fn_80222E34 (list draws with `std::advance` and `_savegpr_16`/`_20`), fn_8022A8A0, fn_8021BB04, fn_8021C6FC (float heavy). I read these but didn't write them.
- I didn't reopen the THP and archive functions, fn_802291A8 or the vector grow pair.

## Caveats on matches

- **fn_80223708** pulls in an out-of-line `Gd<RList,LNode>` destructor that the checker skips (it isn't in symbols.txt). This is the same `Gd` template as in fn_801E4D1C.cpp.
- **fn_80223998:** the call is `adv(o->next, (int)o->sel)`. The `(int)` cast is there only to keep the `extsh` before each unroll count.
- **fn_8021DAD4:** `lv = l0 + (int)((char*)fn_80126B0C(u) + n) / 100;`. The `char*` cast exists only to put the call first in the `add`.
- **fn_80216A8C:** the `w1`/`ap0`/`rp` wrapper depths only place the `Empty` tag copies at the right stack slots. `n2`/`p2`/`n3`/`p3` are split locals, and the `/*P*/` order came from sw.py. MslString is the same layout as in region S.
- **fn_8021EA80:** `*(const f32*)&o->a40 < t` together with a separate `c` read are there for float registers and the reload.
- **fn_80228900:** has a dead `x = NULL;` before the call. The later `if/else` reassigns `x`. This is what makes the `a4c` store share `li r31,0`.
- **fn_8021D964:** uses `const S4C2*` and re-reads `o->a48 + 1`. This gives the `mr r0,r31` copy.
- **fn_8021C278:** the float is re-read with `v = ...; v = ...`.
- **fn_80226410:** `setPos` has its statement order from a search. Its `Pe` struct is named differently from `Eff` because fn_wf.h already defines `Eff`.
- **Names and types:** names, fields and the `It::*` pointer-to-member type are guesses. `lbl_803900D8` is declared as a `PF` extern (only in the fn_802267D8 wip).

## Lessons not in MATCHING.md

- **`std::advance` with an s16 count:** passing `(int)field` into an `adv(LN*, s16 n)` inline keeps the `extsh r3,r5` before each unrolled `subi`/`srwi` count. Passing the field directly drops it.
- **Write the zero early to share it:** `x = NULL;` before an unrelated byte store, followed by `if (it) x = f(it); else x = NULL;`, reproduces a saved `li r31,0` that the store also uses (fn_80228900).
- **`int k = (s8)...` in a sum:** `l0 + (int)((char*)call() + n) / 100` gives `add rD, rS8, rQuot` with the call first in the inner `add`. Ten other spellings were one word off.
- **Size-setter inline (`ix0=0; iy0=0; ix1=w; iy1=h; tx=ty=0; a1a=w>>1; a1c=h>>1`):** it appears at the top of fn_8021D17C and fn_8021C31C and resisted every order and type tried (best 3 words in isolation). Don't spend time on it without a new idea.
- **Scorer bug in round-13 tools:** `lib.parse` doesn't mask `lbl_804CF*` sdata2 floats, so every float load scores as a difference. Masking `lbl_804C[C-F]*` and `lbl_804D*` and scoring with difflib made searches usable on these files.
- **Run copied tools by absolute path:** `sw.py` and `rr.py` make their temp folder next to the script path they are given. Run as `perm/sw.py` from the scratch folder, every compile fails silently and the search scores 9999 throughout.
- **A `grep -h ... | grep -v wip` filter does nothing:** without file names, wip definitions count as matched. Build "open function" lists from `grep -r` with the file name kept.
- **Save near misses as you go:** the scratch folder was wiped during the usage pause, and one recreated near miss (fn_8021C31C) had to be rewritten from the transcript.
