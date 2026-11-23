# Region 0x8025EEF0..0x8028BC54 notes

## Status

316 of 380 functions match, 84464 (0x149F0) of 0x2CD64 bytes (46%). Before round 13 the count was 298 functions and 57636 bytes (taken from `matched_names`; this header had said 295 and 0xDF9C). Round 13 added 18 functions and 26828 bytes (0x68CC). Every `.cpp` directly in this folder prints
MATCH with `python3 -I tools/check_func.py <file> -v`, except `fn_8026961C_search.cpp`, a leftover search draft from Nov 5 that was not added as a match (not re-checked in round 13). Nothing needs `--cc`: the default GC/3.0a5.2 works throughout.

The region is game code, not a library. The only library trace is the NW4R assert inlined from
`SoundArchivePlayer.h` (`fn_8025F238`, panic is `fn_8029C20C`) and calls into NW4R snd and DVD code above 0x802AA000.

| File | Functions | Contents |
|---|---|---|
| `fn_8025EEF0.cpp` | 47 | Sound-player destructors, accessors, adjustor thunks |
| `fn_8025F3D0.cpp` | 6 | Streamed sound reader: DVD read with completion callback |
| `fn_8025F6A0.cpp` | 34 | Tail stubs, scissor helpers, unit-slot menu creation, tiny procs |
| `fn_8025F6B8.cpp` | 2 | Dictionary flag test/set/clear by "DF_*" name |
| `fn_802600A4.cpp` | 4 | Dictionary lookup and state switches |
| `fn_80263160.cpp` | 1 | Dictionary list page draw |
| `fn_80263418.cpp` | 1 | fn_802636F0, dictionary teardown |
| `fn_802639D0.cpp` | 3 | dictionary.bin and dictionaryF.bin loaders |
| `fn_80263D18.cpp` | 1 | fn_80263E5C, builds the visible list |
| `fn_80264EF0.cpp` | 1 | Dictionary caption |
| `fn_80266E3C.cpp` | 14 | Dictionary creation, fades, three-group unit slot table |
| `fn_8026A390.cpp` | 2 | Intro profile bars (Prim2D) |
| `fn_8026A724.cpp` | 13 | Title intro procs (FE10Intro.bin) |
| `fn_8026BE70.cpp` | 11 | Asset load procs, FE8 stream header check, shuffle, teardown |
| `fn_8026FB6C.cpp` | 27 | Menu setup, small dtors, conversation-room accessors |
| `fn_80272624.cpp` | 5 | Sound handle: volume, stop, 3D position |
| `fn_8027D46C.cpp` | 60 | Conversation room, fade bar, accessors, scissor stubs, misc |
| `fn_80280A00.cpp` | 15 | Bar slide, confirm-dialog setup, reset/TV handling, controller scan |
| `fn_80265060.cpp` | 1 | Dictionary description text |
| `fn_802652DC.cpp` | 1 | Relation chart: unit node |
| `fn_80265840.cpp` | 1 | Relation chart: unit box |
| `fn_8026654C.cpp` | 1 | Relation chart: pulsing frame corners |
| `fn_8026B96C.cpp` | 1 | Title press-start screen |
| `fn_8026C1C8.cpp` | 7 | FE8 save transfer: person data, stat rebuild, supports reader |
| `fn_8026D470.cpp` | 1 | Random-order list: switch the shown model |
| `fn_80272FAC.cpp` | 2 | Conversation room: topic jump, cursor position |
| `fn_80274790.cpp` | 5 | Conversation room: scroll setup, layout, topic lists |
| `fn_8027B568.cpp` | 1 | Conversation room: scroll animation |
| `fn_8027F7DC.cpp` | 4 | Three proc teardowns with an inlined vector destructor; `fn_8028BBD0` |
| `fn_80286FC0.cpp` | 1 | Item preview model draw |
| `fn_802758B0.cpp` | 1 | Conversation room: header bar |
| `fn_8026BBE8.cpp` | 1 | Title press-start screen setup |
| `fn_802676A0.cpp` | 1 | Unit slot menu: swap two slots, close the gap |
| `fn_802692FC.cpp` | 1 | Unit slot menu: fill the three groups, create bars |
| `fn_80271EF8.cpp` | 1 | Slide proc setup: allocates three drawer objects per side |
| `fn_8027D7CC.cpp` | 1 | Model viewport: draw callback |
| `fn_8027DA1C.cpp` | 1 | Model viewport: place and draw the model |
| `fn_8027E884.cpp` | 1 | War record row text |
| `fn_8027EFAC.cpp` | 1 | Scrolling list: screen draw and auto scroll |
| `fn_8027F9B0.cpp` | 2 | Two-digit number draw (two alpha sources) |
| `fn_802841E0.cpp` | 1 | Unit record screen: frame and page switch |
| `fn_8028784C.cpp` | 1 | Gradient bar |
| `fn_8028871C.cpp` | 1 | Result report: creation |
| `fn_8028893C.cpp` | 3 | Result report teardown, two timed text procs |
| `fn_80288A98.cpp` | 1 | Staff roll: setup |
| `fn_8028A070.cpp` | 1 | Staff roll: per-frame logic |
| `fn_8028A540.cpp` | 1 | GX state for the capture quad |
| `fn_8028A88C.cpp` | 1 | Classic controller cursor emulation and capture loop (round 15; `.symbols.json` maps `...bss.0` to `lbl_80430CE0`) |
| `fn_8026FE48.cpp` | 1 | Text box proc: message script stepper (round 15) |
| `fn_80262744.cpp` | 1 | Relation chart: per-frame input, zoom, scroll, cursor (round 15) |
| `fn_8028B2E0.cpp` | 1 | Health and safety screen: fade and draw |
| `fn_8028B720.cpp` | 1 | Health and safety screen: language preload |
| `fn_80260B48.cpp` | 1 | Dictionary: per-frame update |
| `fn_80265BCC.cpp` | 1 | Relation chart: frame |
| `fn_8026697C.cpp` | 1 | Relation chart: info window |
| `fn_802678C0.cpp` | 1 | Unit slot menu: second cursor mode |
| `fn_802680FC.cpp` | 1 | Unit slot menu: cursor and buttons |
| `fn_802687FC.cpp` | 1 | Unit slot menu: draw |
| `fn_8026972C.cpp` | 1 | Unit slot menu: unit info window |
| `fn_8026B200.cpp` | 1 | Title intro: profile screen |
| `fn_8026F630.cpp` | 1 | Soundroom: list setup |
| `fn_8027BC1C.cpp` | 1 | Conversation room: list input, mode 0 |
| `fn_8027C1B4.cpp` | 1 | Conversation room: list input |
| `fn_8027CE60.cpp` | 1 | Conversation room: setup |
| `fn_8027DF84.cpp` | 1 | Model viewport: debug camera |
| `fn_8027E4B8.cpp` | 1 | Model viewport: camera angle read-back |
| `fn_80282D00.cpp` | 1 | Confirm dialog: update |
| `fn_802845C8.cpp` | 1 | Unit record: list page (reverse iterator; its weak `__dt__3CRIFv` shows as SKIP) |
| `fn_80286B44.cpp` | 1 | Unit record: per-frame logic |
| `fn_8028831C.cpp` | 1 | Result report: scroll input |

