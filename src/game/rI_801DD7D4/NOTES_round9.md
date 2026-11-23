# Round 9: 0x801DD7D4..0x8023FC24

42 new matches, 0x3B08 bytes (15,112). The 30 KB aim was not reached. Every file below prints MATCH from `python3 -I tools/check_func.py <file>`.

| file | matched |
|---|---|
| fn_8022B07C.cpp | 8022A6E4 8022B07C |
| fn_8022B758.cpp | 8022B758 8022B880 8022B9B8 8022BA6C 8022BB24 8022BC00 8022C9DC |
| fn_8022CF6C.cpp | 8022CF6C 8022D1CC |
| fn_8022DE0C.cpp | 8022DE0C |
| fn_8022EF60.cpp | 80232428 8022EF60 802319E8 8023126C |
| fn_801F7388.cpp | 801F7388 801F7890 801F8088 |
| fn_801F7110.cpp | 801F76C4 801F7BD0 801F7110 801F98A0 801FB0FC |
| fn_801F7CCC.cpp | 801F7CCC |
| fn_801E82D4.cpp | 801E82D4 802241A8 |
| fn_801F28C0.cpp | 802236D8 801F28C0 802228B8 802124D8 80213310 |
| fn_80204348.cpp | 80228E5C 8022906C 80204348 801FD28C |
| fn_801F1688.cpp | 801F1688 |
| fn_80205258.cpp | 80205258 |
| fn_802167C8.cpp | 802167C8 |
| fn_802289EC.cpp | 802289EC 80227950 |
| fn_80222AD0.cpp | 80222AD0 80223B80 |

Several files hold functions from different address runs, and not always in address order, because they were written as batches. Split them before treating them as translation units.

## Near misses (attempts are not in the tree)

Words differ, by the `difflib` score.

| function | diff | state |
|---|---|---|
| fn_8022A174 (0x484) | 4 real | Four `add r4,rA,r5` come out as `add r4,r5,rA`. `s16 x = r.a` fixes the operand order but breaks registers and scheduling. Case 2 and 7 want the other order and are right. |
| fn_802241A8's siblings fn_801E9F38, fn_8022333C (0x244 each) | 4 | Last block: `y2` wants r26 and the shift r27, plus `extsh r3,r30` on `x`. Registers only. |
| fn_801E84FC, fn_802243D0 (0x184 each) | 10 | `y` wants r26, `base` r27; they coalesce. |
| fn_801F8394 (0x150) | 10 | Registers: count `c` wants r30, name `n` r31, whatever the declaration order. |
| fn_8022C080 (0x1C4) | 10 | Raw count wants r5 and the extended copy r6. They come out swapped in both inlined copies. |
| fn_8022A7CC (0xB0) | 4 | Two products swap r0 and r6. |
| fn_8022ADF0 (0x28C) | 20 | Only scheduling and temporaries in the box setup. |
| fn_8022BE9C (0x1E4) | 8 | Frame 0x40 instead of 0x30: the `fctiwz` temp doesn't share the conversion slot. |
| fn_8022CB28 (0x444) | 34 | Registers only. The hoisted `lis` of the format string wants r31. Search did not finish. |
| fn_8022BCA0 (0x1FC) | 30 | The parameter wants r28 below the locals, the open puzzle from round 7. |
| fn_80232334 (0xF4) | 5 | `v` wants r5 and `done` r4; `v` coalesces with the argument register. |
| fn_801F7110-style fn_801FB050 (0xAC) | 5 | Tail `li r0,0; srawi r0,r0,31; rlwinm r3; or.` is a 64-bit test not reproduced. |
| fn_8022776C (0x1E4) | 19 | Registers: hoisted `lis` wants r30. |
| fn_802286A4 (0x25C) | 39 | Nearly all renumbering. The zero `z` wants r31 above `it`. |
| fn_80223580 (0x148) | 34 | Early-exit layout and ranks. |
| fn_8022A8A0 (0x550) | 132 | Mostly renumbering, one saved register short, and frame 0x10 too small. |
| fn_80224554 (0x350) | 130 | Structure right. Registers follow use counts, not declarations. |
| fn_801E351C, fn_801E64E0 (0x25C each) | 28 | The stack `Pt` copies are the open part. |
| fn_801ECF94 family, fn_80223900 | 12 | Loads want to come before the arithmetic; `const` got fn_80223900 part of the way. |

