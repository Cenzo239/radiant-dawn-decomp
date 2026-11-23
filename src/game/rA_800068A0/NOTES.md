# Region A (0x800068A0..0x80025A74) notes

322 functions match here (180 + 100 in the fifth round + 24 in the ninth + 11 in the tenth + 7 in the fourteenth), not counting the
script-matched ones in `src/game/auto`. Every main file prints `MATCH` with
`python3 -I tools/check_func.py src/game/rA_800068A0/<file> -v`.

## Matched functions

| File | Functions |
|---|---|
| `fn_800068A0.c` (8) | 800068A0 800068EC 80006938 80006A0C 80006A2C 80006A64 80006B84 80006CC8 |
| `fn_80006CF8.c` (66) | 80006CF8 80006D00 80006D08 80006D18 80006E1C 80006E94 80006EE0 80006F20 80007374 80007630 800076E8 80007860 800078E4 8000793C 80007A00 80007A5C 80007ABC 80007C58 80007DE8 80007E90 80007EE4 80007F10 80007F3C 80007F68 80007F94 80007FC0 80008060 8000808C 800080B8 800080E4 800081B4 800081BC 800081C4 8000866C 800087FC 800088A0 800088B0 80008A38 80008C98 80008CF0 80008D48 80008E28 80008E5C 80008E88 80008EB4 80008F10 80008F20 80008F4C 80008F54 80008F5C 80008F64 80008F6C 80009030 80009090 800090F0 80009150 80009214 80009274 800092D4 80009334 800096E4 800097B0 8000987C 80009974 80009BC8 80009C7C |
| `fn_80009CD0.c` (4) | 80009CD0 80009D60 80009E20 8000A0A8 |
| `fn_8000A7A0.c` (1) | 8000A7A0 |
| `fn_8000BD3C.c` (5) | 8000BD3C 8000BDB0 8000BE20 8000BE24 8000BEA8 |
| `fn_8000DA14.c` (1) | 8000DA14 |
| `fn_8000EB68.c` (3) | 8000EB68 8000EBCC 8000EC2C |
| `fn_8000F328.c` (7) | 8000F328 8000F3D4 8000F3E4 8000F468 8000F470 8000F478 8000F484 |
| `fn_8000F48C.cpp` (49, GCamera.c) | 8000F48C 8000F748 8000F7F4 8000F954 8000F9C8 8000F9E8 8000FA18 8000FA30 8000FA98 8000FB88 8000FB94 8000FBA0 8000FEA0 8000FF74 800100C8 800102AC 800104DC 800106AC 80010788 8001084C 8001093C 80010960 80010968 80010980 800109B8 80010AB8 80010AE4 80010B54 80010B8C 80010BB0 80010C18 80010C20 80010C38 80010CA4 80010DA4 80010F94 800110F4 80011274 80011280 80011838 800119BC 80011B58 80011B90 80011C4C 80011C60 80011CBC 80011D50 80011E0C 80011E20 |
| `fn_80011E28.cpp` (36, GMaterial.c) | 80011E28 80011E80 80011EAC 80011EB4 80011F0C 80011F38 80011F90 80011FBC 80011FC4 8001201C 80012048 800120A0 800120CC 800120D4 8001212C 80012170 800121C8 80012218 80012268 800122F0 80012430 800138B8 80013C54 800140A0 800146A8 80014760 80014818 80014D40 80014DE4 80014E24 80014F64 80015070 800150F4 80015174 800151EC 8001561C |
| `fn_8000DA60.c` (5) | 8000DA60 8000E9DC 8000EC30 8000EDEC 8000F1D4 |
| `fn_8000E974.c` (6, hand asm) | 8000E974 8000E9A8 8000E9C4 8001D024 8001D144 8001D2FC |
| `fn_800148C0.c` (1) | 800148C0 |
| `fn_80016368.c` (6) | 80016368 80016568 800170B8 80017B08 8001F0A4 8001F4D8 |
| `fn_80017D6C.c` (22) | 80017D6C 80017D94 80017DA8 80017DF0 80017F10 80017FD0 800180F0 8001A4E8 8001A610 8001A9B4 8001AA84 8001B194 8001B254 8001D014 8001D01C 8001E010 8001E044 8001E094 8001E0B4 8001E144 800215D4 80022B54 |
| `fn_80018208.c` (3) | 80018208 800184BC 80018E48 |
| `fn_8001E1A4.cpp` (15) | 8001E1A4 8001E318 8001E44C 8001E51C 8001E548 8001E638 8001E694 8001E6AC 8001E6D0 8001E70C 8001E8E8 8001E9E4 8001E9FC 8001EA74 8001EACC |
| `fn_80021754.c` (16, GX state cache) | 80021754 80021808 80021860 800218A8 80021958 80021A08 80021BA4 80021CB4 80021D18 80021D9C 80021E20 80021E8C 80021F7C 800220B0 800221BC 80022254 |
| `fn_800235B8.cpp` (17) | 800235B8 800236AC 8002386C 80023DCC 80024090 800241B4 800243D4 8002442C 80024640 800249E8 80024E80 80025388 80025510 8002573C 80025830 80025894 80025990 |
| `fn_800247D4.cpp` (9) | 800247D4 80024AD8 80024D1C 80024D2C 80024DE0 80024DFC 80024E20 80024EC4 800257E4 |
| `fn_800125A8.cpp` (6, GMaterial.c) | 800125A8 80012F00 8001393C 80013CF0 80014158 8001444C |
| `fn_800149F4.cpp` (2) | 800149F4 8001528C |
| `fn_8001F5B8.cpp` (1) | 8001F5B8 |
| `fn_80018888.cpp` (2) | 80018888 80019AB0 |
| `fn_80018F74.cpp` (1) | 80018F74 |
| `fn_80019D9C.cpp` (1) | 80019D9C |
| `fn_8001D44C.cpp` (2) | 8001D44C 8001D748 |
| `fn_8001AC30.cpp` (1) | 8001AC30 |
| `fn_8001762C.cpp` (1) | 8001762C |

