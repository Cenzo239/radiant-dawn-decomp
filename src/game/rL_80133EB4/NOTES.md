# Region rL_80133EB4 (0x80133EB4..0x8014C9C8)

265 of 288 functions match, 0x12D1C of 0x18B14 bytes (76.1%). Each file below prints `MATCH` with
`python3 -I tools/check_func.py <file> -v`. Near misses are in `wip/near4.cpp` (newest), `wip/near3.cpp`, `wip/near2.cpp` and `wip/near.cpp`
(older, and some entries in both are now solved). Neither is compiled and their externs aren't complete.

Shared headers: `types.h` (basic types, `Vec`), `map3d.h` (`Mesh`, `MapGroup`, `MapModel`, `Pad`, `MeshAt`) and `talk.h` (`Talk`, `PT`, `Empty`, talk externs).

| File | Matches | Contents |
|---|---|---|
| `fn_8013B9EC.cpp` | 2 | Map per-frame update (`fn_80135554`) and its global wrapper, which inlines it |
| `fn_801368DC.cpp` | 7 | Fog from globals, map environment step (`fn_8013A638`), minimap render, shadow draw, file open, roof percent, tile refresh |
| `fn_80138E6C.cpp` | 1 | `MapModel` reset |
| `fn_8013A8D8.cpp` | 4 | Environment sounds, roof fade colours (`fn_8013B2B8`), mesh refresh, camera quake |
| `fn_8013CCA4.cpp` | 6 | Rolling stone (start, step, draw, stop) and door open start |
| `fn_8013E34C.cpp` | 3 | Fire on and off at a tile, overlay GX setup |
| `fn_8013F238.cpp` | 5 | Unit path buffer: add step, cost, route rebuild (`fn_8013FCE8`), and GX setup |
| `fn_80143D88.cpp` | 1 | Binds map render callbacks to mesh groups by material name |
| `fn_80146BAC.cpp` | 6 | Weather switch (`fn_80146BAC`), snow setup, rain update, water and wave GX |
| `fn_801476E8.cpp` | 5 | Shadow texture blending and GX, phase banner start, unit fade |
| `fn_80148B90.cpp` | 9 | Talk teardown, script setup and token commands, active speaker |
| `fn_8014C2AC.cpp` | 2 | Talk close and restart |
| `fn_801369BC.cpp` | 1 | `.mapshader` loader |
| `fn_801364AC.cpp` | 1 | Map lights from the render settings |
| `fn_8013B74C.cpp` | 2 | Roof opening percent (`fn_8013B74C`), rain texture and offset table setup (`fn_801436EC`) |
| `fn_8013B8D0.cpp` | 2 | Weather refresh wrapper, door virtual call |
| `fn_8013F3D8.cpp` | 1 | Draws marked tiles over the terrain |
| `fn_801402B8.cpp` | 1 | Draws the unit path |
| `fn_80140954.cpp` | 2 | Place markers at unit tiles, reflection matrix |
| `fn_80140E68.cpp` | 1 | Water reflection render pass |
| `fn_80141DCC.cpp` | 2 | Top-down light projection setups for the shadow texture |
| `fn_80144CD0.cpp` | 1 | Weather particle point sprites |
| `fn_8014531C.cpp` | 1 | Weather particle setup per type |
| `fn_80146A4C.cpp` | 1 | Weather process create |
| `fn_8014B4B4.cpp` | 3 | Talk: reply wait mode, next page, fade-out process |
| `fn_8014B650.cpp` | 1 | Talk per-frame text step used when skipping |
| `fn_small.cpp` | 75 | Leaf functions and one-line wrappers from the whole region. They aren't in address order with the other files |
| `fn_80133EB4.cpp` | 10 | Quadtree over meshes (reset, Z bounds, split, cull), name table for map modes, save/load of render settings |
| `fn_80135554.cpp` | 7 | Mesh and group picking |
| `fn_8013608C.cpp` | 5 | `.mapinst`, `.mapdata`, `.maplight` and `.mapfog` loaders; relink after map changes |
| `fn_80138000.cpp` | 3 | Tile test, map render flags switch (`fn_8013A35C`), map teardown (`fn_8013A054`) |
| `fn_801386AC.cpp` | 11 | Minimap render target, global model create and free, positional sound helpers |
| `fn_8013C094.cpp` | 23 | Map events: quake, doors, pitfall, breakable blocks, treasure effect, fade processes |
| `fn_8013F13C.cpp` | 4 | Fade step, path to direction bytes (`fn_8014021C`), marking effects |
| `fn_8014348C.cpp` | 7 | GX setup for screen effects, screen capture textures, weather overlay start |
| `fn_801435E4.cpp` | 20 | Process callbacks: weather, phase banner, capture fade |
| `fn_80148634.cpp` | 14 | Talk system: skip input, script tokenizer, actor lookup, start (`fn_8014BC80`) and restart (`fn_8014C148`) |
| `fn_80149434.cpp` | 1 | Talk script control-code interpreter (four jump tables) |
| `fn_8014A6CC.cpp` | 1 | Talk: opens a text box slot, measures the widest script line |
| `fn_8013826C.cpp` | 1 | Quadtree rebuild |
| `fn_80146554.cpp` | 1 | Weather particles: scatter, then queue the draw callback |
| `fn_8013EA08.cpp` | 1 | One coloured map tile (quad or fan) |
| `fn_80138A78.cpp` | 1 | Minimap start |
| `fn_801384E4.cpp` | 2 | Minimap camera setup, map view rectangle scroll (`fn_8013531C`) |
| `fn_801445E8.cpp` | 1 | Cloud shadow layer draw |
| `fn_8013AF10.cpp` | 2 | Environment audio parameters (`fn_8013AE18`), map matrix setup |
| `fn_80143374.cpp` | 1 | Scroll offset for the map view |
| `fn_8013C4A4.cpp` | 1 | Door falling apart |
| `fn_80144938.cpp` | 1 | Cloud layer scroll step |
| `fn_8013AC48.cpp` | 1 | Round 16: environment sound parameters for the map |

