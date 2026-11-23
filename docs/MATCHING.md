# Matching functions

How to turn functions from `main.dol` into C that compiles to the exact same code.

## Tools

- `build/RFEE01/asm/*.s`: the original disassembly, one file per auto-split object, with every function between `.fn NAME` and `.endfn NAME`.
- `build/ghidra_c/XXXXXXXX.c`: Ghidra's decompilation of every function, grouped by 0x4000-byte chunk of address. For example, `fn_800068A0` is in `build/ghidra_c/80004000.c`. Use it as a starting point. It's often wrong about types and signedness.
- `tools/check_func.py`: compiles one C file with the game's compiler and compares every function in it against the original, by name. Run it with `python3 -I tools/check_func.py src/game/.../file.c -v`. `-v` shows the differing words. It also checks that every call and data reference points at the same address as the original. It prints `MATCH` and exits 0 only when every function matches.

## Compiler

CodeWarrior `GC/3.0a5.2` (4.1 build 60831) with the default flags in `tools/check_func.py`. This was confirmed on `fn_800068A0`, `fn_800068EC` and `fn_80006938`. The Wii compilers insert loop-alignment nops that the game doesn't have, so don't use them.

## Naming

- Functions must keep their `symbols.txt` names (`fn_8000XXXX`) so the checker can find the original. If you're sure what a function does, add a comment with a proposed real name. Don't rename yet.
- Refer to globals by their `symbols.txt` name (`lbl_803BFBE0`) and declare them `extern`. Declare called functions with the right prototype under their `fn_` names.
- Anything not in `symbols.txt` (such as string literals) can't be reference-checked, and the checker prints a note.

## Code style that matches this compiler

- Operand order matters. `a + b` and `b + a` can produce different register orders. Try both.
- Pointer fields that get relocated are usually real pointers in the original source. Cast with `(void*)((u32)base + (u32)field)` rather than doing `u32` arithmetic on a `u32` field. That was the fix for `fn_80006938`.
- `clrlwi rX, rY, 16` around a loop counter means a `u16` counter. `extsh` means `s16`, `extsb` means `s8`, `clrlwi ..., 24` means `u8`.
- A `cmplwi` or `cmplw` compare means unsigned and `cmpwi` means signed, which affects your type choices.
- Repeated reloads of `h->field` in the asm mean the source re-read through the pointer each time. Don't cache it in a local.
- Struct field offsets must match exactly. Define structs with explicit padding arrays (`u8 pad[N]`) when you don't know the fields yet.
- Functions using paired-single instructions (`psq_l`, `ps_*`) are usually hand-written asm or need intrinsics. Skip them for now.
- Inlined small functions show up as duplicated code. If two functions share a body, one may be inlined into the other.

## File layout

Put matched code in `src/game/<region>/fn_<first address>.c`, with one file per run of neighbouring functions and functions in address order. That keeps later splitting into real translation units easy. Shared typedefs go in `src/game/<region>/types.h`. Only commit functions that print `OK`. Put attempts that don't match in `src/game/<region>/wip/` with a comment saying how close they got.

## Lessons from region D (131 functions matched)

- **The game is C++.** Constructors and destructors on stack objects (`fn_80111B34`, `fn_80111C24(this, -1)`) match when written as explicit calls.
- **`#pragma use_lmw_stmw on`** is needed in most files. Without it, functions that save 5 or more registers call `_savegpr_NN` instead of using inline `stmw`/`lmw`. A few functions do call `_savegpr`, which probably means a different source file.
- **The first-declared local gets r31.** Reorder declarations to fix register allocation.
- **`a() + b()` calls `b()` first.** The `add` operand order follows the source text.
- **Different spellings compile differently.** `!(x & 8)` gives `cntlzw`/`srwi`, while `(x & 8) == 0` gives `rlwinm`/`xori`. Early-return `if (p == NULL) return 0;` and positive `if (p != NULL) ...` lay out branches differently.
- **Switch case bodies come out in source order.**
- **Small sdata externs need a size** (`extern char lbl_804CA0C0[8];`) to get `@sda21` addressing instead of `lis`/`addi`.
- **Callee return width matters.** A `clrlwi` or `extsb` after a call means the callee returns a wider type. Two `u8` functions in a row become a tail call.
- **Strings in a pooled data blob** can be referenced as `lbl_XXXXXXXX + offset`.
- **The unit table:** 0x3F0-byte units in the array at `lbl_804CB810`, looked up with a 1-based `u8` id through a `static inline` helper that takes an `int`.

## Lessons from region F (124 functions matched)

- **Use `.cpp` files with `extern "C" { ... }`** so names stay `fn_...`. The checker accepts both `.c` and `.cpp`.
- **Copying a float struct:** copy-construction (`Vec t = a;`) copies it as words with `lwz`/`stw`. Assignment, or passing it as `const Vec&`, copies it as floats with `lfs`/`stfs`.
- **Static data order differs.** C++ lays out file statics in declaration order, while C uses first-use order.
- **Virtual calls only match with a real `class` that has virtual methods.** Vtable slots start at +8.
- **`#pragma auto_inline off`** stops later functions from inlining earlier ones. Explicit `static inline` helpers still inline. Many register misses go away when a loop is written as a small inline helper.
- **Hand-written asm functions** (r11/r12 use, no frame) can be reproduced as CW `asm` functions with `nofralloc`.
- **Checker false positives:** compiler-named `@N` / `@stringBase0` symbols can collide with names in symbols.txt from other files. Use the `lbl_` extern instead.
- **Large .data globals need a full-size declaration** to get `lis`/`lwz` addressing instead of `@sda21`.
- **Process system API (guessed):** `fn_80083B84` finds an instance by class, `fn_80081050`/`fn_80081194` create one, `fn_80083B78`/`fn_80081A90` delete one, and `fn_800C3C3C` registers a script command.

## Lessons from regions A, C and E

- **`stmw` versus `_savegpr` is decided per function.** Wrap only the functions that use `stmw` in `#pragma use_lmw_stmw on` / `off`.
- **Self-recursion is inlined to a fixed depth.** Use `#pragma push` / `#pragma inline_depth(N)` / `#pragma pop`.
- **Use `static inline` for helpers that get inlined.** Plain `static` helpers also get emitted on their own. `-inline auto` inlines any function defined earlier in the same file, so a caller that should tail-call it belongs in a separate file.
- **Several branches converging on a final `mr r3, rX`** mean an inlined function with multiple returns.
- **Locals of an inlined function sit below the caller's on the stack.** Rotated stack offsets mean a missing inline.
- **Use float literals (`0.0f`) rather than `lbl_` externs for constants.** The checker now verifies constant values, strings and jump tables against the original.
- **`A || B`** keeps the original "t=1; test; test; t=0" layout only when both sides are small inline helpers.
- **Bitfields are declared MSB first.** `extrwi.` bit tests come from bitfields.
- **sdata2 constant groups** (repeated 0x43300000 doubles, 0.0f, 1.0f) mark translation-unit boundaries.
- **`tools/perm/perm.py file.c fn_X`** tries every order of the lines between `/*PERM*/` and `/*ENDPERM*/`. It's good for declaration-order register misses.
- **Event flag lookup inlines:** `flagFind`, `flagGet` and `flagExists` in `src/game/rC_8004BE18/decls.h`.

## Lessons from round 2

- **Unrolled loops:** `li r0,0; cmpwi r0,1` plus dead branches means a small constant-count `for` loop was unrolled over an inlined `switch (i)`. Keep the loop in the source. Writing the iterations out by hand folds the switch.
- **Local statics** can match as hand-written `if (!guard) { ctor(obj); __register_global_object(obj, dtor, &chain); guard = 1; }` using `lbl_` externs.
- **Double stores:** `free(p); p = 0; p = 0;` with the global reloaded each time points to a `#define` macro, not a `void*&` inline.
- **`extsh.` on a parameter stored to a field:** the parameter is `int` and the test reads the field back (`m->at = t; if (m->at == 0)`).
- **Local pointer tables:** `const char* tbl[] = {"..."}` reproduces the `lwzu` template copy. A struct copy from the `lbl_` template schedules differently.
- **`lbz r0; extsb r3,r0`** rather than a direct load into r3 means a `u8` field with an `(s8)` cast.
- **`bl g; bl f` with no argument setup** can mean `f(g())`.
- **`#pragma pool_strings on`** with string literals reproduces `lis/addi base; addi off`, but only if the file's whole string pool is present in order.
- **`#pragma auto_inline off` applies at the callee's definition,** not the caller. Wrap the callee in `#pragma push` / `pop` to keep a real call.
- **`psq_st` in a prologue** only saves an FP register, so those functions are ordinary C. Don't skip them as paired-single.
- **Returned Vec:** `Vec v; v = fn(); out->x = v.x;` copies as floats, while `Vec v = fn();` or `*out = v;` copies words.
- **FP load order:** loading into locals in reverse (`f32 my = m->y; f32 mx = m->x;`) fixes `lfs` order before a call.
- **Side-by-side diffs:** `build/tools/dtk elf disasm` on the compiled object, diffed against the region asm.
- **Lazy statics from an inlined derived constructor:** a guard byte followed by `lis r3, vt; li r4, obj; stw r3, 4(r4)` needs two stores, the dead base vtable and then the real one. The base can be a dummy extern. This unlocked about 30 functions in region B.
- **Keeping virtual calls reference-checked:** store the `lbl_` vtable by hand in a plain struct and call `((Functor*)&f)->visit(...)`. A real object emits `__vt__` symbols the checker can't verify.
- **Two field loads in reverse order** before a call usually mean an inline taking those fields as arguments.
- **`s8 x = p->s8field`** stays a bare `lbz` with `extsb` at each use. A `u8` field extends at the assignment.
- **`perm.py` can't permute lines inside a `#define`.** Expand the macro first.
- **Hidden arguments:** a register that looks like allocator noise at a call is often an extra argument. Add the parameter.
- **Range checks:** write `||` range checks directly in the `if`, using a macro. An inline returning BOOL materializes a value and adds 0x10 bytes.
- **Registrars:** long `fn_800C3C3C` runs match from a generated call list. `src/game/rD_8008E3B4/commands.txt` lists all 469 script commands with their real names, which should help the port.
- **Halving:** `x / 2.0f` compiles to a multiply by 0.5 with `x` first, while `x * 0.5f` puts the constant first.
- **`const` parameters** let loads move above stack stores. Dropping `const` keeps source order. Copying a `const` struct also gets hoisted out of loops.
- **Mid-block declarations** only work in C++ and keep separate stack slots (`Vec eye = {...}; c->pos = eye;`).
- **Range switches:** `cmpwi hi; bge; cmpwi lo; bge` is a `switch` with case labels, not an `if` range test.
- **Statement order** changes volatile register numbering even when the scheduler hides the order.
- **Call result as the first `add` operand:** CW emits `call() + var` as `add rD, rVar, rCall` either way you write it. An int temporary (`int ox = o->v60(); ox + x`) keeps the call first.
- **`x == N` as u8:** `cntlzw` followed by `extrwi r3,r0,8,19` is `u8 f() { return x == N; }`.
- **Locals of inlines:** declaration order inside a `static inline` drives register choice too, so permute it there as well.

## Lessons from round 3

- **`base + const + i * step`,** with the constant before the multiply, fixes register colouring that `base + i * step + const` doesn't.
- **Empty functors:** an uninitialised byte copied to a stack slot means an empty functor passed by value (`struct E { E() {} char c; }; f(x, E());`).
- **`p->t++` as its own statement,** read afterwards, forwards the value and keeps the parameter register live. `++p->t` as an argument doesn't.
- **A loop in a `static inline`** lets the parameter keep r31 instead of the loop variable.
- **`(u16)(x & 0x10) != 0`** keeps `rlwinm; neg; or; srwi`, where the plain form collapses to `extrwi`.
- **Address-taken local ints:** the first declared gets the highest stack offset.
- **Input-blocked test:** `lwz r0; lwz r4; rlwinm. 27,27; beq; rlwinm. 26,26` appears 103 times in region I. It matches through `inputBlocked()` in `src/game/rI_801DD7D4/types.h`.
- **`s16` locals:** `s16 x = p->x; x -= w / 2;` keeps one register where `int` splits the value, and can fix other locals' registers when permuting has no effect.
- **Dead `b; bl free` blocks** come from an inlined destructor on a stack guard whose pointer was just set to null.
- **Varargs:** `__builtin_va_info` with a local `va_list` struct matches printf-style functions, including the `bne cr1` FP save block.
- **Declare, then assign:** `u8 a, b, c; c = p[2]; b = p[1]; a = p[0];` sets registers by declaration order and loads by statement order.
- **Single-case switch:** `beq A; b B; A:` comes from `switch (x) { case 0: ...; default: ...; }`.
- **`neg/or/srwi` for `(x & 2) != 0`** needs an inline returning `u16`. Written directly it gives `extrwi`.
- **Epilogue `psq_l`:** a `psq_l` that only restores f31 doesn't make a function paired-single. Check before skipping it.
- **Family fix for `8003A3BC`:** the limit parameter of the inline is `int`, with a separate `s8` local declared first.
- **`|=` with a big constant:** `u32` gives `oris`/`ori`, while `ULL` gives `or` with a hoisted `lis`/`addi` register.
- **Hoisted base registers:** `((T*)&global)->f` and `global.member` allocate them differently.
- **The first function in a file can compile differently** from the same code later in the file.
- **Hill-climbing declarations** (random reorders in parallel, keep the best) scales where `perm.py` doesn't, especially once locals are split per loop. Orders found this way say nothing about the original source.
- **`if (!(x & m)) return 0;`** moves the return block out of line. `if ((x & m) == 0) return 0;` keeps `bne; li r3,0; b end`.
- **`a + b + c + d`** is rebalanced to `(c + a) + (d + b)`. Trying all operand orders by script is faster than reasoning about it.
- **`v *= 1.5f`** gives `fmuls f0,f1,f0`, while `v = v * 1.5f` and `v = 1.5f * v` both give the operands the other way round.
- **u64 flags field:** `li -1; and` on the high word for `&= ~x`, and `rlwinm; subic; subfe` for `(flags & m) != 0`.
- **Big range switches** match directly if you list every case label with bodies in order of first appearance.
- **`#pragma inline_max_size(N)`** controls inlining. With a large N, inlines nested inside big inlines expand fully. N also sets self-recursion depth, but only one value applies per file.
- **`if (a || b || c) return;`** gives `beq L; b end; L:` at the last test. Separate `if`s give `bne end`.
- **A variable in r3 at `blr`** means the function returns it, even if callers ignore it.
- **Stack order:** the last-declared local gets the lowest offset. Reverse declarations if arrays are rotated.
- **Dead-zone idiom:** `v <= 15 ? 0 : v - 15` gives `xoris/subfic/addc/subfe/andc`.
- **Correction to the process API above:** `fn_80083B78` is Proc_Break (clears `loop`), `fn_80083DC4` is Proc_Goto and `fn_80081A90` is Proc_End. It's the GBA Fire Emblem "6C proc" system in C++. See `src/game/rJ_800799AC/NOTES.md`.

## Lessons from round 4

- **Index inlines:** a small inline such as `m = MeshAt(mm, i)` fixes colouring where direct indexing doesn't. It matched five functions in region L.
- **Loop counters:** one block-scoped counter per loop, instead of a shared function-level `i`, can solve big functions.
- **Global access:** `lbl.field` versus `T* t = &lbl` can flip a whole-function register swap.
- **Small structs by value:** a `lwz`/`stw` word copy between stack slots followed by `lbz`/`stb` is a 4-byte struct passed by value to an inline.
- **Float returns:** a float register used after a call means the callee returns float, even if Ghidra shows a pointer.
- **Checker output:** `DIFF: 0 of N words differ` means only a constant or reference is wrong. "User break, cancelled" with `COMPILE FAILED` is an ordinary compile error cut short by `-maxerrors 1`.
- **`const T&` inline parameter** forces the argument into a register before the inline body. A by-value `base + k` gets re-derived after the call.
- **Widget constructors:** the base constructor matches as a plain inline (`wfInit` in region I), with the derived vtable store and a direct virtual call through `lbl_8038CB1C`. About 114 uses of this vtable make it the best byte-count lead.
- **Unrolled loops:** write `for (j = 0; j < 10; j++, s++)` for the 5x unrolled slot loops, because `s++` in the body swaps the `addi`s.
- **`bool` fields:** `x == 0` stored to a `bool` field gives `srwi 5`, while a `u8` field gives `extrwi`.
- **Stack slots:** block locals sit above inline locals, so moving a local into an inline fixes the offsets.
- **`bne A; b B` branch shape:** write `if (!c) goto B; goto A;`. Writing `if (c) goto A; goto B;` compiles to `beq B; b A`.
- **Doubled `beq` on the same compare** is `if (p) delete p;` through a virtual destructor.
- **Vptr after data:** a vtable pointer at +0x28 with `this` unchanged means a class deriving from a plain data base.
- **Language-table lookups:** `slwi r3,2; slwi r0,lang,3; add` comes from `tbl[lang][f()]` on a `[][2]` array.
- **Dump `.sdata2` values before writing `lfs` float literals.** Guessing costs several rounds.
- **`Prim2D` draw functions** using the `fn_8007E154` family match almost straight from Ghidra, so they're the cheapest bytes left.
- **`hill.py`** writes `.best` without the `/*P*/` markers, so add them back before a second run.
- **Aggregate init:** `Color c = {255, 255, 255, a};` makes an sdata2 template with 0 in the non-constant slot and copies it byte by byte, so write the literal rather than externing the `lbl_`.
- **User-defined `operator=`** copies member by member and reloads fields, which unlocked the `fn_80152C20` family.
- **`u->array` versus `(u8*)u + N`:** the member array recomputes `addi` at each use, while the cast expression gets CSE'd into a saved register.
- **`__abs(x)`** emits `srawi; xor; subf` and evaluates left to right, unlike calls.
- **`for (;;) { if (x) break; ... }`** keeps the loop test at the top, where `while (!x)` moves it to the bottom.
- **Avoiding `add` rebalancing:** `a = x + y; a += z; a += w;` keeps a linear chain.
- **`li r3,0; bnelr; ...; li r3,1`** comes from `r = 0; if (a && b) r = 1; return r;`, not early returns.
- **Accessor inlines:** a trivial one (`Trap* t = At(l, i)`) fixed a register swap in list loops that no declaration order could fix.
- **Reading `*s` twice:** `while (*s) { h = *s + h*37; s++; }` gives `lbz r5; extsb. r0,r5; extsb r5,r5`. The `(c = *s) != 0` form gives `lbz r0; extsb. r5,r0`.
- **Constant-count byte compares** written as a `for` loop unroll to a chain of `li r0,0; b` exits. Written out by hand, the last test folds to `cntlzw`.
- **Calls inside arguments:** a field read next to a call (`w->s3A + f()/2`) goes into a saved register, while a local copy is forwarded past later calls.
- **Dead values:** a struct member keeps an otherwise dead value computed, while a plain local is removed.
- **Colours pass by value.** `lbz`/`stb` runs into a stack slot followed by `addi rN,r1,slot` at a call mean a 4-byte `GXColor`-style struct passed by value, for parameters too.
- **Static const colours:** passing one by value gives direct loads then stores. Assigning it to a local gets a base register instead.
- **Masks and inserts:** `x & 0xFE` gives `rlwinm 24,30`, while `x & ~1` gives `clrrwi`. `(v & 0xF) | (fl & 0xFFF0)` gives `rlwinm` then `rlwimi`, while a bitfield store drops the `rlwinm`.

## Fixing m2c drafts (near-miss list)

