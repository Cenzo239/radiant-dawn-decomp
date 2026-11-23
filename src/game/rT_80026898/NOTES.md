# Region rT: 0x80026898..0x8002DDD4, 0x80042914..0x8004A6F4, 0x8004A70C..0x8004B870

111 functions match, 0x4930 bytes (18,736). Each file below prints MATCH with
`python3 -I tools/check_func.py <file> -v`. In 0x80042914..0x8004B870, 19 functions are still open
(14,132 bytes). The 0x80026898..0x8002DDD4 range wasn't worked on in the latest round.

| File | Functions | Contents |
|---|---|---|
| `fn_80026950.cpp` | 14 | Battle round helpers: heal, log, damage split, target selection |
| `fn_80042914.cpp` | 11 | Chapter and phase logic, class masks, map cell updates, a draw callback |
| `fn_80044284.cpp` | 22 | Map music, map loading, command state setup |
| `fn_80047164.cpp` | 5 | Command helpers: inventory prompt, item use, proc item slot |
| `fn_80048260.cpp` | 35 | Staff and action sequences, per-target loops, save read |
| `fn_8004A70C.cpp` | 13 | Flag test, full-inventory prompts, skill scroll prompts |
| `fn_80042C84.cpp` | 3 | Unit reset loop, map cell scan, camera to the first unit |
| `fn_80043078.cpp` | 2 | Phase banner choice, deployed unit move |
| `fn_80043BAC.cpp` | 1 | Reset all units for the next chapter |
| `fn_80044588.cpp` | 1 | Map load process start |
| `fn_800474C8.cpp` | 2 | Weapon level-up prompt, rescue drop |
| `fn_8004AD18.cpp` | 2 | Skill scroll use, skill capacity check |

Functions in a file are not always in address order. Functions that didn't match are in
`wip/near_misses.cpp`, each with its word count.

**Resume point:** `fn_80047974` (2 words: `lwz r5,4(r5)` where ours loads r3), `fn_8004AF14` (5: the unit should be r30 and the data r31), `fn_800487DC` family (16 of 118 each), `fn_8004806C`, `fn_80048168`, `fn_80044284` (18, registers only), `fn_800437D0` (32, registers only), `fn_80042D38` (94, registers only in the second loop). `fn_80043E50`, `fn_8004564C` and `fn_800466B4` haven't been tried. The entries in `wip/near_misses.cpp` for functions now in the table above are stale.

## Blockers worth solving

- **`fn_800487DC` family:** `fn_80048A98`, `fn_80048D54`, `fn_80048FF8` and `fn_800492B8` share its
  body (0x1D8 each, 0x938 bytes). `wip/fn_800487DC.cpp` has it at 16 of 118 words. Writing the `Cell`
  copies out by hand and adding a second walker fixed all the saved registers. What's left is that the
  original loads and stores `b` before `a`, and ours does the reverse. All 2,520 orders of the reads and
  writes were tried without success, and so were `const`, reference and inline forms.
- **`fn_800437D0`, `fn_80042D38`:** see `wip/`. `fn_80043BAC` only matches with `opt_common_subs off`,
  and `fn_800437D0` needs that too, but its group loop still wants the walker at r31 and the offset at r29.
- **`fn_80026C44`:** two aggregate-initialised `Spec` locals (templates `lbl_80361308` and
  `lbl_80361318`). `sd` initialises first but sits at the lower stack slot. Plain declaration order
  gives one or the other. `fn_80026CD8`, `fn_80027088`, `fn_80027228` and `fn_8002DBA0` use the same
  templates and haven't been tried.
- **`fn_8004806C`, `fn_80048168`, `fn_80047B18`, `fn_80047DCC`:** the same index expression. The
  original has `mulli r4,k,0xC; addi r0,n,1; mullw r0,r4,r0`. Every spelling I tried gives
  `k*0xC` r0 or r5 instead. The fix should unlock all four (0x7C8 bytes).
- **`fn_8002742C`:** a 4-byte struct is split into bytes on the stack after `fn_801278B8`, so one of
  the calls returns a struct. Not modelled yet.
- **Not attempted, 0x200 bytes and up:** `fn_80028A68` (0x1D18), `fn_8004564C` (0x1068),
  `fn_800466B4` (0x7E8), `fn_800275C4`, `fn_80027D9C`, `fn_800285CC`, `fn_8002B828`, `fn_8002C86C`,
  `fn_8002D430`, `fn_800437D0`, `fn_80042D38`, `fn_80043E50`, `fn_8002ABE0`, `fn_8002B2AC`,
  `fn_800269E4`, `fn_80027228`, `fn_80027AE0`, `fn_800282A0`, `fn_8002A8A4`, `fn_8002AFBC`,
  `fn_8002CEB0`, `fn_8002D8D8`.
