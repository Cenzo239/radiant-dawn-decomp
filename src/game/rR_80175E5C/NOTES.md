# Region rR_80175E5C (0x80175E5C..0x8017F3F0 and 0x801D0A40..0x801DCE18)

The region has 349 functions, 0x1596C bytes. 173 of them were already matched by script under `src/game/auto` (`build/m2c/matched_names.txt`), and the 176 left came to 0x135FC bytes. This directory matches 104 of those, 0x74E8 bytes (29,928). Each `.cpp` prints `MATCH` with `python3 -I tools/check_func.py <file> -v`. None of the 104 duplicates a name in `matched_names.txt`.

| File | Matches | Bytes | Contents |
|---|---|---|---|
| `fn_80175E7C.cpp` | 19 | 0x5E8 | Small process helpers, text panel, wallpaper object |
| `fn_801D0A40.cpp` | 22 | 0xD0C | Title process teardown and asset loading, event lookup by name |
| `fn_801D0EC0.cpp` | 4 | 0x15B0 | Event script bytecode interpreter and native call |
| `fn_801D41FC.cpp` | 21 | 0x1694 | Title menu items, menu input dispatch, widget helpers |
| `fn_801D60D0.cpp` | 9 | 0xC4C | Window sheet sprite primitives |
| `fn_801D772C.cpp` | 29 | 0x2964 | Window parts built from those primitives |

Headers: `types.h` (`Rect`, `Color`, Prim2D prototypes), `rects.h` (all the sprite rectangles), `menu.h` (copied from `rK_800CF8BC`).

## Subsystems and layouts (names are guessed)

- **Script VM** (`VM`, global at `lbl_8041EEB8`): +0 stack base, +8 current function, +0xC pc, +0x10 top of globals, +0x14 locals, +0x18 sp, +0x1C s8 halt, +0x1D s8 argc, +0x1E, +0x1F s8. `fn_801D0EC0` runs 72 opcodes. Case bodies are in the source order given by `jumptable_8038AFA8`, not numeric order. Globals are at `lbl_804CB6A8`.
- **Script function** (`fn_801D0D58`): +4 code or native pointer, +8 module, +0xC kind (0x10 is a named function), +0xD s8 argc, +0x12 s16 local count, +0x14 name index. The module has +0x20 globals base, +0x24 string base, +0x28 function table.
- **Call frame:** four words after the locals: pc, fn, globals top, locals.
- **Native calls** (`fn_801D20D4`): a jump table on argc 0 to 9, each calling +4 with that many stack values.
- **Window sprites:** `Rect` is {x0, y0, x1, y1} as s16 in sdata from 0x804CBA90 to 0x804CBDF0. `fn_80006A64(sheet, lbl_8041EF60, index)` selects the sprite. The primitive flip argument is 1 horizontal, 2 vertical, 0x100 and 0x200 for the other two transforms.
- **Sheets:** `lbl_804CBDF8` to `lbl_804CBE08`, loaded by `fn_801D5DFC`, with a reference count at `lbl_804CBE0C`.
- **Title process** (`TitleP`, script `lbl_8038B160`): +0x40 music name, +0x44 and +0x48 file handles, +0x4C and +0x50 menus, +0x54 reference-counted widget.
- **Menu definition objects** (0x20 bytes): vtable at +0, second vtable at +4, then s16 x, y, w and more, f32 at +0x18. Lazy static vtable pairs sit from `lbl_804CB9F8` to `lbl_804CBA84`.
- **Text widget:** vptr at +0, s16 rect at +0xA, +0x38 flags, +0x40 a string whose top bit means heap (+0x48), otherwise inline at +0x41. +0x4C alignment, +0x54 scale.

## Near misses in `wip/`

This section and the resume point below date from round 5. See "Round 12" for the current state. Each has a comment with the words that differ. They aren't compiled and use the declarations of the matching `.cpp`.

| Words | Functions | What's left |
|---|---|---|
| 2 | fn_80177418 | one temporary register |
| 3 | fn_801DB3F4 | `fill` should share r28 with `mid`, but takes r23 once x is dead |
| 5 | fn_80176B0C, fn_8017E30C | `fmr`/`frsp` order; register of the first field read |
| 6 | fn_801DBD98 | stack slots of the two int-to-float temporaries |
| 14 | fn_801D65EC | register of the word copy in `Swap`, and argument address order |
| 15 to 18 | fn_801DA184, fn_80179660, fn_801D2AC0 | register order; `Color` stack copy kept; `bne; b` shape |
| 25 | fn_801D7014 | only r16 and r17 swapped |
| 28 | fn_801D0D58 | the original doesn't fold the pushes into offsets from one register |
| 36 | fn_801D7D38 | register rotation |
| 84 and up | fn_8017948C, fn_801D5914, fn_801D820C, fn_801DAEF4 | see below |

