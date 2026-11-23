# Region rC_8004BE18 (0x8004BE18..0x80052534)

276 of 291 functions match byte for byte. They're spread over 23 files (`fn_*.cpp`, one per run of
neighbouring matched functions). Every file prints `MATCH` with `python3 -I tools/check_func.py <file>`.
The files are **C++** (`.cpp`), and every function is `extern "C"` so it keeps its `fn_` name.

Shared headers:
- `types.h` holds the structs, the vtable classes and small inline helpers.
- `decls.h` holds the extern functions and globals, plus the inline helpers that are shared by many functions.
- `helpbox.h` holds the help-box inlines (`helpBox`, `helpBoxY`).
- `labels.h` declares every string label this region uses (message ids and sound names) as `extern char lbl_X[size]`.

Near misses are in `wip/near_misses.cpp`, each with a note on how close it got.

## Subsystem: battle-map unit command menu ("MenuCommand" table callbacks)

Almost every function here is a callback in a GBA-FE-style menu command table. Each command has
usability, effect, help-text and name callbacks:
- **Name/help strings:** `return fn_800D0864("MMM_IDROP")`. `fn_800D0864` is probably `GetMsg(const char* id)`.
  Labels in `.data` are named `MMM_*` (menu text) and `MH_*` (help text).
- **Usability:** `(cmd, menu, idx)`. It returns 0 = usable, 1 = special, 2 = greyed, 3 = hidden.
- **Effect:** `(cmd, menu, MenuEntry* e)`. When `e->active` (0x39) is set it shows the help box and returns 0.
  Otherwise it does the action and returns menu flags: 4 = proc started, 5 = close, 6, 9, 0x10 = blocked.
- `fn_800453B4(&lbl_803CA870, N)` is probably `SetNextUnitAction(state, actionId)`.
- `fn_800D5448(procScript, parent, 0)` is probably `StartProc` / `Proc_Start`.
- `fn_80253EE4("SFX_SYS_SELECT1", 0.0f)` is probably `PlaySE(name, volume)`.
- `fn_801A23E0(x, y, text, menu)` is probably `ShowHelpBox`.
- `fn_801116B8(ItemSlot*)` is probably `GetItemData`. `fn_80044FD0(&state)` is probably `GetSelectedItemSlot`.
- `fn_8011B77C(unit + 0x12C, key)` is probably `UnitHasSkill(skillList, skillId)`. The keys are sdata pointers `lbl_804CA4xx/5xx/6xx`.
- `fn_8010B228("IID_xxx")` / `fn_8010B204(id)` are probably `GetItemByName` / `GetItemById`.
- `lbl_803E7320` (0x1208 bytes) is a scratch result block. Its word 0 is checked after "simulate action"
  calls (`fn_8003A3BC`, `fn_80039AE4`, ...), and `fn_800CFB4C` / `fn_800CFD18` read results out of it.
- `lbl_803CAB38` (`FlagTable`, 0x988 bytes) is the event-flag table: names at 0x144, hashes at 0x344 and
  bits at 0x544, looked up with `fn_80076D18` (hash) and `fn_80291188` (strcmp).
  The inline chain `flagFind`, `flagGet`, `flagExists` (in decls.h) matches exactly. It is used by about 40 functions here.

## Struct layouts (see types.h / decls.h)

- `UnitCmdState lbl_803CA870` (0x130 bytes): unit at +0, unit2 at +4, action id at +0x0C (u8), selected item index at +0x0E (**s8**), cursor x/y at +0x11/+0x12 (s8), Pos8 at +0x13, flag at +0x16 (s8), +0x18 int, flag bits at +0x28.
- `Unit`: +0xF4 sub pointer, +0xF8, map x/y at +0x102/+0x103 (s8), flags at +0x10C (u32), skill list at +0x12C, `ItemSlot items[7]` at +0x1BC.
- `ItemSlot` (0x28 bytes): `ItemData* data` at +0, uses at +4, **bitfield byte** at +5 (tested with `extrwi.`, so declare `u8 f7:1 ... f0:1`, MSB first). Slot index 7 means `lbl_803CAAE0` (a temporary slot), not inventory slot 7.
- `ItemData`: +0 flags0, +4 flags4 (0x1 = weapon?, 0x4 = unusable, 0x10, 0x11 = usable/staff mask), +0x12 type, +0x1C id.
- `MenuEntry`: x/y at +0x30/+0x32 (s16), active at +0x39, index at +0x3A.
- `Menu`: +0x18 MenuProc*, +0x3C MenuOwner* (C++ object with vptr at **+4**; v60/v64 return the s16 x/y origin).
- Virtual call slot for vtable offset `off` = `(off - 8) / 4`. The classes pad with `VPAD(n)` dummy virtuals.

