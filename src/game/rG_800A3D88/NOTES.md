# Region 0x800A3D88..0x800CCEEC notes

505 of the 538 functions match, covering about 145 KB of the region's 168 KB (about 86%). 33 functions and about 23 KB are left. This count is `build/m2c/matched_names.txt` at the start of the latest round plus the 11 functions that round added, each confirmed with the checker.
Each file below prints MATCH with `python3 -I tools/check_func.py <file> -v`. Paths are relative to this folder.

## Resume point

There is no single address to resume from, because the work jumped around to pick mid-size functions.

Good next targets, in order:
- fn_800BBE94 (`wip/fn_800BBE94.cpp`, 56 of 880 lines, 3520 bytes, right size, registers only). The pointers of the two outer `CurF` loops take r28/r27 where r17/r18 are wanted.
- fn_800AF584 (`wip/fn_800AF584_b.cpp`, 13 of 430). `a_i` against `a_j1`/`a_k1`.
- fn_800AF12C (`wip/fn_800AF12C_b.cpp`, 7 of 278). Three byte shifts want r0 each.
- fn_800B1120 (`wip/fn_800B1120_b.cpp`, 19 of 264), fn_800AC664 (23 of 521), fn_800B8BC4 (23), fn_800C5A34 (39, parameters x and y must outrank bx and by), fn_800A47AC (7). All retried this round without a match.
- fn_800CB69C (4224 bytes). Read but not attempted: it saves r14..r31 and f14..f31 and spills hoisted constants to the stack.

Paired-single: none of the region's functions tagged PS that were checked have `ps_` instructions. fn_800A8CC0, fn_800C4EDC, fn_800C99DC, fn_800CA3DC, fn_800CA7A4 and fn_800CB69C only save and restore float registers with `psq_st`/`psq_l`, and three of them now match. Grep for `ps_` before skipping anything.

## Files