## Subsystems and struct layouts (names guessed)

- **MapModel** (0x294 bytes, global `lbl_804CB860`, created by `fn_8013B920`). The layout is in `map3d.h`:
  - +0x08 groups (0xC0 each, count at +0x50), +0x0C meshes (0xD0 each, count at +0x52)
  - +0x4C/+0x4D map size in tiles, +0x80 quadtree root, +0x8A map name
  - +0xB1 model kind (0 is the battle map), +0xB4 flags: 0x40000000 loaded, 0x80000000 paused,
    0x10000000 has roof panels, 0xC0000 shadow mode, 0x1F00000 weather
  - +0xD0 scale, +0xE4 matrix, +0x114 16 sound emitters of 0x18 bytes (the mesh is at +0x14)
- **Mesh:** +0 flags (4 hidden, 8 switched, 0x20 culled), +1/+2 tile position, +4..+7 tile bounds,
  +0x10 group, +0xB0/+0xBC bounding box, +0xC8 next in a quadtree node, +0xCD opacity.
  The group's flags are at +0xB8: 0x800 door, 0x10000000 roof, 0x20000000 hidden on shadow maps.
- **Quadtree node:** +0 split, +1 visible, +2 count, +4 min, +0x10 max, +0x1C/+0x20 list, +0x24 four children.
- **Render settings:** `lbl_804CB830` shadow mode (1 and 2 are the modes checked by `IsShadowMode`),
  `lbl_804CB834` weather, `lbl_804CB839..3F` fog, `lbl_804CB840..4` light direction,
  `lbl_80413BE8`/`lbl_80413BF8` four ambient and four diffuse colours.
- **Map file names** are all in one string pool, `lbl_803694D4`: `%s.mapinst` at +0xA4, `.mapdata` +0xAF,
  `.maplight` +0xBA, `.mapfog` +0xC6, `.mapshader` +0xD0, `.maplink` +0xDD, `.maplinkAt` +0xE8, `.maplinkAbs` +0xF5.
