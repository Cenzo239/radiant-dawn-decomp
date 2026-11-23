# Region rP (0x80105B04..0x80106B84 and 0x80106CA8..0x80112B00)

154 functions match byte for byte, 0x91A0 (37,280) bytes. None is in `build/m2c/matched_names.txt`. Each file prints `MATCH` with `python3 -I tools/check_func.py <file> -v`.

When work started, 167 of the 246 functions (47,564 bytes) had no match. 14 functions (10,576 bytes) are still open.

| File | Matches | Contents |
|---|---|---|
| `fn_80105B04` | 4 | Save time as hours, minutes and seconds; save header lookup; save buffer allocation |
| `fn_80106E30` | 1 | Kind-to-value switch |
| `fn_80106F98` | 9 | Biorhythm: sine curve, peak and trough times, bands |
| `fn_80107864` | 5 | Biorhythm bonuses, item row drawing |
| `fn_80108660` | 9 | Item accessors, weapon-triangle table load and lookup |
| `fn_8010889C` | 23 | `Hist`: per-unit packed status counters |
| `fn_8010940C` | 3 | Options record: save, load, apply |
| `fn_80109A2C` | 4 | Big-endian stream readers |
| `fn_8010B094` | 10 | Item table lookup, name prefix parsing, placement check, record loader |
| `fn_8010C8EC` | 8 | Deployment files, spawning, deployment process steps |
| `fn_8010DB48` | 10 | Resource load and free, side lists, side relation mask |
| `fn_8010E27C` | 2 | Side list unlink and count |
| `fn_8010E9AC` | 19 | Difficulty-scaled balance constants |
| `fn_8010F64C` | 6 | Article ("a" or "an") for item names, weapon type names |
| `fn_8010F73C` | 2 | String-to-enum tables |
| `fn_80110D38` | 1 | Slot clear |
| `fn_801116B8` | 16 | Slot values, item hook table, slot copy and load, forge prices |
| `fn_80105EB0` | 1 | Save header copy |
| `fn_80107AE0` | 1 | Item name and uses row |
| `fn_80108678` | 2 | Mutually recursive slot colour getters |
| `fn_80109B18` | 2 | Table start-up, no-battle table relocation |
| `fn_8010B964` | 10 | Deployment path search, file list build, unit placement, deployment process steps |
| `fn_8010F988` | 2 | Item id to sound class, trait name to flag bit |
| `fn_80110F08` | 2 | Slot display name, weapon rank string parser |
| `fn_80111FE4` | 1 | Forged name store with scaled width |
| `fn_801125B4` | 1 | Forge colour |

Shared headers: `rp.h` (includes the `rH` basic types) and `slot.h` (`Slot`, `ItemD`, `IconFont`). Several files declare their own narrower view of the same struct. All names are guesses from behaviour.

## Subsystems and struct layouts

