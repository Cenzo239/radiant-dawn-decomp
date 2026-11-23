# Region 0x8008E3B4..0x800A3D24 notes

## Status

506 functions match: 131 from round 1, 260 from round 2 and 115 (25,444 bytes) from round 12. Each
file below prints MATCH with `python3 -I tools/check_func.py <file> -v`.

| File | Functions | Contents |
|---|---|---|
| `fn_8008E3B4.c` | 121 | 0x8008E3B4..0x80091E10, except the functions listed below |
| `fn_80091BAC.c` | 2 | fn_80091BAC, fn_80091C5C |
| `fn_80091E38.c` | 1 | registrar, 126 commands |
| `fn_8009283C.c` | 10 | 0x8009283C..0x80092C84 |
| `fn_80092D04.cpp` | 172 | 0x80092D04..0x800988F0, except the near misses below |
| `fn_80098AB8.cpp` | 81 | 0x80098AB8..0x8009A67C, except the near misses below |
| `fn_8009AE54.c` | 1 | registrar, 279 commands |
| `fn_8009C6DC.c` | 1 | registrar, 5 commands |
| `fn_8009CEA4.c` | 1 | registrar, 7 commands |
| `fn_800A35E0.c` | 1 | registrar, 52 commands |
| `fn_80089AA8.cpp` | 19 | RNG, fatal handler, `MemStream` methods, font metrics |
| `fn_80099F54.cpp` | 1 | fn_80099F54 (the copy in `wip/fn_8009999C.cpp` is now stale) |
| `fn_8009A720.cpp` | 26 | script procs, movie commands, 0x8009A720..0x8009CE68 |
| `fn_8009CF6C.cpp` | 10 | script startup, global flags, event caller |
| `fn_8009DBE4.cpp` | 1 | support partner list |
| `fn_8009E900.cpp` | 7 | event trigger procs |
| `fn_8009F768.cpp` | 6 | event trigger conditions |
| `fn_800A04C8.cpp` | 14 | event lookups by position, unit and index |
| `fn_800A1D40.cpp` | 11 | game over check, pad script, `E_*` proc cleanup |
| `fn_800A2ACC.cpp` | 20 | binding commands, flag bitsets, option setters |

`script.h` holds shared declarations for `fn_80098AB8.cpp`. `types.h` gained `u64` and `s64`.
`evflags.h` holds the global flag inlines for the round 12 event files.
`commands.txt` lists all 469 registered script commands as function, name, argument count.

**Resume point: `fn_8008B19C`, then 0x8008B60C..0x8008E398 and fn_8008A868.** From 0x8008E3B4 to
0x800A3D24, only the wip functions below are unmatched.

Near misses in `wip/`:

| Function | File | Words differing | Cause |
|---|---|---|---|
| fn_80092E10 | `fn_80092E10.cpp` | 2 of 10 | `lwz` scheduled before `stw r0` |
| fn_80092F74 | `fn_80092E10.cpp` | 8 of 68 | r4/r5 swap in the slot loop |
| fn_80093084 | `fn_80092E10.cpp` | 7 of 62 | `lbz` scheduled after the register saves |
| fn_80094130 | `fn_80094130.cpp` | 22 of 24, size 0x60 vs 0x6C | unreachable store left by an inlined ctor |
| fn_80095514 | `fn_80095514.cpp` | 3 of 74 | float conversion registers |
| fn_8009999C | `fn_8009999C.cpp` | 5 of 61 | r4/r5 swap in the stream init |
| fn_8009A3D8 | `fn_8009999C.cpp` | 1 of 15 | `fmuls` operand order |
| fn_8009167C | `fn_8009167C.c` | about 28 of 118 | volatile registers in the unrolled loop |
| fn_8009AB90 | `fn_rD12_near.cpp` | 1 of 19 | `fmuls` operand order, same as fn_8009A3D8 |
| fn_8009EEEC | `fn_rD12_near.cpp` | 22 of 175 | volatile registers in the unit loop |
| fn_8009F1A8 | `fn_rD12_near.cpp` | 22 of 122 | same unit loop |
| fn_800A0998 | `fn_rD12_near.cpp` | 3 of 97 | counter register |
| fn_800A15F4 | `fn_rD12_near.cpp` | 2 of 149 | `id` register |
| fn_800A1848 | `fn_rD12_near.cpp` | 6 of 67 | volatile registers in the first stores |
| fn_8008A070 | `fn_rD12_near.cpp` | 6 of 32 | volatile registers around the mask |
| fn_8008A22C | `fn_rD12_near.cpp` | 59 of 60 | u64 sum shape not found |
| fn_8008A37C | `fn_rD12_near.cpp` | size 0x58 vs 0x5C | wants `blt L; b M` |
| fn_8008AEE4 | `fn_rD12_near.cpp` | 8 to 13 of 106 | glyph table and `mid` registers |