- **Talk** (`lbl_804181AC`, 0x244 bytes, layout in `fn_80148634.cpp`): +0 process, +4 string with a short/long
  flag in the top bit (short data at +5, long size at +8 and pointer at +0xC), +0x10 script cursor,
  +0x1C 16 slots of 0x18 bytes, +0x19C slot to actor index, +0x200 current slot, +0x208 five actors,
  +0x21C nine portraits. Script tokens end in `|`, and `fn_80148728` handles Shift-JIS pairs.
- **Processes:** scripts sit in one data blob, `lbl_803861A0` (+0x18 door, +0x5C fall, +0xC8 lift,
  +0x118/+0x14C fade in and out, +0x180.. block switches).

## Caveats: matches that may not reflect the source

- **`volatile` hacks:** `MapLoaded` in `fn_8013A054` reads the flags through a volatile cast to force the second
  load, and `lbl_804CB5F4` is declared volatile in `fn_801386AC.cpp` to fix the epilogue order in `fn_80138764`
  and `fn_80138968`. The original almost certainly has neither.
- **Hand-made pointer:** `lp` in `fn_8013C234` is written out to get the induction register.
- **Variable shape chosen for registers:** `fn_8013A054` has one block-scoped counter per loop and a `Reset16`
  inline, and local `t` pointers and direct globals are mixed in `fn_8014BC80` and `fn_8014C148`.
  Only behaviour is checked, not that the source looked like this.
- **Recursion:** `QTReset` spells out one inlined level of `fn_80133EB4`. The original just recurses.
- **Guessed inlines:** `SetFog`, `SetColor`, `FindMesh90`, `Hex` and `IsShadowMode` reproduce a pattern. `MeshAt` is the
  one I trust most, since it fixed five functions at once.
- **Odd code that is really in the binary:** `fn_80148858` tests `c == 0` twice, so its `|` handling is dead.
- All prototypes of functions outside the region are guessed from call sites, and every name is a proposal.
- `fn_80135554.cpp` still has unused helpers (`LightsMul`, `UpdateEnv`, `CullShadow`) for the near miss in `wip/`.

- **Forced loads:** `fn_8013A054`-style volatile reads are also in `fn_80137724` (`Dirty`). `fn_80138E6C` keeps its first volatile write.
- **Kept dead stores:** `W3` word copies through a cast in `fn_8013C380`, `fn_8013E530` and `fn_8013D7B4`, and `*(int*)&dead.x` in `fn_80138E6C` and `*(u8*)&c.r` in `Upd`
  and `fn_80140BA4`. They reproduce stack writes the original probably got from a returned or by-value `Vec` or colour.
- **Placeholder statics (matters for the port):** `fn_80146BAC.cpp` declares `s80386490`..`s80386540` as zero-filled statics, and the originals are process script data in
  `.data` starting at `lbl_80386490`. The code matches because the offsets are right, but the data must come from the real tables before this file can link usefully.
  The checker doesn't verify these references: it only reports `...bss.0` and `s80386540`. I confirmed the offsets by reading the asm.
- **Dummy function:** `fn_dummy_names` in `fn_8013CCA4.cpp` only keeps `sNames` alive so the `sAxis*` constants land at `.rodata` offset 0x30, as in the original.
- **Declaration orders found by search:** `fn_8013A8D8`, `fn_8014C64C`, `fn_8014C2AC`, `fn_80143D88`, `fn_8013B9EC`, `fn_80135554`, `fn_8013D404` and others have function-level
  locals split per loop, in an order chosen by `sw`, a random search or brute force. The orders say nothing about the source.
- **Explicit stepped pointers:** `t = (Talk*)((u8*)t + 4)` in the talk loops and `off` in `fn_80143D88` stand in for compiler-made induction variables.
- **`fn_8014C2AC` and `fn_8014C64C`** paste the teardown instead of inlining `fn_80148B90`, which is probably how the original was written. `fn_80135554` and `fn_8013B9EC` also hold
  two copies of one body with different declaration orders. The original likely has one function auto-inlined.
- **Guessed:** every struct in the new files, including `Stone`, `Path` and `WeatherP`, is inferred from offsets.

