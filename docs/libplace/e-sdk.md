# libplace e-sdk (lib-place-c2): round 2 of the RVL_SDK / MetroTRK / MSL C sources

Sources are public CC0/decomp code (ogws, wii-ipl, Petari, xd-decomp); license files and headers unchanged.
Fast loop and rules: docs/LIBPLACE.md. Work list: docs/libplace/e-sdk_todo.tsv.

## Placed

| source | fns | cause | fix |
|---|---|---|---|
| ogws NWC24/NWC24Ipc.c | 1 | `.sbss: base not aligned to 8` | tool rule 1 (below) |
| ogws OS/OSContext.c | 15 | `__RAS_OSDisableInterrupts_begin/_end` not names in symbols.txt | source uses `OSDisableInterrupts` for the begin label (same address as the function) and a new label `__RAS_OSDisableInterrupts_end = .text:0x8031CA94` (type:label) in config/RFEE01/symbols.base.txt + symbols.txt |
| petari MetroTRK dolphin_trk.c | 6 | InitMetroTRK is 0x98 in the object, symbols.txt says 0x94 (unreachable `blr` after `b TRK_main`) | tool rule 2 (below), the size fix is written into symbols.txt by gen_config (`Placement.size_fixes`) |
| petari os/OSThread.c | 25 | FE10's range also holds `OSSetIdleFunction` (0x98, ogws OSIdle.c body) between OSWakeupThread and SleepAlarmHandler, plus `static OSThread IdleThread` in .bss after IdleContext; `_stack_addr/_stack_end` linker-script symbols | added the function + static, tool rule 3 (ABS symbols); map.json entries via remap.py (false `diff` entries for dead functions removed) |
| ogws OS/OS.c | 20 | `__OSGetHollywoodRev` and the `DECOMP_FORCEACTIVE` helper were emitted though the DOL range has neither; `__OSDBIntegrator/__OSDBJump/OSExceptionVector` are copied by address (nothing references them); `ShutdownFunctionInfo` exists twice in symbols.txt so the model lost the one at 0x803A1AA0 and could not pad the .data end | `static inline` Hollywood rev, FORCEACTIVE removed, `#pragma force_active on/reset` around the three asm stubs, tool rule 4 (dolmodel keeps duplicate-named locals) |
| ogws OS/OSExec.c | 12 | FE10's range holds Run/Callback (Petari), the older ogws launch code, and `__OSBootDolSimple/__OSBootDol` (Petari) | merged into one file: Run/Callback/PackArgs before `__OSGetExecParams`, ReadDisc/GetApploaderPosition/LoadApploader/LoadDol/StartDol/BootDol after `__OSRelaunchTitle`; local `ExecParams` struct with petari's field names (ogws names them WORD_0x0..), `OSRoundUp32B` macro (the DOL inlines it), `#include <stdio.h>` (sprintf needs the vararg `crxor`), interrupt masks 0xFFFFFFF0 / 0x10 as literals, sbss declaration order Prepared, gameToc, partInfo, bootGameInfo, tmd, __OSInReboot, DVDLowIntType (MWCC lays tentative/static sbss out in reverse) |
| ogws WPAD/WPAD.c | 63 | the object's `WPADIsDpdEnabled` was really `WPADGetRadioSensitivity` (reads the u8 at 0x983, at 0x80335A9C); the real `WPADIsDpdEnabled` (0x80339628, reads wpInfo.dpd) was missing; remap.py mapped three identical 4-byte functions wrongly; `WPADiRetrieveChannel` register allocation | added `WPADGetRadioSensitivity`, restored `WPADIsDpdEnabled` body, map entries of the 5 `blr` stubs restored, `WPADiRetrieveChannel` written in wii-ipl's form (`s32 i`, `_scArray.regist[WUD_MAX_DEV_ENTRY_FOR_STD + i]`, no `(s16)` cast) which gives the DOL register choice. KPAD now sees the real WPADIsDpdEnabled |
| wii-ipl mtx/mtx.c | 19 | FE10's range also has `__PSMTXRotAxisRadInternal`, `PSMTXRotAxisRad`, `PSMTXQuat`, `C_MTXLightPerspective/Ortho` (petari bodies appended in DOL order); .sdata2 order was 1,0,.5,3,deg,-1,2 instead of 1,0,.5,3,2,-1,deg | a dead (never referenced) global `__mtx_pool_order` before `PSMTXQuat` (`a = x*2.0f; return a*-1.0f;`) makes MWCC pool 2.0 and -1.0 before the degree constant; MWLD strips it |