- **Biorhythm.** `lbl_80367F28` is the string `BioParam`, and +9 is `BioData`. `BioData` has one 0x10-byte row per curve, `{amp, scale, freq, base}`. `BioParam` has 0xC-byte rows, `{f32 limit, u8 bonus[8]}`. On a unit, +0x378 is the curve (negative means use `Person+0xE4`), +0x37A the phase (negative means `Person+0xE5`) and +0x37C the time. Value = `amp * scale * sin(freq * 2pi*t/100 + 2pi*phase/100) + base`.
- **`Hist`** (4 bytes, MSB first). Word 0 is `f4:3 f3:3 f2:3 f1:3 f0:3 lock:1`. Word 1 is `g3:2 g2:2 g1:2 g0:2 h1:3 h0:3 lo:2`. The logical order is f4, f2, f1, f3, f0, lock, g3, g2, g1, g0, h1, h0. Setters ignore the call when `lock` is set, and they add 1 to the value when the unit isn't on the current side (`lbl_803CAB38+0x11`). `fn_80108E20(h, 1)` counts every field down by one.
- **Inventory slot** (0x28 bytes, the same as `Inv` in `rH`). +0 item, +4 uses, +5 flag bits (0x80, 0x40, 0x20 forged, 0x10, 8, 4), +6 forged name (0x18 bytes), +0x1E might, +0x1F hit, +0x20 crit, +0x21 weight, +0x22 colour, +0x26 0xFF. The word at +4 is written to saves as a u16 (uses and flags).
- **Item data.** +0 name, +4 id, +0xE index, +0x10 price, +0x12 type, +0x15 article override, +0x16 icon, +0x1B max uses, +0x1E/+0x1F (`fn_801080CC`), +0x38 u64 flags. When a slot has no item, `fn_801116B8` returns a zeroed default at `lbl_804CB7F0`, guarded by `lbl_804CB7E8`.
- **Item hooks.** `fn_80111850` builds a name from the item name plus the suffix at `lbl_803680E8+0x657`, caches it in `lbl_803EC390`/`lbl_804CB7F8`, and looks up a function table: +0, +8, +0xC, +0x10.
- **Icon font.** `lbl_803E7290` and `lbl_803E72D8` have data, then a vptr at +0x44. Slots are at +0x18 and +0x1C.
- **Item table.** `lbl_804CB7D4`, count `lbl_804CB7D0`, 0xB4 bytes per entry. +0x14 and +0x30 are string arrays with `/X` option suffixes.
- **Deployment files.** The header is `{count, kind}`, plus two more bytes when kind is 7, then alignment to 4. `fn_8010BCBC` reads a 0x68-byte record: +0 tag, +4 unit id, +0xC side, +0xE/+0xF start position, +0x10/+0x11 target position. The `Hdr` inline in `fn_8010C8EC.cpp` is the shared header read. `lbl_803EC1D0` is `{lock, n, ids[]}`.
- **Save files.** Magic `FE8J` at +0x40, version 0x20050201 at +0x44, +0x60 kind, +0x62 slot, +0x63 linked slot. Slots sit at buffer +0x2000 + i*0x4000. The second bank starts at +0x1A000, with a stride of 0x6000.
- **Balance data.** `fn_80076F54(lbl_803680D8)` returns a table indexed by difficulty (`lbl_803CAB38` through `fn_80060728`, +0x11). `DiffIdx` maps the value to a table index: 3 to 0, 0 to 1, 1 to 2, 2 to 3, anything else to 0. Which difficulty each value means is not known.

## Caveats: matches that may not reflect the source

- `fn_8010F598` takes `volatile u8*` to force the second load. The original is more likely a bitfield test next to a bitfield store.
- `lbl_804CB7F8` is declared `const void* const` and written through a cast, because that reproduces the load being hoisted above the stack saves. The original is probably a different construct.
- `Hist` chain assignments (`h->f1 = h->f0;` and so on) read oddly, but they reproduce the `rlwimi` runs. They may have been `a = b = c = 0`.
- In the `Hdr` inline, the empty `case 0..6` labels exist to get `cmpwi 7; beq; bge; b`. The real switch may have had other cases.
- `fn_80107C80` declares its callee's last parameter as `char*`, because the near miss `fn_80107AE0` reuses that register. Only the call matters for the match.
- `fn_80105DC0` calls `__div2i` through the compiler's own 64-bit divide, so the checker notes that reference as unchecked. It's `fn_8028C418` in the original.
- Declaration orders in `fn_8010D018` (in wip) and in the wip job loader came from random search, so they say nothing about the original source.
- All prototypes of functions outside the region are guessed from call sites.

## Near misses

`wip/near.cpp` and `wip/fn_8010A2FC.cpp` are older and aren't compiled. Entries in `near.cpp` for `fn_8010D018`, `fn_80105EB0`, `fn_80107AE0`, `fn_80111FE4`, `fn_8010CDB4`, `fn_8010D4E8`, `fn_8010D684` and `fn_8010D770` are stale: those functions now match in the files above.