The `fn_rD12_near.cpp` fragments also need helpers that are not in the file: `clearUnitFlags`
(a unit loop clearing bits 0x1 and 0x800 of the u64 flags) and `evAny(kind)` for fn_8009EEEC and
fn_8009F1A8, and `isDbcs`, `Glyph` and `SysFont` from `fn_80089AA8.cpp` for fn_8008AEE4.

These wip files are fragments and do not compile alone. Each comment says what it needs.
The registrars and `commands.txt` were generated from the raw instruction words in the asm.

Matched functions (fn_8008E3B4.c):
8008E3B4 8008E768 8008E844 8008E880 8008E8AC 8008E8E0 8008E930 8008E980 8008E9E8
8008EA1C 8008EA64 8008EAAC 8008EAF8 8008EB40 8008EB84 8008EBE8 8008EC44 8008EC8C
8008ED74 8008EE50 8008EF10 8008F07C 8008F0C4 8008F10C 8008F164 8008F1BC 8008F21C
8008F264 8008F2C4 8008F324 8008F398 8008F410 8008F494 8008F518 8008F59C 8008F5BC
8008F5E0 8008F61C 8008F62C 8008F6B4 8008F6F8 8008F73C 8008F74C 8008F75C 8008F76C
8008F77C 8008F7C4 8008F7D8 8008F814 8008F820 8008F874 8008F880 8008F8B8 8008F8F0
8008F904 8008F91C 8008F958 8008F968 8008F9C0 8008F9CC 8008F9DC 8008FAAC 8008FB28
8008FBBC 8008FC7C 8008FCC4 8008FD3C 8008FDB4 8008FE2C 8008FEA4 8008FF1C 8008FF9C
80090000 80090060 800900C4 80090138 80090198 8009020C 800902A8 80090318 80090378
800903FC 80090458 800904B4 8009054C 800905AC 8009060C 800906D8 80090764 8009081C
80090890 800908F8 800909C0 80090B1C 80090BBC 80090CC0 80090DFC 80090EDC 80090FEC
8009111C 80091208 800912CC 800913A4 800913E8 8009144C 80091538 80091610 80091854
800918C8 800919B0 80091A14 80091A48 80091A84 80091AA8 80091B40 80091B48 80091B58
80091B80 80091B88 80091DC4 80091E10

Matched functions (fn_8009283C.c):
8009283C 8009285C 800928B0 80092904 80092958 800929AC 80092A00 80092BF8 80092C28 80092C84

## Subsystems (guessed)

- **Script/event command API for units (0x8008E3B4..0x80091E10).** Almost every function takes a unit
  index (`u8`, 1-based), looks it up with `GetUnit`, checks that `unit->pid` (+0xEC) is non-null,
  and then gets/sets one field. These are probably the script engine's `Unit*` builtins
  (GetUnitField, SetUnitField, AddItem, RemoveItem, LearnSkill...).
  - `fn_8008E3B4` = `UnitGetParam(id, field)` and `fn_8008E768` = `UnitSetParam(id, field, value)`.
    Each is a 0x34-case switch over unit fields and stat getters (`fn_8012C250(unit, stat)`).
  - `fn_8008E844/880/980`: army lists. `lbl_804CB814` is an array of 0xC-byte army heads, with
    11 armies. Units are linked through `unit+0xE8`.
  - `fn_8008FBBC`, `fn_8009144C`, `fn_80091538` loop over unit ids 1..254 with an army mask built
    by `fn_8010E41C(mask, 3)`.
  - `fn_80090xxx..80091208`: inventory (7 `UnitItem`s at unit+0x1BC).
  - `fn_80091610..800919B0`: skills (18 `SkillEntry`s at unit+0x12C). The capacity check calls
    `fn_80127A90(unit)` and `fn_8011B8A4(list)`.
  - `fn_800912CC`: convoy (`fn_801059B0()` returns `{int count; UnitItem* items;}`).
    `fn_8010599C(army)` gets the per-army convoy.
