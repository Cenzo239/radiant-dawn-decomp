# Round 23 (agent r23a): equivalent to exact

Tried, still not exact:
- fn_801197F4 (4 words, 2 with `const SData* p`, which moves the load above the `stw r29`; left: the load goes straight into r30 instead of `lbz r0; extsb r30,r0`. With the const parameter every separate-extsb spelling ((s8) of a u8 field, SV/SV2 accessors, by-reference Cl/Sub inlines) still loses the v/result coalescing (14 words, 52 instead of 53). Before: `lbz r0; ...; extsb r30,r0`, ours loads straight into r30). `(s8)` cast of a u8 field gives the separate lbz/extsb but then v goes to r31 and the clamped result to r3 (17 words); s8 locals, Clamp/Calc inlines taking the value or an s8 parameter, return types int/s8, `v = (s8)v` after an int load: 96-cell grid plus ~15 hand variants.
- fn_8012152C (sched): spellings of the saved tile byte (index operand order, pointer to the tile, declaration order) stay at 41 differing lines.
