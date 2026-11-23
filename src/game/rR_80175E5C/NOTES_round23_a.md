# Round 23 (agent r23a): equivalent to exact

Tried, still not exact:
- fn_801DB3F4 (2 words: `fill` should share r28 with `mid`): fill/mid/by types and all declaration orders (48 cells), mid computed by reusing fill, a SegA/SegB inline that takes fill as a parameter and reuses it (11 words).
- fn_8017EA78 (sched, colour byte stores and the copy pair): read only.
