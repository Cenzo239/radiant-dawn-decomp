# Round 23 (agent r23wf): the lbl_8038C1C0 help-bar constructor puzzle (not solved)

Targets: rI fn_80205E50, fn_801F17C4, fn_802020AC, fn_8020B408, fn_80213B4C, fn_8021F5C4, fn_80221050,
fn_8022516C, fn_8022DFE0; rF fn_801D2744; rS fn_80241BF0. The same block also sits in rA fn_80023360,
fn_80023E2C, fn_8002421C and the rC2 fn_8005B508 family (scan of all 270 lbl_8038CB1C sites:
build/tmp/r23wf/scan.txt). No new exact function. Test bed: fn_801F17C4 (build/tmp/r23wf/a3.cpp, a
self-contained copy with a local `wfL` and the WF struct).

## What the original does

Original colours: zero r11, base vtable r5, -1 r5 (defined after `stw r5,0(r3)`), 0x190 r0, derived
vtable r4, r12 unused, `addi r4` (derived vtable low half) scheduled before `li r0,1` (a50).
Ours: zero r12, -1 r0, 0x190 r11 (in the long-lived chain r12..r5), `li r0,1` before `addi r4`.

## Levers that do change the colouring (none gives 0)

1. **x0 as a separate value.** `wfL(&b->w, 5, 400, ...)` gives exactly the original layout (zero r11,
   base vtable r5, 0x190 r0, r12 unused) plus x0 in r5 and -1 in r6. So the original behaves as if
   x0 had its own pre-RA value that then shared the zero register (a coalesced copy?). x0 equal to
   any other constant (0x260, 0x78, 0x10, 0xff, -1) gives the bad pattern.
2. **Any extra distinct constant** in the block (rc = 7, ix0 = 7, a40 = 7, even a64 = 7 at the end)
   gives -1 r5 / 0x190 r0 (zero then in r12). `u16 id` (0xFFFF built with `lis 1; subi`) gives the
   good pattern too, but two instructions. An extra value live through the block from outside
   (global loaded before `if (b)`, stored after) does not.
3. **Derived vtable store position.** Explicit `b->w.vt = lbl_8038C1C0` before `a50 = 1` (any
   position 0..4 of the derived body) gives the right -1/0x190/zero colours; positions 5..12 (the
   original's store order puts it after a5e) are bad. Best: after a4c, 9 words left (base vtable r6
   instead of r5, `li -1`/`li 0x190` order, and the store order of vt/a50/a5a/a5e). Removing a50 or
   a5a/a5e does not help a late store; only having the store early does.
4. **Real C++ classes with compiler-generated vtables** (`__vt__2WF`/`__vt__2WB` mapped with a
   .symbols.json to lbl_8038CB1C/lbl_8038C1C0, class `operator new` calling fn_80079150, a polymorphic
   empty root `Obj` so the vptr sits at 0 and an `RCo` base holding rc so rc is stored first):
   `WB : WF` gives the good colours (13 words) because CW stores the derived vptr right after the base
   constructor, before WB's members (same as lever 3, position 0). Anything that moves the vptr store
   after a5e (intermediate class WM holding a40..a5e, multiple inheritance `WB : WF, EX`) is bad
   again (25). Member initialiser lists and member sub-objects don't move the vptr store (CW sets the
   vptr before members). Note: a non-polymorphic base with members puts the vptr at the END of the
   class in CW (r1.cpp), so the root must be an empty polymorphic class.

## Tried without effect (still the 25-word pattern)

- x0 from: s16/int locals, a newB parameter, `register`, address-taken local, `x1 - ix1`, `x0 * fl`,
  `(s16)w->rc`, reading ix0, u16/u8/f32/long long parameter type, `const s16&` (puts x0 in memory),
  `R(x0)`/`Ri(x0)`/`Z()` accessor inlines, rc/ix0/a1a.. assigned from x0.
- -1 as: inline parameter (first or last), `(u16)0xffff`, `(s16)0xFFFF`, `-1U`, `(unsigned short)-1`,
  local `s16 m`, `M1()` accessor, enum, `static const` member; u16 id field changes the code.
- Constructor shapes: (x, y, w, h) with x1 = x + w, y1 = y + h; rect struct by value/reference
  (goes to memory); split into wfHead/wfRect/wfId inlines; `(WF*)b`, `WF* w = &b->w`; `if (b)`,
  assignment in the condition; derived init inline taking the vtable as a parameter; vtable address
  in a local (before wfL, before the if, before newB) or from `&struct`, `void*[]`, `const u8[]`,
  `+ 0`, `&lbl[0]`; members a40..a4c or a60/a64 as sub-structs with init inlines; types of a50
  (bool, s8, true, `*(u8*)&`, byte offset); dead duplicate stores (all removed by DSE, including a
  dead early derived vtable store, which also removes its lis/addi).
- Base statement order: all 24 orders of rc/vt/id/x0 times derived vtable position 0..7 (192 cells,
  build/tmp/r23wf/gv1.py): best 9 (position 4), every position >= 5 bad.
- Outer code: cutting everything after newB doesn't change the block's colours.
- Pragmas: opt_propagation, opt_common_subs, opt_lifetimes, opt_loop_invariants,
  opt_strength_reduction off, optimization_level 3 (no change); opt_dead_assignments off, peephole
  off, scheduling off (different, worse). Flags -inline deferred/all, -opt nocse, -proc 750,
  -O3/-O2/-O4,s (worse). Compilers GC/3.0a3..3.0a5 same 25 words; Wii 1.0/1.1/0x4201_127 28.
- Matched comparison: fn_8022052C (wfInit with x0 = 0, derived vtable stored right after wfInit)
  has -1 in r0, i.e. the "bad" pattern is normal for x0 = 0; the help-bar class is the odd one.

## Best guess for the next attempt

The original needs one more pre-allocation value in the block that disappears afterwards (most likely
a register copy that the allocator coalesces, e.g. x0 passed through something the optimiser can't
propagate), or the derived vtable address computed early with the store still after a5e. Ideas not
tried: a by-value class argument (struct with a constructor) for the rectangle, x0/y0 from a
default-argument constructor of a point class, a `this`-adjusting cast through a virtual base,
the help-bar constructor as a template.

## Solved (ctor-puzzle branch)

The 0x40..0x4F words are a string object with short-string storage (destructor fn_801D5D54 tests bit 31 of
0x40 and frees 0x48; fn_801D5BB0 reads the short length from the byte at 0x40), zeroed by a loop in its
constructor, and it sits in an intermediate class whose own vtable is dead. With real C++ classes
(src/game/helpbar.h: HbObj -> HbRc -> HbWidget -> HbTextWidget{HbStr s} -> HbHelpBar) and a .symbols.json
mapping __vt__8HbWidget/__vt__9HbHelpBar to lbl_8038CB1C/lbl_8038C1C0, 30 of the 31 sites are exact.
Open: rS fn_80241BF0 (18 words, r30/r31 swap, wip/fn_80241BF0_hb.cpp).