- **Constants one register too low:** the draft dropped pass-through arguments. Add leading parameters and pass them on.
- **Chained calls:** when r3 is untouched between two calls, write `f(g(), x)`.
- **Pointer scaling:** m2c's `ptr + 4` on an `s32*` is 16 bytes. Use `+1` or index a typed array.
- **`lwzx` expected:** declare the extern as `s32 lbl[N]` and index it.
- **`clrlwi.` expected but `cmpwi` emitted:** make the parameter `s32` and compare `(u8)x`.
- **Virtual calls:** drafts never match. Use a `.cpp` with a real class (slot n is at 8+4n; a `struct B { int x; }` base puts the vptr at +4).
- **`*(lbl + idx)` on a u8 extern** emits `lbzx`. Use `*(u32*)(...)` or a typed extern.
- **Constant hoisted into a saved register** after `M2C_FIELD(call(...), s32*, off) = const`: assign the call result to a local pointer first.
- **`extern s32 lbl;` with lis+lwz in the asm:** declare `u8 lbl[N]`, and don't take `&lbl`.

## Lessons from round 5

- **`lwz r4` instead of `r3` as the base before `ori`/`oris`** on a field means a `u64 |=` with a ULL constant.
- **`addc`/`adde` with a hoisted zero register** instead of `addze` means a signed `s64` total.
- **A saved register reused for a result right after being an argument** means the parameter was reassigned (`a = f(c, g(), a);`).
- **`cmpwi 3; beq A; bge B; b B`** comes from `case 3` plus `case 0: case 1: case 2: default:` on one body.
- **Call inside the expression:** `a * b * (f32)fn() + d` puts operands in the original `fmadds` order. Assigning the call to a float local first swaps them.
- **Devirtualization:** a virtual call on a declared global object compiles to a direct call, so go through a cast from a `u8[]` extern.
- **Always-false compare:** `lbz; cmpwi r0,-1` with no `extsb` is a literal `u8 == -1`, so keep it.
- **`int` inline parameter** can fix a whole-function register rotation that a `u16` parameter causes.
- **Manhattan distance is a macro:** `#define ABS(a) ((a) < 0 ? -(a) : (a))` with `r >= ABS(x - xx) + ABS(y - yy)`. Inside a loop, the invariant term keeps its branch form and the varying term becomes `srawi; xor; subf`. This fixed a whole family of map loops.
- **Map grids are 1-D:** `slwi 6` before `slwi 7` in a loop preheader comes from `a[x + y * 0x40]` on the u16 and u8 grids.
- **Unrolled search:** a chain of `addi r3,r3,0x28; li rN,k; cmplw; beq` is an unrolled `for (i = 0; i < 7; i++, q++) if (best == q) break;`.
- **`clrlwi. r4,r3,24` followed by a call with no `li r4`** means `(k = g()) == 0 || f(u, k)`.
- **Jump table order is source order:** sort a dense table's targets by address and write the cases in that order.
- **Assign to the parameter:** when the new value lands in the parameter's register, write `x += 0x69;` instead of a new local. This can fix a whole-function rotation.
- **Pointer plus int:** the pointer always comes first in the `add`. To get `add rD, rK, rPc`, cast the pointer to int.
- **`*vm->sp++ = v`** matches VM stack pushes. An inline doing `*sp = v; sp++` reloads the pointer.
- **`strcpy`:** declare it with its real `char*` return type, or it gets inlined.
- **`addi rN, rBase, 0x0` means pooled file statics.** Plain `static` objects share a base register. A struct member at offset 0 won't reproduce it because it folds. File-static references show as `...bss.0`, so the checker compares offsets but not the base address: confirm the base by reading the asm.
- **Static alignment moves offsets:** `u32` arrays push later statics out of place, and `u8` padding arrays keep them right.
- **Explicit pointer locals** instead of `tbl[i]` let declaration order control the induction register.
- **`scoped { guard } return x`** puts the `extsb` after the unlock.
- **`const` on a struct pointer parameter** changes the scheduling of `*c = *p` word copies.
- **Inline conversions** such as `out->m[i] = fx2f(in->m[i])` through struct pointers stop the scheduler reordering across statements.
- **`li rN, lbl@sda21` before byte stores** comes from field-by-field assignment to an sdata struct. A whole-struct copy gives `lbl+1@sda21`.
- **Paired-single routines with no compiler frame** transcribe mechanically to `asm` with `nofralloc`. Spell `qrN` as a plain number and GQRn as SPR 0x390+n.
- **Hand-written C from the asm** often matches where m2c drafts don't, so don't insist on starting from a draft.

## Lessons from round 6

- **`li r4,0` followed by `subfc; subfe; subfe; neg.`** is a `switch` on a u64 (`u64 f = (u64)x & 0xC0000000ULL`).
- **A `(char*)` cast on a call result** gives `add rD, rCall, rVar` when the sum goes straight into a truncated argument.
- **Unrolled loop counts:** a loop's counter step is the number of unrolled copies minus one, so 6 copies with `addi 5` and `ctr = 3` is 18 iterations, not 15.
- **Inlined self-recursion that ignores the child's result** probably returns its own parameter.
- **Running tools/perm from a scratch copy:** `lib.py` works out `ROOT` from its own path, so a copy needs `ROOT` hard-coded.
- **List insert:** use a guard with members `{list, node}`, pass the sentinel as `LNode* const& e`, and write the value through `&g.node->val`. Solved the `fn_801E5448` family.
- **Pointer-to-member helpers:** `bl fn_8028C178; nop` and `bl fn_8028C148` come from a real pointer-to-member call and test.
- **`cntlzw; li r3,N; srwi.; beq`:** write `BOOL b = f() == 0; int r = N; if (b) r = 0; return r;`.
- **`l->x + f()->x`** keeps the call first. To load the field first, assign the result to a named pointer.
- **Compile error:** `0x4e-0x40` fails because `e-` reads as an exponent, so put spaces around the minus.
- **Clustering:** comparing normalised asm across open functions finds exact or offset-only copies, so one solution can give several matches.
- **Quick triage:** running the draft tool and checker over a whole range takes about 30 seconds and shows which functions are close.
- **`cmpwi cr1` release idiom:** `if (p) { if (--p->rc == 0 && p) p->destroy(1); o->f = 0; }`.
- **Member destructors with `stw r4,off(r3)`** need a real member array, because a cast offset folds.
- **`cmpw r0,rN` right after `li r0,0`** is a store-forwarded field compare.
- **Subsystems:** 0x802356BC..0x802383F4 is the THP movie player, in the shape of the DolphinSDK THPPlayer sample. 0x802383F4..0x8023FBF4 is an archive and file entry manager.
- **By-value `Vec`:** declaring a `Vec` parameter by value in an extern prototype gives `lfs f1; lfs f2; lfs f0; stfs...`.
- **Store then read back:** `a->h = z; a->z = a->h;` emits `stfs; frsp; stfs`, with no double in the source.
- **Inline depth limit:** at the limit, small helpers become real calls too, so the helper needs its `fn_` name.
- **Guard inside an inline:** `if (!(x)) { switch... return 1; } return 0;` reproduces a shared `li rN,0` tail. A ternary at the call site doesn't.
- **Open puzzle:** `fn_800F201C` returns a u32 split into a stack `GXColor`, reloading r and g but forwarding b and a. About 10 functions depend on it; see `src/game/rE_800E5DE4/NOTES.md`.
- **Neighbourhood search beats `hill.py`:** trying every single move and swap of declaration lines, keeping the best and repeating solved several functions where `hill.py` stalled. See `tools/perm/sw.py`. `hill.py` shuffles every `/*P*/` block in a file but scores only one function, so it can break other matches.
- **Auto-inlining inflates sizes:** an earlier function in the file inlines into later ones (`fn_80272FAC` appears five times in `fn_802732FC`). Look for repeated blocks before treating a large function as hard.
- **`lbl + 0x16` directly,** with no string base variable, gets the `lis r3; addi r30,r3` form.
- **`subf r0,r0,r0`** comes from `(data + size) - data`, because `size -= size` folds to 0.
- **`rlwinm` followed by `rlwimi.`** is a non-contiguous mask like `x & 0x100001`.
- **Recursive inlining:** callers only inline a recursive function one level, whatever `inline_depth` or `inline_max_size` say. Writing the levels by hand as inlines reproduces the shape; this unlocked the `fn_800B5784` family.
- **Register order with reference parameters:** with counters, pointers and results as caller locals passed by reference, listing them by descending target register reproduces the allocation.
- **Induction variables:** a compiler-made one can't be ranked by declaration order, but an explicit stepped pointer can (`q = (T*)((u8*)q + 4)`).
- **`li r4,-1; b; bl; mr r4,r3`** needs `else { int t = f(); k = t; }`. Without `t`, the value ends up in r3.
- **Pointer compares** keep `cmplw table, value`, while `u32` operands flip to `cmplw r3,r0`.
- **A ternary in the call's argument list** keeps the earlier argument loads before the test.

## Lessons from round 7

- **Colour and copy slots:** two helpers at the same inline depth (`pA` declares `GXC t; GXC c;`, `pB` declares `GXC c; GXC t;`) reproduced the stack and fixed nearly all float register misses.
- **Static const colours:** direct `lbz lbl+N@sda21` loads need a file-level `static const` passed by value to an inline. An extern gets a `li` base register.
- **`x ? 1 : 0`** computes before the next call, while `x != 0` gets moved past it.
- **`s8` local:** a block-scoped `s8 lang = ...` can fix a register that declaration order can't.
- **Search speed:** compiles run at about 50 per second, so permutation searches over several blocks are cheap.
- **Warning:** very large functions can eat a whole session. `fn_80275FD4` and `fn_80277E10` reached registers-only near misses, but cost an entire round with almost no matches. Time-box them.
- **Inline and ternary results** are coloured ahead of declared locals, so declaration order can't move them. Assign through `if`/`else`, or write the expression without the inline.
- **Implicit CSE:** `mulli r0; slwi r3` then two `add`s comes from repeating `(u8*)o + i * 12 + N` and letting the compiler keep the common part. Named pointers swap the temporaries.
- **u32 split into a point:** `Pt mk(u32 r)` with `Pt q = mk(call())` reproduces `srwi; sth; sth; lwz; stw; lha; lha`. This may solve the `fn_800F201C` puzzle.
- **Scale chains:** r3, r4, r5, r3 needs four nested inlines, one per level.
- **`s16` parameters** on the callee prototype with a float passed directly give an in-place `lwz r4; extsh r4,r4`, which a call-site cast doesn't.
- **Search scoring:** `lib.score` compares by position, so one extra instruction hides all later improvements. A `difflib` score works much better for large functions (it took `fn_801ED290` from 85 to 21 words).
- **7-byte struct return:** a plain 7-byte struct returns in r3/r4 and unpacks with shifts. Adding a copy constructor makes it a hidden pointer, and `t = f();` then gives `lwz; lhz; lbz`.
- **Mask across a u64:** `lis; and; rlwimi.` on a mask spanning both words means one u64 field.
- **`f(list, Slot(a, b, c))`** keeps its stack slot and reloads, while a named local is scalar-replaced.
- **Inline boundary:** moving a whole block and its locals into an inline can fix register swaps no declaration order can. Try this before permuting.
- **Open puzzle:** `fn_8012A0F4`, `fn_8012A440`, `fn_8011E864` and `fn_80116680` want the parameter in a lower register than the locals.
- **Stack layout:** declare named locals from the highest offset down. Slots then follow declaration order.
- **Dead zero stores** survive when written through `*(u32*)&v.x`, but a plain array or union member is removed.
- **`const char* const&` inline parameter** computes the string address before the null test.
- **`double a = __fabs(x); (f32)a`** gives `fabs f3; frsp f1,f3`.
- **Unrolled loops:** `for (...; i++, e++)` on a sized struct gives the 8x unrolled loop with range checks. A stepped `(u8*)` pointer doesn't.
- **Dead ends for recursive inlining and the mirrored stack:** `inline_depth`, `inline_bottom_up`, `defer_codegen`, `inline_max_size`, about 30 `opt_*` pragmas, `-inline` levels, and other GC compilers. Don't retry them.
- **Give each `new` its own inline** (`newT()`). That fixed long constructor functions where declaration order did nothing.
- **A register taking the lowest free number** means the variable was live earlier: `int p = h; ...; p = alloc();`.
- **`extern const T tbl[N]` with a size** lets loads move above stores, giving interleaved `lbz`/`stb` pairs. An unsized `[]` doesn't.
- **A dead `cmpwi` with no branch** comes from `if (!p) p = same_value;`.
- **Stack slots follow inline depth, then source order.** Inside an inline, later declarations get higher slots and registers, the reverse of a plain function.
- **When `bl wfInit__...` appears,** inlining has stopped, so add `#pragma inline_max_size`.
- **String pools are real literals (the main unlock of round 7).** A `lis/addi` base that reloads per group, or `addi rS, rB, off` kept in a saved register across a call for a single use, means string literals under `#pragma pool_strings on`. `lbl + off` can't reproduce this. Put a dummy function first that assigns every pool string in order, so offsets are exact (delete it once the file holds its real strings). In a pooled file, wrap short local string tables in `#pragma pool_strings off`/`on`.
- **Stack slots follow inline nesting depth, breadth first.** A per-call-site search over nesting forms fixes stack order in seconds.
- **Auto-inlining stays within the file:** some helpers inline only inside their own file, and other files call them as real functions.
- **Inline parameter order** sets register order for arguments evaluated at entry.
- **`clrlwi` on a u8 argument** means the value came from a multi-return inline. A plain variable gives `mr`.
- **`li; xoris; stw; lfd; fsubs`** means a constant held in an int or s16 local.

## Lessons from round 8

- **Mask tests:** `lwz r0; rlwinm rN,r0; rlwimi. rN,r0` comes from testing through an int-returning inline such as `flg(e, m)`.
- **Identical branches:** `if (c) { X; return; } X;` keeps both copies, where a plain if/else folds them.
- **`rc` decrement:** `u16 n = e->rc - 1; e->rc = n; if (n == 0)` gives `subi r0; clrlwi. r3,r0,16; sth r0`.
- **Colour copies:** a `const C4*` passed as `*col` to a by-value parameter hoists the `lbz` loads above the argument setup.
- **Moving a switch into an inline** can change colouring where declaration order does nothing.
- **Ghidra can drop things:** it lost FIFO writes in `fn_80235FF4` and hid a store in `fn_8023DE84`. Check it against the asm.
- **Hidden `this`:** `fn_80105158` takes the convoy pointer as a hidden argument; `*m - fn_80105158(m)` fixed a register miss declaration order couldn't. If one short value after `bl X; mr rN,r3; bl Y` has the wrong register, try passing it to Y.
- **Ranking registers:** to rank a temporary from an inline, declare it in the caller and pass it as `T*&`.
- **Loop branch:** `while (1) { ...; if (++i == N) break; }` gives `cmpwi; bne` on a loop with calls. `for` gave `blt` even written with `!=`.
- **Dead vtable store:** `gInit((G40*)o, ...)` keeps it, while `gInit(&o->g, ...)` removes it.
- **Inline arguments load right to left,** so parameter order sets load order.
- **Hand-writing beats permuting.** Natural C++ from the asm, with real nested inlines, won by a wide margin in region G: 26 of 30 matches, some on the first or second compile.
- **Fresh variables change registers.** A block-scoped new variable instead of reassigning, or a declaration moved into the `if` that uses it, changes the register.
- **Template copies:** `lis; lwzu; lwz 4; lwz 8` is an aggregate initialiser, not a copy from the `lbl_` extern.
- **Dead `b` in a switch** comes from `return` inside a switch in an inline. `goto` gets threaded away.
- **Elided lowest case:** `cmpwi 1; beq; bge X; b end; X: cmpwi 3; ...` needs a `case 0:` that only breaks.
- **`mr r3,r31; mr r4,r3; mr r5,r3`** is a `u8` local passed to `u8` parameters.
- **Struct returned by value (solved the `fn_800F201C` puzzle):** a `GXColor` return arrives in r3 and is unpacked by the compiler, so `srwi/extrwi` bytes after a call mean a struct return, not a u32. In a C++ file, just declare `fn_800F201C`, `fn_80175E7C` and `fn_801125B4` that way.
- **Vec temp order:** `Pop(const Vec& v) { Vec w = v; f(w); }` puts the return temp above the copy. `Pop(Vec v) { f(v); }` puts it below.
- **Inline results vs `switch`:** when a variable fed by a multi-return inline won't take the right register, write the `switch` in place.
- **Scoring trap:** with literal strings, the compiled symbol is `@stringBase0` where the original has `lbl_`, which inflates text diffs. Trust the checker's word count.
- **`const u8* s` on a copy loop** lets the 8x unrolled loads move above the stores.
- **Inline with a local table:** a 12-word `lwzu`/`stw` copy before each `fn_800D0864` is `const char* t[] = {...}; return fn_800D0864(t[i]);` in a small inline with a constant index, under `pool_strings off`.
- **Function-level variables shared across switch cases** fixed r27/r28 swaps at single sites that per-item locals could not.
- **Split counters:** give each loop its own counter, then rerun `sw.py`.
- **Conversion temps alternate:** the two hoisted `0x43300000` doubles are handed out in turn, even for conversions later removed as dead. If all later temps are inverted, an earlier statement is missing.
- **Late struct copy:** a by-value struct argument is copied before float arguments that are expressions. If the copy comes last in the asm, pass the floats through an inline's parameters first.
- **`#pragma inline_max_total_size(N)`:** a late `bl` to a static inline in a huge function means the total budget ran out.
- **Split locals, then search:** give each loop its own function-level counter and walker, then run `sw.py`, `rr.py` (random multi-move) or `bf.py` (brute force) in tools/perm. This solved five functions in region L. These scripts expect a `lib.py` beside them with ROOT set correctly.
- **Scorer labels:** `lib.parse` doesn't mask `lbl_804CE*`, `jumptable_*` or `...bss.0`, which inflates scores with false differences.
- **Pooled `.rodata` statics:** `lwz r0, 0x30(r6)` with `addi r4, r6, 0x30` and a base hoisted at entry means several file `static const Vec`s, with earlier data setting the offset.
- **A load into r3 followed by `cmpwi; beq; bl f`** means the value is `f`'s argument (`if (v) d = f(v);`).
- **`fmuls f4, f4, f5`,** where the result reuses the constant's register, comes from `f32 s = m->scale; a *= s;` with a named `s`.
- **`Vec t; f(&t, m); *(W3*)&a = *(W3*)&t; Vec c = a;`** reproduces the stack order and the dead copy of a returned `Vec`.

## Lessons from round 9