| File | Matches | Functions (address without fn_) |
|---|---|---|
| fn_800A3EFC.cpp | 13 | 800A3EFC 800A3F68 800A3F74 800A3F80 800A3F8C 800A3F94 800A4048 800A4060 800A41AC 800A4224 800A4298 800A4318 800A439C |
| fn_800A471C.cpp | 16 | 800A471C 800A4AE4 800A4B00 800A4B18 800A4B30 800A4B40 800A4BBC 800A5D34 800A5D68 800A6100 800A633C 800A6440 800A6490 800A64A0 800A6578 800A66B0 |
| fn_800A7528.cpp | 33 | 800A64AC 800A6588 800A6618 800A66C4 800A6790 800A67EC 800A6B7C 800A6BD4 800A6C38 800A6D08 800A6D7C 800A6F34 800A7324 800A7370 800A7460 800A7528 800A7948 800A7B38 800A7C28 800A7CE8 800A7D44 800A7E34 800A7EEC 800A7FAC 800A8008 800A80F8 800A81AC 800A8208 800A82C8 800A8324 800A83E4 800A85CC 800A8B70 |
| fn_800A9110.cpp | 14 | 800A9110 800A915C 800A9160 800A91B0 800A91C0 800A93B8 800A98C0 800A99C4 800A9FC8 800AA2BC 800AA360 800AA400 800AA444 800AA4C0 |
| fn_800AA848.cpp | 22 | 800AA848 800AA97C 800AAA38 800AAAF8 800AAB14 800AAB1C 800AAB38 800AAB8C 800AAB94 800AABB4 800AABD0 800AABEC 800AAC14 800AAC3C 800AAC64 800AAC68 800AAC98 800AAD1C 800AAD2C 800AAD38 800AAD44 800AAD54 |
| fn_800AB1D0.cpp | 21 | 800AB1D0 800AB310 800AB988 800ABD80 800ACE88 800AD954 800ADC84 800ADC88 800ADCE8 800ADD08 800ADD10 800ADD54 800ADDB8 800ADE58 800ADECC 800ADF64 800ADFA4 800AE03C 800AE0A8 800AE13C 800AE230 |
| fn_800ADD0C.cpp | 10 | 800ADD0C 800ADD38 800ADD3C 800ADD40 800ADD44 800ADD48 800ADD4C 800ADD50 800ADE54 800AE138 |
| fn_800AE4AC.cpp | 24 | 800AE4AC 800AE4FC 800AE58C 800AE61C 800AE634 800AE644 800AE654 800AE688 800AE6C8 800AE714 800AE754 800AE88C 800AE8B8 800AE8E4 800AE8F4 800AEBD4 800AEC54 800AEC70 800AF054 800AF078 800AF07C 800AF104 800AF114 800AF120 |
| fn_800AEE68.cpp | 9 | 800AEE68 800AEEFC 800B0244 800B027C 800B033C 800B053C 800B0554 800B0BF4 800B0C28 |
| fn_800B1540.cpp | 17 | 800B1540 800B1628 800B1728 800B26B0 800B2944 800B2958 800B2994 800B5C3C 800B5CDC 800B6570 800B7260 800B9CA8 800BBAE0 800BCC54 800BD218 800BD22C 800BD280 |
| fn_800B5784.cpp | 1 | 800B5784 |
| fn_800BA1C0.cpp | 32 | 800BE340 800BEBD4 800BED98 800BEE18 800BEE1C 800BEE20 800BEEA0 800BEEB0 800BEEBC 800BEEC8 800BEED0 800BEED8 800BEEEC 800BEEF4 800BF0B4 800BF138 800BF568 800BF750 800C0988 800C09E0 800C0A18 800C0A34 800C0A50 800C0A6C 800C0EE4 800C0EFC 800C0F20 800C0F44 800C1064 800C1184 800C11B8 800C1218 |
| fn_800C1220.cpp | 25 | 800C1220 800C1280 800C1340 800C13A4 800C229C 800C22B0 800C2310 800C2364 800C23C8 800C2D60 800C2D88 800C2DE8 800C2DFC 800C2E84 800C2F24 800C2F88 800C32EC 800C3300 800C3374 800C3460 800C3558 800C3560 800C3568 800C357C 800C3584 |
| fn_800C358C.cpp | 22 | 800C3784 800C3840 800C3A48 800C3B1C 800C3BC8 800C3CF0 800C3D30 800C3DF0 800C3E70 800C3EE0 800C3F64 800C3FD0 800C400C 800C4020 800C4058 800C409C 800C4210 800C4240 800C429C 800C42F8 800C4348 800C43B0 |
| fn_800C4A58.cpp | 27 | 800C4A58 800C4AA8 800C5D3C 800C5D4C 800C5D58 800C5D90 800C5E44 800C63F0 800C642C 800C6450 800C660C 800C6ADC 800C6BD8 800C6C58 800C6CE4 800C6D40 800C6D9C 800C6DF8 800C6E78 800C6F04 800C6F84 800C7010 800C70BC 800C7114 800C716C 800C71CC 800C7230 |
| fn_800C725C.cpp | 16 | 800C725C 800C7324 800C73D0 800C7400 800C74F0 800C755C 800C7680 800C777C 800C7B14 800C7B18 800C7B50 800C7F90 800C7FA0 800C7FC4 800C7FE8 800C7FF4 |
| fn_800A59A4.cpp | 3 | 800A6844 800A59A4 800A947C |
| fn_800A5DE8.cpp | 5 | 800A5DE8 800AE368 800ACF58 800AC418 800AC52C |
| fn_800A91C4.cpp | 1 | 800A91C4 |
| fn_800AA548.cpp | 1 | 800AA548 |
| fn_800AADBC.cpp | 7 | 800AADBC 800AAE94 800AAF20 800BA1C0 800BE940 800A6340 800A8B80 |
| fn_800AAFAC.cpp | 5 | 800ADA7C 800AAFAC 800A9E64 800AE774 800AEC8C |
| fn_800AB734.cpp | 1 | 800AB734 |
| fn_800ABAE4.cpp | 4 | 800ABAE4 800ABC3C 800ABE64 800AC284 |
| fn_800ABFB8.cpp | 2 | 800ABFB8 800AD740 |
| fn_800B056C.cpp | 11 | 800B7468 800B591C 800B196C 800B4574 800B727C 800BD024 800B5010 800B5DF0 800B61B0 800B056C 800B08B0 |
| fn_800B175C.cpp | 1 | 800B175C |
| fn_800B33F4.cpp | 6 | 800B6E2C 800B69D8 800BBB1C 800B33F4 800BCC5C 800B54DC |
| fn_800B377C.cpp | 5 | 800B377C 800B3824 800B38F0 800B41C0 800B65F8 |
| fn_800B5D14.cpp | 5 | 800B5D14 800BF444 800BF608 800C86D4 800C986C |
| fn_800B7F98.cpp | 3 | 800B93F8 800B7F98 800C0A88 |
| fn_800B8810.cpp | 2 | 800B8810 800BAB5C |
| fn_800BCF10.cpp | 2 | 800BEF58 800BCF10 |
| fn_800BE2BC.cpp | 1 | 800BE2BC |
| fn_800C0BD0.cpp | 2 | 800C0BD0 800C0D4C |
| fn_800C48A8.cpp | 3 | 800C48A8 800C4AAC 800C4C3C |
| fn_800C6210.cpp | 2 | 800C6634 800C6210 |
| fn_800C9230.cpp | 5 | 800C9230 800C9EC0 800C9F0C 800CAB40 800C92CC |
| fn_800CABA0.cpp | 7 | 800CABA0 800CB0FC 800CAD6C 800CAF38 800CB278 800CB3A8 800CB520 |
| fn_800CC71C.cpp | 5 | 800CC71C 800CC8AC 800CCA3C 800CCBCC 800CCD5C |
| fn_800A8660.cpp | 1 | 800A8660 |
| fn_800A6F98.cpp | 1 | 800A6F98 |
| fn_800C67F8.cpp | 1 | 800C67F8 |
| fn_800BF798.cpp | 1 | 800BF798 |
| fn_800BF148.cpp | 1 | 800BF148 |
| fn_800A4420.cpp | 1 | 800A4420 |
| fn_800B75FC.cpp | 1 | 800B75FC |
| fn_800B9D18.cpp | 1 | 800B9D18 |
| fn_800A53DC.cpp | 1 | 800A53DC |
| fn_800B3138.cpp | 1 | 800B3138 |
| fn_800AFC3C.cpp | 1 | 800AFC3C |
| fn_800B4000.cpp | 1 | 800B4000 |
| fn_800AE940.cpp | 1 | 800AE940 |
| fn_800BEA14.cpp | 1 | 800BEA14 |
| fn_800BB074.cpp | 1 | 800BB074 |
| fn_800C8D80.cpp | 1 | 800C8D80 |
| fn_800C83DC.cpp | 1 | 800C83DC |
| fn_800C87A0.cpp | 1 | 800C87A0 |
| fn_800C93C0.cpp | 1 | 800C93C0 |
| fn_800C7B74.cpp | 1 | 800C7B74 |
| fn_800C8000.cpp | 1 | 800C8000 |
| fn_800BD86C.cpp | 1 | 800BD86C |
| fn_800BDD94.cpp | 1 | 800BDD94 |
| fn_800BD294.cpp | 1 | 800BD294 |
| fn_800B8FF8.cpp | 1 | 800B8FF8 |
| fn_800B99DC.cpp | 1 | 800B99DC |
| fn_800C8778.cpp | 24 | 800C835C 800C8778 800C8C3C 800C8C90 800C8CE4 800C8CF4 800C8D1C 800C900C 800C9020 800C9030 800C9054 800C9078 800C9108 800C916C 800C919C 800C9244 800C9280 800C96A8 800C9718 800C9770 800C97C0 800C9D58 800C9D60 800C9EB8 |
| fn_800B4240.cpp | 1 | 800B4240 |
| fn_800A95F4.cpp | 1 | 800A95F4 |
| fn_800A5F08.cpp | 2 | 800A5F08 800A614C |
| fn_800C242C.cpp | 1 | 800C242C |
| fn_800C283C.cpp | 1 | 800C283C |
| fn_800C14F0.cpp | 1 | 800C14F0 |
| fn_800BFA4C.cpp | 1 | 800BFA4C |
| fn_800BFE24.cpp | 1 | 800BFE24 |
| fn_800C0478.cpp | 1 | 800C0478 |
| fn_800C43C4.cpp | 1 | 800C43C4 |
| fn_800BE3B4.cpp | 1 | 800BE3B4 |
| fn_800B951C.cpp | 1 | 800B951C |
| fn_800BB520.cpp | 1 | 800BB520 |
| fn_800AFDFC.cpp | 1 | 800AFDFC |
| fn_800B3A1C.cpp | 1 | 800B3A1C |
| fn_800BA2C8.cpp | 1 | 800BA2C8 |
| fn_800C57B0.cpp | 1 | 800C57B0 |
| fn_800B9884.cpp | 1 | 800B9884 |
| fn_800BB3DC.cpp | 1 | 800BB3DC |
| fn_800A5B84.cpp | 1 | 800A5B84 |
| fn_800A7770.cpp | 1 | 800A7770 |
| fn_800B0340.cpp | 1 | 800B0340 |
| fn_800A9A74.cpp | 1 | 800A9A74 |
| fn_800A5120.cpp | 1 | 800A5120 |
| fn_800A526C.cpp | 1 | 800A526C |
| fn_800A4BDC.cpp | 1 | 800A4BDC |
| fn_800C6468.cpp | 1 | 800C6468 |
| fn_800A3D88.cpp | 1 | 800A3D88 |
| fn_800B2810.cpp | 1 | 800B2810 |
| fn_800AD068.cpp | 1 | 800AD068 |
| fn_800CA1B4.cpp | 1 | 800CA1B4 |
| fn_800A8CC0.cpp | 1 | 800A8CC0 |
| fn_800CA3DC.cpp | 1 | 800CA3DC |
| fn_800B2710.cpp | 1 | 800B2710 |
| fn_800BEC84.cpp | 1 | 800BEC84 |
| fn_800C99DC.cpp | 1 | 800C99DC |
| fn_800A79A4.cpp | 1 | 800A79A4 |
| fn_800AB41C.cpp | 1 | 800AB41C |
| fn_800C18A4.cpp | 1 | 800C18A4 |
| fn_800C9FA4.cpp | 1 | 800C9FA4 |
| fn_800CA0A4.cpp | 1 | 800CA0A4 |
| fn_800CA7A4.cpp | 1 | 800CA7A4 |
| fn_800C4EDC.cpp | 1 | 800C4EDC |
| fn_800B79AC.cpp | 1 | 800B79AC |
| fn_800B8154.cpp | 1 | 800B8154 |
| fn_800B4744.cpp | 1 | 800B4744 |
| fn_800B1B48.cpp | 1 | 800B1B48 |
| fn_800B29D0.cpp | 1 | 800B29D0 |
| fn_800B0CD4.cpp | 1 | 800B0CD4 |
| fn_800B663C.cpp | 1 | 800B663C |
| fn_800C219C.cpp | 2 | 800C219C 800C31EC |

