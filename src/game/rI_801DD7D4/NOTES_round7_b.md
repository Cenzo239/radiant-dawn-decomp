# Round 7, part b: 0x80213000..0x8023FC24

40 new matches, 0x8610 bytes (34,320). The 40 KB target was not reached. Every file below prints MATCH from `python3 -I tools/check_func.py <file>`.

## Files

| file | new matches |
|---|---|
| fn_80213F8C.cpp | 80213F8C |
| fn_80215490.cpp | 80215490 |
| fn_8021773C.cpp | 8021773C 8021876C |
| fn_80218C8C.cpp | 80218C8C 8021991C |
| fn_80219C68.cpp | 80219C68 8021A47C |
| fn_8021ABE4.cpp | 8021ABE4 |
| fn_8021B14C.cpp | 8021B14C 8021BFC0 |
| fn_8021E00C.cpp | 8021E00C |
| fn_8022052C.cpp | 8022052C 8022F67C |
| fn_80225DB4.cpp | 80225DB4 80233000 80227528 802336E8 80233944 80233324 80231DC0 80230A34 802313D0 802315E8 8022609C 80220198 80227B2C 8022EBB8 8022F1A8 80228118 8021FA30 8022D9E0 8022D508 80220B78 80226DF8 8022E2D0 802326F0 802327A4 |
| fn_80234954.cpp | 80234954 80234C48 |

`fn_wf.h` holds the shared widget constructors (`wfInit`, `gInit`, `l84Init`, `l6cInit`). `fn_fe.h` holds the file entry struct and statics, and only the wip attempts use it.

## Near misses, in wip/

- **fn_8023A0BC (wip/fn_8023A0BC.cpp):** 3 instructions out of 676. Only the `lwz r5,0x64(r27)` argument load is scheduled too late before `bl fn_8023835C`. The alloc inlines, `getFl` and the hand-unfolded chain are all right, so this is the template for the retry-loop family.
- **fn_802384F0 (wip/fn_802384F0.cpp):** structure and size match, but `src`/`size` are coloured wrongly. Declaration order, extra inlines and wrappers had no effect.
- **fn_8023AC14 (wip/fn_8023AC14.cpp), fn_802396CC:** same family, with registers rotating between paths. fn_80238FB8, fn_8023BF78 and fn_8023CD24 were read but not attempted.
- **fn_80217DF8 (wip/fn_80217DF8.cpp):** 7 words. `sel` and `yo` are swapped.
- **fn_8021DAD4 (wip/fn_8021DAD4.cpp):** about 18 words of register choice. fn_8021E23C is in the same file, where a float register and a few reloads are wrong.
- **fn_80224CCC (wip/fn_80224CCC.cpp):** about 20 words, including the scroll-bar argument order. fn_8022C384 uses the same widget.
- **fn_80214C00 (wip/fn_80214C00.cpp):** all logic matches. The sentinel registers and the stack order of the filter functors can't both be right yet.
- **fn_8021F5C4 (wip/fn_8021F5C4.cpp):** 25 words, all in the `lbl_8038C1C0` constructor, where the original loads 0x190 before -1. fn_80213B4C, fn_8022516C and fn_8022DFE0 have the same constructor and are blocked by this.
- **Fragments that need the header of their batch file (wip/fn_round7b_fragments.txt):**
  - fn_8022FD08: 2 words, `li r5,0` is scheduled one slot late.
  - fn_802307F4: 2 words, a register in `case 0`.
  - fn_8022E620: 2 words, the help string register.
  - fn_80225650: about 11 scored lines, a constant register and a sentinel register.
  - fn_8021CF08: about 11 scored lines.
  - fn_80235098: the byte pairs in the render mode copy.
  - fn_802286A4, fn_80227DFC, fn_8021B444, plus stale copies of fn_802313D0 and fn_80225650's helpers.

## Skipped

fn_802291A8 (4044 bytes), fn_8022130C (2736), fn_80219018 (2308) and fn_802328F8 (1800) were time-boxed and not attempted. fn_8023E264 and fn_8023E8EC are inlined `std::vector` growth with file statics and were read but not attempted. fn_8022BCA0 was tried and dropped (about 65 scored lines).

## Caveats on matches

