# Region S: 0x8023FD30..0x8024C57C and 0x8024CAD0..0x8025EBF0

239 functions match (101,928 bytes). Every `.cpp` directly in this directory prints `MATCH`. Attempts that don't match are in `wip/`.

## Files

| File | Contents |
|---|---|
| `fn_8023FD30.cpp` | 10 condition handlers on the menu global `lbl_803CA870`, and two name-list helpers |
| `fn_802414B4.cpp` | Small UI and save functions: header checks, save header init |
| `fn_8024076C.cpp` | List cursor clamp, confirm dialog start, proc creator |
| `fn_80241A00.cpp` | List window destructor and the talk dispatcher `fn_8024253C` |
| `fn_80242664.cpp` | After a talk: applies its result, restarts the map music |
| `fn_80244470.cpp` | 8 name builders ("PID_" + id table entry) |
| `fn_80244CDC.cpp` | Language switch |
| `fn_80244D90.cpp` | Root save data: `SaveR` constructor and its copies in `fn_80246100` and `fn_80247578` |
| `fn_80245104.cpp` | Bit sets, name table of 0x300 entries, event log of 30 entries |
| `fn_80245888.cpp` | Save block serializers: root and system blocks, write and read |
| `fn_80246494.cpp` | Waits for the save worker thread |
| `fn_802479A8.cpp` | Save jobs: read, verify and clear files and slots (9 functions, built from macros) |
| `fn_80248154.cpp` | Save job: write system block and one slot |
| `fn_8024B450.cpp` | 16 save-file worker thread starters |
| `fn_8024BCAC.cpp` | Top of the save stream: system block, then tagged sections (`fn_8024BD18`, `fn_8024BED8`, `fn_8024C2B4`) |
| `fn_802402B0.cpp` | Column headers of the talk list |
| `fn_80240868.cpp` | Current list item, list window inner rectangle |
| `fn_802409E4.cpp` | Talk list row draw |
| `fn_802410C0.cpp` | List cursor box and input (`fn_802412A8`) |
| `fn_80241F3C.cpp` | Creates the talk list window |
| `fn_8024212C.cpp` | Talk list proc update |
| `fn_80242920.cpp` | Writes the id tables and named data tables to the save stream |
| `fn_80242E50.cpp` | `vector<T*>::push_back` for the 8 vectors of the save header tables |
| `fn_802465E0.cpp` | Builds and writes the Wii save banner (title, banner texture, 8 icons) |
| `fn_8024CB10.cpp` | `vector<T*>::reserve` |
| `fn_80252B04.cpp` | Sets one value on every player of pool A |
| `fn_8024D810.cpp` | Sound player destructors and small locked calls |
| `fn_8024DEF0.cpp` | Pause and unpause: flag, fader, then all four player pools |
| `fn_8024F3FC.cpp` | Player pools: get, find by name, count, oldest, free slot, stop, volume, play wrappers |
| `fn_80251838.cpp` | The 7 play functions: slot, any-kind and with-argument forms, per pool |
| `fn_8025095C.cpp` | Fader setters, global and per channel |
| `fn_802510B4.cpp` | Channel fader getters and stop-all (`fn_802512C4`) |
| `fn_80256BF8.cpp` | Effect buffer resize, effect parameter copies, `fn_80257948` |
| `fn_80257154.cpp` | Command queue of the sound thread |
| `fn_80257A14.cpp` | More faders, callback setter, player has/pause/isPlaying |
| `fn_802577F8.cpp` | Locked read of one bit of the sound flag set |
| `fn_80259718.cpp` | Player update: mix parameters to the low-level handle, 7 functions |
| `fn_8025D218.cpp` | Player methods for all four classes, and more destructors |

`audio.h` declares the manager as an extern with a large `SndMutex`, for functions that use `lis/addi lbl_8042E798` directly. `sndmgr.h` defines the same memory as file statics, for functions that use a pooled base register. Use whichever the function's asm shows.

## Subsystems

**Save worker (0x80242xxx..0x8024C57C).** The strings at `lbl_80372B4C` ("CP_ATKSEQ_LIST", "PID_", "memcard.tpl", "ITBL", "MIND") point to save-file code. One thread (`+0x2C60` from `lbl_80427810`), a 0x4000-byte stack (`+0x2F78`) and one argument block (`+0x6F78`) are shared by every job.

**Sound manager (0x8024CAD0..0x8025EBF0).** Player objects sit in four pointer pools, indexed by `s8` and guarded by a virtual lock/unlock mutex. `fn_8024CCF8` is the sound thread's main loop and reads commands from a message queue.

