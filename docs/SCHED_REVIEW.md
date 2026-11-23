# Review of the flagged `sched`/`slots` rows (round 21)

Scope: the 57 rows of `docs/EQUIVALENT.tsv` whose last column said `N blocks flagged` (70,260 bytes). Each was run through
`tools/equiv/symcheck.py FILE fn REGION --anon -v -x` and `tools/equiv/dd.py`, the flagged blocks were read, and the row was
put in one of three classes:

- **a** artefact of the tool or of naming; nothing differs in behaviour.
- **b** a real difference in the order of work that cannot change behaviour (the reason is given).
- **c** a real difference that can change behaviour.

| verdict | functions | bytes |
|---|---|---|
| a | 47 | 58712 |
| b | 6 | 9816 |
| c | 4 | 1732 |

Three of the four (c) rows and one (b) row were fixed in their `equiv/` file. One (c) and one (b) row sit in `wip/` files, which
this review was not allowed to edit; both have a tested fix below. `docs/EQUIVALENT.tsv` itself was not edited: its class and
symcheck columns are stale for the rows marked in the last column and for the three fixed files.

"Stale register" below means: a temporary left in an argument register that the callee does not read. `symcheck.py` used to
compare every argument register set in the block; it now works out from the original's code which ones the callee can read.
Where it cannot (virtual calls, callees that call through pointers) the row was settled by reading the callee.

## Table (largest first)

