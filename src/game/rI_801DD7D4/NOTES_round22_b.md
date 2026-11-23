# Round 22 (agent r22b)

| Function | Bytes | Level | File |
|---|---|---|---|
| fn_8023FC50 | 0x78 | exact | `fn_8023FC50.cpp` |
| fn_8023FCC8 | 0x68 | exact | `fn_8023FC50.cpp` |
| fn_80235098 | 0x230 | exact | `fn_80235098.cpp` |
| fn_802352C8 | 0x244 | regs (10 words) | `equiv/fn_802352C8.cpp` |
| fn_801E2F40 | 0x188 | slots (9 words) | `equiv/fn_801E2F40.cpp` |
| fn_801EB490 | 0x474 | sched (1 masked word) | `equiv/fn_801EB490.cpp` |

- **fn_8023FCC8** is a static initialiser (five vptr-only menu entries plus a `{table, vptr}` menu definition);
  the file header quotes the global definitions the port should use instead of the stores.
- **fn_80235098 / fn_802352C8** are the Revolution DEMO library's `__DEMOInitRenderMode` and `__DEMOInitMem`.
  The render-mode copy is a plain `rmodeobj = *mode;` (the implicit C++ copy of GXRenderModeObj gives the
  bytewise `sample_pattern` pairs the round-7/8 drafts tried to spell field by field).
- **fn_801E2F40** (Group::AddChild): the position fix-up uses the real `Pu + Pt` helper fn_801E32C8 (inlined;
  the `lhz; extsh` pair is its `(s16)` read of a `u16` copy) and a subtracting twin. The list part needs
  `listFind(...) == &l->prev` inline in the `if` and the sentinel passed again as an expression to the push,
  not named locals (named locals swap the node and sentinel registers).
- **fn_801EB490**: the round-13 fragment lost its `hdr.h`; rebuilt on fn_801EAF64.cpp's declarations it is
  `sched` with symcheck clean. `tys.py` made it "better" by turning `yy` into `s16`, which symcheck flags as
  a behaviour change (truncation): the int version is kept.
- **CATALOG caveat:** fn_8012C250 is listed as `void` (rH definition) but tail-calls fn_8012C0A8 and its
  value is used by fn_801EB490 and 21 other declarations; it returns int.