- **Not attempted, smaller:** `fn_80026CD8`, `fn_80027088`, `fn_8002AAEC`, `fn_8002B668`, `fn_8002CD5C`,
  `fn_8002DBA0` and the four `fn_800487DC` siblings. `fn_8002AAEC` saves FP registers with `psq_st`
  (Ghidra shows the GQR test), so it is probably ordinary C. A scan of the three asm files for paired-single
  instructions other than stack saves was not completed, so the large ones may still contain some.

## Subsystems

- **Battle context `lbl_803C8E80`** (`Battle` in `fn_80026950.cpp`): three 0x4A0-byte combatant copies at
  0, 0x4A0 and 0x940, each starting with a `Unit` copy; the event log at 0xDE0 (`fn_8002600C(log, code, value)`);
  0x15E4 a round flag; 0x15E8 a value (distance in `fn_8004985C`); 0x15EC a flag word (bit meanings
  not established).
- **Command state `lbl_803CA870`** (`CmdState` in `types.h`): the same struct as rC's `UnitCmdState`.
  Its 0x80-byte path buffers at 0x30 and 0xB0 are used by the mini-yell loader.
- **Result block `lbl_803E7320`:** a count at +0 and 0x24-byte `Cell` entries. `fn_800CFD18(block, i)`
  gets an entry and `fn_800CFB0C(cell)` gets its unit.
- **Action wrapper pattern:** `fn_80026CD8(ctx, unit, -1); fn_8002C170(ctx); fn_8002C1C4(ctx, 10); fn_800E8xxx(proc, cb);`
  appears many times. The callback runs per target (the `WRAP` macro in `fn_80048260.cpp`).
- **Stack items:** `Item`, 0x28 bytes, ctor `fn_80111B34`, copy `fn_80111B64`, dtor `fn_80111C24(x, -1)`,
  set by `fn_80110BB4(&it, data)`, looked up by name with `fn_8010B228("IID_...")`.
- **Class masks:** an 8-byte sdata2 list of class ids ended by 0xFF is written into a 0xB-byte table with
  `memset(m, (u8)lbl_804CA0A0, 0xB)`. Units are then filtered by `m[u->f4[8]]`. See `markAll`.
- **Unit lookup:** `unitAt(id)`: 1-based `u8` id into `lbl_804CB810`, 0x3F0 bytes each.
- **Sleep:** `fn_80320978` is OSSleepTicks. `5LL * (*(u32*)0x800000F8 / 4 / 1000)` is 5 ms.

## Struct layouts (see `types.h`)

- `Unit`: 0xE8 next, 0xEC data, 0xF4 class data (+8 faction), 0xF8, 0xFC, 0x102/0x103 map x/y, 0x108 u64 flags,
  0x110 `Hp` bitfield (`n` is bits 7..9), 0x114 s8 hp, 0x12C `SkillEnt skills[18]`, 0x1BC `Slot items[7]`,
  0x37C, 0x386, 0x388, 0x38F, 0x3F0 original unit pointer.
- `Slot`: 0x28 bytes, data at 0, uses at 4, bitfield byte at 5 (bit 0x40 is `f40`, bits 0xCC cleared on drop).
- `GameState` `lbl_803CAB38`: 0x11 phase, 0x14 per-side flags, 0x9A/0x9B cursor, 0x9C, 0xB0..0xBF counters,
  flag names at 0x144, hashes at 0x344, bits at 0x544, list at 0x554.
- `CmdObj`: command objects from the table `lbl_8037B2FC`, with `test` in the vtable at +0x24.

## Compiler lessons from this region

Lessons not in `MATCHING.md`:

- `lwz r4` instead of `lwz r3` as a base before `ori`/`oris` on a field means a `u64` `|=` with a `ULL`
  constant. r3 is reserved for the high word even though it gets folded away.
- `addc`/`adde` with a hoisted zero register, in place of `addze`, means a signed `s64` total.
- `5LL * u32` keeps the dead `li r0,0; mullw` high-word term. `(u64)` folds it away.
- `clrlwi` on an `int` parameter right before a call means the callee takes `u8`: change the prototype.
- `cmpwi 3; beq A; bge B; b B`: `switch` with `case 3`, then `case 0: case 1: case 2: default:` on one body.
- A saved register reused for a result right after being an argument means the parameter was
  reassigned (`a = f(c, g(), a);`). A separate local won't take that register.
- Hill-climbing is cheap on a small file: 160 compiles took about 3 seconds on this machine.

## Caveats: matches that may not reflect the source

- **`fn_80043BAC`:** wrapped in `#pragma opt_common_subs off`, because that gives the hoisted mask constants
  their rank below the locals. This is probably not in the source. A different construct, or a setting for
  that part of the TU, is more likely.
