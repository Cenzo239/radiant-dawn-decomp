# Region rH_80112B48 (0x80112B48..0x8013157C)

424 of 462 functions match byte for byte, about 79% of the region's code by bytes (about 26 KB left in 38 functions). They are in 100 `.cpp` files, and each file prints `MATCH` with `python3 -I tools/check_func.py <file>`. Near misses are in `wip/r14_*` (newest), `wip/r10_*`, `wip/near.cpp` and `wip/r7_*`, each with a comment saying what is left. Some `near.cpp` and `r7_*` entries are now solved, so check the list of matched functions first. Nothing in `wip/` is compiled, and its externs aren't complete.

Shared headers: `types.h` (basic types, `Vec`), `map.h` (`Map`, `MapNode`), `unit.h` (`Person`, `Job`, `Inv`, `Unit`, `UnitGet`).

| File | Matches | Contents |
|---|---|---|
| `fn_80112C84` | 5 | Ally pair lists (fixed list `lbl_804CB7E4`, saved list `lbl_803EC418`), `fn_8011337C` map setup |
| `fn_801135C0` | 21 | Map layers, heights, tile bits, whole-layer copy and fill |
| `fn_80116CFC` | 7 | Terrain lookup with wrap-around, move strings |
| `fn_80118B20` | 7 | Tile positions, name getters |
| `fn_80118F48` | 32 | Support data and message ids, affinity table, item name getters |
| `fn_8011AB30` | 1 | Slot count |
| `fn_8011B32C` | 9 | Skill lists (`fn_8011B77C` is "has skill") |
| `fn_8011D260` | 1 | Terrain id to base terrain group |
| `fn_8011E048` | 12 | Unit init flags, rescue pairing, stat comparisons |
| `fn_8011F428` | 13 | Unit state queries, level-up allowance, hit formulas |
| `fn_80120CA0` | 9 | Laguz transform gauge checks |
| `fn_80122460` | 41 | Stat getters: base + job + personal, with cap and bonus |
| `fn_80126AA4` | 14 | Equipped item, gauge, position |
| `fn_801282F0` | 28 | Exp, transform timer, per-stat counters |
| `fn_8012A7B8` | 7 | Inventory add, remove, sort helpers |
| `fn_8012BA20` | 25 | Weapon rules, weapon rank clamp, status mask |
| `fn_8012CF28` | 32 | Unit table loops: run something on each unit of a side |
| `fn_8012E830` | 7 | Support levels at Unit +0x300 |
| `fn_8012F558` | 15 | Map camera (`lbl_804CB81C`, class `Cam`) |
| `fn_801313E4` | 6 | Small process at `lbl_80385E68` |
| `fn_empty` | 8 | Empty functions and one-instruction tail calls |
| `fn_80113428` | 4 | Map load, wall setup, two flood fills |
| `fn_80115AC8` | 1 | Flood fill step |
| `fn_80116A68` | 2 | Walk a path until blocked, add to the cost grid in a diamond |
| `fn_80118D24` | 3 | Person, job and unit initialisers (slot constructor) |
| `fn_8011ABCC` | 5 | Slot add and merge |
| `fn_8011BAC8` | 2 | Skill list save and load |
| `fn_8011BD2C` | 2 | Library quicksort over slots |
| `fn_8011F1A8` | 2 | Pair tables read from a data file |
| `fn_801209D0` | 4 | Hit stat from the 7-byte bonus struct, returned in registers |
| `fn_801213D0` | 3 | Range scan, unit save and load |
| `fn_80121E3C` | 4 | Duplicate check, reset, stat limit |
| `fn_801243F4` | 1 | HP bonus |
| `fn_80124CF0` | 5 | Equipment and aura stat bonuses |
| `fn_80127134` | 2 | Unit copy, stat clamp |
| `fn_801278F8` | 1 | Speed-type stat with doubling |
| `fn_801288D4` | 4 | Promotion, unit strings save and load |
| `fn_80129CB8` | 3 | Equip selection, item requirements |
| `fn_8012B120` | 4 | Item usable checks |
| `fn_8012E440` | 3 | Support bitsets, growth |

Round 10 added these files, one to three functions each:

| Area | Files |
|---|---|
| Item name, pair lists | `fn_80112B48`, `fn_80112F64` |
| Map walls, terrain costs, flood fill | `fn_80113794`, `fn_80113BB4`, `fn_8011540C`, `fn_801161B0`, `fn_80116CFCb`, `fn_80116E84`, `fn_8011799C`, `fn_80117E30` |
| Terrain names | `fn_8011D1E4`, `fn_8011D3A4` |
| Items, weapon ranks, inventory | `fn_8011E120`, `fn_8011FC88`, `fn_80126934`, `fn_80126F80`, `fn_80127B68`, `fn_8012A0F4`, `fn_8012A850`, `fn_8012C260`, `fn_8012C398`, `fn_8012C448`, `fn_8012C9BC` |
| Unit queries and loops | `fn_8011F428b`, `fn_801223E0`, `fn_801246A4`, `fn_80124BC0`, `fn_80126B0C`, `fn_80126F34`, `fn_8012CC80`, `fn_8012D158` |
| Support | `fn_8012E3AC`, `fn_8012EA2C` |
| Map camera and camera scripts | `fn_8012F070`, `fn_8012F1F4`, `fn_8012F3A8`, `fn_8012F5CC`, `fn_8012F640`, `fn_8012F800`, `fn_8012FD80`, `fn_8012FFD0`, `fn_801301DC`, `fn_80130468`, `fn_8013067C`, `fn_80131294` |