Shared: `types.h`, `calls.h` (external prototypes, inferred from call sites), `prim2d.h`, `dict.h`, `room.h` (conversation-room data and its inlines), `roomdraw.h` (prototypes and helpers for the room draw functions, used by `wip/` only so far).

## Lessons from this round

- Conversation-room functions are mostly `roomData()` expansions. Earlier functions in a file inline into later ones, so `fn_80272FAC` shows up five times in `fn_802732FC`.
- `tools/perm/hill.py` shuffles every `/*P*/` block in the file while scoring one function, so it can break functions that already match. Score all functions in the file, or keep one function per file.
- A neighbourhood search (try every single move and swap of the declaration lines, keep the best, repeat) solved several functions where `hill.py` stalled.

## Lessons from round 13

- Writing a whole function by hand from Ghidra plus the asm usually reached the right size on the first compile, and several had no differences at all. Call-heavy UI, draw and input functions pay best.
- Search grids over declaration order (`gr.py`-style permutations) find orders that a single-swap search misses, because positional scores tie.
- A wrapper is not a general fix. It solved `fn_8026697C` (`body(lbl_804CC008)` put s below n), but on `fn_80275FD4` and `fn_80277E10` it went from 123 to 186 and from 80 to 136 lines, and on `fn_8028530C` it fixed n/tex while breaking block locals.

Register rank:
- Moving a block into an inline with the row or index as parameters fixes the rank of a volatile register (`down` in `fn_802680FC`). `moves(pr, held, d)` with the old value as an inline local fixed an old/d swap in `fn_80260E58`.
- An out-parameter `BOOL& r` through an inline ranks a result register where an inline return cannot (`isEnd8`).
- `f(call1, call2)` with nested calls, in place of a named temporary, gives a value saved over the inner call the rank of a compiler temporary (`fn_802845C8`).
- A literal string base with no variable gives `lis r3; addi r27,r3`.
- Assigning through `if` rather than a ternary moves rank in both directions: ternary results ranked low in `tm` and `bx`, and `if`-form locals ranked high in `pts`.

Stack slots:
- Two levels of inline (`moveCursor` to `moveCursor2`) push a caller local below the inline temporaries.
- By-reference colour locals declared in the outer inline give explicit slots.
- `C4 c = mk5()`, with `inline C4 mk5() { C4 r = kc; return r; }` and a non-const static, puts a colour in the bottom slot.

Instruction shapes:
- `stw r12,8(r1)` followed by r, g, b bytes is a hand zero word plus byte stores. An sdata2 byte load mixed with stores is `C4 c = {r, g, b, 0xFF};` with non-constant RGB.
- A nested `struct It {Pair* p;}` inside a reverse iterator stops scalar replacement. A `const_reverse_iterator` converting constructor that copies only `cur`, plus `~CRI(){}`, keeps it in memory and drops the temporary copy.
- An unsigned field (`u32 m44`) stops `a*k + k` folding to `(a+1)*k`. `int k = 3 - x; (k+1)` stops `3-x+1` folding.
- `x / 32.0f` gives `fmadds conv,k,..` where `0.03125f * x` does not. `r *= -1.0f` gives `fmuls f31,f31,f0`.
- Enum ternary arguments such as `(st&4) ? WK_3C : WK_3B` keep `li r3` before the branch.
- `s16 x = float_expr` with no int cast keeps `lwz rN`, with `extsh` only at wide uses. `(u16)(st&4) != 0` gives an inline u16 flag.
- A one-case or two-label `switch` gives the `bge cr1; cmpwi; bge; b` range shape.

## Round 15

Added 3 functions, 6020 bytes (0x1784): `fn_8028A88C`, `fn_8026FE48`, `fn_80262744`. The round was cut by a usage-limit pause that wiped the scratch folder, losing a finished draft and two searches in progress. Matches another tool committed during the pause (`fn_80282720`, `fn_802889AC`, `fn_8028B154`) are not counted here.