| `fn_800081D4.cpp` (1, round 10) | 800081D4 |
| `fn_8000A22C.cpp` (1, round 10) | 8000A22C |
| `fn_8000A460.cpp` (1, round 10) | 8000A460 |
| `fn_8000C920.cpp` (1, round 10) | 8000C920 |
| `fn_8000D754.cpp` (1, round 10) | 8000D754 |
| `fn_8000E510.cpp` (1, round 10) | 8000E510 |
| `fn_80020AE0.cpp` (1, round 10) | 80020AE0 |
| `fn_80022CCC.cpp` (1, round 10) | 80022CCC |
| `fn_80023170.cpp` (2, round 10) | 80023170 800232FC |
| `fn_800238C8.cpp` (1, round 10) | 800238C8 |
| `fn_8000BF68.cpp` (1, round 14) | 8000BF68 |
| `fn_8000C3C4.cpp` (1, round 14) | 8000C3C4 |
| `fn_800158FC.cpp` (1, round 14, GParticle.c) | 800158FC |
| `fn_800167B0.cpp` (1, round 14) | 800167B0 |
| `fn_80019504.cpp` (1, round 14) | 80019504 |
| `fn_8001BB84.cpp` (1, round 14) | 8001BB84 |
| `fn_8001C904.cpp` (1, round 14) | 8001C904 |

Added to existing files in round 9: 80012308 (`fn_80011E28.cpp`), 8001A644 (`fn_80018208.c`),
8000EF88 (`fn_8000DA60.c`), 80008110 (`fn_80006CF8.c`), 80009EF8, 80009FD0 and 8000A168
(`fn_80009CD0.c`).

Some of these files hold functions that aren't neighbours (`fn_80017D6C.c` runs to 80022B54 and
`fn_8000E974.c` to 8001D2FC), and a few aren't in address order. They need splitting when real
translation units are drawn.

Near misses are in `wip/`, each with a header comment saying how close it got:

- 80008B50: needs 4-level inlining of a recursive function
- 80009454: 17 words differ
- 80009A2C: 36 words differ (volatile registers only)
- 8000BC20: 12 words differ
- 8000FD20: 8 words differ (float register allocation; sibling of the matched 8000FBA0)
- 800105AC: 14 words differ (r4/r5 swapped between list head and prio temp)
- 80010E38: 13 words differ (recursion inlined twice, outer return shape)
- 80011680: about 70 words differ (inlined 80010CA4 stack slots and registers)

Added in round 5:

- 8000DB10: 7 words differ (r3/r8 around the key pointer)
- 8001ECE4: 2 words differ; 8001EBC8: 14 words differ (the `li` for the loop counter sits between two `fmr`s; was 2 words in a scratch variant)
- 80020E7C: 4 words differ (r3/r4)
- 8002468C: 4 words differ (r29/r30 between two saved results; declaration order had no effect)
- 800244C4: 3 words differ (needs the string functions below)
- 80017344: 19 words differ (conversion stack slots 0x80/0x88 rotated)
- 8001AB10: 8 words differ
- 800161E0: 24 words differ (`lhz` pair order in the member copy)
- 800156C8: 47 words differ
- 80020354 / 80020764: 43 / 28 words differ (registers only; whole file in `wip/fn_80020354.cpp`)
- 80024EFC / 800250B0: 39 / 108 words differ (MSL `basic_string` reserve/replace; structure is right)
- 80023E2C / 8002421C / 80023360: about 53 words each (widget constructor colouring: 0x190 must get r0 and -1 r5)
- 80021EF8 / 8002230C: not reproduced (see below)
- 8000AE38 template (8000B100, 8000B3C8, 8000B690, 8000B958; about 0xDE8 bytes): 27 words differ, registers only, in `wip/fn_8000AE38.cpp`. Expanding the search in place fixed n and last; keys/f0/f1 are still rotated.
- 8001B284: 12 words differ (registers; 2.3 KB). The size rounding constant is 0.1f, not 0.5f.
- 80019504: 4 words differ (`seen[n++] = idx` gives the sthx; the xE store must stay ahead of it)
- 8001CD78: 4 words differ (the last count must land in r26)
- 8001BB84: 22 words differ (a walker must take r16)
- 80020F04: about 44 words differ (float registers shifted by one from the z test)

Added in round 10:

- 8001BD34 (3 KB): 46 of 750 words differ, registers only, in `wip/fn_8001BD34.cpp`. Everything else is right; the original seems to have r29 blocked in two regions.
- main (800227D4): 29 of 224 words differ, a pure rotation of four saved registers, in `wip/fn_800227D4.cpp`.
- 800167B0: draft only, in `wip/fn_800167B0.cpp` (259 words); the C4 colour must stay in memory but still CSE.

Added in round 14 (older `wip/` files for 80019504, 8001BB84, 800167B0 and 8000BF68 are stale, those now match):

- 8000D228: 21 of 331 words differ, float registers in the Hermite case only, in `wip/fn_8000D228.cpp`.
- 8000DD0C: 81 of 513 words differ, registers only, in `wip/fn_8000DD0C.cpp`. It inlines 8000D228; the prelude and structure are right. The search locals want lo r7, hi r8, mid r9, keys r10, n r11.
- 8001F1D4: 52 of 193 words differ, float registers and FP scheduling in the blend, in `wip/fn_8001F1D4.cpp`. Integer registers are right.
- 8001BD34: 43 of 750 words (41 real, 2 are rodata label names), in `wip/fn_8001BD34_r14.cpp`, which uses the fixed-address FIFO and puts `i` last in the loop increments. Left: i2 must be r26, not r29, and the last loop's pa/fifo/template/zero are one rank off.

Skipped:

- 8000A838..8000BC20: float animation evaluation. The 8000AE38 family stays at 27 words: keys never reaches r8 in 4000 random declaration orders, only r9, r4 or r3. 8000AB6C has the same asm template but was not compiled.
- 8000E974 / 8000E9A8 / 8000E9C4: GQR / `psq_st`, so hand-written asm

Resume point (round 14): 8000D228, 8000DD0C, 8001B284 (14 real words), 8001CD78 (4 words), 8001BD34, 8001F1D4, the 8000AE38 family, main. Not attempted yet: 8000A838 beyond reading its asm.
80020354: the 45 words start at the vertex block (the two at the top are label names); 80020764 stays at 28, not looked at. 8001BD34's psq are only register saves. 8001EBC8, 8001ECE4, 8001EDF8: a
parameter reassign alone does not fix the float registers. 8001EFE4 stayed at 20 words after a declaration search.

Round 14 lessons:

- **psq code with GQRs is ordinary C.** OSFastCast-style inlines (`register f32 r; asm { psq_l r, 0(p), 1, 5 } return r;`, `u32 tmp; register u32* p = &tmp; asm { psq_st v, 0(p), 1, 3; lhz out, 0(p) }`) get register-allocated and scheduled, and the compiler folds `rec + 1` and `&tmp` into the psq displacement. 800158FC (2.2 KB) was at 75 words on its first compile. GQR5 is `mtspr 0x395`.
- **The FIFO as a fixed-address global** (`volatile WG WGPIPE : 0xCC008000;`, a union as in the SDK) ranks its hoisted `lis` at the top of the saved registers; the `*(volatile f32*)0xCC008000` macro ranks it low. That fixed nearly every saved register in 800167B0.
- **Pinning store order with volatile:** two `volatile` casts force `sth` before `sthx` when the scheduler has no dependency to respect (80019504).
- **`volatile C4 col` with non-volatile reads through a cast** keeps a 4-byte local in memory while its reads still schedule freely (800167B0). `*(C4*)&col = *(C4*)&p->r` then gives the load-all, store-all order.
- **Writing `da[k]` instead of a named walker** makes it a compiler induction variable that takes the lowest register (8001BB84). Copying parameters to locals in the `/*P*/` block lets declarations rank them (8001BB84, 8001F1D4).
- **Avoiding CSE of `n - 1`:** `m = n; hi = m - 1; ... s = (u16)m - 1;` keeps the second `subi` (8000D228).
- **Multi-return tail inline:** a small inline with `if (lo > s) return s;` keeps `ble; b`, while a local `goto` becomes `bgt`.
- **Literal float as a local:** `lim = 300000.0f;` lets declaration order rank a hoisted constant.
- **`a *= b` keeps the target register** where `a = a * b` can start a new web (8000C3C4).
- **Jump tables:** word-identical code can still fail on table order; read the table in the dol and put the case labels in that body order (800158FC).

**Link note.** `fn_800125A8.cpp` defines the allocator tables (lbl_80378780..lbl_80378848) as file
statics because the pooled base register needs that, while `fn_80011E28.cpp` still externs them.
Both belong to one translation unit (GMaterial.c) and must be merged when TUs are drawn.
`fn_8001F5B8.cpp` and others declare the GX wrappers with their own prototypes.

## Subsystems (guessed names)

The region starts with the actor/model/animation engine. The assert strings in rodata give the
file names: `GActor.c` (lbl_80360AAC), `GAnim.c` (lbl_80360B08) and `GCamera.c` (lbl_80360BEC).

- **Resource archive** (800068A0..80006CC8). A header with magic 0x0020AF31 (incremented once
  relocated), a count and a table of {entryA, entryB} pairs. Relocation is offset + base. The
  80006A64/80006B84 pair binds a texture/material from the table (fn_80305A40/5C4C/5C94 look like
  GX texture-object setup).
- **GActor** (`GActor.c`, 80006CF8..80009C7C), 0x9C bytes:
  - 0x00 flags. Bit 0 = heap allocated, bit 1 = animation ended, 0x40000/0x80000 = allocator choice, 0x100 = translucent.
  - 0x04 parent
  - 0x08 GColor {r,g,b,a}
  - 0x0C transform state
  - 0x10 Mtx
  - 0x40 GModel*
  - 0x44 GAnim*
  - 0x48 GRes48* (material/texture set with 0x20-byte named entries at +0x34, count u16 at +0x54)
  - 0x4C, 0x50 other resources
  - 0x54
  - 0x58 current frame (f32)
  - 0x5C speed/scale
  - 0x60 node matrix buffer (count*0x30)
  - 0x64, 0x68, 0x6C/0x70 buffers
  - 0x74 child (animation blend layers, at most 4)
  - 0x78 blend weight
  - 0x7C trail/afterimage list {mode, count, x2, pad, GColor, GActor** items}
  - 0x80..0x82 bytes
  - 0x84, 0x88
  - 0x8C GKey keys[4] {u16 id; s16 val}

  Resource getters (`GActor_FindModel` etc., 80007EE4..800080E4) walk up the `parent` chain.
  Many of them are inlined into their callers as `static inline` copies.
- **GModel nodes**: 0xF4-byte nodes. +0x0C flags, +0x70 pos, +0xBC Mtx, +0xEC low nibble = mode
  (1..6 and 7..12 toggled by 80007ABC), +0xF0 name. GModel: +8 count, +0xC nodes.
- **GAnim** (`GAnim.c`). A linked list of typed chunks {type, data, next}. Type 5 is the key-set
  table {u16 count; u16* offsets} with sets {u16 frame; u8; u8 count; GKey keys[]}. 8000A7A0 is
  a binary search over {u16 frame,u16} keys. Event layers: 8000BE24/8000BEA8.
