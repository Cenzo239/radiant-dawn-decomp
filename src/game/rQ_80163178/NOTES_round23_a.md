# Round 23 (agent r23a): equivalent to exact

Exact (new files in this folder; the equiv/ files are left as they were):
- fn_8016A280 (0x248) -> fn_8016A280.cpp. One word (cmplw operand order in `ter == tid`): reading `u->tid` through an accessor `u8 Tid(Unit*)` puts the tile byte first. Plain operand swaps and casts did nothing.

- fn_8016CDEC (0x18C) -> fn_8016CDEC.cpp. Two swapped `mr`: assignment order of the new minimum (m, t, slot instead of t, m, slot).

Tried, still not exact:
- fn_80168BF0 (2 words: `addi` of the map address scheduled before IsM()'s `li r0,1`, original after). Tried: swapping/delaying the Map*/AiAct* locals, macros instead of locals, IsM variants (parameter, declaration order), volatile on the p[0x34] store. ~15 compiles.
- fn_80167F5C (4 words: the y byte is loaded before x into r0 so x can go straight into r3). Tried: accessors UX/UY on either or both, a wrapper with reversed parameters (breaks the u16 >> 4 fold into extrwi), prototype (s8, s8) from CATALOG, y in a local first.
- fn_8016EDE8 (3 words: the shared b5S/ter address temp gets r16, HasW's counter register, where the original gives it r18, the register of v and HasW's walking pointer). Same body as the exact fn_8016E9A8 apart from HasW. Tried: all 4320 declaration orders of the function block x HasW's locals (no change), T0/B5 accessors on the tile reads, HasW taking v->inv, for-header init of p, block-scoped counter.
- fn_80170664 (sched, abs/Reach registers rotated): const on each parameter, Dist/Reach sum orders and named temporaries (80 grid cells), no gain from 20 lines.
- fn_80175C3C (8 -> 5 words with `{ int e = t->e; BOOL c = t->d == 0; int z = 0; t->b = z; t->c = c; t->f = e; }`; d and e still in r3/r4 swapped): ~120 declaration/statement orders of d, e, z, c. Not saved (not exact).
