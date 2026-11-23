# Round 22 (agent r22b)

| Function | Bytes | Level | File |
|---|---|---|---|
| fn_80176B0C | 0x48 | exact | `fn_80176B0C_b.cpp` |

- **fn_80176B0C** (2D distance): the round-5 `frsp f0; fmr f1,f0` puzzle is solved by routing the sqrt call
  (fn_80295CF0, f64) through `static inline f32 sq(f32 x) { return (f32)fn_80295CF0(x); }` with
  `if (0.0f == d) return 0.0f; return sq(d);`.