- **Round 11 camera form:** in `fn_80141DCC.cpp`, `T` writes zeros through `*(int*)` and `Vec t` is declared before the aggregate `e`. That only reproduces the stack order and scheduling. The original probably has a small `Vec` helper I haven't identified.
- **Round 11 odd spellings:** `-(f32)(f64)h` in `fn_80140C8C`, `sz = l->g * sizeof(Particle)` in `fn_8014531C`, `f->ctr = f->ctr + 1` through a block-local pointer in `fn_8014B650`, and `*(u32*)&p1 = *(u32*)&m1` colour copies. All match, but may not be how the source reads.
- **Parameter inferred from a register:** `fn_8013B8D0` passes the weather id to `fn_80146BAC`, which is consistent with that function's two-parameter match in `fn_80146BAC.cpp`.
- **Round 11 guessed `extern` constness:** `lbl_804CDE88` and `lbl_804CA720` are declared non-const so their byte loads stay in source order, though the first is in `.sdata2`.
- **Round 14 forced shapes:** `fn_8013826C` has `SetMin`..`SetMin4` wrappers that only set stack slot depth, and its loop variables are passed by reference from the caller. The original is almost certainly plain recursion auto-inlined.
- **Round 14 odd declarations:** the float declaration orders in `fn_801445E8`, `fn_8013AE18` and `fn_8013AF10` come from random search. `fn_8013AF10` calls an `EnvSet` copy with a different order from the real `fn_8013AE18`, though the original surely has one body. `xx`/`yy` in those two, `a0`/`b0` in `fn_801445E8` and `k`/`n`/`m` in `fn_80143374` are temporaries that only fix registers.
- **Round 14 other shapes:** `*(u8* const*)&s` in `fn_8014A6CC` stops a CSE (a const read). `goto L` from case 7 to case 12 and the `q` walker in `fn_80149434`, the mixed `(c[3].g + c[2].g + ...)` sums in `fn_8013EA08` and `k *= 1.5f` placed last in `fn_80144938` are shapes found by testing.
- **`fn_8014A6CC` uninitialised `dir`:** that is real: the switch has no default, as in the binary.

## Skipped

- No function here was skipped as paired-single: `psq_st`/`psq_l` appear only as FP saves in the ones I read
  (`fn_80134F90`, `fn_8013531C`, `fn_80135554` and others). The remaining files were not all checked.
- Not attempted because of size: see item 3 of the resume point below.

## Round 16

- **fn_8013AC48 matched** from the near4 near miss with one change: the case-0 lookup goes through a one-line wrapper
  `FindB2(const char* name) { return FindB(name); }` around the by-reference inline. The by-value parameter gives the
  name its own rank (r29 above the file name), which the by-reference form at that site could not; `sw.py` on FindB
  then finished it. The wrapper is a register shape, not evidence of the source.
- **fn_80134F90**: the dummy functions are unnecessary, CW keeps unreferenced file statics, so `sA`/`sB` can stay
  as plain data. `static const` moves it far away (the copies are hoisted). Still 6 words: zero r23/walker r24
  swapped; by-reference locals, types, zero spellings and compiler-made walkers did not fix it.
- **fn_80141334** (4 words) does not respond to View parameter order, F& / Mtx* forms, Eye/T helpers or statement
  order. Its {0,1,0} template is lbl_8036991C, shared by five functions (fn_80141334, fn_80141650, fn_80141DCC,
  fn_801420B0, fn_80142D90), so it is probably one file `static const Vec`; the checker accepts the local template
  by value either way. fn_801420B0 addresses the same pool through lbl_80369910 (offsets 0xC, 0x3C, 0x48, 0x54), so
  it needs the TU's .rodata from 0x80369910 as file statics in order.
- Tried without effect this round: fn_80145980 frame loop (statement orders, s16 counters, a WGPIPE global),
  fn_80148D44 (hoist forms of the counter increment, t1/t2 orders), fn_8013E77C (all orders of six locals and
  inline signatures), fn_80136E74 (parameter copy in the /*P*/ block plus sw, wrapper with inline_max_size, the
  body as an inlined or real member function: the parameter stays r31).

## Resume point

