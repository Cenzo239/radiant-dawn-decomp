# Group A (nw4r snd): notes

## Tooling and config changes needed by the integrator (not in lib/ or docs/)
- `tools/build/dolmodel.py`: `.fn "name<...,...>"` entries (quoted names of templates) were parsed with the quotes,
  so no reference to or from template/ctor names was found and many functions came out "referenced nowhere"
  (dead-strip errors). Quotes are now stripped and comma/space tokens inside quotes are kept together.
- `tools/build/place.py`: `__sinit_*` is never reported as "referenced nowhere" (the unlabelled `.ctors` entry
  in the dtk asm is not a labelled symbol, so the reference was never counted).
- `config/RFEE01/symbols.base.txt` / `symbols.txt`: edits listed in `docs/libplace/a-snd_symbols.tsv`
  (apply with `python3 -I docs/libplace/apply_symbol_edits.py`, idempotent): trailing `blr` symbols that dtk split
  off are merged back; symbols named after the wrong class are renamed. Re-run dtk split (build/RFEE01/asm) after it.
- Note: `build/RFEE01/asm` must exist for dead-strip checks (`dtk dol split config/RFEE01/config.yml build/RFEE01`
  regenerates it without touching config).
- `remap.py` can swap same-sized functions (sinit vs DetachPlayerHeap, both 0xC): do not commit its map output
  without looking at the diff.

- `tools/build/place.py` (own-function sequence): the longest increasing run of DOL addresses is now computed over
  non-weak functions only; weak copies join it only when their DOL address lies between their neighbours.
  Before, a weak copy (LinkListNode dtor, DOL copy in another object) could tie with the real first function
  (ctor) and make the model drop the ctor instead of the weak copy.
- `tools/build/gen_units.py` (lib_unit): map entries for `@unnamed@<file>@NonCopyable` dtors are ignored.
  remap.py matched Voice/StrmPlayer/StrmSound's local copy (dead-stripped in the DOL) to the TaskManager one at
  0x802B67E4, which made the unit look as if it started after that address.
- Full patch of tools/ and config/ edits: docs/libplace/a-snd_tools.patch (git apply it in the integrator tree).

## Placed
- snd_BasicSound.cpp: (1) Attach*/Detach*/GetVoiceOutCount sit between Shutdown and SetPlayerPriority in the DOL:
  moved there; (2) SetAutoStopCounter, Set/Get OutputLine, Set/Get MainOutVolume, SetRemoteOutVolume, GetInitialVolume,
  GetPitch, GetPan, GetSurroundPan, GetRemoteOutVolume, SetAmbientParamCallback were inlined in the original (no
  symbol): bodies moved into the class in snd_BasicSound.h; (3) GetAmbientPriority ends with a tail call plus a
  `blr` that dtk split off as fn_802A3220: merged in symbols; (4) 0x802A329C/0x802A32DC were named after IOStream:
  renamed to BasicSound dtor / GetRuntimeTypeInfo.

## Given up
- snd_TaskManager.cpp, snd_SoundSystem.cpp, snd_BankFile.cpp: no source change; they were rejected as "referenced
  nowhere in the DOL" only because dolmodel.py could not read quoted template names / the .ctors table (see tooling above).

## Placed by the tooling fixes only (no source change)
- snd_Voice.cpp (47 fns): weak DisposeCallback dtor/vtable and the TU-local NonCopyable dtor are dead-stripped
  by MWLD (nothing references them), CalcAxSrc/Lpf/RemoteFilter, SyncAxVoice, RunAllAxVoice, StopAllAxVoice are
  inlined (unreferenced) and stripped too; the placement model failed on the NonCopyable map entry (see above).
- snd_SoundPlayer.cpp (19), snd_StrmSound.cpp (16), snd_SeqSoundHandle.cpp (3): same two causes (weak LinkListNode
  dtor tie in the sequence model; bogus NonCopyable map address).
- snd_AxVoiceManager.cpp (9): the AxVoice dtor at 0x8029DAA4 was unnamed (fn_8029DAA4): renamed (a-snd_symbols.tsv).
- snd_AxVoice.cpp (35): IsMixChanged precedes SetAdpcmLoop in the DOL: moved SetAdpcmLoop after it (GetDspAddressBySample,
  Get*DspAddress and the AxVoiceParamBlock helpers are inlined/unreferenced and stripped by the model).
- snd_EnvGenerator.cpp (10): SetHold sits between SetAttack and SetDecay: moved; the VOLUME_INIT static const (0x804D11C0)
  was only a lbl_ in symbols: renamed.
- snd_Channel.cpp (17): no source change; its reference to EnvGenerator::VOLUME_INIT needed the rename above.
- snd_SoundThread.cpp (9): no source change. Its leading weak LinkListNode dtor (DOL copy at 0x802AF158, other object)
  was taken as "own" because it was only compared with the next function's address; the sequence model now requires a
  weak copy at the start/end of the object to touch its neighbour (place.py).
- snd_Sound3DManager.cpp (10): no source change; tooling: dolmodel.py's operand regexp could not parse names that start
  with `@` (this-adjust thunks `@4@detail_FreeAmbientArg`), so the thunk looked unreferenced.
