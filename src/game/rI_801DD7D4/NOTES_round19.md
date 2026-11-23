# Round 19 (i): 0x801DD7D4..0x8023FC24

Levels: `exact` (check_func.py --strict-references prints MATCH), `renamed`/`regs` and, new during this
round, `sched` (same instructions per basic block, a few in another order) from `tools/check_regs.py`.
All checks below were re-run at the end of the round.

| level | functions | bytes |
|---|---|---|
| exact | 2 | 980 |
| renamed / regs | 6 | 3,316 |
| sched | 33 | 23,360 |
| total | 41 | 27,656 |

The 30 KB aim was missed by about 2.3 KB. Of the 33 `sched` functions, 17 are drafts from earlier rounds
that only needed the new class (10.6 KB, copied to `equiv/` as self-contained files) and 16 were written
or completed this round (12.7 KB).

## Exact (in `src/game/rI_801DD7D4/`)

| file | bytes | notes |
|---|---|---|
| fn_801E10E4.cpp | 728 | multi-line text label draw; builds each line in a std::string |
| fn_8023F9F4.cpp | 252 | state of a named file (entry flags / pending list / exists on disc) |

## renamed / regs (in `equiv/`)

`python3 -I tools/check_regs.py <file> --extra "-i src/game/rI_801DD7D4 -i src/game/rI_801DD7D4/wip"`

| file | class | bytes | notes |
|---|---|---|---|
| fn_80222E34.cpp | regs | 1288 | 18-slot skill list panel with slide/fade animation |
| fn_801E9CA8.cpp | regs | 656 | round 18 draft fixed (see caveats) |
| fn_8021CF08.cpp | regs | 436 | small stat box draw |
| fn_8022E620.cpp | regs | 384 | "can anyone use this service" check |
| fn_80223580.cpp | renamed | 328 | round 18 draft fixed (missing `extsh`) |
| fn_80230FB0.cpp | regs | 224 | dims the unselected row widgets |

## sched (in `equiv/`), written or completed this round (16 functions, 12,716 bytes)

fn_8021BB04 (1208), fn_801EC928 (1000), fn_801E8E88 (1000), fn_801E941C (968), fn_801EC414 (956),
fn_801FE108 (956), fn_80205E50 (796), fn_8020B408 (796), fn_8022516C (772), fn_8022DFE0 (752),
fn_80221050 (700), fn_802020AC (664), fn_801F17C4 (476), and fn_801ECF94 / fn_801EDF9C / fn_801EEFA4
(124 each, in fn_801ECF94.cpp together with fn_801FE8BC).

## sched (in `equiv/`), earlier drafts that the new class now accepts (17 functions, 10,644 bytes)

fn_802384F0 (2540), fn_8022C384 (1560), fn_80224CCC (980), fn_801EBF00 (956), fn_8021C31C (796),
fn_8021F5C4 (772), fn_80213B4C (728), fn_802225E8 (720), fn_80236384 (680), fn_80236738 (576),
fn_801E1D0C (516), fn_8023DCC0 (452, needs `fn_8023DCC0.symbols.json` for an exact-level check only),
fn_8022A7CC (176), fn_80223900 (152), fn_8023DC38 (136), fn_801FE8BC (124), fn_8021D17C (80).
The wip originals are untouched. fn_80213B4C, fn_8021D17C, fn_802225E8 and fn_80224CCC come from
multi-function wip files; in the copies every other exported function is reduced to a prototype.
For each file the moved instructions were read with `tools/equiv/dd.py`: they are constant loads (`li`,
`lis`/`addi`), independent field loads, or stores to different fields. fn_802384F0 has 132 differing
words but only three moved instructions; the rest are register differences.

## Zero-idiom drafts (in `wip/r19zero/`, all `other`, complete)

| file | bytes | source |
|---|---|---|
| fn_801F2954.cpp | 3688 | from wip/r18i/fn_801F4850.cpp (only the selector is attached here) |
| fn_8020B8C8.cpp | 2316 | from wip/fn_80206310.cpp (6 lists instead of 3, fields shifted) |
| fn_801F6C54.cpp | 1056 | identical instructions to fn_801F3D28; that draft renamed |

Not drafted (no sibling to derive from): fn_801F8798, fn_801F9030, fn_801FA9BC, fn_801F43E0.

## Not done (in `wip/r19i/`, each file starts with a comment)

| function | bytes | state |
|---|---|---|
| fn_80223CF4, fn_801E7E1C | 1204, 1208 | 301/301 and 302/302 instructions, one `extsh` one slot late. `sched` by inspection, but check_regs.py prints `other`: its sched test cannot match a `bl __ptmf_scall` (compiler helper, fn_8028C178, not in symbols.txt) against the original call. A tool fix would credit both. |
| fn_80236A5C | 640 | THPPlayerPrepare, 155/160. The original materialises WaitUntilPrepare()'s result (`li 1; b; li 0; cmpwi`); every inline/static/C/deferred form folds it. |
| fn_80232334 | 244 | 60/61, a missing `mr r4,r5` (flag and count swap r4/r5). |
| fn_801FB050 | 172 | 40/43, an unfolded 64-bit compare that occurs once in the DOL. |

## Skipped

- Zero-idiom family and the four local-vector functions, as instructed (except the drafts above).
- fn_801E2924, fn_8021C6FC, fn_8022A174, fn_80225650, fn_8022FD08, fn_802307F4, fn_801E31D4/fn_801E5640
  (list `find_if` with by-value iterators), fn_8023580C, the fn_801DFF2C lazy-static family: not reached.