Functions are not strictly in address order inside `fn_800A7528.cpp` and a few other files. I did not reorder them, because `-inline auto` makes order significant in files without `#pragma auto_inline off`.

Near misses in `wip/`. Stale copies of matched functions remain there too, because files are never overwritten or deleted: fn_800AD068, fn_800AB41C, fn_800B2710, fn_800BEC84, fn_800C18A4, fn_800CA7A4, fn_800C4EDC, fn_800B0CD4, fn_800B663C, fn_800C219C and fn_800C31EC, and fn_800C9FA4 and fn_800CA0A4 inside `wip/fn_800C9230.cpp`. Where a `_b` file exists, it replaces the older file of the same name.

| Function | File | Cause |
|---|---|---|
| fn_800A3FA4 | fn_800A3FA4.cpp | 9/41, float registers |
| fn_800A4A98 | fn_800A4A98.cpp | one word short, `beq` over `b` |
| fn_800A6DE4, fn_800A75E8 | fn_800A6DE4.cpp | 13/84, 77/98, colours in the nested lookups |
| fn_800A84A4 | fn_800A84A4.cpp | 15/74, n/e/i colours and stack slots |
| fn_800AE500, fn_800AE774 | fn_800AE500.cpp | 8/35, 5/70, r30/r31 swap |
| fn_800C0894 | fn_800C0894.cpp | two words short, field must be reloaded |
| fn_800C358C | fn_800C358C.cpp | one word short: an unreachable `b` after the first infinite loop |
| fn_800C3974 | fn_800C3974.cpp | 12/53, r30/r31 swap |
| fn_800C3C3C | fn_800C3C3C.cpp | 12/45, volatile registers. This is the script command registrar. |
| fn_800C6118 | fn_800C6118.cpp | frame and argument shuffle |
| fn_800C763C, fn_800C7850, fn_800C78FC, fn_800C79A0 | fn_800C7850.cpp | registers, unrolled loop bases |
| fn_800C7A98 | fn_800C7A98.cpp | 16/30, size 0x78 vs 0x7C |
| fn_800C9084 | fn_800C9084.cpp | 13/33, r30/r31 swap; also needs `addi r3,r30,0`, which a `base + 0` folds away |
| fn_800C4DDC | fn_800AADBC.cpp | 7/64, one `lfs` scheduled before `mr r5` |
| fn_800C4104, fn_800A40B4, fn_800C9918 | fn_800B5D14.cpp | switch shape; float registers; float registers |
| fn_800C5EA4 | fn_800C6210.cpp | one word over, registers |
| fn_800AC664 | fn_800AC664.cpp | 23/521, second inlined hit. A separate `Hit2` with a nested inline moves c to r28 but then swaps hp and sl |
| fn_800A4D88 | fn_800A4D88.cpp | 72/230, t must outrank both parameters |
| fn_800A6978 | fn_800A6978.cpp | 14/129, registers |
| fn_800B1120 | fn_800B1120_b.cpp | 19/264, nm against k1/b/e |
| fn_800A47AC | fn_800A47AC.cpp | 7/187, scheduling of one `lfs` constant against the y store |
| fn_800B8BC4 | fn_800B8BC4.cpp | 23/269, only the 0.0f constant's float register |
| fn_800C5A34 | fn_800C5A34.cpp | 42/194 (39 after a search that was not kept), right size, ranks only |
| fn_800AF584 | fn_800AF584_b.cpp | 13/430, one rank swap |
| fn_800AF12C | fn_800AF12C_b.cpp | 7/278, byte shift registers |
| fn_800BBE94 | fn_800BBE94.cpp | 56/880, registers only |
| fn_800C91C8 | fn_800C9230.cpp | `addi r0,r5,0` (pooled statics) |

## Subsystems (guessed names)