- **Resource get/release wrappers**: fn_8023F1A4 = get, fn_8023F1A8 = release, fn_8023F7B8 /
  fn_8023F7EC = get/set flags, and flag 0x400000 means "already relocated".
  GAnim: 8000BD3C/BDB0/BE20. GModel: 8000EB68/EBCC/EC2C.
- **GCamera** (`GCamera.c`, 8000F748..8000FB94), 0x150 bytes:
  - viewport floats at +4..+0x18
  - scissor u16 at +0x1C
  - Mtx44 proj at +0x24
  - Mtx44 viewProj at +0x64
  - Mtx view at +0xA4
  - light array at +0x120 (count +0x124, max +0x126)
  - near/far/aspect/fovy at +0x140..+0x14C

  lbl_804CB080 holds the current camera.
- **GCamera additions** (`fn_8000F48C.cpp`). The struct has look-at vectors pos/at/up/offset at
  +0xD4..+0xF8, a pool of 0x10-byte display entries GDisp {next, prio, func, arg} at +0x120 and
  6 per-layer lists at +0x128. Each layer has a draw mode set by 80011838 and is run by 800119BC.
  lbl_804CB084 remembers the last Begin (1 = 3D, 2 = 2D).
- **GFog** (lbl_804CA04C, 0x10 bytes): {type, r, g, b, start, end}. 800109B8 applies it to GX.
- **GLightSet** (lbl_803B6710[8], lbl_804CA050 = current), 0x128 bytes: {x0, x1, ambient, 8
  GLights of 0x24 bytes}. 80011280 loads a set into GX, cached by lbl_804CB088.
- **GDoneRender** (lbl_803B7050, a ring of 256 {func, arg}): callbacks run after drawing, with the
  `GDoneRenderEntry` assert in 80011CBC.
- **GMaterial** (`GMaterial.c`, from 80011E28; assert pool lbl_80360D24). Per-material allocators
  for TEV stages, tex maps, tex coords and tex mtxs, all reset by 80012268. 80012308 is a
  one-entry texture object cache (lbl_803B7850). GMaterial: +6 layer count, +7 flags, +8 rgb,
  +0x14 layers (0x1C each), +0x18 hooks (8 of {type, func}). GMatSet: +0x34 entries (0x20 each,
  name first), +0x54 count.
- **SDK functions identified**:
  - fn_80312318 PSMTXIdentity
  - fn_80312344 PSMTXCopy
  - fn_80312378 PSMTXConcat
  - fn_80312494 PSMTXInverse
  - fn_80312DB4 PSMTXMultVec
  - fn_80312E5C C_MTXPerspective
  - fn_80312FE0 PSMTX44Copy
  - fn_80313024 PSMTX44Concat
  - fn_803134C4 PSVECNormalize
  - fn_80313508 PSVECMag
  - fn_803188A4 DCFlushRange
  - fn_80312444 PSMTXInverse? (fn_80312494 is listed above; unconfirmed which is which)
  - fn_80312654 PSMTXRotRad
  - fn_803128AC PSMTXTrans
  - fn_8031292C PSMTXScale
  - fn_80312A50 C_MTXReflect
  - fn_80312AC0 C_MTXLookAt
  - fn_80312C34 / fn_80312D2C C_MTXLightPerspective / C_MTXLightOrtho
  - fn_80312E08 PSMTXMultVecSR
  - fn_80312F48 C_MTXOrtho
  - fn_80313128 PSMTX44Inverse
  - fn_803133E8 PSMTX44MultVec
  - fn_80313460 / 80313484 / 803134A8 PSVECAdd / Subtract / Scale
  - fn_80305xxx GXInitLight* and GXInitTexObj / GXGetTexObj*
  - fn_80307298 GXSetFog
  - fn_803074C4 GXInitFogAdjTable
  - fn_80307624 GXSetFogRangeAdj
  - fn_80307BCC GXProject
  - fn_80307D98 GXSetProjection
  - fn_80307E48 GXLoadPosMtxImm
  - fn_80308090 GXSetViewport
  - fn_803080DC GXSetScissor

  All of these names are inferred from arguments and neighbours, not from symbols.

  Others:
  - fn_8001E008 = assert(file, line, msg)
  - fn_80078CCC = heap alloc(size, name, flags)
  - fn_80078D9C = alternate-heap alloc
  - fn_80079940 = aligned alloc
  - fn_80078E24 = free
  - fn_80291188 = strcmp
  - fn_80291480 = string-equal (returns BOOL)

- **Round 5 additions (guessed):**
  - **GX state cache** (`fn_80021754.c`): one object at lbl_803B7878 holds the 0x4000-entry s16 sine table (built by 8001E44C) followed by per-stage TEV caches (a8000, a8040 .. a8260). Each wrapper builds a key and calls the GX setter only on a change. The setters are the `fn_803xxxxx` targets there. 8002230C resets everything.
  - **Trail/particles** (`fn_80016368.c`): GActor +0x54 is a state {info +0x30, buf +0x34}. Info has segments of 0x34 bytes, buf has entries of 0x14 bytes, particles are 0x4C bytes {pos, vel, age +0x18, size +0x20, rgba +0x2C}. 80017B08 dispatches on segment type 1..5.
  - **Math** (`fn_8001E1A4.cpp`): s16 fixed point with 7 fractional bits (`fx2f` / `f2fx`) for 3x4 matrices, plus a billboard matrix (8001E8E8) and rotation between vectors (8001EACC).
  - **Hand-written skinning** (`fn_8000E974.c`): 8001D024 / 8001D144 / 8001D2FC use GQR6/7, set by 8001D014 / 8001D01C.
  - **Sally screens** (`fn_800235B8.cpp`): the short-string class at +0x40 is MSL `basic_string` (top bit of byte 0 = long; short data from +1), so the strings at lbl_80361118 + 0xEF, 0x112 and 0x12D are its error messages.

## Compiler quirks found here