- fn_801DAEF4 and fn_801DC2B0 (0x500 each) need two fewer saved registers. Their second half really is an inlined nine-slice.
- fn_8017948C and fn_801D820C load constant colours as `lbz lbl+N@sda21` per byte. An extern array gets a hoisted base register, so a real `static const` POD colour is the thing to try.
- fn_801D5914 has empty `case 0` and range-switch branches I couldn't keep, plus an extra `extsh` on x.

## Resume point

Not attempted, biggest first: `fn_8017B638` (0xB18), `fn_8017C40C`, `fn_80178364`, `fn_8017A188`, `fn_80179A84`, `fn_801DA800`, `fn_801D9818`, `fn_80177A5C`, `fn_8017E470`, `fn_8017B160`, `fn_8017659C`, `fn_8017751C`, `fn_8017ABE4`, `fn_8017CD80`, `fn_8017D428`, `fn_8017EA78`, `fn_801D2744`. Attempting them needs a check of which ones are really paired-single: the `ps` flag in my scan also fires on the `psq_st` that only saves f31, as it did for the fn_801D41FC family. Cheap next: `fn_801D7574` (static gradient tables), `fn_801D77BC`, `fn_801DC7B0`, `fn_801DC984`, `fn_801DCB44`, `fn_801D5BB0`, `fn_801798A8`, `fn_8017E25C`, `fn_8017E9E0`, `fn_8017F194`.

## What may not reflect the original source

- All names outside `fn_` and `lbl_` are mine, and prototypes outside the region are guessed from call sites.
- `fn_801D772C.cpp` declares the primitives with s16 and u16 arguments while `fn_801D60D0.cpp` defines them with int, because the callers extend and the callees don't. They're in separate files for that reason, which says nothing about real translation units.
- `Color` has a user copy constructor and `operator=`, chosen to get byte copies. `Color(col)` at call sites only forces a temporary.
- `*(volatile u32*)&lbl_804CB878`, `extern volatile u32 lbl_804CB700` and `const volatile u8* q` in fn_80177FCC force reloads. These globals probably aren't volatile.
- `#define Push/Pop/Fetch8`, and `Fetch16_`/`Fetch32_`, are how the VM matched, but the real source may have used member inlines. Local `k` temporaries in the VM cases and the `(u8*)(k + (int)vm->pc - 2)` cast only fix operand order.
- `int` locals such as `nx`, `by` and `x2` next to s16 values are what produces `extsh` at each use. They may really be inline parameters.
- `MENUDEF`, `HELPITEM`, `ONE`, `WAVE`, `TITLE_END`, `MENU0` and `LAZY` are my macros for repeated code. The original probably used constructors and inlines.
- `MusicOut` is an inline split I chose.
- Declaration orders in several functions came from trial and say nothing about the source. `goto` in the switch of fn_801D0EC0 (`common`) stands for whatever made the shared return block.

## Round 12

This round adds 46 matches, 0x5C54 bytes (23,636), so the directory now holds 150 matches. The region has 26 functions left, about 25.8 KB. None of the 46 duplicates a name in `matched_names.txt`.

| File | Matches | Bytes | Contents |
|---|---|---|---|
| `fn_801762B4.cpp` | 3 | 0x740 | GX quads through the write-gather pipe, copy-filter setup |
| `fn_80176B0C.cpp` | 4 | 0x14C | Widget counter, palette refresh, null u64, position setter |
| `fn_80176F7C.cpp` | 2 | 0x638 | Signed number text, digit sprites |
| `fn_80177270.cpp` | 9 | 0xAC0 | Sword trail ribbon (`Trail`, `Seg`, `Vtx`) |
| `fn_80179214.cpp` | 4 | 0x634 | Scroll arrows |
| `fn_8017A188.cpp` | 4 | 0xBAC | Letterbox panel (`Panel`, `Str`), colour fade |
| `fn_8017B160.cpp` | 9 | 0x1100 | Screen filters, wave effect, palette setup |
| `fn_801D74B4.cpp` | 5 | 0x8CC | Window frames and a three-band gradient |
| `fn_801D7014.cpp` | 3 | 0x718 | Window parts with `int` flags |
| `fn_801D9818.cpp` | 1 | 0x60C | Tab column |
| `fn_801DAEF4.cpp` | 2 | 0xA00 | Big window; the second function differs only in two constants |