| function | bytes | file (under src/game/) | verdict | reason | fixed | symcheck now |
|---|---|---|---|---|---|---|
| fn_8019FFE4 | 6812 | `rF_8017F400/equiv/fn_8019FFE4.cpp` | a | 12 blocks: our `@stringBase0` is lbl_8036CA00 (111 bytes equal); block 49: stale f9 before fn_801BC88C (reads r3-r7, f1-f8) | - | clean |
| fn_8026D73C | 4768 | `rN_8025EEF0/equiv/fn_8026D73C.cpp` | a | 3 blocks: stale r8 before fn_801BC88C (reads r3-r7, f1-f8) | - | clean |
| fn_80270348 | 4184 | `rN_8025EEF0/equiv/fn_80270348.cpp` | b | 2 blocks: `a14 + (a18 + w)` against the original's `a18 + (a14 + w)`; integer adds wrap, same sum (`--assoc` is clean) | no (harmless) | 2 flagged |
| fn_801A8E20 | 3980 | `rF_8017F400/equiv/fn_801A8E20.cpp` | a | stale r5 before fn_800800D4(int) | - | clean |
| fn_8001BD34 | 3000 | `rA_800068A0/wip/fn_8001BD34.cpp` | a | local `...rodata.0` is lbl_80360E30 (0xBC bytes equal) | - | clean |
| fn_801420B0 | 2964 | `rL_80133EB4/equiv/fn_801420B0.cpp` | a | `...data.0` is lbl_80369910 (0x78 bytes equal); other blocks: stale f1-f5 before fn_8001E6D0 (reads r3, r4); stack bytes equal | - | clean |
| fn_802384F0 | 2540 | `rI_801DD7D4/equiv/fn_802384F0.cpp` | a | local `...bss.0` is lbl_80425478 | - | clean |
| fn_80145980 | 2136 | `rL_80133EB4/equiv/fn_80145980.cpp` | a | stale r6/r7 before fn_80021958 (reads r3, r4) | - | clean |
| fn_80141650 | 1916 | `rL_80133EB4/equiv/fn_80141650.cpp` | a | templates `@20`/`@99` are lbl_80369934/lbl_8036991C (12 bytes each equal); stale float temp before fn_8001E6D0 | - | clean |
| fn_801AC084 | 1832 | `rF_8017F400/equiv/fn_801AC084.cpp` | b | 4 blocks: string pool is lbl_8036D57C (243 bytes equal); block 74: integer add association of a text x position (`--assoc` clean) | no (harmless) | 1 flagged |
| fn_80246E68 | 1808 | `rS_8023FD30/wip/fn_80246E68.cpp` | a | ptmf template `@269` is lbl_80391134 (equal, incl. the pointer to fn_8024CCAC); `__ptmf_scall` = fn_8028C178 | - | clean |
| fn_8022C384 | 1560 | `rI_801DD7D4/equiv/fn_8022C384.cpp` | a | 3 blocks: stale store temporaries in r4-r10 at three `this`-only virtual calls (fn_801DD7D4, fn_8022C244, v34); all stores and their order equal | - | 3 flagged |
| fn_80064AF4 | 1512 | `rC2_8005259C/equiv/fn_80064AF4.cpp` | a | string pool is lbl_80362168 (48 bytes equal); stale r5 before fn_800D0864(char*) | - | clean |
| fn_8017E470 | 1388 | `rR_80175E5C/equiv/fn_8017E470.cpp` | a | `slots`: two colour locals in each other's slot (0x18/0x1C), same bytes | - | 1 flagged |
| fn_8006D790 | 1376 | `rO_80065D64/equiv/fn_8006D790.cpp` | a | block 1: same eight sums, leftovers in r14/r17/r18 are dead (reassigned at ins 206-212 before any use); 5 blocks: jump tables unnamed in the original asm, all 9 tables found byte-equal in the DOL | - | 6 flagged |
| fn_802414C4 | 1256 | `rS_8023FD30/equiv/fn_802414C4.cpp` | a | stale store temporaries in r5-r10 at a `this`-only virtual call (vtable lbl_8038C294 slot 0xC = fn_801DD7D4, which reads r3 only); all stores equal | - | 1 flagged |
| fn_8021BB04 | 1208 | `rI_801DD7D4/equiv/fn_8021BB04.cpp` | b | 4 blocks: the four colour bytes are read before instead of between the GX FIFO writes; the FIFO (0xCC008000) write sequence and values are identical and the colour can't live in the FIFO register | no (harmless) | 4 flagged |
| fn_801E7E1C | 1208 | `rI_801DD7D4/equiv/fn_801E7E1C.cpp` | a | `__ptmf_scall` is fn_8028C178 (helper name) | - | clean |
| fn_80223CF4 | 1204 | `rI_801DD7D4/equiv/fn_80223CF4.cpp` | a | `__ptmf_scall` is fn_8028C178 (helper name) | - | clean |
| fn_8018E6B0 | 1164 | `rF_8017F400/equiv/fn_8018E6B0.cpp` | a | runtime helper names; 2 blocks: stale r8/r9 (texture size temporaries) before fn_801BC88C (reads r3-r7, f1-f8) | - | clean |
| fn_80137BC8 | 1080 | `rL_80133EB4/equiv/fn_80137BC8.cpp` | a | local `...rodata.0` is lbl_80369450 (0x78 bytes equal) | - | clean |
| fn_800B8BC4 | 1076 | `rG_800A3D88/wip/fn_800B8BC4.cpp` | a | 2 blocks: float registers named differently across the block edge; the next block stores the same values (checked by hand), leftover f1 is overwritten | - | 2 flagged |
| fn_80214C00 | 1060 | `rI_801DD7D4/wip/r20/fn_80214C00.cpp` | a | `slots`: functor and its by-value copy in swapped 8-byte slots; r25/r26 swapped and dead afterwards | - | 5 flagged |
| fn_80150F0C | 1052 | `rM_8014C9F8/equiv/fn_80150F0C.cpp` | a | `slots`: colour temporary and its two copies in permuted slots, same bytes | - | 1 flagged |
| fn_802267D8 | 1048 | `rI_801DD7D4/wip/r15b/fn_802267D8.cpp` | b | block 10: the word at lbl_803CA870 is read after instead of before the store to `l->a80` of the object just allocated by newL(); can't alias a static. Blocks 7, 13: dead r27/r28, ptmf copy temporary in r4 (target takes `this` only). Source fix known (see below) | no (file is in wip/, outside the edit scope) | 3 flagged |
| fn_801EC928 | 1000 | `rI_801DD7D4/equiv/fn_801EC928.cpp` | a | stale store temporaries in r5-r10 at a `this`-only virtual call (vtable lbl_8038C294 slot 0xC = fn_801DD7D4, which reads r3 only); all stores equal | - | 1 flagged |
| fn_801E8E88 | 1000 | `rI_801DD7D4/equiv/fn_801E8E88.cpp` | a | stale store temporaries in r5-r10 at a `this`-only virtual call (vtable lbl_8038C294 slot 0xC = fn_801DD7D4, which reads r3 only); all stores equal | - | 1 flagged |
| fn_80224CCC | 980 | `rI_801DD7D4/equiv/fn_80224CCC.cpp` | b | block 12: fields 0x14/0xC/0x10/0x18 of `o` are read on the other side of the stores to fields 0x62/0x8A of the same object (same base, disjoint offsets) | no (harmless; tool now clean) | clean |
| fn_801E941C | 968 | `rI_801DD7D4/equiv/fn_801E941C.cpp` | a | stale store temporaries in r5-r10 at a `this`-only virtual call (vtable lbl_8038C294 slot 0xC = fn_801DD7D4, which reads r3 only); all stores equal | - | 1 flagged |
| fn_801FE108 | 956 | `rI_801DD7D4/equiv/fn_801FE108.cpp` | a | stale store temporaries in r5-r10 at a `this`-only virtual call (vtable lbl_8038C294 slot 0xC = fn_801DD7D4, which reads r3 only); all stores equal | - | 1 flagged |
| fn_801EC414 | 956 | `rI_801DD7D4/equiv/fn_801EC414.cpp` | a | stale store temporaries in r5-r10 at a `this`-only virtual call (vtable lbl_8038C294 slot 0xC = fn_801DD7D4, which reads r3 only); all stores equal | - | 1 flagged |
| fn_801EBF00 | 956 | `rI_801DD7D4/equiv/fn_801EBF00.cpp` | a | stale store temporaries in r5-r10 at a `this`-only virtual call (vtable lbl_8038C294 slot 0xC = fn_801DD7D4, which reads r3 only); all stores equal | - | 1 flagged |
| main | 896 | `rA_800068A0/wip/fn_800227D4.cpp` | a | block 0: the file's `...bss.0` is lbl_803BFBE0 (address load scheduled two slots later, so not auto-aliased) | - | 1 flagged |
| fn_80020764 | 892 | `rA_800068A0/wip/fn_80020354.cpp` | c | REAL: GXBegin(TRIANGLESTRIP, 4) vertices 3 and 4 are swapped: ours (x,y) (x2,y) (x2,y2) (x,y2), original (x,y) (x2,y) (x,y2) (x2,y2); the alpha bytes col[2]/col[3] land on the other corners | no (file is in wip/, outside the edit scope); fix tested | 1 flagged |
| fn_800FA264 | 812 | `rE_800E5DE4/wip/fn_800FA264.cpp` | a | stale r6/r7 before fn_80010DA4 (reads r3, r4) | - | clean |
| fn_8021C31C | 796 | `rI_801DD7D4/equiv/fn_8021C31C.cpp` | a | stale r4 before fn_80079150(size) | - | clean |
| fn_8011E864 | 744 | `rH_80112B48/equiv/fn_8011E864.cpp` | a | stale r10 before fn_80126EB0 (reads r3-r5) | - | clean |
| fn_80280F1C | 716 | `rN_8025EEF0/equiv/fn_80280F1C.cpp` | a | 3 blocks: int-to-float conversion temporaries left in f2/f3 before fn_80253EE4(const char*, f32) (reads r3, f1); stores equal | - | 3 flagged |
| fn_800F199C | 660 | `rE_800E5DE4/wip/fn_800F199C.cpp` | a | local table `@19` is lbl_80367498 (26 bytes equal) | - | clean |
| fn_800156C8 | 564 | `rA_800068A0/equiv/fn_800156C8.c` | b | block 10: `k = s->keys` was read before the two `b->lo/b->hi` resets, the original reads it after (different arrays, harmless); block 3: conversion temporaries in each other's slot (artefact) | yes (block 10; still `sched`, 7 words) | 1 flagged |
| fn_8014D9FC | 524 | `rM_8014C9F8/equiv/fn_8014D9FC.cpp` | a | tool bug: `@sda21(r0)` took r0's value as the base; fixed in symcheck.py | - | clean |
| fn_801E1D0C | 516 | `rI_801DD7D4/equiv/fn_801E1D0C.cpp` | c | REAL: scroll flag x88 was `x44 > x40 - x42`, the original computes `x44 < x40 - x42` (other operand in the branch-free compare) | yes: file is now `exact` | clean |
| fn_80162B54 | 464 | `rM_8014C9F8/equiv/fn_80162B54.cpp` | a | stale struct-copy temporary in r6 before fn_8016D144(Unit*); local tables kAtk/kDef equal lbl_8036B040/lbl_8036B050 | - | 1 flagged |
| fn_8023DCC0 | 452 | `rI_801DD7D4/equiv/fn_8023DCC0.cpp` | a | `...bss.0` is lbl_80425478; stale r5-r7 before fn_8023B5B0 (reads r3, r4) | - | clean |
| fn_801CE174 | 384 | `rF_8017F400/wip/fn_801CE174.cpp` | a | `slots`: two Vec temporaries in each other's slot (0x14/0x2C); the address passed follows the slot | - | 2 flagged |
| fn_8001AB10 | 288 | `rA_800068A0/equiv/fn_8001AB10.c` | a | stale r5 before fn_80304C74 (reads r3, r4) | - | clean |
| fn_8019F108 | 224 | `rF_8017F400/equiv/fn_8019F108.cpp` | a | constants 0 and 1 sit in r4/r5 the other way round as store temporaries (stores equal); fn_800D0864(char*) reads r3 only. String table `@27` equals lbl_8036C52C incl. all 13 strings | - | 1 flagged |
| fn_80263D18 | 200 | `rN_8025EEF0/equiv/fn_80263D18.cpp` | c | REAL (aliasing): with `const char* s` the end test `*s` was read before the `l[col] = 0` store, the original reads it after; differs if the text lies in the line buffer being written | yes: `char* s`; now `regs` (16 words) | clean |
| fn_80168A90 | 196 | `rQ_80163178/equiv/fn_801689C8.cpp` | a | two float-to-int temporaries in each other's stack slot (0x8/0x10); same index computed | - | 1 flagged |
| fn_80223900 | 152 | `rI_801DD7D4/equiv/fn_80223900.cpp` | a | stale temporaries in r7-r9 before fn_801E2204 (reads r3-r5); the stack pair passed is equal | - | clean |
| fn_8013E77C | 128 | `rL_80133EB4/equiv/fn_8013E77C.cpp` | a | tool bug: `@sda21(r0)` base (fixed in symcheck.py) | - | clean |
| fn_80263DE0 | 124 | `rN_8025EEF0/equiv/fn_80263D18.cpp` | c | REAL (aliasing): same as fn_80263D18 (same file) | yes: `char* s`; now `regs` (14 words) | clean |
| fn_801FE8BC | 124 | `rI_801DD7D4/equiv/fn_801ECF94.cpp` | a | stale temporaries before fn_801E2204 (reads r3-r5); the stack pair passed is equal | - | clean |
| fn_801EEFA4 | 124 | `rI_801DD7D4/equiv/fn_801ECF94.cpp` | a | stale temporaries before fn_801E2204 (reads r3-r5); the stack pair passed is equal | - | clean |
| fn_801EDF9C | 124 | `rI_801DD7D4/equiv/fn_801ECF94.cpp` | a | stale temporaries before fn_801E2204 (reads r3-r5); the stack pair passed is equal | - | clean |
| fn_801ECF94 | 124 | `rI_801DD7D4/equiv/fn_801ECF94.cpp` | a | stale temporaries before fn_801E2204 (reads r3-r5); the stack pair passed is equal | - | clean |
| fn_80240814 | 84 | `rS_8023FD30/equiv/fn_80240814.cpp` | a | stale temporaries before fn_801E2204 (reads r3-r5); the stack pair passed is equal | - | clean |

