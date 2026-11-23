# Region E: 0x800E5DE4..0x801059EC

389 functions match byte for byte (`python3 -I tools/check_func.py <file>` prints MATCH for every file).

| File | Functions | Range |
|---|---|---|
| `fn_800E5DE4.c` | 53 | 800E5DE4..800E7CC4 (contiguous) |
| `fn_800E7E70.c` | 46 | 800E7E70..800E9DA4 (skips 800E8F10 and 800E9DF0+) |
| `fn_800EA3DC.c` | 27 | 800EA3DC..800EDAB4 (small functions only, with gaps) |
| `fn_800EDB70.c` | 24 | 800EDB70..800EE78C (skips 800EE324) |
| `fn_800EF6F0.c` | 27 | 800EF6F0..800F1820 (small functions only, with gaps) |
| `fn_800F1F88.cpp` | 1 | 800F1F88 (C++ because of a virtual call) |
| `fn_800F3360.c` | 71 | 800F3360..800FC56C (small and mid-size functions, with gaps) |
| `fn_800FCA40.c` | 20 | 800FCA40..800FD7D8 (with gaps) |
| `fn_80105154.c` | 7 | 80105154..801059B0 (with gaps) |
| `fn_800EAEA4.c` | 3 | 800EA224, 800EAEA4, 800EC46C |
| `fn_800ECCCC.c` | 4 | 800ECD90, 800ED918, 800EE798, 800EFDB0 |
| `fn_800F080C.c` | 4 | 800F080C, 800F14B4, 800F173C, 800F18BC |
| `fn_800F130C.c` | 1 | 800F130C (plus a local static copy of 800F1490, see below) |
| `fn_800F7890.cpp` | 1 | 800F7A98 |
| `fn_800FC5D8.c` | 4 | 800FCBFC, 800FD108, 800FD368, 800FD51C |
| `fn_800FD7F0.cpp` | 11 | 800FD7F0..800FF8C0, 80100384 (movement process) |
| `fn_801006F0.c` | 10 | 801006F0..801018BC (with gaps) |
| `fn_80101E38.cpp` | 6 | 80101E38, 80102438, 8010258C, 80102CD8, 80102D70, 8010316C |
| `fn_801021D8.c` | 3 | 801021D8, 80102E10, 801044A8 |
| `fn_80103638.c` | 24 | 80103304..801046B0 (factories), 80105704..80105928 |
| `fn_80104248.c` | 7 | 80104248, 80104744..80104948, 801051D8..8010536C |
| `fn_80104ABC.cpp` | 3 | 80104ABC, 80104F18, 801050A8 |

Shared headers: `types.h` (basic types and core structs), `mapunit.h` (the `MapUnit` struct, round 2) and `evproc.h` (externs, inline helpers, region structs and prototypes for every function defined here).

The full list of matched functions is the `OK` output of the checker for each file. Every function from 800E5DE4 to 800E7CC4 and from 800E7E70 to 800E9DA4 is matched except the ones listed below.

## Not matched / wip
- `wip/fn_800EB410.c`: 3 of 39 words differ. The original emits `addi r31,r31,lbl@l; addi r3,r31,0`. The 14 class descriptors at `lbl_80384300..` are separate statics in the same TU, and MWCC addresses them all off one base register. I couldn't reproduce this with externs.
- `wip/fn_800F7BF4.c`: 5 of 68 words, a register swap only.
- `wip/fn_800F8294.c`: instruction order after the `fn_801142F0` call (the `frsp` copy).
- `wip/fn_800FAE08.c`: 800FAE08 (13 of 36), 800FAFF0 (4 of 39), and 800FC5AC (all words match, but the original has a dead `blr` after the tail call).
- `wip/fn_800FCD10.c`: 800FCD10 and 800FD05C (FP registers). 800FCDD8 and 800FCEE4 in that file are matched in `fn_800FCD10.cpp`.
- Skipped because they're large: 800E8F10, 800E9DF0, 800EA224, 800EA408, 800EA894, 800EAD10, 800EAEA4, 800EB048, 800EB274, 800EB4AC.. and most functions over 0xC0 bytes after 800EB000.

- `wip/round6_near_misses.txt`: 27 hand-written functions from round 6 with the checker result for each. The structs and externs are in the source file named on each block. Closest: 800FDDE8, 800EF0D8, 800EAD10 (2 words each), 80102300 (3), 80101568 (4), 800ED7E4 (8).
- `wip/fn_80102928.c`: 2 of 209 words differ (`ori` and `mr` swapped after the fn_800F760C call).

## Round 6 caveats
- `fn_80104ABC.cpp` uses file-static `u8` arrays to get the original's `addi rN, rBase, 0x0`. They stand in for class descriptors in .data at lbl_80385050. The checker sees `...bss.0` and compares offsets only. The base was confirmed by reading the asm. These statics are not the real data.
- `fn_800F130C.c` defines a static `fn_800F1490` because the deepest inlined level has to call a helper with that name. The real global definition stays in `fn_800EF6F0.c`. It returns `int` here and `u8` there.
- Some externs have a different prototype in different files, because the prototype changes the code: `fn_80103374`, `fn_800EE61C` and `fn_800E59CC` take pointers where the source may pass by value, and `fn_800E3810` and others vary in their parameter types.
- Some locals exist only for register or scheduling reasons and say nothing about the source: the separate `ox, x, oy, y, z` in 8010431C, `j2` in 800F18BC, and block-level `a`/`b` in 800FD51C.

