# Round 13, part b: 0x80213000..0x8023FC24

7 new matches, 0x2148 bytes (8,520). The 25 KB aim was not reached. Every file below prints MATCH from `python3 -I tools/check_func.py <file>`.

| file | function | bytes |
|---|---|---|
| fn_80219018.cpp | 80219018 | 2308 |
| fn_802328F8.cpp | 802328F8 | 1800 |
| fn_8021B444.cpp | 8021B444 | 1508 |
| fn_8022CB28.cpp | 8022CB28 | 1092 |
| fn_8021ED04.cpp | 8021ED04 | 896 |
| fn_8022BCA0.cpp | 8022BCA0 | 508 |
| fn_8021E734.cpp | 8021E734 | 408 |

## Near misses (attempts are not in the tree)

Word counts are from `tools/check_func.py` where it was run, otherwise the `difflib` diff. Sources are in the session scratchpad only.

| function | words | state |
|---|---|---|
| fn_80217DF8 | 1 | From wip. `u16 sel` gets every register right but emits `clrlwi r29,r3,16` where the original has `mr r29,r3`. Any type that gives `mr` swaps `sel` and `yo` (7 words). |
| fn_8021DAD4 | 1 | From wip. Only `add r23,r4,r3` against `add r23,r3,r4`. `w0 + d` swaps the temporaries instead (8 words). |
| fn_8021F0E0 | 2 | Only `addi r4,r1,8; ...; mr r3,r4` on the by-value colour from a virtual call. Copy constructors, reference inlines and returning copy helpers did not reproduce it. Same shape as fn_801E163C. |
| fn_80227DFC | 4 | Zero: the original has `li r0,0` for `a4c` and a separate `li r31,0` in the else arm. Here the first zero lands in r31 and the else arm disappears. About 30 spellings and the `opt_*` pragmas had no effect. |
| fn_8022BE9C | 58 (mostly offsets) | The frame stays 0x40 where the original is 0x30, because the `fctiwz` temp doesn't share the conversion slot. A grid of inline splits did not change it. |
| fn_8022130C | 6 | Every instruction is right. Only the volatile registers around `id`, `a28` and the string (`lbl_80371CCC + 0x75`). Storing `a40` right after `id` gets all registers right but moves the store. The string needs to be defined before the `a28` constant without its store moving, and 40 spellings failed. |
| fn_802173C0 | 10 | The hoisted `lis` of `lbl_803E7290` wants r29 below `ty` and `ty2`, and `en2` and `s` swap. |
| fn_802133F8 | 13 | `nw` and `x` ranks, plus volatile registers in the `cx < 0x130` bit insert. |
| fn_8021A8F4 | 23 | Ranks of `fp`, `c1` and `dw` only. `clrlwi r3,r30,24` on the second colour index is also missing. |
| fn_8022ADF0 | about 30 | The early part is right. The box corner registers are not: `y` and `y2` swap and the temporaries around them are scheduled differently. |
| fn_802286A4 | 42 | Instruction count is exact. The zero wants r31 and 0x191 wants r27. Not solved by the one-iteration loop. |
| fn_8022C384 | about 85 | Count exact, and the held constants are solved by the one-iteration loop. Still wrong: `x0` wants saved r27, `t` wants r29, the `0x81` id wants r31. |

## Skipped

