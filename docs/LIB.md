# Library code (SDK, MSL, NW4R, HBM) from public decomps

Range 0x8028BC54-0x803608FC, 3,277 functions, 808 KB. Sources are CC0 decomps compiled with the game's compiler:
`doldecomp/ogws` (Wii Sports, SDK Nov 2006), `koopthekoopa/wii-ipl`, `SMGCommunity/Petari`, `xbret/xenoblade` (HBM only),
`Nikman800/wiiplay-pc` (Wii Play, SDK Dec 2006: WPADHIDParser, vi, AXFX, MEM list; key `wiiplay/`), `TeamOrre/xd-decomp` (Dolphin SDK seq/syn,
key `xd/`, edited for the RVL version). Copies live in `lib/<repo>/...`.

Status (tools/lib/check_lib.py --all, see lib/status.txt): 3,273 of 3,277 functions / ~803 KB (99.4%) verified byte-exact
against main.dol, with call and data targets checked. `lib/verified.json` lists them; `lib/map.json` maps source function -> address.

## Tools (tools/lib/)
- `ogcompile.py`, `libcompile.py`: compile a repo's sources to objects (parsed flags, never runs the repo's code).
- `libscan.py`, `place.py`, `mkmap.py`: find identical functions (relocs masked), place whole sections, write `lib/map.json`.
- `install.py`: copy used sources and header trees into `lib/`.
- `check_lib.py <key> [-v]` or `--all`: compile one lib source and compare each function with the DOL
  (runs `libcheck.py`, rules below). OK lines end with the verified address; `--all` writes it to lib/verified.json.
- `fuzzy.py`: rank near-miss candidates for unverified functions.
- `fdiff.py <key> <function substring> [-a] [--src file] [--cc GC/3.0a5] [--flag F] [--noflag F]`: side-by-side disassembly of
  the compiled function and the game (aligned with difflib, symbols masked); `--src` compiles a scratch copy with the flags of `<key>`.
Repos are cloned to `build/lib_ext/` (ignored by git); rebuild: clone, run the compile scripts into `build/lib_ext/objs`, then libscan/place/mkmap/install.

## Open (4 functions after Round 9, see the end of Round 9 Agent B; the list below is older)
- nw4r snd: struct layouts differ from ogws (members shifted by 0x10 etc.); fix the headers once and many functions match (see 1-3 word diffs from fuzzy.py).
- HBM (0x80344000-0x80361000): FE10 has an older nw4hbm. Pane is 0xD4 bytes (name[16] at 0xB4, userData[8] at 0xC4,
  basePosition/alpha/glbAlpha/flag at 0xCC-0xCF, mbUserAllocated 0xD0; fixed in lib/xeno/.../nw4hbm/lyt/lyt_pane.h). Its vtable
  has no GetMaterialNum/GetMaterial(u32) (GetMaterial() at 0x5C, LoadMtx at 0x60, as in ogws nw4r lyt); removing those from the
  xeno Pane/Window sources is the next step (many lyt diffs are vtable slots off by 4). homebutton::gui Manager/Component vtables
  are one slot shorter too (HBMGUIManager update/draw call 0x30/0x44 instead of 0x34/0x50). HBMRemoteSpk: cannotSendCnt limit 60.
- VI/SC/OS small constant differences (SDK revision), BTE leftovers, KPAD parts.
- About 25 functions still have exact bytes but fail a reference (map placed a callee/getter on another copy, snd LinkList
  dtors, data that is .bss in the game such as RFL cFavoriteColor); these are real differences of map or source.
- Not wired into configure.py/splits yet; names are in lib/map.json only, symbols.txt still uses fn_ names.

## Reference rules of the checker (tools/lib/libcheck.py)
Bytes are compared with relocated fields masked; each relocation must then point where the original points:
- Code of the same object (statics, methods, weak template copies such as `LinkList<T>` dtors, `@N@` thunks): OK if the
  name table agrees, or if that function's own code is byte-identical at the address the original branches to and its
  references verify too (greatest fixpoint per object). The callee is then also reported OK at that address
  ("referenced address"), which fixes wrong `diff` addresses of the map. A function start with the same size must exist in symbols.txt.
- Pointer tables (vtables, jump tables, `...data.N` pools): code entries as above (function plus offset, so jump-table
  labels land at the same offset), data entries (RTTI, strings) compared by content recursively, all other bytes equal.
  A pooled `...data.N` reference covers only up to the next address another relocation of the object points to.
- .bss/.sbss/common statics of the object: learned per object (a name table may hold another source's static of the
  same name). All verified references must agree (majority, the rest fail), two statics may not overlap, never in code.
  A global name that the tables place elsewhere still fails.
- Externs: OK at the symbols.txt/map address or at an address that matched code of another source references under the
  same name (nw4r ut is linked twice: main lib and HBM). Non-addresses learned by mkmap (bad HA/LO pairs) are ignored.
- SDK version strings (`__VIVersion`, `__GXVersion`, ...) are checked too: FE10 has "Nov 30 2006 ... (0x4199_60831)";
  wii-ipl sources use `SDKDefineVersionEx(LIB, date, time, 60831)`. Japanese strings must be Shift-JIS (dvdFatal.c).
- HBM classes in FE10 were built with RTTI on (vtable word 0 points to RTTI, names `nw4hbm::...`, `homebutton::...`);
  ogws homebuttonMiniLib HBMAnmController/HBMGUIManager/HBMRemoteSpk use `-RTTI on` in lib/manifest.json. ogws nw4r lyt/ut
  copies of the HBM code fail on RTTI names (`nw4r::` vs `nw4hbm::`), so the xeno nw4hbm sources are the right ones there.