## Colour split (solved in round 8)
`fn_800F201C`, `fn_80175E7C` and `fn_801125B4` return a `GXColor` by value, in r3. Declaring them that way in a C++ file produces the odd split with no extra code: `q->c = fn_800F201C(i);`. A prototype returning `u32` can't reproduce it. Only 80101EEC and 80102030 are still open, for a different reason (see round 8 below).

## Round 8 (32 functions, 17,432 bytes)
| File | Functions |
|---|---|
| `fn_80100760.cpp` | 80100760, 801018F8, 80101B80, 80102714, 80102858, 80103234, 80103A20 |
| `fn_800F5090.cpp` | 800F5090 (0x120C bytes) |
| `fn_800FF998.cpp`, `fn_800FFFDC.cpp`, `fn_800FFEB8.cpp` | movement process |
| `fn_80104C2C.cpp` | 80104C2C (file statics, same caveat as `fn_80104ABC.cpp`) |
| `fn_801053EC.cpp` | 801053EC, 80105558 |
| `fn_80103D80.cpp`, `fn_80100C70.cpp`, `fn_8010403C.cpp` | 80103D80, 80100C70, 80102300 |
| `fn_800FCD10.cpp` | 800FCDD8, 800FCEE4 |
| `fn_800F7890_b.cpp`, `fn_800F97A4.cpp`, `fn_800FC5D8_b.cpp`, `fn_800F634C.cpp` | 800F7890, 800F97A4, 800FC5D8, 800F634C |
| `fn_800ECCCC_c.cpp`, `fn_800ED7E4.cpp`, `fn_800ED24C.cpp`, `fn_800EBB74.cpp`, `fn_800EE324.cpp` | 800ECCCC, 800ED7E4, 800ED24C, 800EBB74, 800EE324 |
| `fn_800EAD10.c`, `fn_800EC0C8.c`, `fn_800E7DDC.c` | 800EAD10, 800EB274, 800EC0C8, 800E7DDC |

`wip/round6_near_misses.txt` still lists the functions above: its entries for them are out of date. The wips `fn_800E7DDC.c` and `fn_800F634C.c` were solved and removed.