- **Not attempted, read only:** fn_802291A8 (a filter draw, 4 KB of conversions, 15+ saved registers) and fn_8023E264 / fn_8023E8EC (`std::vector` reserve and grow inline, `stmw r14`).
- **Not attempted:** fn_8021BB04, fn_80222E34, fn_8022A8A0, fn_8021E23C, fn_80223CF4, fn_802267D8, fn_80226410, fn_8021C31C, fn_8021C6FC, fn_80216A8C, fn_80221050, fn_8022776C, fn_802225E8, the THP and file-manager functions, and the listed near misses from earlier rounds (their attempts aren't in the tree): fn_8022A174, fn_8022333C, fn_802243D0, fn_8022C080, fn_8023DC38, fn_8022FD08, fn_802307F4, fn_8022E620.
- **Left alone as asked:** the retry-loop family (fn_8021F5C4, fn_8022516C, fn_80213B4C) and the `lbl_8038C1C0` constructor (fn_8022DFE0, fn_80224CCC).

## Caveats on matches

- **`dummy1`:** fn_80219018.cpp, fn_8021B444.cpp and fn_8021ED04.cpp contain a `dummy1` function that only places earlier strings of the pool at the right offsets. It is not original code here, emits code the original doesn't have at this spot, and must be removed when the files are split into real units.
- **Local types and order:** the `/*P*/` declaration orders and most `s16`/`int` choices came from `sw.py` and the type search, and say nothing about the source. In fn_8021B444 and fn_8021ED04, a split `y3` and separate `s4`/`s6` string locals are shaped for code generation.
- **Accessors:** `gx()` in fn_8021B444 and fn_8021ED04 exists only for register rank. The real source probably had a real accessor, but its name and shape are unknown.
- **fn_8021ED04:** `(s16)(int)((char*)FONT->v4c() + k)` is purely to put the call first in the `add`.
- **fn_8022BCA0:** the parameter `a` is an `int` reassigned to the font width through `s16 z`. The real parameter is a pointer, and this pair exists only for registers.
- **fn_8022CB28:** `s16 c` around `v34()` schedules the `li`. `(int)k->x5c` and the `KL` fields are guesses.
- **fn_802328F8:** `L44` and `L50` layouts come from the fn_80208C98 draft. The 0x44 object's `a40` and the help text are typed by use only.
- **Prototypes:** the narrow parameter types on `fn_80008F20`, `fn_801DBA68`, `fn_801DA184` and `fn_801D6F1C` are inferred from code generation. They also differ from what other files in this region declare, because each file declares its own.
- **Names:** struct, field and helper names are guesses, and virtual slots come from offsets.
- **Reference checks:** `__ptmf_scall` in fn_80219018 and fn_8022CB28 is reported as unchecked by the checker. It corresponds to `fn_8028C178` in the original.

## Lessons not in MATCHING.md

- **Constants held in saved registers can come from a one-iteration loop.** `li r29,0; li r30,4; lfs f31` loaded before a `new`, each used once afterwards, comes from `for (i = 0; i < 1; i++, id++) { ...; if (i == sel) ... }`. The loop is removed after constant propagation, so the values stay in registers. This partly answers the "`li` constants held across calls" item from round 10.
- **A trivial accessor raises a local's rank.** `s16 gx(MV* o) { return o->tx; }` with `x = gx(o)` moved `x` above `y` and `w` where no declaration order could. It took fn_8021ED04 from 15 words to 0 and fn_8021B444 from 30 to 3.
- **A greedy type search pays.** Trying `int`, `s16`, `u16` and `u32` on each `/*P*/` line, alternating with `sw.py`, took fn_8021ED04 from 51 to 10 and fn_8022CB28 from 51 to 2. A `u16` that gives a right register but `lhz` or `clrlwi` is a hint that the variable needs an accessor. The script is short: replace one declaration's type at a time and keep the best.
- **Narrow callee parameters fix float-to-byte registers.** `lwz r4,0x74(r1); clrlwi r4,r4,24` rather than `lwz r0; clrlwi r4,r0` means the prototype takes `u8` and the float is passed directly: `fn_80008F20(p, 255.9f * x)`. The same goes for `s16` prototypes on draw calls, which also fixed the `extsh` scheduling.
- **`forEach(o->list.next, &o->list, f)` with by-value inline parameters** puts the sentinel in the low register that a named `sent` local cannot reach, in fn_8022CB28. fn_802173C0 is the other way round and keeps the named form.
- **A colour used by several calls with no copy between them** is a `const C4&` parameter (`addi r8,r1,8` before each call).
- **`if (d > 0) return 4; if (d < 0) return 3; return 1;`** gives the `ble; li; b; li; bge; li; clrlwi` shape. An `int` local with the same arms loses the `clrlwi`.
- **Statement permutation as a probe:** moving a store earlier and looking at which registers come right shows what the original colouring order needs, even if the moved store itself is wrong. It isolated the string definition in fn_8022130C.
- **Constructor families are cheaper than they look.** fn_802328F8 reached 7 words on the second compile and fn_8022130C reached 6 on the third, by copying the helpers from fn_80208C98.cpp and fn_80225DB4.cpp.