- **`stmw` vs `_savegpr` is per function.** GActor.c has both. Wrap only the `stmw` functions
  in `#pragma use_lmw_stmw on` / `off`. `optimize_for_size` is not the cause (it also turns
  off inlining).
- **Inlined self-recursion has a fixed depth.** fn_80008A38 matches with `#pragma inline_depth(3)`
  and fn_8000F3E4 with `inline_depth(4)`. Wrap them in `#pragma push` / `pop`. Callers that
  inline an already-expanded recursive function (fn_80008B50) are not reproduced yet.
- **`static inline` helpers are not emitted.** Plain `static` helpers are emitted as extra
  functions when not used everywhere.
- **Branches to a common `mr r3, rX` at the end** mean the function body is an inlined function
  that has several `return`s (fn_8000A7A0). Write it as a wrapper around a `static inline`.
- **A getter is inlined into its caller.** fn_80006D08 matches with `a->scale * fn_80006CF8()`,
  not with the global written directly, because the operand order differs.
- **`mr r3, r0` / `li r0, 0` in a parent-chain walk** means a separate non-inline copy. The
  wrapper `return Inline(a);` also produces that, but writing the loop directly with
  `return a->x;` does not.
- **Parameter width matters.** For a `u16` parameter passed on to a `u16` argument, CW emits no
  `clrlwi`. For a `u32` parameter passed to a `u16` argument it emits `clrlwi` (fn_800092D4).
  fn_80008F10 needed `s32` colour parameters to make the code that inlines it match.
- **Loop form changes the code.** An array-index loop over 4 fixed elements becomes
  `addi r3,8`-style partial unrolling. A `GKey* k` pointer loop becomes `lhzu`.
  `for (i = 0, ...)` and an `i = 0; j = 0; for (;...)` init order change the register order.
- **Struct copy into a stack local, then passing `&local`** to an inlined function matches the
  "stb to stack, use registers" pattern (fn_80009A2C/9454). The rest of those is
  volatile-register numbering that I could not control.
- **Declaration order changes register allocation.** Brute-forcing permutations with a small
  script (`perm.py` in my scratchpad: it permutes lines between `/*PERM*/` markers) solved
  80009334 and 8000BEA8 quickly.
- **`if (p == NULL) {..} else {..}` versus early return** changes block order (fn_8000F954).
- **`x / 2.0f` compiles to a multiply by 0.5 that keeps `x` first.** Writing `x * 0.5f` puts
  the constant first (8000FBA0, 800102AC).
- **`(x & 1) ? 1 : 2` gives `neg`/`addi`.** `2 - (x & 1)` gives `subfic` (8000FF74).
- **C++ `{0.0f, 0.0f, 0.0f}` initialises a Vec with `stw` of integer zero**, and non-zero
  initialisers copy from an anonymous rodata template. Declarations in the middle of a block
  (`Vec eye = {...}; c->pos = eye;`) keep separate stack slots and run at that point, which C
  blocks cannot do (8000F48C). Struct assignment is word copies in C and float copies in C++.
- **A loop re-reads a struct it copies only if the source is not const.** Copying a `const Vec`
  gets hoisted out of the loop and changes the unrolling (80010CA4 reads a rodata {0,0,0} through
  a non-const extern).
- **A `const` pointer parameter lets its loads move above stack stores.** Drop the `const` to keep
  source order (80011B90).
- **An inline function that returns a struct by value** gives the "build it, then copy it to the
  argument slot" stack pattern (80010AE4).
- **Functions the original calls with `bl` although they are defined earlier** can be wrapped in
  `#pragma auto_inline off` / `reset` (8000FF74, 800100C8 as called by 800104DC).
- **Functions with loops are not auto-inlined when recursive**, and `inline_depth` has no effect on
  them (80010E38). Small non-recursive ones with a loop do still get inlined (80010CA4 in
  80011680).
- **A range `switch` shows up as `cmpwi hi; bge; cmpwi lo; bge`.** Write it as `case` labels rather
  than `if (a >= lo && a < hi)` (80010E38, 800110F4).
- **Statement order changes volatile register numbering** even when the scheduler hides it.
  80011280 needed `col = ...` before `scale = ...`, and 80011D50 needed the head update first.
- **Pool strings and per-TU sdata2 constants.** Referencing pooled strings as
  `lbl_80360AAC + off` matches. The per-TU sdata2 constants (0.0f, 1.0f, the int-to-float
  doubles) can be written as literals.