## Fixing a near-miss source
Edit `lib/<key>` (and headers under `lib/<repo>/include`), run `python3 -I tools/lib/remap.py <key>` to re-place its
functions (exact -> ok, best shape match -> diff with the original's size), then `python3 tools/lib/check_lib.py <key> -v`.
Example: snd_Voice.cpp needed a 0x18-byte `VoiceOutParam` (FE10's SoundParam has no priority); its Voice class still has an
extra byte flag before mSyncFlag (see the InitParam diff), so field order is the next thing to reconstruct.

## Notes from the agent round (2026-11-10)
- FE10's nw4r snd differs from ogws: Voice has `mUnkFlag`, BasicPlayer is 0xD0 bytes (OutParam[4]), BasicSound has a new vtable/ctor,
  Channel/EnvGenerator have hold/key-group, SoundArchiveFile is 1.4. Edited headers live in lib/ogws/include/nw4r/snd.
- Some map.json entries were set by hand; re-running remap.py on those sources can undo them. install.py never overwrites edited sources.
- Open: StrmPlayer (multi-voice layout), WsdPlayer (wii-ipl variant), AxVoice SetMix, SeqTrack::UpdateChannelParam, vi.c setVerticalRegs/VIConfigure,
  older HBM (nw4hbm lyt/ut).

## Round 3 (2026-11-11)
StrmPlayer is the newer 8-track version (reference zeldaret/ss), BasicSound/BasicPlayer/AxVoice rebuilt, Pane of the older nw4hbm (0xD4 bytes) in lib/xeno.
Open: WsdPlayer/WaveSound/SoundArchivePlayer (agent stopped by a usage limit, resume), BasicSound::UpdateParam, SeqSound::ReadVariable,
BasicPlayer ctor, snd_StrmFile out-of-line loaders, Pane vtable slots (GetMaterialNum/GetMaterial missing in FE10), Sound3DManager::detail_Update (placeholder body).

WsdPlayer/WaveSound/WsdFile/BankFile/ExternalSoundPlayer/AxfxImpl/FxChorus/FxReverbHi added from the ogws sources (FE10 layouts). Open: PrepareSeq/Strm/WaveSoundImpl
(SoundStartable::detail_SetupSound has 4 args in FE10), SoundPlayer.cpp, Sound3DActor/Listener, Fx SetParam register allocation.

## Round 5 (2026-11-11)
snd start path is the newer NW4R (zeldaret/ss): `SoundStartable::detail_SetupSound(handle, id, hold, startInfo)`, `SoundArchivePlayer::detail_SetupSoundImpl`
(0x802B00C4, ambient info + SoundActor, no ENABLE_PLAYER_ID check in FE10), `SoundInstanceManager::Alloc(priority, ambientPriority)`, Prepare*Impl without voices.
New sources: snd_SoundPlayer.cpp (ss version, sound-thread lock, 0x4C bytes), snd_SoundStartable.cpp, snd_PlayerHeap.cpp (only Attach/DetachSound), petari kpad/KPAD.c
(uniRingBuf[16] in FE10; KPADInsideStatus is still 0x14 bytes too big at the end, see KPADiControlDpdCallback). SoundActor/Sound3DActor are the ss classes
(nw4r::snd::SoundActor, 4 actor players, Sound3DParam in snd_Sound3DManager.h). StrmFile loaders out-of-line incl. ReadStrmTrackInfo.
BasicSound has `AmbientArgInfo mAmbientInfo` (SetAmbientInfo/GetAmbientPriority). PlayerHeap: mSound/mPlayer before the link node.
SoundArchivePlayer vtable: detail_ConvertLabelStringToSoundId (0x28) before detail_SetupSound (0x2C); the former lives at 0x8025F238 (game range).
dtk splits a trailing `blr` after a tail `bctr` into its own symbol (e.g. 0x802A3220); map such functions with the larger size.
HBM: Pane vtable without GetMaterialNum/GetMaterial(u32), Window overrides FindAnimationLink (not ...Self), AnimTransform has one SetResource,
Material has no AnimResource overloads and the older layout (name at 0x4, anim list 0x18, mpGXMem 0x58).
Register-only near misses: detail_SetupSoundImpl (r15/r16 in the seq alloc), BasicSound::UpdateParam (f-registers), BasicPlayer ctor (constant order).
Open: Sound3DManager is the ss version with Sound3DEngine (mpEngine at 0x18), still ogws code; SeqPlayer layout (local variables at 0x154);
nw4hbm Material functions (older version), KPAD tail fields, fuzzy.py 1.000 candidates that fail on references.

## Round 6 (2026-11-12)
- Sound3D: FE10 is the Sound3DEngine generation (zeldaret/ss, older): new sources snd_Sound3DCalculator/Engine/Listener.cpp, Manager rewritten
  (0x28 bytes, engine set in Setup via a function-local static). Positions are relative to the listener matrix, Listener is 0x58 bytes
  (velocity at 0x30, node at 0x50), no biquad filter. All match.
- New snd_StrmSound.cpp / snd_StrmSoundHandle.cpp (ss version, 8 track volumes at 0xE6C). Voice::SetVoiceOutParam, Channel::NoteOff
  (mUnkFlag = release-ignore), SeqTrack::UpdateChannelParam (voice-out loop), UpdateChannelRelease without lock, SeqPlayer Get*Variable,
  DvdFileStream without size fallback, EnvGenerator::Init (SetAttack before SetHold).
- KPAD is the May 2007 version: no aim mode/play modes/fs revise (struct 0x524), KPADDisableDPD/EnableDPD, KPADiUpdateSensorHeight,
  busy-wait in KPADInit, no WPADGetStatus check in KPADRead, needs `-fp_contract off`. Whole file matches.
- SDK: __cvt_sll_flt (runtime), vi3in1 (RGBOverDrive 1), setVerticalRegs (clock select reg), NAND/ARC/GXFifo/AXCL/... re-placed.
- tools/lib/saferemap.py: re-places only unverified functions on exact matches, keeps a change only if OK count rises.
- HBM ut: nw4hbm TextWriterBase has no mWidthLimit (charSpace at 0x4C); xeno ut_TextWriterBase.cpp added.
Open: nw4hbm Material = wii-ipl NW4R lyt material (TexMap 0x20, static colours in .data) in nw4hbm namespace -> port needed;
TextWriterBase big functions (older code, wii-ipl source is closer); FxChorus/ReverbHi ctor (SetParam not inlined) and SetParam
(zero register reuse); TRK_fill_mem (r3/r4 swap, 3 tries); SoundArchivePlayer::detail_GetFileAddress (prologue scheduling, 3 tries);
VIConfigure; HBMBase.cpp not compiled; large unmapped SDK regions without reference source (0x80325E4C-0x8032A1F0, 0x8033B840-0x8033FB84).
wii-ipl ut_TextWriterBase.cpp crashes libcheck (KeyError bytes_ok).

## Round 7 (2026-11-12, HBM)
- HBMBase.cpp compiled and ported: FE10's HBM is "Jul  9 2007 12:47:26 (0x4199_60726)" (version string in .data at 0x803B4080).
  Source is `lib/ogws/src/homebuttonMiniLib/HBMBase.cpp` with `-Dnw4r=nw4hbm -DHBM_PANE_LAYOUT` (the xeno HBMBase.cpp is only the
  ogws file with the sound code commented out, so it was dropped). 47 of 49 functions match; the full-width `L'？'` literal had to
  become `L'\xFF1F'` (SJIS compile), that was the old compile failure.
- FE10 differences to the ogws source: no nw4r::snd in HomeButton (0x750 bytes, `int mUnk5C8` = 1 before iReConnectTime, mAppVolume
  at 0x5D4, AXFX reverb at 0x5E4); BlackFader has a `bool flag_` at 0xC (set by init(), cleared when the Wii Menu button is chosen,
  VISetBlack(mUnk5C8 || !flag_) in state 19); scBtnName/scTxtName have three names + NULL; initgx calls GXSetCullMode first;
  draw/getSelectBtnNum/play_sound/fadeout_sound/BlackFader and all small private helpers are inline (not emitted); new API
  `HBMCreateSound(arc, mem, size)` (tail call to 0x8034856C) and `HBMUpdateSound()` (0x80348DB0) after HBMSetAdjustFlag; no
  HBMStartBlackOut/HBMSetBlackOutColor/HBMIsReassignedControllers; SpeakerCallback uses `Controller::playSound(int)`.
- FE10's HBM has its own small sound engine instead of nw4r::snd: 0x80347FBC-0x80348A28 (4+3 players of 0x3D60 bytes, files
  "wt\\HomeButtonSe.wt"/".pcm", thread, AI callback 0x80348178), callees in 0x80325E4C-0x8032A1F0. No reference source; names in
  HBMBase.cpp are placeholders (HBMSoundCreate/Update/Play/StopAll/SetVolume).
- ogws `lyt_pane.h` `HBM_PANE_LAYOUT` now is the FE10 Pane (name[16] at 0xB4, userData[8] at 0xC4, basePosition/alpha/glbAlpha/flag
  at 0xCC-0xCF, 0xD4 bytes), same as lib/xeno; only HBMBase.cpp uses the define. ogws HBMController.h got the `playSound(int)` overload.
- RemoteSpk::ClearPcm clears only info[0] in FE10 (0x80347A24).
- `KeyError bytes_ok` for wii-ipl ut_TextWriterBase.cpp is not reproducible any more (libcheck fills bytes_ok for every evaluation).
Open in 0x80344000-0x80361000: HBMDraw (0x80348C1C, only the stack slots of the two GXColor temps and the argument copy are swapped:
FE10 has the argument copy at 8(r1), the {0,0,0,a} temp at 0xC and the {r,g,b,a} temp at 0x10; `GXColor clr = getColor(alpha);
GXSetTevColor(GX_TEVREG0, clr)` is the next thing to try), Controller::updateSound (0x803473F0, 568 bytes, no source in ogws/xeno),
a vararg stub 0x8034553C (empty `(const char*, ...)` function before FrameController::init), 8-byte `return 0` stub 0x80346CD8,
the HBM sound engine above, Window::DrawFrame (0x8035A148, wii-ipl lyt_hbm version differs in 25 words of register allocation around
the inlined Get*TexCoord/flipInfos code).


## Round 7 (2026-11-12, Agent B: SDK gaps)
- 0x8033B0D4-0x8033FB88 is `WPADHIDParser.c` (ogws has only the header). The Nov-2006 version is in `Nikman800/wiiplay-pc`
  (CC0, `src/revolution/WPAD/WPADHIDParser.c`, Petari's reconstruction adapted to the old SDK: `initExtension` reads 2 bytes at
  0x04a400fe, `WPADiSendSetReportType` has 3 args, report 0x34 is empty, no `extEnc`). All 22 functions match as-is; installed as
  `lib/wiiplay/src/revolution/WPAD/WPADHIDParser.c` with the wiiplay include tree (ogws-style headers, `-DVERSION_RHAE01`).
  The Petari HIDParser compiles only with `-fp hardware` (the petari spec forces `-fp off` for wpad/) and is the newer SDK.
- 0x80325E4C-0x803267B4 is SEQ (`seq.c`), 0x80327E14-0x8032A274 is SYN (`syn*.c`): the Dolphin SDK MIDI synthesizer, ported to
  the Wii. Source `TeamOrre/xd-decomp` (CC0) `libs/dolphin/src/{seq,syn}`, installed as `lib/xd/...` and edited: SYNSYNTH has the old
  layout (no zeroBase at 0x28) plus two callbacks at 0x3134/0x3138 (`initCallback(axvpb, synth, ch)` after `MIXInitChannel`,
  `updateCallback(axvpb, synth, ch)` in `__SYNUpdateMix`); `__SYNVoice` is a pointer set by `SYNInit` to a static array of
  `AXGetMaxVoices()` (96) entries, guarded by `AXIsInit()`; `SYNInitSynth` does `OSPhysicalToCached(aramBase)`; `MIXInitChannel`
  has an auxC argument (-960); AXPB/AXVPB are the Wii ones (`lib/xd/.../dolphin/ax.h`, pb at +0x28, sync bits 0x400/0x8400/0x48400,
  SRC 0x10001/0x20000); no SRC ratio clamp; `__SYNGetEnvelopeTime` is static, uses `(f32)pow(2.0, x)` and /3 (3 ms frames);
  non-looping samples use the sample start as loop address; SEQ ticks use 96.0f instead of 160.0f; `seq.c` needs compiler GC/3.0a5
  (3.0a5.2 schedules `SEQSetState` differently; `lib/manifest.json` has it per source). 46 of 48 functions match.
  Open: `__SYNSetupVolumeEnvelope` (stack slot of the 2nd fctiwz temp 0x18 vs 0x20) and `__SYNSetupPitchEnvelope` (same + r30/r31 swap).
- MIX (0x8030EE28-0x80311E84, 8 functions incl. 0x16C0-byte `MIXInitChannel` and 0x1690-byte `MIXUpdateSettings`) is the Wii mix.c
  with auxC/DPL2; the Dolphin `mix.c` (xd, dolsdk2001; `libcompile.py` compiles it) only resembles `__MIXSetPan` (0.97) and the
  small setters: a port is still needed. `fn_803106E0` = `MIXReleaseChannel`, `fn_8030F020` = `MIXInitChannel`.
- Other wiiplay-pc hits: `mem_list.c` (MEMInitList etc. at 0x8030ED14, unmapped before), `VI/vi.c` (VIConfigure 0x803304B4 matches
  there; installed with its 22 exact functions only), `AXFXReverbHiExp.c` (callback at 0x802C1268 matches; petari/wii-ipl copies don't:
  petari flags, one missing `earlyLine` write), `__InitParams` ported into wii-ipl `AXFXChorusExp.c`, `PADControlMotor` added to
  wii-ipl `Pad.c` (missing in the IPL source), `GXInitTexObjFilter` added to petari `GXTexture.c` (0x80305DB4 was mapped as an
  8-byte `GXInitTexObjUserData`).
- Small fixes: `__OSBootDol` only needed the `__OSBootDolSimple` symbol; `__CARDUpdateFatBlock` unsigned division (and address
  0x802F2E78); `WPADIsDpdEnabled` reads the byte at 0x983; petari `mtxvec.c` for `PSMTXMultVecSR`; wii-ipl `bte/utl.c` for
  `utl_freebuf` (0x802C71FC; the other exact hit 0x802A0FF0 is a verified snd function); `__OSReturnToMenuForError` (0x8031E34C,
  OSReturnToMenu with flag 2 / shutdown event 1 / `__OSHotReset`) added to ogws `OSReset.c`.
- EXIBios.c (0x802FE2F4-0x802FEA0C, 8 functions) is unmapped: wii-ipl sizes match but 13-18 words differ per function in a way no
  compiler/flag changes (tried 3.0a3-3.0a5.2, 2.x, -O levels); likely a source difference of the Nov 2006 EXI.
- Tried without success (3 attempts): `C_MTXLightOrtho` (FE10 has no fmadd), `DBInitInterrupts` (register choice),
  `__construct_new_array` (DOL function at 0x8028BE18 has a different prologue).
- Result: library range 3,041 of 3,277 functions (was 2,925 at the start of the round; includes Agent A's HBM work).
- Scratch helpers used: a per-function side-by-side disassembly diff (dtk `elf disasm` of the compiled object vs `build/RFEE01/asm`)
  and a compiler/flag sweep; worth adding to tools/lib if needed again.

## Round 8 (2026-11-12, Agent A: MIX, EXI, flag cases)
- MIX is 0x8030EE28-0x80312318 (13 functions, incl. `__MIXUpdateAuxVolumes` 0x80311E84 and `__MIXResetAux` 0x803122C0, the remote
  speaker mix). Source `InusualZ/mhtri-decomp` (CC0) `src/MIX/mix.c`, installed as `lib/mhtri/src/MIX/mix.c` (+ `mix.h`), adapted to
  the ogws AX headers. FE10 (Nov 2006) differences: no MIXQuit/MIXSetSoundMode/MIXGetSoundMode/MIXSetSPan, `MIXInit` without the
  "already initialised" check. All 13 match (tables verified by value). Other Wii mix.c copies: yannicksuter/mscharged-decomp,
  YggdrasziI/mlab-decomp (both CC0, in build/lib_ext/mixsrc).
- EXIBios.c was compiled with `-schedule off` (manifest flag): all 22 FE10 functions of the wii-ipl source match. `EXIProbeEx` ends
  with `return -(__EXIProbeStartTime[chan] == 0);`, version string is Nov 30 2006 03:26:56. A sweep of `-schedule off` over all
  other sources with open functions gives nothing (only 4-12 byte stubs), so this is EXI only.
- `__construct_new_array`: NMWException.cpp needs `-use_lmw_stmw on` (stmw prologue). No other source gains from that flag.
- `C_MTXLightOrtho`: no fmadd because the product is cast: `transS + (f32)(scaleS * (-(r + l) * tmp))` (same for T), size 0x88.
- Still open: `DBInitInterrupts` (matches only with the Wii/1.0 compilers, which break 4 other functions of DebuggerDriver.c, so it
  is a register-choice problem of the source), `TRK_fill_mem` (r3/r4 swap, statement order has no effect), SYN envelopes,
  Fx SetParam, detail_GetFileAddress, BasicSound::UpdateParam, BasicPlayer ctor (compiler sweep GC/3.0a3-3.0a5.2, Wii/1.0x and
  flags -schedule off/-opt nopeephole/-inline off/-ipa off/-opt level=3/-use_lmw_stmw on: no hit).
- Result: library range 3,066 of 3,277.

## Round 8 (2026-11-12, Agent B: HBM leftovers, MSL, TRK, stubs)
- New `lib/ogws/src/homebuttonMiniLib/HBMSound.cpp`: FE10's own HBM sound engine (0x80347FBC-0x80348A28), reconstructed from the
  disassembly, all 8 functions match. It plays the "midi\\NN_*.mid" files of the HBM archive with the SDK's SEQ/SYN/MIX on its own
  thread: work area 0x1D128 bytes (4 + 3 sequence players of 0x3D60 bytes = SEQSEQUENCE + used/next/prev/id, two lists, ARC handle,
  OSThread, message queue, 0x2000 stack, wt/pcm pointers), ids 4/23/25 use the second player pool. `HBMSoundSetVolume(gain)` is
  `10 * 20 * log10(gain)` clamped to -904..60; `HBMSoundUpdate` (0x8034873C) is empty. What made MWCC's register choice match:
  declare variables where they are first used (`for (int i ...)`, `HBMSePlayer* p = NULL;` after the switch) and put repeated code
  in `static inline` helpers (`GetList`, `FreePlayer`, `UpdateList(HBMSeList*)`); the thread stack top is
  `(void*)((u32)work->stack + 0x2000)`.
- `Controller::updateSound` (0x803473F0) written in the xeno HBMController.cpp: speaker is muted for a second (`soundOff(1000)`
  inlined) after 8 minutes of playback or when the byte at WPADCB 0x983 (`WPADGetRadioSensitivity`, 0x80335A9C; ogws WPAD.c still
  calls that function `WPADIsDpdEnabled`, the real one is at 0x80339628) is <= 85. `getController` is the `blr` at 0x80347638.
- xeno HBMGUIManager.h: FE10 has no `Manager::delComponent` and no `PaneManager::add/delLayoutScene` virtuals; with them removed all
  GUI functions match. `Manager::update(KPAD)` is the `return 0` stub at 0x80346CD8, `Component::update(KPAD)` is 0x80346C88.
- Empty vararg debug prints: `WUD_DEBUGPrint` (0x8034553C, new ogws WUD/debug_msg.c), WPAD `DEBUGPrint` (0x80340C30),
  `__DSP_debug_printf` (0x802F5A94).
- MSL: the stdio/string part (0x8028CF74-0x80291CF0) is the Wii Play MSL (`wiiplay-pc/src/MSL`, `src/MSL_C`; only `src/revolution`
  had been compiled). Installed as `lib/wiiplay/src/MSL*/` with the ogws MSL flags: ansi_files, ansi_fp, arith, direct_io, extras,
  file_io, FILE_POS, math_sun, mbstring, printf (both), scanf, string, strtoul, w_sqrt, misc_io, wchar_io, wstring. Added what FE10
  links in addition: `fprintf`, `labs`, `atoi` (strtol inlined), `strtok`, `raise` (new signal.c), `itoa`/`__msl_itoa`,
  `__num2dec` (needs its own copy of the round-up loop with the pointers declared the other way round). ogws `w_acos/asin/atan2/
  fmod/pow.c` installed, `e_log10.c`/`w_log10.c` written (fdlibm). Still different: `double2hex`, `__pformatter` (named symbols).
- MetroTRK: `SMGCommunity/Petari` `src/MetroTRK` (GC/2.7, `-inline deferred, auto -str reuse,readonly -sdata 0 -sdata2 0`) matches
  FE10 as-is: 20 sources, 101 functions (incl. `TRK_fill_mem`), installed under `lib/petari/src/MetroTRK`. wii-ipl `targsupp.c`
  is split into four 8-byte asm functions (the `entry` points are no function symbols for the checker).
- Small SDK additions (FE10 links them, the reference sources lacked them): `GXGetTexObjMinFilt`, `GXGetTlutObjData`,
  `GXGetTlutObjNumEntries`, 24-bit `GXGetTexObjData`, `GXSetCurrentGXThread`, `AXIsInit`, `AICheckInit`, `DVDGetTransferredSize`,
  `__OSReboot` (no partition type). Re-placed stubs: GKI_sched_lock/unlock/delay/exception/os_free, btm_inq_db_init,
  L2CA_RegisterCompression, bta_dm_reset_complete, btm_route_sco_data, __CARDDefaultApiCallback, __DVDRestartMotor, ISFS_Seek,
  AXFXReverbHiCallback, ARCClose/ARCCloseDir, five WPAD->WUD wrappers, ut IOStream/FileStream sinit (typeInfo of IOStream is
  0x804CC230; the old entries had matched BasicSound code by accident). Identical `blr`/`li r3,0` stubs were assigned by link order.
- lib/map.json cleaned: 1,665 unverified entries removed (address is no function start, or verified under another name, or absurd
  size), 70 entries moved to the address the checker verified. Hand-set entries outside the lib range are kept.
- Open (3 tries each, no success): HBMDraw (stack slots of the GXColor temps are exactly reversed; variable/branch/definition
  order and an out-parameter variant change nothing or the code), Window::DrawFrame (25 words of volatile-register choice; the
  order of the local declarations is not it). Not looked at: 0x802C4E78-0x802C5C48 (10 functions, older uusb/USB code),
  CARD 0x802F55B0/0x802F56CC, OSExec 0x8031A00C-0x8031A74C, NAND safe open/close, 0x8031E508-0x8031E718, 0x80321FFC-0x80322120,
  0x80313024-0x803133E8, 0x802A3220 (the `blr` dtk splits off BasicSound::GetAmbientPriority).

## Round 9 (2026-11-12, Agent A: SDK leftovers)
All functions of the list are done except `fn_8028BC54`; `check_lib.py --all`: library range 3,264 of 3,277 (the count only
covers `fn_` symbols; the named leftovers InitMetroTRK, udp_cc_*, gdev_cc_*, __GXInitGX and the three NWC24 functions are verified too).
- uusb (0x802C4E78-0x802C5C48): FE10 has the tracing `uusb_ppc.c` ("HCISU_LOG"/"HCISU_ERR" through OSReport when `usb.trace_state`
  is set). `Nikman800/wiiplay-pc` `src/revolution/BTE/uusb_ppc.c` matches as-is; its bodies replace the wii-ipl file (wii-ipl header
  block kept, compiler GC/3.0a5.2 instead of 3.0a5 for this file: `uusb_WriteCtrlDataCB` needs it). 14 functions.
- NAND: `NANDSafeOpen`/`nandSafeOpen`/`NANDSafeClose` (synchronous, no "simple" mode, 13-byte file name buffer) added to ogws
  NANDOpenClose.c after the wii-ipl source; FE10 does not link the SafeOpenAsync family. `nandChangeDirCallback` (0x80315B50,
  nandConvertErrorCode inlined) is in ogws NANDCore.c as a global (its only user `nandChangeDir` is verified from the wii-ipl copy).
- OSExec (Nov 2006): `__OSLaunchNextFirmware` (0x8031A00C) reconstructed in ogws OSExec.c: static buffers after `views`
  (game TOC 0x20, partition info 0x20, TMD 0x4A00, disk id), static pointers in .sbss, message "\nsecurity error(%d) has occurred",
  failure path `__OSReturnToMenu()` (0x8031E718) or `__OSHotReset()`; the TMD struct needs `#pragma pack(4)` (u64 at 0x184).
  `__OSRelaunchTitle` (0x8031A600; `_ES_GetTitleId` inlined, `pTid` initialised at its declaration). `__OSBootDolSimple`
  (0x8031A74C) is the Petari function without partition type/title id/disk id code; Petari's newer `__OSLaunchNextFirmware` is
  renamed `__OSLaunchNextFirmware_new` (static, unused) so the call goes to the ogws one (lib/map.json `symbols`).
- OSReset: `OSRestart` (0x8031E5B8), its NAND-title helper (0x8031E508, name `RestartNandTitle` is a placeholder; static
  `bootThisDol` in .sbss) and `__OSReturnToMenu` (0x8031E718, line 869) added to ogws OSReset.c.
- OSNet.c (Nov 2006) contains its own weak NWC24 functions: `NWC24iPrepareShutdown`, `NWC24iSynchronizeRtcCounter`,
  `NWC24SuspendScheduler`, static `NWC24iRequestShutdown`/`NWC24Shutdown_`/`NWC24iSetRtcCounter_` and a private `CallbackAsyncIpc`
  (0x80321D60-0x80322250). What matched: `__declspec(weak)` plus `never_inline` on the FIRST declaration (otherwise `__OSInitNet`
  inlines them), descriptor in a local via a macro (not `&fd`), locals declared `result, fd, closeResult`.
- New small sources: `lib/ogws/src/revolution/OS/OSIdle.c` (`OSSetIdleFunction`, 0x803208BC), wii-ipl `card/CARDStat.c`
  (dolsdk2004; `UpdateIconOffsets` + `CARDGetStatus`; keep `CARDSetStatusAsync` in the file or the helper is inlined),
  `card/CARDNet.c` (`CARDGetSerialNo`), `CARDProbeEx` in CARDMount.c, petari `mtx/mtx44vec.c` (`PSMTX44MultVec`), petari
  `UDP_Stubs.c`. Added functions: `DVDCancelAll` + `cbForCancelAllSync` (ogws dvd.c; `DVDCancelAllAsync` locals reordered to
  `enabled, block, success`; 0x802FB0E4 had been mapped as an AX callback by accident), `GXProject` (ogws GXTransform.c, Petari
  source; needs the ogws `-fp_contract off`), `GXAdjustForOverscan` (wii-ipl GXFrameBuf.c, dolsdk2004 source), `PSMTX44Concat`
  and `C_MTX44Inverse` (petari mtx44.c, dolsdk2004 source with `(f32)__fabs()` and `#pragma fp_contract off`).
- `__GXInitGX`: FE10 has no `__GXSetGenMode()` call before `GXSetCoPlanar`. MetroTRK `EXI2_GDEV_GCN/main.c` needs `-sdata 8`
  (manifest flag; gdev_cc_write/read/open use r13). `InitMetroTRK` is mapped with size 0x98 (dtk splits the trailing `blr`).
- Pitfall: a `static` forward declaration keeps a later non-static definition internal, so an unused function silently
  disappears from the object and check_lib prints no line for it (MATCH although nothing was checked): look for the OK line.
- Open: `fn_8028BC54` (0x80 bytes) is no library code: a static initialiser (`__sinit`) of the last game source file
  (referenced from .ctors, writes floats from the game's .sdata2 to game .bss at 0x80430D00/0x80430D2C); it belongs to src/.

## Round 9 (2026-11-12, Agent B: register and stack-slot cases)
Library range 3,273 of 3,277 (together with Agent A). What made the old "register only" cases match was the source form:
- `BasicPlayer::BasicPlayer()`: the later NW4R has `PlayerParamSet() { Init(); }`, then `mId(INVALID_ID)`, then `InitParam()`.
  Writing the body as `InitParamSet(); mId = INVALID_ID; InitParam();` gives the constant order (`li` 0, 1, -1) and the hoisted
  `mPan` store; the ogws fake `mPan = 1.0f;` is not needed (the scheduler hoists that store by itself).
- `BasicSound::UpdateParam`: `lpf = mLpfFreq; lpf += mAmbientParam.lpf;` and a copy loop for `fxSend[i] = mFxSend[i]` before
  `fxSend[AUX_A] += mAmbientParam.fxSend`.
- `FxBase` has `virtual void OnChangeOutputMode() {}` after `UpdateBuffer` (0x802A5F24, vtable slot 0x18); `AxManager::SetOutputMode`
  (0x8029CF8C, 0xF8 bytes) is the zeldaret/ss version (early return, interrupt lock, loop over the three effect lists).
- `FxChorus/FxReverbHi::SetParam`: the zero stored to `busIn/busOut` and the heap size share a saved register (`li r31,0` once, no
  `li` on the `mHeap == NULL` path). MWCC reuses a register that already holds a constant only for later uses in the same block,
  so the size variable must exist before the stores: `u32 heapSize = 0;` before `busIn = NULL` and an inline
  `HeapTotalSize(mImpl.mHeap, heapSize)` that returns its argument for a NULL heap. With that the constructors stop inlining
  `SetParam` too (all four functions match). `mHeap` is read directly (AxfxImpl member is public in the header).
- SYN envelopes: `__SYNGetEnvelopeTime` assigns to a local `s32 time` before returning; then both float-to-int conversions use one
  stack temp (0x18). Pitch envelope: `voice->pePitch = voice->art->eg2Pitch; pitch = voice->pePitch;` (register order) and the decay
  part reads `voice->pePitch` again.
- `DBInitInterrupts`: `#pragma optimization_level 1` around the function (as wiiplay-pc; levels 0/1 build the handler address in r3,
  level 2+ does not). No -O4 source form found.
- `PSMTXTranspose` (0x80312444) and `PSMTXReflect` (0x80312A50) added to wii-ipl mtx.c (Dolphin SDK bodies with `register` locals
  and an `asm {}` block; the compiler schedules them into the FE10 order). The old map entries there (C_MTXInverse, petari
  PSMTXConcat/C_MTXLookAt) were wrong placements and are removed.
- `Voice::Voice()` (0x802B71AC): `VoiceOutParam` has a constructor (volume/pitch 1, rest 0). 0x802A9EAC is
  `SeqSound::SeqLoadTask::~SeqLoadTask()` (map fix; 0x802A7CB4 is the MmlSeqTrack destructor).
- `HBMDraw`: stack slots low to high are the by-value argument, the {0,0,0,a} colour, the {r,g,b,a} colour. Needed: the ogws/xenoblade
  `static void drawBlackPlate(l, t, r, b, GXColor clr)` helper, a named `GXColor clr = getColor(alpha);` in `BlackFader::draw()`, and
  `getColor` building the fader colour in a nested inline (`MakeColor`) while the black colour is a local of `getColor`: locals of a
  deeper inline get the higher slots.
- `check_lib.py --all` now counts a symbol that dtk split off inside a verified function (the `blr` after a tail `bctr`, 0x802A3220,
  inside `BasicSound::GetAmbientPriority`) as verified.
Observations on MWCC (GC/3.0a5.2) from these cases: volatile registers are handed out so that the constant created last gets r0;
stores are kept in source order but a store whose operand is ready early can move up one or two places; `li`/`lfs` loads are
hoisted to the block start; a constant in a register is reused by later instructions of the same block only.
Open (each with more than 5 tries):
- `SoundArchivePlayer::detail_GetFileAddress` (0x802AFE14): only the prologue differs, FE10 has `lwz r0,0x18(r3); cmpwi` directly
  after the LR save, ours after `mr r28,r3`. Named local, inline/auto-inlined getters, goto forms and pragmas do not move it.
  The same hoist exists in `detail_SetupSoundImpl` (`_savegpr` prologue) and in functions that keep `this` in r3.
- `SoundArchivePlayer::detail_SetupSoundImpl` (0x802B00C4): 10 words, r15/r16 of `allocPriority`/dropped sound in the first
  inlined `SoundInstanceManager::Alloc` only (whichever case comes first in the switch; the other two match). Outer clamp forms
  (two statements, ternary, manual if) and Alloc declaration orders change nothing or more.
- nw4hbm `Window::DrawFrame` (0x8035A148): 27 lines in the first (LT) corner block, the `-1` of the `vtxColors` constructor has r0 in
  FE10 and r5 in ours. Declaration orders, const, `ix/iy` forms do not help; constructing `vtxColors` after the LT calls changes the frame.
- `fn_8028BC54` is game code (see Agent A).


## Round 10 (2026-11-12, single agent: the three register cases again, no new match)
Library range stays 3,273 of 3,277. Tried and ruled out (each function 5 to 6 new forms):
- `detail_GetFileAddress`: ss form (`if (const void* addr = ...)` declarations), `&&` chain with one `pAddr`, `self`/`fileId`
  copies, a static inline `HasMgr(this)` condition, an inline returning the manager address; flags `-inline deferred`,
  `-sym on`, `-O3,p`, `-func_align 16`, `--cc GC/3.0a5`. All keep the load after `mr r28,r3`. Analysis: unscheduled
  (`-schedule off`) ours is `lwz r3,0x18(r3)` (dest r3), the scheduler renames it to r0 but does not hoist it above the
  `stw` saves; with `-opt nopeephole` it moves above `mr r28,r3` but still stays below `stw r28`, i.e. our scheduler treats
  the prologue saves as aliasing the `this` load. SetupSoundImpl (`_savegpr`, no `stw` saves) hoists the same pattern.
- `detail_SetupSoundImpl`: `AllocSound` defined out of class in the .cpp (ss layout), Alloc with two-statement clamp, with
  if/else instead of `continue`, with a named `dropPriority`; outer `sum` local, ternary `ambientPriority`. No change: the
  first inline clamp result is always coalesced into the sum register (r16) in ours.
- nw4hbm `Window::DrawFrame`: `{WHITE,...}` initialiser, `const Size`/`const Size&` texSize, vtxColors after texCds, a named
  `f32` for the first LT coord (worse), vtxColors after the LT calls (frame grows to 0xE0). The register permutation of the LT
  block is (ours -> FE10) r5->r0 (-1), r6->r8 (ix), r0->r10, r8->r4, r4->r6, r9->r5, r10->r9.


## Round 11 (2026-11-13, single agent: public sources for the three register cases)
Library range 3,274 of 3,277. Fetched only the relevant files (no clones) to `build/lib_ext/r11/`.
- nw4hbm `Window::DrawFrame` (0x8035A148) matches: `yannicksuter/mscharged-decomp` (CC0, Mario Strikers Charged, GC/3.0a5.2,
  lyt_window.cpp marked `Matching` in its configure.py) writes the LT corner out by hand: `GetLTFrameSize`, then a block with
  `TextureFlipInfo& flipInfo = GetTexutreFlipInfo(TEXTUREFLIP_NONE); int iy = ...idx[FLIPINDEX_Y]; int ix = ...idx[FLIPINDEX_X];`
  `const u8 originX/originY = flipInfo.coords[VERTEXCOLOR_LT][ix/iy];` and two inline helpers `SetFrameTexOrigin`/`SetFrameTexExtent`
  (corner ^ 1/2/3 indexing), then `DrawQuad`; RT/RB/LB keep the macro. Installed in wii-ipl `lyt_hbm/lyt_window.cpp`.
- snd `detail_GetFileAddress`/`detail_SetupSoundImpl`: no public source has another form. Compared ogws, ss (and its copies in
  Whippy, kdc, krtdl, TheLastStory ss_nw4r), pokemon-rumble (revvmp, MIT), wiiplay, key, forecast, boom-street, wii-news-channel,
  Rhae, veryfat-dungeon and the nw4hbm snd copies (mscharged, oot-vc): GetFileAddress is either the ogws order (archive first) or
  the ss order (file manager, archive, `GetFileAddress`); FE10 is between them and our form is already that. SetupSoundImpl and
  `SoundInstanceManager::Alloc`/`ut::Clamp` are token-identical to ours in ss and pokemon-rumble. brawl, mkw, NSMBW-Decomp,
  nsmbw-project, marioparty9, pokepark, rhf have only headers for these.

## Permuter (tools/lib/lperm.py)
Local, token-free hill climber for lib sources. A template is a full copy of `lib/<key>` with markers: `/*P*/ ... /*E*/`
(units reordered; a unit is a line, unbalanced `(){}[]` continue it), `/*A*/ v1 /*|*/ v2 /*Z*/` (one alternative, nestable,
may contain `/*P*/`), `//LPERM-BEGIN ... //LPERM-END` with `--decls` (runs of declaration lines become `/*P*/` blocks).
Score = words of the function that differ from main.dol at its map address (relocs masked as in libcheck), +2 per word of
size difference; the compiler/flags come from lib/manifest.json (plus `-i` of the key's directory). Score 0 is confirmed with
libcheck.py (all references); only then it prints FOUND and stops (source in `build/lperm/<name>.found.cpp`). Best variant,
score and log: `build/lperm/<name>.best.cpp`, `.score`, `.log`; compiles in `build/tmp/lperm_*` (removed after each compile).
`--scan` compiles each single alternative once (check a template); `--worse P` (default 0.02) lets the walk step to best+1..2.
Templates (build/lperm/templates/, start scores = current diffs 8 / 10 / 25):
- `GetFileAddress.cpp`: file-manager block in 8 forms, body with hoisted declarations (`/*P*/`), peephole/opt-level pragmas.
- `SetupSoundImpl.cpp`: local copies `lp::Alloc`/`lp::AllocSound` (clamp forms, lock/declaration order, loop forms,
  comparison direction; `#define private public` around the includes for access only), switch `LP_ALLOCSOUND` between the
  member and the copy; outer priority/ambient/clamp forms and declaration orders. A hit in `lp::` needs the header changed.
- `DrawFrame.cpp` (key wii-ipl lyt_hbm): LT corner expanded with copies `GetLTFrameSizeDF`/`GetLTTexCoordDF` (ix/iy types,
  tSz forms, statement orders), DrawFrame declaration order, `const` vtxColors/texSize forms. DrawFrame4/8 keep the originals.
```
nice -n 10 python3 tools/lib/lperm.py build/lperm/templates/GetFileAddress.cpp ogws/src/nw4r/snd/snd_SoundArchivePlayer.cpp detail_GetFileAddress --jobs 3 --iters 200000
nice -n 10 python3 tools/lib/lperm.py build/lperm/templates/SetupSoundImpl.cpp ogws/src/nw4r/snd/snd_SoundArchivePlayer.cpp detail_SetupSoundImpl --jobs 3 --iters 200000
nice -n 10 python3 tools/lib/lperm.py build/lperm/templates/DrawFrame.cpp wii-ipl/libs/NW4R/src/lyt_hbm/lyt_window.cpp DrawFrame__Q36 --jobs 3 --iters 200000
```
About 0.2 s per compile with 3 jobs. Already compiled variants are cached (not recompiled); the run stops by itself with
"search space exhausted" when no new variant is found around the best one. Adopting a FOUND source: move the
change into `lib/<key>` (and headers), `python3 tools/lib/check_lib.py <key> -v`, then `check_lib.py --all` (must stay >= 3273).

## Placement round (2026-11-13, library side of the buildable tree)
Goal: more library sources that `tools/build/place.py` accepts as whole objects (docs/BUILD.md, docs/tu_libs.tsv).
Measured with a read-only driver (`build/tmp/buildlibs/drv.py --all`, same calls as `try_units.py --libs`, writes nothing
under docs/, config/ or src/tu/): **217 -> 238 sources place** with the current tools; with the tools/build proposals in
`build/tmp/buildlibs/proposals.md` 248-254 (about 273 if both data models of proposal P2 are tried).
`check_lib.py --all` stays at 3,274 of 3,277 functions, 804,732 bytes.

lib/map.json rebuilt (originals in build/tmp/buildlibs/orig/):
- Many tiny identical functions (NonCopyable/LinkList dtors, 4-8 byte getters and stubs, `blr`) were mapped to an
  identical copy in another object. Such an address then had several names, the rename pass (gen_config.lib_renames)
  skipped it, and placement failed ("references X, which the link knows as fn_...", "breaks contiguity").
- New entries come from contiguous chains: every source is compiled and the longest run of its functions that lies
  back to back in main.dol (object order, DOL-adjacent, identical bytes with relocations masked) gives their
  addresses; an entry whose address another source's chain owns under another name is dropped (highest coverage
  wins); ties keep the old address. A few entries are pinned (two identical copies in the DOL: nw4hbm vs nw4r
  LinkList, `__sinit`s, PSMTXRotRad, AXGetAuxACallback; HBMAnmController's dtor at 0x80345750 is
  `GroupAnmController::~GroupAnmController`, not `FrameController`'s). Scripts: build/tmp/buildlibs/chains.py,
  newmap.py (+ pins.json), postfix.py (+ fixes.json). lib/map.json is the source of truth again after that.
- Not FE10 code (their single "verified" functions were coincidences inside other objects; function lists emptied):
  ogws VF pf_errnum.c (0x80320954 is OSThread's SleepAlarmHandler), pf_fat.c, pdm_dskmng.c, egg eggDvdFile.cpp,
  eggAudioArcPlayerMgr.cpp, wii-ipl EGG eggHeap.cpp (0x802FAB20 is DVDSetAutoInvalidation), ogws nw4r
  math_triangular.cpp (HBM range). False map symbols removed: VFiPFVOL_errnum, VFiPFAPI_convertError, fake_function.
- ogws AXAlloc.c: the function at 0x802BDD64 is `__AXAllocInit` (called by AXInit; `__AXInitVoiceStacks` is inlined).
- petari dvdFatal.c `__DVDPrintFatalMessage` is 0x802FBDFC (0x8034C25C is no function start).

Source fixes (each verified with check_lib.py; FE10 functions the reference source lacked):
- ogws AI/ai.c: `AIGetDMAStartAddr` (0x802BCE44). Places.
- ogws DVD/dvd.c: `DVDSetAutoInvalidation` (0x802FAB20), `DVDCheckDiskAsync` (0x802FB1C4, petari body),
  `CancelAllSyncComplete` declared right after `NumInternalRetry` (.sbss order). Places with proposal P2.
- wiiplay VI/vi.c: `VIGetNextField`, `VIGetVSyncTimingTest`, `VISetVSyncTimingTest` (wii-ipl bodies), `__VIResetSIIdle`
  (0x80331784). Places with P2b.
- ogws NAND/NANDCore.c: static `nandChangeDir` (0x803157C8, wii-ipl body) before `NANDChangeDir`; `nandIsPrivatePath`
  in the if/else form (that shape is what FE10 inlines). Places with P2b.
- wiiplay AXFX/AXFXReverbHiExp.c: `AXFXReverbHiExpSettingsUpdate` (0x802C1160, wii-ipl body). Places with P2b.

Newly placing with the current tools (23): HBMRemoteSpk.cpp, lyt_group.cpp, snd_BasicPlayer.cpp,
snd_ExternalSoundPlayer.cpp, snd_SeqTrack.cpp, snd_Sound3DListener.cpp, snd_StrmFile.cpp, snd_TaskThread.cpp,
snd_VoiceManager.cpp, AI/ai.c, AX/AX.c, NdevExi2AD/DebuggerDriver.c, OS/OSIdle.c, WUD/WUDHidHost.c (ogws);
EXI2_GDEV_GCN/main.c, bte bta_dm_api.c, bta_hh_api.c, bte_main.c, gki_ppc.c, gki_time.c, ptim.c, gx/GXFifo.c,
os/OSReboot.c (petari). No longer placing: ogws nw4r ef_handle.cpp and VF pf_fat.c (false matches; snd_StrmFile.cpp
covers the address now).

Still open, by cause:
- MSL extab (11 sources): the FE10 objects have exception tables. `-Cpp_exceptions on` does not make MWCC emit them for
  C, and `-lang c++` breaks names/compiles (tried, reverted); needs the MSL C files compiled as C++ with extern "C"
  headers.
- Data kept by the original link though unreferenced (proposal P2), local-name clashes (P4), label aliases (P3).
- Source differences per object (missing or extra functions, other order, older/newer versions): nw4hbm lyt
  (Pane/TextBox/Window/Material/CharWriter), snd AxVoice/Voice/StrmPlayer/SeqPlayer/BasicSound/WsdPlayer, OSThread,
  WUD.c/WPAD.c, KPAD (.sdata2 order), BTE .data string order. Tools for this: build/tmp/buildlibs/diag.py (object
  functions vs DOL), gaps2.py (DOL functions inside a source's run that it lacks, and who verifies them),
  datadiag.py (data symbol -> DOL address implied by the code), votes.py (place.py base votes per section).

## Library placement round (2026-11-16, thread "Bibliotheksfunktionen platzieren")
Goal: library sources that are verified per function but did not link as whole objects. See `docs/LIBPLACE.md` (workflow),
`docs/libplace/*.md` (per-group notes of the three agent runs: snd, HBM/lyt/ut, SDK C) and `docs/libplace/*_todo.tsv`.
- Fast probe `tools/build/libdrv.py [--all] [-v] <key>` (4 s/source, 1-2 min for all), `libobj.py`, `shiftdiag.py` (after a failed link:
  where symbols moved), `dropunit.py` (remove units from units.json without re-running gen_units, then gen_config/configure/ninja).
- `tools/build/dropfn.py`: weak functions/data whose single DOL copy is in another object are cut out of the compiled object
  (units.json `drop_functions`, ninja rule `mwcc_drop`). Confirmed by a real link: MWLD keeps the FIRST definition in link order, so
  without the cut the object's copy wins and everything shifts.
- Real link results: every batch is only trusted after `main.dol: OK`. Known link blockers found this way and removed from link_select:
  synctrl.c (`__SYNn128` defined twice), AXFXChorusExp.c (`__AXFXGetLfoSinTable` undefined), lyt_picture.cpp (`Material::GetTexCoordGenAry`),
  ut_IOStream/DvdLockedFileStream/FileStream/snd_DvdSoundArchive (`IOStream::Write` undefined), DVD/dvd.c (shifts text/rodata),
  mem_heapCommon/mem_list (MEMInitList), GXInit (needs GXTransform), serpoll.c (`gTRKInputPendingPtr` twice), OSPlayRecord.c (.bss +0x180).
  The `pad_end` relaxation to 16/32-byte padding (agent SDK round) put padding into .text ranges and shifted code: reverted.

### Round 2 (same day)
Real link confirmed (main.dol OK) for the second batch. Link-blocked / dropped again after the real link: serpoll.c (`gTRKInputPendingPtr` defined twice),
OSPlayRecord.c (.bss +0x180), dvd.c (text -0x23c, rodata/data -0x240), OS.c (dtk split: "relocation already exists at 0x803177C0"),
OSExec.c (extab/data shifts), lyt_picture (needs lyt_material, which is skipped), lyt_textBox (needs ut_TextWriterBase). Model-ok but not linked:
those plus petari OSThread.c (overlaps OSIdle.c). `tools/build/dropunit.py` + `iter` loop (gen_config, configure, ninja relink, shiftdiag) bisects a failing batch in ~4 min per step
once units.json holds the full set.
