# Round 6, part a: 0x801DD7D4..0x80213000

119 new matches, 0x6844 bytes (26,692). `python3 -I tools/check_func.py <file>` prints MATCH for all nine files. About 213 functions in this range are still open.

| file | matched |
|---|---|
| fn_801E4D1C.cpp | 801ED010 801EE018 801EF020 801FE938 801E5448 801E5734 801E4D1C 801E4F50 |
| fn_801EDC18.cpp | 801FF9F0 801EDC18 801EEC20 801EFC28 801EDE3C 801EEE44 801EFE4C 801FFC14 |
| fn_801FAD10.cpp | 801FAD10 801FAE74 801FCAA0 801FCCEC |
| fn_801FB194.cpp | 801FB758 801FB7F0 801FB8A8 801FB96C 801FBA24 801FBBC8 801FBE14 801FBF08 801FBF64 801FB560 801FB668 801FBC34 801FB194 |
| fn_801FC014.cpp | 801FC014 801FC0D8 801FC12C 801FC1C4 801FC274 801FC338 801FC3E4 801FC4A8 801FC570 801FC680 801FC73C 801FC824 801FC94C 801FCEFC 801FCFC0 801FD0EC 801FD198 801FD434 801FD5AC 801FD718 801FD894 |
| fn_801FE504.cpp | 801FE504 80204944 80211384 802113E0 |
| fn_801FE5F8.cpp | 801FE5F8 801FE698 801FE76C 80205594 802121F8 80212348 801FEF10 801FFE90 8020540C 80211D2C 80212070 |
| fn_80200E50.cpp | 80201B64 801FDAF8 801FDBB0 8020446C 80201F38 802049A0 80201CE0 80201D58 80201FBC 80202034 801E1BB0 801E1BEC 80201DD0 80203838 80203DD8 80203EC4 80203F80 80204064 802041FC 80204284 80204454 802053FC 80205584 802056E4 80201E94 80200E50 80201388 80201508 |
| fn_80208264.cpp | 80208264 80208A84 8020D81C 8020E03C 80209DAC 8020A448 8020F364 8020FA00 80208B08 8020E0C0 80208C00 8020E1B8 80209C70 8020F228 8020A314 8020F8CC 8020AC0C 802101C4 8020AD10 8020ADD8 8020B03C 8020B1C8 |

## Family solutions

- **List insert (wip fn_801E5448 and the push_back family).** Three things were needed together: a guard class with members in the order `{list, node}`, the sentinel passed as `LNode* const& e` from a local in the caller, and the value written through the guard, `RObj** p = &g.node->val; if (p) *p = c;`. Writing through `&n->val` keeps the sentinel and node registers swapped. See `rPush` in fn_801E4D1C.cpp and `INS2` for the 8-byte value version.
- **`for_each` with a pointer to member (fn_801EDE3C family).** Use a real list member and write `forEach(o->l.next, (LNode*)&o->l.prev, g)`, with the inline returning the functor. Computing the end pointer from `(u8*)o + 0x44` swaps the registers.
- **Pointer-to-member calls.** `bl fn_8028C178; nop` and `bl fn_8028C148` are `__ptmf_scall` and `__ptmf_test`. `(o->x3c->*o->x44)(a, n, 1)` with `if (o->x44 != NULL)` compiles to them directly (`SEL`, fn_801FFE90 family).
- **12-byte struct copy (fn_801FE504 family).** A by-value struct parameter arrives as a pointer: `void f(O* o, T3 v) { o->x44 = v; }` loads all the words first.
- **Rectangle setters (fn_801E1BB0, fn_80201CE0 families).** `setI2` with `int` parameters matches. fn_80201F38 needs `int` for the first three and `s16` for the last (`setI3`).
- **Fades (fn_801E4D1C, fn_801E4F50).** Declare `f32 b; f32 a;` in that order. `r` really is uninitialised on the default path.

## Near misses

Words differ out of total. Only the first three rows have source kept, in a temporary folder, which is temporary. The rest were pruned, so only the description below survives.