- **A register that looks live with no visible use is often an unwritten argument,** including a constant kept in r5 for the next call.
- **`dist(T* const& a, T* const& b) { return b - a; }`** keeps `add; subf; srawi; addze`. Value parameters fold away.
- **A static `u8` array whose size is divisible by 8 gets 8-byte alignment,** which shifts every static after it.
- **Stack slots ascending across switch cases:** put all the cases' guards directly in one inline, not nested inlines.
- **Pass a tag as a temporary:** `f(s, p, n, Empty())` gives the mirrored slot order that a named `Empty e` doesn't.
- **Named float temporaries change colouring:** a block-scoped `f32 d = st * (...)` in each branch before a call can move a variable from f31 to f30.
- **Defining a flag early can move it first in colouring:** `ok = 0; w.own = ok;` took `fn_80248154` from 37 differing words to 2.
- **Prototype parameter order can mix ints and floats:** if float argument code comes before a test for a later int argument, the float parameters may come first in the source.
- **`beq L; blr; L: b fn; blr`** comes from `switch (x) { case 0: fn(); break; default: break; }`.
- **Real guard class:** an inline constructor and destructor on a small struct keep the two vtable stores and the stack slots, where a plain struct is scalar-replaced.
- **Function-level variables don't pin registers:** one variable used in separate cases can land in different registers, as if each def-use web is coloured separately.
- **Huge functions:** a hand-written first draft of `fn_8019AEA8` was within 2 words of the right size, but saved-register colouring is the real cost. Time-box it.
- **`AiCfg* cfg = &lbl_804183F0;` declared first** takes r31 and pushes the parameter to r30. A block-local `AiAct* act = &lbl; Unit* u = act->unit;` gives `lis; lwz lbl@l; addi` at entry.
- **Set `use_lmw_stmw` per function before reading a diff.** Without it, drafts look far worse than they are.
- **`extern u8` byte symbols** (`lbl_804CA7A0`, `lbl_804CA7A1`, ...) give direct `lbz` loads with the reference still checked.
- **`lis rN,1; subi r0,rN,1; clrlwi r4,r0,16`** at each call comes from `int k = 0x10000; f(u, k - 1);`.
- **`srawi; subfc; adde` before the first call,** tested later, is `BOOL ka = sa >= sd + 4;`.
- **Two-branch frames:** declare all locals of both branches at function level, from the highest offset down.
- **Faster search:** minifying the file to one function body makes `sw.py` and `rr.py` much faster.
- **Nested struct:** a nested `struct W2 { u32 a, b; }` as a member stops scalar replacement, giving dead stack stores and `lwz; lwz; stw; stw` pairs.
- **`std::swap` through references** reloads across a branchy comparator, where a hand-written swap forwards the value.
- **`x |= a, x |= b`** gives one load and store with `ori` before `oris`.
- **`d = (q = v) - w;`** schedules the `extsb` late.
- **`/ 1024.0f` vs `* 0.0009765625f`:** same constant, different operand order.
- **Two separate `static const` objects passed by value** load right to left.
- **Registrars:** file statics for the table let the string base take r31 first. This solved `fn_801C7898`, `fn_801C864C`, `fn_801C9E98`, but the real class tables still need supplying.
- **Named products:** `int m = a * b; x = m + y;` gives `add rD,rMul,rY` and fixes the temporaries around it. `pos % cols` with `pos / cols` shares one `divw`.
- **`const` and CSE:** const and non-const reads aren't CSE'd. A reload right after a test comes from a different qualification.
- **Unroll guard:** `for (int i = a; i < (u32)n; i++, q++)` gives the single-guard 8x unroll. A u32 counter adds range checks.
- **Web splitting:** the compiler splits one local into separate webs, so reassigning a local doesn't keep its register. Declare one local per use, then run `sw.py`.
- **`rlwinm r0,r0,0,25,23` on a byte** is a one-bit bitfield set to 0.
- **`if (++x == y) ++x;`** reproduces `clrlwi; addi` on the second increment.
- **Trust the checker over custom scorers:** a `difflib` scorer that masks floats can read 0 on a real MISMATCH.
- **Inline results ignore declaration order.** A variable assigned from an inline's return can't be moved by `sw.py`. Expanding the inline in place as a macro makes declaration order work.
- **Real SDK return types matter:** `u8`/`u16` getters nested inside the `GXInitTexObj` arguments put the registers right and the `clrlwi`s late.
- **By-value colour stack slots:** temp and argument-copy slots pair up only inside small inlines, one per call.
- **`OSInitFastCast`** works as an inline with an `asm {}` block inside ordinary C.
- **Vertex FIFO:** `pos3`, `col4` and `tex2f` inlines called with expressions as arguments reproduce the hoisted conversions.
- **`Vec t = {...}`** copies from a rodata template every time, while a `static const Vec` gets hoisted out of the loop.
- **`extsh` in animation keys:** use `s16` locals read from a `u16*` key array.

## Lessons from round 10

- **Where the bytes are:** functions that reload a global or `this` field in every statement (input handlers, draw functions) match on the first compile or two. Register-only near misses cost far more per byte, so write these fresh first.
- **Partial unrolling:** a 4-iteration loop can unroll 2x. `ctr = 2` with `addi 4` twice and a seemingly dead `addi r8,r8,1` is `for (i = 0; i < 4; i++)` over a flat index.
- **`std::advance`:** `if (n >= 0) { for (int k = n; k > 0; k--) ... } else { for (int k = n; k < 0; k++) ... }` reproduces the long signed range checks.
- **Finding a blocked register:** temporarily add a real use of a variable after a join. If a whole branch then matches, that variable was live across the branch in the original.
- **`s8 v = f(); if (v == x)`** keeps `cmpw r0,rX`. A direct compare flips the operands.
- **Triple `beq` on one value:** three nested `if (l)` reproduce an inlined list destructor.
- **`lhz; extsh` puzzle solved:** a `u16` point field read through `(s16)` after a struct copy. This opened the tween family in region I (15 functions).
- **An int local stops an int-to-float conversion being reused:** `int b0 = p->x + 1; f32 b = b0;`.
- **`bne L; b M; L:` before a range erase** comes from an inline returning a value the caller uses (`it = erase(l, it, j);`).
- **Placement `new` and `p->~T()`** add their own null tests, so drop any hand-written check around them.
- **Inline arguments set pool string order:** `mk("A", "B")` through an inline pools `B` first, and a direct call pools `A` first.
- **Colouring order (working model):** compiler-made CSE temporaries are coloured before declared locals, and locals top-down. Making the "wrong" value a real local deep in an inline fixed `fn_80259718`.
- **Bit sets:** `li rN, lbl@sda21` before a single word read, with `clrlwi` or `extrwi`, can be a bit-array inline with a constant index whose search loop folded away. The unrolled form needs a local copy of the index: `u32 q = n; while (q >= 32) { q -= 32; p++; }`.
- **`lwz r30,0x3C(r1); lwz r31,0x38(r1)`** after the register parameters is a single u64 stack parameter.
- **Base and derived updates:** inlining a base body into a derived function flips float colouring against the macro-expanded form.
- **Unsolved:** `li` constants held across calls, such as `stb r31` reusing a 0 from far earlier.
- **Strength-reduced offsets:** if an offset register steps inside a loop but an expression using it isn't hoisted, write it as `i * step`. Writing `xx += step` by hand lets the compiler hoist it.
- **Keeping `stwx`:** `((u8**)row)[n * 2]` keeps `stwx` with a stepped offset. `row[n].field` turns into a stepped pointer.
- **Dead counters:** `for (i = 0; s[i]; i++)` keeps a counter register that `while (*s) { s++; i++; }` removes.
- **Per-call locals for draws:** when a value across several inlined draws ranks too high, declare each draw's `tex`, `w`, `h` as separate caller locals passed by reference, then search.
- **Non-const static colours** can't have their loads moved above earlier stores. Const static loads do get moved up.
- **`f = r->t; q = k; t = f + q;`** fixes `fadds` operand and load order where `r->t + k` doesn't.
- **Cheapest targets:** low branch density and few hoisted floats often match within a few compiles.
- **Base plus index:** `T* o = &out[n++]; o->a = ...;` or `seen[n++] = v` keeps base+index with a stride register (`sthx`). `out[n].a` becomes a walking pointer.
- **Ranking induction variables:** an explicit stepped offset (`ofs += 2`) lets declaration order rank a compiler induction variable.
- **Hidden returns:** a function that looks void but ends in `mr r3,rX` returns that value.
- **Unrolled guards:** the 8x unroll with its long range checks comes from a plain `for (i = n; i < 4; i++) out[i].id = 0xFFFF`.
- **`Vec b = i == 0 ? p[1] : p[-1];`** puts the temporary above the conversion doubles and copies it as words.
- **`lhz; cmplwi; beq; lhz` of the same field** comes from reading once through a `const` cast and once without.
- **Small locals in memory:** a 4-byte struct or `u8[4]` local is scalar-replaced even with its address taken in an inline; a member of a larger struct stays in memory.
- **Recheck paired-single skip lists:** region H's list of 10 had no `ps_` instructions and were ordinary C; five matched. Grep for ` ps_` before skipping.
- **Parameter below the locals:** write the inline's body in place with its locals at function level (solved `fn_8012A0F4`, `fn_8012A440`), or move the whole body into an inline behind a one-line wrapper.
- **Real string literals under `pool_strings`** fixed walker registers and solved `fn_801246A4`, `fn_8012486C`.
- **Float literals share loads,** where `lbl_` externs reload each time.
- **`u16 v = *p; v |= f; *p = v;`** for read-modify-write. **`(u32)x == 1`** keeps `cmplwi`.
- **Never overwrite:** file names can be taken by a file that no longer holds that function. Scripts must refuse to overwrite.

## Lessons from round 11

- **Global base colouring:** one direct `lbl.f` anywhere in a function changes how the `lis` of that global is coloured for the whole function, compared with `((T*)&lbl)->f`. Check both forms.
- **`lhz -0x2e72(rX)` after `addis rN,base,1`** comes from `lbl.member[i]`. The cast form gives `addis; subi; lhzx`.
- **Mirrored aggregate locals:** declare both inside an inline, where later declarations get higher slots.
- **`(int)((char*)call() + x)`** gets `add rD, rCall, rX` even inside a larger sum, if the callee returns `int`.
- **u64 flags:** `lis; addi r0,rN,-0x8000; and.` comes from `*(u64*)p & 0x8000ULL`. `ori r5,r4,0x800` picking r5 comes from `FLAGS |= 0x80000000000ULL`.
- **`subf; subf; or; srwi.`** comes from `int c = a != b; if (c)`.
- **Non-const `extern` colours keep their `lbz` load order,** and const ones get reordered. The non-const extern also keeps the reference checked.
- **Regions untouched for a while pay better:** region B gave 24 KB this round, against the 15 KB goal.
- **Hoisting of `lis 0x4330` at entry depends on the conversion count, dead ones included.** One dead conversion fixed the whole frame of `fn_8006F1B4`. If later slots use the same temp twice in a row, a dead conversion sits between them.
- **Discarded by-value results still need returning:** if the inline doesn't return the value, every later stack slot shifts.
- **Repeated sums versus walkers:** writing `Spr3(x + mw + 8, ...)` out each time lets CSE keep it late, while a named local computes it early. A walking register needs `ix += 0x10; f(ix); ix += mw;`.
- **`Trap* const& t` on an inline parameter** swapped pointer and counter registers.
- **`f(..., z = 0)`** puts `li` in the final argument block while `z` stays a real variable.
- **Draw routines are cheap in bulk:** region O matched 19 at once with one shared sprite inline.
- **Float copies on the stack:** `struct V : Vec { V(const Vec& o) { x = o.x; ... } };` passed as `f(s, V(pos), k)` puts the float-copied temporary in the stack order of the other temps. This unlocked five functions in region E.
- **Word-pair copies:** `lwz r7; lwz r0; stw; stw; lwz r0; stw` comes from a nested struct, `W3 { W2 ab; u32 c; }`.
- **`int f2 = fl | 1;`** can fix a whole-function register rotation that `fl |= 1` causes.
- **Large local colour tables:** `GXColor t[14] = {...}` compiles to the whole spill pattern with no extra work. Don't skip these for looking huge.
- **Join stores:** a `stfs` after a branch join means an inline returning the float.
- **Recipe for fresh functions:** write them whole from the asm with a `/*P*/` block of function-level locals, then run `sw.py` once.
- **Paired flag lookups:** the first keeps string above index in register order, and the second reverses it. Put the second behind a one-line by-value wrapper, with the inner inline taking `const char* const&`.
- **`unitAt(u8 id)`** with a u8 parameter drops the unit to the lowest saved register, where an int-indexed helper doesn't.
- **Mixed byte reads:** `lbz r4; extsb r4,r4` next to `lbz r0; extsb r5,r0` means one s8 read and one u8 read with a cast. Mix them with `*(s8*)&field`.
- **`beq next; b found` in a search loop** comes from `switch (flag) { case 0: break; default: goto found; }`.
- **Two aggregate descriptors inside one inline** give first-declared the lower slot, which a sibling block in the caller doesn't.
- **Dead end:** the `fn_8005B508` family (15 copies), the `lbl_8038C1C0` constructor and `fn_801EBF00`: -1 and 0x190 registers stay wrong after about 50 spellings across rounds. Skip unless you have a truly new idea.
- **Local types move register rank:** `s16` on six locals took `fn_800C18A4` from 63 lines to 0, and `bool` instead of `BOOL` finished `fn_800AD068`. A greedy type search is worth trying before permuting.
- **Keeping an `extsh`:** the compiler drops `(s16)v` when every definition of `v` is known to fit. Reading through an inline that returns `int` keeps it.
- **`li r0,0; ori r0,r0,K` on a field** is `f = 0; f |= K;`.
- **`lwz @sda21` on a label** means the extern is a word, not an array. An array hoists `lis` pairs.
- **`__alloca(n)`** reproduces a dynamic frame.
- **Avoiding `lwzu`:** `Res* u = R; u->p` gives `lwz` plus `addi`, while `R->p` gives `lwzu`.
- **Copy timing changes colouring:** passing `T(t, x, z)` as a by-value argument, so each `Vec` copy comes right after the value is built, fixed a zero register.
- **`lis` constants held in a saved register** appear when the value comes through a stored field: `l->g = n; sz = l->g * sizeof(T)`.
- **Hoist order follows the expression form:** `TF* f = ...; f->ctr = f->ctr + 1` hoists `li rN, lbl@sda21` last. A direct cast or `f->ctr++` hoists it first.
- **Pass `&lbl` into an inline** around the whole body, with the global's address as a parameter, to fix nearly all saved registers.
- **`list[n++] = m`** gives `addi rN, r6, 1` alongside `stwx`. Two statements lose the extra instruction.
- **Masked diff:** masking registers and symbols in a diff shows when only ranks remain, so it's time to stop or search.

## Lessons from round 12

- **`const char* const&` on a flag name** fixes the whole family of flag lookups. It also gives `lis; lbzu` for `name[0]` on a global.
- **A huge "new" function can be an earlier one inlined many times:** `fn_8009CF6C` (2.5 KB) is `fn_80092E38` eight times. Copy the helper in as a `static inline`.
- **Sequential clears:** `f &= ~1; f &= ~4;` folds to one `and`. To get `clrrwi; rlwinm`, write the second clear as a one-bit bitfield store.
- **`lbz r0; extsb rS,r0` into a saved register:** use a block-scoped `s8 v = p[k];`. A cast inside the argument list doesn't work.
- **Hoisted constant after `call()[k] = 0x7b`:** move the store into a one-line inline.
- **Search scripts:** `sw.py` and `rr.py` miss definitions with `{` on its own line, and `sw.py` rewrites the `/*P*/` order, so insert new locals right after `/*P*/`.
- **Wrapper pass:** a one-line wrapper around an inline copy of the body (`T f(a) { return f_i(a); }`) fixes parameter ranks. It took `fn_801DAEF4` from 61 words to 0. It needs `#pragma inline_max_size(4000)`, and stack order flips, so reverse the declarations. It can be tried by script across every near miss.
- **Inline vs plain declarations:** `ModelDef* def; ModelData* d; d = p->d; def = d->def;` sets registers one way in a plain function. Inside an inline the order must be reversed.
- **`fcmpu f31,f0` against 0.0f** needs the constant as an extern. The literal always comes first in the compare.
- **Whole-struct assignment:** `p->d->scale = v` in an inline taking `Vec v` gives the no-reload float copy.
- **Branch past a reload:** `d = p->d; if (d->f & k) { ...; d = p->d; } if (d->cb) ...`.
- **Scorer trap:** `lib.score` masks labels, so a wrong branch target scores the same. Only the checker catches it.
- **`C4 c = *(C4*)src;`** on a plain 4-byte struct, then reading fields, gives `lbz` loads plus dead `stb`s.
- **Inline result in an expression:** `RectH(s) + (y + s.y0)` with the inline in place stops rebalancing.
- **`int d = aw * -2; nw = d + w;`** gives `slwi; neg; add rD,rNeg,rW`.
- **Jump to scripted spellings:** a script that compiles a list of replacement spellings for one snippet in parallel found about 8 fixes in one round (`tools/perm/var.py`).
- **Check whether a near miss is known SDK code:** writing the PADClamp shape fixed the scheduling, and reversing the inline's declarations took `fn_8007C4B8` from 61 words to 0.
- **Enum ternaries:** `t ? ENUM_A : ENUM_B` with enum operands keeps `li r3,0` before the branch and avoids the neg/or/srawi mask.
- **`cmpwi 0xFE; beq end` plus a range test on 0xFD** means 0xFD has no label and 0xFE has its own empty case.
- **Binary search:** lower_bound-style loops matched only after expanding into macros with function-level locals, then `sw.py` and `rr.py`.
- **Reassigning a parameter:** `p = ((Block*)p - 1)->heap` fixes `subi r31,r30; lwz r30,-0xC(r30)`.
- **Test spellings before reasoning:** a one-function file compiles at about 40 per second, so a grid of 500 spellings takes 15 seconds.
- **Family drafts:** one solved copy of a family often solves the rest with only the changed lines. Spill-heavy functions with 18+ live registers come out right if the logic is written plainly with a `/*P*/` block ordered by target register.
- **Spilled map pointer:** a second `lis r0; mr r3,r0; stw; addi; stw` before the loop comes from a direct `((Map*)&lbl_803EC898)->` in the loop. `m->` and the cast form give separate hoisted rows.
- **Selective CSE:** to keep `x*2` in a saved register while `x*2+K` is recomputed, read through the cast form at the first site and `m->` at later sites.
- **Inline locals are coloured above compiler CSE temps,** while caller locals usually land below them.
- **Keeping a late `extsh`:** a multi-return `s16` inline for the first def, `int` locals, and `(s16)` at the compares.
- **`bf.py` beyond about 6 lines is too slow.** Permute just the top 5 or 6 lines, then split one more counter.
- **Optimiser pragmas reveal the blocker:** `opt_common_subs off` moves hoisted constants below locals, and `ppc_unroll_factor_limit 1` stops unrolling. Scan them for the cause, even if the pragma isn't the real fix.
- **A dead `addi` counter next to a walker in a `bdnz` loop** comes from an `s16` or `s8` counter. An `int` counter gets removed.
- **Mutual recursion:** `if (f) { if (f) return x; return next(s); } { temp }` reproduces the repeated `beq` with temp blocks out of line.
- **Colours in a table:** `(&lbl)[i]` hoists a base register, const statics move their loads up, and non-const statics keep order and direct `@sda21`.
- **Open:** hoisted constants rank above locals in some functions and below in others; there's no single rule.

## Lessons from round 13