1. `wip/near4.cpp` (round 14), closest first. Sections are standalone, and later sections can supersede earlier ones:
   - `fn_8013AC48`: solved in round 16 (`fn_8013AC48.cpp`).
   - `fn_80134F90` (0x38C): 9 words, only zero and walker registers swapped. Uses non-const statics, so check `.rodata` before accepting a match.
   - `fn_8013EED0` (0x268): masked 4 lines, 66 of ranks; parameter must be r23.
   - `fn_80136E74` (0x8B0): masked 0, 100 lines of ranks; parameter must be r22 and always takes r31.
   - `fn_80138FF8` (0x96C): masked 2 lines, about 120 of ranks; inner loop locals must rank above x, y, i.
   - `fn_80143908` (0x480): 33 lines, needs a dead `srawi` (y>>2) hoisted in the output loop.
   - `fn_80144324` (0x194): 74 lines, file statics give the hoisted addresses; copy order wrong.
   - `fn_801478F4` (0x204): row loop must unroll 2x.
2. `wip/near3.cpp`: `fn_80141334` (0x31C, 4 words: template base r5, want r4), `fn_80148D44` (0x6F0, 11 lines: t must be r23/r24, `li` hoist last), `fn_80137BC8` (0x438), `fn_80138000` (0x18C), `fn_80141650` (0x77C), `fn_80145980` (0x858), `fn_80139A7C` (0x5D8), `fn_80135C44` (0x344), `fn_8013E77C` (0x80), `fn_801386AC` (0xB8).
3. `wip/near2.cpp` still holds `fn_80136C34`, `fn_80134ECC`, `fn_80134814`. Its `fn_8013EED0`, `fn_8013AE18`, `fn_8013AC48`, `fn_80144938`, `fn_801478F4`, `fn_8013C4A4` entries are solved or superseded by `near4.cpp`.
4. Not yet attempted: `fn_801420B0` (0xB94). It starts from pooled statics at `lbl_80369910` and the camera form, so solve `fn_80144324` first.
5. Real quantized paired-single code, needing intrinsics or `asm`: `fn_80144BAC`, `fn_80145078` (`psq_l` with `qr5` and `mtspr GQR5`).
6. To list what's missing, subtract the checker's `OK` names from the `.fn` names in
   `build/RFEE01/asm/auto_03_80133EB4_text.s`.

## Compiler lessons from this region

- **An index inline fixes colouring.** `m = MeshAt(mm, i)` with `&mm->mesh[i]` inside matched five functions that direct
  indexing couldn't.
- **One block-scoped counter per loop.** Reusing a function-level `i` across loops changes colouring. Separate
  `{ int k; ... }` blocks solved `fn_8013A054` (0x308 bytes).
- **Direct globals versus a local pointer.** Using `lbl.field` rather than `Talk* t = &lbl` flipped a whole-function
  register swap in `fn_8014BC80` (0x254 bytes).
- **Colours by value:** a `lwz`/`stw` word copy between two stack slots followed by `lbz`/`stb` is a 4-byte struct passed
  by value to an inline.
- **A float register after a call** means the callee returns float, even if Ghidra shows a pointer (`fn_801142F0`).
- **`DIFF: 0 of N words differ`** means only a constant or reference is wrong. Read the `wrong reference` lines.
- **"User break, cancelled" with `COMPILE FAILED`** is an ordinary compile error, such as a missing extern, cut short by `-maxerrors 1`.
- **Struct assignment under `#pragma auto_inline off`** emits an out-of-line `__as__3VecFRC3Vec`, which the checker lists as `SKIP`.
- **Split locals and search.** Moving each loop's counter and walker to separate function-level locals, then running `sw`, a random multi-move search or brute force, solved
  `fn_8013A8D8`, `fn_8014C64C`, `fn_80143D88` and `fn_80135554`. `fn_80135554` had resisted direct fixes at 3 words.