- **Map** `lbl_803EC898`: the tile byte array is at +0x200D (`[y*64 + x]`, s8 coords) and an s16
  move/distance array is at +0x15294. `fn_801151BC(map, unit)` fills that array.
- **Game state / chapter** `lbl_803CAB38` (accessed through `fn_80060754`/`fn_80060728`): s16
  array at +0, a byte at +0x10 and +0x11 (byte +0x11 of the `fn_80060728` result is the
  difficulty/mode, 0..3), s16 at +0x12, a byte array at +0x14.
- **Chapter script loader** `fn_80092A00`: `snprintf("Scripts/%s.cmb")`, then loads
  `"mess/%s%s.m"` with a language directory (`lbl_8037AB10[lang]`, where lang is the s8 at
  `fn_8024BC94()+0x1BC8`) and stores the result in `lbl_804CB610`. `fn_80092BF8` unloads it.
  `fn_80290DDC` = sprintf and `fn_80290D04` = snprintf.
- `lbl_803CA870`: two unit pointers (+0, +4) and a byte at +0xD. This is probably the
  current/target unit pair, for example the battle participants.
- The code is C++. `fn_80111B34`/`fn_80111C24(this, -1)` are the ctor/dtor of a stack `UnitItem`
  (`fn_80090DFC`, `fn_8009111C`). Explicit calls in C reproduce it exactly.

- **Script commands (0x80092D04..0x8009A67C).** Real names are in `commands.txt`, taken from the
  registrars, which call `fn_800C3C3C(name, func, argc)`. Most commands return 1 or 0 and validate
  pointer arguments with `IsValidPtr` (0x80000000..0x81800000 or 0x90000000..0x98000000).
  - 0x80092E38..0x80093254: `global`, `regist`, `get`, `set`, `clr` flags on `lbl_803CAB38`
    (names +0x144, hashes +0x344, bits +0x544).
  - 0x80093328..0x800934E8: `Talk*`, `MessSet*Arg`. 0x8009352C..0x8009394C: `*Focus*`, default talks.
  - 0x80093AB0..0x80093D50: `UnitEscape`, `UnitResetStatus`. 0x8009408C..0x8009433C: `_gi`, `_gs`,
    `MindGetMoney`, `DD*Flag*`.
  - 0x80094364..0x80094EA0: `Rect*`, objects found by name with `fn_800D4228`.
  - 0x80094F18..0x80096528: `GMap*`, on the map named by `lbl_803E5028`.
  - 0x80096598..0x80096BB0: `Dialog*`, `td`, `tde`. 0x80096BB4..0x80097114: `Face*`.
  - 0x80097140..0x800972C4: `Timei*`, `TutShowKari`. 0x80097358..0x800975F4: `Fade`, `Flash`, `Wipe*`.
  - 0x800975F8..0x80097790: `ProcKill`, `ProcExists`, `PadSetMask`, `PadResetMask`.
    `fn_80097694` parses a button string into a mask.
  - 0x800977CC..0x80097A88: `Netuzo*`, state in `lbl_803C8DA0`, battle state in `lbl_803C8E80`.
  - 0x80097CD8..0x800980A0: terrain tiles in `lbl_803CB770` (`AddTT`, `SetFragile`, `SetPit`...).
  - 0x8009812C..0x80098210: `JyokyoMap*`. 0x80098234..0x800988F0: `BGM*`.
  - 0x80098AB8..0x800992FC: `SFX*`, `ENV*`, `VOICE*`. 0x800993E0..0x800994B0: `GetRank`, `Easy`,
    `Normal`, `Hard`, `Maniac`.
  - 0x8009957C..0x800996D8: `MoviePlay`, `ChapterMoviePlay`.
  - 0x80099774..0x80099B50: `UnitsPush`, `UnitsPop`, `AllPush`, `AllPop`, through a `MemStream` on
    buffer `lbl_804CB618`.
  - 0x80099D4C..0x8009A254: `SelectSally`, `SelectAuxiliary`, `SaveMenu`, `Sally*`.
  - 0x8009A4A4..0x8009A554: version checks. 0x8009A5F0, 0x8009A67C: `CreateVMCThread`, `CreateVMCThread1`.