- **Nested calls:** `f(buf, fmt, g1(), s("A"), g2(), s("B"))` makes the results compiler temporaries, so the string base ranks above them. Named locals put the base at the bottom.
- **Four stack words with `addi rN,r1,slot`** are a call with four by-value structs.
- **Anchored sprite:** `x1 = ax * (0.5f * w) + x; x2 = w * sx + x1`, with the constants as inline parameters so they aren't folded.
- **One-pointer struct local:** `lwz r30,8(r1)` before a loop and `stw r30,8(r1)` after it is a one-pointer struct in memory. A nested struct or union member stops scalar replacement.
- **`find_if` loop:** `while (first != last && !P(first->val, v)) first = first->next;`, with `P` returning an int flag, gives `b test` and the materialised flag.
- **`Fx* f = &p->fx[i]`** gives an induction variable at base + offset, while `p->fx[i].on` puts the offset in the load.
- **Functions saving 10 or more registers** tend to stall at register-only misses. Write the global-reloading kind first.
- **Ascending stack slots:** siblings at one inline depth descend, so nest the first draw deepest, one wrapper per draw, under `inline_depth(30)`.
- **Colour locals:** an 8-byte aggregate with its address taken goes to the top of the frame. Two 4-byte `GXColor` locals sit next to the argument copy.
- **Int constants across calls:** `s16 w = 0x13a` in an inline gives saved `li` plus conversion. An inline `int` parameter folds to `lfs`.
- **`col4(r, g, b, C8(a))`,** where `C8` is an inline returning `u8`, hoists `clrlwi` and adds the loop guard.
- **`struct { u8 tex[0x20]; s16 w, h; }`** keeps `sth; lhz` for the size fields.
- **Register recipe for loops:** split function-level counters plus a named zero, then `sw.py`.
- **Held constants can come from a one-iteration loop:** `li` values or `lfs` loaded before a `new` and held in saved registers come from `for (i = 0; i < 1; i++, id++) {...}`.
- **A trivial accessor raises a local's rank:** with `s16 gx(o) { return o->tx; }` and `x = gx(o)`, `fn_8021ED04` went from 15 words to 0.
- **Greedy type search:** try `int`, `s16`, `u16`, `u32` on each `/*P*/` line, alternating with `sw.py` (`tools/perm/tys.py`). If a `u16` gets the registers right but emits `lhz` or `clrlwi`, the variable probably needs an accessor.
- **`lwz r4; clrlwi r4,r4,24`** means a `u8` parameter with the float passed directly.
- **Colour by reference:** a colour shared by several calls with no copy between them is a `const C4&` parameter.
- **Permuting stores as a probe:** moving a store shows what colouring order the original needs.
- **Global address in a local vs direct use:** a named local holding a global's address ranks differently from using the global directly, which makes a compiler temp. Replacing `u8* w = lbl_803C8E80` with direct uses fixed the whole `fn_80155D2C` family.
- **Pre-schedule order:** register allocation appears to see the order before scheduling. Computing a value earlier than it is scheduled changes registers without changing final instruction order.
- **Rank rule for big map loops:** caller locals passed by reference into an inline rank below that inline's compiler temps, and the inline's own locals rank above them. Hand-listing locals by target register often hits 0 at once.
- **Inventory walkers:** a block-scoped `Inv* p = &u->inv[k]` becomes a high-ranked compiler induction variable.
- **Spelling grids:** try `m->x`, `lbl.x` and the cast form per access (`tools/perm/grid.py`, `co.py`).
- **Operand order on a hoisted constant:** `f32 t = call(); r = t * externConst;` gives `fmuls fD,f0,fK`. A literal always comes first.
- **Pushing the parameter down:** one real local that isn't forwarded does it. `s8 vv = b.v[i];` moved `this` from r31 to r22.
- **Raising the parameter:** assign the first local from an inline (`a = fetchA(o)`).
- **Types rank registers:** `int` locals rank high and `s16` low. A greedy type toggle took `fn_801EB490` from 50 words to 2.
- **A small struct local stops constant folding:** keeps `li 0x80; stw; lfd` for a u8-to-float conversion.
- **Hidden float argument:** `lfs f1,K; fcmpu f1,f28` before a call often means `if (k != K) f(.., K)`.
- **`f32 x = q.x; f32 y = q.y;` before the call** fixes the `0x4330` and string `lis` register swap.
- **Forward substitution:** `y -= 2` is substituted into later uses. `int y = y0 - 2;` in an inline keeps it.
- **Flatten nested inlines into function-level locals before searching:** this took `fn_802016AC` from 72 words to 0.
- **Open puzzle:** the `mr rZ,rI` zero idiom before list-sort loops blocks `fn_802038BC`, `fn_801F3D28`, `fn_801F6C54`, `fn_801FA9BC`, `fn_801F43E0`.
- **Wrappers aren't a general fix:** one solved `fn_8026697C` but made `fn_80275FD4` and `fn_80277E10` clearly worse.
- **Out-parameter `BOOL& r` through an inline** ranks a result where an inline return cannot. `f(call1, call2)` gives a saved value the rank of a compiler temporary.
- **Colour loads:** `stw r12,8(r1)` followed by byte stores is a hand zero word. An sdata2 byte load mixed with stores is `C4 c = {r, g, b, 0xFF};` with non-constant RGB.
- **Stopping folds:** `u32 m44` stops `a*k + k` folding, and `int k = 3 - x; (k+1)` stops `3-x+1`.
- **`x / 32.0f` and `0.03125f * x`** give different `fmadds` operand order. `r *= -1.0f` gives `fmuls f31,f31,f0`.
- **`s16 x = float_expr` with no int cast** keeps `lwz`, with `extsh` only at wide uses.

## Lessons from round 14

- **Hoisted constants** out of a loop can take saved registers in order of first use inside the loop. Moving the first use may swap them.
- **`bool off = x == 0;`** instead of `BOOL` can swap two saved registers.
- **List constructors:** `LN* l = &o->l70; l->next = l; l->prev = l; o->v2C();` forces the `lwz r12,0(r3)` vtable reload after the derived vtable store. `lnInit(&o->l70)` forwards the vtable and loses both.
- **`push_back` family:** construct the buffer first (`SplitBuffer buf(0, &v->cap); n = ...`) and declare `t2` before `t1`.
- **Float register search:** when `sw.py` stalls on large float functions, hand-order locals by target FPR, then brute-force 6 middle lines with `grid.py`.
- **Long `sw.py` runs** with 20 or more `/*P*/` lines can pass the 120 s tool limit, so run them in the background.
- **`return a || b;`** gives the flag a register that `t = 0; if (a || b) t = 1; return t;` can't.
- **Real guard class:** `li rG,0; ...; cmplw rG,rNew` that doesn't fold, with a matching call at function exit, is a class with a constructor, `reset` and destructor. Declare it mid-block after the first call.
- **`c->cur = c->tgt = v;`** reproduces the `stfs; frsp; stfs` store pattern for a whole `Vec`.
- **Argument copy slots:** by-value struct arguments put the last argument highest. If the first is higher, the callee takes pointers to two named locals.
- **Split one flag in two:** two function-level locals for one reused flag, then `sw.py`.
- **Mask all registers as `R` in a diff** to see structural differences in very large functions.
- **Shell notes:** macOS has no `timeout`, BSD `sed` has no `\b`, and zsh doesn't word-split `$var`. `0 of N words differ` with MISMATCH usually means a float constant is one bit off.
- **Pooled statics:** `lwz r6,0x18(r29); lwz r5,4(r30)` with `addi r30,r29,0x18` is a word copy from a real file `static const Vec`. An extern array folds the `addi`. A const static copy is hoisted whole out of a loop, a non-const one stays inside.
- **Float declaration search:** write `f32 a, b, c;` with assignments separate, then permute the name list.
- **Hoist order follows body order:** moving `k *= 1.5f` to the end of the loop fixed all of `fn_80144938`'s float registers.
- **Stack depth arithmetic:** for slots low to high A, B, C, D, give each temporary one more inline wrapper than the next.
- **`n = n + sizeof(T)` vs `n += 12`:** the first stops induction elimination and keeps `stfsux` with a stride register.
- **Run multiprocessing searches from a script file,** never from stdin.
- **Open puzzle:** the parameter stays in r31 in `fn_80136E74` and `fn_8013EED0`, whatever wrappers, copies or qualifiers were tried.
- **Per-block locals for lookups:** give every inlined lookup its own locals, listed by descending target register across all blocks, then run `sw.py`. `fn_800B79AC` stalled at 76 lines with shared locals and went to 0 this way. This unlocked most of the `fn_800B5784` family.
- **Named locals for the frame:** one local per stack slot, highest offset first, instead of a frame struct or union, fixed frames and even scheduling.
- **Conversion rank:** `f32 v = (u32)x; v = v / k;` moves the conversion's hoisted double from the top float rank to the bottom.
- **Literal zero:** `0.0f` stores colour the constant first, while `f32 z = 0.0f` colours it last.
- **Shared address temp:** direct `STR(n)` in both arms of an `if` shares one address register, while a named `base` in each arm splits it.
- **Two-line moves:** `sw.py` can't swap two lines that must cross at once. A search over all positions of two lines took `fn_800B29D0` from 40 to 6.
- **`if (f(x))` on a float return** gives `fcmpu f1,f0`, while `!= 0.0f` puts the literal first.
- **Don't name a scratch script `grp.py`:** it shadows a standard module and breaks `subprocess`.
- **By-reference locals are the strongest fix of round 14:** declare an inline's locals in the caller, pass them by reference, then search declaration order. This took the SetAnim and `800314CC` families straight to 0.
- **`li r3,N; bl fn_8028DB44` border loops solve by stack depth:** named locals inside inlines run in ascending slots and sibling inlines at one depth descend. To reverse whole groups, give earlier groups deeper wrapper chains.
- **`subfic r3,r3,0`** comes from a constant passed as an inline parameter. `0 - t` written directly folds to `neg`.
- **`w2 + (x + w1)`** with the sub-sum in parentheses reproduces three-term load orders.
- **The scratch folder is wiped during usage-limit pauses.** Save near misses in `wip/` as soon as they are close. `sw.py` only saves when it finishes.
- **psq with GQRs is ordinary C:** OSFastCast-style inlines with `register f32 r; asm { psq_l r, 0(p), 1, 5 }` get allocated and scheduled normally, and the compiler folds `p + k` into the displacement. Recheck "real paired-single" skip lists.
- **Fixed-address FIFO:** `volatile U WGPIPE : 0xCC008000;` ranks its `lis` at the top of the saved registers, while the `*(volatile f32*)0xCC008000` macro ranks it low. It took `800167B0` from 119 words to 39. Try this on draw routines stuck on register rotations.
- **Pinning store order:** volatile casts force one store ahead of another when the scheduler has no dependency.
- **Parameter copies in the `/*P*/` block** let declarations rank parameters. **`lim = 300000.0f;` as a local** ranks a hoisted constant.
- **`a *= b`** keeps the target register where `a = a * b` can split the web.
- **Jump tables:** identical words can still fail on table order, so read the table from the DOL and order the case labels to match.

## Lessons from round 15

Checks now run with `tools/check_func.py --strict-references` (plus `--symbol-map X.symbols.json` for pooled file statics). See `docs/ROUND15_HANDOFF.md` for the Codex interlude and its dead ends.

- **Function-local `static` instead of an extern global** is treated as non-aliasing and changes scheduling. It fixed a prologue order at once (`fn_801C5874`). Map it to the original label with a `.symbols.json`.
- **File statics with `addi rN,rBase,0`:** separate statics padded with `u8` arrays give a shared pool base. Add a symbol map for the strict check.
- **Retry pooled literals:** old `lbl + off` near misses can fall on the first compile once the string pool is dumped from the DOL into a `StringPool` dummy (`fn_801AEB78`).
- **Alloc/free on every exit with an oddly low handle rank** is a guard object with constructor and destructor (`fn_80165240`, 23 lines to 0).
- **Member pointer vs struct pointer:** `FMCursor* hc = &g->cur; hc->x` ranks a reloaded global differently from `g->cur.x`. It fixed a whole-function r6/r7 swap.
- **Sign-extended values:** `v = (s8)*(u8*)&c->f` into an `s8` local gives it a declared local's rank. Plain `int v = c->f` drops it to the lowest saved register.
- **`a*b + c*d`:** CW computes the right product first (fmuls), then fmadds the left one.
- **Literal 1.0f as an extern** fixed f0/f1 swaps no literal spelling did. Dump `.sdata2` before writing float literals; two "0 words differ" misses were wrong constants.
- **Several induction pointers:** step them explicitly in the `for` header; their order there sets their rank. Grid all permutations.
- **Named fabs temporaries** in the `/*P*/` block fixed FPR choice where inline forms didn't.
- **Late `extsh` after `ox = (s16)-ox`:** read the first definition through an int-returning inline. With `adv(LN*, s16 n)`, pass `(int)field` to keep the `extsh` before the unrolled count.
- **Missing `mr` copy:** read the same field once through a cached pointer and once through the macro.
- **Loop-condition assignments:** `while ((o = g)->f && ...)` shares one global load between test and body; `while ((s = g->sel) ...)` keeps the value live past the loop.
- **Recursion depth:** `#pragma inline_depth(3)` reproduces three inlined self-levels. Callers never inline the recursive function itself.
- **Dead store on one path only:** an inline setter that re-reads the field it just stored.
- **`x = NULL;` early plus `else x = NULL;`** reproduces a saved `li r31,0` shared with an unrelated byte store.
- **Repeat the address expression as the call argument** instead of a named local to fix argument scheduling (`fn_8017B638`).
- **Stack slots:** 8-byte aggregate locals go above 4-byte ones regardless of order; wrap the 4-byte one in an 8-byte struct. Later declarations in an inline get higher slots.
- **Local aggregate templates** are pooled under one `.rodata` base. When the original uses separate `.data` labels, read them through externs.
- **`x ? x : y`** on a pointer gives `beq; b`, while `if (!x) x = y;` gives `bne`.
- **Volatile registers** respond to caller-level locals: expand the inline into a macro and run `sw.py` on the enclosing inline. Statement order in a loop setup can decide them where declaration order does nothing.
- **Big menu handlers** written straight from Ghidra with case bodies in asm order converge in about 15 compiles, even at 7 KB.
- **Tool traps:** `grid.py ... save` saves even when every candidate failed (score 9999). Copied `sw.py`/`rr.py` must run by absolute path or every compile fails silently. `lib.parse` doesn't mask `lbl_804CF*` sdata2 floats. `grep -h | grep -v wip` can't filter wip files.

## Lessons from round 16

Yield fell to about 40 KB with six agents: what's left is mostly register-rank near misses. Run at most three agents at a time (usage limits).

- **Accessor inlines raise a value's rank.** `s8 gx(BU*)`, `orig(&b->b)` or `curPid()` fixed three single misranked saved registers. Grid an accessor form for each misranked value before sw.py.
- **Inlined member functions rank differently** from static inlines taking the same pointer. Making walkers members of a derived struct (`struct ProcM : Proc { void free2(); }`, `((It*)&n)->incr()`) fixed whole-function rotations (fn_8008A868: 197 to 19 lines). Generate recursive walker chains per level (member, static, macro) by script instead of hand-permuting.
- **A call result passed straight into an inline parameter ranks lowest**; a named local gets r31 (fn_80059B18).
- **`(s8)x == s->x` in an inlined loop** makes a loop-invariant temp ranked below a hoisted `lis`; a named local ranks above it.
- **Exhaustive grids beat sw.py** for small inlines: every declaration order × local type (a few hundred compiles) found `u16 n` in fn_800F002C.
- **Per-site by-reference locals scale:** one local set per inlined allocation site, declared in the caller's `/*P*/` block (fn_8023AC14: 97 to 8 words with one sw.py run).
- **Explicit byte offsets for big table loops,** one per loop, then sw.py; the step order in the `for` header (`o += K, i++`) sets the `addi` order. A plain `for (...; i++, it++)` over 7 slots gives the peeled first iteration with `lwzu`.
- **Your own split statics with a `.symbols.json`** give `addi rN,rBase,off` per block. Statics of 8 bytes or less go to .sbss; sizes that are multiples of 8 get 8-aligned; `static + k` shares one base register.
- **Struct copies:** an `int a[4]` member gives paired `lwz;lwz;stw;stw`; implicit assignment copies u8 members bytewise, copy construction copies words.
- **Macro body with `goto end`** instead of an inline with `return` fixed parameter ranks and layout of two template-like wrappers (quicksort pair).
- **`x = y = c; x += k; y += k;`** stops two equal sums being merged.
- **`a = f(x) * f(y) * f(z)` calls `f(z)` first;** write `a = f(x); a *= f(y); a *= f(z);`. `a - b` loads b first; `s = a; s -= b;` loads a first.
- **Float operand order:** `(a + K) / 2.0f`, `x *= K`, `/ 32.0f` give the `f0,f1,f0`/fmadds orders where `* 0.5f` or `x * K` put the constant first.
- **`return y < x;`** reproduces the `xor/srawi/and/subf/srwi` signed-less-than idiom.
- **Volatile in one inline** stops reuse of a field read in a sibling inline, reproducing an in-loop reload.
- **Keep the pooled string extern** when the original holds the base in a register; literal `""` folds the address.
- **`#pragma opt_propagation off`** decides whether a stored constant 1 merges with a later inline's return 1 into a saved register.
- **Placement new into a global is still null-checked by CW**; static-initialiser bodies need explicit inline constructors.
- **Inline call with a branch in its argument is evaluated first;** move it into a wrapper inline taking the other arguments to make it last.
- **NW4R `LinkList::PushBack` with its assert:** compute `endIter()` into a local, then call `nodeOf(p)` on the static directly.
- **Open puzzle:** fn_802384F0/fn_80238FB8 load the size before the data argument at four `DCFlushRange` calls, unique in the DOL; about 30 spellings failed (4.3 KB blocked).
- **Tool traps:** copied grid.py/tys.py compile every candidate as `.cpp` (mangles `.c` names, all 9999); `lib.origfn` only globs `auto_03_*`; `lib.parse`/`lib.score` float masking misses `lbl_804CE*`/`lbl_804CF*`/`lbl_804D*`, use a `(?=@sda21)` pattern; grid.py truncates printed choices.

## Lessons from round 17

Yield about 30 KB from six agents (three at a time). Accessor inlines were the strongest single fix this round.