- **Pooled `.rodata` statics:** `addi r4, r6, 0x30` with `lwz r0, 0x30(r6)` at entry means several file `static const Vec`s, with earlier data (`sNames`) setting the offset (`fn_8013CE9C`).
- **Top-down light view (`fn_80141DCC`):** by-value `Vec` parameters of one inline, listed `(u, t, e)`, sit lowest on the stack. Pass `T(t, x, z)` as an argument so each copy happens right after its value is built. That order alone fixed the zero register.
- **Stack depth test:** a by-value colour parameter one or two inlines deeper moves below a shallower temporary (`SetM2` in `fn_801369BC`).
- **Inline boundary plus pointer parameter:** moving the whole loop into an inline and passing `&lbl` as a parameter fixed nearly all saved registers in `fn_8013F3D8`, and took `fn_8014B4B4` to a match.
- **`lis` constants are CSE'd:** `lis r28, 1` held across calls appears when the size comes through a stored field (`l->g = n; sz = l->g * sizeof(T)`). `li` constants stay rematerialized.
- **Hoist order follows the expression form:** a block-local pointer `f` hoists `li rN, lbl@sda21` last in `fn_8014B650`, while a direct cast hoists it first.
- **Pooled statics, hoisted addresses:** `lwz r6,0x18(r29); lwz r5,4(r30)` with `addi r30,r29,0x18` is a word copy from a real file `static const Vec`. An extern array folds the `addi`. A const static copy is hoisted whole out of a loop, and a non-const static stays in the loop.
- **Float declaration search:** `f32 a, b, c;` then separate assignments, with a random or full permutation of the name list, solved four FP-only misses in seconds. Named read temporaries (`xx = e->x`) add ranks when the permutations alone stall.
- **Hoist order follows body order:** moving `k *= 1.5f` to the end of the loop body put its constant last and fixed the whole float allocation of `fn_80144938`.
- **Stack depth arithmetic:** with slot order low to high `A B C D`, give each temporary one more inline wrapper than the next. It fixes any order, as in `fn_8013826C` and `fn_80134F90`.
- **`n = n + sizeof(T)` versus `n += 12`:** the first stops induction elimination and keeps `addi rB,r1,N; stfsux f0,rB,rN`.
- **Register arguments after stores:** values still in r4/r5 after field stores are the next call's arguments (`fn_80150AFC(p, r.f, r.g)`).
- **`u16` from float:** `f((u16)w, (u16)h)` gives `lwz r3; lwz r4; clrlwi; clrlwi`. A named int local changes the registers.
- **Unsolved:** the parameter stays in r31 in `fn_80136E74` and `fn_8013EED0`, whatever the wrappers, copies, qualifiers or dead uses.

## Round 18

The goal changed: besides exact matches, a function counts when `tools/check_regs.py` classes it `renamed`/`regs` (same instructions, order and references; registers differ). Those are in `equiv/`, one self-contained file each.

**Functionally equal (8 functions, 0x1D40 bytes), all `regs`:**

| File in `equiv/` | Bytes | Source |
|---|---|---|
| `fn_80136E74` | 0x8B0 | `wip/near4.cpp` section, unchanged |
| `fn_80148D44` | 0x6F0 | `wip/near3.cpp`; the counter increment through a block-local `TF* f` puts `li r28,lbl_804CB878@sda21` last in the hoist order |
| `fn_80134F90` | 0x38C | `wip/near4.cpp`, the two `fn_dummy_*` functions removed (not needed) |
| `fn_80141334` | 0x31C | `wip/near3.cpp` section, unchanged |
| `fn_8013EED0` | 0x268 | `wip/near4.cpp`; loop step order `p8--, p16 -= 2, x--` |
| `fn_80136C34` | 0x240 | `wip/near2.cpp` with the declarations of `fn_8013608C.cpp` |
| `fn_80138000` | 0x18C | `wip/near3.cpp` with the declarations of `fn_8013B74C.cpp` and `use_lmw_stmw on` |
| `fn_80134ECC` | 0xC4 | `wip/near2.cpp`, needs only `map3d.h` |

No new exact matches in this region.

**Not done (other), new files in `wip/`:** `r18_fn_80137BC8.cpp` (the eight corner-height stores that the old draft had lost are written back, and the `.rodata` in front now holds the real six Vecs of `fn_80134F90` instead of a pad; same size, 20 masked lines of scheduling in the tile copy), `r18_fn_80144BAC.cpp` (72 of 73 instructions: one stack store of the z velocity is removed as dead here).

