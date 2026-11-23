# Round 10: 0x801DD7D4..0x8023FC24

34 new matches, 0x3B94 bytes (15,252). The 25 KB aim was not reached. Every file below prints MATCH from `python3 -I tools/check_func.py <file>`.

| file | matched |
|---|---|
| fn_801E32C8.cpp | 801E32C8 |
| fn_801E41E4.cpp | 801E41E4 801E459C 801E495C 801E59A8 801E5D60 801E6120 801E351C 801E64E0 801E3E1C 801E3EE0 801E518C 801E3778 801E673C 801E3C18 |
| fn_801E75B0.cpp | 801E75B0 801E769C 801E8D60 801E74CC |
| fn_801E1454.cpp | 801E1454 801E2104 |
| fn_8022B620.cpp | 801E6A88 8022B620 8022B6DC 8021C1EC |
| fn_8021CA54.cpp | 8021CA54 80225C70 80224AAC |
| fn_80224BCC.cpp | 80224BCC 802237FC 801FAF74 |
| fn_80215688.cpp | 80215688 |
| fn_802248B4.cpp | 802248B4 |
| fn_80234888.cpp | 80234888 |

Files hold batches, not translation units, and several mix address runs. Split them before treating them as units.

## Near misses (attempts are not in the tree)

Word counts are from the `difflib` score unless marked.

| function | diff | state |
|---|---|---|
| fn_801EBF00, fn_801EC414, fn_801FE108 | 14 | Down from 19 with `int zq = s->w.a26; int xq = ...;` before the inline constructor call. `x + 8` wants a register that clashes with `li r0,-1`, so it looks computed before the -1 is loaded. Tried without effect: parameter orders, `const&`, a `Rect` struct argument, named temporaries, dead uses. Probably the same puzzle as `0x190` before -1. |
| fn_8022A174 | 12 | `{ s16 a; int raw = 0x250 - w; a = raw; r.a = raw; ... a + w ... }` fixes the `add` order and registers in cases 1 and 4. The same form in cases 3 and 6 gives the sum r11 and the quotient sign r4, where r4 and r5 are wanted. With plain `r.a + w` everywhere it is 6 words. |
| fn_801E9F38, fn_8022333C | 5 | `px` wants r25 and `extsh r3,r30` is folded to `mr`. |
| fn_801E84FC, fn_802243D0 | 10 | `y` and `y2` swap whatever the declaration or reuse. |
| fn_801E2F40 | 6 | Registers solved. The `Pt` temp wants 0xC, the copy 0x10, the result 0x8. About 25 nesting forms reached other orders only. |
| fn_801E7218 | 10 | With the loop in an inline, only the counter and unit pointer swap (r27, r28). |
| fn_801E7A28, fn_80223998 | about 25 | Shape exact. `n` wants r5, and the overflow flag r4; they come out swapped. |
| fn_801E7990, fn_80223900 | 12 | Reads right, products take the wrong volatile registers. |
| fn_801E163C | 6 | Rank of `h` and `y`, and `addi r4,r1,8; ...; mr r3,r4` on the colour copy. |
| fn_801E9CA8 | 42 | Instruction count is exact. Registers and the last block's load order are open. |
| fn_801F1FB0, likely fn_801F37BC | 33 | Pure rotation: the parameter wants r31 above the first local (r30). Copying it to a first local, inline splits and order changes all failed. |
| fn_80201110 | 6 | First-block `w` and `d` swap, and the second `c` wants r26. |
| fn_8021CF08 | 33 | Ranks only. |
| fn_8021EA80 | 9 | The target wants f3 and the field f2. |
| fn_80228900 | 11 | The hoisted `lis` wants r30 and `r` r31. |
| fn_8022291C | 18 | `k` and `it` swap (r7, r8). The inline with `return e` gets the `bne; b` shape. |
| fn_80230FB0 | 16 | The list pointer and counter swap (r6, r7). |
| fn_8021C278 | 4 | Only f0 and f1 around the `180.0f` add. |
| fn_8023DC38 | 1 | Store and register order at the start. |
| fn_8021D964 | 4 | `mr r0,r31; addic. r4,r0,1` and the early load of 0x48. |
| fn_8022C2D8 | 23 | The zero wants a saved register across the virtual call. |
| fn_801E31D4, fn_801E5640 | about 60 | Reverse iterator held on the stack. A nested `RS { cur, base }` keeps it in memory, but the two by-value copies and the reused deref are not reproduced. |