- **`int p = h;` is not used by any match here,** only by the wip retry-loop inlines, where it reproduces the original's register choice. It's unlikely to be the original source.
- **Dead `cmpwi`:** the wip `freeData` uses `u32 q = p; if (p != 0) q = p;`. fn_80238FB8 shows the likely original, `if (!p) p = e->data;`.
- **`{ void* t = s; const char* h = ...; setHelpR(t, h); }`** and `{ void* t = s; s = (S3*)...; }` in fn_80225DB4.cpp only control the register of the help string. fn_80233000 assigns a string to its `S3*` parameter, which is not original source.
- **fn_8021E00C** has its whole body in a one-call `static inline`, purely for colouring.
- **fn_8022052C.cpp** sets `inline_max_size(20000)` and `inline_depth(16)` for the whole file, and its `Col k0..k3` locals exist to get the stack order. The real source is probably a temporary inside the arrow constructor.
- **Stand-ins:** struct and class names and most field names are stand-ins. `Wy`, `S4` and similar overlap the same objects with different layouts. `mv6`, `mvR*`, `mv3` and the depth-only wrappers exist to set stack order.
- **Hand-unfolded chains:** `CHAIN`, `fz` and the like stand in for the inlined recursive fn_801E33B4/fn_801E3468, and their declaration order only sets registers.
- **Rewritten shapes:** `fn_80234954`/`fn_80234C48` share a `BODY` macro, which is probably a template in the original. `fn_80219C68` uses `UP`/`DN` macros, and `extern const C4 lbl_80371930[12]` is sized from the symbol.
- **Unverified:** fn_8021ABE4 calls `__ptmf_scall`, which the checker can't verify because it isn't in symbols.txt. I compared it against `fn_8028C178` in the asm.

## Lessons

- **Put every `new` in its own inline.** `static inline T* newT() { T* o = alloc; if (o) {...} return o; }` fixed the registers of long constructor functions (fn_80213F8C) where declaration order did nothing. If the first object still misses, try it directly in the function (fn_8021FA30).
- **Accessor inlines add temporaries that change colouring.** `flg(e, m)` and `par(e)` in the hand-unfolded recursion fixed the chain's whole register rotation.
- **A register that takes the lowest free number looks like a variable that was live earlier.** `int p = h; ...; p = alloc();` gives `p` the same interference as the original.
- **Interleaved `lbz`/`stb` pairs using two registers** come from a sized const source: `extern const C4 tbl[12]` with member copies lets loads move above stores. An unsized `[]` does not.
- **Dead `cmpwi` with no branch** comes from `if (!p) p = same_value;` after copy propagation.
- **`if (p->a31 == -1) ...` right after `p->a31 = 0`** gives `cmpwi rZero,-1` on the forwarded constant (fn_802315E8), or a `b` over a dead store when the assigned value folds (fn_802313D0).
- **Popups:** `XY mk(u32 r)` returned by value into a by-value inline parameter reproduces the `srwi 16; sth; sth; lwz; stw; lha; lha` copy. Assign `f32 x = c.x; f32 y = c.y;` first to get the right register for the 0x4330 constant.
- **Stack order follows inline depth, then source order.** Main-block locals sit highest, and deeper inlines sit lower. Inside an inline, later declarations get higher slots and higher registers, the reverse of a plain function. Wrapping a helper in a one-line inline moves its locals down.
- **Reloading a field across a virtual call:** `template <class T> mvR(void*, T*& w, ...)` taking the field by reference reloads it for each use, and `s16 y = w->y;` first gives the original schedule.
- **Value kept across a nested call:** `u32 v = s->a40; void* w = z->f(); g(w, v);` keeps `v` in a saved register, where `g(z->f(), s->a40)` reloads it.
- **Pointer-chain declaration order inside an inline:** `Wy* r; Wy* q; Wy* p;` reproduced `r3, r4, r5` in fn_8022609C.
- **Literal block `int v = field;` in a shared inline** stops the compiler forwarding a load past a call (`canUp`).
- **Large inlines stop inlining:** when `bl wfInit__...` appears, add `#pragma inline_max_size(20000)`.
- **Checking with the scratch diff:** a diff that normalises sdata2 labels hides wrong float literals. Always finish with `check_func.py`, which compares their values.