- **Interfaces.** `fn_8024F3FC(ch)` returns a sound channel object (virtuals at +0x10 isPlaying,
  +0x24 stop(fade), +0x38 setVolume(vol, time)). `lbl_804CB5B8` is the pad object (+0x48 trigger,
  +0x8C and +0x90 set and reset mask). The method names are guesses.

- **Round 12 (guessed).**
  - `fn_8009CF6C` initialises the script system: three 0x24-byte contexts at 0x803E5040 (file statics
    here), all registrars, then registers 8 `gf_*` flags and runs `RegistGlobalFlags`.
  - `fn_800C3BC8(p)` walks the script's event entries. Byte +0xC is the kind, and the u16s at +0x14..
    are string offsets resolved by `fn_8009D948`. Kinds seen: 1, 2, 3, 5, 6, 8, 0xA, 0xB, 0xD, 0xE,
    0xF, 0x13, 0x14. `EvProc` (+0x34 kind, +0x38 condition) walks them, and `lbl_803E50B0` is the filter.
  - `fn_8009D958` skips script bytecode to find a label by name.
  - `lbl_804CB5D0` is the 3-word game RNG. `fn_80089AA8` seeds it, and `fn_80089C1C` returns 0..99.
  - `fn_800A26B0` plays a pad input string, for example for tutorials.

## Struct layouts

`Unit`: 0x3F0 bytes. The array is `lbl_804CB810`, 1-based, and the index is `u8`.
```
0x004 f32  x (float pos)      0x008 f32 y
0x0E4 Unit* ?                 0x0E8 Unit* next (army list)
0x0EC PersonData* pid         0x0F0 JobData* job (+0x14 flag, +0xEC u16)
0x0F4 ArmyData* (+0x08 u8 army/faction index)
0x0F8 Unit* rescue/paired     0x0FC u8 unit id
0x0FD u8                      0x0FE s8
0x102 s8 map x                0x103 s8 map y
0x108 u64 state flags (hi word 0x108, lo word 0x10C; bit 0x100, 0x8, 0x4, 0x2, 0x1, 0x10000..)
0x114 s8   0x117 u8   0x118 s8 (-1 = use pid+0xE1)
0x12C SkillEntry skills[18]   (8 bytes: u8* skill(+0x1E cost,+0x1F removable); u8 kind; bitfield byte)
0x1BC UnitItem items[7]       (0x28 bytes: void* data; u8; bitfield byte at +5 (MSB-first bits))
0x37C s16  0x380 u8  0x382 u16 0x384 u16 0x388 u16 0x38A u16 0x38C u16 0x38E u8 0x38F u8 0x390 ...
0x3B4 u32 flags2
```
Item bitfield byte (+5), from the MSB down: 0x80 (flag80), 0x40, 0x20, 0x10, 0x08, 0x04 ("kept",
skipped by the discard loops), 0x02, 0x01.

## Compiler quirks found (GC/3.0a5.2, default flags)

1. **`#pragma use_lmw_stmw on` is needed.** With the default flags, functions that save 5 or more
   GPRs call `_savegpr_27`/`_restgpr_27`, but the original uses `stmw`/`lmw` inline. Functions
   that save 4 or fewer registers use plain `stw` in both cases. Something else is going on as
   well, because 0x80094658 in this region does call `_savegpr_27`. It may be a different TU,
   or the pragma may be toggled there.
2. **`GetUnit` must be a `static inline u8* GetUnit(u8 id)` called with an `int`.** A `u8`
   parameter on the outer function removes the `clrlwi.` that the original has.
3. **Local declaration order picks callee-saved registers.** The first-declared local gets the
   highest register (r31). Reordering declarations fixed 4 functions.
4. **`a() + b()` evaluates `b()` first** when both sides are calls. For `x = f(); return y + x;`
   vs `return x + y;`, the operand order in the `add` follows the source.
5. **`!(x & 8)` emits `cntlzw/srwi`, while `(x & 8) == 0` emits `rlwinm/xori`.** Similarly,
   `item->flag04 == 0` and `!item->flag04` gave different branch layouts inside an `&&`.
