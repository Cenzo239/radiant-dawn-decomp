# Round 23 (agent r23a): equivalent to exact

Exact (new files in this folder; the equiv/ and wip/ files are left as they were):
- fn_801A2F14 (0x154) -> fn_801A2F14.cpp (alone; fn_801A3104 and fn_801A3898 stay in wip/fn_801A2F14.cpp). The shared zero `z` declared `s16` instead of `int` moves the int-to-float temporary to r4 (2 words).
- fn_801C6114 (0xE0) -> fn_801C6114.cpp. `const BData* dc` parameter, `unit` read through dc, then `BData* d = (BData*)dc;` (the `li r7,0` vs `stw` order, a 196-cell grid in round 17). The file-level declaration is changed to match.

Tried, still not exact:
- fn_80183944 (3 -> 2 words with field stores b, g, r: the halved colour bytes are stored a, 9, 8, original 8, 9, a). Store and load orders, u8/s16/u32 locals, a const colour pointer.
- fn_8018524C (2 words, case 0 `li` order): Go/Go2 setter inlines, chained assignments, a named zero, volatile; earlier rounds tried ~50 more.
- fn_8019F3A8 (sched, entry pointer r31 vs the saved zero): const parameter, parameter copy, named int/s16/u16 zero and one locals with memset(e, z, ..) (24 cells): no change from 34 lines.
- fn_801A2268 (3 words, `addi r29,r3,4` placement): const parameter makes it worse (21).
- fn_801DA800 (4 words, sel*0x1C temporary r23 vs r18): type grid over every local (singles and pairs), an explicit `k = sel * 0x1C` local.
- fn_801BFB58 (2 words, m r28 vs r29): declaration orders of m/r, block-scoped r.
- fn_801BB530 (4 words, icon x and slot pointer induction order): direct argument, reversed sum, named slot/byte locals, explicit induction variables in the for header in each order (9-10 words).
- fn_8019F108 (4 words, the 0/1 constants in r4/r5 swapped): named s16 zero, cast zero; the const-parameter sweep found nothing for it or fn_8018524C.
