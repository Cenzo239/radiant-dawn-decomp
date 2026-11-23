# Round 7, part a: 0x801DD7D4..0x80213000

53 new matches, 0x8514 bytes (34,068). `python3 -I tools/check_func.py <file>` prints MATCH for all eight files. This is short of the 40 KB aim. About 160 functions in this range are still open.

| file | matched |
|---|---|
| fn_801EFF40b.cpp | 801EFF40 801F044C 801F06D0 801F0BDC 801F0E60 801F136C 80200064 80200570 |
| fn_801FDC38.cpp | 801FDC38 802044F4 80210B00 80210F10 |
| fn_802114BC.cpp | 802114BC 802117F8 80211B98 80211EB4 |
| fn_801F0178.cpp | 801F0178 801F0908 801F1098 8020029C |
| fn_80208844.cpp | 80208844 8020DDFC 80209450 8020EA08 80207EEC 8020D4A4 80206C1C 8020C1D4 8020B250 80210808 8020616C 8020B724 8020A93C 8020FEF4 80207C50 8020D208 8020AE94 8020AF5C 8020B0CC |
| fn_801ED290.cpp | 801ED290 801EE298 801EF2A0 801FF064 |
| fn_801FF6D4.cpp | 801FF6D4 801ED8FC 801EE904 801EF90C |
| fn_801F2228.cpp | 801F7F70 801F84E4 801F85C0 801F86B8 801F2228 80204174 |

## Family solutions

- **Slide tweens (fn_801EFF40 family).** `b` has to be assigned through `if`/`else` directly, not from a ternary or an inline. Then `int dur; int dy; Tgt* b; int dx;` gives r31, r30, r29.
- **`std::advance` on a list (fn_801F0178 family).** The long block of s16 overflow checks is the compiler unrolling two plain loops: `if (n >= 0) for (; n > 0; n--) it = it->next; else for (; n < 0; n++) it = it->prev;` with `s16 n`. See `adv`. The `ATS` inline supplies the rest of the selected-item lookup.
- **u32 split into a stack point.** The open puzzle of `srwi; sth; sth; lwz; stw; lha; lha` is `Pt mk(u32 r) { Pt p; p.x = r >> 16; p.y = r; return p; }` with `Pt q = mk(call());`. This may also solve `fn_800F201C` in `src/game/rE_800E5DE4/NOTES.md`, which was not tried.
- **Scale chain (fn_80208844, fn_80209450 families).** The pointer pattern r3, r4, r5, r3 comes from four nested inlines, one per level, not from hand-unfolded blocks. To get f28 on the outer level, pass the floats by reference from caller locals (`lv0`). Their declaration order has to be chosen per function: `f3, f2, f1, f0` for a single chain, `f0, f1, f2, f3` when an `x34` chain follows.
- **List draw (fn_801ED290, fn_801FF6D4 families).** See "Register allocation" below. `st = (sg > 0) ? -1 : 0;` gives the `neg; andc; srawi 31` form. `-(sg > 0)` and hand-written shifts do not schedule the same.
- **Tab bars (fn_802114BC family).** Declare `s16` parameters on the callee prototype and pass the float straight in. That gives `lwz r4; extsh r4,r4` in place, which casts at the call site do not.

## Register allocation

These held across several functions and are not in MATCHING.md:

- **An inline's return value or a ternary result is coloured ahead of declared locals.** Declaration order then has no effect on that value. Assign through `if`/`else`, or write the expression without the inline.
- **Implicit CSE instead of named pointers.** `mulli r0; slwi r3` followed by two `add`s, with the base saved, comes from repeating `(u8*)o + i * 12 + N` in the source and letting the compiler keep the common part. Named `c` and `s` pointers swap the temporaries. In the fn_801FF6D4 family `c` is a real local and only the `i * 12` side is implicit.
- **A local keeps its register by being written once with a typed class.** An iterator class (`It j(f2); ++j;`) is coloured after plain locals and after inline temporaries, which pushed it to r31 in the merge near miss.
- **Webs are split.** Reusing one C variable for unrelated values does not tie them to one register, so it cannot be used to force a shared register.
- **`neighbourhood` search needs an alignment-aware score.** `lib.score` in `tools/perm` compares position by position, so one extra instruction hides all later improvements. A copy scoring with `difflib` took fn_801ED290 from 85 to 21 words in one run. The scratch copy is in the temporary folder named under Near misses.

