# Round 20 (rF_8017F400)

Checks: `python3 -I tools/check_regs.py src/game/rF_8017F400/equiv/<file> --extra "-i src/game/rF_8017F400 -i src/game/rF_8017F400/wip"`.
No new exact matches in this region. 12 functions (14,128 bytes) newly in `equiv/`.

## `regs` (4 functions, 2,116 bytes)

| file | function | bytes | notes |
|---|---|---|---|
| equiv/fn_801CD05C.cpp | 801CD05C | 1,052 | 11 words; see "What fixed" |
| equiv/fn_801B40B0.cpp | 801B40B0 | 464 | new: list merge with the two-key comparison (byte 1, then byte 3) |
| equiv/fn_801B3D3C.cpp | 801B3D3C | 300 | copy of wip/fn_801B3D3C_ends.cpp (key byte 0) |
| equiv/fn_801B4480.cpp | 801B4480 | 300 | twin of fn_801B3D3C, key byte 3 (originals differ only in that offset) |

## `sched` (8 functions, 12,012 bytes)

| file | function | bytes | what moved |
|---|---|---|---|
| equiv/fn_8019FFE4.cpp | 8019FFE4 | 6,812 | constant loads, `fmr`, `li`, `lhz` and int-to-float conversions in the 13 frame-piece blocks; saved registers in the item block |
| equiv/fn_801AC084.cpp | 801AC084 | 1,832 | one `extsh`; the four-width sum is associated differently (same value) |
| equiv/fn_8018E6B0.cpp | 8018E6B0 | 1,164 | `li`, constant loads, `lhz` and conversions in the two bar-piece blocks |
| equiv/fn_801BB530.cpp | 801BB530 | 744 | two `addi`/`subi` of the icon x position |
| equiv/fn_801BB334.cpp | 801BB334 | 508 | one `addi r4,r4,8` |
| equiv/fn_801CF270.cpp | 801CF270 | 372 | one `cmpwi`, one `addi` |
| equiv/fn_801C63F0.cpp | 801C63F0 | 356 | two `lfs` against one `addi` |
| equiv/fn_801C6114.cpp | 801C6114 | 224 | one `stw` |

Every `sched` and `regs` file here was also run through `r20_symcheck.py --anon` (see Tools): all blocks compare
equal, except the one block of fn_801AC084 named above and call-name aliases (`__mod2i` = fn_8028C634 etc.).

## What fixed the new ones

- **fn_8019FFE4:** the r13 draft was one instruction long because the first tile-4 frame piece had a named
  `f32 y_ = 11.0f`, which kept `11.0f + 13.0f` as a run-time add. The plain `DRAW(e, col, 4, 72.0f, 11.0f, ...)` macro
  folds it like the original. Everything else was already only scheduling.
- **fn_801CD05C:** (1) the six rotation matrices of the inlined levels are locals of the outer function, declared
  a3, a2, a1, b3, b2, b1 and passed by reference: slots 0x110, 0xE0, 0xB0, 0x80, 0x50, 0x20 as in the original;
  (2) with fn_8001ECE4's mode declared `u8` (or `s16`) the literal mode 2 is no longer merged with the depth value 2
  of the middle level, which restores the two missing `li r3,2`.
- **fn_801BB530:** affinity accessor in the early-return form and `fn_801196F0(u8)` (the prototype the matched
  files use) give the `clrlwi` the draft lacked.
- **fn_801B40B0 / fn_801B4480:** text substitution on the fn_801B3D3C draft after diffing the originals.
- **fn_801BB334, fn_801C63F0, fn_801C6114, fn_801CF270:** old fragments made self-contained with mkself.py; they
  were `sched` at once.

## Complete drafts still `other` (in wip/, all compile on their own)

- wip/fn_801C0638_r20.cpp (2,140): same size. The colour temporaries of the first gauge piece and the last bar piece
  sit in each other's stack slots, and the two value texts evaluate the colour ternary before the coordinate
  conversions (original: between compare and branch). Fixed: `b >= e ? 0x27 : 1`.
- wip/fn_801BD420_r20.cpp (864): one instruction short; colour temp slots 0x14/0xC against 0x10/0x14, and the first
  colour byte comes from another constant.