## Skipped

fn_8023E264 and fn_8023E8EC were read: `std::vector` growth with `stmw r14`, 18 saved registers, not attempted. fn_801F5A44, fn_801F99A0, fn_802125CC, fn_802291A8, fn_8022130C, fn_80219018, fn_802328F8, fn_802038BC, fn_801EBF00, fn_801F3D28, fn_80206310 were not attempted. The retry-loop family and the `lbl_8038C1C0` constructor were left alone as asked (fn_801F17C4 is that constructor).

## Caveats on matches

- **fn_80204348:** uses seven `static u8` arrays by size, to get `addi r3,r31,0x0`. They are in .bss here, while the original `lbl_8038E1D0` is in .data, so the table contents are missing. The checker compares offsets only (`...bss.0`), so the base was compared by eye. A port needs the real data.
- **fn_802319E8:** written as `void`. The asm falls out with whatever is in r3, so it may really have returned a value through paths the source doesn't show.
- **Dummy functions:** `dummy1` in fn_8022B07C.cpp and fn_8022EF60.cpp exists only to place earlier pool strings. They emit code the original doesn't have here; the strings belong to neighbouring functions.
- **Cast tricks:** `*(char*)p` in fn_8022B758 and `++*(s8*)&o->x31` in fn_8023126C exist for code generation. The first works because const and non-const reads aren't CSE'd.
- **Stand-ins:** `forEach((n = o->x48), sent, ft)` with `LNode*&` in fn_8022CF6C is a ranking device. `teSet`, `isSJ` and the `flg` inlines are guesses at real helpers.
- **Search-found orders:** declaration orders in fn_8022CF6C, fn_801F7388, fn_801F7890, fn_801F1688 and fn_80222AD0 came from `sw.py` and say nothing about the source.
- **Reused struct:** fn_802241A8 reuses the fn_801E82D4 body with a shifted struct whose field names therefore lie about offsets (`x52` is at 0x56).
- **Names:** struct, field and helper names are guesses. Virtual slots come from offsets.
- **`__ptmf_scall`:** fn_8022CF6C calls it by the compiler's name. The checker notes this reference as unchecked.

## Lessons not in MATCHING.md

- **Named products:** `int m = a * b; x = m + y;` gives `add rD,rMul,rY` and also fixes all temporaries around it. It solved the fn_801E82D4 grid family at once. `pos % cols` and `pos / cols` share a `divw`.
- **`const` and non-const reads aren't CSE'd.** A reload right after a test (`lbzux; extsb.; lbz` again) comes from reading through a different qualification. Passing `const char* const&` to an inline also blocks it.
- **Signed counter, u32 limit:** `for (int i = a; i < (u32)n; i++, q++)` gives the single-guard 8x unroll (`cmplw; subf; bge; srwi.; mtctr`). A u32 counter gets the longer range checks.
- **CW splits webs.** Reassigning one local does not keep one register. Declare a separate local per use, then search. This solved fn_801F7388 and fn_801E9F38's main body.
- **In-place conditional increment:** `if (++x == y) ++x;` reproduces `clrlwi; addi` on the second increment.
- **`int v = s8field` saved over a call** gives `lbz rN; extsb rN,rN`.
- **Bit clear:** `rlwinm r0,r0,0,25,23` on a byte is a one-bit bitfield set to 0.
- **`extsh` of a parameter before an `add`, with the raw value stored:** the parameters are `int`, and the sum is `(s16)x + (s16)w`.
- **Unrolled scans:** `addic. r4,r0,0x12c` after `add r0,rB,rOff` is `(T*)(b + 0x12c + off)`, with the constant before the offset.
- **`rr.py` is slow on large functions** even with small counts. Bound it by time, or use `sw.py`.
