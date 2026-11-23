# Region 0x800799AC..0x80089494 notes

## Status

271 of 276 functions match, 0xE190 of 0xFAE8 bytes (90%), plus fn_80077D44 outside the region. Each file below
prints MATCH with `python3 -I tools/check_func.py <file> --strict-references -v`.

| File | Functions | Contents |
|---|---|---|
| `fn_800799AC.cpp` | 33 | CRC32, NAND save-file process, small heap block, controller field helpers |
| `fn_8007A528.cpp` | 1 | fn_8007A734: recreate the controller objects |
| `fn_8007A868.cpp` | 4 | fn_8007A528 init, fn_8007A868 per-frame probing, fn_8007B2F4 / fn_8007B458 sampling |
| `fn_8007B2F4.cpp` | 28 | Controller latch, repeat, PAD sampling, rumble, destructors of the pad subclasses |
| `fn_8007B594.cpp` | 45 | Controller accessors |
| `fn_8007C4B8.cpp` | 3 | Classic Controller and sideways Wii Remote readers, with the SDK PADClamp clamps |
| `fn_8007EB30.cpp` | 1 | Prim2D: GX state for a node's blend flags |
| `fn_8007F048.cpp` | 1 | Prim2D command dispatcher |
| `fn_8007DEE4.cpp` | 67 | Prim2D: state block, command list, quads, projection |
| `fn_8007F874.cpp` | 2 | Prim2D render pass and node draw |
| `fn_80080CD4.cpp` | 1 | Tiled quad through the GX FIFO |
| `fn_80081050.cpp` | 10 | Process system: init, create, teardown walkers |
| `fn_80081A90.cpp` | 7 | Process system: everything that inlines Proc_End |
| `fn_80082230.cpp` | 2 | Round 16: end children / end children of a class, through the member walkers in `proc_pm.h` |
| `fn_80077D44.cpp` | 1 | Round 16, outside the region: byte length of the character at s |
| `fn_80083174.cpp` | 16 | Process system: find, count, per-frame runner, goto |
| `fn_8008580C.cpp` | 49 | Process system: tree walk, script interpreter, script commands |
| `fn_80085BB0.cpp` | 1 | Tree walk from a process |
| `fn_80077360.cpp` | 10 | Outside the region: font glyph lookup by Shift-JIS code |
| `fn_80077F98.cpp` | 13 | Outside the region: the 16 game heaps, alloc and free |

Functions in a file are not always in address order: some were placed so that a helper is
defined before its caller.

**Resume point:** fn_8008A868 (5 words, `wip/fn_8008A868.cpp`), then the three Proc_End near misses in
`wip/fn_80085FC4_pm.cpp`, then the near misses in 0x80077308..0x80079990.

## Round 16

- **The Proc_End family is partly solved by member functions.** `proc_pm.h` spells unlink, the onEnd walker and the
  free walker as inline members of `ProcM : Proc` (the mark walker stays the static `mark3`). With that shape
  fn_80082230 and fn_800829CC match at once (`Proc* n` declared inside the loop). An inlined member call ranks
  `this` differently from a static inline's pointer parameter. A generated search over all 2304 member/static
  shapes of the four walker chains (per level, plus the `FREE_MID` macro form) left fn_80085FC4 (56 difflib lines),
  fn_80087F78 (49) and fn_80088948 (40) unchanged; they are saved, generated, in `wip/fn_80085FC4_pm.cpp`.
- **fn_8008A868** (glyph cache build, 0x640) was written fresh: a small binary tree (`Tree` with constructor and
  destructor at 0x28 on the stack; nodes `{left, right, parent|colour, u16 key}`), insert through fn_8008BD3C and
  fn_8008B60C, render through fn_8031C7F8, and the destructor's recursion fn_8008B730 inlined four levels. The tree
  increment had to be a member function of an iterator struct (`((It*)&n)->incr()`): as a static inline it was 197
  lines off, as a member 19. Left: the hoisted `&tree.root` and zero swap (5 words). The file's string pool is `""`
  and `"tree::insert length error"` at lbl_803630C4, dumped into a `StringPool` scaffold.