**Save file format.** One file, written with NAND calls (`fn_80314598` open, `fn_8031490C` open for writing, `fn_80313E54` seek, `fn_80313C94` read, `fn_80313D74` write, `fn_80314818` and `fn_80314C40` close). A 0x4000-byte system block ("FE10ASYS", date 0x20061002) comes first, then slots of 0x18000 bytes ("FE10ADAT", date 0x20060920) at `0x4000 + slot * 0x18000`, and a second set at `0x94000 + slot * 0x18000`. Each block holds a CRC-32 at +0x18, computed with that field zeroed. `lbl_804CBFCC` is the last error, and -3 (busy) retries the job. The stream object is 0x14 bytes: data, cursor, size, own flag, vtable (`lbl_80380928` to write, `lbl_80380940` when destroyed).

**Talk list UI (0x802402B0..0x8024242C).** A list window (0x78 bytes, vtable `lbl_80390EF4`, built on the `fn_wf.h` widget inlines) with a `std::list` at +0x6C and its row items. `fn_802465E0` shows the banner helpers are the SDK NAND ones: `SPEED` is `NANDSetIconSpeed`, and `fn_803162AC` is `NANDInitBanner`.

## Layouts

Manager statics, as offsets from `lbl_8042E798`:

| Offset | Symbol | Contents |
|---|---|---|
| +0x000 | `lbl_8042E798` | Mutex: vptr at +0, lock at vtable +0x08, unlock at +0x10 |
| +0x060 | | Passed to `fn_802AB9E4` when a player is built |
| +0x0FC | `lbl_8042E894` | Sound group table (`fn_802AD3C0`, `fn_802AD3B0`) |
| +0x294 | `lbl_8042EB24` region | Effect state; config at `lbl_8042EB24` and `lbl_8042ECBC` |
| +0x5F0 | `lbl_8042ED88` | Pool A, 4 players |
| +0x600 | `lbl_8042ED98` | Pool B, 16 players |
| +0x640 | `lbl_8042EDD8` | Pool C, 16 players |
| +0x680 | `lbl_8042EE18` | Pool D, 4 players |
| +0x690 | | `SndFader` array; +0x690 default, +0x6B8 and +0x6CC used by pause |
| +0x758, +0x7F8 | `lbl_8042EEF0`, `lbl_8042EF90` | Channel faders, 8 each; two more arrays follow |
| +0x1D30 | | Command message queue |
| +0x1DB0 | `lbl_80430548` | Second mutex, for the command list |
| +0x1DD0 | `lbl_80430568` | `SndCmd` list, 16 bytes each; `lbl_804CBFF8` is the count |

`SndFader` (0x14 bytes): `t`, `frames`, `cur`, `from`, `to`. `frames` is `ms / 16.666666f`.

Player object:

| Offset | Contents |
|---|---|
| +0x04, +0x08 | Manager +0xFC and +0x294 |
| +0x0C | Config from `fn_80076F54`; first word is the name |
| +0x18..+0x3C | Four floats at 1.0, six at 0.0 |
| +0x40, +0x44 | Randomised pitch and pan |
| +0x48, +0x49 | `s8` -1, pause countdown |
| +0x50 | `OSGetTime` at creation |
| +0x58, +0x5C | Config +0x1C, low-level handle |
| +0x60 | Member object (`fn_802AB9E4`, destroyed by `fn_802ABA74`) |

Player vtable slots: +0x08 destroy(1), +0x10 isActive, +0x18 isReady, +0x20 start, +0x24 stop(int), +0x28 and +0x2C setters, +0x34 canSetB, +0x38 fadeTo, +0x94 startTime, +0x98 remaining, +0xB0 setArg. Base vtable is `lbl_80391780`. Derived vtables include `lbl_803916C0`, `lbl_80391540`, `lbl_803913C0`, `lbl_80391240`, `lbl_80391180`. `lbl_80391888` is the scoped lock's vtable.

**Sound flags.** `lbl_804CBFE8` is a bit set with its words at +4, not a pair of u32s. `fn_802577F8` tests any bit. A constant bit such as 0 or 2 folds to `clrlwi` or `extrwi`, and the unused search loop is what leaves `li rN, lbl@sda21` behind. The save data's bit sets use the same loop. The loop only compiles right with a local copy of the index: `u32 q = n; while (q >= 32) { q -= 32; p++; }`.

**Player update.** `fn_80259718` and its three copies take the same body with a different minimum volume constant. `fn_8025A0C0`, `fn_8025B218` and `fn_8025C2C4` wrap that body in a second check and guard (a base update inlined into a derived one). The first and last of those then set a value through a handle object, `fn_802BAC48` or `fn_802AA628`. `fn_80258C70` adds distance attenuation: position through the matrix at +0x98, then `(distance - fader +0x9EC) / fader +0xA00`.