Lessons:
- `addi rN, rBase, 0x0` plus fields at fixed offsets (`fn_8028A88C`): the source used file statics, not one struct global. Pad between them with `u8` arrays to get the offsets, and map `...bss.0` in a `.symbols.json` for `--strict-references`.
- Explicit stepped pointers (`ty++, ps++, pk += 16, pc++, c++` in the `for` header) fixed five induction registers at once; the order inside the header sets their rank, so grid all permutations (120 compiles).
- Named fabs temporaries: `t1 = __fabs(a0); if (t1 > k)` with `t1`, `t2` in the `/*P*/` block put the temporary in the right FPR where every inline or ternary form failed.
- A late `extsh` on a value that was already sign-extended at its `neg` (`ox = (s16)-ox`) came back only when the first definition was read through an int-returning inline (`ox = rd4(d + 0x28)`).
- `mr` copies of a loaded value (`lha r3; mr r4,r3`) where ours loaded the copy directly: read the global twice, once through the cached pointer and once through the macro (`x = e->x44; ox = CH->x44;`). The compiler CSEs the second read into a copy after coalescing.
- Pre-schedule statement order decided volatile pointer registers in a loop setup (`old = CH->m0; st = ...; e3 = CH;`) where declaration order did nothing.
- Colour stack slots in a long draw function (`fn_80270348`): when by-value colour temporaries and their argument copies need an order no nesting gives, named colour locals at function level (highest offset first) with a `C4*` prototype and a hand word copy fix every slot at once.
- Element copies in a backward vector move: `E(const E& o) { *(W2*)this = *(const W2*)&o; }` gives the `lwz`/`lwz`/`stw`/`stw` word copy; the implicit copy of a struct with a user constructor copies member by member.
- `grid.py ... save` writes the best candidate even when every candidate failed to compile (score 9999). Check the score before saving.

## Subsystems (names are inferred from strings and behaviour)

| Range | What |
|---|---|
| 8025EEF0..8025F6B0 | Sound glue classes over NW4R |
| 8025F6B8..8026724C | Dictionary / glossary menu with relation chart (`mess/e_dic.m`, `RectDictionary`, `RectRelation*`) |
| 8026725C..8026A340 | Menu moving units between 3 groups of 20 (`lbl_80430740`) |
| 8026A390..8026B958 | Title intro unit profiles |
| 8026B96C..8026C1B8 | Asset-loading procs |
| 8026C1C8..8026D470 | Reader with magic `FE8J` (0x4645384A) and "PersonData8". Probably Path of Radiance save transfer |
| 8026D470..8026FBC8 | Random-order list using `lbl_804CC044` (purpose unknown) |
| 80272624..802729F8 | Sound handle wrapper |
| 80272A14..8027D740 | Conversation room (`E_ConversationRoom`, `E_ConversationRoomFe8`, `MCR_*`) |
| 8027D7CC..8027E884 | Model viewport proc (`FadeBar` here), camera defaults |
| 80280990..80280EE0 | Sliding bars (`lbl_804CC0A8`) |
| 80283688..80283B5C | Confirm dialog (`lbl_80392C18`, `SFX_SYS_SAVE_ERROR1`) |
| 8028A7C8..8028BC44 | GX framebuffer capture, power/reset handling, controller scan |

Not identified: 8026D73C, 80270348, 802732FC..8027ACDC (large draw functions), 802818FC, 8028530C.

## Tools from this round (kept out of the repo, easy to redo)

- Collapse `roomData()` when reading asm: match from `bl fn_80085708` through the second join label and print one line. A 2000-line function becomes about 1000.
- Compare with registers blanked first. Once that diff is empty, only colouring is left, and a table of ours -> original register pairs shows whether it is one rotation or several.

## Struct layouts

- `DictState` (`dict.h`, `lbl_804CC004`, 0x80 bytes): fields from +0x28 to +0x4B repeat per page, 0x24 apart; use `DICT_PAGE`. +4 mode, +8/+C text lines, +0x10/+0x14 visible list, +0x18 page, +0x74 model proc, +0x78 scrollbar object, +0x7C another proc.
- `DictState2` (`lbl_804CC008`, 0x8C bytes): chart state. Scroll +0x44, zoom +0x5C/+0x60/+0x64/+0x68, visibility byte arrays +0x6C/+0x70/+0x74.
- `DictMain` and `DictFlags` (`lbl_804306E8`, `lbl_80430710`): pointers into the files, alternating count and table.
- Save data (`fn_8024BC94`): +0x20 flags, +0x18B4/+0x18C8/+0x18D4/+0x18E0 dictionary bitsets, +0x18E8.. menu state, +0x1BC8 language (s8).
- `Slot` (8 bytes): unit pointer, 2 s16. `lbl_80430740[3][20]`.
- `SndHandle` (0x18): mode, s8 sound id, range, volume, position, +0x14.
- `Reader` (stack, `fn_8026C650`): buf, cur, size, own, vtable at +0x10. The destructor sets vtable `lbl_80380940` and frees if own.
- Classes with the vtable pointer at +0x28 (`DtorObj`): data base class first, destructor at slot 0x14.

## Resume point

Best bytes first:

1. **Very close, registers only**: `wip/fn_8027C5CC.cpp` (6), `wip/fn_80287B54.cpp` (9), `wip/fn_80280F1C.cpp` (10), `wip/fn_8028B84C.cpp` (2), `wip/fn_8027ECA4.cpp` (5, not retried with the round 13 tricks).
2. **Larger near misses**: `wip/fn_80260E58.cpp` (22), `wip/fn_8027D14C.cpp` (25), `wip/fn_80289214.cpp` (about 28), `wip/fn_80280060.cpp` (16 to 32), `wip/fn_802818FC.cpp` (51).
3. **`wip/fn_8028530C.cpp`**: 0x16D4 bytes, right size, 41 words. Wrapper and hybrid forms gave nothing better, so it needs a new idea for the block locals a0, b0, e, w0 and x.
4. **`wip/fn_802644CC.cpp`** (9), **`wip/fn_80288094.cpp`** (11), **`wip/fn_80271434.cpp`** (15), **`wip/fn_80266024.cpp`** (21). Not solved in round 13.
5. **Vector push**: `wip/fn_8027F368.cpp` (15 lines, 8-byte items, backward copy loop),  `fn_80283BC8`, `fn_802811E8`, `fn_80287358`, and `wip/fn_8027F84C.cpp` (`reserve(0x50)` inlined into two procs). They probably share one fix.
6. Time sinks, leave for last: `wip/fn_80277E10.cpp`, `wip/fn_80275FD4.cpp`, `wip/fn_802732FC.cpp`, `wip/fn_80282FF4.cpp` (91), `wip/fn_8026D73C.cpp` (165), `fn_8027970C`.
7. Not attempted: `fn_80261728`, `fn_8026E9DC`, `fn_8027163C`. Round 15 near misses: `wip/fn_80270348.cpp` (38, registers only), `wip/fn_80260140.cpp` (19, registers only), `wip/fn_802828B4.cpp` (flag term shape plus registers).

