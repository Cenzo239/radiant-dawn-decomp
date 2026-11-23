# libplace c-sdk (lib-place-c): RVL_SDK / MetroTRK / MSL / Dolphin-SDK C sources

Sources are public CC0/decomp code (ogws, wii-ipl, Petari, wiiplay-pc, xd-decomp, mhtri); their license files and headers are unchanged.

## Environment note
`tools/build/dolmodel.py` reads `build/RFEE01/asm`. A fresh worktree does not have it, and without it every
function looks unreferenced (`refby` empty) and the dead-strip model fails everywhere. Create it without ninja:
`build/tools/dtk dol split <config.yml pointing at symbols.base.txt/splits.base.txt> build/RFEE01` (about 1 s; build/ is ignored).

## Tooling fixes (docs/libplace/c-sdk_tools.patch, patch of tools/build/place.py and gen_units.py; not committed to tools/, the integrator applies it)
1. `strip_object`: a relocation at offset == end of the previous kept symbol was mapped into that symbol when the
   symbol it really belongs to was dropped (WUDGetAllocatedMemSize's tail call `b __ntd_get_allocated_mem_size`
   became a reference of WUDRegisterAllocator: "reference to X: not in symbols.txt"). Relocation sources now map strictly.
2. `pad_end`: the last object of a section (no following symbol, e.g. WUD's .sdata/.sbss/.sdata2) may take the
   padding up to the section end; zero padding up to a 16/32-byte boundary before the next symbol is accepted
   for non-bss sections (fs.c `.data range ... is not 4-aligned`).
With the patch and the asm dir `libdrv.py --all` gives 289 ok (was 276).

## Placed with the tooling fixes only (no source change)
WUD/WUD.c (64 fns), FS/fs.c (25), GX/GXTransform.c (17), ARC/arc.c (13), AX/AXCL.c (12), OS/OSAlloc.c (3) (all ogws),
petari bte/hcisu_h2.c (8), wii-ipl bte/bd.c (2), vi/vi3in1.c (1).
WUD: the object has 20 functions the FE10 range lacks (newer SDK); the dead-strip model drops them and the data
strings of the dead functions stay (kept-data retry).

## Placed by a lib/map.json symbol entry
- petari bte/bta_sys_main.c (9), bta_dm_act.c (56), bta_sys_conn.c (8): the object defines `bta_sys_cb` (.bss 0x80492E18,
  0x90 bytes) but map.json did not name it, so the DOL symbol lbl_80492E18 looked undefined and bta_dm_act/bta_sys_conn
  could not resolve their reference. Fix: `symbols["bta_sys_cb"] = 0x80492E18`.
- petari bte/gap_utils.c (6), hidd_pm.c (3), wii-ipl bte/hidd_api.c (1): map.json symbols `gap_cb`=0x80495A80, `hd_cb`=0x80495E30
  (the objects define/reference them; the DOL only has lbl_ names).
- xd syn/synctrl.c (7), synlfo.c (2), synmix.c (5), synvoice.c (3), syn.c (7): symbols `__SYNn128`=0x803AF390,
  `__SYNVolumeAttenuation`=0x803AF6B0, `__SYNAttackAttnTable`=0x803AF8B0, `__SYNVoice`=0x804CC7D0, `__SYNSynthList`=0x804CC7D4,
  `__SYNNumVoices`=0x804CC7D8. syn.c: the DOL has the three sbss pointers in one 12-byte block (`__SYNVoice` is defined in
  syn.c, synvoice.c only declares it); MWCC lays tentative definitions out in reverse order, so they are written NumVoices,
  SynthList, Voice.
- petari bte/gap_conn.c (8): the 11 GAP_Conn* API functions are not in the DOL (dead-stripped by the original link, together with their
  trace strings). The dead-strip model keeps the survivors' strings at 8-aligned offsets (place.py strip_object keeps the alignment
  of the old offset), the DOL packs them at 4. Fix: made the dead API functions `static` in the source, so the object
  carries no strings of them (general trick for "stripped" sources whose data does not derive).
3. `gen_units.lib_unit`: the kept-data retries get a fourth variant (keep .bss/.sbss/.data/.sdata, strip .rodata/.sdata2):
   the original link kept the string pool of dead functions but not their const tables (bta_hh_utils.c, hidd_mgmt.c).