Caveats on round 8 matches (they match, but may not be the original source):
- Files with a string pool define a dummy function (`pool_7d50`, `pool_7ba4`, `pool_707c`, `pool_72a0`) that exists only to place the strings at the right offsets. It isn't in symbols.txt and must not be linked as real code.
- `fn_800F7890_b.cpp`: the `VW` word-copy struct stands in for two `Vec` copies in reversed stack slots.
- `fn_800FFEB8.cpp`: `if (z == 0) z = e->vC;` exists only to produce a dead `cmpwi`.
- `fn_800FFFDC.cpp`, `fn_800ED24C.cpp`, `fn_800EE324.cpp`: helpers `H2`, `Set2` and the switch written in place of `DX`/`DY` set stack slots and register colouring, so they say little about the original structure.
- `fn_80100760.cpp`: `((s8)y << 6) + (s8)x` only sets the `add` operand order.
- `fn_8010403C.cpp` holds only 80102300, despite its name (8010403C and 8010436C didn't match).
- Prototypes differ between files because the prototype changes the code, for example `fn_801181E8` takes `s8` in `fn_800FC5D8_b.cpp` and `int` elsewhere, and `fn_802549C4` takes `const Vec&` here and `Vec` in older files.

Near misses, closest first (all registers or stack slots):
- `wip/fn_80101EEC.cpp`: 80101EEC and 80102030, 1 word each. The original has `li r0,0x10; srawi r28,r0,1`. `Half(const int&)` with a literal gets everything else right but loads the constant with `lwz @sda21`. About 70 other spellings fold to `li r28,8` or give `srawi r28,r28,1`. 800FD65C has the same `li; srawi` with 0xC.
- `wip/fn_80102928.c`: 2 of 209, and 800EF0D8: 2 of 97 (`ori` and `mr` swapped). About 18 more forms tried, no change.
- `wip/fn_800EB988.cpp`: 800EB988 3 of 123 (`n` in the wrong register), 800EBE80 8 of 146 (Vec temp and copy swapped on the stack).
- `wip/fn_800EB048.c`: 6 of 139. `wip/fn_800F002C.cpp`: 7 of 504.
- `wip/fn_800F491C.cpp`: 800F4B94 7 of 157, 800F4E08 15 of 160, 800F491C 17 of 158. `wip/fn_800F6AEC.cpp`: 48 of 585, same layout. All four expand the same `SetAnim` inline, so solving its colouring should unlock about 1,060 words.
- 8010403C (14 of 104), 8010436C (11 of 79), 800FF170 (about 25 of 172), 80101568 (4 of 80), 800F1E9C (3 of 59), 80103410 (13 of 41), 800F15AC, 800FC7D0.
- 800F0CBC is the recursive `fn_800F130C` inline written out twice, with the `Lookup` from 800F002C. Not attempted beyond reading it.

## Resume point (round 8)
76 functions, about 56.6 KB left. Try a string-pool rewrite first on any function with `lis/addi base; addi off`: add a `pool_XXXX` dummy built from the rodata, with `#pragma pool_strings on`, and use real literals. Largest untried: 800F98E4 (FP heavy), 800FDFFC, 800EC5A8, 800F0CBC, 800F8C2C, 800FE7EC, 800F2B04, 800F22E8, 800EF25C, 800EA894, 800E9DF0, 800EA408, 800E8F10, 800EB590. The list under the old resume point below is out of date for anything in the round 8 table.

## Round 11 (33 functions, 30,400 bytes)
All hand-written from the asm into new files, one per function except `fn_800F280C.cpp`, which holds 800F280C and 800F3050. Files: `fn_800E8F10.cpp`, `fn_800E9DF0.cpp`, `fn_800EA408.cpp`, `fn_800EA894.cpp`, `fn_800EB590.cpp`, `fn_800EBE80.cpp`, `fn_800EC5A8.cpp`, `fn_800ECE7C.cpp`, `fn_800ED100.cpp`, `fn_800EE910.cpp`, `fn_800EEB3C.cpp`, `fn_800EEEC4.cpp`, `fn_800EF25C.cpp`, `fn_800EF6F4.cpp`, `fn_800F1E9C.cpp`, `fn_800F22E8.cpp`, `fn_800F280C.cpp`, `fn_800F2B04.cpp`, `fn_800F33A4.cpp`, `fn_800F3B90.cpp`, `fn_800F8044.cpp`, `fn_800F8294.cpp`, `fn_800F8430.cpp`, `fn_800F8880.cpp`, `fn_800F8C2C.cpp`, `fn_800F93E4.cpp`, `fn_800FA9C0.cpp`, `fn_800FB9D0.cpp`, `fn_800FC270.cpp`, `fn_800FDFFC.cpp`, `fn_800FE7EC.cpp`, `fn_800FF420.cpp`.

Older wips `wip/fn_800F8294.c` and the 800EBE80 half of `wip/fn_800EB988.cpp` are now out of date.

Caveats (they match, but may not be the original source):
- `struct V : Vec { V(const Vec&) }`, `W(f32, f32, f32)` and `Mk` stand in for whatever made a float-copied temporary (probably a real Vec class with a member-by-member copy). Used in 800E8F10, 800EA408, 800EA894, 800EB590, 800EBE80, 800FE7EC.
- `W3 { W2 ab; u32 c; }` casts stand in for Vec word copies in 800F33A4, 800F8044, 800FE7EC, 800FF420. Splitting the declaration from the copy exists only to set stack slots.
- `fn_800F8044.cpp` declares `fn_800076E8` with an explicit out pointer instead of a Vec return, to control the temp's slot. Its `GP` inline is a copy of 800F7790, which the original probably auto-inlined in the same TU; 800F93E4 does the same with 800F3B90 and 800F7724.
- Extra locals that only set registers: `f2`/`fl` in 800EE910 and 800EEEC4, `d`/`r` in 800E9DF0, `m2`/`i` in 800EF6F4, `u16 a` in 800F1E9C, the `const` cast in 800F93E4.
- 800E9DF0 and 800EA894 load the colour template from +0 of a compiler pool, the original from +4 of a pool whose first entry belongs to another function. Values match, and the checker compares values.
- Files with `pool_72a0`/`pool_707c` dummies: same rule as round 8, not real code. `fn_800FDFFC.cpp`, `fn_800FE7EC.cpp` and `fn_800FF420.cpp` address +0x48/+0x4C as `f5C[-5]`/`f5C[-4]`, which is only a shorthand.
- `fn_800EF0D8` is declared floats first in `fn_800EF25C.cpp`, and `fn_8024F50C` takes the `s8` slot in `fn_800FE7EC.cpp`. Other files may declare them differently.
- 800F8C2C leaves `c` unset for an unknown class, as the asm does.

New wips: `fn_800FBC90.cpp` (2 of 88), `fn_800FA264.cpp` (5 of 203), `fn_800F199C.cpp` and `fn_800F1C30.cpp` (register rotations only), `fn_800FC09C.cpp`, `fn_800FA590.cpp`.

Still open: the SetAnim family (800F491C, 800F4B94, 800F4E08, 800F6AEC, and now 800FBDF0 with the same inline; about 40 more spellings tried without improvement), 800F002C (first Lookup only: the original has n r28 and i r31, and i shares a web with the return value), 800FB398 and 800FA590 (need pooled file statics at `lbl_80367A58`), 800F98E4, 800F0CBC, 800F201C, 800F35AC, 800FC7D0, 800FF170, 800FD65C, 800FDDE8, 800EB048, 800EB410, 800EB988, 800EF0D8, 80101EEC, 80102030, 80102928, 8010403C, 8010436C, 801010F0, 80101568, 80103410.

## Subsystems (guessed names)
- **Battle/map event effect processes** (`EvProc`, 800E5DE4..800E9DA4). Each process is created by a factory `fn(parent, cb)`: it calls `fn_80081194(classDesc, parent)` to allocate, then `fn_800E5DE4(p, cb, effectName)` (a guessed `EvProc::Init`). It tracks two participants (`h1`/`h2`, handles to units whose `+0x3F0` is the map actor) and an effect name. The names are EID_* strings in the pool at `lbl_8036707C`, for example "EID_HEALINGHAND", "EID_BLISS", "EID_CURE", "EID_SHOOTER", "SFX_BMP_MISS1". Staff and skill effects: heal, bliss, sorrow, brave, boon, blessing, evil-eye, lava, shooter/onager.
  - `fn_800E3A10(name, proc)` / `fn_800E3810(name, proc)` create an **EvCmd** (an effect instance). Its `ctl` (+0x30) has callbacks `onUpdate` (+0x98) and `onEvent` (+0x9C). `fn_800E46C4(cmd, n)` tests "event n fired" and `fn_800E28E4(cmd)` is the default event handler.
  - The `EvProc_CreateAnim` inline pattern (name from `sub->str44` or `p->name`, then the `fn_800E4904` x2 / `fn_800E5BC0` setup, then `flags |= 0x400`) appears in about 12 functions.
  - Finish callback: `if (p->cb && !p->doneCb) { p->doneCb = 1; p->cb(p); }`.
- **Battle sequence process** (`BtlProc`, 800EC204..800EDAB4): state at 0x40..0x48, 3 participants iterated with `fn_801D0784(seq, i)`.
- **Floating text/number popups** (`MsgProc`, 800EDB70..800EE78C): uses the font `lbl_80367458`, draws with `fn_8007E4E4`/`fn_80080430`, and does bounce/fade easing with `fn_8001EBC8` / `fn_8001EF30` (start, end, duration, t). Factories take `(Vec pos, parent)` and query the width through `fn_800893E4(cls, fn_800EDB98, &w)`.
- **HP gauge windows** (`FadeProc` / `GaugeProc`, 800EF6F0..800EFFE8): `fn_800EFB6C(h1, h2, parent, mode)` opens them, and `fn_80083B84(cls)` finds the live instance of a process class.
- **Data tables** (800F08DC..800F0C68): weapon-type code strings ("sw","sp","ja","ax",... in `lbl_803674B4`), and a name lookup table read with `fn_80109A2C` (a reader that skips headers) from `lbl_804CB7C0`. The path builders `sprintf(lbl_803E8F98, fmt, ...)` (`fn_80290DDC` = sprintf) build model/animation file names from a character's PID string.

Engine helpers seen often: `fn_80083B78` = process end/kill, `fn_80083DC4(proc, state)` = set state, `fn_80081A90` = delete process, `fn_80081050`/`fn_80081194` = create a process (two variants), `fn_8012FCD0` = camera/battle-view object (f32 at +0x68 and +0x8).

- **Map unit sprites** (`MapUnit`, 800F3360..800FC56C, one TU; its string pool starts at `lbl_80367BA4`, its first user is 800F35AC): model instance at +0x28, map position +0x04, offset +0x10, facing angle in deg*64 at +0xC4, u64 state flags at +0x108. 800F43F0 picks the character data (fallback "AID_DUMMY") and 800F0CBC loads an animation from it. 800F3F38/800F3FE4 convert between a direction bitmask (1,2,4,8) and the angle. 800F3900/800FB824/800FB904 are a fixed pool of timed nodes at `lbl_804CB748` (next/prev list plus a free stack).
- **Screen rectangles** (800F7D30..800F8030): a shrinking or growing box in `lbl_803E8FD8`/`lbl_803E8FE4`, drawn through a scissor.
- **Map-unit effect processes** (`UProc`, 800FCA40..800FD7D8, a new TU; string pool `lbl_80367D50`): small processes with a `MapUnit*` at +0x30 that fade its colour, shake it through `offX`, bounce it, or swap its animation. Fields after +0x34 differ per class, hence the `PSlot` union.
- **Slot table** (`SlotTbl`, 80105158..801053DC): a count and 0x28-byte entries; a slot is free when its first word is NULL.

## Resume point
Round 6 stopped with 108 functions (about 74 KB) left in this region. Next, in order:
1. The colour split above: solving it unlocks about 10 functions at once.
2. Near misses in `wip/round6_near_misses.txt` and `wip/fn_80102928.c`. 800FFFDC (register shift by one) and 800FF998 (float register order) are large.
3. Large functions not attempted: 800E8F10, 800E9DF0, 800EA408, 800EA894, 800EB048, 800EB590, 800EB988, 800EBB74, 800EBE80, 800EC5A8, 800ECE7C, 800ED24C, 800ED4AC, 800EE910, 800EEB3C, 800EEEC4, 800EF25C, 800EF6F4, 800F002C, 800F0CBC, 800F199C, 800F1C30, 800F201C, 800F22E8, 800F280C, 800F2B04, 800F3050, 800F33A4, 800F35AC, 800F3B90, 800F491C, 800F4B94, 800F4E08, 800F5090, 800F6AEC, 800F8044, 800F8430, 800F8880, 800F8C2C, 800F93E4, 800F98E4, 800FA264, 800FA590, 800FA9C0, 800FB398, 800FB9D0, 800FBC90, 800FBDF0, 800FC09C, 800FC270, 800FDFFC, 800FE7EC, 800FF420, 80100C70, 80102928, 80103A20, 80103D80, 8010403C, 80104C2C, 801053EC, 80105558.
4. Older wips listed above. 800EB410 can probably use the file-static trick from `fn_80104ABC.cpp`.

## Recurring struct layouts
- `Handle { UnitObj* obj; ...; s16 unk6 @6; s16 unkE @0xE }`, `UnitObj+0x3F0 = Actor*`, `Actor+4 = Vec pos`.
- `EvProc`: 0x30 seq data (s16 kind at +2, where 0x70 = a special branch), 0x34/0x38 handles, 0x3C/0x40 cached actors, 0x44 doneCb, 0x45 name[0x23], 0x68 EvSub*, 0x6C/0x6D s8 x/y, 0x6E s8 skill id, 0x70 s16 value, 0x74 cb, 0x78+ subclass fields (u8 state, or the map object pointer for the shooter, with 0x7C..0x7F s8 coordinates).
- `EvCmd { +0x18 EvProc* proc; +0x30 EvAnimCtl* ctl }`, `EvAnimCtl { +0 obj; +0x18 flags; +0x98/+0x9C callbacks; +0xA4/+0xA8 user data }`.

## Compiler quirks found
1. **Declaration order sets register allocation.** The first-declared local tends to get the highest callee-saved register. Several functions matched only after reordering declarations or moving a declaration out of a loop body.
2. **Locals of an inlined function are placed below the caller's locals and temporaries on the stack.** In 800E67D0 the stack layout matched only after the `Vec v; Vec w;` copy moved into a `static inline` helper.
3. **Nested inlines change argument evaluation order and register allocation.** `Setup(a, HandleObj(h1), HandleObj(h2))` evaluates h2 first. Assigning to locals inside the inline first restores the original order.
4. **Float constants.** When the original loads a constant in an odd place (before the stack setup, or interleaved), a C float literal (`0.0f`, `40.0f`, `-32.0f`) matches where the extern `lbl_804CDxxx` doesn't. The checker doesn't verify literal values, so check them against sdata2. The u8 colour initialisers (`GXColor c = {0x80,0x80,0x80,0x40}`) are also compiler-generated constants. Storing a call result through a pointer (`*(f32*)(call()+0x68) = K`) hoists the constant load above the call. Using a temporary pointer fixes it.
5. **A range switch builds booleans.** The pattern `cmpwi 3; bge F; cmpwi 0; bge T; b F` is `switch (x) { case 0: case 1: case 2: return 1; } return 0;`.
6. **u8 compares.** `u8 > 0x40` gives `cmplwi`, while `(int)u8 > 0x40` gives `cmpwi`.
7. **Strings in a pool** can be written as `(char*)lbl_POOL + off`, which emits `lis/addi base; addi off` and passes the reference check. Accessing a field of a large .bss object (`*(s32*)(lbl_803C8E80 + 0x3F0)`) also keeps `addi @l` and the field offset separate.
8. **`#pragma use_lmw_stmw on`** was needed for 800E8304 only. The other functions in this region use `_savegpr_NN` (it's mixed per TU).
9. **Auto-inlining:** a function defined earlier in the same file gets inlined into a caller (`-inline auto`). 800EDB70 has to sit in a different file from 800EA810 so it keeps its tail call.
10. **C++ virtual calls** (`lwz r12,0(r3); lwz r12,off(r12); mtctr r12`) only match from a `.cpp` file with a real class. C function-pointer tables load into a different register. Use `extern "C"` to keep the `fn_` names. The vtable offset includes the 8-byte header.
11. **Walking-pointer loops.** When the original uses a separate pointer induction register and the index register is allocated first, a hand-written walking pointer (`r = (T*)((u8*)r + 4)`) reproduces it.
12. **`cond ? 2 : 1`** gives `neg/or/srwi` then `addi` (800F416C). Storing a masked bit in a `u16` local and returning `f != 0` gives `rlwinm` then `neg/or/srwi` (800FADA0).
13. **Returned Vec:** `Vec v; v = fn(); out->x = v.x; ...` gives float copies. `Vec v = fn();` and `*out = v;` copy words.
14. **s8 fields:** using the field directly gives `lbz r0; extsb. rN, r0`. An `int` local gives `lbz rN; extsb. rN, rN`.
15. **Float to s8 arguments:** `f32 x = m->x; f32 y = m->y; fn(map, (s8)x, (s8)y);` gives the original's `lfs f0 / lfs f2 / fctiwz f1,f0 / fctiwz f0,f2`.
16. **`#pragma auto_inline off` works at the callee's definition**, not at the caller. Wrap the callee in `#pragma push` / `pop` (800FAE98) to keep a real call to it.
17. **Reversed FP loads:** `f32 my = m->y; f32 mx = m->x;` before a call fixes `lfs` order (800FB100). Writing a float field from locals loaded z, y, x matches 800FD0CC.
18. **`#pragma pool_strings on` with literals** reproduces `lis/addi base; addi off` and keeps the base in a register, but needs the TU's whole pool in order. `base + off` on an extern gets each sum CSE'd.
19. **`(x & 0x22U) != 2`** gives `cmplwi`.
20. **By-value `Vec` in an extern prototype** gives `lfs f1; lfs f2; lfs f0; stfs f1; ...` (800FC5D8, 800F15AC, 80100C70 shapes). Passing a pointer to a copy doesn't.
21. **Store then read back:** `a->h = z; a->z = a->h;` gives `stfs f1; frsp f1,f1; stfs f1` with no double in the source (80100384). `K * p->f84` right after storing it does the same (800EA224).
22. **`inline_depth` and helpers:** at the limit, both the recursive call and a small helper become real calls (800F130C with depth 3), so the helper needs its `fn_` name.
23. **Guard inside an inline:** `if ((p->h52 & 0x80) == 0) { switch ... return 1; } return 0;` as one inline reproduces the shared `li r30,0` tail (800FDA20, 800FEEF0). A `cond ? 0 : f()` at the call site doesn't.
24. **Non-folded constants:** `int n = 0x10; (f32)n` keeps `li; xoris`. `li r0,0xC; srawi r31,r0,1` in 800FD65C wasn't reproduced: every form folds.

## Round 14 (7 functions, 5,536 bytes)
| File | Functions |
|---|---|
| `fn_800F0CBC.cpp` | 800F0CBC |
| `fn_800F35AC.cpp` | 800F35AC |
| `fn_800F491C.cpp` | 800F491C, 800F4B94, 800F4E08 (the SetAnim family) |
| `fn_800FBDF0.cpp` | 800FBDF0 (same `SETANIM` macro) |
| `fn_800FC7D0.cpp` | 800FC7D0 |

What solved them: the locals of `Data`, `Pick` and the lookup loops are declared in the caller and passed into the inlines by reference. They then rank below the compiler temporaries. `SETANIM` is a macro only so that each caller owns those locals. `wip/fn_800F491C.cpp` is now out of date.

Caveats (they match, but may not be the original source):
- By-reference `s`, `r`, `v`, `ok`, `n`, `t`, `i` and `m` parameters, and the `SETANIM` macro, exist only to rank registers. The original probably had plain inlines with ordinary locals.
- `fn_800F0CBC.cpp`: `H0..H3` write out the recursive `fn_800F130C` by hand, and `Last` exists only to set the stack slot. It has a `pool_74b4` dummy, and `fn_800F491C.cpp` and `fn_800FBDF0.cpp` have `pool_7ba4`: not real code, same rule as round 8.
- `fn_800F35AC.cpp`: explicit `o1`/`o2` byte offsets, `z2` and `u->x0 = z; u->x0 |= 0x3c0;` only shape the code. The original probably indexed the arrays.
- `fn_800FC7D0.cpp`: the whole body sits in `body` behind a one-line wrapper; `Pl3` and the split `my`/`mx` declarations only set load order.

Still open: 800F6AEC is registers only (`k` and `w` want r28, the third `Data` result r27; see `wip/fn_800F6AEC_r14.cpp`). An out-parameter for `e` moved other registers and scored worse. 800FBC90 (2): a by-reference `u` fixes the load order but ranks it r30, not r26. 800EB988 (3): about 12 spellings of `n` tried, no change. 800F002C (7): by-reference `n`/`i` at every Lookup made it worse. Not retried this round: 800FA264, 800EB048. Not attempted: 800F98E4.

## Round 16 (1 function, 2,016 bytes)
- `fn_800F002C.cpp`: solved from `wip/fn_800F002C.cpp` by an exhaustive grid of the first lookup's inline locals (4 declaration orders x 5 types for `n` x 3 for `i`, 360 compiles): `void* b; u16 n; Pair* t; int i;` with the assignments separate. `u16 n` is what moves `n` to r28. Caveat: `Lookup2` exists only for this one call site's ranks; `pool_74b4` is the StringPool dump (not code). Passes `--strict-references`.
- Tried without success: 800FBC90 (576 declaration x assignment orders of its four prologue loads), 800EB988 (sharing `n` with Notify's counter, by-reference counter), 80102928 (10 spellings of `a = f(); fl |= 0x20`), 800F6AEC (`tys.py` + `sw.py` on the r14 WIP, no change).

## Round 18 (goal changed: exact, or functionally equal in `equiv/`)

From this round a function is done at one of two levels: exact (`check_func.py --strict-references` prints MATCH, file in this folder) or functionally equal (`check_regs.py <file> --extra "-i src/game/rE_800E5DE4 -i src/game/rE_800E5DE4/wip"` prints `renamed` or `regs`, file in `equiv/`). Every `equiv/` file compiles on its own.

Exact (3 functions, 1,348 bytes):

| File | Bytes | Contents |
|---|---|---|
| `fn_800F201C.c` | 0x2CC | Colour by index from a 14-entry table copied to the stack. Needs `#pragma use_lmw_stmw on`; a plain local array initialiser reproduces the whole spill pattern. |
| `fn_801010F0.c` | 0x138 | Fade a unit sprite out while sliding it back to its owner (sibling of fn_801013EC). `UX`/`UY` accessor inlines give the load schedule. |
| `fn_80101568.c` | 0x140 | Start of the slide to another unit (sibling of fn_80101268). |

Functionally equal (8 functions, 4,736 bytes):

| File | Class | Bytes | Contents |
|---|---|---|---|
| `equiv/fn_800F6AEC.cpp` | regs | 0x924 | SetAnim. The round 14 wip plus one fix: `fn_8000866C(qq, -1.0f)` (the wip passed 0.0f, which was a wrong constant, not a register miss). |
| `equiv/fn_800FDDE8.cpp` | regs | 0x214 | Movement process: start of a step. `StepScale(n, 1.0f)` keeps the multiply by 1.0f. |
| `equiv/fn_800ED4AC.cpp` | regs | 0x1F4 | Battle sequence step that spawns the action 0x16 effect model. |
| `equiv/fn_8010403C.cpp` | regs | 0x1A0 | Start of a one-direction push (direction bits 1/2/4/8). |
| `equiv/fn_800F15AC.cpp` | renamed | 0x180 | Model sound events at the "se" joint. Written as C++. |
| `equiv/fn_800F7BF4.c` | regs | 0x110 | From `wip/fn_800F7BF4.c`, with a local inline copy of fn_800F7724. |
| `equiv/fn_80103410.cpp` | renamed | 0xA4 | Start or reuse the movement process of a unit. |
| `equiv/fn_800FCD10.c` | regs | 0x80 | From `wip/fn_800FCD10.c`. |

Written this round but still class `other` (same instruction count, one scheduling swap; functionally the same code), saved in `wip/`: `r18_fn_800EF0D8.cpp` (gauge frame sprite, `ori`/`mr` order in one call), `r18_fn_8010436C.cpp` (straight-line move start, store order), `r18_fn_800FF170.cpp` (next path node, volatile registers and one `stw`/`xoris` pair).

Still open and why: 800F98E4, 800FB398, 800FA590 (matrix-heavy draws with many `Vec` temporaries and pooled statics at `lbl_80367A58`; not attempted this round), 800FD65C, 80101EEC, 80102030 (the `li r0,N; srawi rX,r0,1` idiom is still unsolved), 800EB048, 800F199C, 800FA264, 800FBC90, 80102928, 800FAE08, 800FD05C (one or two instructions scheduled differently; register-coupled), 800FC09C, 800FC5AC, 800EB410.

Caveats for a port:
- The `equiv/` files built from a parent file repeat that file's helper block with the exported bodies turned into prototypes. Where the original inlines a matched neighbour, the file has a local `static inline` copy with an `_i` suffix (`fn_800F7724_i`); a port should call the real function.
- `fn_800F15AC` is C++ although `fn_800F080C.c` next to it is C: the assignment copies need C++ semantics. `Evs()` and the declaration order only set the entry schedule.
- `fn_800ED4AC`: `EffPos`, the named copy `t` and the unused `Get7790`/`ActPos2` inlines come from the stack slot search.
- `fn_8010403C`: `DirX`/`DirY` are inferred; the `p->t = 0` after the step count is a statement order found by search.
- `StepScale(n, 1.0f)` in `fn_800FDDE8` is probably a real speed-scale constant, but its name and form are mine.

Lessons:
- A wip that prints "other, 0 words" is often a wrong constant: `check_func.py -v` showed 0.0f against the original's -1.0f in fn_800F6AEC, and fixing it moved 2.3 KB to `regs` at once.
- A ternary written inside the call (`f(0.0f, 0.0f, 0.0f, 0.0f, b ? 0xE8 : 0xF0, d)`) puts the float argument loads before the conditional; a named local computed before the call does not.
- Accessor inlines on a re-read pointer field (`UX(p->unit)`) schedule the pointer load early; `p->unit->x` written directly loads it late.
- A multiply by 1.0f survives only when the constant arrives as an inline parameter.
- Statement order matters at `regs` level too: permuting five independent statements found the one order that removed a scheduling difference (fn_8010403C).

## Round 20 (small leftovers; `sched` and `slots` now count)

Levels as printed by `python3 -I tools/check_regs.py <file> --extra "-i src/game/rE_800E5DE4 -i src/game/rE_800E5DE4/wip"`. `sched` files were looked at with `tools/equiv/dd.py` (moved instructions are listed in each file header) and run through `tools/equiv/symcheck.py --anon`.

Totals: exact 3 functions / 1016 bytes, sched 1 functions / 112 bytes.

| Function | Class | Bytes | File | symcheck |
|---|---|---|---|---|
| 800FD05C | sched | 0x70 | `equiv/fn_800FD05C.c` | clean |
| 80101EEC | exact | 0x144 | `fn_80101EEC.cpp` |  |
| 80102030 | exact | 0x1A8 | `fn_80102030.cpp` |  |
| 800FD65C | exact | 0x10C | `fn_800FD65C.c` |  |

Complete self-contained drafts still at `other` (new `wip/*_r20.*` files; the header of each says what differs):

- `wip/fn_800FAE08_r20.c` (0x90): same size; frame 0x20 vs 0x10 (the original reuses one conversion slot) and float load order.
- `wip/fn_800FC5AC_r20.c` (0x2C): all 10 instructions equal; the original has a dead blr after the tail call (size 0x2C). A conditional path before the call gives b; blr, but no unconditional form tried does (inline wrapper, do/while, for+break, goto, switch, non-void).

Solved idiom (open since round 9): `li r0,N; srawi rX,r0,1` is an inline with a local constant, `static inline int Half(void) { int x = 0x10; return x >> 1; }`, compiled under `#pragma opt_propagation off`. 80101EEC, 80102030 and 800FD65C (new, written from the asm) match exactly. The pragma is placed after the parent's helpers, so it only covers the one function in each file.

Not attempted this round: 800F98E4, 800FA590, 800FB398, 800FC09C (the self-contained wips are unchanged), 801059EC (no draft).

800FC5AC: a conditional path in front of the tail call gives the original's `b fn; blr`, so the source probably has an early return that folds away late; eight unconditional forms do not give it.

## Round 21 (small functions)

Totals: exact 1 function / 280 bytes.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 801059EC | exact | 0x118 | `fn_801059EC.cpp` (+ `.symbols.json`, check with `--symbol-map`) | static initialiser of the rP unit, hand-written over pooled statics; header lists the global definitions and the port caveats |

Not done: 800F98E4 (2.4 KB of matrix and float code, frame 0x470, no draft; not started), 800FB398 and 800FA590 (pooled constant data at `lbl_80367A58`; unchanged), 800FC09C (the conversion-slot problem; unchanged).

## Round 22

| function | level | bytes | file |
|---|---|---|---|
| fn_800FB398 | sched (2 hoisted constant loads swapped), symcheck clean | 1164 | `equiv/fn_800FB398.cpp` |
| fn_800F98E4 | draft (`other`, size 0x99C vs 0x980) | 2432 | `wip/r22/fn_800F98E4.cpp` |

- fn_800FB398 did not need a pooled-static rewrite: lbl_80367AA0 and lbl_80367B8C are the anonymous .rodata objects of
  `Vec v = {0,0,-1}` / `{0,1,0}` initialisers, and the checker accepts them by value. Writing them as externs makes
  the compiler hoist their loads out of the loop (wrong). The same probably holds for fn_800FA590.
- fn_800F98E4 (unit shadow blob, optionally stretched between two joints): complete draft. Its six camera vectors
  sit at lbl_80367A58 + 0x48/0xD8/0xE4/0xF0/0xFC/0x108 and are addressed off one base register; the 0x14C-byte pool
  is shared by the file's draw functions (dummy.tpl name, colour tables, pointer table into .sdata2), so offsets
  only come out right with the whole file's constants in one source. Next step for exactness: put fn_800FA590,
  fn_800FB398 and fn_800F98E4 (and whatever else uses the pool) in one file in address order.

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`; symcheck `--anon --xargs` clean):

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_800EF0D8.cpp` | fn_800EF0D8 | 0x184 | fn_8007E374 declared with its CATALOG prototype `(void*, void*, u16)`: the `ori r5` then schedules before `mr r4` |
| `fn_800FD05C.c` | fn_800FD05C | 0x70 | `z = Tick(p); z = Gz(p) - Hgt(p, z);` (step `s48 += 1.0f`, unit z and the height through three one-line inlines, one variable for t and z) and the s40 damping store first inside the clamp |
| `fn_80102928.c` | fn_80102928 | 0x344 | the flags parameter typed `u16` (`fn_80102928(MapUnit*, int a, int n, u16 fl, void*)`): the `ori r26,0x20` then schedules before `mr r24,r3`. Every caller passes a small constant; CATALOG says `int`, ABI is the same. |

Tried in round 23 without an exact result (all targets also went through r23b's automatic searches: callee prototypes
from CATALOG, statement moves up to 3-4 lines, local/parameter int-type changes, split-and-permute declarations,
const on pointer parameters, statement moves inside the called static inlines):
- fn_800FB398: `s = 0.5f` declared at function scope and assigned at each of 11 loop positions; the hoist order stays.
- fn_800FBC90: 696 declaration/assignment orders of r, sv, f, u plus accessor inlines; `lwz u` stays after `lfs f`.
- fn_800EB988: n as s16/int/u16 with accessors, by-reference Notify counter, 3 decl orders: no change at all.
- fn_800FDDE8, fn_8010436C, fn_8010403C (one family): the first `(int)` of the speed conversion wants r4 (r0 here).
  Separate local, reuse of the field variable, `Fr(int t){ t = t/K; return t; }` inlines, nested inlines, all
  positions of `t = 0`/`to.z`: no change.
- fn_800FA264: shared `k = 1` for both calls, Avg inline, operand orders.
- fn_800F7BF4: mdl declared/assigned late, field address inline, `u64 f` / `u32 lo` copies in the inline.

## Round 24

- fn_800EB048 (6 words; z wants r29 shared with fn_800EA848, gets r30): zero as constant, `int`, inline parameter, function-level `z` at three positions, `z` reused for the handler address (the compiler splits the web), handler locals swapped or assigned at the top, one-iteration loops around Init or the stores: no gain.