## Near misses

Words differ out of total. Sources are in a temporary folder, which is temporary.

| function | diff | state |
|---|---|---|
| fn_80209768, fn_8020ED20 | 2/322 | `s12.cpp`. Only `mr r26,r3` for the `fn_801059B0` result: mine picks r28. |
| fn_80205778, fn_80205AE4 | 4/219 | `q.cpp`. Only the list sentinel in the clear loop: wants r24, gets r26. The second function also needs kind 1, getter fn_801E7114 and its own tables. |
| fn_801FDE7C, fn_80204738, fn_80210D44, fn_80211154 | 18/115 | `ls7.cpp`. List merge, four identical copies. Rotation of `j`, `a` and the second key (r31, r30, r12 wanted). |
| fn_80209E28, fn_8020F3E0 | 16/315 | `db3.cpp`. Structure is right; `id`, the money pointer, `j` and the cursor pointer have the wrong registers. fn_8020A4C4 and fn_8020FA7C are the same shape and were not tried. |
| fn_80205E50, fn_8020B408 | about 80/199 | `q2.cpp`. Widget constructors through `wbInit`. The last six call arguments reuse the constructor's constants, so they are likely the inline constructor's parameters. |
| fn_801E41E4 | 19/238 | Unchanged from round 6. Twenty-four parameter orders of `ptSub2`, bitfields and reassignments all failed to get `extsh r0,r0` in place. |

Not attempted: fn_801F3D28 and fn_801F6C54 (draft read, looks doable with `adv` and `findIf`), fn_80206E14 and fn_80206310 pairs, fn_80204A08 and fn_801FEA10, fn_801F5A44, fn_801F99A0, fn_802125CC and the other constructors above 150 words.

## Caveats

- **Unchecked references.** fn_801ED290, fn_801EE298, fn_801EF2A0 and fn_801FF064, and the fn_801FF6D4 family, depend on `__ptmf_scall`, which the checker does not verify. The instructions match.
- **`volatile` read.** `t = (int)*(volatile f32*)&q->f` in the fn_801ED290 family exists only to stop a second load being merged. The field is almost certainly not volatile. How the original avoided the merge is unknown.
- **Stand-in comparator split.** fn_801FDC38's `sLess` may not be the original form: the merge near miss needed different local arrangements for each of its compares, which suggests the true comparator has not been found.
- **Hidden shapes.** `cen`, `setR`, `mapP`, `setCB`, `setHf` and `lv0`..`lv3` were chosen for code generation. `lv0` and friends in particular replace what is probably one recursive inline.
- **`f32& ` chain.** Passing floats by reference is purely a way to pick float registers.
- **Declaration orders in the fn_801ED290 and fn_801FF6D4 families came from search.** They say nothing about the original source.
- **Macros.** `LIST`, `DRAWL`, `S6`, `SHOW`, `BLK`, `SLIDE_IN`, `SLIDE_OUT`, `LSORT`, `PICK` and `TAB_LOOP` stand in for what are probably templates or shared bases.
- **Prototypes.** `fn_801D820C`, `fn_801D855C`, `fn_800CB3A8`, `fn_800CB278` and `fn_80126D9C` have `s16` parameters from register evidence only. `fn_800CB3A8` keeps its first parameter as `s16` with an `(int)` cast at the call, which is a register choice.
- **File grouping.** Files are grouped by batch. fn_801EFF40b.cpp has a `b` because fn_801EFF40.cpp already exists. fn_801F2228.cpp does not list its lowest address first.
