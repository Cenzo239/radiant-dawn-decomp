# Round 18 (i): 0x801DD7D4..0x8023FC24

The goal changed this round: a function is done when it is exact, or when `tools/check_regs.py` classes it
`renamed`/`regs` (same instructions, order and references; only registers differ). The 40 KB aim was not
reached: 13 new functions, 15,272 bytes, plus 7 older near misses (5,264 bytes) copied into `equiv/`.

## Exact (4 functions, 7,648 bytes), in `src/game/rI_801DD7D4/`

Each prints MATCH from `python3 -I tools/check_func.py <file> --strict-references -v`
(fn_8023BF78 also needs `--symbol-map fn_8023BF78.symbols.json`).

| file | bytes | notes |
|---|---|---|
| fn_802291A8.cpp | 4044 | gradient bar: per-segment colour lerp, then three textured quads |
| fn_8023BF78.cpp (+ .symbols.json) | 2640 | open or re-reference an archive entry and wait for it; sibling of fn_8023C9C8 |
| fn_801DE450.cpp | 656 | menu entry draw (icon + centred label) |
| fn_802170E8.cpp | 308 | draw callback: perspective + viewport for a widget's 3-D model |

## Functionally equal, new (9 functions, 7,624 bytes), in `equiv/`

Each prints `regs` from `python3 -I tools/check_regs.py <file> --extra "-i src/game/rI_801DD7D4 -i src/game/rI_801DD7D4/wip"`.

| file | bytes | notes |
|---|---|---|
| fn_801F19A0.cpp | 1552 | builds the four widgets of a unit-list screen |
| fn_8022A8A0.cpp | 1360 | scrolling text grid draw |
| fn_80204EB4.cpp | 932 | weapon-type tab strip draw (two jump tables) |
| fn_801E8680.cpp | 852 | d-pad navigation of an item grid |
| fn_80224554.cpp | 848 | same body as fn_801E8680, fields 4 bytes later |
| fn_80200B18.cpp | 660 | price / funds box draw |
| fn_8022333C.cpp | 580 | menu cursor draw (eased) plus pinned cursor |
| fn_8022C080.cpp | 452 | left/right selection in an option row |
| fn_802243D0.cpp | 388 | grid selection cursor draw |

## Functionally equal, written in earlier rounds, copied to `equiv/` (7 functions, 5,264 bytes)

These were already listed in `docs/EQUIVALENT.tsv`. The wip originals are untouched; the copies compile on
their own and print `regs`: fn_80217DF8 (1616), fn_8021E23C (1168), fn_802007E4 (668), fn_802173C0 (632),
fn_80201110 (540), fn_802133F8 (488), fn_801E7990 (152).

## Not done: saved in `wip/r18i/` (all class `other`, each file starts with a comment saying what is left)

| function | bytes | state |
|---|---|---|
| fn_801F4850 | 3700 | 917 of 925 instructions. Zero idiom before the sort loop; `li` scheduling in the last constructor. |
| fn_8023CD24 | 3220 | Local `std::vector<FE*>` twice. Structure and calls right; scheduling inside reserve/push_back differs. |
| fn_8023E264, fn_8023E8EC | 1672 each | Same vector code, and all 18 saved registers are in use: the original keeps the lock pointer and leaves one `lis` in the loop, ours does the opposite. |
| fn_801EA5E4 | 1672 | 418 of 418 instructions, 10 diff lines in the third colour clamp (pointer in r6 instead of r3 moves one `lwz`). |
| fn_80236384 | 680 | THPPlayerOpen. One `addi` scheduled three instructions early. |
| fn_801E9CA8 | 656 | `addi; lwz` merged into `lwzu` in the slot loop; argument load order of the last call. |
| fn_801E1894, fn_801E163C | 580, 448 | The colour-copy puzzle of fn_8021F0E0 (`addi r4,r1,8` before the byte copy, then `mr r3,r4`). |
| fn_80236738 | 576 | THPPlayerSetBuffer. Only the audio-buffer block: zero stores of buffers 1..4 are delayed in the original. |
| fn_8023DCC0 | 452 | 3 words: `li`/`addi` order in the prologue of the local entry's constructor. |
| fn_80223580 | 328 | One `extsh` of an `lha` value missing. |
| fn_8023DC38 | 136 | With `flags = 0` first (the original store order) 4 words; the r16i copy is at 1. |

## Skipped (read, not written or not finished)

- **Zero idiom family** (11 functions, about 19 KB: fn_801F2954, fn_801F3D28, fn_801F43E0, fn_801F4850,
  fn_801F6C54, fn_801F9030, fn_801FA9BC, fn_80202344, fn_802038BC, fn_80206310, fn_8020B8C8, and fn_801F8798
  from the old list). `check_regs.py` does not accept `li` for `mr`, so they stay `other`. See below for what
  was learned.
- **Local-vector functions** fn_801FEA10 and fn_80204A08: same template code and register pressure as
  fn_8023E264.
- **Constant-heavy constructors** (fn_801EBF00 family: fn_801E8E88, fn_801EC928, fn_801E941C, fn_801EC414,
  fn_801FE108; `lbl_8038C1C0` users fn_801F17C4, fn_80205E50, fn_8020B408, fn_80221050): the existing drafts of
  this shape are all `other` because of `li` scheduling, so I did not write more of them.