| Function | Words left | What's wrong | Attempt |
|---|---|---|---|
| `fn_8010A2FC` | 8 of 407 | The hoisted 0 takes r31 where the original has it below the locals (r26), and the second count takes r26 where the original has r31 | `wip/fn_8010A2FC.cpp` |
| `fn_8010A958` | 23 of 349 | The same swap as `fn_8010A2FC` | `wip/fn_8010A958.cpp` |
| `fn_80109DF8` | 2 of 321 | Two `addi` swapped. Also needs a pragma against unrolling (see caveats) | `wip/fn_80109DF8.cpp` |
| `fn_80112364` | 8 of 148 | Each `fctiwz` has its own stack slot in the original; ours reuses one, so the frame is 0x20 smaller. It's the four `fn_801120C0` family bodies inlined | Not saved. Write them as inlines and add the results in a linear chain |
| `fn_80107DC4` | 7 of 88 as saved | Wants `clrlwi r5,r29,24` on the colour. Without the `PriceCol` inline it gets to 2 words, with `mr r5,r29` | `wip/fn_80107DC4.cpp` |
| `fn_80107F24` | about 30 of 73 | The flag local should be r31 with the parameters at r27..r30 | `wip/fn_80107DC4.cpp` |
| `fn_801080CC` | 46 of 144 | Registers only: the colour should be r26 below the parameters, ours r31 above them | `wip/fn_801080CC.cpp` |
| `fn_801116F4` | 15 of 87 | One swap | `wip/near.cpp` |
| `fn_801095FC` | 12 of 82 | Constant registers | `wip/near.cpp` |
| `fn_80105BBC`, `fn_80106190` | many | First attempts | `wip/near.cpp` |

## Resume point

1. The rank puzzle shared by `fn_8010A2FC` and `fn_8010A958`. Declaration order, block scope, `int`, `u8` and `const` counts, inline parameters and about 30 optimiser pragmas didn't move it.
2. `fn_8010830C` (0x30C) starts like the colour getters. Ghidra shows the draw calls.
3. `fn_801062C0` (0x768) hasn't been read. `fn_80106B84` isn't in the `auto_03` asm files that `tools/perm/lib.py` searches, so read it from Ghidra.

To list what's missing, subtract the checker's `OK` names and `build/m2c/matched_names.txt` from the `.fn` names in the two asm files.

## More caveats from the later round

- `fn_8010BED8` names `m3 = fl & 3` and `m4 = fl & 4` as locals because that gives the hoisted masks their register rank. `fn_8010D770` and `fn_8010D8B4` use explicit stepped offsets and `while (*(const u8*)p != 0x40) d = *p++;` for the same kind of reason.
- `fn_8010D184` has hidden parameters `a` and `b`, passed on to `fn_8010B964`. `fn_8010D4E8` and `fn_8010D770` pass the count and the list. What `fn_8010B964` does with them isn't known.
- `fn_8010B964` takes `s8* px, u8* py` to reproduce the mixed byte reads. They're almost certainly both one type in the source.
- `fn_801125B4` uses non-const file statics for its 10 colours. The original reads them from `lbl_804CDC68`, 0x28 bytes in `.sdata2`. A const static lets the loads move up, and indexing an extern hoists a base register. The checker confirms the values, but this file's data would not link to the original address.
- `fn_80108678`, `fn_80108774`, `fn_80110F08` and `fn_801125B4` write the recursion levels by hand as inlines, and use `T1()`/`T2()` wrappers purely to set stack slots. The temp colours return the address of a local. That is what the code does, but the real source is probably a reference-returning inline.
- `fn_8010AF44` and `fn_80109B18` model the stream as a plain struct plus a cast to a class with a vptr at +0x10, so virtual calls stay indirect.
- `wip/fn_80109DF8.cpp` uses `#pragma ppc_unroll_factor_limit 1` and an `s16` dead counter. That pragma isn't likely to be in the source: something probably made the loop body too big to unroll.

## Compiler lessons from this region