## Skipped

- **Read, not attempted because of the register count:** fn_801FEA10 and fn_80204A08 (`std::vector` growth, `stmw r14`).
- **Not attempted:** fn_802038BC, fn_801F5A44, fn_801F99A0, fn_802125CC, fn_802291A8, fn_8022130C, fn_80219018, fn_802328F8, fn_80232334, fn_801FB050, fn_8022C080, fn_801F8394.
- **Left alone as asked:** the retry-loop family and the `lbl_8038C1C0` constructor.

## Caveats on matches

- **`Pt` with `u16` fields:** fn_801E32C8 and the tween family need `u16 x, y` read through `(s16)` to get `lhz; extsh`. The real type may differ (a template or a copy idiom), and field signedness in `Tw` is a code-generation choice.
- **fn_80215688:** `dummy1` only places the earlier strings of the pool at the right offsets, so it emits code the original doesn't have here. The literals are real and the checker verified the ones this function uses, but they belong to neighbouring functions' pool order.
- **Stand-ins:** in fn_8022B620.cpp, `int t = 0; p = (char**)t;` in `cols` exists only for register order. In fn_801E41E4.cpp, `const Ps& cf`, the int locals in `rate` and `twApply`/`twScale` are shaped for code generation.
- **fn_801E74CC, fn_8021CA54, fn_80224AAC, fn_80225C70, fn_801FAF74:** declaration orders came from `sw.py` and say nothing about the source.
- **Prototypes and types:** `fn_801E8D60` and `fn_80224BCC` take `Eq` by value with a padding word, inferred from the stack. `HV` (a handle released through `fn_80011CBC`) is a guess at a smart pointer. Struct, field and helper names are guesses, and virtual slots come from offsets.
- **Reference checks:** the checker skips the compiler-emitted out-of-line destructors (`__dt__17Gd<...>`, `__dt__2HV`). They come from `#pragma auto_inline off` and don't exist in the original at these names, so a real build needs them removed or inlined.

## Lessons not in MATCHING.md

- **`lhz; extsh` is a `u16` field read through `(s16)` after a struct copy.** `Pt r = a; r.x = (s16)r.x + b.x;` on `struct { u16 x, y; }`, with the other operand on an `s16` struct. A direct `(s16)v.x` from memory still gives `lha`. This solved the open puzzle from rounds 6 and 7.
- **An int local blocks CSE of an int-to-float conversion.** `int b0 = p->x + 1; f32 b = b0;` shares the integer add but repeats the `xoris; stw; lfd; fsubs`. `f32 b = p->x + 1` reuses the earlier conversion.
- **Order int and float locals separately.** `int b0; int a0; f32 a = a0; f32 b = b0;` sets the integer order and the conversion slots independently.
- **`const Pt& v` with `Pt n = v;` one inline down** mirrors the return temp and copy slots, as the Vec lesson says for `Vec`. It also applies to the 4-byte `Pt`.
- **`const T&` local aliases control CSE per field:** `const Ps& cf = p->from;` declared after the first use got both field reads to reuse the earlier loads.
- **`bne L; b M; L:` before a range-erase body comes from `return` in an inline that returns a value used by the caller.** `it = erase(l, it, j); if (it == end) break;`. A void inline, `goto`, `switch` and an empty `if` all give `beq`.
- **Placement `new` adds its own null test,** and so does `p->~T()`. Remove any hand-written `if (p != NULL)` around them. Declare `operator new(unsigned long, void*)` outside `extern "C"`.
- **Named functor argument:** `Eq e(x); f(l, e);` and `f(l, Eq(x))` give the same slots here, unlike a named variable passed to an inline that copies it.
- **`li r4,..` unused at a call can be `o` passed as a second argument:** `mr r4,r3` before `lfs fN,off(r3)` meant `fn_801A1AC4(lbl, o, ...)`, and `lwz r4,0x40(r3)` before a call meant an argument, not a local.
- **Inline arguments set pool string order.** `mk("A", "B")` through an inline pools `B` first. A direct call pools `A` first. `setHelp(o, "S")` with `const char* const&` keeps the string in a saved register across the call.
- **`cmpwi r0,N; beq A; bge B; b B`:** add the empty lower cases, as with case 3, for any N. It reproduced fn_80234888 with `case 4`.
- **Reusing one local doesn't pin a register, but splitting does help search:** give each def-use web its own local, then run `sw.py` (fn_80201110 went from 19 to 11 this way).
