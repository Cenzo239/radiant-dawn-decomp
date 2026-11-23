# Round 20 (i): 0x801DD7D4..0x8023FC24

Levels as in round 19 (`exact`, `renamed`/`regs`, `sched`). All checks below were re-run at the end.

| level | functions | bytes |
|---|---|---|
| exact | 6 | 3,244 |
| regs | 5 | 7,936 |
| sched | 3 | 1,896 |
| total counted | 14 | 13,076 |

The 20 KB aim was missed. Besides the counted files there are 16 complete drafts in `wip/r20/`
(about 26 KB, all `other`), most of them instruction-for-instruction equal to the original except for
one named detail (see the table below).

## Exact (in `src/game/rI_801DD7D4/`)

`python3 -I tools/check_func.py <file> --strict-references -v` prints MATCH; the four lazy-static files
need `--symbol-map <file>.symbols.json` (function-local statics and their guard bytes).

| file | bytes | notes |
|---|---|---|
| fn_8022A174.cpp | 1156 | text-window layout for 8 screen anchors |
| fn_801E041C.cpp (+ .symbols.json) | 652 | prompt window with caller-supplied labels |
| fn_801E0274.cpp (+ .symbols.json) | 424 | yes/no prompt, variant 3 |
| fn_801DFF2C.cpp (+ .symbols.json) | 420 | yes/no prompt (M_ASK_Y / M_ASK_N) |
| fn_801E00D0.cpp (+ .symbols.json) | 420 | yes/no prompt, variant 2 |
| fn_8023580C.cpp | 172 | THPPlayer VideoDecoderForOnMemory thread |

## regs / sched (in `equiv/`)

`python3 -I tools/check_regs.py <file> --extra "-i src/game/rI_801DD7D4 -i src/game/rI_801DD7D4/wip"`

| file | class | bytes | notes |
|---|---|---|---|
| fn_8022130C.cpp | regs | 2736 | rebased from wip/r13b (its header-bar statements had been cut out, nothing else was wrong) |
| fn_801F8798.cpp | regs | 2200 | convoy unit-select screen builder; NOT a zero-idiom function (no sort loop in it) |
| fn_80225650.cpp | regs | 1568 | unit-list screen builder, sibling of fn_8021FA30 |
| fn_8022FD08.cpp | sched | 1408 | shop confirm sub-menu handler; one `li r5,0` a slot late |
| fn_8021C6FC.cpp | regs | 856 | 5-card selector fade/scale update |
| fn_802307F4.cpp | regs | 576 | shop "unit chosen" step |
| fn_801E31D4.cpp | sched | 244 | reverse find of a child by id (list at +0x40) |
| fn_801E5640.cpp | sched | 244 | same template code, list at +0x34 |

Moved instructions of the three `sched` files were read with `tools/equiv/dd.py` and are listed in the
file headers (a constant load; two loads in a prologue that still precede every store).

## Complete drafts left at `other` (in `wip/r20/`), and exactly what differs

| file | bytes | difference from the original |
|---|---|---|
| fn_801E2924.cpp | 1228 | 307/307 instructions, same registers. Only the 13 four-byte point locals are in mirrored stack slots (orig X = ours 0x50-X). |
| fn_801EA5E4.cpp | 1672 | 418/418, frame and slots now right. In the third colour clamp one `lwz o->a4c` is loaded a block early (pointer in r6 instead of r3) and two stack stores are swapped. |
| fn_80214C00.cpp | 1060 | 265/265, same registers. Functor and its by-value copy sit in swapped 8-byte slots (twice). |
| fn_801FA9BC.cpp | 648 | zero idiom + one redundant `extsh r4,r4` missing |
| fn_801F43E0.cpp | 1136 | zero idiom + the same redundant `extsh` missing |
| fn_801F9030.cpp | 1868 | 467/467: zero idiom, one extra saved register, constant scheduling in two small constructors |
| fn_801FEA10.cpp, fn_80204A08.cpp | 1196 each | local std::vector; 289/299: ours hoists three addresses out of the loops and spills the outer counter (see header) |
| fn_801F3D28.cpp, fn_801F6C54.cpp | 1056 each | zero idiom ONLY (264/264) |
| fn_802038BC.cpp | 1304 | zero idiom + one `addi` a slot apart |
| fn_80206310.cpp, fn_8020B8C8.cpp | 2316 each | zero idiom + one extra saved register + one `neg` a slot apart |
| fn_80202344.cpp | 1496 | improved to 374/374: zero idiom + one extra saved register + one `neg` |
| fn_801F4850.cpp, fn_801F2954.cpp | 3700, 3688 | improved to 925/925 and 922/922: zero idiom + `neg` + constant order in the 0x48 constructor |