- **`(f32)fn() * x`:** `a * b * (f32)sin(v) + d` gives `fmadds f1,f0,f1,f31`. Assigning the call to a float local first swaps the operands.
- **Two conversions in one expression:** CW may evaluate the more complex side first. Separate float locals fix the order.
- **Sign helpers:** `s = 0; if (s < m) ...` written as an inline taking `m` fixes register choices that no declaration order could.
- **Unsigned range switch:** on a `u8`, an empty `case 0..6` with `case 7` gives `cmpwi 7; beq; bge; b`, because the low bound test is dropped.
- **`int` inline parameter:** `FindByTag(int tag)` fixed a whole-function rotation that `u16 tag` caused.
- **Devirtualization:** a virtual call on a declared global object compiles to a direct call. Go through a cast from a `u8[]` extern.
- **`u8 == -1`:** `lbz; cmpwi r0,-1` with no `extsb` is exactly that always-false comparison, so keep it. `fn_80105EB0` has one.
- **Unrolled byte loops:** the 6-byte copy with `ctr = 5` and the 10-step `ctr = 3` scan are plain 0x1E-count `for` loops.
- **Field stores before bitfields:** in `fn_80109744`, plain byte stores written before bitfield stores match, even though the asm's bitfield loads come first.
- **Hidden arguments again:** `extsb r3,r0` and `extsb r4,r0` beside plain `extsb r0,r0` in a range test meant `x` and `y` were arguments to a later `fn_8012CF28(x, y)`. The same check on `fn_8010D184` showed its r5/r6.
- **Two-word `ori` chains:** a string chain with `or` through `lis; addi` in a few blocks is a `u64 |= ...ULL` in every block.
- **Rank of hoisted constants:** a direct `lbl.w` member gave the `lis`/`addi` of the global its top rank, ahead of hoisted `li` constants, where a cast didn't.
- **`(cap / w)`:** when two conversions come out reversed, check the division isn't simply the other way round. `fn_80111FE4` was wrong for that reason.

## Round 16

One new match: `fn_80106B84.cpp` (292 bytes), the system save header ("SYSF", version 0x20050201) reset with a time-based seed, then marked invalid. Its `SysInit` inline is also the tail of `fn_801062C0`. Passes `--strict-references`.

