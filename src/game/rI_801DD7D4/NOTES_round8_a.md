# Round 8, part a: 0x801DD7D4..0x80213000

20 new matches, 0x6040 bytes (24,640). This is short of the 35 KB aim. `python3 -I tools/check_func.py <file>` prints MATCH for all five files.

| file | matched |
|---|---|
| fn_80206E14.cpp | 80206E14 8020C3CC |
| fn_80207670.cpp | 80207670 8020CC28 80208388 8020D940 80209768 8020ED20 80209E28 8020F3E0 8020A4C4 8020FA7C |
| fn_80208C98.cpp | 80208C98 8020E250 |
| fn_80205778.cpp | 80205778 80205AE4 |
| fn_801FDE7C.cpp | 801FDE7C 80204738 80210D44 80211154 |

`fn_shop.h` holds the shared shop declarations. `fn_801FDE7C.cpp` declares what it needs itself.

## What unlocked these

- **`fn_80105158` takes the convoy pointer as `this`.** `bl fn_801059B0; mr rN,r3; bl fn_80105158` has no visible argument setup because r3 already holds it. Declaring `int fn_80105158(void*)` and writing `*m - fn_80105158(m)` fixed the "wrong register for the money pointer" miss in five families at once. No declaration order could.
- **Caller locals passed by reference to an inline.** A local in an inline or a compiler temporary can't be ranked. Declaring it in the caller and passing `T*&` puts it in the declaration search. This fixed the sentinels in fn_80208C98 (`newL(s, s2)`, `newN(s3)`) and fn_80205778 (`ilClear(l, z)`, `listAdd(l, v, e, n)`).
- **List size and cursor:** `u32 sz = --l->size; s16& c = ((SWa*)w)->cur[j]; if (c >= sz) c = sz - 1;` gives `lwz r4; add r3` where every other spelling swapped the two registers.
- **Block scope in fn_8020A4C4.** `s16 n2` and `int id2` as block locals got the right registers where a reused function-level `n` didn't. fn_80209E28 then needed them back at function level, in search order.
- **Two member effects in one widget (`Eff`).** Use `Eff* m = &o->m2; effC(m, 3); ((VO0N*)m)->v0C(); effD(m);`. The `0x78(r29)` stores with `r25` afterwards appear only in this form. In fn_80208388 the first member's pointer `m1` must be declared before `o` in the alloc inline.
- **Dead vtable store:** `gInit((G40*)o, ...)` keeps the base vtable store. `gInit(&o->g, ...)` followed by `o->g.w.vt = ...` removes it as dead.
- **Inline constructor shape:** `sbInit(o, y, w, h, x, z)` with `wfInit(&o->w, x, y, x + w, y + h, w, h, z, fl)`. Inline arguments are evaluated right to left, so parameter order sets load order.
- **Plain locals in the merge (fn_801FDE7C).** Replacing the iterator class and block locals with one flat list of function-level locals let `sw.py` reach 0 from 40.

## Near misses, in wip/

Words differ out of total, by the `difflib` score.

| function | diff | state |
|---|---|---|
| fn_802038BC | 16/326 | Zero-byte idiom below, `addi r4`/`addi r5` order in the clamp, one saved register. |
| fn_801EBF00, fn_801EC414, fn_801FE108 | 19/239 | fn_801FE108's disassembly is identical and fn_801EC414 has the same shape. Only the base constructor's constants: the original keeps `x` in r27 and `x + w` in r10. |
| fn_801F3D28, fn_801F6C54 | 46/264 | Instruction shapes are right. Registers only, plus the zero-byte idiom. fn_801F6C54's disassembly is identical. |
| fn_80206310, fn_8020B8C8 | 54/579 | The 0x158 puzzle and zero-byte idiom below, plus the pointer-to-member slot order (0x24 and 0xc wanted, 0xc and 0x24 produced). |
| fn_801E459C | 88/240 | Unfinished: an earlier draft was at 74. The float block is not settled. fn_801E495C, fn_801E5D60 and fn_801E6120 are the same shape. |

Not saved to wip: fn_80205E50 and fn_8020B408 are still at about 80/199 from round 7's `q2.cpp`, with no progress this round.

## Open puzzles

