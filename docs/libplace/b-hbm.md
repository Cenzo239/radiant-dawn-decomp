# libplace group B (HBM / nw4hbm / homebutton) notes

Baseline of `libdrv.py --all -j 1` at start: ok 164 (the 276 of the hand-over counts already linked sources too).

## Tooling changes (docs/libplace/b-tools.patch, applied in this worktree but not committed: tools/ is outside the allowed paths)
- `tools/build/place.py` strip_object: the own-function selection is now the heaviest increasing run of DOL
  addresses (global definition weighs 2, weak copy 1) instead of the longest one. On ties the weak copy
  (e.g. `Color::~Color`, whose DOL copy is elsewhere) was kept and the real first function was classed as foreign.
- `place.py`/`gen_units.py`: a `force_active` function that the DOL does not have is treated as dead-stripped
  by the original and is cut out of the object with dropfn (units.json `drop_functions`), so a source may
  carry `#pragma force_active on` for functions the DOL keeps although nothing references them, without
  keeping the dead-stripped dtors the DOL lacks.
- Effect on `libdrv.py --all -j 1`: ok 164 -> 166 (CharWriter + wii-ipl runtime.c), no source dropped.

## Placed
- ut_hbm/ut_CharWriter.cpp (+27 functions): out-of-line copies of functions the original inlined
  (ResetColorMapping, SetScale, SetCursor(3), LoadTexture, SetupGX*, SetupGXCommon) were emitted; made them
  `inline`/`static inline` (bytes unchanged, check_lib MATCH). The DOL keeps ctor/SetFont/... although nothing
  references them: file-wide `#pragma force_active on`; explicit `~CharWriter` removed (the DOL lacks it).

- lyt_hbm/lyt_pane.cpp (+28 functions): DOL's dtk symbols split the trailing `blr` of the switch-style
  Get/SetColorElement off as `fn_` stubs (object function 0x28 = DOL 0x24 + 4): place.py now accepts a function
  whose DOL symbol plus following tiny unnamed fn_ symbols tile its size. Weak vtable/RTTI copies (PaneBase,
  Pane RTTI) lie in lyt_bounding's data: place.py votes (weak_else) + strip_object(extra_else) + dropfn data
  support. `__sinit` is referenced by .ctors only: dead-strip check now honours .ctors entries.
  map.json: `typeInfo__Q36nw4hbm3lyt4Pane` had a bogus address (0x1f9fb8 -> 0x804C9FB8); GetVtxColor/SetVtxColor
  entries pointed to a stub.

## Tooling (cumulative, see b-tools.patch)
- Prerequisite: `build/RFEE01/asm` must exist (`build/tools/dtk dol split config/RFEE01/config.yml build/RFEE01`);
  without it every "referenced nowhere" check fails (276 baseline ok needs it).
- weak data elsewhere (vote based), unnamed weak function matched by bytes, ext. references resolved to
  unnamed DOL labels and renamed (units `renames`), ctor-only references, 4th keep_data mode (no .data).

## Placed by the tooling alone (no source edit; need b-tools.patch)
ogws homebuttonMiniLib/HBMAnmController.cpp (3), ogws nw4r ut/ut_DvdLockedFileStream.cpp (6), ut_Font.cpp (1),
ut_IOStream.cpp (3), wii-ipl lyt_hbm/lyt_group.cpp (6), xeno hbm/HBMController.cpp (24). Cause: references to
functions that only exist as `fn_` in the base symbols (renamed by the unit), weak copies, ctors-only sinit.
libdrv --all -j 1 with the patch: ok 306 (276 before; mem_list.c turned `duplicate` because the wiiplay twin places),
no ok source lost; check_lib --all 3274/3277.

## Round 2 (tooling + map.json, no source edits)
Placed: lyt_hbm/lyt_window.cpp (21), lyt_picture.cpp (11), lyt_bounding.cpp (6), plus (by the same tooling) ut_hbm/ut_ResFont.cpp,
lyt_common.cpp, ut_LinkList.cpp, math_triangular.cpp. Causes/fixes:
- map.json `symbols`: `typeInfo__Q36nw4hbm3lyt{Picture,TextBox,Window,Bounding}` added (symbols.txt names them nw4r).
- place.py: global/weak data the DOL only has as unnamed `lbl_` at its placed address is adopted (unit renames the label).
- place.py: a DOL function larger than ours (dtk symbol swallowed the next, unnamed function, e.g. TextBox GetVtxColor 0x34 =
  0x8 + GetTextColor 0x2c) is accepted and the swallowed neighbour is kept by byte comparison.
Final `libdrv --all -j 1`: ok 317 (276 at start), no ok source lost (mem_list.c became `duplicate` of its wiiplay twin),
`check_lib --all` 3274/3277.

## Given up / open (cause)
- lyt_textBox.cpp: weak TextBox RTTI/strings placed in another data order than the DOL (.data of TU not contiguous; needs the
  weak-data model to follow link order), plus force_active for unreferenced inline copies.
- lyt_material.cpp: .rodata literal pool base conflict (0x80378620 vs 0x80378628).
- HBMGUIManager.cpp / HBMBase.cpp / HBMSound.cpp: RTTI of Interface lies inside the unit's DOL data range (weak-data model drops it);
  HBMBase.cpp function order (create at 0x80348F74); HBMSound literal pool.
- ut_ResFontBase/ut_TextWriterBase/ut_TagProcessorBase/DvdFileStream/lyt_layout/lyt_animation/lyt_arcResourceAccessor/
  lyt_drawinfo/ogws nw4r lyt+ut copies: not reached (time); first errors in docs/libplace/b-hbm_todo.tsv.