- Not reached: fn_80222E34, fn_80223CF4, fn_801E7E1C, fn_8021BB04, fn_8022A174, fn_801E2924, fn_8021C6FC,
  fn_801E10E4, fn_8022DFE0, fn_8022516C, fn_80236A5C, fn_8023F9F4, the fn_801DFF2C lazy-static family and
  the three 124-byte functions fn_801ECF94/fn_801EDF9C/fn_801EEFA4.
- The other old wip files were re-classified with `check_regs.py`; none beyond the 7 above is `regs`.

## Caveats (where the source may not reflect the original)

- Names, structs and virtual slot signatures are guesses throughout.
- **fn_802291A8:** the colour inlines take `C4` by value because that is what keeps the copies in memory and
  orders the stack slots; `cols(lo, hi, lo, hi)` is by value for the same reason. `xx = x + t.w` is a second
  variable for the running x.
- **fn_8023BF78:** the final flag clear is written with a bitfield view (`FB`) of the volatile flags word, to
  get two `rlwinm` in a row. The original probably has two separate bit clears of some other form.
  The file re-declares the fn_fe.h statics like its neighbours.
- **fn_801DE450:** `icons()` returns `&lbl_803E7290` only so that calls stay virtual.
- **fn_8022333C:** `rowH` and `x` are read in the second block without being set when `sel < 0`, as in the
  original. `gx()` exists to keep one `extsh`.
- **fn_801E8680 / fn_80224554:** `((const T*)o)->cur` for `old` forces a second load; the wrap-down branch
  writes `cur` before `top`.
- **fn_80200B18:** `adv()` and the named `xr` exist for scheduling and register count.
- **fn_80204EB4, fn_8022C080, fn_802243D0, fn_8022A8A0, fn_801F19A0:** local types (`int` vs `s16`) were
  chosen from the `extsh` positions.
- `regs` means not proven equivalent by the tool: live ranges are split differently, the instruction
  sequence is identical.

## Lessons not in MATCHING.md

- **`a + b + c` without parentheses blocks hoisting.** `y = row * o->v34() + sc + dy` keeps `add sc,dy`
  inside the loop (reassociated after the invariant pass); `+ (sc + dy)` hoists it and frees a register.
- **By-value struct arguments of an inline** stay in memory and are copied bytewise at the call, where
  `const C4&` parameters or struct locals are scalar-replaced. Their temporaries are allocated in call
  order, interleaved with other by-value temporaries; the first parameter gets the highest slot.
- **`i++` as an inline argument** gives `mr rK,rI; addi rI,rI,1` with the first use on the old register.
- **Callback pairs:** `b->fn = (void*)f; b->arg = k` only loads `k` before the first store when the two
  fields and the loaded global have different types (`void*`, `int`, `*(int*)lbl`). Same-typed fields
  force store, load, store.
- **Pointer-to-member constant passed to a virtual call** explains a 12-byte `.data` copy to the stack with
  an early `addi r4,r1,N`: `obj->v2C(lbl_pmf)`.
- **`x ? 0 : 1` as a branch,** not `cntlzw`: `switch (x) { default: v = 0; break; case 0: v = 1; break; }`.
- **`or` after `clrrwi` instead of `rlwimi`:** pass the flag through an `int` inline parameter and cast to
  `s16` in the setter (`setFi(p, lti(a, b))`).
- **Two `rlwinm` in a row on one load** (no folded mask): two 1-bit bitfield assignments through a struct
  view.
- **A devirtualised call on a global object** (`bl v4C__...`) goes back to a virtual call through an inline
  that returns the object's address.
- **`lbz; cmpwi rN,1; beq; b`** is `switch (x) { case 1: ... }`, not `if (x == 1)`.
- **`cmpwi` after `lbz` with a constant other than 0:** compare as `(int)*(u8*)p == 9`.
- **Statement order decides store scheduling ties:** `o->cur -= k; o->top = 0;` vs the reverse changed
  `other` to `regs` in fn_801E8680.
- **A value kept in a named variable assigned in both arms of an `if`** (instead of a repeated expression)
  reuses one register across the arms (fn_80200B18, `xr`).
- **Register pressure changes instruction sequences.** With all 18 saved registers used (fn_8023E264) the
  compiler rematerialises address constants and stops hoisting; a draft that is right in a roomier sibling
  (fn_8023CD24 keeps the lock pointer) comes out `other` there.
- **Zero idiom (`li rI,0; mr rZ,rI` before a list-sort loop), still open.** All 11 occurrences in the DOL are
  the same inline: a loop calling a list sort with an empty comparator object passed by value. Findings:
  an `E0()` temporary gives `li rZ,0`; an uninitialised empty object gives `lbz` from the stack at the same
  position as the original `mr`; an uninitialised object with a user copy constructor (`struct ED { u8 c;
  ED() {} ED(const ED& o) : c(o.c) {} }`) is register-allocated with no definition at all, takes a saved
  register from function entry and gives `stb rX` with no `mr`, or `clrlwi rZ,rX,24` when passed through an
  inline parameter. So the original `mr` is probably a hoisted copy of an undefined or zero register value
  that the allocator placed in the counter's register. `z = i` copies survive only when `i` has two
  reaching definitions (an outer loop the compiler cannot remove). No spelling reproduced the exact four
  instructions.
- **Tool note:** `check_regs.py` says `other, 0 words differ` when sizes differ; a masked-register diff of
  the two disassemblies (registers, stack offsets and sda21 constants replaced) finds the place quickly.