- **`const` on a struct pointer changes copy scheduling.** With `const GXBlock* p`, `*c = *p` loads the next word before the previous store (80022254).
- **A wrapper's unused-looking register is often a pass-through argument.** The GX wrappers need every parameter passed on to the setter or all the temps land one register off.
- **An inline conversion stops loads being scheduled across statements.** `out->m[i] = fx2f(in->m[i])` through struct pointers gave the one-at-a-time layout of 8001E1A4 and 8001E318, where plain expressions got reordered.
- **Recursion with a depth argument:** 8000F1D4 is 8000EF88 inlined with d = 0. It only matched as nested `static inline`s with one local per branch (`g`, `h`), not through `inline_depth`.
- **`li rN, lbl@sda21` before byte stores** comes from assigning an sdata struct field by field (80021754); a whole-struct copy uses `lbl+1@sda21` instead.
- **Big-offset struct members:** 80021EF8 and 8002230C compute `base + 0x10000` once and derive the arrays with `subi`, then index with `stwx`. Direct members, a base pointer and array-pointer locals all fold to `stw` with a displacement instead.
- **Round 9: inline results don't take declaration order.** A variable assigned from an inline's return is ranked with the inline's temporaries, so `sw.py` can't move it. Expanding the inline in place as a macro (`ALLOC_TEV(st)`) made declaration order work; this solved 8001393C, 8001444C, 80014158 and 800125A8.
- **Real SDK return types:** with `u8`/`u16` getters, `GXInitTexObj(obj, GetData(obj), GetW(obj), GetH(obj), GetFmt(obj), 1, 1, GetMip(obj))` written nested gives the right registers and late `clrlwi`s. That fixed 80012308 and 80012F00.
- **Stack slots of by-value colours:** each `{r,g,b,a}` temp and its argument copy pair up only inside small inlines (`set4`, `set3`, `setE`), giving the interleaved order of 800125A8.
- **OSInitFastCast** is an inline with an `asm {}` block (`mtspr 0x392..0x395`). It compiles inside ordinary C (80018888).
- **Vertex FIFO:** `vtx(x + w, y, c, u, v)` through `pos3`/`col4`/`tex2f` inlines with expressions as arguments reproduces the hoisted conversions at once (8001F5B8). Named x2/y2 locals don't.
- **Literal Vecs vs const statics:** `Vec t = {1.0f, 0.0f, 0.0f};` copies from an anonymous rodata template each time, while a `static const Vec` gets hoisted out of the loop.
- **Dead conversion flips temp slots:** a `u = (f32)seg;` before a loop swaps the two 0x43300000 slots (8001BB84, see the conversion-temp lesson in MATCHING.md).
- **Search order:** run `sw.py`, then `rr.py`. `rr.py` found the last swap of 8001762C after `sw.py` stalled, but it finds nothing when a structural change is missing.
- **Sibling functions:** 80018F74, 80019504, 80019D9C and 8001B284 share one billboard switch. Once one matched, 80019D9C matched first try by renaming.
- **Round 10:** a key list store `GKey* o = &out[n++]; o->id = ...; o->val = ...;` keeps base+index with a stride register (8000A22C), where `out[n].id` becomes a walking pointer. An explicit stepped offset (`ofs += 2`) lets declaration order rank what was a compiler induction variable. Functions that look void but end in `mr r3,rX` return that value, and only then does the copy into a new counter (`mr r10,r3`) appear.
- **Round 10, locals:** `Vec b = i == 0 ? po[1] : po[-1];` makes the temporary above the conversion doubles with word copies (8001BD34). Node transforms are one 0xAC struct, `center` and `dir` next to a corner array suggest one `Vec[6]`.
- **Keep a one-use temp:** `int t = x; fn(t, t)` style pointer locals like `Mtx* p = &buf[i]` fixed the prologue `mr` order of 8000EF88; an out-pointer inline (`fd(a, &r)`) gave 80008110 both the `beq; b` shape and declared-order registers.

## Round 16

3 more functions match (752 bytes), all strict-reference clean:

| File | Functions |
|---|---|
| `fn_8001EDF8.cpp` | 8001EDF8 (integer-power ease, 312 bytes) |
| `fn_80020E7C.cpp` | 80020E7C (aligned scratch buffer grow, 112 bytes) |
| `fn_8002468C.cpp` | 8002468C (window title draw, 328 bytes; header copied from `fn_800247D4.cpp`) |

The `wip/` entries for 80020E7C and 8002468C are now stale.

- **8001EDF8:** the power loop is a `static inline` taking both running products by reference (`pw(f32& pe, f32& pc, f32 e, f32 c, int n)`). Written in place, the floats were wrong; in the inline they and the counter (r5) come out right at once.
- **8001EBC8 / 8001ECE4:** compiled together in address order (`wip/fn_8001EBC8_r16.cpp`) both are at 2 words. The only difference is `li r8,1` scheduled one slot early. The older single-function wip files overstate how close they were (they were 16+ by a diff scorer).
- **8002468C:** `s16 h` (the half-height) instead of `s32` fixed the r29/r30 swap; found by a type grid, not by declaration order.
- **80020E7C:** increment the counter before computing the aligned size (`lbl_804CB0AC++; a = (size + 0x1F) & ~0x1F;`).
- Tried without success: 8001CD78 (inline/identity wrappers for the last count, then sw: worse), 8000DB10 (16 spellings of the key header reads, stays 7).

## Round 17

No new matches here.
- 8001EBC8/8001ECE4: the `fmr` for `p = x` is scheduled two slots earlier than the original whatever the order of the setup statements (12 permutations, with `b -= a`, and eight `for`-header/`i = 1` placements). Swapping the loop body order breaks the unrolled loop. Using the `pw()` by-reference inline from 8001EDF8 is much worse (40 words).
- 8001B284: the Vec templates are anonymous `.rodata` read as `addi r3,r24,0x44; lwz r7,0x44(r24)` off `lbl_80360E30`, so they need a file `.rodata` pool whose first 0x44 bytes are the sibling objects (lbl_80360E30..E68). The wip gets that only with a padding array plus a dummy referencing function, which the rules don't allow, so it was left alone.

## Round 18 (exact and functionally-equal level)

The goal changed: a function also counts when `tools/check_regs.py` prints `renamed` or `regs` (same instructions,
order, constants and references; only registers differ). Those live in `equiv/` as self-contained files.

Exact (1 function, 508 bytes), `python3 -I tools/check_func.py <file> --strict-references -v` prints MATCH:

| File | Function |
|---|---|
| `fn_8000DB10.c` | 8000DB10 (hide nodes whose visibility key is 0). Fix: the key header is read through a walking `u16*` (`n = *keys++; id = *keys++;`) |

Functionally equal (14 functions, 7,764 bytes), check with
`python3 -I tools/check_regs.py <file> --extra "-i src/game/rA_800068A0 -i src/game/rA_800068A0/wip"`:

| File (`equiv/`) | Function | Class | Bytes |
|---|---|---|---|
| `fn_80009454.c` | 80009454 (GActor_CreateTrail) | regs | 0x290 |
| `fn_80009A2C.c` | 80009A2C (GActor_UpdateTrail) | regs | 0x19C |
| `fn_8000A838.cpp` | 8000A838 (colour track evaluator; new, no earlier draft) | regs | 0x334 |
| `fn_8000AB6C.cpp` | 8000AB6C, 8000AE38, 8000B100, 8000B3C8, 8000B690, 8000B958 (animation track evaluators) | regs | 0x10B4 |
| `fn_8000BC20.c` | 8000BC20 (GAnim_Relocate) | regs | 0x11C |
| `fn_8000FD20.cpp` | 8000FD20 (GCamera_GetFarPlaneMtx) | regs | 0x180 |
| `fn_800105AC.cpp` | 800105AC (GCamera_SortDisps) | regs | 0x100 |
| `fn_80010E38.cpp` | 80010E38 (GLightSet_Alloc) | regs | 0x15C |
| `fn_800244C4.cpp` | 800244C4 | regs | 0x148 |

Notes on these:
- **Fragments.** 80009454, 80009A2C, 8000BC20, 800244C4, 8000FD20, 800105AC and 80010E38 are their parent file
  with every exported `fn_` body replaced by a prototype, plus the old wip fragment. Where the original inlines an
  exported function (80008F10, 80008F20, 80006E1C, 8000987C) the parent's body is kept as a `static inline` copy
  named `fn_XXXXXXXX_inl` with a `#define fn_XXXXXXXX fn_XXXXXXXX_inl` in front of it. A port should fold those back
  into the one real function.
- **800105AC was wrong in the old wip**, not just a register miss: the branch targets differed. In the original
  `ins = l` runs at the end of every iteration and the list head is only stored when the list is not empty.
- **80010E38:** the outer recursion level is written directly; the old wrapper inline changed the return shape.
- **8000FD20:** `farD(c)` and `halfF(c)` accessor inlines give the original load and multiply schedule.
- **The track evaluators** (8000AB6C..8000B958) are one macro, `ANIM_TRACK_FN(NAME, TYPE, OUT_T, STORE)`, expanded
  six times: chunk types 6, 8, 9, 10, 11, 12. Type 6 stores a `u8`, type 10 scales by 1/16, the others by 1/1024.
  The body is the old 8000AE38 wip with its declaration order searched again for instruction order instead of
  register score, and the key reads in source order f0, v0, f1, v1. The `goto`s are the key search (the same search
  as `fn_8000A7A0`) expanded in place; the original most likely calls one inline.
- **8000A838** is the same lookup with the chunk type as a parameter and RGB565 key values, interpolated per
  channel into three bytes. It was `regs` on its first compile from the 8000AE38 text.

New wip files (still `other`, both self-contained):
- `wip/fn_80011680_r18.cpp` (80011680): stack slots and instructions now match (a flat copy of 80010CA4 with the two
  Vec temporaries in sibling inlines gives the original slot order amb, c, d, p). Left: the set pointer and the
  light pointer are in swapped saved registers, which also moves one prologue `stw`.
- `wip/fn_8002230C_r18.c` (8002230C, 0x38C): same size. A `hi = base + 0x10000` pointer with negative offsets
  reproduces the single base register held across the whole function, and the two flush routines are inline copies
  that read the cache arrays as members of `lbl_803B7878`. Left: the first `li -1` is scheduled before the base
  address is complete, and the 8-entry `a8180` fill (the original stores entry 0 through the base and entries 1..7
  through a pointer, with a second `li -1`).

Tried without result: 80020764 (16 instruction slots off in the vertex block whatever the x2/y2 spelling), 8001EBC8
(an `fmr`/`fsubs` pair stays swapped over 40 statement orders and return spellings), `main` (the saved-register
rotation also moves the prologue stores, so it is `other`), 8001F1D4 and 8001BD34 (declaration searches scored by
instruction order stalled at 10 slots off; 8001BD34 also depends on the `rodata_dummy` function, which the rules do
not allow), 8000DB10's neighbours 800156C8/80017344/800161E0/8001AB10 and the 80023360 family (untouched fragments,
all `other` when built self-contained).

Lessons:
- **`regs` needs equal branch targets.** A masked diff that hides labels can look identical while the code differs
  (800105AC). Compare branch displacements too.
- **Walking pointer for a packed header:** `n = *p++; id = *p++;` keeps one register and one `addi rX,rX,4`;
  indexing the header and then adding 4 makes a second pointer (8000DB10, exact).
- **Stack slot order of sibling inlines:** two temporaries in two sibling inlines get descending slots, while the
  same two declared in one body ascend (80011680).
- **Score a search by instruction order, not by register words.** A hill climb over declaration order whose score
  is "positions where the register-masked instruction differs" found `regs` forms in a few hundred compiles where
  the old exact-match score had stalled (8000AE38 family).

## Round 20 (small leftovers; `sched` and `slots` now count)

Levels as printed by `python3 -I tools/check_regs.py <file> --extra "-i src/game/rA_800068A0 -i src/game/rA_800068A0/wip"`. `sched` files were looked at with `tools/equiv/dd.py` (moved instructions are listed in each file header) and run through `tools/equiv/symcheck.py --anon`.

Totals: sched 4 functions / 1680 bytes.

| Function | Class | Bytes | File | symcheck |
|---|---|---|---|---|
| 800156C8 | sched | 0x234 | `equiv/fn_800156C8.c` | flags the two swapped conversion slots |
| 800161E0 | sched | 0x188 | `equiv/fn_800161E0.c` | clean |
| 8001AB10 | sched | 0x120 | `equiv/fn_8001AB10.c` | flags the argument set of one call (ordering artefact) |
| 80024EFC | sched | 0x1B4 | `equiv/fn_80024EFC.cpp` | clean |

Complete self-contained drafts still at `other` (new `wip/*_r20.*` files; the header of each says what differs):

