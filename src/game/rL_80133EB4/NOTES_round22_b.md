# Round 22 (agent r22b)

| Function | Bytes | Level | File |
|---|---|---|---|
| fn_801386AC | 0xB8 | sched (4 masked words) | `equiv/fn_801386AC.cpp` |
| fn_80144324 | 0x194 | draft (`other`, 0x188) | `wip/r22/fn_80144324.cpp` (+ `.symbols.json`) |
| fn_801478F4 | 0x204 | draft (`other`, 0x178) | `wip/r22/fn_801478F4.cpp` |

- **fn_801386AC**: the wip/near.cpp form (named `zero`, `-(w * 0.5f - x)`) built with mkself.py from
  `fn_801386AC.cpp` is `sched`; symcheck clean.
- **fn_80144324**: what the original shows, for the next attempt: the target temporary is built first (word
  copy of table[0] at 0x2C, x/y stored, copied word by word to the argument slot 0x8), then the eye from
  table[1] at 0x38 with `c->x30`/`c->x34` re-read (an aliasing store, reproduced by a `Vec& T(Vec&, x, y)`
  builder), then table[3] to 0x20. Slots match with `Look(Mtx*, Vec u, Vec e, Vec t)` by value and
  `Vec e = tab[1], t = tab[0];`. Still missing: the three hoisted `addi` table addresses and the reuse of
  the proc pointer's register for the target's z (ours needs one more saved register).
- **fn_801478F4**: the original's 2x unrolled row loop with a strictly sequential nibble chain is not
  produced by `opt_unroll_loops`/`opt_unroll_count` or by hand-written 2x bodies. Draft only.