Round 14 added these files, one function each:

| Area | Files |
|---|---|
| Map heights and walls | `fn_80113C74`, `fn_80113F00`, `fn_801142F0`, `fn_80117200`, `fn_8011843C` |
| Terrain name hashes | `fn_8011D17C` |
| Unit death, pair rescue search | `fn_8011E414`, `fn_8011EB4C` |
| Unit queries and gauge | `fn_80120524`, `fn_80124A4C`, `fn_80126C28`, `fn_80127650` |
| Inventory | `fn_80129B20` |
| Camera scripts | `fn_80130BB4`, `fn_80130EB8` |

## Subsystems and struct layouts (names guessed)

- **Map** (`lbl_803EC898`): 64x64 grids indexed `x + (y << 6)`. `ter[0]` is the unit id, `ter[1]` the terrain id, `ter[2]` a range flag, `ter[3]` flags. `flags` holds wall bits. `cost` and `cost2` are move costs, and `cur` points at the active one. `buf` at 0x15194 is a move path of direction bytes (1, 2, 4, 8) ending in 0x40. `costTbl` at 0x15294 is the cost per terrain, 0xC7 entries. `hgt` and `hgt2` hold four corner heights per tile, and `scale` is at 0x1D424. The flood-fill work queue is `head`/`tail` at 0x2622C, with `MapNode` entries.
- **Wrap-around maps:** `lbl_804CB84C` turns wrapping on, and `lbl_804CB84D`/`lbl_804CB84E` are the x and y offsets.
- **Unit** (0x3F0 bytes, `lbl_804CB810`, 1-based ids through `UnitGet`):
  - +0xE4/+0xE8: prev/next in the side's list
  - +0xEC Person, +0xF0 Job, +0xF4 side (byte +8 is the side index), +0xF8 rescue partner or map actor
  - +0xFE transform gauge, +0x100 transform timer, +0x102/+0x103 x/y
  - +0x108: **u64** flags
  - +0x114 HP, +0x115/+0x116 exp and move bonus, +0x119 eight stats
  - +0x12C: 18 8-byte skill slots
  - +0x1BC: 7 `Inv` entries (0x28 bytes each)
  - +0x2D4 weapon rank table (s16), +0x300 support levels
- **Person** (`Unit+0xEC`): +0 name, +0x1C id, +0x1F level, +0x22 base stats, +0xDC support data, +0xE8..0xEB gauge rates.
- **Job** (`Unit+0xF0`): +0 name, +0x18 promoted job, +0xEE weapon mask, +0xF0 level, +0xFC base stats, +0x104 stat caps.
- **Sides** (`lbl_804CB814`): 11 `{head, tail, n}` lists. `fn_8010E41C(tbl, n)` fills a `u8 tbl[0xB]` side mask, and `FOR_SIDE` in `fn_8012CF28.cpp` is the loop that uses it.
- **Terrain hashes** (`lbl_80413098`): `(h + c) << 4` per character.
- **Flags** at `lbl_803CAB38`: the `flagGet` family, copied from `rC_8004BE18/decls.h`.
- **Vowel test** (`fn_8011A174`): the jump table for A, E, I, O, U picks an article index, so "a" or "an" is chosen from the item name's first letter.

## Caveats: matches that may not reflect the source

These match, but the spelling is probably not what the original author wrote:

- `fn_801198C8` walks a hand-made `q` pointer by 8 bytes to get the right induction register.
- `fn_8012401C` and `fn_80124144` read a u8 through `*(s8*)&`, and `fn_8011E294` uses `(s8)*(u8*)&a->y`. The signedness of those fields is really unclear.
- `fn_80128D70` sets bits with `((u8*)&o)[5] |= ...` next to bitfield reads.
- `HeroId`, `StatJ` and similar inlines are guesses that reproduce a register pattern. Only the behaviour is checked, not that the inline existed.
- Register-only spellings, added to reach the bytes and saying nothing about the source: the two `flagFind` loops with a stepped `FlagTable*` (`fn_80124CF0`, `fn_801243F4`), which differ per function (`AuraOn` versus `AuraOn2`, `EquipIdx` versus `EquipIdx2`), `(FlagTable*)((u8*)p + 4)`, `(Unit*)((u8*)o + i * 8)` in `fn_80121E3C` and `(UC*)((u8*)s + i * 8)` in `fn_80127134`, the `CP` pair copy in `fn_80127134`, the `Step` inline in `fn_8011BD2C`, and `Map* q = (Map*)((u8*)m + y * 0x40 + x)` in the map scans.
- `Slot::operator=` in `fn_8011ABCC.cpp` reads `item` through a `volatile` cast only to force the reload the original has. The original has no reason to be volatile.
- `Bonus` in `fn_80124CF0.cpp` and `fn_801278F8.cpp` declares a copy constructor it never defines, so that a call returns through a hidden pointer. `fn_801278B8` shows the callee is really `void f(Bonus*, u8*)` and that the struct is plain, so the true form may be a temporary filled through that pointer.
- `fn_80127134` copies through a hand-laid `UC` overlay. Fields of `Unit` in `pad121`, `padF8`, `pad3BD` and raw offsets are real fields that aren't named yet.
- `fn_8011F1A8.cpp` emits a stray out-of-line `__dt__2RdFv` that the checker skips; `Rd` looks like the stream reader class from another region. The vtable store and buffer release are that class's destructor.
- `__ptmf_scall` in `fn_80121E3C.cpp` and `fn_8011BAC8.cpp` is not reference-checked by name. The bytes around it match, and it is `fn_8028C178`.
- `fn_8012E264` writes the unit constructor as explicit stores and an array construct call. `fn_80118D24`, `fn_80118DF4` and `fn_8012E264` use `Slot::init()` in a hand loop; the original is surely a member array constructor.
- `lbl_` float externs remain in `fn_8012F58C`, `fn_8012F62C` and `fn_8012FCD8`. `fn_8012F558` uses literals.
- All prototypes of functions outside the region are guessed from call sites.
- **`fn_80116CFC.cpp` and `fn_8011F428.cpp` were rebuilt in round 10.** A script overwrote them, and they were restored from the commands in earlier session transcripts, without git. All 20 functions match again, but the text may differ from what was there before. These spots were redone by hand or search: `MapTer`'s wrap expression, the `s8 y; s8 x` loads in `fn_80118280`, `fn_8011F6F8` reading the u64 flags, and the named temporary in `fn_8012084C`.
- Round 10 search artefacts:
  - Declaration orders found by search: `fn_80112FFC`, `fn_80127B68`, `fn_80127CA0`, `fn_8012CC80`, `fn_801161B0`, `fn_8012A850`, `fn_8011540C`, `fn_80124BC0`.
  - `fn_8011540C` uses a stepped `Map* w` and a named `q`.
  - `fn_8012F800` and `fn_8013067C` copy `Vec`s through a `W3` overlay and use helper inlines (`Rot`, `Tail`, `MkZ`) to get the stack order.
  - `fn_8012C260` and `fn_8012C398` read through `(const Unit*)` only to block CSE.
  - `fn_8012FD80` and `fn_80126B0C` use `(u32)` casts on bool and u8 compares.
  - `fn_8012F3A8` declares `fn_8012F1F4` as taking a `Vec` by value, while `fn_8012F800` declares it as `void f(Vec*, const Vec*, f32)`. The second parameter is really a pointer, so the two prototypes disagree on purpose.
  - `fn_80112B48` writes its recursion levels out by hand.