- **Try an accessor inline on each misranked value before any declaration search.** `curUnit()`, `rb0(r)`/`rb1(r)` (s8), `gx`/`gy`, `skl`, `hpOf` each fixed a function in one compile where sw.py did nothing.
- **A value stuck below a compiler temp** (e.g. a global's address): wrap the body in an inline that takes the value as a parameter from a caller local.
- **Search which value reuses which parameter:** grid every temporary as "reuse parameter X" or "new local" (fn_800DE794 13 to 0).
- **Floats assigned only under a condition inside a loop live from function entry.** Declare them in the exported function and pass them by reference; their order there sets the FPR order (fn_801335C4 family, 3.7 KB).
- **Use a global directly instead of `T* m = &global`** (fn_801CD478 25 to 4 words).
- **Assignment in a loop test** (`if (k >= (st = g)->n) break;`) fixes volatile swaps; a const accessor in a `while` test stops the body reusing the test's load.
- **A `u8` index is zero-extended again at the use;** `int k = f() & 0xFF;` gives `clrlwi` at the definition and plain `slwi` at the index with a low rank.
- **`row * stride * (n + 1)`:** `int rr = row * 0xc; u8* r = base + rr * (n + 1); r += col * 0xc;` gives the original mullw/add order.
- **Byte-equality chains are early returns,** not `&&`: `if (a.r != b.r) return 0; ... return a.a == b.a;`. `&&` materialises a bool with neg/or.
- **Switch pivots:** cases 0..2 pivoting on 2 need an empty `case 3:`.
- **Template struct copies inside loops need non-const externs;** `extern const` hoists the copy and grows the frame.
- **By-value colour parameters:** the first goes to the higher stack slot; split an 8-byte pair into two `C4` parameters to get it below the return temporary.
- **Hidden arguments:** a seemingly free r4 before a call may be a real argument (`fn_8001EF44(int total, int cur, f32, f32)`).
- **Split sdata2 halfwords** come from a local aggregate initialiser with one non-constant member.
- **Dead `b; stb` after constructor stores** comes from `if (p) flag = 1;` right after `p = 0`. An empty destructor keeps a stack object in memory.
- **Epilogue order shows block structure:** `addi r11` before the last `lfd` means an early branch to a separate epilogue block.
- **`s8 cs(f32)` conversion helper** separates the load and fctiwz registers.
- **Element copies:** `struct { u32 w[2]; }` assignment gives load, load, store, store; `u64` members keep 24-byte items out of memory.
- **Store after `if (p) {...}`** instead of inside it fixed branch target and epilogue order; `if (p == 0) return;` last keeps a dead cmpwi.
- **Static `__sinit`** reproduces exactly with real virtual classes, but the checker can't credit it under an `fn_` name (fn_8013157C).
- **Open:** `k = 4` passed as float and int stays in a saved register where the original reloads `li r3,4` (fn_8026E9DC). fn_8001B284 needs file-level rodata padding (blocked by the no-dummy rule). The r13b wip of fn_8022130C has rotted (header changed); rebase before retrying.
- **Tool traps:** copies of tools/perm compute ROOT from their own path; outside `tools/perm` they fail silently. Hardcode ROOT and point mkdtemp at your build/tmp folder.

## Register-only near misses (from 2026-11-11)

The port doesn't need register choice to match, so near misses are now classified with `tools/check_regs.py FILE --extra "-i region -i region/wip"`:

- `exact`: byte for byte with right references. Only this counts as a match.
- `renamed`: same instructions and references, registers differ by one consistent renaming of callee-saved registers. Same program.
- `regs`: same instructions and references, other register differences. Very likely equivalent, not proven.
- `other`: size, order, constants or references differ.

`docs/EQUIVALENT.tsv` lists the best `renamed`/`regs` wip file per unmatched function (name, class, differing words, size, file). At the first scan: 80 functions, 132 KB. 141 of 447 wip files are fragments that don't compile on their own and weren't counted, so this is a lower bound. Save new near misses as self-contained files.

Working rule: write unwritten functions first and stop at `regs` level unless an exact match is close; time-box register searches.

## Lessons from round 18 (exact or register-only)

Yield: 27 exact functions (21 KB) and about 118 KB newly at `renamed`/`regs` level, against 30 KB in round 17. Helpers kept in `tools/equiv/`: `mkself.py` (parent file with exported bodies stripped + fragment = self-contained file, `--inline fn_X` keeps a callee as a static inline), `dd.py` (register-masked diff against the original), `ps.py` (order search scored on masked instructions).

Working at `regs` level:
- **"other, 0 words" says nothing** (check_regs.py stops at the first structural difference). Use `dd.py` and `check_func.py -v`; it is often a wrong constant, a missing statement or a wrong branch target, i.e. a real bug in the draft (fn_800F6AEC passed 0.0f for -1.0f; fn_800105AC had different branch targets).
- **Try the plain original statement and store order first.** Old wips were tuned for register scores and are `other` only for that.
- **Fragments lose the parent's `#pragma use_lmw_stmw` state** and auto-inlined callees. Set the pragma from the original (stmw or not) and keep any callee the original doesn't `bl` as a static inline copy.
- **Score searches on masked instruction order,** not raw words; sw.py can break `regs` level, so re-check after it. One `f32 t = expr;` per line, permuted, finds schedules (fn_80158354).
- **Register pressure changes instruction sequences.** With all of r14..r31 in use, addresses are rematerialised per use and values spill, so `regs` needs nearly the original allocation. Check `stmw r14` plus stack reloads first.
- **Port caveats to undo later** are listed in each region's NOTES Round 18 section: shared globals written as local statics (fn_8019AEA8 `lbl_804CB944`, fn_80177A5C colour table), `_inl`/`_i` inline copies of real functions, volatile casts.

Codegen:
- **Separate `lis` register** (`lis r7,sym@ha` early, `addi r21,r7,sym@l` later): a local `T* m = &lbl` plus `&lbl` passed directly as an inline's pointer argument (fn_8016BE04, fn_801662AC exact).
- **Unparenthesised `a + b + c` blocks hoisting;** `+ (b + c)` hoists the invariant add.
- **`const T*` parameters:** `*out = *a` loads all floats before storing; plain `T*` keeps load/store pairs.
- **A ternary inside the call** puts float argument loads before the conditional.
- **`i++` as an inline argument** gives `mr rK,rI; addi rI,rI,1`. `n = *p++; id = *p++;` keeps one walking pointer.
- **`x ? 0 : 1` as branches** is a `switch` with `default` first; `lbz; cmpwi 1; beq; b` is a one-case switch.
- **Two `rlwinm` in a row on one load:** two 1-bit bitfield assignments. `clrrwi; or` instead of `rlwimi`: pass the flag through an `int` inline parameter.
- **`rlwinm; subic; subfe` on a single-bit test of a call result:** a `u64` flags field.
- **`bne A; b B; A: fneg`:** `c == 0 ? r : -r`. `li -1` with `stb`: an `s8` field. `li rN,sym@sda21` needs the extern declared with its real small size.
- **64-bit big-endian read:** `a = (u64)b0 << 56; a += ...;` gives the `addc` chain.
- **`err(const char* msg) { fprintf(stderr, msg); abort(); }` as an inline** loads the string before `__files`.
- **One load with two sign-extensions around an sda store** means a function-local static.
- **Pre-loop local vs in-loop expression** decides which side of the hoisted values it lands on.
- **Short strings referenced from a data table** are separate `.sdata2` objects: `#pragma pool_strings off` around the table. With a symbol map on `...data.0`, pooled strings need `#pragma readonly_strings on`.
- **Static initialisers can be written by hand** with a `BaseCtor` inline and plain vtable stores (fn_800CCEEC exact).
- **A devirtualised call on a global object** becomes virtual again through an inline returning its address.
- **By-value struct arguments of an inline stay in memory;** the first parameter gets the highest slot. Locals of an inline are laid out last-declared highest.
- **Zero idiom `mr rZ,rI` (11 functions, about 19 KB):** all are one inline, a list sort passing an empty comparator object by value; the `mr` is probably a copy of an undefined value. Still unsolved, and check_regs.py rejects `li` for `mr`.
- **Not yet credited:** many `other` cases have the right instructions with one or two scheduled a slot apart. A class for "same instructions per basic block, order differs" would need a dependency check to be sound.

## The `sched` class (2026-11-11)

`tools/check_regs.py` has a fourth accepted class, `sched`: same size and block structure as the original, and every basic block (cut at branches, calls and branch targets) holds the original's instructions, registers aside, in a different order. Our words are linked against symbols.txt first, so reference targets take part; words that refer to unnamed literals match on everything but the relocated field. It doesn't check dependencies between the moved instructions, so it is weaker evidence than `regs`: look at the moved lines with `tools/equiv/dd.py` before saving a `sched` file in `equiv/`. First scan: 75 functions, 71 KB of earlier `other` drafts.

## Lessons from round 19

Yield: 8 exact functions (5 KB) and about 130 KB newly at `regs`/`sched` level (part of it older drafts the `sched` class now accepts).

Method:
- **Diff originals against each other before writing.** Siblings and mirrors are often instruction-identical or differ in a few constants (fn_801EC414 = fn_801EBF00, fn_801F6C54 = fn_801F3D28, the fn_8005B508 family of 15). Constant-heavy constructors are cheap at `sched` level: one draft, text substitution, one compile each.
- **Check constants before trusting an old draft.** Run `check_func.py -v` and look for "constant … but original has"; no masked diff shows a wrong float. File-static placeholder constants can hide wrong values (fn_802818FC had eight 0xFFFFFFFF colours).
- **"Wrong reference" lines on drafts shifted by one slot are artefacts.** `check_regs.py`'s "N words differ" is not a distance to exact.
- **A size-4 "function" right after a tail call or infinite loop** is that function's dead `blr` (fn_8012E888, fn_80118008 in `rH/fn_empty.cpp` are not real functions).
- **mkself.py traps:** drop structs or inlines the parent already defines from the fragment; add `#pragma use_lmw_stmw on` by hand when the original uses `stmw`. dd.py doesn't mask `lbl+0xN@sda21`.
- **Real bugs found this round in old drafts** are listed in the region notes (wrong scale 0.5f/1.0f in fn_801E9CA8, three shape errors in fn_80117A84, `rH/map.h` declares a `u16` grid where the code reads `s8`, fn_8017F68C takes its mode first).

Codegen:
- **Static initialisers:** plain member stores over externs plus `#pragma use_lmw_stmw on` reproduce a real `__sinit` (fn_801DCE18, 110 rectangles). The port should use the global definitions quoted in the file header.
- **`addi rX,rBase,0` plus unfolded offsets** means one symbol is several pooled statics (lbl_803CA870 = 0x30 + 0x80 + 0x80).
- **`lis rS; addi rS,rS,sym` in one saved register** is an explicit local pointer set before the loop; `lis r3; addi rS,r3,sym` is compiler hoisting.
- **Inline arguments are evaluated last to first;** wrap a call in an inline with reversed parameters to reorder float loads. Prototype parameter order changes argument scheduling.
- **`if (a) if (b)` vs `if (a && b)`** with inlined bool helpers branch to different targets. `bne next; b end` after two `beq end` is `if (!a || !b || !c) return;`.
- **Test-at-top search loops with a `b` back** are `for (;; p--, i--) { if (i < 0) break; if (p->x) break; }`.
- **`e = buf; e++;`** computes the address late as an add; `&buf[1]` computes it early.
- **`v <<= 1; v |= a;` on a `u16`** truncates per step; `v = (v << 1) | a` defers it.
- **`u8 f(u16 v) { return (v & M) ? 0 : 1; }`** gives `rlwinm; cntlzw; extrwi`; `== 0` gives `extrwi; xori`.
- **C vs C++ dead stores:** a local struct filled field by field and then assigned keeps its stack stores in C only.
- **A constant converted at run time** (`li 5; xoris; ... fdivs`) is a local inside the inline, not a parameter.
- **Unrolled constructor calls at r1 offsets** are a plain stack array of a class with an inline constructor.
- **Epilogue `lwz r31; lwz r30; lwz r0`** can mean a global is wrongly declared volatile.
- **Three destructor copies of a loop-local object** mean the body has both `continue` and `break`.
- **MSL shapes:** `__selection_sort` and median-of-three show as a comparator inlined N times followed by three-field swaps; reverse iterator `operator*` is `tmp = base(); --tmp;`.
- **Open:** fn_80112364 gives each of four float-to-int conversions its own stack slot (frame 0x40) where ours reuses one; fn_80236A5C materialises an inlined result every form folds; four zero-idiom functions have no draft (fn_801F8798, fn_801F9030, fn_801FA9BC, fn_801F43E0).

## Lessons from round 20

Tools: `check_regs.py` has a `slots` class (like `regs`, locals in other stack slots by one consistent mapping, same register at each such access) and picks up `<file>.symbols.json`. `tools/equiv/symcheck.py FILE fn REGIONNAME --anon [-v]` executes each basic block of both versions symbolically and compares stores, stack bytes, live-out values, call arguments and branch conditions; `docs/EQUIVALENT.tsv` records its result for every `sched`/`slots` function. Flags can be artefacts (local template names, jump-table blocks, helper aliases), so read `-v` before believing either way.

Method:
- **Check prototypes of shared helpers against matched files before any search.** Two multi-round puzzles were wrong prototypes: fn_8017F68C is `(int mode, f32, f32, f32, f32)` (the `li r3,4` reload in fn_8026E9DC), and fn_80179888/fn_80179A7C return `int`/`u8`.
- **Order open work by calls per instruction, not size.** Call-heavy functions reach a counted level in a handful of compiles (fn_80179A84 exact in five, fn_801420B0 `sched` in six).
- **Split near*.cpp at their section markers and check each section alone** before writing anything.
- **Incomplete sources:** rK fn_800DC824, fn_800DC9D4, fn_800D5DC4 drafts miss blocks; rM fn_80160018 needs re-reading. Don't port from them.

Codegen:
- **Function-local statics are real:** guard `lbz; extsb.; bne`, vtable store, field stores, `stb 1,guard` is `static T obj(args);` with an inline constructor. Map `name$NN` and `@GUARD@name$NN` in the symbols.json (the whole fn_801DFF2C family went exact).
- **`addi rX,rX,off; lhax`** on a struct array is a pointer to data member: `(p->*m)[i]` with `s16 (T::*m)[12]`.
- **`li r0,N; srawi rX,r0,1`:** an inline with a local constant, `int x = N; return x >> 1;`, under `#pragma opt_propagation off`.
- **To stop two equal constants merging,** give one parameter another integer type in the prototype (`u8 mode`).
- **Temporaries of hand-inlined recursion levels:** declare them in the outer function in first-use order and pass by reference (fn_801CD05C to `regs`).
- **Strings of 8 bytes or less go to .sdata unless `#pragma pool_strings on`.**
- **12 bytes copied from .data to the stack before a virtual call** with `addi r4,r1,N` is a by-value struct argument. Unexplained frame space can be an unused struct member.
- **Stack slots follow who creates the object:** deeper inline means lower slot; when a group comes out mirrored, turn the data flow round (function-level locals initialised from inlines returning by value). At function level the first-declared local is highest; inside an inline the last-declared.
- **`beq; b` vs `bne`:** `if (m) return m;` inside an inline, or a one-case `switch`, give `beq; b`. `x >= y ? A : B` gives `li B; blt; li A`.
- **`r.x + (w - K)` vs `r.x + w - K`** decides the operand order of the shared add.
- **Compound literals as call arguments** give one 3-byte `.sdata2` constant per argument, built last first.
- **Pool layout follows first use, not declaration order.**
- **A pointer local declared at the top of a function that fills r14..r31 costs a register throughout;** declare it just before its loop.
- **A named float local used twice can block constant folding** (one extra run-time add).
- **Still open:** zero idiom (`mr z,i` appears after constant propagation; only fn_801F3D28/fn_801F6C54 differ in nothing else), local-vector functions (ours hoists three addresses the original doesn't), redundant `extsb`/`extsh` at a join (fn_801596C0, fn_8015CC24), `stfs` slot per float-to-int conversion (fn_80112364).

## Lessons from round 21 and the equivalence review

State after round 21: exact 2,053 KB (77.7% of game code), equivalent 476 KB (18.0%), rest 113 KB of which 96 KB are complete drafts. `docs/SCHED_REVIEW.md` holds the review of every flagged `sched` and `regs` row.

- **`regs` and `sched` are evidence, not proof.** The review found eight real behavioural bugs in rows the checker accepted, almost all wrong prototypes: a call missing an argument compiles to the same instructions with a stale register (fn_800CD5F4, fn_8027247C, fn_800C9918, fn_8002FFDC, fn_801689C8, fn_800ED4AC, fn_8004564C), or two stores swapped by register only (rectangle corners in fn_80020354). **A register difference in an argument register right before a call is a prototype bug until shown otherwise.**
- **Run `symcheck.py FILE fn REGION --anon --xargs` on every `regs`/`slots`/`sched` file before it goes into `equiv/`.** `--xargs` adds the cross-block argument check that caught four of the eight. Other options: `-x` (what only one side has), `--assoc`, `--eqsym`, `--virt-this`, `--ret=`.
- **Take prototypes from the callee's definition.** A short prototype can even compile to identical bytes when the missing register happens to hold the right value, so exact files aren't immune as source. Known wrong declarations left in older files are listed at the end of `docs/SCHED_REVIEW.md` (fn_8031292C with two floats, fn_801030B8 with five arguments, fn_800C5EA4 with six, fn_8017F68C float-first).
- **No tool compares values that cross a block edge in a non-argument register.**
- **m2c first, then a model sibling:** writing from `tools/m2c_draft.py` output as a few inlines put the 4.7 KB fn_80131DE4 at `sched` in five compiles. Big draw routines with 18+18 saved registers reach `sched` in original statement order with the WGPIPE form.
- **Hand-written initialisers over pooled statics can be exact:** .bss statics are laid out in declaration order even when unused; .data objects follow definition order with a function's jump table at that function's position.
- **`Filt* fp = &f;` before a loop** gives `addi rS,r1,N` held in a saved register. `subi; cntlzw; srwi.` on a call result is `return (u8)f() == 1;` in an inline.
- **A hoisted constant spilled as a double** is an unnamed temporary; any named local spills as a float.
- **`operator=`-style copies return the destination**, which keeps r3 alive. Returning a struct by value gives the word copy; assignment between locals gives `lfs/stfs` pairs.
- **An unrolled loop count gives the true bound** (`ctr = 0x7f` with two bodies was `i < 0xff`). An argument copied to r9 before a six-register call means a seventh parameter.
- **Open:** dead `srawi` in texture loops (fn_8017C40C, fn_8017D428, fn_80143908), `frsp` through a double-typed path (fn_800DC824), zero idiom, local-vector hoisting, fn_8004B870 and fn_8024C57C (large static initialisers), fn_800F98E4 (no draft).

## Round 22: the last functions without a draft

Every game function now has source: 13 more exact, 12 more equivalent, 6 complete drafts (fn_80116DB8, fn_800F98E4, fn_8004B870, fn_8024C57C, fn_80144324, fn_801478F4; their headers say what differs). Region notes: "Round 22" sections and `NOTES_round22_b.md`.

- **Compiler `__sinit` functions can be credited under their `fn_` name** when written by hand: inline constructors over pooled file statics, including the base constructor's dead vtable store (store 0 when the base vtable is gone from the DOL). Without that store the registers come out reversed (fn_8013157C).
- **Check large static initialisers by evaluating the stores:** symbolically run the original's and the draft's stores and compare the final values (build/tmp/r22a/symstores.py, cmpstores.py).
- **`const T*` vs plain pointer parameters move the first field load** relative to the prologue stores (fn_80092E10, fn_80093084).
- **Function-local aggregate initialisers go into the file's `...rodata.0` pool;** POD brace-initialisers returned by value from an inline read `.sdata2` templates byte by byte; a `static const` local gives a `li` base.
- **A `case 0` that only re-truncates (`x = (s16)x;`) survives as its own block**; `break` or `x = x;` merge it into `default`.
- **Script VM pushes are an inline `*vm->sp++ = v`;** a macro gives offset stores from one register.
- **Type searches (tys.py) can change behaviour** (`int` to `s16`): run symcheck afterwards. Wrong float constants show only in `check_func.py -v`.
- **CATALOG corrections:** fn_80078CCC is the allocator `(size, file, line)`; fn_8012C250 returns int.

## Lessons from round m1 (unit-blocking functions)

Yield: 16 of 102 near misses exact, plus fn_8012E854 and fn_80117F74 after the build thread merged their dead `blr` pseudo-functions in symbols.base.txt.

- **Move a loop or computation into an inline with its own locals** when only loop counters, pointers or temporaries sit in the wrong registers. This was the most frequent fix; accessor inlines (`tid(u)`, `wW()`) were next.
- **Full permutation of declaration orders** pays off where a move-one hill climb stalls: fn_80168098 went exact only at one of 720 orders. Worth running whenever there are 7 or fewer locals.
- **Recursive inlining several levels deep** can be written as hand-made inline levels (fn_80008B50: Del1..Del4, the last calls the real function).
- **Nested call arguments** (sprintf args as calls, evaluated last to first) instead of named locals (fn_80288094).
- `check_func.py` takes options before the source path: `check_func.py --symbol-map X.symbols.json --strict-references X.cpp`.
- Per-function logs of what was tried for the remaining 86: build/tmp/m1/m1-{a,b}/results.tsv (local only).

## Lessons from round m2

Yield: 10 of 72 exact. New levers:
- **Per-iteration address instead of a walking pointer** (`head = &c->lists[i]` inside the loop) fixed register order twice; the reverse (a `Fog*` walker stepping by sizeof) fixed it once. Try both.
- **A repeated statement block as a small constant loop** (`for k < 3`) that the compiler unrolls (fn_801A2268).
- **An empty `case -1: break;`** reshapes the switch comparison tree (fn_800C4104).
- `tools/equiv/dd.py` now also finds originals that moved to `build/RFEE01/asm/tu/`.
- Improved-but-not-exact drafts (fn_800A4D88 2 words, fn_800A6DE4 3, fn_80066E24 11, fn_800665E4 12, fn_800A6978 8, fn_800A84A4 8) are in build/tmp/m2/m2-{a,b}/ with logs in results.tsv (local only).

## Help-bar constructor family (ctor-puzzle)

- **Read the destructor before spelling a constructor.** The help-bar puzzle (31 functions, ~100 failed spellings) was a wrong layout: 0x40..0x4F is a string member with a loop-zeroing constructor, not four ints. The destructor and a draw method showed it.
- **Some register colourings only come from real C++ classes.** The same stores written as structs with explicit vtable stores (even with the loop) stay wrong; compiler-generated vptr stores in a 3-level hierarchy match. Map `__vt__N<Class>` to the `lbl_` vtables with a `.symbols.json` (`src/game/helpbar.h`, 30 functions exact).
- **Sites with other constants** take them as constructor arguments (`new HbHelpBar(0x316)`); other widget kinds get their own small class deriving from `HbWidget` (`HbPanel`, `HbInfoPanel`).

## Lessons from round m3

Yield: 3 of 27 exact (fn_800A3FA4 and fn_800A40B4 complete unit 800A2200-800A4420, plus fn_800A6DE4).
- **A value in the wrong callee-saved register:** read it in its own inline with a named local (`static inline int Id(...) { int id = ...; return id; }`); fixed fn_800A6DE4, improved fn_800A6978.
- **Two int-to-float conversions in one expression:** named locals plus a declaration-order search fixed the float registers twice.
- Remaining near misses (fn_800A4D88 2 words, fn_8009999C 2, fn_800A6978 7, fn_800A84A4 8) and per-function logs are in build/tmp/m3/m3/ (local only).

## Round m4 (branch `matching`, paused 2026-11-14 at the usage limit)

Yield: 7 exact of 42 (fn_800156C8, fn_8001AB10, fn_8001B284, fn_80024EFC, fn_800C5A34, fn_8022ADF0, fn_80283BC8). Big 1-blocker functions (list A) gave 0 of 10.
Levers: `bx += ...` instead of `bx = bx + ...` changes register ranks (fn_800C5A34); reading a size through `Dim** t` puts t/w/h in r3/r4/r5; `(f32)x / 4.0f` fixes fmadds operand order (fn_8022A8A0); declaring a byte local as `u8` fixed every register in fn_801AF2A8 (left: clrlwi at assignment).
Best near misses saved as `wip/m4_<fn>.cpp`: fn_80270348 (4 words), fn_80148D44 (4), fn_8022A8A0 (10), fn_801AF2A8 (12). More drafts and the per-function logs are local in build/tmp/m4/m4-{a,b,c}/ (results.tsv), e.g. fn_80055A64 4 words, fn_8005586C 12, fn_80017344 13.
Known wrong prototype still in the fn_802828B4 equiv and the fn_80282FF4 wip: fn_8017F68C is `(int mode, f32, f32, f32, f32)`. fn_800CB69C's symbols.json is stale (`dirs$189`, fixed map in build/tmp/m4/m4-a/g1.symbols.json).
Resume: m4-c had not finished list C (build/tmp/m4/targets_c.tsv): see which rows lack a line in build/tmp/m4/m4-c/results.tsv.

## Round m5 (one agent)

Yield: 3 exact (fn_80148D44, fn_8022E620, fn_80230FB0) of about 20 attempted; no unit completed (8022DFE0 now has 2 of 4 open functions left).
- **Hoist order of an sda address:** declare the global as the struct it really is (`struct { u32 f; u16 ctr; } lbl_804CB878; lbl_804CB878.ctr++`) instead of a scalar; set a header's conflicting declaration aside with `#define`/`#undef` around the include (fn_80148D44).
- Near misses still open (2-5 words): fn_80109DF8 2, fn_802225E8 2, fn_802307F4 2 (`wip/m5_fn_802307F4.cpp`), fn_800EB988 3, fn_8015804C 3, fn_80270348 4, fn_80055A64 4, fn_80141334 4, fn_8008A868 5, fn_8027ECA4 5. Logs in build/tmp/m5/m5/results.tsv (local only).
- Units 80140BA4 (dead-srawi fn_80143908), 80144324 (paired-single helpers), 80221FD8, 80223B80, 8022516C can't complete soon; skip them.

## Round m6 (one agent, Fable)

Yield: 7 exact (fn_8019F108, fn_8019F3A8, fn_80183944, fn_800FB398, fn_800FDDE8, fn_8010436C, fn_80137BC8) of 22 never-tried rows listed as 1-2 words in EQUIVALENT.tsv.
- **Dead first store sets constant creation order** (fn_8019F108, fn_8019F3A8): when 0 and 1 sit in each other's registers, write a dead store of the one that must be created first (`w->mode = 0; w->flags = 1; ... w->mode = 0;`).
- **Named local before a zero-initialised aggregate** (fn_80183944): `int r = col[0] >> 1; LCol c = {0,0,0,0}; c.r = r; ...` gives the first byte r5, the zero r4.
- **Compound assignment for int x float** (fn_800FDDE8, fn_8010436C): `n *= k;` keeps the first float-to-int result in n's register; `n = (int)((f32)n * k)` puts it in r0. The original's "multiply by 1.0f" is `n *= (1.0f - slow)` in a shared inline with slow = 0.0f; in fn_8010436C the factor had to be a named float computed first.
- **Hoisted constants: creation follows definition order, rank follows declaration order** (fn_800FB398): `f32 fy; f32 fx; f32 s = 0.5f;` at the top of the loop body.
- **No local for a global base inside a loop** (fn_80137BC8): `lis r4 / li / addi r30,r4` means the loop used the global directly and the address was hoisted.
- **Constant loop over a repeated store pair** (fn_80137BC8, confirms m2): `for (k = 0; k < 4; k++) { H(i*4+k) = ...; L(i*4+k) = ...; }`.
- Rows marked `sched 1-2 words` can hide large register differences (the class masks registers): fn_8011E864 is 64 words, fn_8012152C ~40, fn_801D820C ~35 unmasked.
- Near misses still open: fn_800FBC90 2, fn_80168BF0 2, fn_801BC88C 2, fn_801DB3F4 2, fn_8027C5CC 2, fn_801BFB58 2 (last three: a short-lived value takes the lower of two free callee-saved registers, probably one common cause), fn_8023DC38 3, fn_801B05F8 3, fn_80246E68 7, fn_801D65EC 14, fn_8021C31C 21 (entry block fixed, draft local). Logs and drafts in build/tmp/m6/m6/ (local only).

## Round m7 (two agents, Fable)

Yield: 19 exact. List a (rC2 rF rG rH rI rM rQ): fn_801BC88C, fn_801BB530, fn_801CB1A0, fn_801DA800, fn_80158CA0 (+ siblings fn_80158DB8, fn_80158EE0, fn_80159008, fn_80159124, fn_80159244), fn_801959A0 (+ fn_8009999C). List b (auto rA rB rE rN rO rR): fn_801DB3F4, fn_8027C5CC, fn_80265574, fn_8006CE30, fn_802732FC, fn_802643B8, fn_80047974. Stale rows (already exact inside multi-function files): fn_801EDF9C/fn_801EEFA4/fn_801FE8BC (fn_801ECF94.cpp), fn_8005B6E4..fn_8005CF68 (fn_8005B508.cpp), fn_802836C0 (fn_80283528.cpp), fn_80020764 (fn_80020354.cpp): check per-function `OK` lines before listing targets.
- **`#pragma opt_lifetimes off` plus variable reuse** (fn_801DB3F4, fn_8027C5CC): for "a short-lived value takes the lower of two free callee-saved registers", the pragma gives each variable one register for the whole function; store the short-lived value into the variable whose register the original uses. Neither alone works.
- **Narrow parameter type flips prologue copy order** (fn_801BC88C): `u16`/`s16` second parameter gives `mr r27,r4` before `mr r26,r3`.
- **Explicit induction variables in the `for` header** (fn_801BB530): `xp -= 20, q--, i2--` and permute their declarations.
- **r3 read after a branch where ours uses the saved copy = wrong prototype** (fn_801CB1A0): fn_8001EBC8/fn_8001ECE4 are `(f32, f32, f32, f32, int)`; several rF files still declare `(int, f32, ...)`.
- **CSE temporary in the wrong saved register** (fn_801DA800): name it as a function-level local and grid its declaration position against the loop counter; commutative add operand order follows operand types (`u32 top`).
- **Binary search over a table is MSL `lower_bound`** (fn_80158CA0 and 5 siblings): `int k = key; int len = n; while (len > 0) { i = first; len2 = len / 2; i += len2; if (i->key < k) { first = ++i; len -= len2 + 1; } else len = len2; }`.
- **Stack memory streams are real classes** (fn_801959A0, fn_8009999C): base ctor `own = 0` (dead store fixes registers), dtor frees; map `__vt__2MB`, `__vt__3MB2`, `__vt__2SS` to lbl_80380940, lbl_80380928, lbl_80388858.
- **Reuse existing int locals as call-argument temporaries** (fn_80265574): `x = (int)fx; y = (int)fy; f((s16)x, (s16)y)`.
- **Register rank among many call-crossing locals: interference degree first, declaration order second** (fn_8006CE30): probe natural vs fully reversed order to see where groups split.
- **`(n + 1) * K` written as `n * K + K`** (fn_802732FC); **0/1 flag typed `bool`** (fn_802643B8); **loop-tail increments not in source order: try all orders** (fn_802643B8); **`x == 1 || x == 2` flag as an inline returning the `||`** (fn_80047974).
- Strict check with pooled statics: map `"...bss.0"` to the first pooled label and `__div2i` to fn_8028C418 (rF_8017F400/fn_80196E14.cpp fails strict for this reason).
- Near misses still open: fn_80168BF0 2, fn_801BFB58 2, fn_800FBC90 2, fn_80069220 2, fn_80150B20 3, fn_8011D580 3, fn_80181470 4, fn_801B78F0 5, fn_801151BC 5, fn_800FA264 5, fn_800F7BF4 5, fn_80069F14/fn_8006A434 5, fn_800642B4/fn_800649AC/fn_800656BC 6 (one shared loop), fn_80264034 6, fn_801875CC 6. Logs and drafts in build/tmp/m7/m7-{a,b}/ (local only).

## Round m8 (one Fable agent, one Sonnet agent)

Yield: 13 exact. Fable (m7 near misses and new rows): fn_80069220, fn_801151BC, fn_800F7BF4, fn_80069F14 + fn_8006A434, fn_801CABAC, fn_8025F0E8, fn_8000BC20, fn_8017B040, fn_8010403C (in `fn_8010403C_m8.cpp`, because `fn_8010403C.cpp` holds fn_80102300). Sonnet (never-tried rows): fn_80120F50 + fn_80121080, fn_801B6B18. Stale rows (already exact): fn_801E31D4, fn_801E5640, fn_801ECF94, fn_8005B508, fn_8025F068.
- **Undo hand-written strength reduction** (fn_80069220): `it->x = (s16)x0 + r * (s16)dx;` inside the inner loop lets the compiler build the accumulators and hoist the `extsh` in the original order.
- **Call an accessor twice** (fn_801151BC): `Cost(t, job) >= 0 ? Cost(t, job) : 0x7fff` gives the pointer two uses and fixes the volatile registers. fn_8011540C could be simplified the same way.
- **Drop helper locals from old drafts** (fn_80069F14/fn_8006A434, fn_8025F0E8 `f->t++` after the interpolation, fn_8017B040 `--o->wait`); the reverse, a block-local `void** d = c->data`, fixed fn_8000BC20.
- **Fields read inside an inlined predicate as named locals** passed in, declared `mdl, f, f2` (fn_800F7BF4).
- **One-line float helpers as inlines** (`fabsf_()`, `Deg()` in fn_801CABAC) make their results separate temporaries and fix f1/f2/f3.
- **Compound assignment and store order** (fn_8010403C): `n = speed / K; n *= dist;` with `p->t = 0` moved first.
- **Two flags in swapped registers:** write the inline body out with function-level locals and hill-climb their declaration order (fn_80120F50: `int mid; BOOL r; s8 v;`).
- **Named local for a cast call argument** (fn_801B6B18: `s16 n = lbl_803E7320[0]; Count(d, n, ...)`).
- `#pragma scheduling off` is a useful probe: it shows the order before scheduling.
- **Wrong prototype in rF drafts:** fn_8001ECE4 is `(f32, f32, f32, f32, int)` but the fn_801CD05C and fn_801CCCBC equiv drafts declare it mode-first; grep other callers of fn_8001ECE4/fn_8001EBC8. symcheck.py crashes on functions whose original moved to `asm/tu/` (use dd.py).
- Near misses still open: fn_800D70F4 2, fn_80168BF0 2, fn_801BFB58 2, fn_800FBC90 2, fn_80150B20 3, fn_8011D580 3, fn_80181470 4, fn_801135C0 5, fn_800DC770 5, fn_80075AC0 5, fn_801B78F0 5, fn_800FA264 5, fn_800FCD10 6, fn_80263418 6, fn_800642B4/fn_800649AC/fn_800656BC 6, fn_80264034 6, fn_801875CC 6, fn_801CD05C 7, fn_80263B64 7, fn_80246ADC 7, fn_80217DF8 7, fn_802173C0 8, fn_8017E470 8, fn_801CCCBC/fn_801CCE8C 8, fn_801B3D3C/fn_801B4480 9, fn_80134F90 9. fn_80177A5C and fn_80217DF8 drafts use local statics where the original reads lbl_804CE470/lbl_804CFBCC. Logs and drafts in build/tmp/m8/m8-{f,s}/ (local only).

## Round m9 (one Sonnet agent, first pass over never-tried rows)

Yield: 3 exact of 30 (fn_801B0E88, fn_801BB334, fn_800DF0B8); fn_80263D18 was stale (exact in fn_80263D18_x.cpp). About 319k tokens.
- **In-place add in one switch case only** (fn_801B0E88): case 0 `x = d->x1C; x += 0x10;`, cases 1 and 2 keep `x = d->x1C + K`.
- **Declaration order plus loop-tail order** (fn_801BB334): `Slot* s; SkillD* d; int i;` and `s++, i++`.
- **Write one of two multi-return inlines out in place** when their results swap registers (fn_800DF0B8: `UnitId()`).
- **Per-site, differently spelled copies of a repeated inline**, searched by script (fn_801241F4 15 -> 6).
- **A block moved into an inline with its own parameters** (fn_800DE044/fn_800DE1B8 16 -> 11); **an explicit pointer stepped by 4 bytes** for 2-iteration loops over a member array (fn_8019555C 19 -> 5).
- Listed distances that were far too low: fn_8011FFD0 150 (listed 14), fn_801951BC 30, fn_800FF170 24, fn_801C63F0 17.
- Best pickups: fn_800D5C44 4 (float load order f2,f1,f0 vs f0,f1,f2), fn_8019555C 5, fn_801241F4 6, fn_800DE044/fn_800DE1B8 11. Per-row log and drafts in build/tmp/m9/m9-s/ (local only).

## Round m10 (one Fable agent)

Yield: 7 exact of 27 near misses (build/tmp/m10/targets_f.tsv); the second half (after a usage-limit pause) gave none. Exact: fn_800D70F4, fn_800D5C44, fn_801135C0, fn_800DC770, fn_80075AC0, fn_800FCD10, fn_80263418 (files with `_m10` where the natural name was taken).
- **Coalesced copy in the loop preheader** (`void* p2 = p;`) flips a scheduler tie between `li` and `addi@l` (fn_800D70F4).
- **Float temps of an inlined copy declared in reverse** (`az, ay, ax`) fixes lfs order (fn_800D5C44).
- **Named function-level int reassigned with an `(s8)` cast** for a loop column (fn_801135C0); **named f32 x, y read first, converted at the stores** (fn_800DC770).
- **Integer arithmetic for a block end** (`u32 q = (u32)h + (size & ~3)`, fn_80075AC0); **named zero assigned right before the inline call** (fn_800FCD10).
- **Function-level locals shared by reference between loop inlines**, assignment found by a grid (fn_80263418; fn_8019555C 5 -> 2 the same way with `#pragma opt_lifetimes off`).
- **The preheader copy only works next to a loop;** in straight-line blocks the copy is propagated away first (about 75 placements did nothing on fn_80168BF0, fn_800FBC90, fn_800FA264). `#pragma scheduling off` dumps don't show what the allocator saw. Inside an inline, float temporaries colour in reverse declaration order compared with a stand-alone function.
- The shared-by-reference lever failed on fn_80263B64 and fn_801241F4; `opt_lifetimes off` scrambled fn_80263418. fn_801951BC (same file as fn_8019555C) wants a different loop-counter register, so the two can't share one spelling as written.
- symcheck.py crashes on fn_800DC770 and shows only the `sin`/`fn_80295940` name on fn_800FCD10.
- Near misses still open (unchanged by m10 unless noted): fn_8019555C 2 (was 5; left `c->sel` load in r0, want r9), fn_80168BF0 2, fn_801BFB58 2, fn_800FBC90 2, fn_8011D580 3, fn_80150B20 3, fn_80181470 4, fn_801B78F0 5 (only load/store order), fn_800FA264 5, fn_801241F4 6, fn_801875CC 6, fn_80264034 6, fn_800642B4 family 6, fn_80263B64 7, fn_80246ADC 7, fn_801CD05C 7, fn_802173C0 8, fn_801CCCBC/fn_801CCE8C 8, fn_800DE044/fn_800DE1B8 11. Logs and drafts in build/tmp/m10/m10-f/ (local only). Most of these have now failed in two or three rounds.

## Round m11 (one Sonnet agent, triage only)

All 71 never-tried rows measured, none exact or stale, none within 6 words. Kinds: 48 registers only, 11 float registers, 10 scheduling/structure, 2 stack slots. `sched` rows are mostly far above their listed distance (fn_801C336C 66 vs 22, fn_8021BB04 86 vs 35, fn_801B2150 184 vs 115).
- Best value: the six-function family fn_8000AB6C/fn_8000AE38/fn_8000B100/fn_8000B3C8/fn_8000B690/fn_8000B958 (32 words each, one shared draft, same register pattern).
- Next: fn_800AF584 13 (r24/r26), fn_800F6AEC 17, fn_80258C70 19, fn_80260140 19, fn_800659B0 21, fn_8021C6FC 21, fn_80260E58 22, fn_800581F4 23, fn_8006A834 23, fn_80136C34 23, fn_8027AF54 26 + fn_8027ACDC 29 (shared draft).
- Ranking and per-row table in build/tmp/m11/m11-s/ranking.md and results.tsv (local only; cause/effort columns are script guesses).

## Round m12 (one Fable agent, m11 triage candidates)

- 16 rows from the m11 ranking. 7 functions exact in 6 files: fn_80134ECC (rL), fn_8006A834 (rO), fn_801C62D8 (rF), fn_8027ACDC + fn_8027AF54 (rN), fn_801633C0 (rQ), fn_8021C6FC (rI). `--strict-references` reports MISMATCH for fn_8021C6FC only because of the unchecked `__ptmf_scall` reference (same as existing fn_801EDC18); plain check is MATCH, build byte-identical.
- Improved but not exact: fn_8000AB6C family (6 functions, 32 -> 19 words each), fn_800659B0 21 -> 13, fn_8005840C 21 -> 12, fn_80136C34 23 -> 16, fn_8027D14C 25 -> 23. No change: fn_800AF584, fn_800F6AEC, fn_80258C70, fn_80260140, fn_80260E58 (all already flat and hill-climbed; stop trying).
- Lessons:
  - All locals at the top of the function, volatile ones before loop counters (fn_80134ECC); one volatile local after a counter flips the callee-saved order.
  - Remove names the original doesn't have: single-use call results become nested arguments. In the fn_8027ACDC pair both sprintf sites must change together (one alone 26 -> 38).
  - An accessor inline for a repeated table row (`&tbl[d->page]` at every site) moves the hoisted base where no declaration order could (fn_801C62D8).
  - Twice-used inline: write it out with function-level locals, then hill-climb (fn_801633C0, fn_800659B0).
  - Read a swap's `mr` sequence literally; the original may keep the second value in a typed temporary (fn_801633C0).
  - Explicit walking pointer for a strength-reduced `&a[i]` so its declaration position counts; iterator assigned inside the argument list keeps evaluation order (fn_8021C6FC).
  - Read-modify-write through an `int` temporary fixes address/value/new-bits registers (fn_80136C34).
- Wall: compiler-made values (0/1 flags, constants held across a call, the temporary of a `const T&` bound to an rvalue) are coloured before all declared locals regardless of type, position or spelling. This blocks fn_800659B0, fn_800581F4/fn_8005840C, fn_8027D14C, probably fn_80260E58/fn_80260140, and the fn_800642B4 family.
- Drafts, results.tsv, lessons.md and helper scripts (rm.py register mapping, vr.py variants) in build/tmp/m12/m12-f/ (local only).

## Round m13 (one Opus agent, next rows of the m11 ranking)

- 18 rows (17 untried from the m11 ranking, 31-60 words, plus fn_80136C34 from m12). 8 functions exact: fn_80063DFC (rC2), fn_80163808 and fn_801635B8 (rQ), fn_801D7D38 (rF), fn_8024CF54 (rS, with symbols.json; also emits `__sinit` for the static `sMutex` like the equiv draft), fn_80178364 (rR), fn_801E8680 and its sibling fn_80224554 (rI, same body, grid fields 4 bytes later). Build byte-identical.
- Near misses (drafts in build/tmp/m13/m13-o/, local only): fn_802662EC 7 words (hoisted 0x4330 constant in r24 vs r23, the m12 wall), fn_80171E5C 9, fn_80136C34 16, fn_800BBE94 17 (was 56), fn_800787E4 19 (was 60), fn_80138000 33, fn_8021CF08 33, fn_8016B90C 36. No progress: fn_8006436C, fn_800D5DC4 (stack slots), fn_801B09D0.
- Lessons:
  - Without a short-lived (non-call-crossing) local, declaration order does nothing. Writing an inline's walking pointer out as a function-level local gives the hill climb a pivot (fn_801635B8 42 -> 0).
  - Under `#pragma opt_lifetimes off`, give each loop its own counter where the original keeps them in different registers (fn_80178364).
  - Volatile registers off by one for a CSE'd value: swap neighbouring independent statements that use it (fn_80178364).
  - Volatile spellings: named copy of a field before `%`, chained assignment `o->cur = c = o->cur - cols`, clamp as an expression without a named local (fn_801E8680).
  - "Remember best" updates: copy the order of the original's `mr` triple (fn_80163808).
  - Explicit `(u8)` cast in a call argument instead of `(int)` into a u8 parameter (fn_80063DFC).
  - Declaring a block's locals at the start of that block is a separate lever from hoisting them (fn_80171E5C 19 -> 9).
  - `opt_lifetimes off` alone may do nothing, but chained hill climbs under it can (fn_800BBE94 56 -> 17).
  - Per-site copies of a repeated inline, each with its own searched local order (fn_800787E4 34 -> 23).
- Notes: hill.py's score can disagree with check_func (fn_8024CF54 scored 46 while OK); re-check .best files. fn_8016B90C's original uses the map pointer as a plain integer constant (`(Map*)0x803EC898`, no relocation, kept in a stack slot). fn_801D7D38 keeps the equiv's local s16 prototypes (definitions in fn_801D60D0.cpp take int).

## Round m14 (one Opus agent, m13 near misses + ranks 40-60)

- Stopped early after ~15 of 24 rows (tool permission checks stopped answering). Not tried: fn_801B0B58, fn_80277E10, fn_801C3AB4, fn_8000A838, fn_801681E0/fn_80168558, fn_8011CDC0, fn_8027970C, fn_80261728, fn_8000DD0C.
- Exact: fn_80171E5C (rQ). Fix: delete the second scan's `Map* m = &lbl_803EC898` local and write `((Map*)&lbl_803EC898)->` at each use, then hill-climb the block's locals.
- Near misses (drafts in build/tmp/m14/m14-o/, local only): fn_802662EC 4, fn_801B40B0 6 (was 62), fn_80236384 7 (was 47), fn_801E7E1C 14 (was 63), fn_800BBE94 17, fn_800787E4 19, fn_80204EB4 35, fn_800650DC 43, fn_80164330 43, fn_8024CCF8 45, fn_80112CD4 59. Sibling fn_801B4480 (std::list merge) at 9 words.
- Lessons:
  - Delete named base-pointer locals the original never had; the compiler hoists the address as its own temporary, in the right register (fn_80171E5C, fn_802662EC). The m12 "hoisted 0x4330 constant wall" on fn_802662EC was really this.
  - The reverse: when the original keeps a pool base in a high saved register, declare it as a struct-pointer local so declaration order ranks it (fn_8024CCF8).
  - Hill-climb an untouched equiv draft once before restructuring (fn_801B40B0 62 -> 6).
  - `x / 4.0f` gives a different fmadds operand order than `x * 0.25f` (fn_801E7E1C).
  - The order of increments at the end of an inner loop follows the order in the for header (`col++, idx++`).
  - Float constants hoisted out of a loop load in their own order regardless of source (fn_801C336C).
- Note: `--symbol-map` rejects the existing src/game/rS_8023FD30/equiv/fn_8024CCF8.symbols.json ("'...bss.0' must be an object-local symbol absent from symbols.txt"); the checker seems to have changed since.

## Round m15 (one Opus agent, m14 near misses + untried rows)

- 14 rows. 6 functions exact in 3 files: fn_801B3D3C (with fn_801B40B0, fn_801B4480; rF, three std::list::merge copies), fn_801681E0 (with fn_80168558; rQ, MSL std::sort pair), fn_80223CF4 (rI, sibling of fn_801E7E1C; plain check MATCH, `__ptmf_scall` unchecked). Build byte-identical.
- Near misses (drafts in build/tmp/m15/m15-o/, local only): fn_801E7E1C 2 (one scheduling pair), fn_802662EC 4, fn_80236384 7, fn_80261728 13, fn_8027970C 21, fn_8011CDC0 25, fn_80277E10 26, fn_8000A838 39, fn_801C3AB4 42. No move: fn_801B0B58 (75 for every spelling, like fn_801B09D0), fn_8000DD0C (its inlined fn_8000D228 isn't exact either).
- Lessons:
  - Copy an exact instantiation of the same template from another region. rI fn_8021CA54.cpp (fn_80224AAC) has an exact list merge (`while` loop, block-local `nb = j` copy, tail block with own locals); transplanted plus a short hill climb it solved all three rF merges. rH fn_8011BD2C.cpp has an exact sort with a `Step` inline; `for (;;) { --j; if (i == j || comp) break; }` fixed the sort pair's last word. The sort pair also needed MSL `__selection_sort` and `min_element` as separate inlines, loop pointer declared before `r`.
  - A 0/-1 select as `if (s > 0) row = -1; else row = 0;` instead of a ternary schedules differently (fixed "extsh one slot late" in fn_80223CF4).
  - Delete named locals the original computes as compiler temporaries: `s16 cw` in fn_801E7E1C (write `x += (s16)cwi`), item pointers in an inlined predicate in fn_8011CDC0 (89 -> 25), a named clamp bound in fn_80261728.
  - `hh / 2.0f` instead of `hh * 0.5f` fixes fnmsubs operand order; struct field store order fixes volatile registers; `for (col = 0, x = 0; ...)` fixes zero-init order.
- Notes: old drafts of the solved functions remain in equiv/ and wip/. fn_801681E0.cpp keeps three unused locals from the hill climb; it matches as is.

## Round m17 (one Opus agent, m15 near misses)

- 9 rows, 0 exact; no draft improved on m15 (fn_801E7E1C 2, fn_802662EC 4, fn_80236384 7, fn_80261728 13, fn_8027970C 21, fn_8011CDC0 25, fn_80277E10 26, fn_8000A838 39, fn_801C3AB4 42).
- Findings:
  - fn_802662EC is a pre-RA scheduling effect: `#pragma scheduling off` gives the magic constant f3 in both calls; f1/f2 depend on where the scheduler puts the 0.0 and 255 loads. Any extra int instruction after the first result's `lwz` produces the original's order, so the original has the same instructions in a different pre-scheduling order. `u8 a`/`s16 a` gives the exact float block but misplaces clrlwi/extsh.
  - fn_801E7E1C: the copy of a call argument into r4 is created at call lowering, after all statements and inline-argument computations; statement order can't reach it (~30 spellings tried).
  - Wall family: a short-lived temporary takes a different one of several free registers (fn_80261728, fn_8027970C, fn_80277E10, fn_8011CDC0, fn_8000A838). Per-site copies, hill climbs and variable merging don't move them.
  - fn_801C3AB4's draft copies two 9-float tables from local templates where the original uses lbl_8036E0D0 / lbl_8036E0F4.
- Drafts and logs in build/tmp/m17/m17-o/ (local only).

## Round m16 (one Opus agent, older near misses from m12-m14; ran in parallel with m17)

- 11 rows, 1 exact: fn_80136C34 (rL). Fix: coordinate reads as `s8 x = call()` instead of `int x = (s8)call()` (puts the hoisted map base above x and y), all 16 locals at function level, one counter per loop (i1, i2, i3), 150 s hill climb.
- Improved: fn_8021CF08 33 -> 12 (y as `u16` lets `o` outrank y; not the original spelling, it loads with lhz), fn_800650DC 43 -> 33. Unchanged: fn_800BBE94 17, fn_800787E4 19, fn_80138000 33, fn_80204EB4 35, fn_8016B90C 36, fn_80164330 43, fn_8024CCF8 45, fn_80112CD4 59. Drafts in build/tmp/m16/m16-o/ (local only).
- Lessons:
  - Local types change register rank: s8/u8/s16/u16 vs int moves a value against parameter copies and compiler temporaries where declaration order does nothing. One compile per variant; try it first on rows that ignore declaration order.
  - Callers can inline fn_800B5784's recursion (contradicts src/game/rG_800A3D88/NOTES.md): `inline` plus `#pragma always_inline on` and `#pragma inline_depth(5)` gives fn_800BBE94 the original size and layout. Pragma state is read at file end, so the callee's own weak copy comes out too deep; a template stand-in `template<int D> inline Eff* Lk(...)` with `Lk<0>` calling the real fn_800B5784 avoids that (build/tmp/m16/m16-o/alt_fn_800BBE94_template.cpp). Loop counters still colour differently. May apply to the whole fn_800B5784 caller family.
  - Drop a walking pointer the original never had, per loop (fn_800650DC).
  - `#pragma opt_lifetimes off` did nothing on fn_800BBE94's template form or fn_8016B90C.
- Note: fn_8016B90C's raw `lis 0x803f / subi` map constant is probably `&lbl_803EC898` with a relocation dtk missed (value goes through a stack slot); check_func no longer flags it.

## Round m18 (two Sonnet agents, "never touched" game functions)

- The 74-function list (build/tmp/m18/all.tsv) was stale: 73 are already exact, defined through macros (`STATE_FN`, `PLAYER_METHODS`, `PLAYER_DTOR2`, ...) that a grep for the function name misses. All 36 rN ones are in fn_8025EEF0.cpp. Use build/tmp/m18/m18-a/finddef.py (local) to find macro definitions.
- Only fn_800060BC (.init, `OSResetSystem(0,0,0)` wrapper) has no source; check_func reads only .text symbols, so it can't be verified. The game-code pool of untouched functions is exhausted.

## Round m19 (one Opus agent, fn_800B5784 effect-lookup family)

- 3 open callers. Exact: fn_800AF12C (rG). Fix: fn_80175E7C returns a 4-byte struct (`struct Rgba {u8 r,g,b,a;}`, `Rgba col = fn_80175E7C(&ta, &tb, f);` declared at the call) instead of a u32 split by hand, then one hill climb (32 -> 0). It keeps the hand-unfolded `E4`; `Lk<4>` scores 96.
- Unchanged: fn_800AF584 13 (a natural `SetTint(ChrE*, GXColor)` inline with colour by value gives the exact instruction shape, but stack slots and counters come out reversed: 164), fn_800BBE94 17 (every natural form scores 49).
- The natural recursive form does not reproduce already-exact callers (fn_800B7468: template 35, `L1..L4` chain 16, recursion + always_inline + inline_depth(4) 16; fn_800B5010: 35). Size, layout and scheduling are right; only locals from inlined bodies (loop counters, stack slots) come out in exactly reverse order. No pragma (inline_bottom_up, defer_codegen, opt_lifetimes, opt_propagation, auto_inline, inline_max_auto_size), local layout, type, definition order, C vs C++, or seven other compiler versions changed that.
- Likely explanation: callers have 1 + 3 levels and the exact standalone fn_800B5784 has 3 inlined levels, so the original probably inlined fn_800B5784's already-expanded body once. Our setup re-expands an `inline` callee from source per caller, and never inlines a non-inline same-file definition. Keep the hand-unfolded E1..E4 with searched declaration orders as the working method.
- Inlining facts (correct src/game/rG_800A3D88/NOTES.md "no setting makes callers inline fn_800B5784"): `inline_bottom_up` defaults on; turning it off changes the depth reached. push/`inline_depth(3)`/pop around an `inline` callee makes callers inline one level and grows the emitted fn_800B5784 to 0x35C. `always_inline on` + `inline_depth(N)` for the whole file expands N levels in callers and in the emitted copy. A `template<int D> inline Eff* Lk(...)` stand-in needs no pragma under `-inline auto` and adds no symbol. fn_800AF584's original probably passes GXColor by value, like the exact fn_800FCEE4.
- Experiments, drafts and scripts in build/tmp/m19/m19-o/ (local only).

## Round m20 (one Opus agent, old short "sched" rows)

- 63 rows from docs/EQUIVALENT.tsv listed at 1-3 words and tried once (rounds m1-m8). 0 exact.
- 22 rows are stale (already exact): fn_801E31D4, fn_801E5640, fn_8025F068, fn_801ECF94 (+fn_801EDF9C, fn_801EEFA4, fn_801FE8BC), fn_8005B508 and its 14 siblings up to fn_8005CF68. EQUIVALENT.tsv still lists them.
- Listed words understate sched rows badly: of 41 live rows only 9 are at 2-3 real words; others up to 79 (fn_80069428 79, fn_8011E864 69, fn_800776F8 55).
- Closest (real words, unchanged): 2: fn_8018524C (case-0 `li` order), fn_8001EBC8/fn_8001ECE4 (fmr copies at loop entry), fn_800D0BFC (hoist order of `li 0x40` vs table address), fn_802225E8 (inline-argument copy after `li i=0`, the fn_801E7E1C wall). 3: fn_8015804C, fn_8016EDE8, fn_8023DC38, fn_801B05F8. 4-7: fn_801197F4, fn_80167F5C, fn_8008D75C, fn_8002AFBC, fn_80075714 (4 with y,x,id statement order), fn_800EB048, fn_800A47AC.
- Lessons:
  - Two stored constants are coloured by first-store order (first stored gets the higher register); the original then schedules the other constant/store first, which no source order reproduces (fn_8023DC38, fn_8018524C). Treat as a scheduler wall.
  - Widget scroll-bar family (fn_801E941C, fn_801E8E88, fn_801FE108) as real classes (`SBase : HbWidget`, `SB : SBase`) gets vptr and stores right but is worse than the old equiv (75 vs 14); real Eff member objects are much worse (199); `new SB` swaps the object and m1 registers.
  - `int v = (s8)u8field` gives the original's `lbz; extsb` pair (fn_801197F4) but moves v's register; a separate `y*64` statement fixes slwi/extsb order in fn_8002AFBC but swaps load registers.
- Note: a `multiprocessing.Pool` script hung silently on macOS (workers never started); use ThreadPool for parallel compile helpers.
- Triage and drafts in build/tmp/m20/m20-o/ (local only).

## EQUIVALENT.tsv cleanup (2026-11-16)

- Removed 179 rows whose function is already exact: 88 found as `---- fn_X from src/game/...` C sections in the generated src/tu files, 91 more defined in exact src/game files (mostly rounds m8-m19, not yet in src/tu) and confirmed with `check_func.py` printing `OK fn_X`. 300 rows remain (299 functions + header). Two rows whose regex hit didn't confirm (fn_800DA1FC, fn_801151BC) were kept.
- A function is open when its tu file says `---- fn_X: not matching yet`. Grepping src/game for a definition misses macro-defined functions (STATE_FN, PLAYER_METHODS, ...).

## Round m21 (one Opus agent, least-tried open rows)

- 30 open rows of the cleaned EQUIVALENT.tsv (4-7 listed words, tried once, mostly m1-m8). 2 exact: fn_801CF040 (rF), fn_801386AC (rL, in fn_801386AC_m21.cpp because fn_801386AC.cpp holds fn_80138628). No stale rows.
  - fn_801CF040: write the At2 lookup inline as `s->x0 < 0 ? 0 : (void*)((u8*)s + 0x50 + (s->x0 << 5))`; the ternary puts the result in r31 shared with `w = Wpn(w)`, and `0x50` before the scaled index sends the add temp through r4. Each change alone left 2 or 5 words.
  - fn_801386AC (listed 4, really 24): `ox = m->x - m->w / 2.0f` with `fx = s * ((0.5f + x) - ox)` (fnmsubs + fsubs), `/ 2.0f` instead of `* 0.5f`, and `f32 s; f32 w; f32 tw = m->tw; w = m->w; s = tw / w;` for the f6/f7 colours.
- Near misses (real words; drafts in build/tmp/m21/m21-o/, local only): fn_801CF270 9 (was 20; prologue only), fn_800578FC/fn_80057B7C 4, fn_8001CD78 4, fn_80141334 4, fn_801507EC 5, fn_8021E23C 6, fn_8022130C 6 (two-stored-constants wall), fn_80063A80 7, fn_80076D48 7, fn_8003DD6C 7, fn_8007A1CC 9, fn_800769D0 10, fn_8011F70C 10. Real distances far above listed: fn_8013E77C 15, fn_80145980 70, fn_8022C384 87, fn_801420B0 219.
- Lessons:
  - Copy the exact sibling's spelling first: fn_801CF270's Ev25 part was fixed by copying sibling Ev25b's declaration order (`int k;` first).
  - Float multiply operand order follows `/ 2.0f` vs `* 0.5f`, not the source operand order.
  - CW removes a dead local or a dead 1-field struct but keeps a dead field of a 2+-member struct or `u32 g[2]` in a register (explains fn_80076D48's `HK hk`).
  - Call-lowering order of float literal arguments (fn_80280060) and sda byte loads (fn_8013E77C) doesn't change with inline parameter order, argument permutations or literal types.
- Note: hill.py's score is unreliable for rO files (fn_80076D48 scored 133 where check_func says 7); use check_func-based variant runners there.

## Round m22 (one Opus agent, m21 near misses + tried-once rows)

- 25 rows, 1 exact: fn_801CF270 (rF). Fix: use the sibling `Theirs()` inline from fn_801CE800.cpp (`s8 v = s->x0; if (v < 0) return -1; return 1 - v;`) instead of the in-place ternary, keeping m21's Ev25 declaration order (9 -> 0). No stale rows.
- Near misses (real words; drafts in build/tmp/m22/m22-o/, local only): fn_802307F4 2 (case 0 `id` in r29 vs r30; identical default body gets r30), fn_80263B64 3 (loops as static inlines `rel2`/`rel3` with own locals; loop 2 exact, loop 1 `i` r28 vs r27), 4: fn_800578FC, fn_80057B7C, fn_8001CD78, fn_80141334; 5: fn_801507EC; 6: fn_8021E23C; 7: fn_80063A80, fn_80076D48, fn_8003DD6C, fn_80217DF8; 8: fn_801E7990, fn_8026A9D4, fn_800785FC, fn_8010A2FC, fn_8017E470; 9: fn_801516AC, fn_80134F90, fn_80150F0C. Far: fn_80264204 22, fn_802267D8 21, fn_8006758C 28, fn_80135C44 129 (listed 9).
- Lessons:
  - Wrapping a computation in the sibling's tiny inline helper, even if it re-reads a field, can fix prologue colours and schedule.
  - Splitting independent loops into separate static inlines with their own locals changes colouring a lot.
  - In fn_802307F4 two identical case bodies get different registers in the original; a shared inline made both wrong.
  - fn_801507EC: plain C merges the two loads of lbl_804CB700 into one; only a volatile second read gives two.
  - fn_801516AC's exact sibling fn_80151600 has the same colouring as our draft, not the target's.
- Tooling: hill.py's score disagrees with check_func outside rO too (fn_80263B64: 10 vs 3). build/tmp/m22/m22-o/hill2.py scores with check_func; dis.py prints ours vs original side by side.

## Round m23 (three Opus agents in parallel, m23a/b/c)

- 43 rows (m22 near misses + tried-once rows). 9 functions exact, no stale rows:
  - m23a: fn_800487DC, fn_80048A98, fn_80048D54, fn_80048FF8, fn_800492B8 (rB, one file; family listed and real at 14 words, m9's 576-order grid had failed). Each switch body and its locals moved into `static inline void runN(Act* q)` (locals assigned cx, cy, x, y; declaration order from a hill climb inside the inline), and the cell copy into a `cp(Cell* e, Cell* o)` inline (locals declared separately, assigned a, d, c, b, stored a, b, c, d).
  - m23b: fn_80076D48 (rO; hash loop as `static inline u32 Hash37(const char* p)` over its own parameter, dead 31-hash kept in `HK hk; hk.g`), fn_801516AC (rM; clear loop as `static inline void WinClearI(int i, Win* w)` called as `WinClearI(0, f->win)`).
  - m23c: fn_8015F680 (rM; list walker `Unit*** list = (Unit***)&lbl_804183F0.res[0x85];` declared first, walked with `*(*list)++`), fn_80177A5C (rR; nine preset colours as separate `extern C4 lbl_804CE474; ... lbl_804CE494;` interior addresses of the merged .sdata2 lbl_804CE470, matching the original's `lbl_804CE470+0x4..+0x27` relocations; `void* anim; int end;` before `int f`). `--strict-references` flags only those interior names (not in symbols.txt); plain check is MATCH.
- Near misses (real words; drafts in build/tmp/m23/m23?-o/, local only): 2: fn_802307F4, fn_801F19A0, fn_801F8798 (stored-constants wall on x48 stores); 3: fn_80263B64; 4: fn_800578FC, fn_80057B7C, fn_8001CD78, fn_80141334; 5: fn_801507EC, fn_8026A9D4 (was 8), fn_802352C8 (was 10); 6: fn_8021E23C; 7: fn_80063A80, fn_8003DD6C, fn_80217DF8; 8-9: fn_801E7990, fn_800785FC, fn_8010A2FC, fn_8017E470, fn_80134F90, fn_80150F0C, fn_801A2588, fn_801E2F40, fn_80287B54; 12: fn_80066C48 (was 20).
- Lessons:
  - Whole body (or each switch body) as a static inline with its own locals changes how locals rank; a declaration hill inside the inline works where the same hill in the plain function didn't.
  - Inline parameters get their vregs and colour priority in parameter order, before the inline's locals; making the variable that needs the lower volatile register an earlier parameter fixed fn_80076D48 and fn_801516AC. It doesn't move callee-saved colours. Parameters colour and load in argument evaluation order (right to left), so they can't give disagreeing load and colour orders; locals inside the inline can.
  - Separate declaration and assignment: assignment order sets load order, declaration order sets colours, independently.
  - Declaration order of a pointer local can decide which of two loop invariants gets the lower register (fn_8015F680, fn_801F19A0's sentinel pointers).
  - Data inside a merged .sdata2 symbol: separate interior-address externs give per-use sda21 loads; `static const` copies or arrays get hoisted.
  - Look for SDK header inlines in library-style code (`MEMCreateExpHeap` -> `MEMCreateExpHeapEx(start, size, 0)`, fn_802352C8).
  - An inline's parameters merge with the outer parameters, so their order has no effect (fn_8006D19C).
- Tooling: build/tmp/m22/m22-o/hill2.py matched `OK fn_X` with one space while check_func prints `OK   fn_X`, so exact candidates scored 9999 and were thrown away; fixed to `OK +fn_X` (m22-era hill runs may have missed exact orders).
- Stale tu markers: src/tu still lists fn_80151424, fn_80151AA0, fn_80151B94 (exact in fn_80150AC0.cpp) and fn_80178364 as "not matching yet"; the tu files aren't regenerated for newer exact files.

## Round m24 (two Opus agents in parallel, m21-m23 near misses)

- 25 rows (2-12 real words). 3 exact, no stale rows:
  - fn_802307F4 (rI, 2 -> 0): in the fmtUnit switch, declare the locals of every case separately at the top of the inline (still assigned inside the cases), then hill that block: `u0, u1, n, k, u2, id0, id2`. Earlier rounds had only moved id/u to switch scope.
  - fn_802352C8 (rI, 5 -> 0): written like the SDK's `__DEMOInitMem`, with one set of function-level locals (`lo, hi, h, sz, k`) reused by the arena carve and every half; matched on the first compile. Calls use the real SDK names (MEMCreateExpHeapEx, MEMInitAllocatorForExpHeap, MEMAllocFromAllocator).
  - fn_8021E23C (rI, 6 -> 0): each `while (...) { ...; if (lvSum(...) % 100 == 0) break; }` loop moved unchanged into its own `static inline void upLoop(BO* o)` / `dnLoop(BO* o)`; that alone puts the costs at the non-loop canUp sites into f31.
- Unchanged near misses: 2: fn_801F19A0, fn_801F8798 (stored-constants wall: constants and string address are rebuilt at the store, so colour order follows store order; 36 orders, value/const& parameters, string literal all failed); 3: fn_80263B64; 4: fn_800578FC, fn_80057B7C, fn_80141334, fn_8001CD78 (free-register wall); 5: fn_8026A9D4, fn_801507EC; 7: fn_80063A80, fn_8003DD6C, fn_80217DF8; 8: fn_801E7990, fn_8010A2FC, fn_800785FC, fn_8017E470; 9: fn_80134F90, fn_801A2588, fn_80287B54, fn_80150F0C, fn_801E2F40; 12: fn_80066C48.
- Lessons:
  - Hoist the locals of every switch case into one declaration block at the top of the inline, then hill that block.
  - For SDK/library-style code try C89 style first: all locals at the top, reused in every block.
  - Moving a whole loop into an inline, with no other change, can fix float colouring at call sites outside that loop.
  - The body/loop-as-inline lever made most other near misses equal or worse (24-48 words); with fn_8010A2FC's loop body as an inline, CW stops inlining the nested Rd() helper.
  - CW gives one shared function-level variable separate registers in separate loops.
  - Check each extern against the callee's matched file: fn_80116CFC is `(Map*, s8, s8, s8)` (src/game/rH_80112B48/fn_80116CFCb.cpp); m23's fn_80066C48 draft declares it with ints ("2 wrong references").
- Drafts and logs in build/tmp/m24/m24a-o/ and m24b-o/ (local only).

## Round m25 (three Opus agents in parallel, 45 open rows untouched by m20-m24)

- 9 exact, 1 stale (fn_801DB3F4, already exact in rR):
  - fn_800244C4 (rA, 3 -> 0): `#pragma opt_lifetimes off` at file top (push/pop around the function did nothing) plus `if (p->s.l.lng == 0) size = ...; else size = ...;` into one variable; the pragma alone, or a ternary, changed nothing.
  - fn_801116F4 (rP, 15 -> 0): price term as `static inline int price(ItemE*, FSlot*)`.
  - fn_801BE154 (rF, 15 -> 0): written like the exact sibling fn_80186FA4 (plain function, `f32 w, h;` set to `x1 - x0`, `y1 - y0`).
  - fn_8006B528 (rO, 16 -> 0, listed "renamed"): all locals at the top C89-style, then a declaration hill (30 evals).
  - fn_80145078 (rL, 16 -> 0): hill over declaration order plus the last block's statement order (`n->d.pos = pos` after the vel stores).
  - fn_800D1D14 (rK, 18 -> 0): the exact sibling fn_800D1EDC's `CapCreate(p)` inline verbatim; symcheck differs only in library names (snprintf vs fn_80290D04), like the sibling.
  - fn_800D4864 (rK, 19 -> 0): zero Color argument built by `static inline Color zc() { Color z; *(u32*)&z = 0; return z; }` called inside the argument list, `fn_80080940(zc(), zc(), k1a, k1b)`; the 0 is then built after the constant copies, in r0.
  - fn_80150B20 (rM, 3 -> 0): the colour is a by-value struct parameter, `void fn_80150B20(Win* w, Color c) { w->col = c; c.a = 255; }` (the rL caller's prototype gave it away); the store into the by-value copy is kept.
  - fn_8015BD44 (rM, 15 -> 0): the exact sibling fn_801540B0's spelling `int cost = (u16)fn_801676D8((s8)x, (s8)y);`. The file keeps the equiv's `extern u32 fn_801676D8(int,int)`; the real `u16` return type reshuffles colours (55 words).
- Near misses (real words; drafts in build/tmp/m25/m25?-o/, local only): 2: fn_80109DF8 (dead s16 loop counter's addi scheduled before the pointer step), fn_800A4D88; 3: fn_800EB988, fn_800A0998; 5: fn_8008A868, fn_8022333C (was 14), fn_800A84A4 (was 8), fn_800FA264, fn_8027ECA4; 7: fn_80246ADC, fn_80246E68 (stored-constants wall); 8: fn_801729C0, fn_8008D414, fn_800F15AC; 9: fn_801CC5CC; 13: fn_802133F8.
- Lessons:
  - `#pragma opt_lifetimes off` at file top plus one variable assigned through if/else (not a ternary or cast, which make their own temps) fixes "a short-lived value takes the wrong free callee-saved register".
  - Check callers' prototypes for by-value struct parameters; a store into a by-value parameter is kept and changes the schedule.
  - Building a struct argument with a tiny inline inside the argument list changes when it is built and which register it gets.
  - Declare every local separately from its assignment and hill both blocks; C89 hoisting fixed rows that earlier only got combined declaration orders.
  - A block-scoped counter per loop can be right where a shared function-level one is wrong (reverse of m24's finding).
  - CW propagates every alias of a parameter (copy, inline parameter, `&e->x` at offset 0, `(u32)` cast, `register`).
  - Check hill results for use-before-assign orders (`e = Evs(hh); hh = h;`) that produce the same code.

## Round m26 (three Opus agents, first third of the 107 worthwhile rows)

- 36 open rows (listed 11-25 words, untouched since m20, tried at most twice). 5 exact, no stale rows:
  - fn_80010E38 (rA, 22 -> 0): inside the loop take the light pointer by index (`l = &s->body.lights[i];`) instead of walking it with `l++`.
  - fn_800665E4 (rO, 25 -> 0): store positions by index (`pos[n].x = ..; pos[n].y = ..; n++;`) instead of through a walking `Pt* p`.
  - fn_80223580 (rI, 21 -> 0): equiv body unchanged, all locals moved to the top C89-style, declaration hill found `held, cur, nw0, trig, nw, n, m` in 4 evals.
  - fn_8009EEEC + fn_8009F1A8 (rD, 22 -> 0 each, one file): in clearUnitFlags load the unit array into a local before the loop (`base = lbl_804CB810;`) and pick the unit with if/else into a function-level `u` (`u8 n = i; if (n) u = base + (n - 1) * 0x3F0; else u = 0;`), declared `mask, i, base, u`. An independent exact form (agent m26b): the loop written in place with `mask, i, u` as function-level locals (all 6 orders match).
- Near misses (real words; drafts in build/tmp/m26/m26?-o/, local only): fn_800FF170 3 (was 24), fn_802173C0 6, fn_801241F4 6, fn_801CD05C 7 (listed 11 used a wrong fn_8001ECE4 prototype), fn_800A6978 7 (was 24), fn_801CCE8C 8, fn_801CCCBC 8, fn_8005586C 9 (was 16), fn_8010830C 10 (was 20), fn_8022C080 10 (was 21), fn_801CE174 10, fn_800DE1B8 11, fn_8005840C 12, fn_800659B0 13, fn_80266024 14 (was 20), fn_80054378 14.
- Lessons:
  - Replace a walking pointer with an index form first on any row with a swapped pointer/counter register (two rows solved).
  - The if/else lever also fixes which volatile register a value gets, without `opt_lifetimes off` (fn_8009EEEC); a ternary, an inline helper or `u = 0; if (n) u = ...` did not.
  - With declarations split from assignments, volatile registers follow declaration order (earlier declared gets the lower register).
  - Copy an exact sibling's helpers: grep the region's exact files for the same globals or struct offsets first (fn_800A6978 24 -> 7 with fn_800A6DE4's helpers; fn_8022C080 is the exact siblings fn_8022B9B8/fn_8022BA6C inlined).
  - The reverse of body-as-inline can help: flatten an inline that holds all of a loop's locals.
  - An inline taking the struct and loading a string field into its own local can fix colours a `const char*` parameter can't.
  - Stored constants colour by first appearance in the source (fn_802828B4).
  - If a hill doesn't move in its first ~50 evals, change the code's shape instead (fn_800581F4, fn_8000D228, fn_800437D0 ignore declaration order).
  - A self-recursive function can inline itself with `inline` + `#pragma inline_depth(N)` outside push/pop and one address reference; inline helpers use up that depth.
- Tooling: tools/perm/lib.origfn and dis.py miss functions whose asm is only in build/RFEE01/asm/tu/** or src/tu opword comments; m26 agents' dis.py/dis3.py (build/tmp/m26/) search there.

## Round m27 (three Opus agents, second third of the worthwhile rows)

- 36 open rows (listed 25-40 words). 5 exact, 2 stale (fn_801E8680 since m13, fn_80224554 since m13; EQUIVALENT.tsv still lists them):
  - fn_8027D14C (rN, 25 -> 0): m12's "statement temporaries take r31" wall was really named locals (k, m, m4, v, w) the original never had. Writing the stores as expressions with sibling fn_8027C5CC's spellings (`*(s16*)(fn_80272A8C() + *(s16*)(fn_80272A8C()+0xC)*2) = cntm1();`, `fn_802732FC(fn_80272B84(), (int)fn_80272D58(), 0);`) gave 23 -> 4; a declaration order and `i = 0; off = 0;` closed it.
  - fn_80009A2C (rA, 36 -> 0) and sibling fn_80009454 (rA, 17 -> 0): the fn_8000987C colour loop written in place with function-level locals (36 -> 8), then an explicit byte offset stepped beside the counter, `for (i = 0, off = 0; ...; i++, off += 4)` reading `*(GActor**)((u8*)l2->items + off)`.
  - fn_802243D0 (rI, 26 -> 0): copy of exact sibling fn_801E84FC.cpp (same cursor-draw body) with field offsets +4 and v18 taking the draw context; first compile.
  - fn_80066E24 (rO, 28 -> 0): direction table read by index (`DirX(tbl[i])`) instead of a walking `u32* p`, plus the trap search as the sibling Find's index loop with reversed parameters and tx/ty assigned in the argument list: `FindR(l, 0xB, ty = (s8)(y+dy), tx = (s8)(x+dx))`. Each lever alone gave 17 and 11.
- Near misses (real words; drafts in build/tmp/m27/m27?-o/, local only): fn_80088948 2 (was 40; findName by index + middle free layer as `static inline fr1_s(Proc*)`), fn_8022A8A0 4 (was 10), fn_8014D808 9 (was 26), fn_801A32BC 10 (was 27), fn_80225650 11 (was 34), fn_800A75E8 13 (was 28), fn_80087F78 13 (sibling, was 47), fn_8015B1C4 16 (was 39), fn_801E9CA8 16 (was 29), fn_800C5EA4 16 (was 26), fn_8021BB04 17 (was 86), fn_80105BBC 22 (was 32). fn_8000AB6C family: 22 with sibling search inlines, still worse than m12's 19.
- Lessons:
  - An apparent "temporaries wall" can come from named locals the original computed as expressions; try the exact sibling's expression spelling first.
  - When a loop counter and its strength-reduced offset are swapped, make the offset an explicit variable (the reverse of m26's index lever).
  - A self-inlined helper whose loop counter lands in the wrong volatile register can be fixed by writing its body in place with function-level locals.
  - Two inlined copies the original colours differently each need their own inline copy with the parameter turned into a local.
  - Re-check old near misses that used only one lever, adding the index form.
  - Byte loads don't move across volatile FIFO stores; an interleaved order in the original must be written in source.
  - If a declaration hill hasn't moved after ~50 evals it won't; change the shape (fn_8015F07C 1298 evals, fn_8011A804 576 orders).
  - fn_8012FA44's cameras are file statics: check with `--symbol-map` (`{"...bss.0": "lbl_804133B8"}`), not extern objects.
- Tooling: hill2.py scored a compile error at start as 9999 and kept running; build/tmp/m27/m27c-o/hill2.py stops when the start score fails.
- Stale tu marker: fn_802241A8 is exact in fn_801E82D4.cpp but src/tu still says "not matching yet". Real library names: fn_80295CF0 = sqrt, fn_80291480 = strstr, fn_80290DDC = sprintf.
- Siblings worth a try next: fn_80085FC4 and fn_80087F78 (fn_80088948's levers), fn_8014D9FC (FlakeInit inline from fn_8014D808).

## Round m28 (three Opus agents, last third of the worthwhile rows; end of the planned series)

- 35 remaining pool rows (listed 40-303 words) plus m27 near misses/siblings. 3 exact, no stale rows:
  - fn_80088948 (rJ, 2 -> 0): m27's draft (findName by index, `fr1_s` static) plus an offset beside the counter in findName: `for (i = 0, off = 0; i < 0x100; i++, off += sizeof(Proc)) q = (Proc*)((u8*)lbl_803D9A58 + off);` (`off += ..., i++` gives 2 again; walking `q++` gives 44).
  - fn_801AF2A8 (rF, listed 53; m4's n3 draft was already 12): keep `u8 r` at function level but widen the call value where assigned, `r = (int)fn_800634D8(gb2);` (`& 0xFF` and `(u8)(u32)` also match): clrlwi at the definition, mr at the use.
  - fn_801A4744 (rF, real 85 -> 0): declaration hill (81 -> 19); frame like fn_801A4068's `Bg` (`C4 c; C4 t;`, u32 copy, call through a pointer-taking cast of fn_801BC88C, scale as inline parameter) -> 12; model colour as `C4 m; C4 n;` with fields stored one by one plus a u32 copy -> 2; x102/x103 as s8 fields passed without `(s8)` casts -> 0.
- Near misses (real words; drafts in build/tmp/m28/m28?-o/, local only): fn_8022A8A0 4, fn_8014D9FC 9 (was 35), fn_80222E34 11 (was 45), fn_80087F78 13, fn_80158354 15 (was 51), fn_8024044C 17 (was 43), fn_801586C8 32 (was 40), fn_800D5DC4 34 (was 45), fn_80020F04 41, fn_80085FC4 56, fn_8026E9DC 59 (was 77), fn_80138FF8 94 (was 194), fn_801805E0 100 (was 120).
- Lessons:
  - Old rounds' results.tsv can hold drafts much better than the listed equiv file (fn_801AF2A8: m4's 12-word draft). Check them first.
  - u8 local fed by a call returning u8, with clrlwi at definition and mr at use: keep the u8 local, cast the call value.
  - Large "regs" rotations can fall to a plain declaration hill (fn_801A4744 85 -> 19, fn_80138FF8 194 -> 94).
  - Two 4-byte struct locals take stack slots in declaration order when their fields are stored one by one; with an aggregate initialiser the order doesn't move.
  - Constant stores to different globals: the scheduler reorders the stores but the constants load in source order (fn_8014D9FC), which may help other stored-constants rows.
  - Two loops sharing counter/offset variables: give each loop its own (fn_80222E34 45 -> 24). Do the structural change first, then the hill; the flat hill plateaus higher.
  - Float registers follow statement order, never declaration order (fn_80158354). Reading a float field into a local before a multiply fixes the int-to-float constant's load order. Reordering a sum's terms fixes volatile load registers (fn_8026E9DC).
  - Unsolved pattern in many big rows (fn_801586C8, fn_80136E74, fn_8004564C, fn_802818FC, fn_80275FD4, mirror in fn_80085FC4/fn_80087F78): the original ranks one value lowest, ours puts it in r31 and everything shifts by one. No known lever moves it; it probably needs a source shape that creates the value later.
- Note: fn_80131DE4's equiv header claims 65 words but it really scores 265 against the current headers.