Every zero-idiom draft is now self-contained in `wip/r20/` and its header answers "is the mr/li
instruction the only difference". Only fn_801F3D28 and fn_801F6C54 can say yes.
The earlier copies (wip/, wip/r15a, wip/r18i, wip/r19zero) are untouched.

Older drafts I retried without progress (left where they were): fn_80232334 (flag/count r4/r5),
fn_801FB050 (unfolded 64-bit compare), fn_80227DFC (`b; li r31,0` else-arm: the compiler always hoists the
`li`), fn_801E163C / fn_801E1894 / fn_8021F0E0 (colour-copy puzzle: six more spellings, see lessons),
fn_8023BB70 (two swapped stack words plus one moved `addi`).

## Skipped / not reached

- fn_80236A5C, fn_8021A8F4, fn_801EA17C, fn_8023CD24: looked at the diffs only; no change.
- fn_8023E264 / fn_8023E8EC: the wip/r18i draft stays the complete draft (same open point as
  fn_801FEA10); no new copy made.
- fn_801E2424: the wip/r15a `_levels` draft has the same single difference as fn_801E2924 (mirrored
  slots); not re-saved.
- fn_802267D8, fn_80223CF4, fn_801E7E1C are already listed as done elsewhere and were not touched.
- fn_801EB490, fn_801E2F40, fn_802286A4, fn_8022ADF0, fn_8022BE9C, fn_8022C2D8, fn_80235098, fn_802352C8,
  fn_80238FB8: not looked at beyond a distance scan.

## Real bugs found in old drafts

- **fn_801F4850 / fn_801F2954 (and fn_80202344):** `lbl_8038D720` / `lbl_8038D6C4` / `lbl_8038E4B0` are
  not pointer-to-member constants copied dead to the stack: each is a 12-byte constant {0, 0x60, 0}
  passed BY VALUE to the header child's v2C. The drafts called v2C with no argument (8 instructions
  missing) or built the triple as a local initialiser (frame 0x10 too big).
- **fn_80202344:** v38 was called with an argument (0) that the original does not pass.
- **fn_80214C00:** the two "add all units except x" loops take a functor object by value; the draft had a
  plain loop (8 instructions missing).
- **fn_8022130C (wip/r13b):** not rotted by the header, the four statements that set up the header bar
  (id 0x80, a28 8, sy 0, caption string) had been replaced by a `/*X*/` placeholder.
- **fn_801E041C (my own first draft):** spacing constant is 50.0f, not 16.0f; found only by
  check_func.py's "constant ... but original has" line.
- **Earlier notes:** fn_801F8798 was listed as a zero-idiom function; it has no sort loop at all.

## Caveats (things a port should undo)

- Names, structs and virtual slot signatures are guesses throughout.
- **Lazy-static prompts (fn_801DFF2C family):** `KB/KA/KC/KD/KE` are plain structs whose constructors
  store vtable labels; the real classes are virtual. The two objects are real function-local statics
  (that is what reproduces guard bytes and store order). The three pooled-string variants need
  `#pragma pool_strings on`; fn_801E041C's labels are the small-data strings lbl_804CA930/8.
- **fn_8023580C:** THPReadBuffer has a third member (isValid) that the function never touches; it is
  what makes the frame 0x30.
- **fn_8022FD08:** the shC/shD, shG/shH and mvC/mvD/mvE wrapper chains exist only to order stack slots.
- **fn_801E31D4 / fn_801E5640:** `RIt` is MSL's reverse_iterator with its scratch iterator in front; the
  scratch word is copied uninitialised, as in the original. Use std::list::reverse_iterator.
- **fn_80225650, fn_801F8798, fn_8022130C, fn_801F9030:** constructors are inlines over plain structs
  with vtable stores by label; several widgets are used without a null check after allocation, as in the
  original.
- **fn_801EA5E4 (draft):** clampD/clampE wrappers only order stack slots.
- **fn_801FEA10 (draft):** `StringPool` is the documented dump of this file's real string pool
  (lbl_8036F03C, 36 strings); fn_80204A08 uses its pool by label instead.
- **equiv/fn_8022FD08.cpp and equiv/fn_802307F4.cpp** carry a full copy of fn_80225DB4.cpp's
  declarations (made with tools/equiv/mkself.py); wip/r20/fn_801FA9BC.cpp and fn_801F43E0.cpp carry
  fn_801FA670.cpp's.
- `sched` is weaker evidence than `regs`; `other` drafts above were compared with dd.py by eye.

## Outside the rules

Nothing edited outside `src/game/rI_801DD7D4/`; temporary files only in `build/tmp/r20i`; no git; nothing
killed; no background search was started. One usage-limit pause; all files survived. One slip: three of my
own new exact files (fn_801DFF2C/00D0/0274.cpp) were written twice within a minute because the first
write had a wrong header line; no pre-existing file was overwritten.

## Problems with the tools