- **0x800A3EFC..0x800A439C small effects:** wobble process `lbl_80381E58`/`lbl_80381E80` that moves a target's +0x40/+0x44 on a sine.
- **0x800A471C..0x800A6440 battle body** (`Body` in fn_800A471C.cpp): shake at +0x88.., camera target at +0x94/+0x98, view flags.
- **0x800A64AC..0x800A85CC data tables:** blobs read through `fn_80109A2C` (first read returns the count). `Count`/`Data`/`TBL_COUNT`/`TBL_DATA` in fn_800A7528.cpp wrap this. Tables and entry sizes: `lbl_804CB650` 0x154, `lbl_804CB658` 0x18, `lbl_804CB664` 0x18, `lbl_804CB668` 0x10, `lbl_804CB66C` 8, `lbl_804CB670` 0x14, `lbl_804CB674` 0x24, `lbl_804CB678` 8, `lbl_804CB67C` 0xC, `lbl_804CB680` 0xC, `lbl_804CB684` 0x14, `lbl_804CB688` 0x10, `lbl_804CB68C` 0x48, `lbl_804CB694`/`698` name lists, `lbl_804CB69C` 8 (name, int, the tuning-value table behind fn_800A84A4), `lbl_804CB65C`/`660` 0x14.
- **0x800A9110..0x800AAE94 battle scene helpers:** `Ev` (0x5C bytes, fn_800AA848.cpp) wraps a model at +0x50, with visibility, alpha and tint pushed by `Ev_Sync`.
- **0x800AB1D0..0x800AE368 battle scene controller** (`Battle` in battle.h): a process whose states are the `fn_800ADxxx` entries. `lbl_803C8E80` (`SceneGlobal`) carries the scene flags at +0x15EC.
- **0x800AE4AC..0x800AE8B8 battle/event boundary:** BGM (`+0x1600`), fade, script call.
- **0x800AEBD4..0x800AF120 picture process** `PicP`.
- **0x800B1540..0x800BD280 battle character** (`Chr` in chr.h, `ChrB`, `ChrE`): model +0x30, data +0x78, anim state +0x7C, effects +0x3C[2], flags +0x50.
- **0x800BE2BC..0x800C1218 attached effect** (`Eff` in fn_800BA1C0.cpp): model +0x34, data +0x38 from table `lbl_804CB674`, fade state +0x9C..+0xA6, flags +0x46.
- **0x800C1220..0x800C3460 title/logo slides** (`Title`, `Title3`, `TweenB`, `TweenS`): file name from `lbl_80382650[lang][wide]`; generic tweens on a u8 or s16 field use `fn_8017F68C(mode, from, to, t, n)`.
- **0x800C3558..0x800C3C3C script container:** `.cmb` files with magic `cmb` and a 4th byte of `S` when suspended. `CmbFile`/`CmbCmd` are in fn_800C358C.cpp; files sit in a list at `lbl_804CB6A0`, last error `lbl_804CB6B8`. `fn_80076D48`/`fn_80077174` register and unregister a name in the hash. fn_800C358C byte-swaps and relocates a file. fn_800C3C3C registers a native command.
- **0x800C3CF0..0x800C4348 character/face files:** `lbl_80365E0C` strings, narrow/wide by `fn_801D09F0`; 8 face slots at `lbl_803E50D0`.
- **0x800C5D3C..0x800C7B50 face objects:** `Face`, `FaceAnim`, fade procs, and the cache at `lbl_803E7200` (`FaceCache`: res, key, delete timer, refcount).
- **0x800C7F90..0x800C9D60 screen effects:** pad-like state objects `lbl_804CB6D0..DC` with state word at +0x32; TEV setup in fn_800C9770/fn_800C97C0.

## Lessons

- **Constant registers:** among volatile registers, the first constant encountered in the source appears to take the highest free one (seen in these two functions, not tested more widely). To swap `li r4,0` and `li r5,1`, move the first use (`e->m30 = 1;` first). This fixed fn_800AF054 and fn_800AA444.
- **Declare, then assign:** `u8 a, b, c; c = p[2]; b = p[1]; a = p[0];` gives registers by declaration order and loads by statement order. This fixed the byte-swap inline and fn_800C409C. Writing `int i = ...` in one line can't separate the two.
- **Bare blocks versus inlines:** `{ u8* r = t; n = read(&r); read(&r); }` colours differently from a nested inline. Table lookups inside an inline only matched with bare blocks (the `TBL_*` macros), while the same lookup at function level matched as nested inlines.
- **Single-case switch:** `beq A; b B; A: ...` comes from `switch (x) { case 0: ...; default: ...; }`, not from `if`/`goto` (fn_800AE13C).
- **Long-lived constants:** `li r31,0` kept across calls comes from a local `int z = 0` (fn_800C13A4).
- **`(x & 2) != 0` as neg/or/srwi:** that form needs an inline returning `u16` (`EffFlag`). Written directly it gives `extrwi`.
- **Ternary arguments:** `fn(lbl, p == NULL ? (void*)3 : p)` keeps the first argument loaded before the test (fn_800C22B0).
- **Toggle:** `int f = !e->m4c; e->m4c = f; ... (u8)f` gives `srwi` then `clrlwi.` (fn_800AA97C).
- **Delay:** `(BUS / 4 / 1000) * 5LL` reproduces the 64-bit tick multiply with the dead `0 * 5` (fn_800A6618). `5ULL` folds it.
- **Unreachable `r4`:** a `lis r4` right before a call with no `r4` argument may just be scratch (fn_800C9280). A plain passthrough means a second parameter (fn_800C70BC).
- **PS tag:** the region scan flags any `psq_l`. A single `psq_l` in the epilogue is only an FP restore.
- **Inlined effect lookup (fn_800B5784 family):** callers inline fn_800B5784 four levels deep, but no `inline_depth` or `inline_max_size` setting makes the compiler do that outside the function itself. Write the levels by hand as `E1`..`E4` and `Cur`, as in fn_800B056C.cpp. Pass every loop counter, loop pointer and result as a reference to a caller local, and step an explicit pointer (`q = (ChrE*)((u8*)q + 4)`) instead of indexing.
- **Declaration order is register order:** with counters and pointers as caller locals, listing the locals by descending target register reproduces the allocation. Two sequential chains can share a register, so list both at that rank. Parameters can outrank locals; when one is rotated, `hill` over the same list usually fixes it.
- **Explicit pointers instead of compiler induction variables:** a compiler-made induction variable ranks against the locals in a way declarations can't change. An explicit pointer can be placed (fn_800A91C4, fn_800BE2BC).
- **Loop body in an inline:** moving a loop or its body into a `static inline` changes which locals rank highest (fn_800AB734, fn_800ADA7C).
- **Value must land in the argument register:** `li r4,-1; b; bl; mr r4,r3` comes from `int k; if (m == NULL) k = -1; else { int t = f(m); k = t; }`. Without `t`, the result coalesces with r3 and gives `li r3,-1`. This fixed six functions, including fn_800B377C and fn_800B175C.
- **Pointer compare order:** a pointer compare keeps `cmplw table, value`, while `u32` operands canonicalize to `cmplw r3, r0` (fn_800CC71C).
- **Fixed stack order with word copies:** declare every slot at function level, use out-parameters and copy with `*(W3*)&v = *(W3*)&t` to get `v`/`t` pairs in declaration order (fn_800AD740).
- **Hex literals:** `0x5E-0x58` is a lexer error, because `E-` reads as an exponent.
- **Doubled `beq cr1`:** a second `if (p != NULL && ...)` on a pointer tested earlier re-tests the saved compare (fn_800BEF58).