Duplicate effect: petari OSThread.c now also covers 0x803208BC (OSIdle.c, ogws) and ogws OSThread/petari OSExec/petari mtx.c are alternatives of
placed sources (the placement model reports them as duplicates); the integrator picks one.

## Tool rules changed (tools/build)

1. `place.py` alignment check: MWCC writes `sh_addralign` 8 for every `.sbss` object (even a single `int`), yet the DOL packs one object's
   sbss at a 4-aligned address (the original objects were compiled the same way). `.sbss` with align 8 and a 4-aligned base now passes.
   Newly placing because of it (see the --all comparison below): NWC24Ipc.c (others only if listed there).
2. `place.py` function size: a DOL symbol that is 4/8/... bytes shorter than the object's function when the extra bytes are raw `blr`
   words not covered by any symbol (trailing unreachable `blr`) is accepted; the symbol is grown through `size_fixes`.
3. `place.py` `LD_ABS`: absolute linker-script symbols (`_stack_end`, `_stack_addr`, `_db_stack_addr`, `_db_stack_end`, `__ArenaLo`,
   `__ArenaHi`, values computed from the ldscript) count as known targets of references. (The real link has them in ldscript.lcf.)
4. `dolmodel.load_symbols`: a name that occurs at two addresses in symbols.txt keeps the later one under the plain name and the earlier under
   `Name_<ADDR>` (what dtk calls them in the asm). Before, the earlier one was missing from the model (`ShutdownFunctionInfo` 0x803A1AA0).

5. `gen_units.lib_unit`: the dead-strip retry also starts when `.sdata2/.rodata/.sdata` differ from the DOL by words (a pool constant that only dead code used,
   e.g. an unused `GXColor fg = {255,255,255,0}` in an inlined helper; MWLD strips such unreferenced `@N` constants). In the `libdrv --all` before/after
   comparison only ogws OS/OSExec.c starts placing because of it.

`libdrv --all -j 1` before/after: 341 -> 348 ok. New: NWC24Ipc, OS.c, OSContext, OSExec, WPAD.c (ogws), dolphin_trk, mtx.c (wii-ipl) (+ petari OSThread.c, which the
model reports as `duplicate` because ogws OSIdle.c is already placed at 0x803208BC: link-test it with OSIdle.c removed from link_select; it covers
OSIdle's range). ogws vi.c changed from shared-data to codegen (the .sbss waiver moved the first error). Nothing that placed before stopped placing.

Link notes for the integrator: OSContext needs the new label in symbols.txt (done in config/RFEE01/symbols.base.txt and symbols.txt; gen_config regenerates symbols.txt from the base);
OSExec dropped `FORCE_BSS_ALIGN` (the dead-strip model removes it anyway); KPAD (placing since round 1) now has a real `WPADIsDpdEnabled` in ogws WPAD.c.

## Given up (cause)

- xd syn/synenv.c: .sdata2 order. DOL: conv-double (0x43300000 80000000), 2.0, 78643200f, 1000.0f, 78642000f; ours 1000.0, 2.0, 78643200,
  78642000, conv. Swapping the operands of `1000.0f * pow()` does not change the pool, the conv constant is created at code generation
  and always comes last here; no source form found in ~10 min.
- ogws OS/OSNet.c: the DOL .data keeps the function-name strings passed as the `user` argument of inline helpers ("NWC24iPrepareShutdown"
  ...); MWCC drops a string literal whose only use is an unused inline parameter. `(void)user`, `if (user) {}`, `const char* u = user;`
  do not keep it; `if (user == NULL) return -1;` keeps it but adds code. Needs the original usage (a debug trace in the inline helper).
- Not touched (alternatives of already placed sources; the list only shows them because the model reports the overlapping one):
  petari OSCache.c, arc.c, GXTexture.c, vi3in1.c; wii-ipl WPAD.c (ogws WPAD.c covers the range; its function sizes differ).
- Not attempted (no time): the MSL extab group (strtok/strcmp/ansi_fp/printf/mbstring/alloc/buffer_io/math_api/strtoul/scanf: MSL C needs
  exception tables, see docs/LIB.md), wii-ipl MetroTRK targsupp/mslsupp, bte, GX, VI, AX, DVD 'codegen' sources.