`wip/` near misses (comment in each file):

| Function | Words | Cause |
|---|---|---|
| fn_80270348 | 38 | round 15; colour slots and shape right, by-reference locals searched |
| fn_80260140 | 19 | round 15; first lookup st/pg swap, final page pointer and zero |
| fn_8027F368 | 15 | round 15; vector push of 8-byte items, string base rank, copy order |
| fn_802828B4 | 2 short, 18 masked | round 15; 0x1A flag term wants extrwi/neg/or/srawi |
| fn_8028530C | 41 | registers only, same size; wrapper gives 34 but breaks block locals a0, b0, e, w0, x, so the plain form stays |
| fn_802818FC | 51 | o should be r23, end r17 |
| fn_80289214 | about 28 | zero colour words should reuse xa (r25) |
| fn_80282FF4 | 91 | off is coloured first |
| fn_8026D73C | 165 | same size; registers and float hoist order |
| fn_80287B54 | 9 | e r27 vs s r28 |
| fn_8027D14C | 25 | temporaries r31 vs r30 |
| fn_80280F1C | 10 | registers |
| fn_80260E58 | 22 | registers; `moves` inline fixed old/d |
| fn_8027C5CC | 6 | end temporaries r26, should be r27 |
| fn_80280060 | 16 to 32 | literal load order vs s16/int prototype |
| fn_802644CC | 9 | loop base r4 and index r5 swapped |
| fn_8027ECA4 | 5 | loop offset and hoisted `lis` swapped |
| fn_8028B84C | 2 | value kept across a call: r31, should be r29 |
| fn_80288094 | 11 | string base should rank lowest |
| fn_80271434 | 15 | entry swap; `bne A; b B; A: fneg` not reproduced |
| fn_80266024 | 21 | needs `mr r3,tex` before the tile branch |
| fn_802732FC | 4 | case 5 at +0x1148: m42 r5, row term r6, `add r31,r6,r5`. Grids over m42 and row forms, statement order, wrappers and 10 inline shapes all stay at 4 |
| fn_80265574 | 4 | final text call: x through r0, y in r4 |
| fn_8026961C | 6 | third slot loop registers |
| fn_8026D0F8 | 12 | e and first name result swap r30/r26 |
| fn_802662EC | 17 | string registers and hoisted 0x4330 |
| fn_8027ACDC, fn_8027AF54 | 29, 26 | string base should stay r26 |
| fn_8027B144 | about 28 | `li r3,4` and `(f32)4` must share a register; `const int&` gets `lwz` from sdata2 |
| fn_80275FD4 | registers only, 123 lines | x r21, should be r31. Wrapper plus search: 186, no gain |
| fn_80277E10 | registers only, 80 lines | tx/bx swap, rect and flag temporaries. Wrapper plus search: 136, no gain |
| fn_8027F84C, fn_80287188 | 42 | reserve: element copy registers |
| fn_80283528, fn_802836C0 | 12, 4 | load scheduling only |
| fn_8028B154 | 2 | `addi r3, r31, 0` instead of `mr` |
| fn_80263D18, fn_80263DE0 | 12, 10 | load of `*s` after store, loop registers |
| fn_80263418 | 6 | first two loop offsets should be r27 |
| fn_80263B64 | 7 | second loop registers |
| fn_80264034, fn_80264204 | 6, 22 | one register swap; base pointer colours |
| fn_802643B8 | 10 | flag and base registers |
| fn_8026A864 | 13 | r30/r31 swap |
| fn_8026A9D4, fn_8026AB7C | 16, 10 | loop registers |
| fn_8027247C | 12 | float registers only |
| fn_8026FC38 | 25 | clamp through r0, final order |
| fn_8025F068, fn_8025F0E8 | 4, 11 | scheduling, conversion registers |
| fn_8026806C | 2 | `lha` above `stwu` |
| fn_80280CB4 | 2 | `li` and `addi` order |
| fn_80280DF8, fn_80282720, fn_802889AC | 1 extra word, 8, no tail call | dead `cmpwi`; base register; call kept non-tail |

## Matches that may not reflect the source