**Still open:** `fn_801420B0` (0xB94, not attempted), `fn_80138FF8`, `fn_80145980`, `fn_80141650`, `fn_80139A7C`, `fn_80143908`, `fn_80135C44`, `fn_80144324`, `fn_801478F4`, `fn_80134814`, `fn_801386AC`, `fn_8013E77C`, `fn_80145078`. Their drafts differ in instruction order or count, not only registers; the diffs are mostly scheduling that follows the register choice (`fn_80145980`, `fn_80141650`, `fn_80137BC8`), so they need the registers nearly right first. A masked-score declaration search on `fn_80141650` and `fn_80137BC8` did not move them. `fn_80139A7C`: a `do { n += C2(k - 1); } while (++i < 4);` top level keeps the count loop unfolded but not as a `bdnz` loop; every `for` form folds to `li r3,0x1144`.

**Caveats:** `equiv/fn_80134F90.cpp` keeps `sA`/`sB` as non-const statics (the original data is in `.rodata`). `equiv/fn_80136C34.cpp` and `equiv/fn_80138000.cpp` start with a whole parent file's declarations. The earlier caveats on these drafts (declaration orders from searches, `Hit` wrappers, by-value `Vec` helpers) still apply.

**Lessons:**
- `fn_80144BAC`/`fn_80145078` are not hand-written asm: `mtspr GQR5` and `psq_l ..., 1, qr5` come out of `static inline` asm helpers (`SetGQR5`, `LD5`) with ordinary C around them. A compiler store right after an asm `psq_l` survives because the next asm block is a barrier for dead-store removal.
- A fragment listed as "registers only" can still be `other` once it is compiled alone: check the `#pragma use_lmw_stmw` state of the parent it came from.

## Round 20

Levels as in `docs/MATCHING.md`; all files below are self-contained and were re-checked with `tools/check_regs.py <file> --extra "-i src/game/rL_80133EB4 -i src/game/rL_80133EB4/wip"`.

**New at a counted level (6 functions, 0x2898 bytes), in `equiv/`:**

| File | Bytes | Class | Notes |
|---|---|---|---|
| `fn_801420B0` | 0xB94 | sched | New, from the disassembly. Three-pass texture projection, sibling of `fn_80141650` |
| `fn_80138FF8` | 0x96C | regs | Round 14 draft fixed: door search as an inline with early returns, loop step order `off0 += 8, i++` |
| `fn_80145980` | 0x858 | sched | `wip/near3.cpp` section, unchanged |
| `fn_80141650` | 0x77C | sched | `wip/near3.cpp` section, unchanged |
| `fn_80135C44` | 0x344 | sched | Plain function instead of the `Body` inline wrapper (which lost one `mr`) |
| `fn_8013E77C` | 0x80 | sched | `wip/near3.cpp` section, matched neighbours removed |

**Copied from `wip/` (already listed in `docs/EQUIVALENT.tsv`):** `equiv/fn_80137BC8.cpp` (0x438, sched).

The moved instructions of every `sched` file are listed in its header.

**Complete draft left at `other`:** `wip/r20_fn_80134814.cpp` (0x178, 98 of 94 instructions in one block: the original keeps four constants in saved registers and writes its three local colours to the stack last; see the header for what was tried).

**Checked, still `other`:** `fn_80143908` (17 masked lines, the dead `srawi`), `fn_80139A7C` (count loop folds), `fn_80144BAC` (third `stfs` removed as dead; an `LDV(&d.x, p)` store-through inline, an empty asm barrier and an `LD3` wrapper changed nothing), `fn_801386AC` (46 of 46 instructions, 8 masked lines: an `fsubs` and two float loads sit in other positions and one load pair differs, so it is not `sched`; not worked on), `fn_80144324`, `fn_801478F4`. `fn_80145078` has no draft.