- `wip/fn_80008B50_r20.c` (0x148): the original inlines the recursion four levels deep (82 instructions); this draft compiles to the plain recursive form (28). Needs #pragma inline_depth and the recursive helper as an inline.
- `wip/fn_80017344_r20.c` (0x2E8): same size; int-to-float conversions use each other's stack slots and one lha/xoris pair is scheduled across the fn_80021EF8 call boundary, one fmuls targets f0 instead of f31.
- `wip/fn_80021EF8_r20.c` (0x84): 27 vs 33 instructions: the original keeps base+0x10000-0x7fc0 in r31 and indexes with lwzx, and invalidates four dependent tables through four separate base registers (pooled file statics); the draft uses one struct.
- `wip/fn_8002230C_r20.c` (0x38C): rewritten with the GX state caches as separate definitions pooled behind the sine table (the real fn_8001E44C is repeated in the file to put the table at the head of the pool). That reproduces the per-array base registers and the 8-entry fill, but this compiler lays pooled objects out in order of first use, so the offsets of 0x8040..0x8260 differ from the original (address order). wip/fn_8002230C_r18.c is the other near miss (one struct, 2 words).
- `wip/fn_80023360_r20.cpp` (0x258): frame 0xb0 vs 0xa0 and 151 vs 150 instructions; the constructor-style store block (li 0x190, vtable store) is ordered differently.
- `wip/fn_80023E2C_r20.cpp` (0x18C): 100 vs 99 instructions: in the constructor-style store block the original reuses r0 for 0x190 where ours takes r11 and one more instruction; store order differs.
- `wip/fn_8002421C_r20.cpp` (0x1B4): same block as fn_80023E2C (110 vs 109 instructions).
- `wip/fn_800250B0_r20.cpp` (0x2D8): 178 vs 182 instructions; the original saves r19 as well (stmw r19).

Finding for 8002230C/80021EF8: `lbl_803B7878` is the pooled `.bss` of the translation unit (sine table, then the GX state caches as separate objects). With separate definitions the per-array base registers and the 8-entry fill of the original appear, but this compiler orders pooled objects by first use, and the original has them in address order, so the functions before them in the unit must touch the caches in that order. `wip/fn_8002230C_r20.c` shows the state; it repeats the real fn_8001E44C to get the sine table to the head of the pool.

Also for 8002230C: the two channel colours at `lbl_804CCC5C` are two separate 4-byte objects (the original loads +4..+7 through sda21 directly), not one array.

Not attempted (no draft): 8001EFE4, 80025A74, 8002600C, 8002607C, 80026208, 80026440, 800265B4.

## Round 21 (small functions without a draft)

Checked with `python3 -I tools/check_regs.py <file> --extra "-i src/game/rA_800068A0 -i src/game/rA_800068A0/wip"`; exact files also with `check_func.py --strict-references`.

Totals: exact 5 functions / 1460 bytes, regs 1 / 104, sched 1 / 152.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 8002600C | exact | 0x70 | `fn_8002600C.cpp` | append to the command list |
| 8002607C | exact | 0x18C | `fn_8002607C.cpp` | code translation, two switches; returns u32 (no narrowing) |
| 80026208 | exact | 0x80 | `fn_80026208.cpp` | fn_8002600C inlined |
| 80026440 | exact | 0x174 | `fn_80026440.cpp` | |
| 800265B4 | exact | 0x1C4 | `fn_800265B4.cpp` | assignment; returns the destination (that keeps r3 and gives the original registers) |
| 8001EFE4 | regs | 0x68 | `equiv/fn_8001EFE4.c` | Catmull-Rom interpolation; four named basis temporaries |
| 80025A74 | sched | 0x98 | `equiv/fn_80025A74.cpp` | static initialiser as plain stores; symcheck clean; header gives the global definitions it stands for |

The command list at 0x80025B0C.. is `{s16 n; s16 mark; Ent e[0x1ff]; Ent* cur; u8 mode;}` with 4-byte entries `{u8 code; u8 x1; s16 val;}`. Callers in rB narrow the code to u8 at the call (see rB notes), so the real prototype of fn_8002600C is probably `(Seq*, u8 code, s16 val)`; the matched file has `u32 code`, which compiles the same.

Skipped: 8001BD34. `wip/fn_8001BD34.cpp` is `sched` with a clean symcheck, but it places its rodata templates with `sPad` plus the `rodata_dummy` function, which the rules do not allow. The 0x8C bytes in front of the templates belong to six other functions of the unit (80018208, 80018F74, 80019504, 80019AB0, 8001A644, 8001B284, one of them unmatched); a clean file needs those real functions in front, as was done for fn_800C9084 in rG.

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`). symcheck `--anon --xargs` flags in these files are only
callee-name artefacts (the asm now names SDK functions `tan`, `PSVECAdd`, `GXSetVtxDesc`...); the equiv files show the
same flags.

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_8000FD20.cpp` | fn_8000FD20 | 0x180 | `halfF` reads the field into a local first: `f32 f = c->fovy; return f / 2.0f;` (f2/f3 swap) |
| `fn_8001EFE4.c` | fn_8001EFE4 | 0x68 | the h2 basis term computed one statement later (statement-move search) |
| `fn_80020354.cpp` | fn_80020354 + fn_80020764 | 0x410 + 0x37C | fn_80020764's first parameter typed `s16` (type search). fn_80020354 was already exact in the equiv file. |

Tried in round 23 without an exact result (besides r23b's automatic searches, see rE NOTES):
- fn_800156C8: statement moves + decl orders + `f32 c = b->cur;` local reach 6 words (hi/len FPRs and the keys/parts
  load order); 24 decl/load orders of those tried.
- fn_80024EFC: decl permutation + an `Err(msg)` inline reach 6 words; the message `lis` still loads after `__files`
  (8 Err/stderr spellings, FILE array type).
- fn_8001AB10: setClear colour as by-value struct, word store, casts: worse.
- fn_800244C4: second size as SLen inline / new local / block local: no change.
- fn_8001CD78: n2 merged with n, block-scoped, u32: no change.