- **Natural-locals recipe:** when temporaries sit in the wrong stack order, declare named locals from the highest offset down, and copy with `*(W3*)&a = *(W3*)&b` (words) or `a = b` (floats). Zero with `*(u32*)&v.x = 0` or a union member. Slots then follow declaration order exactly, which solved fn_800B3138, fn_800BB074, fn_800BEA14, fn_800BD86C and others without any frame struct.
- **Grouped copies:** two word copies stay grouped as all loads then all stores only when source and destination are separate locals. Inside one aggregate they stay in statement pairs.
- **Dead stack stores:** zero stores to a local nothing reads survive when written through `*(u32*)&v.x`, but a union or plain array is removed (fn_800B8FF8).
- **`const char* const& n`:** an inline parameter of this type computes the string address before the null test, as `lis r3; addi r3; addi r4,r3,off` (fn_800B9D18, fn_800B4240). A plain `const char*` computes it after the branch.
- **`T t = f(); v = t;` works for floats too:** it fixes `lfs f31` versus `lfs f1` on a branch that skips `fmr` (fn_800B9D18).
- **`(f32)__fabs` temp registers:** `double a = __fabs(x); if ((f32)a <= k)` gives `fabs f3; frsp f1,f3`. For a compare of two values, write `double p1, p2; f32 q2 = p2; if ((f32)p1 > q2)` (fn_800BD294, fn_800B99DC).
- **Induction form:** `for (i...; i++, e++)` on a sized struct gives the 8x unrolled loop with `ctr` and its range checks; a stepped `(u8*)` pointer does not (fn_800A8660).
- **Unrolled retry loop:** dead `bl; b` blocks between iterations come from `for (j = 0; j < 3; j++) { if (j == 2) { f(); break; } if (!test) break; ... }` (fn_800B75FC).
- **Copy before zero:** `li r0,0` with loads in r7,r6,r5 needs the word copy written before the zero stores in the source (fn_800BD86C).
- **Inline locals against parameters:** moving a block into an inline can lift its locals above the caller's parameter (fn_800AFC3C). It did not help fn_800A4D88 or fn_800B0CD4, so this isn't a general rule.
- **Tried with no effect on the recursion or stack-order mysteries:** `inline_depth`, `inline_bottom_up`, `defer_codegen`, `inline_max_size`, command-line `-inline` levels, other GC compiler versions, and about 30 `opt_*` pragmas.

- **Hand-written bodies:** writing a function from the asm as ordinary C++ (variables declared where first used, real nested inlines, tween and lookup blocks as helpers) beat permuting near misses by a wide margin. fn_800B3A1C (1508 bytes), fn_800C43C4 and fn_800B951C needed almost no tuning.
- **Fresh variable for a new value:** a block-scoped `ChK* o2 = c->m80;` instead of reassigning `o` changes the register (fn_800B4240), and so does moving a declaration inside the `if` that uses it (`Cam* r = b->m7c;` in fn_800A5F08). `int m2 = f(); m = m2;` swapped two ranks in fn_800A95F4.
- **Reference parameter to keep a caller rank:** passing a caller local as `Bone*& c` to an inline puts it among the caller's locals while the inline's locals rank above the parameter (fn_800BFA4C). Moving the loop or the lookup block into an inline is what lifted the parameter there.
- **A long-lived value in a parameter register:** when a parameter shares a high register with a later value, declare the later value as a local before the others instead of reassigning the parameter (`int tw, th;` in fn_800C57B0).
- **Temporaries in order:** named locals at the top, an aggregate-initialised template mid-block, and each lower temporary inside its own inline reproduce a whole descending stack (fn_800BFE24, fn_800BB520). One more nesting level moves a temporary below its siblings (`MkA2` in fn_800A9A74, `Hand2` in fn_800BB520).
- **Template copies:** `lis; lwzu; lwz 4; lwz 8` is an aggregate initialiser (`Vec k = {1.0f, 0.0f, 0.0f};`, `u16 ids[5] = {...}`), not a copy from the `lbl_` extern.
- **Sum into the operand's register:** `f32 rz = a->z + z; f32 ry = a->y + y; c->x = a->x + x; c->z = rz; c->y = ry;` and `z = a->z + z; y = a->y + y;` give different float registers for the same code. A statement-order search does not cover these forms, so try them by hand (fn_800B951C, fn_800BE3B4).
- **Dead `b` in a switch:** an unreachable `b` after a case comes from `return` inside a switch in an inline, where `goto` is threaded away (fn_800B0340).
- **Elided lowest case:** `cmpwi 1; beq; bge X; b end; X: cmpwi 3; bge end` needs a `case 0:` that only breaks, so the pivot lands on 1 (fn_800C5A34).
- **Register chain at a call:** `mr r3,r31; mr r4,r3; mr r5,r3` is a `u8` local passed to `u8` parameters three times (fn_800C57B0).
- **Search note:** `sw.py` needs an absolute `argv[0]`, because it takes its directory from that path, and `perm.py` only works from the project root. Don't run a `multiprocessing` script from stdin: the workers can't re-import it and the pool respawns forever.

- **Integer type moves a rank:** changing a local's type moves its register with no other code change. `s16` on `h`, `e4`, `a2`, `a4`, `ox` and `oy` took fn_800C18A4 from 63 lines to 0 where declaration order had stalled, and `bool isF` instead of `BOOL` solved fn_800AD068. Try this before permuting.
- **Keeping an `extsh` on a clamped local:** the compiler drops `(s16)v` when every definition of `v` is known to fit. Read the value through an inline returning `int` (`Hp` in fn_800AD068) to keep it. A direct `->m6 = hp` after a call evaluates the cast before the call, so assign the call result to a named pointer first.
- **`li r0,0; ori r0,r0,K` on a field:** `c->flags = 0; c->flags |= K;` (fn_800B2710, fn_800BEC84).
- **`fmr` from a hoisted constant:** `f32 u0 = 0.0f; b0 = u0; f(..., u0, b0);` shares one hoisted register in a loop. A literal argument reloads each time (fn_800A8CC0).
- **`frsp` into a lower register:** route the call through an inline returning `f32` (`Ac` in fn_800A8CC0).
- **`lbl_` read as `lwz @sda21`:** a hoisted `lis` pair instead means the extern is declared as an array when it is a word. Two extra saved registers in fn_800AB41C came from this alone.
- **Scorer blind spot:** `sw.py` scores by position, so a one-word length difference hides every improvement. "start N, final N" on a wrong-size function says nothing about declaration order. Fix the size first.
- **Search nesting forms as a product:** bare block, inline, or nested inline for each table read, crossed with a few declaration orders, solved fn_800A79A4's stack in under a minute.
- **Stepping the whole object:** `q = (Bat*)((u8*)q + 4)` with `q->e[0]` keeps `mr rN,this; lwz 0x3C(rN)` and can be ranked, where `b->e[i]` makes an induction variable that can't (fn_800AB41C).
- **Dead use to keep a value:** the unroller recomputes `n - 1` unless that value is live afterwards. `u32 m = n - 1; s16 j = m; ...; n = m;` keeps it in a register (fn_800CA1B4).
- **`lwz 4(r3); addi r3,r3,4` without `lwzu`:** go through a local base (`Res* u = R; if (u->p) f(&u->p);`). A direct `R->p` gives `lwzu` (fn_800CA0A4).
- **`__alloca(n)`** reproduces the dynamic frame (`neg; clrrwi; stwux`, r31 as frame pointer) in fn_800CA1B4.
- **Parameter register through reuse:** reassigning a dead parameter gives its register to a value that otherwise takes the lowest free one, but only for the first such web. A second reassignment splits off (fn_800C4EDC, unsolved).