- petari bte/port_utils.c (7): dead functions made `static` (their .rodata tables otherwise had no code reference).
- petari bte/bta_hh_utils.c (5), wii-ipl bte/hidd_mgmt.c (1): tooling fix 3 (see above), no source change.
4. `gen_units.lib_unit`: the dead-strip retry also starts on "no references from code" (a const object only dead functions use,
   e.g. ptmf.c's `__ptmf_null`).
- ogws runtime/ptmf.c (2), wii-ipl gx/GXFrameBuf.c (15): tooling fix 4 (GXFrameBuf's .data had no code reference; with the dead-strip
  retry it places). map.json symbols `GXNtsc480IntDf`/`GXPal528IntDf`/`GXEurgb60Hz480IntDf`/`GXMpal480IntDf` (0x803A03F8/0470/04AC/0434)
  added for petari GXInit.c, which still fails (GXSetViewport name only exists once GXTransform.c is in link_select; data
  `GXTexRegionAddrTable`/`GXShutdownFuncInfo` unreferenced).
- ogws SC/scsystem.c (22): map.json had two false function entries (`__SCSetDirtyFlag` -> 0x802A1E3C inside nw4r BasicSound,
  `__SCGetConfBuf` -> 0x802C2954 inside AXFX): tiny identical-bytes coincidences, FE10 has no such functions. Removed from
  map.json (check_lib --all unchanged, 3273 of 3277).
- wii-ipl gx/GXTexture.c (32): FE10's range has `GXInitTexObjFilter` (between GXInitTexObjTlut and GXInitTexObjUserData); added with the
  Petari body in wii-ipl's `__GXTexObjInt` style, remap.py. (petari gx/GXTexture.c is now a duplicate; it also has 11 extra functions.)
- ogws GX/GXAttr.c (12): GXGetVtxDesc/GXGetVtxDescv/GXGetVtxAttrFmt/GXGetVtxAttrFmtv are not in the DOL; made `static` (the
  dead-strip model kept GXGetVtxDesc by its size).
5. `dolmodel.load_refs`: dtk names a non-unique local symbol `Name_<ADDR>` in the asm (PlayRecordCallback_803213C4); the reference graph
   lost those functions' references ("referenced nowhere in the DOL"). Names are now normalised back to the symbols.txt name.
- ogws NAND/nand.c (20), NAND/NANDOpenClose.c (12): `NANDSeekAsync` / `NANDOpenAsync` are kept in the DOL though unreferenced (export
  table): `#pragma force_active on` around them (as petari does for GXInitTexObjUserData).
- ogws OS/OSPlayRecord.c (4): tooling fix 5 only.
- petari MetroTRK msghndlr.c (16): map.json symbol `__TRK_reset` = 0x800060BC (a function in .init, dtk name fn_800060BC).
- wii-ipl axfx/AXFXChorusExp.c (7): symbol `__AXFXGetLfoSinTable` = 0x802C2954 (this is what the false scsystem mapping pointed at).
- symbols MEMAppendListObject/MEMGetNextListObject/MEMInitList/MEMRemoveListObject added (0x8030ED2C/EE08/ED14/ED9C) but
  ogws MEM/mem_heapCommon.c still says "the link knows it as fn_8030ED2C" until mem_list.c (duplicate, rename clash `MEMInitList`) is in the link set.
6. `place.strip_object(natural=True)` (+ `gen_units.lib_unit` retries it after the other variants, and also starts the dead-strip retry on
   "cannot derive a single base"): the model kept every symbol at the alignment of its OLD offset (8 for a float that merely sat at an
   8-aligned offset) and the padding behind it, so dropping a dead literal shifted the rest by 4. `natural` aligns 4-byte entries to 4 and
   drops the padding behind objects.
- ogws MTX/quat.c (2): tooling fix 6.
- petari kpad/KPAD.c (21): with fix 6 the data places; what is left is `reference to WPADIsDpdEnabled ... link knows as fn_80339628`.
  Added map symbol `WPADIsDpdEnabled` = 0x80339628; needs a WPAD source in the link set (or the integrator's rename of that symbol).
- petari MetroTRK serpoll.c (5): the DOL has one 0x18 .bss block (gTRKFramingState 0x14, then gTRKInputPendingPtr 4); the declarations were in
  the other order (`void*` tentative definition is laid out after the static), so they are swapped.
- NOT placed, wii-ipl mtx/mtx.c (14 fns): FE10's range also has __PSMTXRotAxisRadInternal/PSMTXRotAxisRad, PSMTXQuat, C_MTXLightPerspective/Ortho
  (bodies from Petari compile and the 17 functions place), but the .sdata2 pool order differs (DOL: 1,0,.5,3,2.0,-1.0,deg; ours 1,0,.5,3,deg,-1,2.0);
  reordering statements did not fix it. Reverted.
- ogws OS/OSReset.c (11): the DOL order is __OSShutdownDevices, __OSReturnToMenuForError, OSShutdownSystem; the source had OSShutdownSystem
  first and a global `__OSGetDiscState` the DOL does not have. Moved `__OSReturnToMenuForError` before KillThreads/OSShutdownSystem and made
  `__OSGetDiscState` static (inlined).
- wii-ipl Runtime/src/runtime.c (13): the file had `#pragma force_active on` at the top, so the model could not drop the five functions the DOL lacks
  (__shr2u, __shr2i, __cvt_sll_dbl, __cvt_ull_dbl, __cvt_ull_flt). force_active now only around __save_fpr/__restore_fpr/__save_gpr/__restore_gpr
  (the DOL references them only through the _savefpr_NN labels).

## Given up (cause)
- ogws WUD-independent WPAD (wii-ipl wpad/WPAD.c 24, ogws WPAD.c 39): FE10's WPAD differs from both (OnShutdown not in the DOL; WPADiManageHandler, __ClearControlBlock, WPADInit sizes differ).
- ogws OS/OS.c (20), OS/OSThread.c (20), petari os/OSThread.c (4), petari DolphinTRK dolphin_trk.c: the objects reference linker-script symbols (`__ArenaLo`, `__ArenaHi`, `_db_stack_end`,
  `_stack_addr`, `_stack_end`, `_db_stack_addr`) that are absolute values, not in symbols.txt; needs ABS symbols in the integrator's ldscript/place model.
  OSThread (petari) also needs `SleepAlarmHandler` mapped to 0x80320954.
- petari MetroTRK dolphin_trk.c (6): InitMetroTRK is 0x98 bytes in the DOL (trailing unreachable `blr` after `b TRK_main`), symbols.base.txt says 0x94: fix the symbol size (integrator), source is right.
- ogws OS/OSContext.c (15): needs labels `__RAS_OSDisableInterrupts_begin/_end` inside OSDisableInterrupts as symbols.txt labels (symbols.base.txt change).
- ogws OS/OSExec.c (7), petari os/OSExec.c (5): FE10's range also contains Run/Callback and __OSBootDolSimple/__OSBootDol (0x66c/0x1e0, between __OSRelaunchTitle and _ES_GetTicketViews) which
  neither source has in one file; a merge of both is needed (other bss layout too). petari os/OSCache.c, petari gx/GXTexture.c, vi/vi3in1.c (petari) are duplicates of placed sources.
- petari kpad/KPAD.c (21): data now places (fix 6) but references `WPADIsDpdEnabled`, which is only named once a WPAD source is in the link set.
- ogws MEM/mem_heapCommon.c (3): same (references MEM list functions the link knows as fn_ until mem_list.c, which clashes on `MEMInitList`, is in the set).
- wii-ipl mtx/mtx.c (14), petari mtx/mtx.c (10): float pool order differs, see above; petari lacks PSMTXTranspose/PSMTXRotRad.
- xd syn/synenv.c (4): FE10's .sdata2 order is 176.0, 2.0(double), 7.86432e7, 1000.0, 7.8642e7; the source creates 1000.0 first.
- ogws OS/OSNet.c (7): the DOL .data keeps the function-name strings ("NWC24iPrepareShutdown", ...) passed to inline helpers that ignore them; the compiler drops them.
- ogws NWC24/NWC24Ipc.c (1): `.sbss` base 0x804CC754 is not 8-aligned (MWCC emits 8-aligned section here, the DOL has it at 4); needs an alignment waiver in place.py.
- petari gx/GXInit.c (6): `GXSetViewport` name appears only when GXTransform.c is in the link set; `GXTexRegionAddrTable`/`GXShutdownFuncInfo` data not referenced.
- ogws MSL/e_pow.c, wii-ipl MSL_Common string/alloc/buffer_io/math_api, wiiplay MSL ansi_fp/printf/mbstring/string/strtoul/scanf/extras: MSL extab / exception-table objects (see docs/LIB.md), not tried.
- wii-ipl MetroTRK targsupp.c/mslsupp.c (4/2): functions in another order/version than the DOL (`.text: base not aligned to 32`), not pursued.
- ogws runtime/runtime.c (11): duplicate of the wii-ipl runtime placement now.

## Result (libdrv.py --all -j 1): 321 sources ok (baseline 276 with the asm dir present: 289 after fix 1-2); check_lib --all unchanged at 3273 of 3277.