`strpool.h` holds a scaffolding `StringPool` that fixes the offsets of the pool at `lbl_8036B4C8`. It isn't game code.

Near misses added to `wip/`. Each has a comment and none overwrites an older file:

| Words | Function |
|---|---|
| 2 | `fn_801DB3F4` |
| 5 | `fn_80176B0C` |
| 9 | `fn_8017B638`, `fn_801DA800` |
| 12 | `fn_8017B040` |

The older `wip/` files still contain functions that now match: fn_80177418, fn_801DBD98, fn_8017E30C, fn_80179660, fn_8017948C, fn_801D7014, fn_801DA184, fn_801DAEF4. The `.cpp` files win over those copies.

Not attempted this round, biggest first: `fn_8017C40C`, `fn_80178364`, `fn_80179A84`, `fn_80177A5C`, `fn_8017E470`, `fn_8017ABE4`, `fn_8017D428`, `fn_8017EA78`, `fn_8017DECC`, `fn_8017EE1C`, `fn_801D2744`, `fn_80175FF4`, `fn_80175E7C`. `fn_80179A84` needs a class with its vptr at +0x28. `fn_80178364` is Catmull-Rom interpolation plus UV generation.

### Layouts (names are guessed)

- **Trail:** +0x30 archive, +0x34 texture, +0x38 and +0x3C colours, +0x40 `Seg` ring, +0x44 `Vtx` array, +0x48 head, +0x4A vertex count, +0x4C count, +0x4E capacity, +0x50 flags, +0x52 subdivisions, +0x55 fade, +0x58 and +0x60 joint names.
- **Filter:** +0 base, +4 to +0x10 buffer offsets, +0x24 mode, +0x25 and +0x26 alpha factors, +0x27 pass count, +0x28 s16 parameter, +0x2B colour. Modes come from the Shift-JIS names in the pool: blur, bokeh, cross-fade, glow, gray, zoom in and out, depth of field, invert, wave, sepia.
- **Panel `Str`:** the top bit of the first word means heap, with the length at +4 and the pointer at +8. Otherwise the length is byte 0 and the text starts at byte 1.

### What may not reflect the original source, round 12

- `const C4& c = White();` in fn_8017CD80 binds to a local of a finished inline. That dangling reference exists only to get the stack slot.
- fn_80178DB4 is written out with named `Vec` slots, `GetFn` casts and `W3` word copies, because its stack is the exact mirror of fn_801780B8. The original is probably fn_801780B8 inlined, but inlining it gave the wrong slots.
- `*(u32*)&col[i] = w` in `wip/fn_8017B638.cpp`, `*(u32*)&v.x = 0` in fn_8017E3B4 and `*(C4*)&lbl_804CA7C0` force word copies, dead stores and byte reads.
- One-line wrappers around `Body_fn_801DAEF4` and `In` exist only to set parameter registers. `dy` and `dh` on the body are how I share one source between two functions.
- `int fl` parameters in `fn_801D7014.cpp` and `fn_801DAEF4.cpp` next to `u16` in older files: the real type is unknown.
- `fn_8017C2F4`, `fn_8017D1DC` and others use real string literals, and `@stringBase0` in the object stands for `lbl_8036B4C8`. The checker compares the values.
- Declaration orders from `sw.py` say nothing about the source.

## Compiler lessons from this region

- **Jump table order is source order.** Sorting a dense table's targets by address gives the case order to write. Reordering took the interpreter from 460 differing diff lines to 169.
- **`*vm->sp++ = v` versus a push inline:** the postincrement form schedules `addi` before the value load and matches. An inline that writes `*sp = v; sp++` reloads the pointer.
- **Assign to a parameter, not a new local,** when the asm's new value lands in the parameter's register: `x += 0x69;` fixed a whole-function rotation that declaration order couldn't.
- **`const Color&` parameters, not by-value,** when callers pass a pointer directly with no temporary.
- **Pointer plus int always puts the pointer first.** To get `add rD, rK, rPc`, cast the pointer to int.
- **Passing through arguments:** `mr r4, r31` right after a call with `r3` untouched is a call whose first argument is the previous result.
- **`strcpy` needs its real return type** to stay a call.