| function | diff | state |
|---|---|---|
| fn_801E41E4 | 19/238 | `near_TWEEN.cpp`. Structure is right, volatile registers are not. The `lhz; extsh` read of the target point is reproduced only by the `int` parameters of `ptSub2`. fn_801E459C and fn_801E495C differ from it only in mode; they, fn_801E59A8, fn_801E5D60 and fn_801E6120 were not tried. |
| fn_801FF6D4 | 26/199 | `near_DRAWL.cpp`. Wants n=r28, y=r27, px=r29, x=r30. Declaration hill climbing reached 24. fn_801ED8FC, fn_801EE904 and fn_801EF90C differ only in offsets and were not tried. |
| fn_801EFF40 | 8/142 | `t1.cpp`. Only `b` and `dur` are swapped (r29 and r31). `o->x40++;` as its own statement fixed the rest. Siblings not tried. |
| fn_80208844, fn_8020DDFC | about 10/112 | Pointer chain wants r3, r4, r5, r3 where the hand-unfolded chain gives r4, r3, r4, r3. This probably needs the real recursive inline. |
| fn_801FE8BC | 10 to 13/31 | fn_801ECF94, fn_801EDF9C and fn_801EEFA4 share the shape. Load order of 0x1E, 0x20, 0x58, 0x70 not reproduced. |
| fn_801FFCBC | about 28/113 | Rotation: wants o=r27, k=r28, i=r29. |
| fn_801FA508, fn_801FAC44 | 7/52, 7/51 | Keep `cmpwi r31,0; bne` on a register known to be zero. The compiler folded every version tried. |
| fn_801FB050 | 5/43 | `li r0,0; srawi r0,r0,31; or.` u64 test not reproduced. |
| fn_801E32C8 | 6/14 | Needs `lhz; extsh` with no stack copy. Probably the same trick as fn_801E41E4. |
| fn_801FB0FC, fn_801FD28C, fn_801FAF74 | 2 each | One register or store order. |

fn_80204348 uses `addi r3, r31, 0x0` on a pooled base and was dropped.

Not attempted: fn_801F0178 and its family (`std::advance` with s16 overflow checks), fn_801FDC38 and fn_801FDE7C (list sort and merge, 4 copies each), fn_801E518C, fn_801E2F40, fn_801E75B0, the 0x80206310..0x8020FEF4 pairs above about 100 words, and most other functions above 150 words.

## Caveats

- **Unchecked references.** The checker does not verify `__ptmf_scall` and `__ptmf_test`, because they are not in symbols.txt. fn_801FFE90, fn_8020540C, fn_80211D2C, fn_80212070, fn_801EDE3C, fn_801EEE44, fn_801EFE4C and fn_801FFC14 depend on them. The instructions match, and the asm's fn_8028C178 and fn_8028C148 were identified as these helpers from their call pattern only.
- **Macros, not source.** `INP`, `SEL`, `SETCUR`, `INS2`, `FADE`, `DRAW1/2/3`, `FOREACH` and others stand in for what are probably templates or shared bases. Their `*(s16*)((u8*)o + N)` access is not how the original was written.
- **Register shaping.** These choices exist only to get the right registers: the outer `int y2` in fn_80200E50, `s8 c` before `i` in fn_801FD0EC, `dr2` in fn_80200E50, and `#define s` in fn_801FB560.
- **Hand-unfolded recursion.** fn_801FD894, fn_80209C70, fn_8020F228, fn_8020A314 and fn_8020F8CC write the scale recursion out by hand.
- **Guessed types.** Class and struct names, parameter types and slot signatures are stand-ins. `T3`, `PtS`, `It` and similar were chosen for code generation only. The `arg` in `FOREACH` is an `int` that may really be a pointer.
- **File grouping.** Files are grouped by batch, not by translation unit. Some file names are not the lowest address in the file.

## Lessons

- **`cntlzw; li r3,N; srwi.; beq`:** `BOOL b = f() == 0; int r = N; if (b) r = 0; return r;`.
- **`0x4e-0x40` is a compile error,** because `e-` is read as an exponent. Put spaces around the minus.
- **`l->x + f()->x` keeps the call first.** To load the field first, take the result in a named pointer: `Ent* e = f(); l->x + e->x`.
- **Casted offsets get a hoisted base.** A `(u8*)o + N` macro gets `addi` hoisted when used several times. A per-instance struct generated by the macro avoids that (`P##fn`).
- **`hill.py` needs an absolute script path under `-I`,** because it finds `lib.py` from `argv[0]`.
- **Cluster before writing.** Comparing normalised asm across open functions found many exact or offset-only copies, and solving one then gave up to four.