## Compiler quirks found (GC/3.0a5.2, C++)

1. **The code is C++.** Virtual calls (`lwz r12,0(r3); lwz r12,N(r12); mtctr r12`) only come out with real
   C++ virtuals. C function pointers put the vtable in another register.
2. **`#pragma use_lmw_stmw on`** is needed. `fn_8004CA34` is the only function in this region that uses `_savegpr_27`.
3. **`A || B` inside an inline bool helper** gives "t=1; if A goto; if B goto; t=0". A plain
   `int f = 1; if (!A && !B) f = 0;` is always rewritten to t=0 / t=1. The pattern that worked:
   `static inline u32 dataFlagB(s) { return data(s)->flags & X; }`, `static inline bool slotF4(s) { return s->f4; }`,
   then `return (dataFlagB(s) || slotF4(s)) ? 2 : 0;`. The `isUnusableA` and `isUnusableB` helpers follow it.
4. **`(x & m) == 0` and `!(x & m)` lay out blocks differently.** `== 0` keeps the early-return body right after the branch (`bne next; li r3,3; b end`).
5. **`cond ? 0 : 3` vs `== 0 ? 3 : 0`:** the first gives `neg/or/srawi/andc`, the second gives `cntlzw/extrwi/neg/clrlwi`. Choose the one that matches the asm.
6. **A function argument typed `s8`** makes the caller emit `lbz rX; extsb rY` into the argument register. `int` gives a different register pattern.
7. **Small-struct returns:** a 1-byte struct with a user copy-ctor (`Mask`) is returned through a hidden pointer (`stb r0,0(r3)`). Write `Mask m = f();` (direct init, so no copy) and pass it as `const Mask&`, because the temporaries' stack slots must line up. `bool Mask::test(const Mask&) const { return v & o.v; }` fixed an `and.` operand-order mismatch.
8. **Two-byte copy that loads +1 first:** `u8 y = p->y; u8 x = p->x; dst.x = x; dst.y = y;`. A struct assignment didn't do it.
9. **Inventory loops:** `ItemSlot* s = cmdItem(i);` with `static inline ItemSlot* cmdItem(int i) { return &state.unit->items[i]; }` got the strength-reduced offset register order. The open-coded form didn't.
10. **Inline null check:** `&unit->items[i]` followed by `s == 0 ||` gives `addic.` (a null check kept on an address).

## Round 2

Six more functions match: `fn_8004C2EC`, `fn_8004C6D0`, `fn_8004DD78`, `fn_8004FD00`, `fn_80050DE4`, `fn_80050F54`.
The help-box tail was the blocker. CW turns `call() + var` into `add rD, rVar, rCall` whichever way round you write it.
Two spellings keep the call result first: an int temporary (`int ox = o->v60(); ox + x`) or `o->v60() - -x`.
`fn_8004C2EC` also needs its locals declared at the top of the function. `decls.h` now declares `fn_80066D18` as returning `ItemSlot*`.

## Unmatched (15)

Attempts are in `wip/near_misses.cpp`.
- Help-box tails: `fn_8004C820` (14 words; two inlined copies with different registers in each), `fn_8004CA34` (2 words; saved `a6` in r29, want r31).
- `fn_80051FF4` (12 words; `&lbl_803CAB38` must be materialised before the 0x33 test).
- Register-allocation near misses: `fn_8004DE70`, `fn_8004E0A0`, `fn_8004FC10`, `fn_8004FFF8`, `fn_80050248`, `fn_800504AC`, `fn_80050744`, `fn_8005211C`.
- `fn_8004CB40`: the bit test compiles branchless. A local `bool` gets it down to 5 words, and the other spellings tried are 8-10 words off.
- `fn_8004DB80`: s8 compare against 0x1e.
- Not attempted: `fn_800512D8`, `fn_80052264`.