**Caveats:** `equiv/fn_801420B0.cpp` holds the translation unit's ten `.rodata` vectors as non-const file statics (four of them belong to `fn_80141334`/`fn_80141650` and are there only for the pool offsets); with local initialisers the function is one word from the original apart from the pool offsets. Its `PROJ` macro with explicit copies replaces what is most likely a by-value inline (`View`). `equiv/fn_80138FF8.cpp` keeps the per-site `FIND` macro and locals of the old register search.

**Lessons:**
- **`.rodata` pool layout of this translation unit (`lbl_80369910`):** +0x00 and +0x18 are `fn_80141334`'s eye and up templates, +0x0C is an eye template shared by `fn_80141650` and all three passes of `fn_801420B0` (so it comes from one shared inline), +0x24 is `fn_80141650`'s up, +0x30 an unused up, +0x3C/+0x48 the two scale vectors and +0x54/+0x60/+0x6C the three ups of `fn_801420B0`.
- **Unreferenced `static const` objects are dropped by the compiler; non-const statics are kept.** A const static that is copied several times is also loaded once and held in saved registers across calls, where local-initialiser templates are reloaded each time.
- **Stack layout tells block scope from inline:** at function level the first-declared local is highest and all by-value copies of inlined calls come after every named local; per-pass groups `t, e, u, copy, copy` mean explicit copies in function scope (or a macro).
- **A recursive function written as `return Body(...)`** loses the entry copy of a parameter that the plain function keeps.

## Round 21 (large functions without a draft)

Levels as in `docs/MATCHING.md`; every file below is self-contained and was re-checked with `tools/check_regs.py <file> --extra "-i src/game/rL_80133EB4 -i src/game/rL_80133EB4/wip"`.

**New at a counted level (1 function, 0x2A4 bytes):**

| File | Bytes | Class | Notes |
|---|---|---|---|
| `equiv/fn_80145078.cpp` | 0x2A4 | regs | New, from the disassembly. Weather particle spawn; 16 words differ, all in the choice of f0..f3 |

**Complete drafts left at `other` (now self-contained files instead of `near*.cpp` sections):**

| File | Bytes | Instructions | What differs |
|---|---|---|---|
| `wip/r21_fn_80143908.cpp` | 0x480 | 287 of 288 | The dead `srawi r3,r9,2` in the texture write loop; ten more forms tried, listed in the header |
| `wip/r21_fn_80139A7C.cpp` | 0x5D8 | 370 of 374 | The node count loop folds to `li r3,0x1144` (the original keeps `li r0,4; addi r3,r3,0x15; bdnz`), one `li 2` is shared, two `stbux` are `stbx; add` |

**Caveats:** `equiv/fn_80145078.cpp`: `ST5b`/`ST5c` are wrappers that only order three stack temporaries; the GQR5 inlines stand for `(s16)f`, `(s16)(f * 256.0f)` and `(f32)s16`; the block-scoped `fx/fy/fz` only fix the operation order. The `Part` node layout (list header 8 bytes, then `t`, `life`, `alpha`, `vel[3]`, `pos`) agrees with `wip/r18_fn_80144BAC.cpp`.

**Lessons:**
- **Fast-cast groups:** three `psq_st` conversions whose temporaries descend on the stack are three sibling inline calls; a group whose temporaries ascend needs one more wrapper level per earlier call (`ST5c`, `ST5b`, `ST5`). Computing all operands into block-scoped floats first (`f32 fx = …; f32 fy = …; f32 fz = …;` then the conversions) reproduces "all subtractions, then all stores" and moved the draft from `sched` to `regs`.
- **The pool allocator inline** (`n = *l->c; if (!n) return 0; n->p = l->e; n->n = 0; …; l->c++; l->f++;`) matches as written; the caller's `if (n)` then repeats the null test.
- **A recursive `static inline` is inlined one level and then called out of line** whatever `inline_depth` says (2..30 tried), and a plain recursive static under `-inline auto` is not inlined at all; neither gives the original's "outer loop kept, inner levels folded" count in `fn_80139A7C`.
- **A hoisted row local in the texture loop (`int row = …` or `u8* row = …` in the outer loop) stops the 2x unrolling** (435 instead of 288 instructions in `fn_80143908`).