Config (`SndCfg`, partly known): +0x00 name, +0x0A `s16`, +0x0C `s8` semitones, +0x15 instance limit, +0x16 and +0x18 random range, +0x1A and +0x1B pan range, +0x1C `u16`.

MSL string: top bit of word 0 means long; long size at +4, long data at +8; short size is the low 7 bits of byte 0, short data at +1. `fn_800250B0` is the replace function.

## Source that may differ from the original

- **`goto` loops** in `fn_8024FBAC`, `fn_80250068`, `fn_80252984` and their siblings. A `for` loop stopped the mutex address being hoisted.
- **A mutex pointer assigned inside the loop** (`m = &lbl_8042E798;`) in the same functions.
- **`RawGuard` in `fn_8024DEF0.cpp`** replaces a real scoped lock with explicit on/off calls, so the stack slots come out ascending.
- **Hill-climbed declaration orders** in `fn_802512C4` and the four functions in `fn_8024DEF0.cpp`. They say nothing about the original source.
- **Mixed loop forms in `fn_802512C4`.** Pools A to C use explicit pointer variables and pool D an index, only to get the registers right.
- **Uninitialised values kept on purpose:** `ok` in `fn_80257154`.
- **Guessed names:** every class, method and field name here comes from behaviour. The job argument block (`JobArg`) is only partly understood.
- **`fn_80257948`:** the buffer is 0x30 bytes, but 0x28 and 0x2C also match, so the real size is unknown.
- **Split manager statics in `sndmgr.h`.** `sMember60`, `sEffect` and the `sGroups` size exist only to give those offsets their own symbols; the original more likely had one object. `sGroups` is deliberately short with `sPad288` after it, because a size divisible by 8 forces 8-byte alignment.
- **`ok = 0; w.own = ok;` in `fn_80248154`** is how the source was made to colour the flag first. A constructor is the likelier original.
- **`goto done` in the save jobs** stands in for whatever the original control flow was, and `fn_8024B0B4` and its siblings come from macros that may have been inlines.
- **`case 0x80: break;` in `fn_80242514`** is a placeholder for an elided lowest case; the real label is unknown.
- **`info[0x24]`** in the save jobs is sized to give the frame; the real NAND file structure is probably larger and laid out differently.
- **`#pragma inline_max_size` in `fn_80251838.cpp`** and the `create` inline holding every case's guards are there to get the stack slots in order.
- **Update family (`fn_80259718.cpp`).** The bodies are macros. The second-guard forms use `RawGuard` and `goto out` in place of what was almost certainly an inlined base method; a real inline gets the stack slots right but the float registers wrong. `cb`, `cb2`, `mm` and `rr` are written out because the `getCb` and `fMax` inlines (the likelier original) change the registers.
- **Root save init (`fn_80244D90.cpp`).** One constructor as a macro with two ways of writing the point resets and the functor, chosen per function to get the stack slots. `LogE::clear` is a placeholder name: each copy has its own pointer-to-member template with the same value, and the checker doesn't check `__ptmf_scall`.
- **Log entry search (`fn_80245614`).** The stepped `SaveLog*` is only there to produce the `0x1900(rN)` offsets. The `if (i >= 0)` chain in `fn_802452B4` stands for nested inlines.
- **`fn_8024BED8`.** The zeroing of the 0x6C-byte object is written word by word, and `blobFree` has four nested null tests to reproduce the repeated `beq`. It's probably a real class with a destructor.
- **Hand word copies in `fn_802402B0`.** `*(u32*)&t1 = *(u32*)&c` with named locals stand for what were probably by-value colour arguments, only to get the stack slots.
- **`gi()` and `s16 ty` in `fn_802410C0`,** and the `volatile` double read in `inputBlocked` (`fn_802410C0.cpp`, `fn_8024212C.cpp`), are there for register rank and load shape.
- **`setR` in `fn_80240868.cpp`** is a guess at a rectangle setter; `fn_802419AC` only colours right through it.
- **`rS_poolDummy` in `fn_80242E50.cpp`** exists to give the pooled strings their offsets. It emits a real function and should go once the string pool is real.
- **`const char* s = lbl_80372B4C`** in the save stream functions stands for string literals; the checker sees the references this way.
- **Statics not fully reference-checked.** References through the `sndmgr.h` and `fn_8024B450.cpp` statics print as `...bss.0`, so the checker compares their offsets but not their base address. The base is `lbl_8042E798` or `lbl_80427810` by reading the asm.

