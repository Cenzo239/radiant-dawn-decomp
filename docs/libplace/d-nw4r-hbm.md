# Group D (round 2: nw4r snd/ut/lyt, HBM) notes

Baseline `libdrv.py --all -j 1` at start (lib-place-b2): ok 342.
Symbol edits are in `docs/libplace/d-nw4r-hbm_symbols.tsv`; `docs/libplace/apply_symbol_edits.py` now applies every
`docs/libplace/*_symbols.tsv` (idempotent). After applying, regenerate the asm with
`build/tools/dtk dol split config/RFEE01/config.yml build/RFEE01` (dolmodel reads the asm). config/ is NOT committed by this branch.

## Placed
- ut_DvdFileStream.cpp (ogws, +25), ut_DvdLockedFileStream.cpp, ut_FileStream.cpp, snd_DvdSoundArchive.cpp (27), ut_IOStream.cpp:
  (1) map.json: 0x802BCB00 is `DvdFileStream::CanAsync` (vtable slot 0x28) and 0x802A4D64 (other object) is `CanCancel` (both return 1, the
  map had them the other way round); (2) FE10's IOStream: `ReadAsync` is pure, slot 0x1C is `s32 Write()` returning 0 (`li r3,0`), and there is
  no out-of-line `IsBusy`. The DOL symbol 0x802BC430 was misnamed `ReadAsync__IOStream` (renamed to Write, tsv); ut_IOStream.h/.cpp and
  ut_NandFileStream.h changed accordingly. This also removes the `IOStream::Write undefined` blocker of round 1 (snd_DvdSoundArchive, DvdLocked, FileStream).

## Tool changes (tools/build/gen_units.py, lib_unit)
1. Regression of the merge of the SDK round: `PL.strip_object(obj, in_dol, kd, wd)` passed the weak-data set `wd` as the 4th positional argument,
   which became `natural` when the SDK round inserted that parameter before `extra_else`. The weak-data strip retry of the HBM round
   (RTTI/vtable copies whose DOL copy is in another object) therefore never cut anything. Now `strip_object(obj, in_dol, kd, nat, wd)`.
2. The strip retry is also started when the only errors are `.data`/`.rodata` mismatches and the first model found weak data pointing elsewhere
   (`P.weak_else` non-empty). General, only reached for weak RTTI/vtable references.
Effect of both (libdrv --all -j 1, 359 -> 365 ok, nothing lost): **newly placing, to be link-tested by the integrator**:
lyt_hbm/lyt_pane.cpp (28), lyt_picture.cpp (11), lyt_resourceAccessor.cpp (3), lyt_textBox.cpp (21), lyt_window.cpp (21),
ogws homebuttonMiniLib/HBMAnmController.cpp (3).

## Given up
- lyt_hbm/lyt_drawinfo.cpp (1): the DOL has no DrawInfo dtor of its own; the vtable slot points at 0x803527E0, the weak LinkListNode-shaped dtor that is the
  first function of the Group object (splits: Group starts at 0x803527E0). Renaming it to DrawInfo dtor makes drawinfo place but its range
  (0x80352764-0x80352820) then overlaps lyt_group (tried, reverted). Needs a model where a weak function may be matched to a same-bytes weak copy under another name.

## Placed (round 2, source edits)
- lyt_hbm/lyt_material.cpp (+23): the two file-scope statics `DefaultBlackColor`/`DefaultWhiteColor` are pooled in the DOL as black then white
  (.rodata 0x80378628: 8 zero bytes, white, 0.5f); the source had them the other way round. Swapped the definitions.
- ut_hbm/ut_ResFontBase.cpp (24): map.json had `Font::~Font` at 0x8035E1B4 and no ResFontBase dtor. 0x8035E1B4 is `ResFontBase::~ResFontBase` (slot 2 of its
  vtable); the weak `Font::~Font` copy is at 0x803592C4 (inside lyt_textBox, the first object that needed it). Map entries fixed, no source change.
- homebuttonMiniLib/HBMSound.cpp (8): the two archive names `wt\HomeButtonSe.wt/.pcm` are in .rodata in the DOL (0x80378250/0x80378264) while every
  other string of the object is in .data: they are file-scope `static const char[]` (a `readonly_strings` pragma does not work per function under `-ipa file`;
  it applies to the whole TU). Defined `sWtName`/`sPcmName` before HBMSoundCreate.

## Given up / open (round 2, cause)
- snd_StrmPlayer.cpp (48): .sdata2 pool order. DOL (from 0x804D1360): 0.0f, pad, double 2^52+2^31, double 2^52, 1.0f, 127f, 63f. Our compile (`-ipa file`)
  registers float literals at parse time in source order (1.0, 0.0, 127, 63) and the int->float doubles later at codegen (2^52 then 2^52+2^31). Swapping
  the pan/volume blocks of UpdateVoiceParams only flips 63/127 and the doubles; no source order tried gives 0.0 first, doubles, then 1.0/127/63
  (InitParam, the first user of 1.0, loads it from the late slot 0x804D1378). Not solved.
- lyt_hbm/ut_TextWriterBase.cpp (20): after the chain fix below the object models fine except `.bss range 0x804CA000-0x804CA022 is not 4-aligned`:
  the object is the last in .bss (section end 0x804CA024) and pad_end only pads up to a next symbol. A "last object of the section" padding rule would place it
  (not done: pad_end rules must not be relaxed). The model also needed place.py own_run to chain weak copies backwards from the trailing `__sinit`
  (template-instantiation object whose only non-weak function is __sinit): tried, no other source changed (libdrv --all identical), reverted.
- lyt_hbm/lyt_drawinfo.cpp (1): see above.
- HBMBase.cpp (44, not a libdrv candidate because HBMDraw is map status "diff"): the DOL has a weak `ArcResourceAccessor::~ArcResourceAccessor` (0x80348F08, size 0x6C)
  between the HomeButton ctor and create(); the ogws header has an implicit dtor and our create() does not emit it. Needs the original's use of the dtor.
- ogws nw4r lyt/ut/snd sources (lyt_pane, lyt_common, lyt_material, lyt_arcResourceAccessor, lyt_resourceAccessor, lyt_textBox, ut_ResFontBase, ut_ResFont, ut_CharWriter,
  wii-ipl/xeno variants of AxManager, SoundArchivePlayer, WsdPlayer, CharWriter, lyt_layout/animation): alternatives for ranges that another source of the same range already places
  (the DOL has one copy of the nw4hbm code, named nw4hbm; the nw4r-named ogws sources map onto the HBM addresses). Not worked on.
- ogws snd_AxManager.cpp (AXGetAuxACallback): `libdrv` says ok; symbols.txt names 0x802BE938 AXGetAuxACallback already, nothing to fix.
- extra-symbol (0 functions) entries (ef_handle, lyt_picture/window ogws, math_triangular, ut_TextWriterBase ogws): no own text section, nothing to place.