## Round 16

New matches (strict references):
- `fn_8004FFF8.cpp` (`fn_8004FFF8`, `fn_80050248`), `fn_800504AC.cpp`, `fn_80050744.cpp`: the item loop is an inline returning `0`/`3` directly (`useItemsR`), not a bool turned into `? 0 : 3`. `fn_80050248` also needs the loop counter and slot pointer passed by reference from function-level locals.
- `fn_800512D8.cpp`, `fn_8004C820.cpp`, `fn_8004CA34.cpp`: help-box tails written out in the function with one set of locals per copy, the y sum taken right after `v64()` (`oy = o->v64() - -y;` before the `v60()` call), then `sw.py`. `fn_8004CA34` also has `refreshProc` expanded.
- `fn_80052264.cpp` (fresh): cursor x/y kept as `int` with `(s8)` casts at the compares and index (the stores use the raw value), the failing branch first, and one function-level `CursorRef* c`.

Still open: `fn_8004CB40`, `fn_8004DB80`, `fn_8004DE70`/`fn_8004E0A0` (2 words; by-ref flag locals made it worse), `fn_8004FC10` (5 words after `sw.py`), `fn_80051FF4`, `fn_8005211C` (14 words with direct `lbl_803EC898` uses; the unit wants r31 above the map base).

## Round 17

New matches (all pass `check_func.py --strict-references`), 5 functions, 1856 bytes:
- `fn_8004DE70.cpp`, `fn_8004E0A0.cpp`: the unit argument is read through an accessor inline (`curUnit()`), passed straight to the call. A named local or a direct `lbl_803CA870.unit` read put it in r28 instead of r29.
- `fn_8004FC10.cpp`: the two tile bytes go through `s8` accessors (`rb0(r)`, `rb1(r)`). That moves the unit from r28 down to r26.
- `fn_8005211C.cpp`: the whole body is an inline `body(MenuProc* p, Unit* u)` called with a caller local `u`. Written in place, the unit ranked below the `lbl_803EC898` address temp. Passing `lbl_803CA870.unit` straight into the inline (no local) does not work.
- `fn_80051FF4.cpp`: `t = &lbl_803CAB38;` as a named local before the call (else the address was materialised after the slot kind), then a declaration-order permutation (`p, slot, e, b, i, t`) fixed the i/b swap.

The corresponding blocks in `wip/near_misses.cpp` are now stale.
Still open: `fn_8004DB80` (5 words: the `li r0,0x1e; xoris` compare survives 56 spellings and pragma combinations, including `opt_propagation off`, a named limit, an inline parameter and explicit masks), `fn_8004CB40` (size).

## Round 22

- fn_80052534 (104 bytes) exact in `fn_80052534.cpp`: the file's static initialiser (five small-data table pointers
  and an 8-byte object with base and derived vtable stores), written as plain stores plus inline constructors.
  Port: real global definitions instead of the function.

## Round 24

Targets: the functions that keep build units from linking (docs/tu_units.tsv). Unit 440 (0x8004C4C4..0x80051EFC, 243 functions) was blocked by these two only.

- `fn_8004DB80.cpp` exact (0xE8). The old draft in `wip/near_misses.cpp` had the last test inverted: the original returns 0 when `fn_801284C4(unit) >= 30` and 3 otherwise (`li r0,0x1e; xoris; subi; addc; subfe; andc` is the carry form of `a < 30 ? 3 : 0`). The 56 spellings tried earlier all compiled the wrong condition. Real bug in the draft, not in any equiv file.
- `fn_8004CB40.cpp` exact (0x58). `switch (dataFlag4(s)) { default: return 2; case 0: return 0; }` keeps the branches that `if (...) return 2; return 0;` turns into a branchless sequence.