- **`fn_80042C84`:** `u64 mm = ~0ULL; FLAGS(u) &= mm;` reproduces the `and` with -1, which a constant expression folds away. The original presumably cleared a mask that happened to be 0.
- **`fn_8004333C`:** passes `side` to `fn_8012D2B0` as an argument deduced from the register use only.
- **`fn_80043078`:** passes `side` to `fn_80062A9C` for the same reason, and has empty `case 0, 1, default` labels only to shape the compare tree.
- **`(s8)*(u8*)&u->y103`:** several functions want `lbz r0; extsb r5,r0` for y while x loads directly.
  The cast produces it but is surely not the original spelling, and neither field type explains
  every use (`fn_80044BCC`, `fn_8002BCC4`, `fn_80046FE4`).
- **`fn_80049E3C`:** `case 0: break;` exists only to shape the compare tree.
- **`fn_8004A9F0`:** `case 0, 1, 2, default` on one body, same reason.
- **`fn_80046FE4`:** `goto found` and the out-of-line block were chosen to fit the layout.
- **`fn_8004A70C`, `fn_80044654`:** real inlines copied from rC and the OS macros, so these are likely close.
- **Parameter types:** many `void*` and `int` types are unconfirmed. Names of fields are guesses.
- **Declaration orders** were permuted by hand in many functions to fix registers, and say nothing
  about the source. No function in the matched files kept an order found by the hill climber.

## Round 15

2 more functions match (0xB18 bytes): `fn_80043E50.cpp` (map music per frame, first compile) and `fn_800466B4.cpp` (command action finish, a 93-way switch in jump-table order).

Near miss: `wip/fn_8004564C.cpp` (command action start, 0x1068). All 1050 instructions match structurally. What's left is a rotation: `o`/`p` should be r31/r29, but the first case-local in each case outranks them. The two `Spec` templates are `.data` objects `lbl_8037B188`..`lbl_8037B200`, read through externs because local aggregate templates go to a pooled `.rodata` base.

Caveats: in `fn_800466B4`, `Rst1`/`RstAll`/`TchA`/`Tch1` are inline splits chosen for registers. `RESET_ALL`/`TOUCH_ALL`/`MARK_SIDE` are macros for repeated code.

## Round 16

2 more functions match (1,700 bytes), strict-reference clean:

- `fn_8002ABE0.cpp` (988 bytes): height advantage of both combatants. The terrain-map helpers and declarations are copied from `rB_8002E1C4/fn_8002AAEC.cpp`. The height difference is `hdiff(gx(a), gy(a), gx(d), gy(d))`: an inline with four `s8` parameters fed through trivial coordinate accessors (`s8 gx(BU*)`). Direct field arguments always swapped the two saved coordinate registers; the accessors fixed it.
- `fn_8002D8D8.cpp` (712 bytes): the adjacent ally that steps in to protect the defender. Direction switches as three small inlines, `cell(s8, s8)` for the map byte, and the defender's unit read through an accessor `orig(&b->b)`, which raised it from r28 to r29.

Near misses saved in `wip/`:

- `fn_8002DDD4.cpp` (static constructor of `lbl_803C8E80`, 1,008 bytes): blocks 2 and 3 match when the inline constructors take `CUnit* const&`. Block 1 still uses `sthu` and shares the loop-end register. Real classes with placement new reproduce the shape but add a null check.
- `fn_8002AFBC.cpp` (terrain bonus, 752 bytes): 6 of 188 words, only the `x + y*64` index at two sites (y<<6 wants a fresh register before `extsb x`). The same expression in `fn_8002ABE0` matches, so the difference must come from the offset being reused for the second array.
- `fn_8002B828.cpp` (battle exchange, 1,180 bytes): structure right. The original keeps every short temporary in r3 and never holds the constant 1 across `fn_80027D9C`. Ours merges the `f15e4 = 1` store with the `over()` result. `opt_propagation off` and `global_optimizer off` both move closer, so a construct is missing.

Not attempted: `fn_80027D9C` (1,284 bytes).

## Round 21 (small functions)

Totals: regs 1 function / 988 bytes. `equiv/` is new in this region.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 800437D0 | regs | 0x3DC | `equiv/fn_800437D0.cpp` | check with `--extra "-i src/game/rT_80026898 -i src/game/rT_80026898/wip -i src/game/rB_8002E1C4"` |

Real bug in the old draft (`wip/fn_800437D0.cpp`): the first team list was `{0,5,6,7,8,9,0xff}`; the original constant at 0x804CCE08 is `{0,5,7,8,9,10,0xff}`. `check_func.py -v --strict-references` prints it as "constant ... but original has"; check_regs.py only says `other`. Also: `lbl_804CA0A4` is a 7-byte .sdata string (declare it with its size to get `li r3,sym@sda21`), and the last name test is an inline that takes the pointer and dereferences it inside.

`wip/fn_8002DDD4_r21.cpp` (`other`, 251 against 252): with the context declared as a typed global and the first combatant constructed through `&lbl_803C8E80.c[0]` passed by value, the head has the original's `lis r3; addi r31,r3; sth lo(r3)`. Left: the original keeps the end of the skill array in r0 and forms `addi r3,r31,0x1bc` twice.