6. **Branch layout follows the source.** `if (p == NULL) return 0; return p->x;` and
   `if (p != NULL) return p->x; return 0;` compile differently (bne vs beq first).
7. **Switch case blocks are emitted in source order**, after a compare tree. Code that puts
   `case 3` first means the source listed case 3 first.
8. **u64 field ops match as written.** `*(u64*)(u+0x108) &= ~(s64)mask;` and `return u64 |= x;`
   (with an int return type, so the low word is returned) match exactly, including the odd
   `srawi` sign-extension forms.
9. **A small sdata object must be declared with its size** (`extern char lbl_804CA0C0[8];`) to
   get `li rX, sym@sda21`. With an unsized declaration you get `lis/addi`.
10. **Small fixed-count loops (7 iterations) with simple bodies are fully unrolled.** Loops with
    a call or a compare against a parameter are not.
11. **Callee return types matter.** If the asm has `clrlwi`/`extsb` after a `bl`, the callee
    returns a wider type than the wrapper. When both are `u8`, the call becomes a tail call
    instead.
12. **Reused locals.** `fn_8008EF10` only matched when the return value of `fn_800C3558()` was
    assigned back into the `unit` variable, not used as a temporary.
13. **A register left holding a value at a call is an argument.** `extsb. r4, r31` in fn_80091BAC
    and r5 in fn_80097A88 looked like allocator noise, and both were a second or third argument
    to the next call. The fix was adding the parameter to the prototype.
14. **`|| ` range checks must be written in the `if`.** `IsValidPtr` matches as a macro. As an
    inline returning BOOL it materializes a value and adds 0x10 bytes.
15. **The same constant stored twice around a call** goes into a callee-saved register unless each
    store is in an inline setter (`setFlag1C`).
16. **Earlier functions inline by themselves when small.** fn_800937E0 calls fn_8009358C and
    fn_800988F0 calls fn_800988A8, fn_800986E8 and fn_800985C8. fn_800977CC is too big, so its body
    is `static inline NetuzoInit`, which fn_80097A88 also uses.
17. **`_savegpr` is the default in these files.** Only functions that show `stmw` sit inside
    `#pragma use_lmw_stmw on`/`off`.
18. **A struct initializer with a constant member** places its template in sdata2, which is why
    lbl_804CD1F7 is a lone 0xFF byte (`GXColor c = {r, g, b, 0xff}`).
19. **Vtables can be written out by hand.** A plain struct with `void* vtbl` set to the `lbl_`
    vtable keeps references checkable, and is what matched `MemStream`. Real classes referenced
    a local `__vt__` symbol instead. Classes are fine when only making virtual calls.
20. **Giant registrars are easy.** A long run of `fn_800C3C3C` calls matches from a generated list of
    calls. Decode targets from the raw words: the `@ha`/`@l` symbol pairs in the asm can disagree.
21. **Flag lookups have three register shapes.** `flagFind(const char* const&)` keeps the string above
    the index. For string below index below walker, rank them in the caller with `flagFindR` and
    `FLAG_GET_R` in `evflags.h`. A by-value inner parameter does not change the rank.
22. **Auto-inlining is a free 2.5 KB.** `fn_8009CF6C` is `fn_80092E38` inlined 8 times, and
    `fn_8009E900` is `fn_8009E554`'s body. Wrap a callee in `auto_inline off` when the caller has a real `bl`.
23. **Two sequential clears fold.** `f &= ~1; f &= ~4;` becomes one `and`. To keep `clrrwi; rlwinm`,
    write the second as a one-bit bitfield store.
24. **Const reference for a global's first byte.** `flagGet(t, const char* const& name)` on `lbl + 0`
    gives `lis; lbzu`. A by-value parameter gives `lbz; addi`.

## Round 16

`fn_800A15F4.cpp` matches (596 bytes, strict-reference clean). It takes the declarations of `fn_800A04C8.cpp`. The last `id` register was fixed by reading the current unit's person through a trivial accessor (`curPid()`) instead of `*(void**)(lbl_803CA870.a + 0xec)`. The fragment in `wip/fn_rD12_near.cpp` is now stale.

Tried without success: `fn_800A0998` (counter register; wrappers, counter types and declaration orders stay at 3 words), `fn_80093084` (the `name[0]` load is still scheduled before the register saves).

## Round 19