- **fn_80077D44** matched as `int n = 1; n += isSjis(s) != 0; return s + n;`; every one-expression spelling is
  reassociated.
- Tried without effect: fn_800776F8 (load order of the two code bytes: statement splits, local bytes, all
  declaration orders and types), fn_8007A1CC (argument forms of fn_802F531C).

## Near misses in `wip/`

| Function | File | Words differing | Cause |
|---|---|---|---|
| fn_8008A868 | `fn_8008A868.cpp` | 5 of 400 | hoisted &tree.root and 0 swap (r25/r26) |
| fn_80085FC4 | `fn_80085FC4_pm.cpp`, `fn_80082230.cpp` | 56 scored | p should be r29, inlined prev r28 |
| fn_80087F78 | `fn_80085FC4_pm.cpp`, `fn_80082230.cpp` | 47 scored | q should be r24, i r25 |
| fn_80088948 | `fn_80085FC4_pm.cpp`, `fn_80082230.cpp` | 40 scored | returned process should be r29 |
| fn_80079D90, fn_8007A1CC | `fn_80079D90.cpp` | 2 of 18, 9 of 69 | epilogue order; base register |
| fn_800785FC | `fn_800785FC.cpp` | 8 of 122 | the 0 and h+0x20 temporaries swap |
| fn_800787E4 | `fn_800785FC.cpp` | 84 of 274 | first key should be r8, counter r3 |
| fn_80077A58 | `fn_80077A58.cpp` | 16 of 98 | font pointer and key swap |
| fn_800776F8 | `fn_80077A58.cpp` | 3 of 108 | byte load order |
| fn_80077D44 | `fn_80077A58.cpp` | 3 of 27 | ptr + flag + 1 gets reassociated |

`wip/fn_8007C4B8.cpp`, `wip/fn_8007EB30.cpp`, `wip/fn_8007B2F4.cpp` and `wip/fn_8007A528.cpp` are superseded
by matches. Tried on the Proc_End family without effect: inline/macro/`const&` mixes per walker layer
(about 1,700 builds each on fn_80085FC4, fn_80082230 and fn_80088948; 240 macro forms on the other two), and,
on fn_80085FC4 only, full macro expansion with function-level locals, where declaration order changed
nothing, unlike the font functions.

## The process system

It is the "6C proc" system of the GBA Fire Emblem games, ported to C++. Scripts drive a tree of
fixed-size objects. All names below are proposed, from the behaviour.

`Proc` (0xB0 bytes, `proc.h`), 256 in `lbl_803D9A58`:

| Offset | Field | Meaning |
|---|---|---|
| 0x00 | script | start of the script, NULL when dead |
| 0x04 | cur | next command |
| 0x08 | onEnd | called on destruction |
| 0x0C | onIdle | called every frame after the script |
| 0x10 | loop | current repeat function, NULL to continue the script |
| 0x14 | name | string, default `lbl_803625A8` |
| 0x18 | parent | a tree slot number below 11, or a parent process |
| 0x1C | child | most recently added child |
| 0x20 / 0x24 | next / prev | siblings |
| 0x28 | sleep | s16 countdown |
| 0x2A / 0x2B | mark / layer | |
| 0x2C | flags | 1 freed, 2 ended, 4 blocking, 8 sync to parent, 0x10 being created, 0x20 may be killed when the pool is empty |
| 0x2D | lockCnt | blocking children plus manual locks |
| 0x2E | pause | |
| 0x30.. | | user data; the sleep process uses 0x60 and 0x64 |

Globals: `lbl_803E4A58` free stack with `lbl_804CB5C8` as its pointer; `lbl_803E4E60` the 10 tree
roots; `lbl_803E4E88` the global lock (virtual lock at +8, unlock at +0x10); `lbl_803E4EA8` eight
command table pointers, set with fn_80089388.

API:

| Function | Proposed name |
|---|---|
| fn_80080F18 | Proc_InitSystem |
| fn_80081050 | Proc_Create(script, parent) |
| fn_80081194 | Proc_CreateBlocking |
| fn_800811E4 | create, blocking if parent is a process (pointers are negative as int), not if it is a tree slot; 0 means slot 3 |
| fn_80081280 | create the sleep process |
| fn_8008130C / fn_80081948 / fn_800815A8 | teardown walkers: mark ended, run onEnd, return to the stack |
| fn_80081A90 | Proc_End |
| fn_80082230 / fn_800829CC | end children / end children of a class |
| fn_80083174 / fn_8008319C | set / clear blocking |
| fn_800831C4 | Proc_Alloc; kills a flag-0x20 process if the pool is empty |
| fn_800839DC | count of free slots |
| fn_80083A48 / fn_80083B58 | run a tree / a root, once per frame |
| fn_80083B78 | Proc_Break: clears loop so the script continues |
| fn_80083B84 / fn_80083CB4 | find / count by class, under the lock |
| fn_80083DC4 | Proc_Goto(p, label) |
| fn_80083E10 / fn_80083E18 | set onEnd / onIdle |
| fn_80083E20 / fn_80083E90 | for each / for each of a class |
| fn_80083F0C / fn_800846BC / fn_80084F0C | end all on a layer / of a class / by name |
| fn_80084E64 | break all of a class |
| fn_80085708 | find by name |
| fn_8008580C | find child of a class |
| fn_800858B0 / fn_80085BB0 | tree walks |
| fn_80085ECC / fn_80085EF8 | index to and from pointer |
| fn_80085F0C | run the script until it blocks |
| fn_800893E4 | search a class with a callback |

Script format: each word has the opcode in bits 0..11 (bits 8..10 select a table, bits 0..7 index
it), the length in words in bits 12..15, and an s16 argument in bits 16..31. A command returns
nonzero to keep interpreting. Opcode 1 is a label. Commands are fn_80086764..fn_800892F4:
set mark, layer, name, onEnd, onIdle; sync flag; nop; sleep; block; goto; loop goto; restart; call,
call-if-goto, call-until; set loop; create, create blocking, create in tree; wait for class; break
class; wait for name; end self, end siblings, end class, end by name; clear blocking; set killable.
fn_80087C70 loads its function pointer from the same word as its arguments, which looks like a
bug in the original.

## Other subsystems

- **NAND save file** (fn_80079BE4..fn_8007A3BC): `SaveFile` at `lbl_803CD8E0`, with a 0xA000-byte
  buffer and then state. `result` at 0xA004 is volatile, because NAND callbacks write it.
- **Controllers** (`pad.h`): class `Pad`, 0x5C bytes, objects in `lbl_803D7918` with PAD status at
  +0x10 and Wii Remote data at +0x40 (0x840 each). Subclass vtables are `lbl_80380978`,
  `lbl_80380A64`, `lbl_80380B50`, `lbl_80380C3C` and `lbl_80380D28`. Virtuals are named after their
  vtable offset. Buttons are remapped to a common layout in `raw` (0x30), then latched into `held`
  (0x20) with repeat handling in `press` (0x28) and `repeat` (0x2C).
- **Font** (0x80077360..0x80077F98): `Font` at `lbl_803CD858`, current font `lbl_804CB598`; glyphs are 0x10
  bytes sorted by Shift-JIS code, found by binary search, falling back to `lbl_804CA3B0` and then 0x8199.
- **Heaps** (0x80077F98..0x80079990): 16 slots at `lbl_803CD868`, mutex at `lbl_803CD8A8` + 4. Blocks have
  a 0x20-byte header; a negative size marks a block from the top of the heap.
- **Prim2D** (the source file name "Prim2D.c" is in `lbl_80362570`): `GState` at `lbl_804CB5C0` is a
  bump allocator with a list of nodes keyed by a word sum of the state at +0x20 (0x70 bytes). Each node
  holds a chain of commands, 0x18 to 0x5C bytes depending on type. Screen space is 608x448.
  fn_8007E84C and fn_80080578 scale by 0.763819 for widescreen around x = 304.

## What may not reflect the original source

- `fn_8007A868.cpp` defines `pads`, `status` and `data` as file statics, because `addi rN, rBase, 0` needs
  pooled statics. They stand for `lbl_803D7918`; other files still extern that label, so the addresses
  are only compared by offset and the file would need its statics merged to link.