## Category (c): what each one changes in the game

1. **fn_801E1D0C** (`rI_801DD7D4/equiv/fn_801E1D0C.cpp`), fixed. A scrolling widget sets two flag bytes after drawing its bar:
   `x60 = pos > 0` and `x88`. The draft had `x88 = x44 > x40 - x42`; the original computes `x44 < x40 - x42`. The flag (most
   likely "can scroll further", read by the sub-object at 0x7C) was the wrong way round whenever the two values differ.
   One-character fix; `check_regs.py` now reports the file **`exact`** (was `sched`, 2 words).
2. **fn_80263D18** and **fn_80263DE0** (`rN_8025EEF0/equiv/fn_80263D18.cpp`), fixed. Both split a text into the dictionary
   menu's line buffers. After writing the terminator `l[col] = 0` they test `*s` for the end of the text. With the parameter
   declared `const char*` the compiler read `*s` before the store; the original reads it after. The result differs only if
   the text passed in lies inside the line buffer being written (then the original stops, the draft goes on). Fix: the
   parameter is `char* s`. Both are now class **`regs`** (same instruction order as the original; 16 and 14 words differ in
   registers, was `sched` 9 and 7) and symcheck is clean. Callers should declare them with `char*`.
3. **fn_80020764** (`rA_800068A0/wip/fn_80020354.cpp`), **not fixed** (file is in `wip/`). See below.

## Left unfixed

- **fn_80020764 (c)**, `src/game/rA_800068A0/wip/fn_80020354.cpp`, lines 154-157. The function fills a rectangle with one
  `GXBegin(0x98 /* triangle strip */, 0, 4)`. The draft sends the corners in perimeter order (x,y) (x2,y) (x2,y2) (x,y2);
  the original sends strip order (x,y) (x2,y) (x,y2) (x2,y2). As a strip the draft's order draws the triangles
  TL-TR-BR and TR-BR-BL: the lower left part of the rectangle is missing and part is drawn twice, and the per-corner
  alpha bytes `col[2]`/`col[3]` go to swapped corners. Fix: swap the two `gxPos3` calls of the third and fourth vertex
  (`gxPos3(x, y2, 0.0f)` third, `gxPos3(x2, y2, 0.0f)` fourth; the `gxCol4` lines stay). Tested copy:
  `build/tmp/r21review/try/fn_80020354.cpp`: still `sched`, 2 words, and the only flag left is a stale f1 before
  fn_803077C4(int).
