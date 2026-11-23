# Round 17 (rF_8017F400)

9 new functions, 6,748 bytes. All of them MATCH with `--strict-references`; fn_801A7FDC also needs
`--symbol-map fn_801A7FDC.symbols.json` (`...data.0` -> `lbl_80388F00`).

| file | function | bytes | what it is |
|---|---|---|---|
| fn_801A7FDC.cpp (+ .symbols.json) | 801A7FDC | 2,248 | class change / level up screen state machine (26-entry jump table) |
| fn_801CD478.cpp | 801CD478 | 1,308 | map object bones: bend under units, write map height tables, refresh matrices |
| fn_801B6738.cpp | 801B6738 | 992 | unit list: draw the visible rows' 3D unit models |
| fn_801CCA38.cpp | 801CCA38 | 524 | model bounding box from the 8 transformed corners |
| fn_801CA688.cpp | 801CA688 | 464 | map object animation state set |
| fn_801C957C.cpp | 801C957C | 412 | is any tile in range free (ABS/`__abs` Manhattan loop) |
| fn_801B5EB4.cpp | 801B5EB4 | 392 | text line with scissor mode and palette colour |
| fn_801B1DF8.cpp | 801B1DF8 | 220 | five script registrations with the 4-word state at lbl_803CAB38+0xF0 saved/restored |
| fn_801C77DC.cpp | 801C77DC | 188 | use the command unit's item (Ref struct passed by value) |

## Near misses filed in wip/ (new files only)

- wip/fn_801959A0_r17.cpp: 2 of 1290 words (was 8). `y = 0x3e + ib * 0x38` inside the slot loop fixed the induction
  order; `SInit(&st, lbl_804CB934->x88, 0x1000)` (an inline taking the buffer and size) fixed the Stream registers.
  Left: the original stores `vt` before `p`. All 5040 store orders in SInit and 576 split base/derived orders
  (BInit inside SInit) stay at 2; volatile stores make it worse. Still uses the s_c1..s_b2 statics and `__div2i`.
- wip/fn_801B78F0_r17.cpp: 5 words (was 6), without the kRect stand-in: the rect is a local aggregate initialiser
  `{0x28, y, 0x1B8, 0x16}`; lbl_804CF360/4/6 in sdata2 are its template pieces (the gap at F362 is the y slot).
  Left: the original loads w, h, then x.
- wip/fn_801CCCBC_r17.cpp: 14 words (was 36). `t = fn_8001ECE4(2, t, 0.0f, c, d)` reusing the float parameter fixed
  the size and the f31 reuse; fn_801CCE8C (fresh, same shape with the child at +0) is at the same 14.
  Left: level-1 `e` vs level-2 `k` registers and the conversion order of the innermost call result.
- wip/fn_801CD05C.cpp: ~168 lines. fn_801CCCBC/fn_801CCE8C are inlined three levels deep there, but CW never inlines
  a recursive function into another (tried keyword `inline`, every inline_depth), so LEVEL macros stand in. The original
  keeps `li r0,2` for d separate from the literal-2 argument; our expansion CSEs them, which looks like the original was
  inlined after optimisation. Probably needs the real inliner behaviour, not a spelling.
- wip/fn_801CE174.cpp: 21 lines; stack slots of the two anchor Vec copies, the clamp copy and the argument copy.

## Tried without success

fn_80181470 (u64 swap colouring), fn_801BC88C (prologue `mr` order), fn_801C6114 (`li r7` schedule; 196-cell grid
of init positions and all decl orders), fn_8019555C (sel wants r9), fn_8018524C and fn_8019F108 (`li 0` before
`li 1`: both look like the same scheduler quirk), fn_80183944 (store order of the halved colour), fn_801CB1A0
(x38 read through r3 instead of r31), fn_801CF040, fn_801A2588 (0xFF/0x5555 constant web vs `x`),
fn_801C63F0 (the original keeps `e` in r4 where no call precedes and a copy in r31 elsewhere; separate block copies,
`&e->x` pointers and by-ref inlines all coalesce), fn_801BE154, fn_801A8E20 (29 words, R-rect stores and a long
float block), fn_801B6B18 (s64 flag test with `srawi r0,rZero,31`).

## Skipped