- `IntGuard` in `fn_8007A868.cpp` is a plain struct with the vtable stored by hand.
- ClampStick is the SDK's PADClamp, recalled from memory and widened to s16 or changed to have no dead-zone
  subtraction. The reversed declaration order in the inline is what the compiler needed.
- In `fn_80077360.cpp` and `fn_80077F98.cpp`, std::lower_bound-like loops and list helpers are macros with
  function-level locals, in orders found by search. `SEEK` and `SEEKD` differ only in a named header pointer.
- fn_80078E24 and fn_800796D8 reuse the parameter as the heap pointer through `#define h ((Heap*)p)`.
- The heap and font field names, and Heap's first block at +0x20, are inferred.
- `proc_inl.h` spells out the self-inlined walkers as layers (`mark0..mark3`, `free0..free2`,
  `clear0..clear1`) and needs the real functions in another file. The original almost certainly just
  calls recursive functions. The depth is set per function with `inline_depth` in fn_80081050.cpp.
- `procEndV` reads `script` through a volatile cast in fn_80084F0C and fn_80086818, to force a reload
  the original does without volatile.
- `free2m` and `free2` are the same code written two ways, because each matches different callers.
  Which one is used has no meaning.
- `#pragma inline_max_size(5000)` in `proc_inl.h` is mine; the original's setting is unknown.
- In fn_8007FFDC and fn_8008580C's name search, declaration order and the `goto` are what the
  register allocator needed, not evidence of the source. fn_8007FFDC's order was found by a search.
- fn_8007E06C is written as asm because it uses r11/r12 like hand-written code.
- Field and class names are mine. Vtable-offset names on `Pad` are placeholders.
- `proc_pm.h` is a second spelling of the walkers in `proc_inl.h`. The original surely has one set of recursive
  functions (probably Proc members); which walkers are members and which static here is only what the two
  callers in `fn_80082230.cpp` needed. `wip/fn_80082230.cpp` is superseded for those two functions.
- fn_80077D44's `int n = 1; n += ...` is the spelling that stops reassociation, not evidence of the source.

## Round 18

The goal changed: besides exact matches, a function counts when `tools/check_regs.py` classes it `renamed`/`regs` (same instructions, order and references; registers differ). Those are in `equiv/`, one self-contained file each.

**Exact (13 functions, 0x209C bytes), all `MATCH` with `--strict-references`:**

| File | Bytes | Contents |
|---|---|---|
| `fn_8008BDDC.cpp` (+ `.symbols.json`) | 0x524 | video.cpp `DisplayInit`: render mode from TV format, reset code and console settings |
| `fn_8008C594.cpp` | 0x4FC | Screen position / width adjust menu: draw |
| `fn_8008B19C.cpp` | 0x45C | Draw a string with the cached 24x24 glyphs |
| `fn_8008B9B8.cpp` | 0x384 | Red-black tree: rebalance after insert |
| `fn_8008C300.cpp` | 0x294 | Adjust menu: input step |
| `fn_8008B730.cpp` | 0x288 | Tree: free a subtree (plain recursion, `inline_depth(3)`) |
| `fn_8008CA90.cpp` | 0x27C | Apply screen offset, build the vertical copy filter |
| `fn_8008AEE4.cpp` | 0x1A8 | Width of the widest line of a string |
| `fn_8008CD0C.cpp` | 0x14C | Adjust menu: setup |
| `fn_8008CF20.cpp` | 0x138 | Adjust menu: teardown |
| `fn_8008B60C.cpp` | 0x124 | Tree: insert a node |
| `fn_8008A22C.cpp` | 0xF0 | Read a big-endian 64-bit value from a memory stream |
| `fn_80079088.cpp` | 0xC4 | Largest free block of a heap |

