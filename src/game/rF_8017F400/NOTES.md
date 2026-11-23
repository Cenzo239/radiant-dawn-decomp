# Region 0x8017F400..0x801D09F8 notes

570 functions match: 124 from round 1, 114 from round 2, 196 from round 3, 109 from round 6, 20 from round 7 and 7 from round 8 (`python3 -I tools/check_func.py <file> -v` prints MATCH for every file below).
Round 1 went in address order from 0x8017F400 to 0x8019315C, and round 2 from 0x80193198 to 0x801A4614. Round 3 took the tractable functions between 0x801A77A0 and 0x801CA434, without covering everything in that range. Paired-single functions were skipped, along
with a few large ones (fn_80181470, fn_80183FE8, fn_80186768, fn_8018708C and others).

## Round 8 (7 functions, 19,444 bytes)

| file | functions |
|---|---|
| fn_801BDF20.cpp (added) | 801C13D0 801C2828 |
| fn_801CE800.cpp (new) | 801CE800 801CEAE0 801CF3E4 |
| fn_801ADED4.cpp (new) | 801ADED4 |
| fn_801912E0.cpp (new) | 801912E0 |

Near misses:
- wip/fn_801875CC.cpp: the 28,900-byte config menu draw. Only 6 real words are off: in the first slider (case 4) `arch` wants r28 and `w` wants r29, and ours swaps them. The other four sliders and all items match. Worth more than anything else left in this region. The file passes the colour through an explicit `kt` copy and a pointer prototype of fn_801BC88C, so it's a reproduction rather than the source. Tried without effect: every declaration order, function-level `arch`, `w`, `h`, reference parameters, reading the percent field after `arch`.
- wip/fn_801CE800.cpp: fn_801CEC98 (13: the second Find1 wants r4 for the pointer, r3 for the key).
- wip/fn_801ADED4.cpp: fn_801AF2A8 (59: `v` wants r30, pool base r29, table base r28 in the first branch).
- wip/fn_801BDF20.cpp: fn_801BFB58 (2 unique: `m` wants r29, and shared or function-level `m` and `r` don't change it), fn_801BE4E4 (18, three causes), fn_801C5874 (19 as filed; `(u8)(i == 2 ? 1 : 0)` for the colour index saves one word, and the rest is counter scheduling in the prologue), fn_801C0638 (102 as filed; expanding `GaugeBg` and `Bar` with a depth search reached 81, not filed), fn_801C4F0C, fn_801BD420, fn_801C336C unchanged.
- fn_8019AEA8 (16,972 bytes, the file menu state machine) was read but not written: a large `switch` of plain calls, probably tractable by hand with bodies sorted by address.

### What unlocked these

- **Inline with a local table:** a 12-word `lwzu`/`lwz`/`stw` copy before each `fn_800D0864` is `const char* t[] = {...}; return fn_800D0864(t[i]);` in a small inline with a constant index, under `#pragma pool_strings off`. fn_801912E0 is 55 of those.
- **Function-level variables shared across cases:** one `const char* s` and `int u` for all switch cases fixed odd r27/r28 swaps at single sites that per-item locals couldn't (fn_801875CC).
- **Split one counter into several** and rerun `sw.py`: one `j` per loop solved fn_801ADED4 in seconds after it had stalled on a shared `j`.
- **Conversion temps alternate:** the two hoisted `0x43300000` doubles are handed out in turn, including for conversions later removed as dead. If every later `0x1728`/`0x1730` is inverted, one earlier statement is missing, such as a dead `x += ...` (fn_801875CC case 0x11).
- **Late struct copy:** a by-value struct argument is copied before float arguments that are expressions. If the `lwz`/`stw` copy comes last, the floats go through an inline's parameters first (`Dr2`).
- **`#pragma inline_max_total_size`:** when `bl` to a static inline appears only late in a very large function, the total budget ran out. `inline_max_size` alone doesn't help.
- **`if ((int)f->a > 0) { int n = f->a;`** gives `extrwi.` then `ble` on a bitfield, with `n` in its own register (fn_801C13D0).
- **`clrlwi` kept on a constant-valued colour:** return it from a small `u8` inline (`GetC5`, fn_801C2828).

### Caveats for round 8

- `StringPool` in fn_801912E0.cpp and fn_801ADED4.cpp is scaffolding, as in round 7.
- fn_801ADED4's declaration order and its split counters `j`, `j1`, `j2` came from search. `GetC3v` and `GetC5` (fn_801C2828) are guesses at the inline boundaries. fn_801C13D0's repeated bitfield reads with an `int` cast are unlikely to be the source's spelling.
- fn_801912E0's `N` inline keeps the table as literals, so the original's template `lbl_8036C318` and its strings are matched by value, not by symbol.

## Round 7 (20 functions, 18,028 bytes)

| file | functions |
|---|---|
| fn_801BDF20.cpp | 801BDF20 801BE2A4 801BF50C 801BF80C 801C0220 801C0E94 801C25D8 801C2ED8 801C4268 |
| fn_801A5C80.cpp | 801A50C4 801A53DC 801A5800 801A5C80 801A5ECC |
| fn_801AC7AC.cpp | 801AC7AC 801AC8BC 801AC9D8 |
| fn_801ACD98.cpp | 801ABC34 801ACB9C 801ACD98 |

`drawinl.h` holds the shared draw inlines. fn_801BCA5C (`SetScale`), fn_801BCA94 (`FontReset`), fn_801BD170 (`Tile`) and fn_801BD2EC (`Sprite`) are real functions that get auto-inlined inside their own file, so they are only inlined in 0x801BCxxx..0x801C5xxx. Other files call fn_801BCA5C and fn_801BCA94 as real functions.

Near misses, by words off, with the first cause:
- wip/fn_801BDF20.cpp: fn_801BFB58 (2: `m` wants r29), fn_801BE4E4 (18), fn_801C5874 (19: counter scheduling), fn_801C4F0C (73: FP colouring), fn_801C0638 (~100: FP colouring), fn_801BD420 (~130), fn_801C336C (~480, not tuned)
- wip/fn_801ADED4.cpp: fn_801AF2A8 (59: pool base and table base swap in the first branch)
- wip/fn_801ACD98.cpp: fn_801AC084 (55; probably needs inlines for the tile switch and terrain lookup)

The wip copies keep `/*P*/` and `/*S*/` markers. `fn_801C3AB4` (493) was read but not written. fn_801A4744 and fn_801A6220 are long and were left alone.

### What unlocked these

- **String pools are real literals.** A `lis rN, lbl; addi rN` base that reloads per group, and `addi rS, rB, off` kept in a saved register across a call for one use, come from string literals under `#pragma pool_strings on`. `lbl + off` is rematerialised at the use and can't reproduce this. Each pool file starts with a dummy `StringPool` function that assigns every pool string in order, so the offsets are exact. The checker skips it as "not in symbols.txt", and it isn't in the original.
- **Short strings in a table:** in a pooled file, wrap `const char* t[] = {...}` in `#pragma pool_strings off` / `on`, or the table entries point at the pool and the checker fails them.
- **Stack slots follow inline nesting depth,** breadth first: a shallower inline's slots sit above a deeper one's. The same drawing code needs a different nesting per call site. drawinl.h has the forms (`Tile`, `Tile1`, `TileF`, `TileG`, `Sprite2`, `Sprite3`, ...), and they differ only in slot order.
- **Function-level variables interfere more than inline locals.** `Hdr` (fn_801C2ED8 and others) has `w`, `h` as inline locals so they share registers with later variables. The same locals at function level never do.
- **A loop in a static inline, or a block-scoped pointer with its stepping** fixed saved-register rotations in fn_801A5800, fn_801A53DC and fn_801A50C4.
- **Inline parameter order sets register order** for arguments evaluated at entry: `Row(lab, key, v, ...)` matched fn_801C4268 and no other order did.
- **Color temporaries:** `C5(0, a)` as a constructor temp passed by value gives [copy, temp] adjacent slots (fn_801BDF20). A colour returned through three levels of inline lands below everything else (fn_801BE4E4).
- **`clrlwi` kept on a u8 argument** means the value came out of a multi-return inline. A plain variable holding constants or `lbz` values compiles to `mr`.
- **Dead `cmpwi`:** an `if` whose body only touches a dead variable (fn_801BF80C) leaves the compare, while an empty body removes it.
- **Hoisted float constants:** a literal inline argument is folded at each use. A local `f32 q = 191.0f` stays in a saved register.
- **Int to float of a constant:** `li; xoris; stw; lfd; fsubs` comes from a constant held in an int or s16 local, since a literal argument is folded to `lfs`.

### Caveats for round 7

- `StringPool` is scaffolding, not game code. Delete it once the real file holds all the strings in order.
- The depth wrappers in drawinl.h (`Sprite3`, `Sprite4`, `TileG`, `WRAP*`) were found by search and only encode stack order. Declaration orders found by `sw.py` say nothing about the source. fn_801BF80C's dead `z` is invented.
- fn_801BE4E4's `G0`/`G1` three-level inlines are the same kind of guess.

## Resume point

Round 6 took the small and mid-size functions between 0x801BA664 and 0x801D0940, without covering everything. `build/m2c/matched_names.txt` won't list its 109 matches until it's regenerated, so check the table below too.

Not attempted in 0x801BA664..0x801D09F8 (word counts in brackets):
- Draw functions, most with a prologue `psq_st` only, so ordinary C: fn_801BD420 (216), fn_801BDF20 (141), fn_801BE2A4 (144), fn_801BE4E4 (1034), fn_801BF50C (192), fn_801BF80C (211), fn_801BFB58 (434), fn_801C0220 (262), fn_801C0638 (535), fn_801C0E94 (335), fn_801C13D0 (1154), fn_801C25D8 (148), fn_801C2828 (428), fn_801C2ED8 (293), fn_801C336C (466), fn_801C3AB4 (493), fn_801C4268 (809), fn_801C4F0C (602), fn_801C5874 (496)
- Model and bone code: fn_801CA688 (116), fn_801CBA60 (387), fn_801CC06C (148), fn_801CC2BC (196), fn_801CC5CC (283), fn_801CCA38 (131), fn_801CCE8C (116, same shape as fn_801CCCBC), fn_801CD05C (263), fn_801CD478 (327), fn_801CDD5C (173), fn_801CE174 (96), fn_801CE800 (180), fn_801CEAE0 (110), fn_801CEC98 (234), fn_801CF3E4 (427)
- fn_801D087C (26) and fn_801D08E4 (23): a stack guard object that stores vtable lbl_80380F00 around OSDisableInterrupts / OSRestoreInterrupts
- fn_801CBA0C (21): `addi r3, r31, 0x0` means pooled file statics, so an extern can't reproduce it

Not attempted in round 3's range, 0x801A4744..0x801BA664 (word counts in brackets):
- Prologue `psq_st` only, so ordinary C: fn_801A50C4 (198), fn_801A5C80 (147), fn_801A6220 (631), fn_801A88A4 (351), fn_801ABC34 (276), fn_801AC084 (458), fn_801AC7AC (68), fn_801AC8BC (71), fn_801AC9D8 (113), fn_801ACD98 (206), fn_801ADED4 (744), fn_801AF2A8 (770), fn_801B5EB4 (98)
- No paired-single at all: fn_801A6BFC (214), fn_801A6F54 (127), fn_801A7150 (404), fn_801ACB9C (127, bubble sort over 4 ints), fn_801AD7D8 (159), fn_801B10B0 (664), fn_801B378C (142), fn_801B3B3C (128), fn_801B3D3C (75), fn_801B3E68 (146), fn_801B40B0 (116), fn_801B4280 (128), fn_801B4480 (75), fn_801B46B4 (110), fn_801B486C (970), fn_801B603C-family helpers fn_801B6B18 (174), fn_801B6EBC (82), fn_801B78F0 (1156), fn_801B8DB4 (372), fn_801B9454 (499), fn_801B9CEC (145), fn_801B9F30 (89), fn_801BA20C (82)
- MSL `std::list` / `std::bitset` / `std::advance` inlines: fn_801B05F8 (150), fn_801B0850 (55), fn_801B09D0 (98), fn_801B0B58 (160), fn_801B1B10 (174), fn_801B1DF8 (55), fn_801B1EE4 (155). These need the real templates rather than hand-written loops.
- Paired-single or not checked for it: fn_801A4744, fn_801A53DC, fn_801A5800, fn_801A5ECC, fn_801A7FDC, fn_801A8E20, fn_801AA1CC, fn_801B2150, fn_801B6738, fn_801B6DD0, fn_801B7004, fn_801B739C, fn_801B7554, fn_801B7644

Not attempted before 0x801A4744, and not paired-single:
- fn_80196E14 (314 words), fn_801972FC (313)
- fn_8019AEA8 (4243 words)
- fn_8019FD1C: destructor that stores vtable lbl_80380940, so a compiler-made vtable gives a wrong reference
- fn_801A2F14 (85), fn_801A3104 (110), fn_801A32BC (375), fn_801A3898 (69), fn_801A39AC (380), fn_801A4068 (363)

Skipped as paired-single: fn_80193774, fn_8019467C, fn_801959A0, fn_8019846C, fn_801986C4, fn_80198CC0, fn_8019A82C, fn_8019F5E8, fn_8019FF0C, fn_8019FFE4, fn_801A1AC4, fn_801A1BE0, fn_801A1DCC, fn_801A1F64, fn_801A2588.

## Files and matched functions

| file | functions |
|---|---|
| fn_8017F400.c | 8017F400 8017F408 8017F410 8017F418* 8017F44C* 8017F464* 8017F480* 8017F4A0* 8017F658 |
| fn_8017F990.cpp | 8017F990 8017FA1C 8017FA24 8017FA40 8017FA84 8017FB24 8017FB88 8017FBCC 8017FC60 8017FCE0 |
| fn_8017FDC8.c | 8017FDC8 |
| fn_80180444.cpp | 80180444 801804F8 80180598 801805D4 |
| fn_80180C90.cpp | 80180C90 80180C98 80180CBC 80180D0C 80180D24 |
| fn_80180E40.cpp | 80180E40 80180E9C 80180FB8 80180FC4 80181104 80181168 80181190 801811B4 801811F4 80181268 801812B8 80181318 |
| fn_8018277C.cpp | 8018277C 80182820 801828B8 8018295C 801829F0 80182A9C |
| fn_80183B10.cpp | 80183B10 80183B30 80183BA8 80183BC8 80183C60 80183C80 80183CF4 80183D14 80183E34 80183E54 80183EA8 80183EC8 80183EEC 80183F0C 80183F74 80183FB0 |
| fn_80184398.cpp | 80184398 801843EC 8018454C 80184648 |
| fn_801855C8.cpp | 801855C8 801855E0 80185658 8018569C 801856C8 801856F4 80185720 8018574C 80185874 |
| fn_80185C7C.cpp | 80185C7C 80185C84 80185C8C 80185CA0 80185D08 |
| fn_80186544.cpp | 80186544 80186668 801866B0 |
| fn_801868E8.cpp | 801868E8 80186920 801869B4 801869D0 801869EC 80186A44 80186A84 80186A94 80186AF0 80186B88 80186C30 80186C5C 80186C64 80186CB8 80186D4C 80186D7C 80186DAC 80186DFC 80186E4C 80186E9C 80186EEC 80186F3C 80186F8C |
| fn_80191134.cpp | 80191134 801911B4 801911C4 801911D4 8019120C 80191240 |
| fn_80192F48.cpp | 80192F48 80192F74 80192F78 80192FC8 80192FD4 80193014 80193054 80193094 801930DC 80193120 8019315C |
| fn_80193198.cpp | 80193198 80193294 80193404 80193590 80193A2C 80193DD8 80193E24 80193ED0 80193F54 80193F60 80194108 80194114 80194198 80194234 80194288 801943D8 80194524 |
| fn_801945C0.cpp | 801945C0 801945E8 80194644 801947D4 801947E0 801947EC 80194800 80194814 80194820 80194834 80194840 801949E4 80194A28 80194AC0 80194B58 80194B60 80194C08 80194CB0 801950F4 |
| fn_801958C0.cpp | 801958C0 801958D0 80196DC8 80196DD4 801977E0 8019782C 80197858 80197880 801978D8 801978E0 801978E8 80197908 80197918 80197928 80197BAC 80197BB4 80197BF0 80197DF0 80197EA0 80197FC8 80198180 80198338 801985DC 8019AD58 |
| fn_8019F0F4.cpp | 8019F0F4 8019F0FC 8019F1E8 8019F234 8019F260 8019F288 8019F2E0 8019F2E8 8019F2F0 8019F2F8 8019F334 8019F35C 8019F368 8019F370 8019F39C 8019F50C 8019F534 8019F6D8 8019F7CC 8019F85C 8019F964 8019F9FC 8019FABC 8019FAC8 8019FB08 8019FB10 8019FBA4 8019FBAC 8019FC40 8019FC48 8019FC74 8019FC80 8019FC88 8019FD14 8019FDA0 8019FDA8 8019FDB0 8019FDB8 8019FDC0 8019FE04 8019FE6C 8019FEC0 8019FEFC 8019FFD4 |
| fn_801A1A80.cpp | 801A1A80 801A1CFC 801A2224 801A2384 801A23E0 801A2570 |
| fn_801A3068.cpp | 801A3068 801A3F9C 801A3FF8 801A4614 |
| fn_801A77A0.cpp | 801A77A0 801A7840 801A790C 801A7A80 801A7ADC 801A7B20 801A7BB0 801A7BE0 801A7C48 801A7C88 801A7CCC 801A7D10 801A7D34 |
| fn_801A7D4C.cpp | 801A7D4C 801A7F4C 801A9DAC 801A9DF0 801A9E4C 801A9F34 801A9F38 801A9FE0 801AA018 801AA01C 801AA070 801AA0DC 801AA148 801AA1B4 |
| fn_801AAF10.cpp | 801AAF10 801AB1C4 801AB50C 801AB574 801AB588 801AB5AC 801AB604 801AB618 801AB674 801AB68C 801AB7C4 801ABA64 801ABB5C 801ABBA8 |
| fn_801AD0D0.cpp | 801AD0D0 801AD11C 801AD208 801AD21C 801AD304 801AD3E4 801AD400 801AD418 801AD428 801AD434 801AD46C 801AD4A4 801AD4DC 801AD514 801AD5A4 801AD614 801ADA54 801ADB38 801ADC34 801ADCE4 801ADD1C 801ADD8C 801ADE00 801AEA74 801AEC38 801AEE9C 801AF040 801AF078 801AFEB0 801AFF0C 801AFF9C 801B0000 801B0054 801B00A8 |
| fn_801B00C0.cpp | 801B00C0 801B0418 801B04A4 801B0530 801B092C 801B0DD8 801B0E28 801B1DC8 801B1ED4 801B3688 801B39C4 801B3A30 801B3ABC |
| fn_801B45AC.cpp | 801B45AC 801B45B4 801B45C0 801B45CC 801B45F0 801B4600 801B4638 801B5794 801B57E4 801B5884 801B58C8 801B58E4 801B5988 801B5A74 801B5B14 801B5BC8 801B5C60 801B5D14 801B5D24 801B5D30 801B5D68 801B5DA0 801B5DD8 801B5E3C 801B5E50 801B5E64 801B5E78 801B5E8C 801B5EA0 |
| fn_801B603C.cpp | 801B603C 801B61B8 801B63A0 801B6698 801B66E8 801B7290 801B76F0 801B76F8 801B7808 801B7874 801B8B00 801B8B1C 801B8B84 801B8BEC 801B8CD0 801B9384 801B9C20 801BA094 801BA0D8 801BA158 801BA1B8 801BA1C8 801BA354 801BA39C 801BA3D8 801BA420 801BA544 801BA584 801BA5C4 801BA628 |
| fn_801C6034.cpp | 801C6034 801C61F4 801C6554 801C6564 801C6690 801C66F4 801C6820 |
| fn_801C7A70.cpp | 801C7A70 801C7AF0 801C7B4C 801C7B94 801C7C1C 801C7C64 801C7CF0 801C7D38 801C7DC4 801C7E0C 801C7E98 801C7EFC 801C7F90 801C7FA8 801C8028 801C8030 801C80B0 801C80C0 801C8144 801C8184 801C8208 801C827C 801C828C 801C8298 801C8318 |
| fn_801CA138.cpp | 801CA138 801CA190 801CA1D8 801CA1E8 801CA218 801CA228 801CA248 801CA260 801CA274 801CA2C4 801CA300 801CA33C 801CA388 801CA3DC 801CA3E4 801CA40C 801CA434 |
| fn_801BA664.cpp | 801BA664 801BA760 801BA8C0 801BA994 801BA9E0 801BAA04 801BAAA4 801BAB7C 801BAC38 801BAD90 801BAFF4 801BB26C 801BB818 801BB8B8 801BB958 801BBA8C 801BBBA4 801BBC84 801BBDE4 801BBECC 801BBF8C 801BC094 801BC130 801BC1B0 801BC548 801BC654 801BC740 |
| fn_801BCB08.cpp | 801BCB08 801BCD90 801BD070 801BD170 801BD2EC |
| fn_801C6830.cpp (not in address order) | 801C6830 801C6D2C 801C6DA0 801C6EAC 801C7404 801C7558 801C7668 801C7988 801C8380 801C8434 801C8598 801C8C80 801C8CB4 801C8D70 801C8E9C 801C8F10 801C8FB4 801C8FE8 801C90E0 801C91D8 801C936C 801C9484 801C94B8 801C97D0 801C9890 801C9A0C 801C9A40 801C9B18 801C9CCC 801C9D00 801C9D10 801C9DCC |
| fn_801CA4FC.cpp | 801CA4FC 801CA568 801CA5D4 801CA858 801CA920 801CAA24 801CAC38 801CAC64 801CAD54 801CAE28 |
| fn_801CAE88.cpp | 801CAE88 801CB0A4 801CB4B8 801CB504 801CB5EC 801CB6D4 801CB734 801CB920 801CCCA0 801CD994 801CE068 801CE5B8 801CE670 |
| fn_801CDAF8.cpp | 801CDAF8 801CDC14 |
| fn_801CFA90.cpp | 801CE760 801CFA90 801CFB10 801CFB7C 801CFC58 801CFCE0 801CFD50 801CFDEC 801CFE3C 801CFE78 801CFED8 801CFF0C 801D0214 801D02FC 801D038C 801D040C 801D0518 801D0674 801D0784 801D0940 |

\* hand-written asm (r11/r12, no frame), reproduced with CW `asm` functions and `nofralloc`.

wip/ near misses:
- fn_8017F4C8 (LZ77 decompress, 70/100 words): the header register order differs, and CW adds a `len<=0` guard in the unrolled copy loop.
- fn_80181788 (gmap release, 14/86 words): r29 and r30 are swapped between the loop counter and the pointer.
- fn_80184324 (gmap destroy, 14/29 words): the original keeps the u8 index and re-shifts it each time, while ours keeps idx*4. Round 2 retried it with inline accessors and an int index, with no improvement.
- fn_80181788: round 2 retried the two loops as inline helpers, and it got worse (79/84 words differ).
- fn_80194D58 (file menu cursor input, 165/231): register colouring in the cursor-move inline.
- fn_801951BC (202/232) and fn_8019555C (198/217), both in wip/fn_801951BC.cpp (file menu cursor tick): win[] iterator gets r28 instead of r29, and the sel*0x73 / x6 operands swap.
- fn_8019F108 (window init, 52/56): the registers for constants 0 and 1 are swapped; store orders were permuted without success.
- fn_8019F3A8 (entry init, 55/89): the entry pointer gets r31, where the original keeps the constant 0 in r31.
- fn_801A2268 (help text line splitter, 68/71): scheduling of the line pointer init only.

- fn_801AEB78 and fn_801AEDC4 (title sprintf, wip/fn_801AEB78.cpp): the original keeps the string base in r26 and the results in r27..r31; ours always gives the base r31.
- fn_801AF104 (title bars and caption, 103/105): only `lwz r0; extsh r3,r0` versus the original `lwz r3; extsh r3,r3`.
- fn_801B01E4 (load check): one branch, `bne next; b end` in the original and `beq end` here. Stack layout matches.
- fn_801B0E88 (help window move, 124/138): the switch base register is r5 in the original and r7 here.
- fn_801C8300 (set unit flag, 3/6): the original loads the unit into r4, ours into r3.

Round 6 near misses. Each wip file holds only the functions, except fn_801CCCBC.cpp; take the declarations from the matched file of the same name.
- wip/fn_801BA664.cpp: fn_801BB334 (21/127, r5 and r6 swapped between the skill pointer and the counter); fn_801BB530 (82/186, the last struct-loop operands and a missing `clrlwi` before fn_801196F0).
- wip/fn_801BCB08.cpp: fn_801BC88C (2/116, `mr r27,r4` should come before `mr r26,r3`); fn_801C6114 (2/56, one `li` scheduled against a store); fn_801C62D8 (29/70, register rotation); fn_801C63F0 (17/89, the original keeps the link in r4 and copies it to r31 only for branches that cross a call); fn_801BD780 (83/488 with block-scoped locals, float register colouring. Hill climbing on function-level locals made it worse).
- wip/fn_801C6830.cpp: fn_801C7898, fn_801C864C and fn_801C9E98 (registrars, about half the words: the string base must be r31 and the table base r30. They're probably pooled literals and file statics); fn_801C7110 (ours is 146 words against 154, and 121 of those differ: register order); fn_801C846C (8/75).
- wip/fn_801CA4FC.cpp: fn_801CABAC (11/35, float registers); fn_801CADE0 (ours is 12 words against 18: needs the stack copy of the colour).
- wip/fn_801CAE88.cpp: fn_801CB1A0 (2/75, `lwz r4,0x38` should use r3, not r31).
- wip/fn_801CDAF8.cpp: fn_801CE2F4 (45/96, stack and register layout); fn_801BE154 (15/78, x1 and y1 should be in f31 and f30).
- wip/fn_801CFA90.cpp: fn_801CF040 (6/140, first pointer should be r31); fn_801CF270 (20/93).
- wip/fn_801CCCBC.cpp: fn_801CCCBC (33/116, inlined recursion, registers rotated).

Each wip file from rounds 1 and 2 holds the shared declarations as well as the near-miss function. Round 3 wip files hold only the function, except fn_801B01E4.cpp; take the declarations from the neighbouring matched file.

## Subsystems (guessed names)

- **0x8017F400 memory/LZ utils**: word compare, fill and copy (asm); LZ77 type-0x10 decompress and header size.
- **0x8017F990 timing**: random value from OSGetTime ms, frame counter (`lbl_804CB8D8`), frame delta, OSTime to h/m/s.
- **0x8017FB24 Rect16 helpers**: overlap test, move to origin.
- **0x8017FBCC background decompression thread**: OSMessageQueue request/free queues, thread main loop, init. The thread, stack and queues are file `static`s.
- **0x8017FDC8..0x80181318 EventArrow** (script commands EventArrowAppend/Start/Focus/Color/FadeOut/Wait/Delete): `Track` (0x3250 bytes, keyframes keys[]/vals[] sorted by bubble sort). There are 8 tracks, `new[]`'d through `__construct_new_array` (fn_8028BE18) in an owner process found with fn_80083B84 (find process by class) and fn_80081050 (create process). fn_800C3C3C registers a script command (name, func, nargs).
- **0x80181470..0x80184648 GMap (world map)**: "gmap/tpl/gmap.tpl", "gmap/curve/%s.bin" and "gmap/rect/%s.bin" resources. GMap is 0x278 bytes, and two are kept in `lbl_804CB908[2]`. A GMapProc owns each one, with its index at +0x30. See gmap.h for the layout.
- **0x801855C8..0x80185D08**: fan-out functions that call four subsystems (fn_801AD4xx, fn_801B5Dxx, fn_80193xxx, fn_80280Exx), a scrolling 608x480 background draw, and BGM helpers ("BGM_EVT_CLASS_CH...").
- **0x80186544..0x80186F8C class-change event**: process class `lbl_80388140`, with mode at +0x30 (0..5) and unit at +0x34. Mode 1..4 is tested with a `switch` inside an inline. The "EID_CLASSCHANGE1_F" effect has callbacks at model node +0x98/+0x9C/+0xA0, and "SFX_FF_LEVEL_UP1" is played.
- **0x801911D4 cursor process** (class `lbl_803884A0`): x/y at +0x58/+0x5C, dir at +0x6A.
- **0x80192F48 fade process** (class `lbl_803885F0`): flags +0x30, dir +0x32, speed +0x34, mode +0x36, alpha +0x38.

- **0x80193198..0x80194524 battle exp/result gauge**: reads the battle event queue at `lbl_803C8E80 + 0xDE0` (fn_800262A8 has event, fn_800262F4 get value). `BS_GetPlayerUnit` is an inline loop over u[0], u[1] for a faction id in {0,5,7,8,9,10}. Uses "SFX_SYS_EX_POINT1".
- **0x801945C0..0x8019F964 file menu (start/load/save)**: global `lbl_804CB934` (0x4F0 bytes) owned by a process in `lbl_804CB930`; strings are pooled in `lbl_8036C5E8` ("FM_*", "window/filemenu/filemenu"). Holds a u8 tween at +0x8C, a fade pair at +0x9C, six 0x28-byte windows at +0xB0, six 0x7C-byte entries at +0x1A0, a cursor at +0x488 and two 0x1C-byte markers at +0x4B0 ("EID_DRAGONBALL"). fn_80197BF0 is the draw/tick callback.
- **0x80194A28..0x80194CB0 save slot checks**: static save buffers at lbl_8041CA08 / lbl_8041DA88 with guard bytes lbl_804CB938/9. fn_80245C88 constructs and fn_8019FAC8 destructs. Each is scanned over 6 slots.
- **0x8019FB10..0x8019FDB8 small accessors**: bit-array test and set at obj+0x20 / obj+0x40, and byte getters. Owners unknown.
- **0x8019FDC0..0x8019FEFC game over**: "BGM_GAMEOVER1" and "RID_..." picture, wide variant chosen by fn_801D09F0.
- **0x801A1A80..0x801A2570 help window**: `lbl_8041EB20` (0x124 bytes), process class `lbl_80388A70`, "window/help/help". fn_801A2570 forwards a rect to fn_803080DC.
- **0x801A3068..0x801A4614 (unnamed)**: global `lbl_804CB94C` (0x98 bytes, process in `lbl_804CB948`) with a VWin at +0x94 whose vptr is at +0x28; fn_801A4614 is a dim-and-pulse draw using `lbl_804CB964`.

- **0x801A77A0..0x801A7D34 fullscreen overlay**: `lbl_804CB964` (0x35C bytes, process in `lbl_804CB960`). State 0/5/10 at +8, timer at +0xA, alpha at +0x338. fn_80085708 finds a process by name. fn_801389C0 and fn_80138D6C act on the object from fn_8013B9A8.
- **0x801A7D4C..0x801AA1B4 level up / class change stats**: 0x14C-byte data holding the unit at +0x14, 11 stats at +0x1C and 10 diffs at +0x27. Three process classes (mode at +0x10).
- **0x801AAF10..0x801AB674 list menu**: `lbl_804CB98C` (0xD4 bytes, process in `lbl_804CB988`). 11 entries at +0x2A, scroll at +0x1C, scroll bar `VWin` at +0xD0. fn_800D1D14 plays the selected entry, whose ids are in `lbl_80389010` at stride 12.
- **0x801AB68C..0x801ABBA8 caption card**: text at +0xC, split at the newline into +0x90 and +0x110. Voice id at +0x8C, mode at +0x194.
- **0x801AD0D0..0x801AD4DC letterbox** (class `lbl_803891A4`) and **0x801AD514..0x801ADD8C timed text** (classes `lbl_80389210`, `lbl_80389234`). Times are in ms, divided by `1000.0f / 60.0f`.
- **0x801ADE00..0x801B0054 difficulty/mode prompt**: 0x210-byte data, six options (+0x98, +0xB0, +0xC8), 5 text lines at +0xCE. fn_800D0864 looks up a message string by id.
- **0x801B00C0..0x801B3ABC picture list**: `lbl_804CB9BC` (0x6C bytes, process in `lbl_804CB9B8`). `std::list` at +0x18, tab at +0x24, focus column at +0x28. Picture names per language in `lbl_8036DA88` and `lbl_8036DC60`.
- **0x801B45AC..0x801B5EA0 cursor unit window** (class `lbl_80389480`): the unit under the cursor comes from the `CursorUnit` inline, `lbl_803CAB38 + 0x934/0x938` and map bytes at `lbl_803EC898 + 0xD`.
- **0x801B603C..0x801BA628 manual / help viewer**: pages at +0x34, page index +0x63, scroll +0x68/+0x6A, mode +0x6C. Paged with a 0x150-wide slide. Strings at `lbl_8036DEB0`, messages named "Mess_Help...".
- **0x801C6034..0x801C6820 unit info pages**: link table `lbl_8038A038` (0x21C per page, 0x14 per link).
- **0x801C7A70..0x801C8318 battle preparation commands**: `lbl_803CA870` is the acting state (unit at +0, item slot at +0xE). `lbl_803C8E80` is the battle system. Pairs of a "can do" check and a "do" function.
- **0x801CA138..0x801CA434 model wrappers**: small setters around fn_80007F3C, fn_80008F10 and fn_8000866C.
- **0x801BA664..0x801BC740 unit list tables** ("Mess_Help_list_*"): each page has a column layout function (`*b` by column, then the same three stores), a header message, a sort key and a cell text function. `SortKey` is the shared inline for column 0. Rows hold the unit at +0.
- **0x801BCB08..0x801BD070 unit info window**: uses the `BData` layout from fn_801C6034.cpp. fn_801BC88C draws a textured quad, and fn_801BD170 / fn_801BD2EC draw window tiles from `lbl_804CB588`.
- **0x801C8380..0x801C9E98 staff and item effects**: pairs of a target check and an effect. `lbl_803E7320.n` is the target count and `lbl_803CA870` the acting state.
- **0x801CA4FC..0x801CB920 model effects**: procs that fade colour (fn_801CAE88, fn_801CB734) or a value at +0xCD. Each has a setter that kills the running proc, then applies at once or starts a new one.
- **0x801CE760..0x801D0674 battle participant copy and skill lists**: a 0xB2-byte struct with 32 u16 skill ids at +0xE and three 0x20-byte entries at +0x50. `Q` in fn_801CFA90.cpp is the event queue at `lbl_803C8E80 + 0xDE0`.

## Caveats for round 6

- fn_801C8CB4 and fn_801C9A40 cast a call result to `char*` so the `add` keeps the call first. The original probably didn't.
- fn_801CFA90.cpp advances the parameter by raw bytes (`s = (SK*)((u8*)s + 2)`) to reproduce the strength-reduced loops. The source probably indexed an array.
- fn_801D0940 calls the compiler's `__cvt_fp2unsigned`, so the checker notes that reference as unchecked. It's `fn_8028C1A0` in the original, and it reads the float through `extern const f32 lbl_804CF770` to keep the operand order.
- fn_801CA920 calls fn_80083B78 in two separate paths, written with an early `return` so they aren't merged.
- All prototypes of functions outside the region are guessed from call sites.

## Recurring structs / globals

- Process system: fn_80083B84(cls) finds an instance, fn_80081050(cls, parent) creates one, fn_80081194(cls, parent) creates one as a child, fn_80083B78(proc) deletes it, fn_80081A90(proc) deletes another proc, fn_800846BC(cls) kills all of a class, and fn_80083DC4(proc, result) finishes a script proc. Class descriptors are 0x20..0x28-byte .data objects.
- `lbl_804CB700`: global skip flags. `& 0x8001` means skipping.
- `lbl_804CB5B8`: pad object (C++). Its vtable +0x34 is the trigger, +0x48 is held, and the button mask is 0xFFF0.
- Model (fn_800E3C04 / fn_800E3A10 spawn): node pointer at +0x30.
- fn_80290DDC = sprintf, fn_80291188 = strcmp, fn_8023F1A4 / fn_8023F1A8 = load / free file, fn_80006A2C = release handle, fn_80078CCC / fn_80078E24 = alloc / free, fn_800791B0 / fn_80079474 = new[] / delete[].

## Compiler quirks found

- **`li r4,0` with `subfc; subfe; subfe; neg.`** is a `switch` on a u64 (`u64 f = (u64)x & 0xC0000000ULL`).
- **A truncated `add`:** when a sum goes straight into an `s16` argument, a `char*` cast on the call (`(s16)(int)((char*)call() + a)`) gives `add rD, rCall, rVar`.
- **A register still live at `blr`:** fn_801D02FC returns its switch value, which keeps it in r3.
- **Recursion with `return d`:** a level's result that looks like a constant after inlining (fn_801CCCBC) means the function returns its parameter rather than the child's result.
- **Unroll counts:** the counter step is the number of copies minus one, so 6 copies with `addi 5` and `ctr = 3` is an 18-iteration loop.

- **The code is C++.** Use `.cpp` with `extern "C" { }` so names stay `fn_...`.
  - Struct **copy-construction** (`Vec t = a;`) copies words (lwz/stw), while **assignment** (`a = b;`) of an all-float struct copies with lfs/stfs. A `const Vec&` parameter gives the float copy too. This fixed fn_80180444 and fn_801804F8.
  - **File statics are laid out in declaration order in C++** (in C they come out in first-use order). The base address is CSE'd and hoisted into a saved register. That fixed fn_8017FCE0, whose statics are `lbl_80418680`, `lbl_8041C998` and `lbl_8041C9B8`. The checker can't verify those references.
  - Virtual calls (`lwz r12,0(r3); lwz r12,N(r12); mtctr r12; bctrl`) match only with a real `class` with virtual methods. The vtable starts at +8 (RTTI and offset words first). When there are data members before the first virtual, the vptr sits after them (fn_80191134 has its vptr at +0x28).
- `#pragma auto_inline off` is needed when a non-inline function is called from a later function in the same file (fn_80180E40 called from fn_80180FC4). Explicit `static inline` helpers still inline. Many duplicated loops in this region come from small inline helpers (`FindCurve`, `GetOwner`, `IsActive`, `Proc_Delete(void*&)`), and writing them as inlines often fixes register allocation.
- Using a pointer local inside the loop (`Track* t = &o->tracks[i]`) or a separately incremented pointer (`e++` at the end of the body) changes the counter/pointer register assignment.
- An empty `if (create() == NULL) return;` at the end of a function leaves a dead `cmpwi r3,0`. This is likely an assert compiled out.
- `if (a < b) return r + a; return r + b;` computes `r+b` first and then branches.
- Float literals give `@N` constants. If `@N` happens to exist in symbols.txt (another TU's local), the checker reports a "wrong reference" even when the bytes match. In that case use the `lbl_804CExxx` extern instead. The same happens with `@stringBase0`, so pooled strings are referenced as `lbl_XXXX + off` (needs `#pragma pool_strings on` / `readonly_strings` otherwise).
- Large .data objects (`lbl_80387D10`) need a full-size declaration (array/struct) to get lis/lwz instead of sda21.
- A `switch` on a u8 with cases 1..4 gives the `cmpwi 5 / bge; cmpwi 1 / bge` pattern, where a plain range check gives `cmplwi`.
- 64-bit `/` and `%` emit `__div2i` / `__mod2i` (fn_8028C418 / fn_8028C634 in this DOL). The checker can't verify those calls, but they match.
- **Unrolled loops keep unfolded switches.** A `for (i = 0; i < 2; i++)` with an inlined `switch (i)` fully unrolls, leaving `li r0,0; cmpwi r0,1` and dead branches (fn_80193198). Hand-writing the two iterations folds the switch instead. The loop only unrolled once the second switch was written directly in the loop body, not as an inline returning BOOL.
- **Inline helpers fixed the register order in fn_80197928 and fn_801950F4**, where declaration order had not.
- **Function-local statics are written by hand.** `if (!guard) { ctor(obj); __register_global_object(obj, dtor, &chain); guard = 1; }` with `lbl_` externs matches, since a real class would call a mangled ctor. Not source-faithful, but byte-identical.
- **Double stores come from macros.** `free(p); p = 0; p = 0;` with the global reloaded each time means a `#define` macro, not a `void*&` inline (fn_8019F6D8).
- **`extsh.` on a parameter stored to a field:** the parameter is `int` and the test reads the field (`m->at = t; if (m->at == 0)`), which forwards the value. Same for array indexes (`tbl[w->id]`).
- **Local pointer arrays:** `const char* tbl[] = {"..."}` reproduces the `lwzu` template copy, and literals up to 8 bytes land in sdata2 as in the original (fn_8019F108). A struct copy from the `lbl_` template schedules differently.
- **`lbz r0; extsb r3,r0`** rather than a direct load into r3 means the field is `u8` with an `(s8)` cast (fn_80194198).
- **`f & 0x800` returned as `!= 0`** gives `extrwi`, and if-return-style BOOL inlines are what keep the value materialised before `cmpwi` (fn_80194288, fn_80194524).
- **`-fp_contract on`** gives `fmadds` for `a * b + c` (fn_801A4614).
- `extern void f(); ... bl g; bl f` with no argument setup can mean f takes g's result in r3 (fn_802450BC(fn_8024BC94())).
- **`base + const + i * step`:** this spelling, with the constant before the multiply, fixed the register allocation in fn_801AAF10 and fn_801B0530. `base + i * step + const` schedules the same but colours differently.
- **Uninitialised byte copied to a stack slot** (`lbz r0,N(r1); stb r0,M(r1); addi r4,r1,M`) is an empty functor passed by value. `struct E { E() {} char c; }; f(x, E());` inside a small inline reproduces it (fn_801B0418).
- **`p->t++` as its own statement,** with the value read afterwards, forwards the value and keeps the parameter register live before `li r3` (fn_801AD614). `++p->t` as an argument loads r31 instead.
- **A loop written in a `static inline`** lets the parameter keep r31, where a loop variable in the function body would take it (fn_801B7290).
- **Inline parameter types steer FP registers:** `f32` parameters match where the value is converted late, `int` where it is converted first (fn_801AB1C4 needs both forms).
- **`(u16)(x & 0x10) != 0`** keeps `rlwinm; neg; or; srwi` where `(x & 0x10) != 0` collapses to `extrwi` (fn_801C61F4).
- **`beq; blt; cmpwi 7; bge`** on one value is `m != 0 && m >= 0 && m < 7` (fn_801B61B8).
- **Two loads of one global before a branch** need a volatile read for one of them (fn_801AD614, fn_801B45CC), since CW otherwise CSEs them.
- **Local address-taken ints:** the first declared gets the highest stack offset (fn_801B61B8).

## Round 24

- fn_8018524C (2 words): case-0 store orders give 4-5 words. The one-instruction `li`/`addi` scheduling misses (fn_8008D75C, fn_80168BF0, fn_800D0BFC, fn_8018524C: the original finishes an address `addi`, or materialises a constant, one slot later or earlier than ours) are not a compiler setting: `#pragma scheduling 601/603/604/750/7400/8240/off`, `-proc 750/603e/604/7400/generic`, the GC 3.0a3..3.0a5 compilers and `-O3,p`/`-O4,s` leave them or make things worse; a same-file definition of the address target (fn_8008D91C) does not move it either.
