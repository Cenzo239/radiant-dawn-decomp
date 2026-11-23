# Round 22 (agent r22b)

| Function | Bytes | Level | File |
|---|---|---|---|
| fn_8026A9D4 | 0x130 | regs (8 words) | `equiv/fn_8026A9D4.cpp` |
| fn_8026FC38 | 0x100 | exact | `fn_8026FC38.cpp` |

- **fn_8026FC38** is instruction-identical to rI's fn_801E2104 (scissor-clamp draw callback); its source matched
  at once. Diffing against already matched functions first would have saved the round-14 wip.
- **fn_8026A9D4**: the shared `introFind(i, id)` inline puts `li i,0` above the fn_80109A2C call when called
  with a constant 0 (class `other`); a separate loop written with `for (i = 0, ofs = 0; ...)` keeps it after
  the call. Left at `regs` (id/n/ofs registers).