`wip/r16_fn_801062C0.cpp` is a full draft of `fn_801062C0` (1,896 bytes, the save-slot validation pass): 23 of 474 words left, all register ranks in the first slot loop (see the file's comment). Helpers it needs and that match: `Valid` (FE8J header), `SysValid`, `CrcOk` (the 0x12345678 / x60 == 1 shortcuts, then the checksum through `fn_80079A6C`), `Time` (`n > 0x100000 ? 0 : n`). Findings while writing it:
- Offsets written as `b->base + o` with a stepped `o` match the slot loops that make calls; the call-free cleanup loop wants `b->base + (i * 0x4000 + 0x2000)` and the scan loop a cached `base`.
- `o5 += 0x6000, i5++` (offset step first) fixes the increment order in the bank-2 loop.
- A string literal `""` in place of `lbl_80367E9C` (which starts with an empty string) folds the address and loses a saved register, so that pool is referenced through the extern.
- A wrapper around the whole body made it much worse (153 words), and `tys.py` found nothing.

Not retried: `fn_80109DF8` (2 words; 15 rounds of `rr.py` plus loop-form, counter-type and walker variants did not swap the two `addi`s), `fn_8010A2FC`, `fn_8010A958`, `fn_8010830C`.

## Round 19

Two functions newly at `regs` level (1,744 bytes), in `equiv/` (check with
`python3 -I tools/check_regs.py <file> --extra "-i src/game/rP_80105B04 -i src/game/rP_80105B04/wip"`):

| File | Function | Bytes | What changed |
|---|---|---|---|
| `equiv/fn_8010A958.cpp` | fn_8010A958 | 1,396 | wip with `j += 0x50` before the 4-byte alignment of the read pointer |
| `equiv/fn_801116F4.cpp` | fn_801116F4 | 348 | near.cpp fragment + `fn_801116B8.cpp` declarations |

Left as `other`:
- `fn_80109DF8` (1 swap): the two-entry pair loop keeps a dead counter (`li r8,0` ... `addi r8,r8,1`) that the
  original increments after the pointer. An `int` counter is removed entirely; an `s16`/`u8` one stays but is
  incremented first. Index forms, struct arrays, do/while and reusing other locals did not give the original.
- `fn_801080CC`: the last call passes the highlight flag with `mr` (ours `clrlwi`); u8/bool/int flag types and
  reusing parameter `a` for the compare result did not change it.
- `fn_801095FC`: only `stw r0,0x14(r1)` and `li 0x14` swap in the prologue; moving the `x9` store through all 18
  positions of the bitfield block did not help.
- `fn_80106190` and `fn_80105BBC` (near.cpp fragments, now compile with `fn_80105EB0.cpp`): frame size and a hoisted
  constant differ (6190), loop structure differs (5BBC). `fn_80107DC4`, `fn_80107F24`: unchanged.
- Not attempted: `fn_8010830C`, `fn_80112364`.

## Round 19b (sched class)

One function added to `equiv/` (1,284 bytes): `equiv/fn_80109DF8.cpp`, fn_80109DF8, `sched`. It is the wip unchanged; the only
difference is the dead pair-loop counter `addi r8,r8,1` placed before the pointer step instead of after it (checked with dd.py).

`wip/r19b_fn_80112364.cpp` (new, self-contained, `other`): all 148 instructions are the original's, but the original gives each of the
four float-to-int conversions its own stack slot (0x18, 0x20, 0x28, 0x30, frame 0x40) and ours reuses 0x18 (frame 0x20). One
expression, a `r +=` chain, four named results, wrapper inlines of different depths, auto-inlined real functions and float-returning
parts cast in the caller all give the same frame. Functionally identical.

`fn_8010A958` (wip) also classes as `sched` but is already in `equiv/` at `regs`. Not attempted: `fn_8010830C`, `fn_80105BBC`,
`fn_801095FC`, `fn_801080CC`, `fn_80106190`, `fn_80107DC4`, `fn_80107F24` (unchanged from the Round 19 list above).

## Round 21 (small functions)

Checked with `python3 -I tools/check_regs.py <file> --extra "-i src/game/rP_80105B04 -i src/game/rP_80105B04/wip"`.

Totals: exact 1 function / 292 bytes, regs 2 / 1084, slots 1 / 780, sched 1 / 328.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 80107F24 | exact | 0x124 | `fn_80107F24.cpp` | the x and y arguments of the text call go through two `s16` locals before the colour is chosen |
| 801080CC | regs | 0x240 | `equiv/fn_801080CC.cpp` | `a = lv <= have;` inside `if (a)`, then `hl = a != 0;` after it (explains the `mr` the round 19 note could not get) |
| 80105BBC | regs | 0x1FC | `equiv/fn_80105BBC.cpp` | two nested search inlines returning the entry or NULL, base pointer passed as a parameter |
| 8010830C | slots | 0x30C | `equiv/fn_8010830C.cpp` | fn_80108678 inlined six levels deep; the six default-colour temporaries are in other slots; symcheck flags 4 blocks, explained in the header |
| 801095FC | sched | 0x148 | `equiv/fn_801095FC.cpp` | prologue pair swapped; symcheck clean |

Complete drafts at `other`:
- `wip/fn_80107DC4_r21.cpp`: 88 instructions as the original, right registers; the colour argument is passed with `mr` here and `clrlwi r5,r29,24` in the original, one slot later.
- `wip/fn_80106190_r21.cpp`: 73 against 76; the original has a dead `li r3,0` and one more saved register (probably a 64-bit operand of the ticks-per-hour product). Nine spellings of the product gave the same code.

The static initialiser of this unit, fn_801059EC, is in rE (`rE_800E5DE4/fn_801059EC.cpp`, exact); it shows the unit's statics: a 16-entry item array object at `lbl_803E8FF0+0x10`, a 12-byte object at +0x298, a 300-entry item pool at +0x2b0 and five `{count, pointer}` spans over the pool at `lbl_804CB750..804CB770` (300 all, 100/100/100, and 200 from entry 100).

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`; symcheck `--anon --xargs` clean):

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_801080CC.cpp` | fn_801080CC | 0x240 | the highlight flag `hl` typed `u8` instead of `u32` (type search over locals and parameters) |

Tried in round 23 without an exact result: fn_801095FC (bitfield init order a0, a3, a5 first and x9 first gets 5 words;
`li r0,0x14` still takes r6; 41 positions of the x9 store).

## Round 24

- fn_80112364 (8 words, one fctiwz stack slot where the original has four): a named int or f32 result in each part, four named part results added at the end: no change.