Ten functions newly at `regs` level (3,304 bytes), in `equiv/`, all self-contained (check with
`--extra "-i src/game/rD_8008E3B4 -i src/game/rD_8008E3B4/wip"`). Most are the old fragments joined with their parent
file's declarations by `tools/equiv/mkself.py`:

| File | Function | Bytes | Notes |
|---|---|---|---|
| `equiv/fn_8009167C.c` | fn_8009167C | 472 | fragment + `fn_8008E3B4.c` (the fragment's own `SkillEntry` dropped) |
| `equiv/fn_80092F74.cpp` | fn_80092F74 | 272 | fragment + `fn_80092D04.cpp` |
| `equiv/fn_80095514.cpp` | fn_80095514 | 296 | function only; `Color2`/`callColor` are already in `fn_80092D04.cpp` |
| `equiv/fn_8009999C.cpp` | fn_8009999C | 244 | fragment + `fn_80098AB8.cpp` |
| `equiv/fn_8009AB90.cpp` | fn_8009AB90 | 76 | 1 word: `fmuls` operand order |
| `equiv/fn_8009EEEC.cpp` | fn_8009EEEC, fn_8009F1A8 | 700 + 488 | `evAny` and `clearUnitFlags` rewritten (the round 12 copies were lost); EEEC needs `use_lmw_stmw on` |
| `equiv/fn_800A0998.cpp` | fn_800A0998 | 388 | needs `use_lmw_stmw on` |
| `equiv/fn_800A1848.cpp` | fn_800A1848 | 268 | |
| `equiv/fn_800A3D24.cpp` | fn_800A3D24 | 100 | new, hand-written static initialiser (base vtable, three table pointers, derived vtable) |

Caveat: `fn_800A3D24` is compiler-generated in the original (constructors of a static object and three static
pointers); the hand-written stores only reproduce its effect.

Still `other`: `fn_80092E10` (the `lwz` is scheduled before `stw r0`), `fn_80093084` (the `name[0]` load comes after
the register saves), `fn_80094130` (unreachable `b; stb` after the constructor stores).

## Round 22

All three former `other` functions are now exact (self-contained files in the region folder; the wip fragments are
superseded):

| function | file | fix |
|---|---|---|
| fn_80092E10 | `fn_80092E10.cpp` | parameter `const Obj90*`: the `lwz` then schedules before `stw r0` |
| fn_80093084 | `fn_80093084.cpp` | name parameter plain `char*` (not `const char*`): the `lbz` moves after the saves |
| fn_80094130 | `fn_80094130.cpp` | Ref constructor `p = 0; kind = 2; flag = 0; if (p) flag = 1;` (as in rF fn_801C77DC) |

Port note: fn_80094130 declares fn_8004B03C with a by-value `Ref`; the definition takes `ItemRef*`. Same ABI.

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`; symcheck `--anon --xargs` clean):

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_8009AB90.cpp` | fn_8009AB90 | 0x4C | `f32 v = fn_8017FA1C(); return (int)(v * lbl_804CD1FC);` with the constant as `extern const f32`: a literal always comes first in `fmuls`. |
| `fn_800A3D24.cpp` | fn_800A3D24 | 0x64 | static initialiser: `BaseCtor(&lbl_803E50C0)` after the three table-pointer stores (statement-move search) |
| `fn_80095514.cpp` | fn_80095514 | 0x128 | the float argument computed first (`f32 v = 0.01f * d;` before `Color2 col(color);`): the int-to-float bias then lands in f2 as in the original |
| `fn_80092F74.cpp` | fn_80092F74 | 0x110 | free-slot loop with an explicit table-view pointer `q` (`q->names[0]` = `names[i]`, as in flagFindR), `q` stepped before `i` in the for header (symcheck: one callee-name artefact, strcmp) |
| `fn_800A1848.cpp` | fn_800A1848 | 0x10C | this file's copy of `evSet13` stores e, a, b (not a, e, b). Shared inlines in self-contained files can be tuned per function. |

Tried in round 23 without an exact result: fn_800A0998 (evNth by reference + flagFindR, 2880 declaration orders),
fn_8009999C (all 120 store orders in this file's MemWriterInit: `owned` first gives the right registers but then the two
stores are in the wrong order; dead base vtable store, volatile and comma forms keep 2 words).