- Round 14 search artefacts and overlays:
  - Declaration orders found by search: `fn_80113F00`, `fn_801142F0`, `fn_80124A4C`, `fn_8011843C`, `fn_8011E414`.
  - `fn_80130BB4` uses `F`, `F0`, `E`, `Look`, `L5` only to get stack slots. `fn_8012F3A8` is declared there as `void f(Vec*, const Vec*, const Vec*)`, which disagrees with its own file.
  - `fn_80113C74` writes the threshold as `0.04000000283f` because the original constant is one bit above `0.04f`. Its row walkers are hand-made, and `Sq3` is an inline chosen for float colouring.
  - `fn_80117200` has two average inlines (`Avg`, `Avg2`) with different bodies only to rank float registers.
  - `fn_8011E414` keeps unused `Purge` inlines from search, two flag variables in its loop, and the `dumS` pool dummy. Remove `dumS` when "PID_SOTHE" has its real user in that file.
  - `fn_8011EB4C` reads `y` as `(s8)*(u8*)&u->y` at one call and uses a raw `g5` byte read; that array's real type is unknown.
  - `fn_80124A4C` keeps the direction byte in an `int`, and its table is the extern `lbl_804CDD18`.
  - `fn_8011843C` reads the height cap from `pad1D428` at 0x1D428; the field is unnamed in `Map`.
- `fn_801246A4.cpp` and `fn_8011F428b.cpp` hold a dummy function that fills the first string pool slot. The checker skips it. The real owners of "IID_TORCH" and "PID_SOTHE" are other functions, so remove the dummies when those strings have their real users in the same file.

## Skipped