- `check_regs.py` has no class for "same instructions, same registers, locals in other stack slots".
  Three drafts (fn_801E2924, fn_80214C00, and fn_801E2424 from round 15) differ in nothing else. A class
  that maps r1 offsets below the register save area one-to-one would credit about 3.5 KB.
- `check_regs.py` cannot take a symbol map, so files with function-local statics print `sched`/`other`
  where check_func.py with the map prints MATCH (it did not matter here because the exact check counts).
- `check_func.py --symbol-map` rejects `@stringBase0` ("must be an object-local symbol absent from
  symbols.txt"); pooled strings are verified by value anyway, so leave it out of the map.
- `dd.py` does not mask stack offsets; a copy with `N(r1)` and `addi rX,r1,N` masked (ddm.py in my tmp
  folder) plus a slot-mapping script made the three slot-only cases visible at once.
- `mkself.py` output keeps the parent's prototypes, so a fragment must use the parent's parameter types
  (fn_801F43E0 is declared `int (void*)` there).

## Lessons not in MATCHING.md

- **Function-local statics are real.** `lbz guard; extsb.; bne` followed by `stw vt,obj@l(rN)`,
  `addi rM,rN,obj@l`, field stores, derived vtable, `stb 1,guard` is `static T obj(args);` with an
  inline constructor. Placement new or hand-written guards never reproduce the register use; the real
  thing matched four functions at the first compile. Map `name$NN` and `@GUARD@name$NN` in a
  symbols.json (read the names from the disassembly of the object).
- **Strings of 8 bytes or less go to .sdata unless `#pragma pool_strings on`.** A pooled `lis/addi`
  string base with `addi r9,r5,8` for the second literal needs the pragma plus real literals; an extern
  array for the pool gives another register order.
- **Stack slots follow who creates the object, not who uses it.** Deeper inline = lower slot; function
  locals first-declared highest; by-value arguments first-parameter highest. When a whole group comes out
  mirrored, turn the data flow round: fn_801E31D4 was mirrored with "temporaries passed down by value
  into an inline with locals" and right with "locals in the function initialised from inlines that
  return by value" (`RIt it = rbegin(w); RIt e = rend(w);`).
- **MSL reverse_iterator** is two words {scratch, current}; `*it` writes scratch twice (`tmp = current;
  --tmp`). Uninitialised words copied between stack slots at function entry are such scratch members.
- **`#pragma inline_bottom_up off` makes callers inline a recursive function** (to the inline_depth
  limit). With the default it is never inlined into a caller. It did not solve fn_801E2924 (the depth
  limit cuts the last level differently), but it is the only switch found that changes this.
- **A struct with a nested empty member (`struct F { E0 op; void* x; }`) passed by value** reproduces
  functor copies on the stack (`stw x,4(slot); lwz pad; stw; stw`); the same struct with an `int` pad is
  scalar-replaced away.
- **12 bytes copied from `.data` to the stack right before a virtual call with `addi r4,r1,N`** is a
  by-value struct argument, not a pointer-to-member constant, when the data is not {delta, index, func}.
- **Extra unused frame space** can be an unused struct member: 8 more bytes of frame in
  fn_8023580C came from a 12-byte THPReadBuffer.
- **`r.x + (w - K)` vs `r.x + w - K`** decides the operand order of the shared `add` (fn_8022A174 went
  from `regs` to exact).
- **A reused variable (`a = find(5); ...; a = find(0xb);`)** instead of two variables is what the
  original has when a later widget lands in the first one's register; it did not change registers here
  but keeps the source honest.
- **Three clamps in ascending slots:** `int v; int lo; int hi;` (declaration order = slot order) in the
  clamp inline, and one more wrapper inline per earlier clamp.
- **Zero idiom, new findings (still open).** (1) Under `#pragma opt_propagation off` our loop comes out
  as `li i; li z; mulli ofs,i,12`: the induction start is computed from the counter and normally folded.
  The original has `li i; (hoisted load); mr z,i; li ofs`, so its `mr` is created after constant
  propagation, between the hoisted loads and the strength-reduction start, like a late loop-invariant.
  (2) An uninitialised int or class in a register gives `stb rX` with no definition and one saved
  register fewer; the original has the same register count as the `li` form. (3) `z = i = 0`, `i = z = 0`,
  a constructor taking `i = 0`, an empty base class of the counter (`struct Ctr : Cmp { int i; }`), a
  union of counter and comparator and a ternary all give `li` or a stack `lbz`. (4) In the three
  constructor-style members of the family the original also uses one saved register fewer than ours.
- **Local-vector functions:** the original does not hoist the addresses used in the five error paths
  (`__files`, the string pool, the bad_alloc text) although it hoists six integer constants; ours hoists
  the addresses too and then has no register left for the outer counter. Real string literals, explicit
  induction variables and a list-base parameter did not change that.