- **fn_80020354 (not one of the 57: class `regs`, same file)** has the **same vertex-order bug** (lines 126-129, with `z`).
  `regs` only compares instructions with registers masked, and here the corner is chosen by which register is stored,
  so the class accepted it. It needs the same swap; not tested here.
- **fn_802267D8 (b)**, `src/game/rI_801DD7D4/wip/r15b/fn_802267D8.cpp` line 97. Harmless as it stands. To get the original's
  order, replace the block by
  `{ L88* l = s->a54; struct P2 { void* f; void* d; }; P2 t; t.f = (void*)fn_80226BF0; t.d = *(void**)lbl_803CA870; *(P2*)&l->a80 = t; }`
  (tested copy `build/tmp/r21review/try/fn_802267D8.cpp`: still `sched`, 7 words, block 10 clean).
- The other (b) rows (fn_80270348, fn_801AC084, fn_8021BB04, fn_80224CCC) were left as they are; no search for the
  original's order was made.

## Tool changes (`tools/equiv/symcheck.py` only)

Stricter:
- **Call arguments are compared register by register in `--anon` mode too.** They used to be compared as a sorted multiset,
  which accepts two swapped arguments. No row that was `clean` became flagged by this (all 108 clean `sched` rows are still clean).
- **`@sda21(r0)` / `0(r0)` bases are the literal zero**, not the value of r0 (wrong before; cleared fn_8014D9FC, fn_8013E77C).

Fewer artefacts, without comparing less of what can matter:
- **Local data names** (`@stringBase0`, `@123` reached by `lis/addi`, `...data.0`, `...rodata.0`, `...bss.0`, file statics)
  are renamed to the original's `lbl_X` when the uses agree one-to-one and, where our object's bytes are known, the DOL bytes
  at `lbl_X` are equal. Each renaming is printed as a `note:` line; "contents not compared" notes (sections, objects with
  relocations) were compared by hand for this review (`build/tmp/r21review/datacmp.py`), all equal.
- **Runtime helper names** `__ptmf_scall`, `__div2i`, `__mod2i`, `__cvt_sll_flt`, `__cvt_dbl_usll` map to their `fn_` names.
- **Callee argument registers**: at a direct `bl` only the registers the original callee can read before writing them are
  compared (liveness over the callee's original code, followed through its own direct calls; unknown, indirect or mutually
  recursive callees fall back to "all"). `--allargs` restores the old behaviour, `--args=` still overrides.
- **A store through the same unchanged base register at a non-overlapping constant offset** no longer counts as a store
  a later load may depend on (cleared fn_80224CCC).
- `.byte a, b, c` lists in our object's data are parsed (string pools were not readable before).

New options: `-x` prints, per flagged block, the stores / stack bytes / arguments / live-out values only one side has, as
expressions; `--assoc` compares nested integer `add`s as one sum (off by default so that association differences stay visible).

Known limits, unchanged: `--anon` treats all incoming registers of a class as one value, so a value handed to the next block
in another register is only caught by the live-out multiset; stack-slot permutations (`slots`) are always flagged; virtual
calls compare every argument register; jump tables are not followed (liveness treats `bctr` as "any block").

## Not part of this review, but found on the way

Re-running the new `symcheck.py` over all 449 rows (`build/tmp/r21review/all.tsv`): of the 57 flagged rows 32 are now clean
and 25 are still flagged (all explained above); none of the 108 `clean` rows changed. `regs` rows have no symcheck column
at all, and **27 of the 254 `regs` rows (46,872 bytes) are flagged** by it. One of them, fn_80020354, is a real bug (above);
the rest were not looked at:

| function | bytes | file | result |
|---|---|---|---|
| fn_8019AEA8 | 16972 | `rF_8017F400/equiv/fn_8019AEA8.cpp` | 1494 blocks, 8 differ |
| fn_80275FD4 | 7740 | `rN_8025EEF0/wip/fn_80275FD4.cpp` | 474 blocks, 2 differ |
| fn_80277E10 | 6396 | `rN_8025EEF0/wip/fn_80277E10.cpp` | 388 blocks, 1 differ |
| fn_80020F04 | 1744 | `rA_800068A0/wip/fn_80020F04.cpp` | 142 blocks, 1 differ |
| fn_80225650 | 1568 | `rI_801DD7D4/equiv/fn_80225650.cpp` | 41 blocks, 1 differ |
| fn_801A32BC | 1500 | `rF_8017F400/wip/fn_801A32BC_r15.cpp` | 60 blocks, 1 differ |
| fn_8016B3F4 | 1304 | `rQ_80163178/equiv/fn_8016B3F4.cpp` | 71 blocks, 1 differ |
| fn_8016B90C | 1268 | `rQ_80163178/equiv/fn_8016B90C.cpp` | 69 blocks, 1 differ |
| fn_80020354 | 1040 | `rA_800068A0/wip/fn_80020354.cpp` | 40 blocks, 1 differ |
| fn_801681E0 | 888 | `rQ_80163178/equiv/fn_801681E0.cpp` | 64 blocks, 1 differ |
| fn_80168558 | 888 | `rQ_80163178/equiv/fn_801681E0.cpp` | 64 blocks, 1 differ |
| fn_80164064 | 716 | `rQ_80163178/equiv/fn_80164064.cpp` | 43 blocks, 1 differ |
| fn_80164330 | 680 | `rQ_80163178/equiv/fn_80164330.cpp` | 46 blocks, 1 differ |
| fn_8016A280 | 584 | `rQ_80163178/equiv/fn_8016A280.cpp` | 33 blocks, 1 differ |
| fn_800CD5F4 | 512 | `rK_800CF8BC/equiv/fn_800CD5F4.cpp` | 45 blocks, 1 differ |
| fn_8027247C | 424 | `rN_8025EEF0/equiv/fn_8027247C.cpp` | 23 blocks, 2 differ |
| fn_80138000 | 396 | `rL_80133EB4/equiv/fn_80138000.cpp` | 22 blocks, 1 differ |
| fn_800A75E8 | 392 | `rG_800A3D88/equiv/fn_800A75E8.cpp` | 34 blocks, 1 differ |
| fn_80169B20 | 336 | `rQ_80163178/equiv/fn_80169B20.cpp` | 14 blocks, 1 differ |
| fn_80095514 | 296 | `rD_8008E3B4/equiv/fn_80095514.cpp` | 15 blocks, 1 differ |
| fn_8000BC20 | 284 | `rA_800068A0/equiv/fn_8000BC20.c` | 23 blocks, 1 differ |
| fn_80175C3C | 228 | `rQ_80163178/equiv/fn_80175C3C.cpp` | 8 blocks, 1 differ |
| fn_800C9918 | 196 | `rG_800A3D88/equiv/fn_800C9918.cpp` | 5 blocks, 1 differ |
| fn_801CABAC | 140 | `rF_8017F400/wip/fn_801CABAC.cpp` | 6 blocks, 1 differ |
| fn_8008A070 | 128 | `rJ_800799AC/equiv/fn_8008A070.cpp` | 5 blocks, 1 differ |
| fn_800FCD10 | 128 | `rE_800E5DE4/equiv/fn_800FCD10.c` | 4 blocks, 1 differ |
| fn_800C7A98 | 124 | `rG_800A3D88/equiv/fn_800C7A98.cpp` | 6 blocks, 1 differ |