## Round 15

2 more functions match (0xF28 bytes): `fn_8017B638.cpp` (screen filter draw, 0xB18; the old 9-word near miss is fixed by passing `o->base + o->c` directly as the argument in the three blur loops instead of the named `tex`, with `tw`/`th` as the size arguments) and `fn_8017ABE4.cpp` (filter setup, 0x410).

Caveats: in `fn_8017ABE4` the tint colour is a non-const file static `kTint` (checked by value), where the original reads `lbl_804CE4E0+4` in .sdata2. A const static or an indexed extern each changed the load schedule. `SetCol0`/`SetCol` are wrapper depth only, for the stack slot.

Near miss added: `wip/fn_8017EA78.cpp` (colour fade start; one extra dead byte store). It uses an 8-byte `struct { int k; int z; }` for the search key only to get the key above the two colour pairs on the stack.

## Round 17

3 more functions match (0x770 bytes, 1,904), one file each, all `MATCH` with `--strict-references`:

| File | Bytes | Contents |
|---|---|---|
| `fn_8017794C.cpp` | 0x110 | Trail setup: archive, joint names, defaults, trail colour from `lbl_804CE470` |
| `fn_8017DECC.cpp` | 0x34C | Light fade step: three-state interpolation, then position, range and two scaled colours |
| `fn_8017EE1C.cpp` | 0x31C | Colour fade step (`Fade` of fn_8017F194): delay, eased lerp, finish when target equals max |