- wip/r18i: fn_801EA5E4 (two stack arrays swapped, so offsets differ), fn_801E163C/fn_801E1894 (the
  colour-copy puzzle; by-value, copy-constructor and wrapper forms tried again without success),
  fn_8023CD24, fn_8023E264/fn_8023E8EC, fn_801F4850: still `other`.
- Older `other` drafts within a few lines that I looked at but did not fix: fn_8021A8F4 (4 lines),
  fn_801EA17C (one duplicated `extsh`), fn_80227DFC (3 lines), fn_802267D8 (10 lines).

## Caveats (where the source may not reflect the original; things a port should undo)

- Names, structs and virtual slot signatures are guesses throughout.
- **fn_8021BB04:** `#pragma opt_propagation off` and the `xform` inline exist only to keep the 30.0f field
  of view in a register and to order the stack; `fov` is a plain constant. The FIFO is written through a
  declared object at 0xCC008000 (`volatile WG WGPIPE : 0xCC008000`), which is compiler specific: a port
  must replace the vertex writes with real GX calls. Class `sched`: in the original the four colour bytes
  are loaded before the position stores of each vertex; ours loads them after. Harmless unless the colour
  pointer aliases the FIFO.
- **fn_801E10E4:** `String`, `PushBack`, `c_str` are hand-written stand-ins for MSL std::string
  (fn_800250B0 is its replace/insert). The checker skips the emitted `__dt__6StringFv`.
- **fn_80222E34 / fn_801E9CA8:** the halved width is written `(s16)(w >> 1)`; the cast only steers
  scheduling. fn_801E9CA8 also fixes a real bug of the round 18 draft: the scale before the map sprite is
  0.5f, not 1.0f.
- **fn_80223580:** the cursor is read once into an `s16` and copied into two `int`s; that is what keeps
  the original's extra `extsh`.
- **fn_8022E620:** `memset(map, (u8)lbl_804CAA88, 0xb)` reads a global int that is 0 in the DOL; the
  original is probably a fill helper. Unit id 0 gives a NULL unit that is dereferenced, as in the original
  (ids start at 1 here).
- **Constructor family** (fn_801EBF00 siblings, fn_8022DFE0, fn_80205E50, fn_8020B408, fn_8022516C,
  fn_80221050, fn_801F17C4, fn_802020AC): the widget constructors are inlines over a plain struct
  (`wfInit`, `newB`, vtable stores by label); the real code is a C++ class hierarchy with `new`. When
  allocation fails the original still writes through the null pointer, and so does the source.
  fn_801EC414 is identical to fn_801EBF00 and fn_801FE108 differs only in which pool its float literals
  come from, so both are the same source.
- **fn_801ECF94 family:** `setP` and the byte-offset macro are conveniences, the row arrays are probably
  real members.
- **fn_8023F9F4:** uses local `FE` and the lock/list by their labels instead of the fn_fe.h statics.
- `sched` is weaker evidence than `regs`: dependencies between the moved instructions were checked by eye
  only.

## Outside the rules

Nothing edited outside `src/game/rI_801DD7D4/`; temporary files only in `build/tmp/r19i`; no git; nothing
killed. Two usage-limit pauses; all files survived.

## Lessons not in MATCHING.md

- **With `sched` available, the constant-heavy constructors are cheap.** The only miss of the whole family
  is which constant gets r0, which moves two `li`. One sibling diff (`sib.py`-style: mask labels, diff two
  originals) plus text substitution gave nine functions in about one compile each.
- **Diff the originals against each other before writing.** fn_801EC414 = fn_801EBF00, fn_801F6C54 =
  fn_801F3D28 (identical instructions), and five more differ by a few constants.
- **Re-check old `other` drafts with check_func.py -v for "wrong reference … constant".** fn_801E9CA8 was
  one instruction from `regs` for a round because of a wrong float (1.0f for 0.5f), which no masked diff
  shows.
- **`(s16)(w >> 1)` instead of `w >> 1`** makes the width chain "longer" for the scheduler (the cast is
  removed later) and moves its loads ahead of another argument's.
- **`T* it = o->p->item[i]` vs `(T*)((u8*)o->p + off + K)`:** the array form keeps `add; addi rN,rT,K;
  lwz 0(rN)`; the byte-offset form is merged into `lwzu`.
- **A value read once into an `s16` local and copied into `int` locals** keeps `extsh` on later `(s16)`
  casts; an `int` assigned straight from the field loses it (fn_80223580).
- **`f32 fov; … fov = 30.0f;` under `#pragma opt_propagation off`** keeps a float constant in a saved
  register and stops `fov * 0.5f` folding; an inline parameter does not when every use is constant.
- **Locals of an inline called from the body sit below the body's own arrays** (used to put a 3x4 matrix
  under a 4x4 one).
- **`return !(w >> 31) ? a : b;`** gives `bne; a; b; b` layout; `if (!(w >> 31)) return a; return b;` and
  the positive ternary give the other.
- **Three destructor copies of a loop-local object** mean `continue` and `break` both occur in the body.
- **Pass a loaded field by value into a "find then store" inline** when the original loads it before the
  call; a `const T&` parameter loads it after (fn_802020AC).
- **Release of a ref-counted member:** `RO* p = r; if (p) { if (--p->rc == 0) { if (p) p->destroy(1); }
  r = NULL; }` gives the `cmpwi cr1` reuse; testing the member twice reloads it.
- **Statement order decides which constant gets r0 in store-heavy constructors** (moving `y0` first flips
  it), but no order tried reproduced both the registers and the store order.
- **Tool limits:** check_regs.py `sched` fails on any function that calls a symbol missing from
  symbols.txt (`__ptmf_scall`); "wrong reference" lines for drafts whose instructions are shifted by one
  slot are artefacts, not bugs.