**Functionally equal (8 functions, 0x2674 bytes):** `equiv/fn_80088948` (0x89C, renamed), `fn_80087F78` (0x7C0, regs), `fn_80085FC4` (0x7A0, renamed) are the three Proc_End script commands from `wip/fn_80085FC4_pm.cpp`; `fn_8008A868` (0x640, regs, 5 words); `fn_800787E4` (0x448) and `fn_800785FC` (0x1E8) from `wip/fn_800785FC.cpp`; `fn_80077A58` (0x188); `fn_8008A070` (0x80, from rD's `wip/fn_rD12_near.cpp`).

**Still open:** `fn_800776F8` (byte load order), `fn_80079D90` (epilogue order), `fn_8007A1CC` (argument scheduling), `fn_8008A37C` (wants `blt L; b M`; six branch shapes tried). All small and already in `wip/` or rD's wip.

**Subsystem notes:** 0x8008B60C..0x8008BD3C is an MSL `std::set<u16>`-style red-black tree (colour in bit 0 of the parent word, 1 = red) used only to collect the glyph codes. 0x8008BDCC..0x8008D058 is `video.cpp` (the name is in `lbl_803631B0`): `lbl_804CB5F4` display flags (0x10000 NTSC, 0x20000 PAL, 0x40000 EURGB60, 0x80000 MPAL, 0x40 progressive, 0x100 60 Hz, 0x30 set after init, 0x1000000 alarm armed), `lbl_804CB5F8`/`lbl_804CB5FC` interlaced and progressive render modes, `lbl_804CB600`/`lbl_804CB601`/`lbl_804CA3D4` screen x/y offset and width, `lbl_804CA3D0`/`lbl_804CA3D2` the saved VI origin.

**Caveats:**
- `fn_8008BDDC.cpp` defines the five `GXRenderModeObj` tables as file statics with the original values read from `main.dol` at `lbl_803811D0` (the code needs a pooled base). They are real data, but other files still refer to `lbl_803811D0` by label. The symbol map also maps the compiler's `__cvt_dbl_usll` to `fn_8028C818`. `StringPool` in that file and in `fn_8008B60C.cpp` is the documented string dump scaffold; `#pragma readonly_strings on` is needed there so the pool lands in `.rodata` next to `.data` statics.
- `lbl_804CB5F4` is declared `volatile` in the video files. Here the binary supports it: a load whose result is never used survives after `fn_803315F8()`, and consecutive flag updates are not merged.
- `lbl_804CA3D4` is `u8` in `fn_8008CD0C.cpp` (zero-extended sums) and `s8` in the other video files (sign-extended reads). One of the two is a cast in the original.
- `fn_8008B19C` takes its colour by value: only then are the four bytes loaded before any is stored.
- `fn_8008A22C.cpp` and several `equiv/` files start with a whole parent file's declarations (bodies stripped by script); `fn_8008A22C`'s parent is rD's `fn_80089AA8.cpp`.
- `NodeGuard`, `rotateLeft`/`rotateRight` and the `Node` accessors follow the usual library shape; names are guesses. In `fn_8008B9B8` the grandparent and its left child are named locals because the original shares them between both branches.
- SDK names in comments (`GXSetCopyFilter`, `OSSetAlarm`, `SCGetProgressiveMode`...) are inferred from behaviour.

**Lessons:**
- **`a = (u64)b0 << 56; a += (u64)b1 << 48; ...; a += b7; return a;`** (first term assigned, not added to 0) gives the `addc rN,zero,zero` chain; a single expression or `a = 0` first does not.
- **A length-error helper** `inline void err(const char* msg) { fprintf(stderr, msg); abort(); }` loads the string before `__files`; the direct call loads `__files` first.
- **Checker and `.data`:** with a symbol map on `...data.0` the checker compares the whole emitted `.data` by value, so pooled strings must not land there.
- **Variable declared after the others** (`int i` after `c` and `s`) takes the higher volatile register in a leaf-like block; swapping two declarations finished `fn_8008CA90` and `fn_8008C594`.

## Round 20 (small leftovers; `sched` and `slots` now count)

Levels as printed by `python3 -I tools/check_regs.py <file> --extra "-i src/game/rJ_800799AC -i src/game/rJ_800799AC/wip"`. `sched` files were looked at with `tools/equiv/dd.py` (moved instructions are listed in each file header) and run through `tools/equiv/symcheck.py --anon`.

Totals: sched 1 functions / 276 bytes, slots 1 functions / 72 bytes.

| Function | Class | Bytes | File | symcheck |
|---|---|---|---|---|
| 80079D90 | slots | 0x48 | `equiv/fn_80079D90.cpp` | clean |
| 8007A1CC | sched | 0x114 | `equiv/fn_8007A1CC.cpp` | clean |

`equiv/fn_80079D90.cpp` is printed as `slots`, but the only difference is the epilogue order (`lwz r0,0x14` before `lwz r31,0xc` in the original). check_regs.py accepts the two swapped restores as a consistent slot mapping; treat the file as `sched` level.

Not attempted (no draft): 8008A37C, 8008D058, 8008D414, 8008D75C, 8008D91C, 8008DB58, 8008DC34, 8008DF4C, 8008E07C, 8008E1B0.

## Round 21 (small functions without a draft)

Checked with `python3 -I tools/check_regs.py <file> --extra "-i src/game/rJ_800799AC -i src/game/rJ_800799AC/wip"`; exact files also with `check_func.py --strict-references`.

Totals: exact 8 functions / 2560 bytes, regs 1 / 724, sched 1 / 448.

| Function | Class | Bytes | File | Note |
|---|---|---|---|---|
| 8008D058 | exact | 0x3BC | `fn_8008D058.cpp` | screen-adjust menu creation: six `new Spr(kind)` with an inline constructor, then six setPos |
| 8008D91C | exact | 0x120 | `fn_8008D91C.cpp` | script command 0xC handler; flag lookup inline with `p` declared before `i` |
| 8008DB58, 8008DC34 | exact | 0xDC, 0xE0 | `fn_8008DB58.cpp` | bonus tally sums; DB58 is the plain loop, DC34 `base + sum()` |
| 8008DF4C, 8008E07C | exact | 0x130, 0x134 | `fn_8008DF4C.cpp` | team-mask unit scans; the loop runs `i = 1; i < 0xff` |
| 8008E1B0 | exact | 0xA8 | `fn_8008E1B0.cpp` | `int y, x;` order |
| 8008A37C | exact | 0x5C | `fn_8008A37C.cpp` | `blt; b` is an inline `if (n >= 0) return n; return strlen(p) + 1;` |
| 8008D75C | sched | 0x1C0 | `equiv/fn_8008D75C.cpp` | symcheck clean; one store/addi pair swapped |
| 8008D414 | regs | 0x2D4 | `equiv/fn_8008D414.cpp` | the body of fn_8008CA90 inlined (kept as `applyVideo`; port: call fn_8008CA90) |

Family facts: `lbl_803E4EF8` is the bonus tally `{char names[8][0x20]; int vals[8]; int seen; int n; int base;}` and `lbl_804CB608` points at it. fn_8008D414 = set the three video globals + fn_8008CA90 + fn_8030390C; inside the inline the two byte arrays must be declared `a[4]` before `b[3]` to land in the original's slots.

## Round 23 (r23b: equivalent to exact)

New exact files (each prints MATCH with `--strict-references`; symcheck `--anon --xargs` clean):

| File | Function | Bytes | Fix |
|---|---|---|---|
| `fn_80079D90.cpp` | fn_80079D90 | 0x48 | `*(volatile u8*)&lbl_803CD8E0.busy = 0;`: a volatile last store moves the lr reload (`lwz r0,0x14`) before `lwz r31` in the epilogue. Port caveat: the field is probably volatile in the original (set by NAND callbacks). |

Tried in round 23 without an exact result: fn_8008D75C (store orders, global vs pointer), fn_800785FC (magic store at
each position; the statement-move search gets 4 words).

## Round 24

- fn_8008D75C (5 words): a handler local, chained zero stores, a separate `base` local, a Clr inline: no change. The one-instruction `li`/`addi` scheduling misses (fn_8008D75C, fn_80168BF0, fn_800D0BFC, fn_8018524C: the original finishes an address `addi`, or materialises a constant, one slot later or earlier than ours) are not a compiler setting: `#pragma scheduling 601/603/604/750/7400/8240/off`, `-proc 750/603e/604/7400/generic`, the GC 3.0a3..3.0a5 compilers and `-O3,p`/`-O4,s` leave them or make things worse; a same-file definition of the address target (fn_8008D91C) does not move it either.