## Resume point

Best next targets, by bytes:

1. **Near misses in `wip/`, all registers or a single puzzle:** `fn_8024044C` (0x320, 20 lines: wants `cfg` and `node` in r20 with the string size in r17), `fn_80240CD8` (0x3E8: needs the `extsh r4,r29` on each unroll guard with the counter a raw `mr r5,r29`), `fn_8024CCF8` (0x254: right shape, ranks of the constants and pointers off), `fn_80246E68` (7 words, first instructions), `fn_80246ADC` (7 words, r26 and r27), `fn_80248CCC` (5 lines) and `fn_8024A410` (the 0 or 1 held in a saved register across calls), `fn_80258C70` (12 words, float registers), `fn_80240814_a` (0x54, cursor row point).
2. **Unstarted:** `fn_8024953C` (save job, reads and verifies one slot), `fn_802414C4` (builds the scroll bar and its two effect members), `fn_8024CF54` (0x8BC), `fn_80257CC8` (0xDA4, the manager's per-frame fader update).
3. **Skipped:** `fn_80241BF0` holds the `lbl_8038C1C0` constructor, the known dead end from `MATCHING.md`. `fn_8024C57C` has no `.fn` entry in the text asm files.

## Round 16 (1 function, 3,492 bytes)

- `fn_80257CC8.cpp` (+ `fn_80257CC8.symbols.json`, `...bss.0` = `lbl_8042E798`): the manager's per-frame update. Faders through one `upd(SndFader&)` inline returning `cur`, the flag test and set as the `fn_802577F8` loop inlined, the four player pools through a `POOL` macro. Check with `--symbol-map fn_80257CC8.symbols.json --strict-references`.
  - The products must be written as `base = upd(a); base *= upd(b); base *= upd(c);`; `upd(a) * upd(b) * upd(c)` calls `c` first.
  - The 8-step channel loops need an `s16` counter: an `int` counter merges the two unrolled increments.
  - In `POOL`, the locals are declared `s, p, m, i` (reverse of their target registers r27..r30).
  - Caveat: includes `sndmgr.h`, whose `rS_sndKeep` is the existing layout-keeping helper (not new, not in symbols.txt).
- New WIP: `wip/fn_8024CF54_r16b.cpp` (manager init, 18 of 559 words, pool-clear counters r26 vs r24). It defines its own statics instead of `sndmgr.h`, split at +0x28, +0x294, +0x38C, +0x524, +0xA18, +0xD30, +0x1D50 so each block is addressed straight off the pool base. Rules found: unreferenced bss statics are kept, statics of 8 bytes or less go to .sbss (so they can't pad the pool), and any static whose size is a multiple of 8 is 8-aligned, so split blocks to avoid that. The NW4R `LinkList::PushBack` with its null assert reproduces as `endIter()` into a local, then `nodeOf(p)` with the assert, called on the static directly (`((Obj60*)sMember60)->list.pushBack(...)`), not through the cached pointer.
- New WIP: `wip/fn_802414C4.cpp` (talk list scroll bar, 17 of 314 words; volatile registers of three constants in the bar constructor). `int z = a26;` before the first `wfInit` and `int x, h` locals fixed the rest; `setPos(e, x, y, z)` fixed the arrow stores.
- `fn_80258C70`: rewriting it on the matched `UPDATE2_FN` body from `fn_80259718.cpp` (with the distance code as the tail) scores worse than the old WIP (the tail floats push the base's temporaries to f29). Not kept.
- Skipped as instructed: the save-job retry-loop family (`fn_80246E68`, `fn_80246ADC`, `fn_80248CCC`, `fn_8024A410`, `fn_8024953C`, all with `cmpwi -3` retry loops) and `fn_80241BF0` (`lbl_8038C1C0` constructor).

## Round 19

Two functions newly at `regs` level (2,832 bytes), in `equiv/` (check with
`--extra "-i src/game/rS_8023FD30 -i src/game/rS_8023FD30/wip"`):

| File | Function | Bytes | What changed |
|---|---|---|---|
| `equiv/fn_8024CF54.cpp` (+ `.symbols.json`) | fn_8024CF54 | 2,236 | r16b wip with the four channel pointers declared `a, b, c, d` (was `a, b, d, c`) |
| `equiv/fn_8024CCF8.cpp` (+ `.symbols.json`) | fn_8024CCF8 | 596 | the manager block `lbl_8042E798` written as separate pooled statics (as in fn_8024CF54) instead of one `Mgr` struct: the command mutex address is then rematerialised per use like the original |

Both use file-local statics for the sound manager block (`...bss.0` = `lbl_8042E798`), each with its own partial
layout. A port needs one shared definition (the full layout is in `equiv/fn_8024CF54.cpp`).

Left as `other`:
- `fn_80240CD8`: with `it = adv(w->first, top)` (no `(s16)` cast at the call) 3 instructions are missing instead of 4
  hunks: one `mr r5,r29` copy and two re-extensions `extsh r4,r29`. Parameter types, `s16 top`, and a two-level
  `std::advance` shape did not produce them.
- `fn_80248CCC`, `fn_8024A410`: still the 0 / 1 kept in a saved register and reused for `w.own` / `ok`.
- `fn_802414C4`, `fn_80246E68`: several stores and constant loads scheduled a slot apart, tied to volatile registers.
- `fn_80240814`: not examined further. Not attempted: `fn_80241BF0`, `fn_8024953C`, and the two static
  initialisers `fn_8024C57C` and `fn_8025EBF0`.

## Round 19b (sched class)

Two functions added to `equiv/` (1,340 bytes), both existing wip files that now class as `sched` (moved instructions checked with dd.py
and listed in the file headers):

| File | Function | Bytes | Moved |
|---|---|---|---|
| `equiv/fn_802414C4.cpp` | fn_802414C4 | 1,256 | `lis`/`addi` of two vtable addresses, one `lfs`, `li 0x10` in the constructor block; stores keep their order |
| `equiv/fn_80240814.cpp` | fn_80240814 | 84 | LR save, two stack addresses and four independent `lha` loads interleaved differently |

`fn_8024CF54_r16b` also classes as `sched` but the function is already in `equiv/` at `regs`. Not attempted: `fn_80241BF0`,
`fn_8024953C`, `fn_80240CD8`, `fn_80248CCC`, `fn_8024A410`, `fn_80246E68` (unchanged from the Round 19 list above).

## Round 21 (small functions)

Checked with `python3 -I tools/check_regs.py <file> --extra "-i src/game/rS_8023FD30 -i src/game/rS_8023FD30/wip"`.

Totals: exact 2 functions / 2464 bytes, sched 1 / 736.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 8025EBF0 | exact | 0x300 | `fn_8025EBF0.cpp` (+ `.symbols.json`, check with `--symbol-map`) | static initialiser of the sound manager statics, hand-written over the pooled statics of `equiv/fn_8024CF54.cpp` |
| 8024953C | exact | 0x6A0 | `fn_8024953C.cpp` | copy one save slot to another; written from the asm with the helpers of `fn_80248154.cpp`; the argument is `{s8 from; s8 to;}` |
| 80241BF0 | sched | 0x2E0 | `equiv/fn_80241BF0.cpp` | two widget constructors (fn_wf.h style); string literals under `#pragma pool_strings on`; symcheck clean |

Layout facts from 8025EBF0 for `lbl_8042E798`: destructor-chain records at +0x1c, +0x54, +0x88, +0xf0, +0x288, +0x380, +0x518; objects at +0x28 (heap), +0x60, +0x98, +0xfc, +0x294 (effect: vtables `lbl_80391840` and +0x14, floats 1/0/0 at +0xe0), +0x38c, +0x524; the default fader at +0x690 starts at 1.0, all others at 0.0; the command mutex at +0x1db0 has the same vtable as the main lock.

Not done: 8024C57C (1.4 KB static initialiser with inlined constructors, a pointer-to-member loop and dead stores; not started), 80240CD8, 80248CCC, 8024A410 (unchanged; `#pragma opt_propagation off` on the two save functions does not give the kept 0/1 register, it changes six other instructions), 80246E68 (already `sched` in docs/EQUIVALENT.tsv from its wip file).

## Round 22

- fn_8024C57C (1364 bytes): complete draft in `wip/r22/fn_8024C57C.cpp`, class `other`. The save-worker file's
  `__sinit`: constructs SaveWork (pool +0x10: serialisable value members with vtables lbl_80391160/lbl_8037F7E0, 30
  elements of 0x18 bytes, an inlined Clear() with a pointer-to-member Reset() loop over the elements through
  __ptmf_scall) and the object at pool +0x1BF0, and registers both destructors. Hand-written over the pool layout of
  fn_8024B450.cpp; the original's unrolled constructor loops and store schedule are compiler output from the class
  definitions. Same stores and calls (checked by hand against the asm; see the file header).
- fn_8024C57C now has its own asm file (`build/RFEE01/asm/auto_fn_8024C57C_text.s`); the older note saying it has no `.fn` entry is out of date.