- snd_Sound3DActor.cpp (6): no source change (thunk-name parsing, see Sound3DManager).
- snd_WaveSoundHandle.cpp (2): no source change; typeInfo__WaveSound (0x804CC228) was only a lbl_ (renamed).
- Known: check_lib reports `__dt__Sound3DManager` (weak, 0x8025EEF0) as size 0x60 vs 0x58; pre-existing, not part of this object.
- snd_FxChorus.cpp (9), snd_FxReverbHi.cpp (8): no source change. Symbols: 0x802A5F24 is FxBase::OnChangeOutputMode (empty
  virtual, FxChorus vtable slot 6), the FxChorus/FxReverbHi vtables (lbl_80393CB0/CD8) and their weak virtual dtors in the
  game range (fn_8025F31C/2A0) get their names, 0x802C1E50 is AXFXChorusExpGetMemSize. lib/map.json: removed the
  FxBase::UpdateBuffer/Shutdown entries of FxChorus/FxReverbHi (remap had matched them to other objects' 4-byte stubs).
- snd_MmlSeqTrackAllocator.cpp (4): the 8-byte function at 0x802A7DE8 (`addi r3,r3,8; b CountImpl`) is
  GetAllocatableTrackCount (vtable slot), remap had called it Destroy; Destroy itself is not in the DOL (unreferenced, stripped).
  Map entry and symbol fixed.
- snd_SoundActor.cpp (6): no source change; `SoundArchivePlayer::detail_SetupSoundImpl` (0x802B00C4, map status "diff",
  so never renamed) now has its name in symbols.
- snd_RemoteSpeaker.cpp (9): dtk saw Update + ExecCommand as one 0xD4 function (Update falls through into the inlined-adjacent
  ExecCommand without a blr): symbol split into Update 0x34 + ExecCommand 0xA0 (a-snd_symbols.tsv `split`).
- snd_WaveSound.cpp (15): the 0x40 weak dtor at 0x802BA950 was mapped as BasicSound's dtor. BasicSound/WsdPlayer/NonCopyable dtors
  compile to the same bytes (no vtable store), so remap's shape matching is ambiguous; it is WsdPlayer's dtor (first user in
  link order). Renamed in symbols, map entry fixed. (0x802A329C is BasicSound's own.)
- snd_WsdPlayer.cpp (14): no source change; the empty PlayerCallback::OnUpdateVoiceSoundThread (0x802A6D18) had no name.
- snd_SeqPlayer.cpp (26 of 36 uncovered): SeqPlayer's weak virtuals and this-adjust thunks are split between the first object that
  emitted them (0x802A6D00..6D54) and SeqPlayer's own range. Several were unnamed or named after other classes (dtk/remap by shape):
  fixed in symbols (0x802A6D14 InvalidateWaveData, 0x802A6D18 PlayerCallback::OnUpdateVoiceSoundThread, 0x802A6D34/6D44 thunks,
  0x802A9DFC ChannelCallback, 0x802A9E00/9E08 `@208@/@220@__dt`) and map.json. Tooling: (a) `@N@name` thunks were never treated as
  named DOL functions (in_dol rejected every name starting with `@`), (b) the strip model attached the relocation of a dropped
  function to the next kept function (`new_off` accepted the span end for relocations), which turned a dropped `b Update` stub into
  a wrong reference on ChannelCallback; (c) weak copies at the end of an object now chain by adjacency.
- snd_Task.cpp (1): `Task::~Task` is at 0x802B67E4 (map had matched it to another dtor of the same shape); the Task vtable is
  unreferenced in the DOL (dead-stripped), which needs the strip retry on `.data: ... no references from code` (gen_units.py).
- snd_SeqSound.cpp (26): ReadVariable/ReadGlobalVariable come before WriteVariable/WriteGlobalVariable in the DOL: reordered. The
  two 8-byte functions at 0x802AA2CC/2D4 are SetChannelPriority/SetReleasePriorityFix (SeqSound::SetTempoRatio is not in the DOL,
  unreferenced): remap had shifted the names by one.

## Given up
- snd_StrmPlayer.cpp (47 fns): everything places (weak dtors, StrmDataLoadTask/Task dtor names fixed, thunks) except
  `.sdata2: cannot derive a single base`. The DOL literal pool of the StrmPlayer range is [double 2^52+2^31, double 2^52, 1.0f, 127.0f, 63.0f]
  preceded by 0.0f at 0x804D1360, while MWCC emits floats first in first-use order ([1.0f, 0.0f, 127.0f, 63.0f, double 2^52, double 2^52+2^31]).
  Needs the literals' first-use order changed across InitParam/SetupPlayer/UpdateVoiceParams or a pooled-literal trick; not found in the time box.
- snd_DvdSoundArchive.cpp (27 fns): everything places except `reference to Write__ut::IOStream`: the DvdFileStream vtable slot 0x1C
  points at the 8-byte stub 0x802BC430 (named ReadAsync__IOStream, `li r3,0; blr`) in the DOL, i.e. FE10's IOStream has no void
  `Write` default there; the ogws header (lib/ogws/include/nw4r/ut/ut_IOStream.h) has Write at 0x1C. Needs the ut IOStream vtable
  reconstructed (ut group, affects ut_IOStream.cpp which fails for the same reason: `Write` not in symbols).
- snd_AxManager.cpp, wii-ipl/.../snd_AxManager.cpp: ogws version: `references AXGetAuxACallback, which the link knows as fn_802BE938`
  (rename-map inconsistency: ogws AXAux.c maps it at 0x802BE938, wii-ipl AXAux.c at 0x8031E070 so the name is not renamed in symbols.txt
  by lib_renames; integrator/SDK group). The LinkList<FxBase,4> dtor naming (0x8029C780) is fixed. wii-ipl version: ctor size 0x530 vs 0x4A0 (codegen), not tried.
- wii-ipl/.../snd_SoundArchivePlayer.cpp: `__ct__SoundArchivePlayer size 0x14C vs 0x12C` (codegen of the wii-ipl variant), not tried (ogws version already places).