# Review of the regs rows (round 21, second pass)

Scope: the 27 `regs` rows of `docs/EQUIVALENT.tsv` that `tools/equiv/symcheck.py --anon` flagged (46,872 bytes, list at the
end of the section above), the left-overs of the first review, and a spot-check of the unflagged rows. Same method and
verdicts (a / b / c) as above.

| verdict | functions | bytes |
|---|---|---|
| a | 17 | 40608 |
| b | 6 | 4092 |
| c | 4 | 2172 |

All four (c) rows are fixed, and all four are now **`exact`**: in each case the "register difference" was a call with a
missing argument or a wrong vertex order, and the right source compiles to the original's registers. Four more (c) cases
outside the 27 were found by a new cross-block check (`--xargs`, below) in rows the default run calls clean: three in
`equiv/` files, fixed (fn_8002FFDC and fn_801689C8 now `exact`, fn_800ED4AC still `regs`), and one in a `sched` wip file
(fn_8004564C, not fixed, tested fix below). `docs/EQUIVALENT.tsv` was not edited: its class column is stale for
fn_80020354, fn_800CD5F4, fn_8027247C, fn_800C9918, fn_8002FFDC and fn_801689C8 (all `exact` now), the word count for
fn_800ED4AC (10), and fn_80020354/fn_80020764/fn_802267D8 have corrected files in `equiv/` that the table doesn't point to.

Lesson: **`regs` with a difference in an argument register right before a call is a prototype bug until shown otherwise.**
Three of the four (c) rows had a header note that explained the difference away ("r3/r4 swap with every spelling tried",
"float registers", "it->data kept in r3 instead of r4").

## Table (largest first)

"symcheck now" is the default `--anon` run; an option in brackets is what clears a row whose flag is an artefact.