- Declaration orders from `hill.py`: `fn_8025F6B8`, `fn_80263160`, `fn_802636F0`, `fn_80267360`, `fn_80267568`, `fn_8026FD98`. The split variables and unused-looking ordering in them are compiler steering.
- `handleInit` writes float locals through `int*` to get the stack `stw`, and `VecW` copies words. The original probably used a vector class.
- `lbl_804CB700` is volatile as in region I, except in `fn_80280A00.cpp`, which defines `RN_FLAGS_PLAIN`. It is probably not really volatile.
- `int v = 0xFFFF` in `fn_8027D948` exists to get the masked constant.
- Prototypes in `calls.h` and the file-local ones are inferred and may have the wrong types.
- Declaration orders from a neighbourhood search: `fn_80265060`, `fn_802652DC`, `fn_80265840`, `fn_8026654C`, `fn_8026C1C8.cpp`, `fn_8026D470`, `fn_80272ED0`, `fn_80274790.cpp`, `fn_80286A3C`.
- `fn_80265060` writes the loop's induction variables by hand (`off`, `yy`), and `msg` doubles as the float result on purpose.
- `Icon` in `fn_802652DC` and `setCur*`/`cur*` in `room.h` exist for register and offset effects. The parameter order of `Icon` is reversed to get the evaluation order.
- `fn_802758B0`: `part` only wraps `part0` to push the colour slots below the `grad` parameters. `fn_801BC88C` is declared with `GXC*` and the by-value copy is written by hand as a word copy to a second local; the original almost certainly passes `GXC` by value. `sc0` and `sc1` are one 8-byte block in the original (`lbl_804D05DC`), and the checker verifies them by value only.
- `fn_8026BBE8`: the block-scoped `s8 lang` was found by trial.
- `fn_80286FC0` reads `p[0]` once through `void* const*` and once through a `volatile` cast, to keep one early load and one reload. The original surely had neither.
- `vecClear` in `fn_8027F7DC.cpp` spells the size as a pointer difference, because `size -= size` folds to 0. It probably really was `end - begin`, but that is a guess.
- `fn_8026C1C8.cpp`: the `Buf` class and the plain `Reader` struct describe the same object. `Reader` avoids emitting a vtable.
- `int b = fn_8008A1A0(...)` in that file is there for the `mr r0,r3` before the `u8` argument. The real source probably used an inline or a wider return.
- Declaration orders from a neighbourhood or random search: `fn_802692FC`, `fn_8027F9B0.cpp`, `fn_8027E884`, `fn_80288E90`, `fn_8028A070`. The `/*P*/` and `/*E*/` comments mark those blocks.
- `fn_8027F9B0.cpp`: `mix`, `dv` and `rm` exist only so their results colour ahead of declared locals. `fn_8028A070` and `fn_80288E90` split `f` and `q` for the same kind of reason.
- `fn_802692FC`: `((u8**)row)[n * 2]` writes an 8-byte `Slot` as two pointers to get `stwx`; `row[n].unit` steps a pointer instead. The original may have been that spelling, but it is a guess.
- `fn_802676A0`: `*(int*)q` reads the unit a second way, only to stop the compiler reusing the earlier load.
- `fn_802841E0`, `fn_8028B2E0`, `fn_80266024` (wip): colour copies are written by hand as word copies into named locals, with `C4*` prototypes. The originals almost certainly pass the colour by value.
- `fn_8027D7CC`, `fn_802841E0`: `kc`, `c0`, `c1` are non-const statics to stop loads moving above stores. The originals are in `.sdata2`, so they were const. The checker compares their values only.
- `fn_8028B2E0`: the `f32 v` step exists for `fadds` operand order. `fn_8028B720`, `fn_8028A540`, `fn_8028784C` prototypes are inferred from register use.
- Round 13, all files: declaration orders come from search (the `/*P*/` blocks), and struct layouts and prototypes are inferred.
- Hand word copies of colours with pointer prototypes: `fn_802687FC`, `fn_8026972C`, `fn_8026D73C` and `fn_802818FC` (both wip). Zero-word colours written by hand: `fn_80265BCC`, `fn_8026B200`. The originals almost certainly pass colours by value.
- `fn_802687FC`: three copied group inlines with different declaration orders, references for colour slots, and a double-nested `first2`, all for allocation.
- `fn_802680FC`: the `moveCursor` double wrapper, the `isEnd8` out-parameter, and duplicate `down` inlines. The `Pt` copy constructor is steering too.
- `fn_8026B200`: the `(u8)` casts, `int z=0x10000` and int `k` are spelled for code shape.
- `fn_802845C8`: the `CRI` struct, non-const static `kc`, `u32 m44` and `pdraw` are steering. The real source likely used a library iterator type. It also emits a weak `__dt__3CRIFv` that may not be in the original.
- `fn_80286B44`: local `k`. `fn_8026F630`: int local `z` for the zero conversion. `fn_8028831C`: block-local `w` at one site. `fn_8027C1B4`, `fn_8027BC1C`: local `v` with a literal 0.0f argument.
- `fn_80265BCC`, `fn_8027DF84`: `*(int*)&d.x = 0` to get an integer store into a float field.
- `fn_8027E4B8`: an extern non-const `Vec3` stands in for a constant template.
- `fn_80282D00`: statement order and `xi + a + q*2` are chosen to match, not known.
- `fn_8026697C`: the `body(lbl_804CC008)` wrapper exists only for allocation.
- Round 15, `fn_8028A88C`: the file statics and their padding stand in for whatever the original TU declared at `lbl_80430CE0`; `f32 o = 1.0f; f32 k = ...; d = o / k` stops the divide folding; `t1`/`t2` fabs temporaries, the `BOOL a, b` order in `update` and the pointer step order in the `for` header were found by search. `FastCast` is an `asm` block.
- Round 15, `fn_8026FE48`: the `(s32)*(u8*)` and `*(const u8*)` reads exist to keep one compare as `cmpwi` and force a reload; the case order inside the switches was chosen to match the layout.
- Round 15, `fn_80262744`: `x = e->x44; ox = CH->x44;` reads the same field two ways only to get the `mr` copies, and the declaration order of the hoisted locals comes from `sw.py`.

## Round 17

Added 7 functions, 6784 bytes (0x1A80). All print MATCH with `python3 -I tools/check_func.py <file> --strict-references`:

| File | Function | Bytes | Contents |
|---|---|---|---|
| `fn_8027163C.cpp` | fn_8027163C | 0x810 | Conversation room: next topic entry, caption objects, seven inlined `setText` (std::string assign) |
| `fn_802644CC.cpp` | fn_802644CC | 0xA24 | Dictionary list page frame and text lines (old wip, 9 words) |
| `fn_8027F368.cpp` | fn_8027F368 | 0x3C0 | Text-run vector of 8-byte items, push_back inlined (old wip, 15 lines) |
| `fn_8027F84C.cpp` | fn_8027F84C | 0x164 | Proc with an 8-byte-item vector, reserve(0x50) inlined (old wip, 42) |
| `fn_80287188.cpp` | fn_80287188 | 0x1D0 | Same reserve, second proc (old wip, 42) |
| `fn_80280DF8.cpp` | fn_80280DF8 | 0x64 | Create a proc unless the boot string matches (old wip, 1 extra word) |
| `fn_80280CB4.cpp` | fn_80280CB4 | 0xF4 | Countdown bars: state block and window/deadcount.cms (old wip, 2) |

