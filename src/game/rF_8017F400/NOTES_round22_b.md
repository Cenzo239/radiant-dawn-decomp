# Round 22 (agent r22b)

| Function | Bytes | Level | File |
|---|---|---|---|
| fn_801D0D58 | 0xC0 | exact | `fn_801D0D58.cpp` |
| fn_801D5914 | 0x220 | sched (6 words) | `equiv/fn_801D5914.cpp` |
| fn_801D65EC | 0x2F8 | sched (2 words) | `equiv/fn_801D65EC.cpp` |
| fn_801D820C | 0x350 | sched (2 words) | `equiv/fn_801D820C.cpp` |
| fn_801B6B18 | 0x2B8 | regs (10 words) | `equiv/fn_801B6B18.cpp` |
| fn_801B0E88 | 0x228 | regs (14 words) | `equiv/fn_801B0E88.cpp` |

- **fn_801D0D58** (script VM call): the four pushes must be an inline `*vm->sp++ = v` (a macro gives offset
  stores from one register; the inline gives one register per slot and the first store as `stwx`), and the
  local-clearing loop must start from the field read as `s8` (`F(fn, s8, 0xD)`), not `(s8)` of a `u8` read.
- **fn_801D5914**: a `case 0` that only re-truncates (`x = (s16)x;`) survives as its own block; an empty
  `case 0: break;`, `x = x;` or `x += 0;` merge it with `default`.
- **Argument load order follows the declared parameter order.** fn_800CB0FC declared `(f32, int)` (its real
  order) loads the float first; declared `(int, f32)` the same registers load the other way round. For a
  callee declared correctly, an inline wrapper with the callee's own order did the same for fn_800CA3DC.
- **Real bugs in the old fn_801B6B18 fragment:** `fn_8007E720(5.0f)` is `-0.1f` in the original
  (lbl_804CF334) and the page is drawn at (48, 18), not (0, 0). Both show only as "constant ... but original
  has" lines in `check_func.py -v`; check those before trusting a register-level score.
- **fn_801B6B18**: the s64 flag test with the unfolded zero high word (`li r4,0; srawi r0,r4,31`) is
  `int k = 0x10; s64 m = k; ... if (!(f & m))`.
- **fn_801D820C**: the "array" lbl_804CF7FF is .sdata2 aggregate templates (a 0xFF byte, then white and grey
  4-byte colours). A POD `struct GC { u8 r, g, b, a; }` initialised from braces inside an inline that returns
  it by value gives the `lbz sym+N@sda21` byte reads and the word copy; `static const` locals give a `li` base
  instead. Its fragment also declared fn_8028C764 (`__cvt_sll_flt`) as returning f64.
- **fn_801B0E88**: the fragment only lacked declarations (fn_800D0864, fn_801A1DCC); with them it is `regs`.
  Port caveat: x, y and the help string stay unset for an out-of-range area/tab, as in the original.
- **fn_801D65EC**: the old fragment was already `sched` with its parent; no change.