fn_801875CC and fn_8019AEA8 (giants, as asked), fn_8019FFE4 and fn_801B2150 (wips far off), fn_80182D24,
fn_801A4744, fn_801C3AB4 (f14..f31 float-heavy), fn_801805E0, fn_801AC084 (pooled strings, 411 words in the
fragment), fn_801B0B58 (MSL list iterators on the stack).

## Caveats

- fn_801A7FDC: sX/sY/sOrd are file statics holding the real data of lbl_80388F00 and lbl_80388F14 (the symbol
  table makes F14 one 0x20-byte object; the code addresses its byte tail as a third pool member at +0x28). The ease
  start values for modes other than 0..2 are uninitialised, as in the original.
- fn_801B1DF8: `Save` stores the vtable lbl_8037F7E0 by hand and has an empty destructor only to keep the object in
  memory; `Refs` with `q.b = q.a + 1` exists only to reproduce the three held pointer registers. The real code is
  probably a small saver class over the 128-bit flag set.
- fn_801C77DC: `Ref() { ...; flag = 0; if (p) flag = 1; }` reproduces a dead `b; stb` that the original keeps;
  the real constructor shape is unknown. Same pattern in rD's wip/fn_80094130.cpp (not touched, outside my region).
- fn_801CA688: the second `fn_80312378` passes `(u8*)a + 0x10` and the first `&((MdlM*)a)->mtx` so the address is
  not CSEd; the original probably had two different member paths.
- fn_801B6738: `sc = 0.625f` as a named local before the loop holds the constant in f28.
- fn_801CD478: `f32 fx = u->x; f32 fy = u->y;` before the int conversions, and `f32 sc = ...scale` before the
  divides, exist for load order. Locals are per-loop (i1/nd1, i2/nd2, ...) found with sw.py.
- fn_801B5EB4: the colour copy goes through `SetCol(u8*)` only for the argument-slot order.

## Lessons not in MATCHING.md

- **Named pointer to a global vs direct use, again:** in fn_801CD478 `HMap* m = &lbl_803EC898;` cost 25 register
  lines that sw.py could not fix; using `lbl_803EC898.hA[...]` directly took it to 4 at once.
- **Inline with the values as parameters fixes init registers:** fn_801959A0's Stream init went from 6 to 2 words
  when the stores moved into `SInit(Stream*, void* buf, int n)` called with `lbl->x88`; no store order or named
  local had moved them.
- **Several separate arrays pool, a struct does not:** `static s16 a[10]; static s16 b[10]; static u8 c[12];`
  share `...data.0` with `addi rN,rBase,0/0x14/0x28`; putting b and c in one struct static gave separate `lis`.
- **Local aggregate initialisers explain split sdata2 halfwords:** `R4 q = {0x28, y, 0x1B8, 0x16}` loads the
  constant members from compiler pieces in sdata2, matching original labels lbl_804CF360/4/6 with a gap for y.
- **Dead `b; stb` after constructor stores:** `if (p) flag = 1;` in a constructor that just set `p = 0` leaves a
  branch over a dead store and keeps the constructor's stores live (fn_801C77DC; fn_80094130 in rD has it too).
- **An empty destructor keeps a stack object in memory** (otherwise its fields are scalarised); frame slots for a
  scalarised second struct still get reserved (fn_801B1DF8).
- **Loop `break` into the next case:** a `for (;;)` search whose found-branch ends in `break` and falls into the
  following case label gives `bne next_case; b end` (fn_801A7FDC case 10/15).
- **Reusing a float parameter as the result** (`t = f(..., t, ...)`) puts the result in the parameter's saved FPR
  at the outermost level of an inlined recursion (fn_801CCCBC).
- **`int a = v / 32; int b = a + 8;` vs `int b; int a = ...; b = a + 8;`** swapped two volatile registers in
  fn_801B6738's visibility test; the declaration-with-initialiser form matched.
- **Recursive functions are never inlined into callers,** whatever `inline` keyword or inline_depth: fn_801CD05C
  contains three inlined levels of fn_801CCCBC in the original, so the original compiler or source differed there.
- Tool notes: copies of tools/perm must sit three levels below the project root or have `lib.ROOT` set by hand;
  `asm.py`-style fragment assembly must keep the helpers above the first function (the old sweep dropped them,
  which made several wip fragments look 400 words off).