| function | bytes | file (under src/game/) | verdict | reason | fixed | symcheck now |
|---|---|---|---|---|---|---|
| fn_8019AEA8 | 16972 | `rF_8017F400/equiv/fn_8019AEA8.cpp` | a | 8 blocks: our function-local static `lbl_804CB944$20` against the original's `lbl_804CB944` (name map in `fn_8019AEA8.symbols.json`, which symcheck now reads). All 8 uses of lbl_804CB944 in the original are in this function, so the local static is probably the original form | - | clean |
| fn_80275FD4 | 7740 | `rN_8025EEF0/wip/fn_80275FD4.cpp` | a | block 0: `psq_st` counted as defining the stored register (tool bug, fixed); block 84: local `@260` = {lbl_80373558, lbl_80373564} is lbl_804D0618/lbl_804D061C (pointer words now compared by value) | - | clean |
| fn_80277E10 | 6396 | `rN_8025EEF0/wip/fn_80277E10.cpp` | a | block 239: compare temporary left in r4 (original: r0) before fn_800D0864(char*), which reads r3 only | - | 1 flagged (`--virt-this` clean) |
| fn_80020F04 | 1744 | `rA_800068A0/wip/fn_80020F04.cpp` | a | block 87: six compares use f0/f1 the other way round, same operands; the leftover in f1 looks live at blr, the function returns int | - | 1 flagged (`--ret=r3` clean) |
| fn_80225650 | 1568 | `rI_801DD7D4/equiv/fn_80225650.cpp` | a | block 3: dead temporary in r26 looked live at blr because `bl _restgpr_26` was not seen as reloading r26-r31 (tool bug, fixed) | - | clean |
| fn_801A32BC | 1500 | `rF_8017F400/wip/fn_801A32BC_r15.cpp` | a | block 57: store temporary in r7 (original: a reloaded pointer) before fn_80253EE4(const char*, f32), which reads r3 and f1; the original's three call sites leave three different things in r5-r7 | - | 1 flagged (`--virt-this` clean) |
| fn_8016B3F4 | 1304 | `rQ_80163178/equiv/fn_8016B3F4.cpp` | a | block 0: the original asm has `lis r0, 0x803f` ... `subi r4, r4, 0x3768` unsymbolised (the half goes through a stack slot); 0x803F0000 - 0x3768 = lbl_803EC898, what ours loads | - | 1 flagged |
| fn_8016B90C | 1268 | `rQ_80163178/equiv/fn_8016B90C.cpp` | a | same as fn_8016B3F4 | - | 1 flagged |
| fn_80020354 | 1040 | `rA_800068A0/wip/fn_80020354.cpp` | c | REAL: triangle-strip corners 3 and 4 swapped (see first review) | yes: new `rA_800068A0/equiv/fn_80020354.cpp`, **`exact`** | clean (new file) |
| fn_801681E0 | 888 | `rQ_80163178/equiv/fn_801681E0.cpp` | b | block 26: `i == j` compiled as cmplw j,i, the original has cmplw i,j; only `beq` tests it, flags dead after | no (harmless; `j == i` in the source changes nothing) | 1 flagged (`--eqsym` clean) |
| fn_80168558 | 888 | `rQ_80163178/equiv/fn_801681E0.cpp` | b | same as fn_801681E0 (same macro) | no (harmless) | 1 flagged (`--eqsym` clean) |
| fn_80164064 | 716 | `rQ_80163178/equiv/fn_80164064.cpp` | b | block 39: `ter != u->tid` operands the other way round in cmplw, tested by `beq` only | no (harmless) | 1 flagged (`--eqsym` clean) |
| fn_80164330 | 680 | `rQ_80163178/equiv/fn_80164330.cpp` | b | block 42: same compare as fn_80164064 | no (harmless) | 1 flagged (`--eqsym` clean) |
| fn_8016A280 | 584 | `rQ_80163178/equiv/fn_8016A280.cpp` | b | block 17: `ter == u->tid` operands the other way round, tested by `bne` only. It is the one word that differs; three spellings tried, none flips it | no (harmless) | 1 flagged (`--eqsym` clean) |
| fn_800CD5F4 | 512 | `rK_800CF8BC/equiv/fn_800CD5F4.cpp` | c | REAL: fn_800620A8 called without its first argument (see below) | yes: **`exact`** (was regs, 10 words) | clean |
| fn_8027247C | 424 | `rN_8025EEF0/equiv/fn_8027247C.cpp` | c | REAL: fn_80253DAC / fn_80253718 called without their last f32 argument (see below) | yes: **`exact`** (was regs, 12 words) | clean |
| fn_80138000 | 396 | `rL_80133EB4/equiv/fn_80138000.cpp` | a | block 7: r0/r3 the other way round as temporaries; leftover r3 at blr of a void function | - | 1 flagged (`--ret=none` clean) |
| fn_800A75E8 | 392 | `rG_800A3D88/equiv/fn_800A75E8.cpp` | a | block 0: load temporaries in r5/r6 (original r4/r5) before fn_800F416C(void*), which reads r3 only | - | 1 flagged (`--virt-this` clean) |
| fn_80169B20 | 336 | `rQ_80163178/equiv/fn_80169B20.cpp` | b | block 4: same compare as fn_8016A280, tested by `bne` only | no (harmless) | 1 flagged (`--eqsym` clean) |
| fn_80095514 | 296 | `rD_8008E3B4/equiv/fn_80095514.cpp` | a | block 11: the original leaves the int-to-float bias in f2 before fn_80183944(GMap*, int, int, int, u8*, f32), which reads r3-r7 and f1 | - | 1 flagged (`--virt-this` clean) |
| fn_8000BC20 | 284 | `rA_800068A0/equiv/fn_8000BC20.c` | a | block 17: r3/r4 the other way round in the chunk loop; leftover r3 at blr of a void function | - | 1 flagged (`--ret=none` clean) |
| fn_80175C3C | 228 | `rQ_80163178/equiv/fn_80175C3C.cpp` | a | block 6: temporaries in other volatile registers, the four stores are equal; leftover r3 at blr, void | - | 1 flagged (`--ret=none` clean) |
| fn_800C9918 | 196 | `rG_800A3D88/equiv/fn_800C9918.cpp` | c | REAL: PSMTXScale called without its z argument (see below) | yes: **`exact`** (was regs, 5 words) | clean |
| fn_801CABAC | 140 | `rF_8017F400/wip/fn_801CABAC.cpp` | a | block 0: f1/f2 the other way round, stores and both compares equal; leftover f1 at blr, void | - | 1 flagged (`--ret=none` clean) |
| fn_8008A070 | 128 | `rJ_800799AC/equiv/fn_8008A070.cpp` | a | block 2: temporaries in other volatile registers, the stored counter is equal; leftover r3 at blr, void | - | 1 flagged (`--ret=none` clean) |
| fn_800FCD10 | 128 | `rE_800E5DE4/equiv/fn_800FCD10.c` | a | block 1: float temporaries in other registers, the three stores are equal; leftover f1 at blr, void | - | 1 flagged (`--ret=none` clean) |
| fn_800C7A98 | 124 | `rG_800A3D88/equiv/fn_800C7A98.cpp` | a | block 3: temporaries in other volatile registers, both `sthx` stores equal; leftover r3 at blr, void | - | 1 flagged (`--ret=none` clean) |

The "stale register" verdicts were checked by working out, from the original's code, which argument registers each callee
can read when the virtual call inside it (the lock in fn_80076F54) is taken to read `this` only: fn_800D0864 r3;
fn_80253EE4 r3, f1; fn_800F416C r3; fn_80183944 r3-r7, f1. "Void" was read off the original: no path sets r3/f1 for the
return.

## Category (c): what each one changes in the game

1. **fn_80020354** and **fn_80020764** (`rA_800068A0/wip/fn_80020354.cpp`), fixed in the new
   `rA_800068A0/equiv/fn_80020354.cpp`. Rectangle fills sent their four corners in perimeter order to a triangle strip, so
   half of every filled rectangle (fades, dimming boxes) would be missing. With the third and fourth `gxPos3` swapped
   fn_80020354 is **`exact`** and fn_80020764 stays `sched` (2 words; the one flagged block is a float temporary left in f1
   before fn_803077C4(int), which reads r3 only). The wip file is still wrong; the new file's header says so.
2. **fn_800CD5F4** (`rK_800CF8BC/equiv/fn_800CD5F4.cpp`), fixed, **`exact`**. Chapter start: on one branch it calls
   fn_800620A8, which is `(SaveData*, f32 x, f32 y)` (it stores the position at 0x934.. of its first argument; five matched
   files declare it that way). The draft declared `(f32, f32)` and r3 held `(u8 value) ^ 0x80000000`: the callee would have
   written the cursor position through a wild pointer, a crash on a console and memory corruption in a port.
   `rK_800CF8BC/wip/fn_800CCF84.cpp` still has the two-argument prototype.