- **Zero-byte idiom:** `li rI,0; li rJ,0; mr rZ,rI` before a loop calling a list sort with `stb rZ,8(r1)`. It's in fn_80206310, fn_802038BC, fn_801F3D28 and fn_80202344. `while (1) { ...; if (++i == N) break; }` gets the `bne`, but about 25 spellings of the byte, including uninitialised functors and copies of `i`, all give `li rZ,0`.
- **The 0x158 register:** the list constructor with `fn_8028BFD8` wants `li r8,0x6c; li r7,0x158`, and produces `li r7,0x6c; li r26,0x158`, which pushes every saved register down one. It's in fn_80206310 and fn_80202344. Inline parameter order and const locals had no effect. Moving stores helps, but store order is visible in the output, so that isn't the answer.
- **fn_80205E50's `li r0,0x190` before `li r5,-1`** looks related: a constant argument loaded ahead of the base constructor. fn_80213B4C, fn_8021F5C4, fn_8022516C and fn_8022DFE0 have the same constructor.
- **fn_801FEA10 and fn_80204A08** (`std::vector` growth with `stmw r14`) were read but not attempted.

## Skipped

fn_801F5A44, fn_801F99A0 and fn_802125CC were not attempted, because the families above paid better. fn_80202344, fn_8020291C, fn_80202FF4, fn_802016AC and the other shop functions above 0x80200000 remain open.

## Caveats

- **Search-found orders.** Declaration orders in fn_80206E14, fn_80207670, fn_80208C98, fn_80209E28, fn_80205778 and fn_801FDE7C came from search and say nothing about the original source.
- **Reference parameters.** `s`, `s2`, `s3` in fn_80208C98, and `z`, `le`, `ln` in fn_80205778, exist only to rank registers. Assigning `s3` in `newN` and passing sentinels as parameters to `g2` is not likely to be the original.
- **Inlines.** `effC`, `effD` and `effX` were split for code generation and probably stand in for real constructors.
- **Macros.** `BODY_*`, `MK` and `MERGE` stand in for what are probably templates or shared bases. The paired functions differ only in list slot, count and callbacks.
- **Prototypes and struct fields.** `fn_801A1F64`, `fn_8010E41C` and the `VS`/`VL`/`VA` slots come from register evidence. Field names are guesses. The `L7C`, `L50` layouts have only the offsets these functions touch.
- **`*(int*)o->c = 0`** in `newD` in fn_80208C98.cpp writes field 0x40 through the wrong member. The layout is `L50` reused for a different widget.
- **Emitted helper.** fn_80205778.cpp also emits `__dt__2GdFv`, which the checker skips because it isn't in symbols.txt. I didn't check whether the original object has one.

## Lessons not in MATCHING.md

- **Check for a hidden `this` first.** When one short web after `bl X; mr rN,r3; bl Y` has the wrong register, try passing it to Y.
- **Register choice is not simply "highest free".** In fn_80209768 the money pointer stayed in r28 across 10 random declaration orders while r29 to r31 were free. Working theory, not confirmed: a web reuses the lowest register it doesn't interfere with, in colouring order, and a web's order moves when it becomes a declared local.
- **`sw.py` needs absolute paths when copied.** With a relative `argv[0]`, its temp folder is resolved against `ROOT` and every score is 9999.
- **`sw.py` takes the name of an inline as its third argument** and searches the `/*P*/` block there while scoring the caller. It also stops after 6 rounds, so rerun it if it's still improving.
- **`cmpwi; bne` on a call loop** comes from `while (1) { ...; if (++i == N) break; }`. `for` gives `blt`, even written with `!=`.
- **Functor with pointer-to-member:** `extern MF0 lbl;` with `MemF(MF0)` and a by-value `forEachA(b, e, memf(lbl))` reproduces the `lwzu` copy to two stack slots. Passing a PMF to a virtual call passes a stack copy by pointer.
- **Word copy with `lwzu`** from a `.data` or `.rodata` label is a pointer-to-member assignment, not a struct copy (`b->t = lbl_803741A8`).
- **Arguments computed before an inline's stores** force later reloads. `setXY(w, x, 4 - h)` reproduced the second `lha` pair that separate `setX` and `setY` calls lost.
- **`int m = call(); f(m + a)`** gives `add r4,r0,r26`, where the expression form gives the operands the other way round.