New or improved `wip/` near misses (comment in each file): `fn_802828B4_r17.cpp` (31 positional, the 0x1A flag term is solved), `fn_8027C5CC_r17.cpp` (2 words), `fn_80270348_r17.cpp` (26 lines, from 38), `fn_80287358.cpp` (93 lines, registers only), `fn_8026E9DC.cpp` (95 lines, fresh), `fn_802811E8.cpp` (225 lines, registers only, fresh), `fn_80280060_r17.cpp` (16 lines). The older wip copies of the matched functions are left as they were.

Lessons:
- **Assignment in the loop condition** (`if (k >= (st = lbl_804CC004)->listCount) break;`) swapped two volatile registers in a loop that no declaration or statement order fixed (fn_802644CC, 9 words to 0).
- **A const accessor in a `while` test** (`while (idx(r) < tbl[0])` with `idx(const Room*)`) keeps the body from reusing the test's load of the same field; the original reloads it at the top of the body.
- **Named `Empty e;` versus `Empty()`:** the named tag put the temp/copy slot pair the original way round in `setText`; the temporary mirrored it.
- **Inline locals:** in `setText(Side* o, key)`, declaring `const char* s;` before `Txt* t = o->x60;` and assigning after gave the r27/r28 split; the other order swapped every site.
- **`new` of an inline-constructed object:** read the constructor arguments inside `if (p)` after the allocation (`newCap(Room* r)` reads `r->x40` there); passing them as parameters loads them before the call.
- **The vector length error string is a pooled literal.** `lis`/`addi` bases for `__files` and the pool swapped ranks until `"vector length error"` was a real literal under `pool_strings` (with a `StringPool` dump of the pool's earlier strings, fn_8027F368). Same fix lowered fn_80287358 from 99 to 93.
- **Element copies:** `struct W2a { u32 w[2]; }` copied by `*(W2a*)d = *(const W2a*)s` gives `lwz;lwz;stw;stw` (fn_8027F368, fn_8027F84C). For 24-byte items stored high word first (`stw 4; stw 0`), `u64` members did it and kept a local element scalar-replaced (a nested `W2` member stops scalar replacement and grows the frame).
- **vector::clear without folding:** `size -= ((u8*)data + size) - (u8*)data` gives `subf rX,rY,rY`, as in fn_8027F7DC; a typed `T*` difference adds `srawi/addze`.
- **push_back that keeps the capacity in a register:** when the vector is a local, `n = v->size + 1 - c` and `c += Max(...)` on the same variable reproduce one register for old and new capacity; on a heap object the rS form (`v->cap` reloaded) is right.
- **A store after `if (p) { ... }` that runs even when p is null** (`p->m38 = 0;` outside the if) fixed both the branch target and the epilogue order of fn_8027F84C.
- **Dead compare after a call:** `if (p == 0) return;` as the last statement keeps `cmpwi r3,0` with no branch.
- **Prototype types for in-place `extsh`:** `s16` parameters on fn_8027FD08 gave `lwz r5; extsh r5,r5` (fn_80280060).
- **`int k = 4` passed as both float and int argument** to fn_8017F68C stays in a saved register in our build, while the original reloads `li r3,4` after the call and converts it; every spelling tried (block locals, inline locals and parameters, `const int&`, s16) failed. This blocks fn_8026E9DC.
- **By-reference per-site locals rank below everything** in fn_8028530C (all of them went to r20/r21), so they cannot raise a value's rank; that function stays at 41.
- Dead ends this round: fn_8028B84C (14 spellings of the m28 block), fn_80260140 first lookup block, fn_8027ECA4 hoisted `lis`, fn_80260E58 page moves, fn_8027ACDC/AF54 with pooled literals (same 29/26 words).

Matches that may not reflect the source:
- fn_8027163C: `idx(const Room*)` exists only to stop the CSE of `x3C`; the `Cap`/`Txt`/`Side` layouts and the vtable stores (`lbl_80392768`, `lbl_80392750`) are inferred; `Obj` has a declared virtual destructor only so `delete` calls slot 8.
- fn_8027F368, fn_80280CB4: `StringPool` is the documented dump of the real pool strings (lbl_8037387C, lbl_803738BC); the weak `__dt__11SplitBufferFv` in fn_8027F368's object shows as SKIP. `(buf.first + buf.start)[buf.size] = x;` before `d = ...` is spelled for the add operand order.
- fn_8027F84C, fn_80287188: `W2a` word copy, the `(u8*)` difference in `vecClear`, and the declaration order of `s`, `d`, `e` come from search; the original surely used a template vector.
- fn_802644CC: the assignment inside the loop test is the only change from the old wip.
- fn_80280DF8: the empty `if (p == 0) return;` stands in for whatever the original did with the result.

## Round 18 (functionally-equal level)

No new exact matches. 10 functions, 15,272 bytes (0x3BA8), at `regs`/`renamed` level as self-contained files in `equiv/`.
Check: `python3 -I tools/check_regs.py equiv/<file> --extra "-i src/game/rN_8025EEF0 -i src/game/rN_8025EEF0/wip"`.

| File | Function | Bytes | Class | Contents / source |
|---|---|---|---|---|
| `equiv/fn_8027970C.cpp` | fn_8027970C | 0x15D0 | regs | Conversation room (Fe8): support pair list draw. New, written from the asm |
| `equiv/fn_80261728.cpp` | fn_80261728 | 0x101C | regs | Dictionary: entry list input. New, written from the asm |
| `equiv/fn_80283BC8.cpp` | fn_80283BC8 | 0x618 | regs | Unit record list: collect, sort, portraits. New, written from the asm |
| `equiv/fn_802811E8.cpp` | fn_802811E8 | 0x714 | regs | r17 wip; `s8 b8` (`li -1`) and `lbl_804CA798[8]` (sda21) |
| `equiv/fn_80263418.cpp` | fn_80263418 | 0x2D8 | regs | wip fragment + helpers of `fn_80263418.cpp` |
| `equiv/fn_80271434.cpp` | fn_80271434 | 0x208 | regs | wip; sign flip as `side == 0 ? r : -r` |
| `equiv/fn_8027247C.cpp` | fn_8027247C | 0x1A8 | regs | wip fragment + helpers of `fn_80272624.cpp` |
| `equiv/fn_8026A864.cpp` | fn_8026A864 | 0xE8 | renamed | wip fragment + helpers of `fn_8026A724.cpp` |
| `equiv/fn_8026AB7C.cpp` | fn_8026AB7C | 0xA4 | renamed | wip fragment (`fn_8026A9D4.cpp`) + same helpers |
| `equiv/fn_8025F0E8.cpp` | fn_8025F0E8 | 0x7C | regs | wip fragment (`fn_8025F068.cpp`) + helpers of `fn_8025EEF0.cpp` |

Lessons:
- **fn_8027970C** is fn_80277E10 without the title box and with a 0x2C-byte pair record; with `roomdraw.h` it took six
  compiles. One x variable accumulates across the row (`px = width + px + 6`), the flag colour is a `u8`, and
  `tx = x + 0xC` has to be written inside the loop so it is hoisted after the pool base.
- **fn_80261728:** the scroll helper takes the start value by value (`scrollTo(q->f10, v, t)`: the load comes before the
  clamp) and the maximum is a macro evaluated twice (`if (v > MAXSC) v = MAXSC;` converts `count - 9` twice).
  Comparison operand order follows the source: `q->cur > (int)q->f18 + 6`.
- **fn_80283BC8:** the frame has no room for an element temporary, so `push_back` takes the two words separately and
  stores through one element pointer; the backward move is `if (d) *(W2a*)d = *(const W2a*)e;` (load, load, store,
  store without forcing a stack copy elsewhere). In the bubble sort the class byte must not be a named local
  (`TY(a)` repeated: the compiler temp takes r0, which keeps the data pointer out of an update-form store), the element
  offset is an explicit `jo` stepped after `j`, and the swap is a plain three-assignment struct swap through
  `o->v.data`. The last loop reads `n = o->x78` in its condition.
- **`bne A; b B; A: fneg`** is `c == 0 ? r : -r`; `c != 0 ? -r : r` and the if/else forms give `beq`.
- **`li rN,-1` stored with `stb`** means the field is `s8`; **`li r4,sym@sda21`** needs the extern declared with its real
  small size (`char lbl[8]`), an unsized array gives `lis/addi`.

Still `other` in wip/: fn_8026D73C, fn_80270348 (20 lines: three load/step orders per half), fn_80289214, fn_802818FC,
fn_8026E9DC (the `li r3,4` reload), fn_80280060 (float argument load order), fn_80282FF4, fn_80287358 (stack slots of
two saved words), fn_802828B4, fn_8027B144, fn_80280F1C, fn_80266024, fn_802662EC (only two `lfs` swapped), fn_80264204,
fn_802836C0, fn_80283528, fn_802643B8, fn_80263D18, fn_80263DE0, fn_8026A9D4, fn_8026806C, fn_8025F068, fn_8026FC38.
Every function of this region now has a draft.

Caveats: fn_80283BC8's two-argument `push_back`, raw `W2a` move and macro-repeated class test are spellings that
reproduce the code, not the original template vector; `(u16)(n - i - 1)` reproduces a 16-bit index mask. fn_8027970C's
`Fe8Item`/`Fe8St` layouts and field meanings are inferred; `lbl_8037359C + 0x46..0x4C` are pool offsets kept as
extern arithmetic like `room.h`. fn_80261728 reuses `DS`/`sync()` from wip/fn_80260E58.cpp and declares its own `PG`
and `D2` views of the state blocks. `regs` means same instructions, order and references with different registers;
it is not a proof.

## Round 19

No new exact matches and nothing newly written. 14 functions moved to `equiv/` (14,732 bytes): 1 at `regs`, 13 at the
new `sched` level (same instructions per basic block, order differs). Check:
`python3 -I tools/check_regs.py equiv/<file> --extra "-i src/game/rN_8025EEF0 -i src/game/rN_8025EEF0/wip"`.

| File | Function | Bytes | Class | What differs / source |
|---|---|---|---|---|
| `equiv/fn_802818FC.cpp` | fn_802818FC | 0xE10 | regs | wip with the eight gradient colours set to the original bytes |
| `equiv/fn_80270348.cpp` | fn_80270348 | 0x1058 | sched | wip r17; `lha` pairs and `li`/`srawi` per half |
| `equiv/fn_80280060.cpp` | fn_80280060 | 0x930 | sched | wip r17; four `lha r3,2(r3)` one slot apart |
| `equiv/fn_802828B4.cpp` | fn_802828B4 | 0x44C | sched | wip r17; one `li`, one `srwi`, one `sth` |
| `equiv/fn_80280F1C.cpp` | fn_80280F1C | 0x2CC | sched | `stb` against `fsubs` |
| `equiv/fn_80283528.cpp` | fn_802836C0, fn_80283528 | 0x26C, 0x144 | sched | `lha`/`ori`/`li` order, one `sth` |
| `equiv/fn_802662EC.cpp` | fn_802662EC | 0x260 | sched | the two swapped `lfs` (0.0f and 255.0f) of the second easing call |
| `equiv/fn_80264204.cpp` | fn_80264204 | 0x1B4 | sched | copy of wip/fn_80264034.cpp; two `lwzx` |
| `equiv/fn_802643B8.cpp` | fn_802643B8 | 0x114 | sched | fragment + helpers of fn_80263418.cpp; `addi`/`cmpwi` |
| `equiv/fn_80263D18.cpp` | fn_80263D18, fn_80263DE0 | 0xC8, 0x7C | sched | fragment + helpers of fn_80263418.cpp; see caveat |
| `equiv/fn_8026806C.cpp` | fn_8026806C | 0x90 | sched | fragment + helpers of fn_80266E3C.cpp; `lha` above `stwu` |
| `equiv/fn_8025F068.cpp` | fn_8025F068 | 0x30 | sched | fragment + helpers of fn_8025EEF0.cpp; one `lfd` |

Notes:
- **fn_802818FC:** the wip had eight placeholder colours, all 0xFFFFFFFF, as file statics, which the checker cannot
  tie to `lbl_804D0830`. The original bytes are FFFFFFFF x2, FFFFFF00 x4, FFFFFFFF x2; with them (k00 = +0xC, k01 = +8,
  k02 = +4, k03 = +0, k10 = +0x1C ... k13 = +0x10) the constants are verified by value and the class is `regs`. Other
  drafts with file-static constants deserve the same look before being trusted.
- **fn_80263D18 / fn_80263DE0:** ours reads the next source character before storing the line terminator, the
  original after. This is only the same if the line buffers never overlap the source text.
- **fn_802662EC:** an inline wrapper with reversed parameters (the fix for the same symptom in rF's fn_801805E0) did not
  move the loads here; the bias double of the second call wants f2 because f1 still holds the first result.

Still `other` in wip/: fn_8026D73C, fn_80289214, fn_8026E9DC, fn_80282FF4, fn_80287358, fn_8027B144, fn_80266024,
fn_8026A9D4 (self-contained with fn_8026A724.cpp's helpers it is one `li r28/r29,0` away, but not `sched`),
fn_8026FC38 (same size, block contents differ). None of these was worked on this round.

Caveats: `sched` is weaker evidence than `regs` (dependencies between moved instructions are not checked by the tool;
each diff here was read by hand and is loads, constants or independent stores, except the fn_80263D18 pair above).
The equiv copies keep the spellings of their wip sources, including hand word copies of colours.

## Round 20

One exact match and four functions newly in `equiv/` (13,372 bytes). Check:
`python3 -I tools/check_regs.py <file> --extra "-i src/game/rN_8025EEF0 -i src/game/rN_8025EEF0/wip"`.

| File | Function | Bytes | Class | What changed |
|---|---|---|---|---|
| `fn_8027B144.cpp` | fn_8027B144 | 0x424 | exact | easing prototype (below) |
| `equiv/fn_8026D73C.cpp` | fn_8026D73C | 0x12A0 | sched | two swapped prototypes and eight placeholder colours fixed |
| `equiv/fn_80289214.cpp` | fn_80289214 | 0xE5C | sched | one shared zero colour word declared after `xa = 0`; two `(s16)` casts swapped |
| `equiv/fn_8026E9DC.cpp` | fn_8026E9DC | 0xC54 | regs | easing prototype; 77 words |
| `equiv/fn_80266024.cpp` | fn_80266024 | 0x2C8 | regs | integer-first fn_801BC88C prototype, ternary in the call, wrong constant fixed |

**The `li r3,4` puzzle (open since round 17) is solved.** fn_8017F68C is `(int mode, f32 from, f32 to, f32 t, f32 dur)`,
as rF declares it, not `(f32, f32, f32, f32, int)`. With `k = 4; fn_8017F68C(k, a, b, t, k)` the constant sits in r3
and is converted from there for each call. fn_8027B144 matched on the first compile and fn_8026E9DC went to `regs`.
Other files of this region still use the old prototype (register passing is the same, so their matches stand); a
port should use the mode-first form. `#pragma opt_propagation off` gets close with the old prototype (two `li` per
call) and `fn(a, b, t, k, k = 4)` even classes as `sched`, but that one converts `k` before assigning it: a false
positive of the `sched` class.

Real bugs found in old drafts:
- fn_8026D73C: `fn_80179888(void*, u8)` / `fn_80179A7C(void*, int)` were the wrong way round (it is `int` and `u8`),
  so the scroll offset `28.0f * m148` was cut to 8 bits. The eight gradient colours were all FFFFFFFF; the original
  bytes at lbl_804D04E8+8.. are 3C3C3CFF, 000000FF, 3C3C3CFF, 000000FF, then four times 000000FF.
- fn_80266024: the last call is `fn_801BCA5C(1.0f)`, the draft had 0.0f.
- fn_80289214: the second line of a two-line left column is drawn at `(s16)(y + 0x14)` and the centred one at
  `(s16)y + 0x14`; the draft had them swapped (same value unless y overflows 16 bits).

Still `other`:
- fn_80282FF4 (wip unchanged): `(s16)yy` in the first text call fixes one hunk. What is left: the original adds
  `off + y` (y not sign-extended) again for each of the two button texts, ours computes `off + (s16)y` once before
  them. Tried: `int` x/y with explicit casts (removes the extension but not the sharing, and needs casts at every
  other use), inline forms of YF (worse), `s16 off`.
- fn_80287358 (wip unchanged): one instruction short. In the bubble sort the original reloads the vector's data
  pointer from the stack (`lwz r4,0x34(r1)`) for the second store, and two saved words go to swapped slots.
- fn_8026A9D4, fn_8026FC38: fragments, not touched.

Caveats: `equiv/fn_80266024.cpp` and the other new files keep hand word copies of colours from their wip sources.
`equiv/fn_8026D73C.cpp` and `equiv/fn_80289214.cpp` hold their colour constants as file statics with the original
bytes (verified by value). All five files were run through `src/game/rF_8017F400/r20_symcheck.py --anon` (per-block
symbolic comparison, described in rF's NOTES_round20.md): no block differs, apart from operand order of commutative
operations.