- **Effect-lookup recipe:** with `efflookup`-style `Cur`/`CurF`/`E4` and named stack locals, the fn_800B5784 family writes almost straight from the asm. Give every inlined lookup its own set of locals, one per `/*P*/` line, list them by descending target register across all blocks, then run `sw.py`. This took fn_800B79AC from 112 lines to 0 where shared locals had stalled at 76.
- **Named locals instead of a frame struct:** declaring each stack slot as a local from the highest offset down gave the right frame and even the right scheduling for fn_800B8154, fn_800BBE94 and fn_800AF584.
- **`f32 v = (u32)x; v = v / k;`:** splitting the conversion from the divide moved the conversion's hoisted double from the top float rank to the bottom (fn_800CA7A4, 17 lines to 0).
- **Literal instead of a named zero:** `f32 z = 0.0f; a->m4 = z;` colours the constant after the loads, and literal `0.0f` stores colour it first (fn_800B29D0, 30 lines). This did not help fn_800B8BC4.
- **Overflow into a saved register:** when r3..r12 are all busy, a value that doesn't cross a call takes a saved register. Which one depends on what is coloured by then, so an unexplained saved register in a volatile-looking block is a rank question (fn_800C4EDC). A dead parameter reassigned there (`x = (int)&k`, `a = (int)(c + o)` in fn_800B4744) takes the parameter's register.
- **Direct global uses share one temp across branches:** `STR(n)` in both arms of an `if` gave one register for the address, where a named `base` in each arm split into two (fn_800B8154).
- **Pair moves:** `sw.py` moves one line at a time, so a swap between two lines that must cross at once needs both moved together. A search over all positions of two lines took fn_800B29D0 from 40 lines to 6 and fn_800AF584 from 17 to 13.
- **Register args hidden by a wrong prototype:** `lbz r4; lbz r5; lbz r6` just before a call are arguments. A one-parameter prototype for fn_80008F10 cost a long search in fn_800B29D0 before this showed up.
- **Read through the stored pointer:** `u8* a = &t->m36; p->p = a; p->from = *a;` keeps the address in r4 and fixed fn_800C219C and fn_800C31EC.
- **`f32& v` out-parameter with a reused result:** `Radius(c, ..., v1); v1 = e - v1; Radius(o, ..., e); d = v1 - e;` fixed the float registers of fn_800B663C.
- **Sequential clears don't always fold:** `c->m50 &= ~0x100; c->m50 &= ~0x600000;` kept two `rlwinm` in fn_800B1B48, with the byte stores after them.
- **`if (f(x))` on a float** gives `fcmpu f1,f0`, while `f(x) != 0.0f` puts the literal first (fn_800B0CD4).

## Caveats

- **Struct names and fields are guesses.** Sizes and offsets are only as good as the accesses seen so far.
- **The hand-unfolded effect lookup is not the original source.** fn_800B056C.cpp, fn_800B175C.cpp, fn_800B33F4.cpp and fn_800B8810.cpp hold copies of `E1`..`E4` and `Cur` with reference parameters and declaration orders found by search. The original is almost certainly one recursive `fn_800B5784` call, compiled in a way not yet reproduced.
- **Other register-driven spellings:** `int t = f(); k = t;`, the explicit pointer steps in fn_800A91C4 and fn_800BE2BC, the `base`/`off` locals in fn_800C6210, the `W3` and `Vg` casts in fn_800AD740 and fn_800AA548, `int d = 4` in fn_800C0A88 and `*(u32*)&a` copies in fn_800BCF10 were chosen to produce the code, not read from anything. Declaration orders found by `hill` say nothing about the source.
- **Prototypes vary between files:** there is no shared header, so the same `fn_` can be `void*` in one file and `int` in another. fn_800C09E0 is defined as `u8` here but declared `int` in fn_800B5784.cpp because the caller shows no `clrlwi`. That may mean the real return type differs, or that the call happens inside the same class.
- **Non-source-faithful spellings** that match but probably don't reflect the original:
  - `ZERO_VEC` and the `*(u32*)&v.x = 0` stores (fn_800A9110, fn_800B5C3C, fn_800BEEF4). The original likely had a Vec constructor.
  - `(void*)3` as a parent (process tree constants).
  - The `int z` locals.
  - `TBL_*` macros in place of the original reader class.