3. **fn_8027247C** (`rN_8025EEF0/equiv/fn_8027247C.cpp`), fixed, **`exact`**. Positional sound start: fn_80253DAC is
   `(id, pos, f32 vol, f32 ms)` and fn_80253718 `(id, f32 vol, f32 ms)` (matched in `rS_8023FD30/fn_8024F3FC.cpp`). The
   original passes 0.0f as the fade time (the same constant it has just stored in the handle, kept in f2 across the
   switch). The draft declared both without `ms`; f2 held `pos->y` at the two fn_80253DAC calls, so 3D sounds would fade
   in over "y coordinate" milliseconds. `rN_8025EEF0/wip/fn_8027247C.cpp` still has the old prototypes.
4. **fn_800C9918** (`rG_800A3D88/equiv/fn_800C9918.cpp`), fixed, **`exact`**. fn_8031292C is PSMTXScale(m, x, y, z); the
   draft passed no z, so the matrix got 2^52 + 2^31 (the int-to-float bias left in f3) where the original passes 1.0f.
   No visible effect, because the matrix is then loaded as a 2x4 texture matrix (fn_80307F10(m, 0x21, 1)), but any port
   that loads all three rows would see it. `rG_800A3D88/fn_800B5D14.cpp`, `rG_800A3D88/equiv/fn_800A40B4.cpp` and
   `rG_800A3D88/wip/fn_800C4104_r20.cpp` still declare fn_8031292C with two floats (not edited: the first is a matched
   file, the other two were not part of this review; none was checked for a call).

Found outside the 27 by `--xargs` (all four rows were "clean" in the default run):

5. **fn_8002FFDC** (`rB_8002E1C4/equiv/fn_8002FFDC.c`, `regs`), fixed, **`exact`** (was regs, 7 words).
   "Can the weapon just used break": fn_8012C260 is `(Unit*, item data*)` (`rH_80112B48/fn_8012C260.cpp`) and reads the
   item type through r4. The draft called it with the unit only; r4 held whatever fn_801116B8 left there, so the weapon
   break flag came from a wild read. The original keeps `it->data` in r4 across the three type tests for that call, which
   the old header noted as "it->data kept in r3 instead of r4". `rB_8002E1C4/wip/fn_8002FFDC.c` still has the old prototype.
6. **fn_801689C8** (`rQ_80163178/equiv/fn_801689C8.cpp`, `regs`), fixed, **`exact`** (was regs, 3 words). AI camera step:
   fn_801030B8 has six arguments (`rB_8002E1C4/fn_800402C0.cpp`; it hands the sixth on to fn_80102E10). The draft passed
   five and r8 was never set; the original passes the proc `p` in r8 (six of the other seven call sites set r8 right before the call). The
   move would have been started with a garbage sixth argument. Five-argument declarations of fn_801030B8 without a call
   remain in `rQ_80163178/fn_80170F50.cpp`, `fn_80165B48.cpp`, `fn_801662AC.cpp`, `equiv/fn_80167F5C.cpp`,
   `equiv/fn_80168098.cpp`, `equiv/fn_80168BF0.cpp`, `equiv/fn_80169B20.cpp`.
7. **fn_800ED4AC** (`rE_800E5DE4/equiv/fn_800ED4AC.cpp`, `regs`), fixed, still `regs` (10 words, was 12). Battle sequence
   step: fn_801CE474 is `(Handle*)` (`rE_800E5DE4/fn_800ED100.cpp`); the draft called it with no argument, so r3 held
   `*p->h1` (or 0) where the original passes `p->h1`. The effect model name would have been looked up for the wrong
   object (a null dereference when the handle is empty).
8. **fn_8004564C** (`rB_8002E1C4/wip/fn_8004564C.cpp`, `sched`), **not fixed** (wip file). See below.

## Left unfixed

- **fn_8004564C (c)**, `src/game/rB_8002E1C4/wip/fn_8004564C.cpp` lines 77 and 462 (and `wip/fn_8004564C_r17.cpp` line 80).
  Case 47 of the battle event switch looks up a trap with `t = fn_80066130(lbl_803CB770, x, y, 10)` and then calls
  `fn_80117F74(fn_80065E10(), buf)`. fn_80065E10 is `char* (Trap* t)` (matched in `rO_80065D64/fn_80065D64.cpp`): it reads
  four bytes at t+4 as a string offset. The original keeps the trap in r3 and the direction byte in r4; the draft reads
  the byte into r3 and calls fn_80065E10 with it, so the text shown for the trap would be read from a wild offset.
  Fix: `void* fn_80065E10(u8*);` and `fn_80065E10(t)`. Tested copy `build/tmp/r21review2/try/fn_8004564C.cpp`: still
  `sched` (287 words, was 292), symcheck `--xargs` clean.
- The six (b) rows (fn_801681E0, fn_80168558, fn_80164064, fn_80164330, fn_8016A280, fn_80169B20) keep their swapped
  equality compare. All are in `rQ_80163178/equiv/`; the compiler picks the order and no source spelling tried changes it.
- Wrong prototypes or bodies that remain in files outside this review's edit scope are named in the list above
  (`wip/fn_800CCF84.cpp`, `wip/fn_8027247C.cpp`, `wip/fn_8002FFDC.c`, `wip/fn_80020354.cpp`, the three fn_8031292C and
  seven fn_801030B8 declarations). A declaration with too few parameters compiles to the same bytes when the missing
  register happens to be right, so `exact` files were not checked for this and a port should take prototypes from the
  callee's definition.

## Left-overs of the first review

- **fn_80020354 / fn_80020764**: `src/game/rA_800068A0/equiv/fn_80020354.cpp` (new, self-contained, both functions):
  `exact` and `sched` (2 words); symcheck clean and 1 block flagged (stale f1, above).