Near miss added: `wip/r17_fn_8017E470.cpp` (8 of 347 words; the two-channel version of fn_8017EE1C, only the first `Eq` call's two stack slots are swapped). `wip/fn_8017EA78.cpp` is unchanged; writing the second colour without its blue byte (`t.b.r/g/a = ...` and `bb` from `o->c54.b`) removes the dead store but leaves 10 register words, which is no better.

Caveats: `lbl_804CE470` is read through a non-const `extern C4` although it lives in `.sdata2`; const or a static const hoists the byte loads above the field stores. `Ease(t, n)` exists only to load `dur` before `t`. In fn_8017DECC the empty `case 3:` reproduces the pivot-2 switch layout (state 3 is set by case 1, so it is plausible). `Lerp(C4 from, C4 to, f32 k)` and `Eq` taking colours by value are inferred from the stack copies.

Lessons:
- **Unexplained live register before a call is an argument:** `fn_8001EF44` takes `(int total, int cur, f32, f32)`; a `addi r4` that looked like a register choice was the second argument (`o->cnt++` then pass `o->cnt`).
- **By-value C4 arguments into inlines:** the first parameter lands in the higher slot. A two-colour struct parameter instead puts the 8-byte copy above the return temp; splitting it into two `C4` parameters fixed the slot order of fn_8017EE1C at once.
- **Return slots:** `o->cur = Lerp(...)` with a `C4` return gives the `lwz/stw` word copy then a bytewise store, i.e. the "local, copy, bytes" pattern.
- **Byte equality chains** (`cmplw; beq; li r0,0; b` and a final `cntlzw`) come from `if (a.r != b.r) return 0; ... return a.a == b.a;`, not `&&`. Two of them combined match as `BOOL d; d = Eq(..); if (d) d = Eq(..); if (d)`.
- **Switch pivot:** `cmpwi 2; beq; bge end; cmpwi 0; beq; bge` for cases 0..2 needs an empty `case 3:`; without it the compiler pivots on 1.

## Round 18 (goal changed: exact, or functionally equal in `equiv/`)

From this round a function is done at one of two levels: exact (`check_func.py --strict-references` prints MATCH, file in this folder) or functionally equal (`check_regs.py <file> --extra "-i src/game/rR_80175E5C -i src/game/rR_80175E5C/wip"` prints `renamed` or `regs`, file in `equiv/`). Every `equiv/` file compiles on its own.

Exact (2 functions, 1,080 bytes):

| File | Bytes | Contents |
|---|---|---|
| `fn_80175FF4.cpp` | 0x2C0 | Closest point between two lines and whether it lies inside both segments. `Perp` is an inline inferred from two identical blocks. |
| `fn_80175E7C_b.cpp` | 0x178 | fn_80175E7C: blend of two RGBA colours, returned as one word. The file has `_b` because `fn_80175E7C.cpp` is the older multi-function file. |

Functionally equal (2 functions, 1,680 bytes):

| File | Class | Bytes | Contents |
|---|---|---|---|
| `equiv/fn_80177A5C.cpp` | renamed | 0x570 | Trail events 0xC8..0xD3 (alpha and nine preset colours) |
| `equiv/fn_8017B040.cpp` | regs | 0x120 | Filter fade-in, from `wip/fn_8017B040.cpp` |

Written this round, still class `other`: `wip/r18_fn_8017D428.cpp` (wave filter step, 0x3B0). The setup and the whole 32x32 simulation loop match; in the texture write loop the original adds `(i>>2)*16 + (i&3)` before the row term and keeps a dead `srawi`, ours adds the row term first (about 35 index spellings).

Checked, still `other`: 8017E470 (the two by-value colours of the first `Eq` call sit in swapped slots; argument order, wrappers, named locals, accessor inlines all tried: each either moves other slots or changes the load order), 8017EA78 (one dead byte store too many, or without it one load pair scheduled differently), 80176B0C (0x48 bytes, `frsp`/`fmr` shape). Not attempted: 8017C40C, 80178364, 80179A84 (each about 2 KB of float code). The functions at 0x801D0A40 and up (801D0D58, 801D2744, 801D2AC0, 801D5914, 801D5BB0, 801D65EC, 801D820C) were left alone: another agent placed 801D7D38 and 801DA800 in `rF_8017F400/equiv/` this round, so check there before starting one. The five with drafts all compile to class `other` with their parent files.

Caveats for a port:
- `equiv/fn_80177A5C.cpp` holds the nine preset colours as non-const file statics `kCol1..kCol9` (values checked against the DOL). The original reads `lbl_804CE470+4..+0x27`, one const table in `.sdata2` whose entry 0 is the default used by fn_8017794C. A port should use one const table of ten colours. An indexed extern or const statics hoist the loads out of the loop.
- `fn_80175FF4` takes non-const `Vec*` parameters on purpose (see the lesson).

Lessons:
- `const T*` parameters let the compiler load all three floats of `*out = *a` before the stores; with plain `T*` it keeps load/store pairs. That was the only difference between `other` and an exact match of fn_80175FF4.
- An inline's locals are laid out with the last declaration highest, so declare them in reverse stack order (`t`, `b`, `a` for slots 0x2C, 0x38, 0x44).
- `len = f(n); r = 0.0f; if (r == len) return r;` gives the `lfs` after the call and the `bne; b` shape.

## Round 20

Levels as in `docs/MATCHING.md`; all files below are self-contained and were re-checked with `tools/check_regs.py <file> --extra "-i src/game/rR_80175E5C -i src/game/rR_80175E5C/wip"`.

**Exact (1 function, 0x704 bytes):** `fn_80179A84.cpp`, the text panel's scroll bar (arrows, track, thumb), `MATCH` with `check_func.py --strict-references`. New, from the disassembly.

**New functionally equal (2 functions, 0xCD8 bytes), in `equiv/`:**

| File | Bytes | Class | Notes |
|---|---|---|---|
| `fn_80178364` | 0x934 | regs | New, from the disassembly. Trail update: spline resampling of the segment ring, smoothing, alpha and texture coordinate by arc length |
| `fn_8017EA78` | 0x3A4 | sched | `wip/fn_8017EA78.cpp` with the second colour copied field by field (removes the extra dead store) |

**Copied from `wip/` (already listed in `docs/EQUIVALENT.tsv`):** `equiv/fn_8017E470.cpp` (0x56C, sched: the two by-value colours of the first symmetric `Eq` call sit in swapped slots), `equiv/fn_801DB3F4.cpp` (0x37C, regs).

**Not done:** `fn_8017C40C` (0x974, not written: its texture write loop has the same dead `srawi` as `fn_8017D428` and `fn_80143908`, so it cannot reach a counted level until that is solved), `fn_8017D428` (unchanged, `wip/r18_fn_8017D428.cpp`).

**Caveats:** see the header of `equiv/fn_80178364.cpp` (fast-cast inlines, an unused `tot`, two wrappers that only place stack slots, the grey constant at `lbl_804CE470+0x28`, `fn_8000987C` declared with a pointer). `fn_80179A84.cpp` declares the bar as a class with two virtuals after its data so the vtable pointer lands at 0x28; `if (off + sz > room) sz = room - sz;` is what the original computes.

**Lessons:**
- **Call-heavy draw routines are cheap:** `fn_80179A84` (67 calls) was exact after five compiles. Order the remaining list by calls per instruction, not by size.
- **`int a = (h - K) * p / t; int b = (h - K) * q / t; int room = h - K;`** (the shared term written out, the named local last) fixed an r4/r5 swap that every declaration order of `room` kept.
- **A setter inline `Pos(a, x, y)`** loads the object pointer once for two float stores; two separate `obj->p->f = ...` statements reload it.
- **`__OSf32tou8` has a `u32` temporary:** a `u8` temporary packs with other byte locals and shifts the frame.
- **Four structs addressed from one walking pointer at +0x28, +0x50, +0x78** are an array `Pt p[4]`, not four locals.
- **`extrwi r0,r0,8,23` on a byte** is `(u32)b >> 1` stored to a `u8`; `b >> 1` gives `srawi`.
- **A 3-byte `.sdata2` constant next to byte stores** is a local initialiser `{k, k, k, expr}`.

## Round 21 (large functions without a draft)

No function reached a counted level here; one complete new draft.

**Complete draft at `other`:** `wip/r21_fn_8017C40C.cpp` (0x974, wave/heat-haze displacement texture; 597 of 605
instructions, same frame, saved registers, calls and constants). What differs: the eight dead `srawi rX,y,2` of the
original are missing (one in the outer pixel loop, seven in the unrolled left/right edge loop), the texel index
adds the row term before `(x & 3)`, and a few float loads are scheduled differently (see the file header).
Everything else, including the two table loops, the distance fall-off and the sine lookups, lines up.

**Unchanged:** `fn_8017D428` (`wip/r18_fn_8017D428.cpp`, 235 of 236, the same dead `srawi`).

**The dead `srawi` puzzle, what is now known** (about 90 compiles on both functions, all in `build/tmp`, none
kept):
- The original computes `y >> 2` (signed), leaves it unused, and forms `(y >> 2) * 0x80` directly from `y`
  (`extlwi rA,y,25,5`); the `x` side never has a dead shift. In `fn_8017C40C` it shows for the loop-invariant `j` of
  the pixel loop and for `j+1 .. j+7` of the unrolled edge loop (not for the first copy, whose row term is an
  induction variable), and not in the edge loop over `i`. So it belongs to the `y` half of the index expression,
  not to loop nesting.
- One form reproduces a dead `srawi` on the `y` side only: indexing a two-byte struct array with the index
  expression written out twice, `((P2*)d)[IX(i, j)].a = a; ((P2*)d)[IX(i, j)].b = b;`. But it also distributes the
  element size into the row term (`d + row * 2` hoisted, 235 or 579 instructions), where the original adds row and
  column first and shifts once (`slwi rN,r0,1`).
- No effect: a named `by` at inner, outer or inline level; `u32` casts and unsigned constants; `/` and `%`; `<<`
  instead of `*`; a width or stride parameter through an inline; `Row()`/`Col()` inlines; a pointer `q` or an
  `int o = IX * 2`; the index repeated per store through a `u8*`; `opt_propagation`, `opt_dead_assignments`,
  `opt_common_subs`, `opt_strength_reduction`, `opt_lifetimes`, `opt_dead_code`, `opt_loop_invariants` off.
- Next thing to try: forms that keep the struct-array duplicate (which is what leaves the shift behind) but stop
  the element scale from being distributed, e.g. the texture pointer reloaded per store as in `fn_8017C40C`
  (`lbl_804CB8CC` is re-read before each `stb`), with the index held in a temporary of another type.

**Caveats for a port:** `wip/r21_fn_8017C40C.cpp` declares the parameter record of `fn_8000DD0C` as
`f32 prm[0x2C]` (0xB0 bytes on the stack; six floats used) and the texture as `u8*`.

**Lessons:**
- **`bne A; b B; A:` around a float divide** is `inv = 0.0f == r ? 0.0f : 1.0f / r;` (the zero stays in the result
  register).
- **A per-row float term computed in the outer loop** (`f32 aj = j * frq + phx;` before the inner `for`) is not
  hoisted by the compiler when written inside the inner loop next to the per-column term; write it where the
  original computes it.
- **Both channel values as named locals before the stores** (`f32 va = ...; f32 vb = ...; t[o] = 128 + va; ...`)
  give the original's "second call before the first store" order.
- **A frame 0xA0 too small with the same locals** was the callee's output record: check the highest local's offset
  against the next save area before looking for missing variables.