- **Dead declarations:** a few functions declare one more parameter than they use, kept where a register suggests it (fn_800C6118 in `wip/`, fn_800C5D58 passing +0x34 as a second argument). fn_800C5D58's second argument may be only a scratch load.
- **More spellings chosen to produce the code:** the `W3`, `VU` and `*(u32*)&` copies in this round's files, `Radius(..., f32& v)` in fn_800BD86C, fn_800BDD94 and fn_800BD294, the explicit offset `o` in fn_800AFC3C, `FindN`'s `nm` copy in fn_800A6F98, and the unused zeroed `v8c` in fn_800B8FF8. Originals probably used a Vec class with constructors and by-value parameters, and the stack layout that gives is the mirror of what this compiler produces from that source, which is not understood.
- **`.cpp` everywhere:** all files are C++ with `extern "C"`. `battle.h`, `chr.h` and `types.h` are specific to this region.
- **Spellings from this round chosen to produce the code:** `Hand`/`Hand2`, `Send`/`Send3` and `Cur` in fn_800BB520, `Get` and `Warn` in fn_800BFE24, `MkA2`, `Upd0`/`Upd1`/`Upd5` and the `pa`/`pb` pointers in fn_800A9A74, `Add1`..`Add3` in fn_800BE3B4 (the same operation written three ways), `Link` with `Bone*& c` and `sc` in fn_800BFA4C, `Pan` with its reversed `Col x6..x1` in fn_800C242C and fn_800C283C, `int m2` in fn_800A95F4, `y2` in fn_800C14F0, the `(int)` compare in fn_800B2810. The originals probably used Vec operators and constructors.
- **Guessed meaning:** names such as `Bob`, `Stretch`, `Blink` and the struct fields in this round's files come from the asm alone. Prototypes for `fn_800E48C8`, `fn_800A4AE4` and `fn_800B93F8` take pointers here where the source likely passed `Vec` by value.
- **Spellings from the latest round chosen to produce the code:** `n = m` as a dead store in fn_800CA1B4; `(int)((u8*)cb + (l + ca))` in the wip fn_800C4EDC; `Hp` and the named `UP* u` in fn_800AD068; the `UnX` member type, `MC` inline, stepped `Bat*` pointers and `u8* rb; u8* ra` in fn_800AB41C and fn_800A79A4; `s16` on `a2`, `a4`, `h`, `e4`, `ox`, `oy` in fn_800C18A4; `bool isF` in fn_800AD068; `flags = 0; flags |= K` in fn_800B2710 and fn_800BEC84; `Ac` and `u0` in fn_800A8CC0; `RB ? RB : RA` in fn_800CA3DC. Local declaration orders in these files came from `sw.py` and say nothing about the source.
- **Duplicated helpers:** fn_800CA3DC keeps its own `Res` class and `SwapMode`, and fn_800C9FA4 and fn_800CA0A4 declare `Res` with a different slot layout from fn_800C9230.cpp. Virtual slot numbers are read from the asm, and the class shape is a guess.
- **Spellings from the latest round chosen to produce the code:** `x = (int)&k` in fn_800C4EDC and `a = (int)((u8*)c + o5)` in fn_800B4744 (a pointer held in an int parameter); `v = v / 64.0f` in fn_800CA7A4; `v1 = e - v1` and reusing `e` in fn_800B663C; `*(u32*)` zero stores and the `W3* p` pointer in fn_800B8154; the separate `x1`..`x5`, `y1`.. and `c1`.. locals and `Eff*& x` in fn_800B4744's `Mk`; the extern `K0` in fn_800B1B48. Local orders came from `sw.py` and two-line searches and say nothing about the source. The four-level lookup remains the hand-unfolded copy, so fn_800B79AC, fn_800B8154, fn_800B4744, fn_800B1B48 and fn_800B29D0 carry the same caveat as above. The originals probably used Vec operators and one recursive `fn_800B5784`.
- **Duplicated preludes:** each new effect-lookup file repeats the head of fn_800B056C.cpp, and fn_800C219C.cpp repeats the declarations of fn_800C1220.cpp, including unused helpers, because the new files had to stand alone.

## Round 16
No new matches. Tried: fn_800AF12C with `fn_80175E7C` returning `Col` by value (fixes the byte-shift registers but moves the stack slots: worse), fn_800C358C (loop exit as `break`/`goto`/`while` forms; none keeps both the back branch and the dead `b end`). fn_800CB69C read again: 18 GPRs + 18 FPRs and WGPIPE, not started.

## Round 18 (goal changed: exact, or functionally equal in `equiv/`)

From this round a function is done at one of two levels: exact (`check_func.py --strict-references` prints MATCH, file in this folder) or functionally equal (`check_regs.py <file> --extra "-i src/game/rG_800A3D88 -i src/game/rG_800A3D88/wip"` prints `renamed` or `regs`, file in `equiv/`). Every `equiv/` file compiles on its own.

Exact (1 function, 152 bytes): `fn_800CCEEC.cpp`, the static initialiser of two global objects with a common base. `BaseCtor` stands for the base class constructor.

Functionally equal (8 functions, 2,308 bytes):

| File | Class | Bytes | Source |
|---|---|---|---|
| `equiv/fn_800C5EA4.cpp` | renamed | 0x274 | `wip/fn_800C6210.cpp`, plus a missing `f->m30 = NULL` at the end of the second branch and a separate `return f` in the first. The old draft was one instruction short because of that missing store, so it was a real difference, not a register miss. |
| `equiv/fn_800A75E8.cpp` | regs | 0x188 | `wip/fn_800A6DE4.cpp`, NULL return moved last, rule lookup in an inline (`GetRule`) |
| `equiv/fn_800A6DE4.cpp` | regs | 0x150 | `wip/fn_800A6DE4.cpp` with the path buffer at 0x44 bytes |
| `equiv/fn_800A84A4.cpp` | regs | 0x128 | `wip/fn_800A84A4.cpp` with a wrapper around `Index69C` |
| `equiv/fn_800C3974.cpp` | regs | 0xD4 | `wip/fn_800C3974.cpp` |
| `equiv/fn_800C9918.cpp` | regs | 0xC4 | `wip/fn_800B5D14.cpp` |
| `equiv/fn_800C3C3C.cpp` | regs | 0xB4 | `wip/fn_800C3C3C.cpp` |
| `equiv/fn_800C763C.cpp` | regs | 0x44 | `wip/fn_800C7850.cpp` |

Already at `regs` level before this round (see `docs/EQUIVALENT.tsv`, files still in `wip/`): 800A6978, 800AC664, 800AF584, 800B1120, 800BBE94, 800C5A34.

Checked and still class `other`: 800AF12C (`wip/fn_800AF12C_b.cpp`, three byte extracts scheduled differently), 800B8BC4 (store order of the 0.0f constant), 800A47AC, 800A4D88, 800A3FA4, 800A40B4 (float schedule), 800C4DDC (the float argument loads before the ternary; 3 spellings), 800C358C (one unreachable `b` missing; 10 loop spellings tried), 800C4104, 800C6118, 800C7850, 800C78FC, 800C79A0, 800C7A98, 800C9084, 800C91C8 (per-array base registers: pooled file statics), 800A4A98, 800C0894. Not attempted: 800CB69C (4.2 KB, saves r14..r31 and f14..f31 and spills).

Caveats for a port:
- The `equiv/` files repeat the helper block of their parent file with the exported bodies turned into prototypes.
- `char buf[0x44]` in `fn_800A6DE4` is sized from the stack offset; the name fits in 0x40.
- `Index69C_w` and `GetRule` are wrappers that only set stack slots or the prologue order.

Lessons:
- When a draft is one instruction short, look for a missing store before trying spellings (fn_800C5EA4).
- A buffer that sits 4 bytes lower than expected may be 4 bytes bigger: here a 0x40-byte array was placed at 0x18 and a 0x44-byte one at 0x14.
- Moving the common `return NULL` to the end and the first lookup into an inline fixed a prologue `mr` that was scheduled around the register saves.

## Round 20 (small leftovers; `sched` and `slots` now count)

Levels as printed by `python3 -I tools/check_regs.py <file> --extra "-i src/game/rG_800A3D88 -i src/game/rG_800A3D88/wip"`. `sched` files were looked at with `tools/equiv/dd.py` (moved instructions are listed in each file header) and run through `tools/equiv/symcheck.py --anon`.

Totals: exact 3 functions / 584 bytes, regs 3 functions / 536 bytes.