- **fn_802267D8**: `src/game/rI_801DD7D4/equiv/fn_802267D8.cpp` (new): `sched`, 7 words, the load of lbl_803CA870 is on the
  original's side of the store. One block still flagged (a ptmf copy temporary in r4 at `__ptmf_scall`, target takes `this`
  only); the "dead r27/r28" block of the first review is gone with the `_restgpr` fix.

## Spot-check

`build/tmp/r21review2/all.tsv` is a fresh default run of the changed tool over all 449 rows:

- **`renamed`: all 30 rows clean** (19,480 bytes): fn_8005586C fn_80063A80 fn_800642B4 fn_800649AC fn_8006746C fn_80069220
  fn_8006B528 fn_8006CE30 fn_80085FC4 fn_80088948 fn_800B1120 fn_800C5EA4 fn_800D70F4 fn_800DF0B8 fn_800E24F8 fn_800F15AC
  fn_800F1C30 fn_80103410 fn_8012FA44 fn_8015BD44 fn_80168098 fn_80169558 fn_80177A5C fn_80223580 fn_80246ADC fn_8026A864
  fn_8026AB7C fn_8026D0F8 fn_8027ECA4 fn_80287B54.
- **unflagged `regs`: all 227 rows clean**, among them the 20 drawn at random (seed 21): fn_80009454 fn_8000AB6C fn_80068638
  fn_8006D19C fn_80092F74 fn_800A0998 fn_800C3C3C fn_801116F4 fn_801258D8 fn_801520C0 fn_80158354 fn_8015D768 fn_8015F680
  fn_801635B8 fn_801C4F0C fn_801E8680 fn_8024CCF8 fn_8024CF54 fn_80260E58 fn_802732FC.
- No row that was clean before the tool changes is flagged now; fn_80214C00 and fn_802267D8 (wip) each lost one
  "dead saved register" block.

**"Clean" is weaker than it sounds, though.** The default run compares one block at a time, so an argument prepared in an
earlier block than the call is never compared; fn_8002FFDC and fn_8004564C were both "clean". `--xargs` over all 449 rows
(first pass `build/tmp/r21review2/allx.tsv`, final tool with the fixed files `allx2.tsv`) reported seven rows:

| function | class | result |
|---|---|---|
| fn_8002FFDC | regs | c, fixed (5 above) |
| fn_801689C8 | regs | c, fixed (6) |
| fn_800ED4AC | regs | c, fixed (7) |
| fn_8004564C | sched, wip | c, not fixed (8) |
| fn_802811E8 | regs | a: r7 temporaries differ before `fprintf(stderr, msg)` (fn_80290B48, varargs, so every register counts as read); the original leaves a stale value there too |
| fn_80283BC8 | regs | a: same with r5 |
| fn_8006D790 | sched | a: block ending in an unnamed jump table (already (a) in the first review) |

After the fixes the final run flags only the last four. Six further hits of the first pass (fn_8001F1D4, fn_800B8BC4,
fn_8010436C, fn_80117A84, fn_801C336C, fn_80222E34, plus fn_800FCD10 and fn_80168A90 from the tables above) were a
callee that never writes f1/r3 counting as reading it, and `mftb` in OSGetTick; both are handled in the tool now.

## Tool changes (`tools/equiv/symcheck.py` only)

Stricter or more exact (on by default):
- **`psq_st` / `psq_l` are a store and a load.** They went through the generic path, where the stored register counted as
  defined (the flag in fn_80275FD4 block 0); stack bytes written by `psq_st` are now compared.
- **`bl _restgpr_N` / `_restfpr_N` reload registers N..31.** Without that a dead temporary in a saved register counted as
  live at `blr` (fn_80225650, one block each of fn_80214C00 and fn_802267D8).
- **`FILE.symbols.json`** (the name map `check_regs.py` already passes on) is applied to our side's names and printed as
  `note:` lines (fn_8019AEA8).
- **`mftb`, `mfmsr`, `mfspr` only write their first operand** when a callee's argument reads are worked out.
- **Pointer words in our local data** (`.4byte lbl_X` / `fn_X`) are resolved to the address, so an 8-byte `{ptr, ptr}`
  template is compared by value with the original's `.sdata2` words (fn_80275FD4).

Opt-in, each off by default so that the difference stays visible:
- **`--xargs`**: cross-block argument check. For every direct call, the argument registers the callee reads (worked out
  as under `--virt-this`) and the calling block doesn't set must hold the same value, by register name, in the block that
  sets them. It only adds comparisons. For this check a value that merely survives in r3/f1 to the callee's `blr` is not
  a read (so a callee that just returns its argument is missed). Known artefacts: varargs callees and blocks ending in
  an unnamed jump table. **Run it on every `regs`/`sched` file before saving it in `equiv/`.**
- **`--virt-this`**: when a callee's argument registers are worked out, an indirect call inside it is taken to read r3
  only (default: every register not yet written). An assumption; use it to confirm a "stale register" reading.
- **`--eqsym`**: operand order of a register-register compare is ignored when only the block's own `beq`/`bne` tests it
  and cr0 is dead after.
- **`--ret=none|r3|f1`**: which return register is live at `blr` (default both).

Unchanged limits: `--anon` treats all incoming registers of a class as one value, so two values swapped between blocks
are only seen by `--xargs` (at calls) or the live-out multiset; unsymbolised `lis`/`subi` pairs in the original asm
(fn_8016B3F4) and stack-slot permutations stay flagged.

## Not settled

- The six (b) rows keep a compare the other way round (harmless, no spelling found).
- The "stale register" verdicts for fn_80277E10, fn_801A32BC, fn_800A75E8 and fn_80095514 rest on the virtual lock call
  inside fn_80076F54 / fn_80253EE4 reading `this` only; the target was not identified (the object's vtable is set at run
  time), but the original leaves different leftovers in those registers at its own call sites.
- No tool compares values that cross a block edge in a non-argument register. A `regs` draft that swaps two saved
  registers between blocks would pass everything here; only the `renamed` class rules that out.
- `exact` files with a short prototype (previous section) were not searched.