- `fn_8011C330` (the sort's median helper) inlines the `fn_8011A804` comparator several times, so solve the comparator first. Its colouring is still 35 to 41 words off.
- `fn_80128AA0` and `fn_80128FFC`: an inlined short-string class, read but not attempted.

## Resume point

1. `wip/r14_*`, closest first:
   - `fn_8011D580` (3 words, 2760 bytes: only `addi r3,r3,0x32; lhax` versus `add; lha 0x32` is left).
   - `fn_801241F4` (6), `fn_80120F50` and `fn_80121080` (7 each), `fn_8012E944` (7) and `fn_8012E9B4` (15).
   - `fn_801252F8` and `fn_801258D8` (14 to 18), `fn_8011A36C` (27), `fn_80112CD4` (64), `fn_8011E864` (71).
   - `fn_8011F9C4` (scheduling of the per-stat sums), `fn_80116294` (first draft, 15 saved registers).
2. `wip/r10_*`: `fn_801151BC` (5, the value and table temp swap), `fn_8012FA44` (39; `wip/r14_fn_8012FA44_note.txt` is a worse form), `fn_80114D00` (47), `fn_80117A84` (97), `fn_80116680` (about 120). `fn_80120378` has 1 word left, a dead `b`, and about 800 case-label sets did not produce it.
3. Not yet hand-written: `fn_8011FFD0`, `fn_8011CDC0` (after `fn_8011A804`), `fn_8012EDA0`, `fn_8012EEFC`.
4. Older near misses, not retried with the newer methods: `fn_8011F70C` (10), `fn_8012152C`, `fn_8012D3EC` (15), `fn_801135C0` (5), `fn_80119BB4`, `fn_801197F4`, `fn_8012A9A4` (needs `lwzu`), `fn_8012E854` and `fn_80117F74` (dead `blr`).
5. To list what's missing, subtract the checker's `OK` names from the `.fn` names in `build/RFEE01/asm/auto_03_80112B48_text.s`. `build/m2c/matched_names.txt` is not updated by matching, so check it against a grep of the `.cpp` files before starting a function.
6. **Before writing a new file, check that its name is free.** Files here are named by the first function they were started for, and an existing file can have that name without containing that function.

## Compiler lessons from this region

- **`if (!(x & m)) return 0;` moves the return out of line** (`beq L; ...; L: li r3,0`). `if ((x & m) == 0) return 0;` keeps `bne; li r3,0; b end`. The same goes for `if (!t)` and `if (t == 0)` on a BOOL local.
- **`a + b + c + d` is rebalanced** to `(c + a) + (d + b)`. Write the sum in every order: one of 24 usually matches, and reasoning about it rarely helps. The same search solved `x = (dx + x + w) % w` in `MapTer`.
- **`v *= 1.5f`** gives `fmuls f0,f1,f0`, while `v = v * 1.5f` and `v = 1.5f * v` both give `fmuls f0,f0,f1`.
- **A u64 field:** `u->flags &= ~(u64)2` gives `li -1; and` on the high word as well. `(u->flags & 0x80) != 0` gives `rlwinm; subic; subfe`.
- **Single-case switch:** `cmpwi; beq L; b far` is a `switch` with one case or an inline `return`, not an `if`.
- **Big range switches work directly.** `fn_8011D260` matched at once by listing every case label, with bodies in order of first appearance.
- **An int local from an s8 field stays in one register** (`lbz r31; extsb r31,r31; add r31,r31,r4`). `(s8)` on a u8 field splits it into two.
- **Reversed argument loads:** `s8 y = u->y; s8 x = u->x; f(m, x, y);` fixes the load order at an inline call.
- **A byte list loop** as a small inline taking `const u8*` keeps the pointer in r4 and the value in r5. Written in place it comes out swapped.
- **Tooling:** `check_func.py` crashes with `KeyError` when a misaligned function has a jump table. Copy it to scratch and wrap the table read in `try` while iterating, then confirm with the real tool. Trying a list of text replacements of one statement against the checker finds more matches, faster, than careful register analysis.
- **The 7-byte bonus struct:** a plain `struct { s8 v[7]; }` returned by value comes back in r3/r4 and is unpacked with shifts (`fn_801209D0`). Adding a copy constructor makes it a hidden pointer, and `t = f();` then gives the `lwz; lhz; lbz` copy.
- **Item flags at +0x38 are one u64:** `lwz r6,0x3c; lwz r5,0x38` before the first test, and `lis; and; rlwimi.` for a mask spanning both words.
- **`flags |= x == 0 ? 1 : 0;`** gives `cntlzw; srwi; or r3,r3,r4`. It's what the slot constructor needed; a member read after the store (`if (item)`) is what keeps `cmpwi r6,0` from folding.
- **A temporary keeps its stack slot:** `f(list, Slot(a, b, c))` stores and reloads, while a named `Slot t(a, b, c)` is scalar-replaced.
- **Empty functor by value, from a pointer to member:** `SkFn g(lbl); each(a, e, g);` with a real constructor gives both 12-byte copies in the right slots.
- **Param and local order flips with the inline boundary:** moving a whole block into an inline with its locals (`Step` in `fn_8011BD2C`) swapped registers no declaration order could. Search this before permuting.
- **`int` loop counters with `(s8)` at each use** (`for (int x = m->x0; ...; x++)`, `(s8)x`) are the map scans' shape, with no `extsb` on the increment.
- **Tooling:** compiles take about 40 ms, so a parallel search over dozens of spellings costs seconds. A diff of `dtk elf disasm` output against the region asm finds the fix faster than hex words.
- **Parameter below the locals (solved two ways):** `fn_8012A0F4` and `fn_8012A440` want the inline's body written in place, with its locals at function level. For `fn_80116680`, moving the whole body into an inline with one thunk gives ascending parameter registers, though that function isn't finished.
- **Function-level locals plus `sw.py`:** moving every block local to function level, including one variable per loop, solved register-only near misses in a single run where earlier searches had stalled.
- **Real string literals fix walker registers:** `"gf_gameover"` under `pool_strings` instead of `lbl_80369010 + 0xa` solved `fn_8011F428` and the flag part of `fn_8011E414`. The same change solved `fn_801246A4` and `fn_8012486C`.
- **Manhattan distance:** the `ABS` macro alone solves the `add` order in `fn_80126F34`, `fn_80124BC0` and `fn_80116CFC`. `__abs` can't.
- **Read-modify-write:** `u16 v = *p; v |= f; *p = v;` in an inline keeps `add r7; lhz r8; or; sth` (`fn_80113794`).
- **Array form of the second loop:** `lbl[i].c` with no walker gives the `lis/addi` base and `bdnz` of `fn_80112F64`.
- **Float literals:** `7.0f` and `1.0f` get shared loads where `lbl_` externs reload each time. `fn_8012F640` matched on the first compile once it used literals, and `/ 8.0f` gives the operand order.
- **Value left in r4 before a call:** `extsb. r4,r3` before `bl` was a real argument (`fn_8012A80C(u, k)`).
- **Struct copy with a nested pair:** `struct W2 {u32 a, b;}` as a member gives the `lwz; lwz; stw; stw` pair and also fixes the saved registers around it (`fn_801301DC`).
- **Hidden time argument:** `(f32)p->key == z`, with `z` an inline parameter set to `0.0f`, gets `fcmpu conv, zero` where a literal compare doesn't (`fn_8013067C`).
- **Returned `Vec` for stack order:** `Add(s, 3, MkZ())` reproduced the dead zero copy and its slot where a named local couldn't.
- **`(const Unit*)` read:** this stops CSE of the element address and keeps only the index in a saved register (`fn_8012C260`).
- **`(u32)x == 1`** keeps `cmplwi` and the branch where `x == 1` folds to `cntlzw` or reorders a chain (`fn_8012FD80`, `fn_80126B0C`).
- **`return a || b;`** gives the flag a register that `t = 0; if (a || b) t = 1; return t;` cannot (`fn_80127650`).
- **Real guard class:** a `li; ...; cmplw rGuard, rNew` compare that does not fold, with `fn_80079210` at the end, is a class with a constructor, a `reset` and a destructor (`GP` in the `fn_8011D580` draft). It took that function from 189 words to 49 in one step.
- **Split one flag into two function-level locals, then `sw.py`:** this solved `fn_8011E414`.

## Round 16

Ten new matches (3,132 bytes with rP's one; rH alone 2,840 bytes in nine functions), all passing `--strict-references`:

| File | Functions | Contents |
|---|---|---|
| `fn_80131628`, `fn_80131828` | 1 each | Free camera updates for two modes (pad axes, 45-degree snaps with sounds, fade value). Shared header `campad.h` (pad object `lbl_804CB5B8` with virtual slots, camera class with its vptr at +0x6C) |
| `fn_80131AEC` | 1 | Camera work area set-up at `lbl_80413510` (two models, 4+4 children, cleared rotations) |
| `fn_8012E944` | 2 | Support list index (`fn_8012E944` in place, `fn_8012E9B4` through `SupIdx(SPer* const& p, ...)`) |
| `fn_8011EFC8` | 1 | Sort comparator on `fn_80123BF0` |
| `fn_80119BB4` | 1 | Unordered pair list add (`lbl_80412C18`, count `lbl_804CB80C`) |
| `fn_8012A9A4` | 1 | Any inventory slot with flag 0x40: a plain `for` with `it++` gives the peeled `lwzu` form |
| `fn_8012D3EC` | 1 | Unit list rebuild: explicit byte offsets per loop at function level, then `sw.py` |

New near misses in `wip/r16_*`: `fn_801335C4` (41 words; it is the shared core of `fn_80133034` and `fn_80133B10`, so solving it should give all three), `fn_8012EDA0` (15), `fn_8012EEFC` (30), `fn_801197F4` (4). Each file says what is left.

Caveats:
- `fn_8012E944.cpp` reads the support list count through `volatile SPer*` to keep the original's reload of +0xDC on every loop test. The original probably reached it some other way; it is a codegen constraint, not evidence of a volatile in the source. The same trick is in the EDA0/EEFC WIPs.
- `fn_8012D3EC` walks the side and unit tables through explicit byte offsets (`(u8*)lbl_804CB814 + o1`); the source more likely indexed the arrays.
- `fn_80119BB4` puts `r = 0` into the `for` header because that fixes the `li` scheduling; declaration order came from `sw.py`.
- `fn_80131AEC` uses a stepped `Obj*` that is cast to `CamW*` to reach `c[0]`/`d[0]` flags, to rank the compiler walker. Declaration order came from `sw.py`.

Skipped this round: `fn_8011D580` (about 20 spellings of the `addi; lhax` read, none moved it), `fn_801252F8` (by-reference EquipIdx locals give the right walker but the counter stays r27 instead of r28), `fn_80120F50`/`fn_80121080`, `fn_8011F70C`, `fn_801151BC`, `fn_801135C0` (statement orders, inline forms and param orders did not move their few volatile registers), `fn_80131DE4` (4.7 KB, read only).

Lessons from this round:
- **Inline stack depth for the camera family:** the root-model matrices sit lowest in the frame, so `Root()` must be wrapped once more (`Root2() { Root(); }`) than the sibling `Children()` inline, whose own matrices go above and whose quaternion temp sits lowest of all in a third-level inline.
- **Uninitialised-on-one-path locals** (`if (on) { px = ...; } use(px);`) appear in this family; the loads still match with ordinary locals.
- **Explicit table walkers in the `for` header** (`tx++, ty++, j++`) fixed both their ranks and their increment order in `Children`.
- **`(a + 50.0f) / 2.0f` and `x *= 0.9f`** give the `fmuls f0,f1,f0` operand order where `* 0.5f` and `x * 0.9f` put the constant first. `f / 32.0f` vs `* 0.03125f` decides the `fmadds` operand order too.
- **A virtual call result passed straight on:** `c->v18(c->mode)` explains a `mode` value left in r4 after a store.

## Round 17

3 new matches, 3,736 bytes, in `fn_80133034.cpp`: `fn_80133034` (0x590), `fn_801335C4` (0x54C) and
`fn_80133B10` (0x38C). The file prints MATCH with `--strict-references`. `wip/r16_fn_801335C4.cpp` is now
superseded.

What solved them (from 41 words):
- **Floats that are uninitialised on one path live from function entry.** The loop locals `px/py` (Heights) and
  `px/py/pz` (Children) are only assigned under `if (W.b6D5)` inside the loops, so their live ranges overlap
  all the others. Declaring all five in the caller (`f32 cx; f32 cy; f32 cz; f32 hx; f32 hy;`) and passing them
  by reference took the float registers from 14 words to 0 in one 120-order grid. The same orders inside the
  inlines, or at the inline level, never moved them (as round 16 found).
- **`bool same`** instead of `BOOL` as a local in Heights fixed the r30/r31 swap between `same` and the W base.
- **`f32 x = G.x; f32 y = G.y;`** in the `b6B4` branch, and an `s8 cs(f32)` helper for the `(s8)` conversions in
  the else branch, fixed the volatile float registers (the helper gives the load and the `fctiwz` separate registers).
- **Shared body:** `fn_80133034` = `Reset(); Update(...)` and `fn_801335C4` = `Update(...)`. The locals must
  stay in the exported functions and be passed down; moving them into `Update` broke the registers again.
- **fn_80133B10:** `Reset(); if (W.b6D5) { heights at (x, y); ChildrenB(); W.b6D4 = 1; }`. The tell was the
  epilogue order (`addi r11` before the last `lfd`): the early `beq` goes straight to the epilogue, so the final
  store is in its own block.

Caveats:
- `ChildrenB` is a copy of `Children` with its locals declared as `ty, tx, j` rather than `ty, j, tx`. No single
  order or caller-level alternative worked for all three functions. The original may have copy-pasted the loop,
  or shaped it some other way.
- `Root(f32, f32)`, `Root2()` and the by-reference float locals are register and stack devices kept from round 16
  plus this round. The names and the `CamW`/`Obj` layout are guesses.

Near misses and findings:
- `fn_8013157C` (0x3C): this is a compiler `__sinit` for three static camera objects. The vptr at +0x6C belongs
  to a base class that has its own virtual, and three derived classes override it. Compiled that way, the
  generated `__sinit` is byte-identical, but the checker matches by name, so it can't be credited. See
  `wip/r17_fn_8013157C.cpp`. A hand-written function gets the registers reversed, and placement new adds null checks.
- `fn_801197F4` (4 words): 28 more spellings (s8/int locals, SV/SV2/Clamp return types, whole-expression forms)
  stay at 4 or worse. The `lbz r0` / `extsb r30,r0` split did not appear.

Not attempted: `fn_80131DE4` (4.7 KB map-cursor update, many float clamps; read only), `fn_8012EDA0`,
`fn_8012EEFC`, and the older list.

## Round 19

Two functions newly at `regs` level (912 bytes), in `equiv/` (self-contained; check with
`python3 -I tools/check_regs.py <file> --extra "-i src/game/rH_80112B48 -i src/game/rH_80112B48/wip"`):

| File | Function | Bytes | What changed |
|---|---|---|---|
| `equiv/fn_80112CD4.cpp` | fn_80112CD4 | 656 | r14 wip with the second loop's increments in original order (`e2++, i++`) |
| `equiv/fn_801135C0.cpp` | fn_801135C0 | 256 | near.cpp fragment + `fn_801135C0.cpp` declarations (mkself.py) |

Finding: **`fn_8012E888` and `fn_80118008` are not functions.** `fn_8012E854` and `fn_80117F74` compile to the
original words plus one dead `blr`, and that `blr` is in the original too: symbols.txt splits it off as a 4-byte
"function", which `fn_empty.cpp` then matched as an empty function. The sources in `wip/r19_fn_8012E854.cpp` and
`wip/r19_fn_80117F74.cpp` reproduce both symbols byte for byte, but the checkers compare by symbol size and report a
size mismatch (`other`), so they are not counted. A port should drop the two empty functions.

Tried once and left (all still `other`, with what dd.py shows):
- `fn_80120378`: one dead `b` after the second switch's compare chain (25 switch spellings: case orders, default
  first/last, goto, loops, empty cases).
- `fn_8011D580`: still only `addi r3,r3,0x32; lhax` (integer-typed base, reference-returning accessors, double reads).
- `fn_80114D00`, `fn_8011F70C`, `fn_8012EEFC`, `fn_801197F4`, `fn_8011E864`: one or two instructions scheduled a slot
  apart, each tied to a register difference (the prologue `mr` or a load lands next to a different neighbour).
  Statement and expression orders did not move them.
- `fn_80116DB8` (self-contained now, 48 of 51 instructions): the original converts the flag test to bool twice
  (`neg; or; srwi` twice); bool/BOOL/int/u8 inline return types and function return types all fold it.
- Not attempted: `fn_8011C330`, `fn_80131DE4`, `fn_80128AA0`, `fn_80128FFC`, `fn_8012152C`, `fn_8011FFD0`,
  `fn_8011F9C4`, `fn_80116294`, `fn_80116680`, `fn_80117A84`, `fn_8011A804`, `fn_8011CDC0`.

## Round 19b (sched class, new functions)

Eight functions added to `equiv/` (8,276 bytes; check with
`python3 -I tools/check_regs.py <file> --extra "-i src/game/rH_80112B48 -i src/game/rH_80112B48/wip"`):

| File | Function | Class | Bytes | Notes |
|---|---|---|---|---|
| `equiv/fn_8011C330.cpp` | fn_8011C330 | regs | 2,704 | new: median-of-three step of the skill slot quicksort (`x = !less(c,a); y = !less(b,c); ...`), predicate inlined three times |
| `equiv/fn_8011CDC0.cpp` | fn_8011CDC0 | regs | 956 | new: MSL `__selection_sort` + `min_element` with the predicate inlined |
| `equiv/fn_8011A804.cpp` | fn_8011A804 | regs | 812 | r7 wip; the last comparison reads both flag bytes through the slot pointers (b first), which moves the a-flags load to its original block |
| `equiv/fn_80117A84.cpp` | fn_80117A84 | sched | 940 | r10 wip fixed (was 44 diff lines): see below |
| `equiv/fn_80114D00.cpp` | fn_80114D00 | sched | 1,212 | r10 wip unchanged; two independent byte loads and their extsb/slwi/add swap |
| `equiv/fn_8011E864.cpp` | fn_8011E864 | sched | 744 | r14 wip unchanged; prologue `stw r29`/`mr`, `li 0`/`extsb`/`mr` a slot apart |
| `equiv/fn_8011F70C.cpp` | fn_8011F70C | sched | 696 | r7 wip, other functions of that file reduced to prototypes; one `lbz` and one `subf` swap |
| `equiv/fn_801197F4.cpp` | fn_801197F4 | sched | 212 | r16 wip unchanged; one `lbz` two slots later in the prologue |

Every `sched` file was looked at with `tools/equiv/dd.py -u`; the moved instructions are listed in each file's header.

What fixed fn_80117A84 (useful for fn_80116294 / fn_80116680, which use the same grids):
- The neighbour test is `(v & 0x2000) ? 0 : 1` returning `u8` (gives `rlwinm; cntlzw; extrwi 8,19`); `== 0` and `!` give `extrwi; xori`.
- The 5-bit code is built in a `u16` that starts as the bit itself: `u16 v = (f >> 13) & 1; int hi = v; v <<= 5; if (hi) { v <<= 1; v |= a; ... }`.
  `v = (v << 1) | a` defers the truncation (`clrlslwi 16,1` instead of `17,1`).
- The byte grid at Map+0xF18E must be indexed as `((s8*)m + 0xF18E)[y * 0x40 + x]` to get its own row pointer.
  **map.h declares that area as `u16 g5[0x1000]`; the first 0x1000 bytes are really an `s8` grid.** A port should fix the layout.

Caveats for a port:
- `equiv/fn_8011C330.cpp` and `equiv/fn_8011CDC0.cpp` carry a local inline copy of `fn_8011A804` (`SlotLessCall`) and swap through a
  three-member view `Raw` of `SkillSlot` so the copy is member-wise. Use one slot type and `std::swap`/`std::sort`.
- The three files define `SkillSlot` with a nested flag struct `SF`; `fn_8011BD2C.cpp` has the flags directly in the slot. Same layout.

Left in `wip/`:
- `r19b_fn_80128FFC.cpp` (`other`): MSL `basic_string(const basic_string&, pos, n)`. Logic right, 84 of 85 instructions; the stack
  slots come out in reverse order and the error string is loaded after `__files`. `fn_80128AA0` (not written) is its caller:
  `std::string s(name); s = s.substr(0, s.size() - 1); s += "3" / "2" / "1"; return fn_8010B228(s.c_str());` (thresholds 0x14b and 0xfb on
  `fn_8012C250(u, 5)`). Both use the pool `lbl_80369170`, so they belong in one file, fn_80128AA0 first.
- Not attempted this time: `fn_80131DE4` (4.7 KB), `fn_8012152C`, `fn_8011FFD0`, `fn_8011F9C4`. `fn_80116294` and `fn_80116680` were only
  re-diffed (46 and 22 diff lines; conditional `subi` blocks, a reloaded `m->...5190` pointer and `clrlwi` on the candidate costs are missing).
- `fn_8012A0F4`/`fn_8012A440` (wip r7) now class as `sched` but are already matched elsewhere; nothing to do.

## Round 20

One function newly at `regs` level (2,760 bytes):

| File | Function | Class | Bytes | Notes |
|---|---|---|---|---|
| `equiv/fn_8011D580.cpp` | fn_8011D580 | regs | 2,760 | the `addi r3,r3,0x32; lhax` puzzle |

**The `addi; lhax` puzzle is a pointer to data member.** The person's weapon-rank row is read as `(p->*m)[i]` with
`s16 (PF::*m)[12] = &PF::w` (inline `Q10` in the file). Every plain spelling (struct member, cast, accessor, 2-D
array, reference, compound-assigned pointer, about 30 forms over the rounds) folds `+0x32` into the `lha`
displacement. With an `int` index the instruction order is the original's and three volatile registers rotate
(`regs`, 5 words); with a `u32` index the registers are right but the `lwz` of the person and the `clrlslwi` swap
(`sched`, 1 word). A grid over index types of the load and of the store did not give both.
`__ptmf_scall` (= fn_8028C178) is still not reference-checked by name.

Not attempted this round: fn_80131DE4 (4.7 KB, not written), fn_80116294, fn_80116680, fn_8011FFD0, fn_80128AA0,
fn_80128FFC, fn_8011F9C4, fn_8012152C, fn_80120378 (drafts unchanged, all still `other`).

## Round 21 (large functions without a draft)

Four functions, 6,812 bytes, all at a counted level. Checked with
`python3 -I tools/check_regs.py <file> --extra "-i src/game/rH_80112B48 -i src/game/rH_80112B48/wip"`; the `sched`
files also with `tools/equiv/symcheck.py <file> <fn> rH_80112B48 --anon -v` (flags explained in each header).

| File | Function | Class | Bytes | symcheck | Notes |
|---|---|---|---|---|---|
| `fn_80128AA0.cpp` | fn_80128AA0 | exact | 720 | | job id string minus its last character plus "3"/"2"/"1" by weapon rank; MSL `std::string` |
| `equiv/fn_80131DE4.cpp` | fn_80131DE4 | sched | 4,688 | 178 blocks, 2 flagged (fctiwz scratch slots) | map cursor movement from the pad, new from the disassembly |
| `equiv/fn_8011FFD0.cpp` | fn_8011FFD0 | sched | 936 | 30 blocks, 1 flagged (dead r6..r10 at a two-argument call) | class change; rewritten self-contained from the old fragment in `wip/r7_fn_8011F70C.cpp` |
| `equiv/fn_8012152C.cpp` | fn_8012152C | sched | 468 | 22 blocks, 0 flagged | nearest free tile; `wip/r7_fn_8012152C.txt` made self-contained and fixed |

Nothing left at `other` from this round's list. Not touched: fn_80128FFC, fn_80116294, fn_80116680, fn_8011F9C4,
fn_80120378.

**fn_80131DE4** is six inlines used several times each: `Clamp` (cursor into the playable area), `Snap` (target to
tile centre), `Step` (one tile by d-pad, twice inlined), `Follow` (cursor eases to target by 0.5 or 0.25, three
times), `Stick` (analogue move rotated by camera yaw, twice) and `Settle`. Written that way the first compile was
9 instructions off; three fixes brought it to the original's size and frame:
- the `s8` conversion helper `cs(f32)` of `fn_80133034.cpp` for every `fn_80118098` argument;
- a named `f32 e = 0.001f` in `Follow` (one `lfs` held across four compares, where the literal is reloaded);
- `int ax = (int)nx, cx, cy, ay` locals for the "occupied tile" test, declared before the test: the original
  converts the new tile before testing the current one, which needs four scratch doubles at once and gives the
  0xb0 frame. The slots still come out in another order (that is the `sched` part).
`fn_80062230` takes `(GmC*, f32 x, f32 y)`: all four call sites pass the cursor position in f1/f2 (older files
declare it with a `u8*` and two floats, which agrees).

**fn_80128AA0** went exact in three compiles. What mattered: the string is a struct with only an inline destructor
(a real constructor moves the `Empty` allocator temporaries to lower stack slots: `slots` instead of exact), the
substring temporary is a block-scoped object, and the result is returned straight from `fn_8010B228(...)` so the
value kept across the destructor is a compiler temporary (a named `void* r` took r30 in every declaration order).
The same destructor-only struct should be tried on `fn_80128FFC` (same pool `lbl_80369170`), whose draft has its
stack slots mirrored.

**Real differences from the old fragments:** `wip/r7_fn_8012152C.txt` read the grid cost as `u16` and built the
tile pointer before the first test; the original reads it signed (`lhax`), compares the best value unsigned and
forms the pointer after the reachability test. `wip/r7_fn_8011F70C.cpp`'s fn_8011FFD0 was equivalent but spelled
the two stat additions out by hand; they are `stat += job->gain` and `stat += oldJob->base - job->base` on an
8-byte struct.

**Port caveats:** `equiv/fn_8011FFD0.cpp` and `fn_80128AA0.cpp` declare their own cut-down unit/job structs
(`UnitC`, `JobC`, `UnitS`, `JobS`); they describe the same memory as `unit.h` (job +0x14 next class, +0x1C id
string, +0x24 skill list, +0xB8 weapon rank minimums, +0xFC bases, +0x114 promotion gains: `unit.h`'s `Job` has
`max[8]` at 0x104 and nothing at 0x114, so extend it rather than keep both). `equiv/fn_80131DE4.cpp`: the `int ax,
cx, cy, ay` locals and `e` are codegen devices; `CamW` there has only the fields this function uses.

**Lessons:**
- **Four float-to-int scratch slots instead of two** (frame 0x10 larger, `stfd` to 0x18/0x20 and 0x28/0x30): two
  conversions of one statement are done before a test that itself converts two values. Declaring the later pair as
  `int` locals before the test reproduces the frame and the early `fctiwz`; an inline with `s8` parameters does not
  (its arguments are evaluated lazily, after the first test).
- **`extsb` at the use, not at the conversion:** `int ax = (int)f;` then `(s8)ax` in the index. An `s8` local or the
  `cs()` helper extends at the definition.
- **A named local for a float literal used in four compares** (`f32 e = 0.001f`) keeps it in one register across
  basic blocks; the literal is reloaded in every block.
- **Value returned across a destructor in the wrong register:** drop the named result and `return f(...)` directly
  with a real destructor on the object; the compiler temporary takes the freed r31.
- **Destructor-only struct plus a constructor inline called as a plain function** keeps by-value empty-class
  temporaries (`Empty()` allocator arguments) in declaration order, highest first.
- **m2c first:** all four functions were written from `tools/m2c_draft.py` output plus the list of calls; reading
  the disassembly was only needed for float argument registers (`fmr f1; fmr f2` before `fn_80062230`).

## Round 22

| function | level | bytes | file | note |
|---|---|---|---|---|
| fn_8013157C | exact | 60 | `fn_8013157C.cpp` (+ `.symbols.json`) | compiler `__sinit` of three static cameras, written as inline constructors over pooled statics |
| fn_80116DB8 | draft (`other`) | 204 | `wip/r22/fn_80116DB8.cpp` | second redundant 0/1 conversion still folded (3 instructions short) |

- fn_8013157C: the inline base constructor must store a vtable that the derived constructor overwrites; the dead
  store is what gives the original register assignment (round 17 had the registers reversed without it). The base
  vtable no longer exists in the DOL, so the dead store writes 0. Port: real classes and global definitions, drop
  the function (see file header).
- fn_80116DB8: the flag test written as `Test(u16 v, u8 d)` on the loaded halfword fixes the `clrlwi` placement;
  the double `neg; or; srwi` stays unexplained. Same behaviour (the second conversion is the identity on 0/1).

## Round 24

- fn_8012E854 still compiles to its words plus the dead `blr` that symbols.txt splits off as fn_8012E888; it can only be credited when that split is changed in config (not done here).