| Function | Class | Bytes | File | symcheck |
|---|---|---|---|---|
| 800A40B4 | regs | 0xF8 | `equiv/fn_800A40B4.cpp` |  |
| 800A3FA4 | regs | 0xA4 | `equiv/fn_800A3FA4.cpp` |  |
| 800C7850 | exact | 0xAC | `fn_800C7850.cpp` |  |
| 800C78FC | exact | 0xA4 | `fn_800C7850.cpp` |  |
| 800C79A0 | exact | 0xF8 | `fn_800C7850.cpp` |  |
| 800C7A98 | regs | 0x7C | `equiv/fn_800C7A98.cpp` |  |

Complete self-contained drafts still at `other` (new `wip/*_r20.*` files; the header of each says what differs):

- `wip/fn_800A4A98_r20.cpp` (0x4C): beq L here, bne L; b L in the original (one instruction short).
- `wip/fn_800C358C_r20.cpp` (0x1F8): one unreachable b missing (see NOTES round 18).
- `wip/fn_800C4104_r20.cpp` (0x10C): the mode test after the float store is a different branch shape (original: beq; bge; b; cmpwi 2; bge; b, i.e. a switch; ours if/else), 65 vs 67 instructions.
- `wip/fn_800C9084_r20.cpp` (0x84): same instructions except the first proc script argument: the original has lis/addi of lbl_80382930 in r30 and addi r3,r30,0 (pooled file statics in .data: scripts at +0, +0x40, +0x58, +0x80 with a jump table between them), ours splits lis and addi. Needs the real pooled data definitions.
- `wip/fn_800C91C8_r20.cpp` (0x68): same cause as fn_800C9084: the original forms the pool base lbl_80382930 once at entry and compares against addi r0,r5,0 / 0x80 / 0x70; also ends in b fn_800893C4; blr (26 vs 25 instructions).

Key fact: the face cache `lbl_803E7200` is four pooled file statics (`res` +0, `key` +0x20, `del` +0x40, `ref` +0x50). Written as statics, plain indexed loops match 800C7850, 800C78FC and 800C79A0 exactly (`fn_800C7850.cpp` with `fn_800C7850.symbols.json`). The `FaceCache` struct in the other files describes the same memory; in a port use one definition.

Real difference found: 800A3FA4 and 800A40B4 load both source fields before the first store in the original (the drafts stored `t->x` before loading `p->y`).

Not attempted: 800CB69C (4.2 KB, no draft), 800A4D88, 800C0894, 800C4DDC, 800C6118 (old fragments no longer compile against their parents; not rebuilt this round).

Lesson: 800C9084/800C91C8 need the pooled `.data` proc scripts at `lbl_80382930` (+0, +0x40, +0x58, +0x70, +0x80, with fn_800C8000's jump table between them); without real definitions of that data they stay one `addi rX,rBase,0` away.

## Round 21 (large functions without a draft)

One function newly at a counted level (4,224 bytes):

| Function | Class | Bytes | File | symcheck |
|---|---|---|---|---|
| 800CB69C | sched | 0x1080 | `equiv/fn_800CB69C.cpp` (+ `.symbols.json`) | 7 of 113 blocks flagged, all explained in the header |

`fn_800CB69C` is the string draw routine (glyph quads through the GX FIFO, the same `#` escapes as the width function `fn_800CA3DC`, shadow and eight-direction outline passes). Written from the disassembly: 1056 of 1056 instructions with the original's 18 integer and 18 float saved registers. Moved instructions: three stores/loads in the entry block, `subf`/`lis` before the main loop, and the interleaving of glyph byte loads, conversions and float operations before `bl fn_80077D18`.

Facts: the outline direction table is a function-local `static V3 dirs[8]` (lbl_80382E68, guard lbl_804CB6F8): four constant rows in `.data`, four diagonal rows filled at first use with cos/sin of 45, 135, 225 and 315 degrees. `volatile Fifo WGPIPE : 0xCC008000;` (union of `u8` and `f32`) gave the original's FIFO base rank.

Caveats for a port: `Res`, `Glyph8`, `FontHdr8` are local views of shared structures; `Val()` and the colour save copies only reproduce stack copies; `check_func.py --strict-references` prints three "wrong reference" lines that come from the one-slot shifts and the static's local name.

Lesson: a 4 KB draw routine that fills r14..r31 and f14..f31 still reaches `sched` when it is written in the original's statement order with a function-local static for its table; the remaining differences were pure scheduling.

## Round 21 (small functions without a draft)

Checked with `python3 -I tools/check_regs.py <file> --extra "-i src/game/rG_800A3D88 -i src/game/rG_800A3D88/wip"`; exact files also with `check_func.py --strict-references`.

Totals: exact 5 functions / 984 bytes, regs 1 / 920.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 800C9084, 800C91C8 | exact | 0x84, 0x68 | `fn_800C9084.cpp` (+ `.symbols.json`) | the proc scripts at `lbl_80382930` as real file statics reconstructed from the DOL; the real fn_800C8000 is repeated in the file so that its jump table falls between the first and second script (+0x18) |
| 800C0894 | exact | 0xF4 | `fn_800C0894.cpp` | the two flag tests go through `static inline int EffHas(const Eff*, int)`; that stops the tested value being forwarded into the following `m46 &= ...` |
| 800C4DDC | exact | 0x100 | `fn_800C4DDC.cpp` | written from the asm |
| 800C6118 | exact | 0xF8 | `fn_800C6118.cpp` | fn_800C5EA4 takes seven arguments; the old fragment passed six |
| 800A4D88 | regs | 0x398 | `equiv/fn_800A4D88.cpp` | rewritten: it and fn_800B3A1C return `Vec` by value; `r[n++] = ...` |

Pool layout of `lbl_80382930` (.data): +0x00 E_Fade script, +0x18 jump table of fn_800C8000, +0x40 E_Flash, +0x58 E_Wipe, +0x70 the grab script (`lbl_803829A0`), +0x80 E_ForceFade. Data objects are laid out in definition order with a function's jump table at the place of the function.

Prototype problem in a matched file: `fn_800C4A58.cpp` declares `fn_800C5EA4` with six parameters; the function takes seven (`int slot, const char* name, int x, int y, u32 flags, int z, int parent`, as in `equiv/fn_800C5EA4.cpp`). A port must use the seven-parameter form.

Not done: 800CB69C (another session's draft is in `wip/r21_fn_800CB69C.cpp`).

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`; symcheck `--anon --xargs` clean):

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_800C7A98.cpp` (+ `fn_800C7A98.symbols.json`) | fn_800C7A98 | 0x7C | `sRef[i]--;` before `sDel[i] = 2;` (found by a statement-move search) |

Tried in round 23 without an exact result: fn_800A47AC (moves get 5 words; 240 orders of the y/z copy), fn_800A4D88
(moves/decl orders get 2 words: the `addi r1,0x38` loop pointer and its copy swap; 20 for-header spellings).