- wip/fn_801CE2F4_r20.cpp (384): two short; the position Vec3 is built in the other of two slots.
- wip/fn_801C7110_r20.cpp (616): six short, not analysed. wip/fn_801B7004_r20.cpp (652): seven short (switch shape).
- wip/fn_801CE174.cpp (384, unchanged): the first offset temp and the by-value argument copy are in each other's
  slots (ours 0x2C/0x14, original 0x14/0x2C). Named copies, pointer prototypes, block order and wrappers tried.
- wip/fn_8017F4C8.c, wip/fn_80184324.cpp: unchanged. fn_80184324 keeps `idx*4` where the original keeps `idx` and
  shifts twice; a table-pointer local did not change it.

## Not done

- Not written: fn_80182D24 (3,104), fn_801A4744 (2,432), fn_801C3AB4 (1,972).
- Fragments that still do not compile with their parents: fn_801B0E88 (parent fn_801B10B0.cpp), fn_801B6B18
  (parent fn_801B7644.cpp).
- rR-range drafts fn_801D5914, fn_801D0D58, fn_801D820C, fn_801D65EC: not touched.

## Caveats (things a port must undo or check)

- equiv/fn_801CD05C.cpp: the `u8` mode parameter of fn_8001ECE4 is a spelling that reproduces the code; every other
  file declares it `int`. The LEVEL macros and the by-reference matrices stand in for fn_801CCCBC / fn_801CCE8C
  inlined three levels deep. A port should call the two real functions.
- equiv/fn_8019FFE4.cpp, equiv/fn_801AC084.cpp: `StringPool` is the documented dump of the file's string pool.
- equiv/fn_801B3D3C.cpp, fn_801B4480.cpp, fn_801B40B0.cpp: hand-written `std::list::merge` with the comparison
  written inline; a port should use one merge with three comparators.
- equiv/fn_801BB530.cpp and the three other mkself files carry the whole declaration header of their parent.
- `sched` and `regs` are not proofs. The symbolic check is per basic block and treats values entering a block
  anonymously (register class only), so it does not prove that the right saved register is read.

## Tools

- `src/game/rF_8017F400/r20_symcheck.py FILE fn REGION [--anon] [-v] [--strbase=lbl_X] [--args=fn_Y=nInt,nFloat]`
  (belongs in tools/equiv; tools/ was out of scope). It executes each basic block of both versions symbolically and
  compares non-stack stores, final stack bytes, live-out register values, call arguments and branch conditions.
  Copies are transparent, commutative operands are sorted, sdata2 literals are compared by value. It caught two
  things check_regs.py passes: a `sched` candidate of fn_8026E9DC that read a variable before assigning it, and a
  wrong float constant (rN fn_80266024).
- **check_regs.py `sched` does not compare literal values** (words that refer to unnamed literals match on everything
  but the relocated field), and check_func.py's "constant ... but original has" lines are positional, so on a `sched`
  file they are artefacts. A wrong float in a `sched` draft is only caught by a per-block value comparison.
- check_regs.py's "N words differ" for `sched` is not the number of register differences.
- dd.py does not mask `"@39"+0x1@sda21` against `lbl+0x1@sda21`.

## Lessons not in MATCHING.md

- **Check prototypes of shared helpers against the matched files before anything else.** The "open puzzle" of
  rounds 17 to 19 (`li r3,4` reloaded, rN fn_8026E9DC) was fn_8017F68C declared `(f32, f32, f32, f32, int)` instead
  of `(int mode, f32, f32, f32, f32)`. Same register passing, different code.
- **A constant that must not merge with an equal constant** (mode 2 vs depth 2): give the parameter another integer
  type (`u8`/`s16`) in the prototype.
- **Slot order of temporaries in hand-inlined recursion levels:** declare them in the outer function in first-use
  order and pass them by reference.
- **A named float local can block folding** (`f32 y_ = 11.0f; ... y_ + 13.0f` stays a run-time add when the name is
  used twice); the plain literal folds.
- **`x >= y ? A : B` and `x < y ? B : A` differ:** the first gives `li B; blt; li A`.
- **`lbz; clrlwi` on a byte that came through an `s8` inline** means the callee prototype takes `u8` and the
  accessor returns early (`if (w == -1) return a; return w;`), not `v = a` in an `if`.
- **Diff sibling originals first** (fn_801B3D3C / fn_801B4480 differ in one offset).
