# Round 16 (i): 0x801DD7D4..0x8023FC24

2 new matches, 0x138C bytes (5,004). The 25 KB aim was not reached. Both print MATCH from
`python3 -I tools/check_func.py --strict-references --symbol-map <file>.symbols.json <file>`.

| file | bytes | notes |
|---|---|---|
| fn_802396CC.cpp (+ .symbols.json) | 0x9F0 | open an entry from disc, allocate, start the read |
| fn_8023AC14.cpp (+ .symbols.json) | 0x99C | open an entry from a file context (old wip at 91 words) |

The symbol maps send `...bss.0` to `lbl_80425478` (the fn_fe.h statics). Note that the already
matched fn_8023A0BC.cpp has no map and fails `--strict-references` for that reason only.

## What solved them

- **Per-call-site locals by reference.** Each of the eight inlined allocation sites (`tail1/tail2/head1/head2`,
  each with `evict1/evict2` and the `nextMode` switch) gets its own `h`, `p`, `m` declared in the caller's
  `/*P*/` block and passed by reference. sw.py then took fn_8023AC14 from 97 to 8 words in one run.
- **`flg(e, 0x04000100)`** (int-returning inline) instead of `e->flags & 0x04000100` fixed the volatile
  registers of the first test.
- **`e->a98` is the DVD command block's userData.** The task at +0x6C is a DVDFileInfo; +0x98 is its
  `cb.userData` (+0x2C). Writing `((FI*)task)->user = e` instead of `e->a98 = e` puts the `addi rX,e,0x6c`
  where the original has it (address arithmetic is otherwise sunk to its first use).
- **Reading a global twice into a min temporary** (`lwz lbl` for the compare, `lwz lbl` again stored to a
  stack temp): `std::min`-style `mn(len, maxRead())` where `static inline u32 maxRead() { return lbl_804CAA98; }`.
  A direct `mn(len, lbl)` binds the global (`li rN,lbl@sda21`), and every cast/conversion spelling loads once.
- **`lbz r8; extsb r8,r8` on a by-value argument:** declare the callee parameter `int`, not `s8`.

## Near misses (wip/r16i/)

| function | words | state |
|---|---|---|
| fn_802384F0 | 37 (difflib) | Per-site by-reference version of the old wip. Registers mostly right; remaining: `size + 4` rematerialised at the call in the original, kept in a register in ours, and the DCFlushRange argument order (below). sw.py and rr.py are at a local minimum. |
| fn_80238FB8 | 93 | Loader thread loop (OSReceiveMessage, switch on message type, dec chains, startLoad, freeData). Structure is exact; registers and the dec-chain order off. Same DCFlushRange problem. Its startLoad tests `e->data` again, not `src`. |
| fn_8023BB70 | 18 | DVD read callback. Needs `rd4(fi, addr, n, e, lim)` (the max-with-priority inside a wrapper, so it is evaluated last), `post()` for the message so `m` gets the lowest slot, `rem2` (`s = size; s -= pos`) for the load order, and the `maxRead()` trick. Left: one stack slot pair in the second block and two volatile registers around `e->pos += ...`. |
| fn_8023DC38 | 1 | Entry destructor. The volatile `flags = 0` store must come before the vtable store and the `cmpwi r4`; writing it first in source swaps the zero and vtable registers (14 words). fn_8023DCC0 shows the same order in its local constructor and destructor, so the original probably has a base/derived split I couldn't reproduce. |
| fn_802225E8 | 1 | Unchanged from round 15 (`mr r5,r4` vs `li r6,0` order). Counter types and loop forms tried. |

Also retried without success: fn_8022A7CC (lha scheduled before `stw r29`; volatile read, local orders and
struct forms all stay at 1 word), fn_80217DF8 (`int sel` gives the `mr` but swaps sel with the yo/col web;
tys.py and sw.py from both starting points, accessors and compare spellings all stay at 2 or 8).

## Open puzzle: DCFlushRange argument order

fn_802384F0 and fn_80238FB8 (4 sites) load `lwz r4, size` before `lwz r3, data` before `bl DCFlushRange`.
These are the only places in the whole DOL with that order for two saved-register field loads before a call.
Tested and not reproducing it: `void*`/`u32` prototypes and casts, `const` and volatile reads, named locals in
either order, inline wrappers with either parameter order or `const&`, an 8-byte struct copy, bitfields,
`#pragma scheduling off`. The scheduler only put `r4` first when the size expression had a longer dependency
chain (e.g. `e->size ? e->size : 0`) or a side effect (`e->size++`), neither of which is in the original.

## Skipped

As told: the zero-idiom functions, the `lbl_8038C1C0` constructor users, the retry-loop family, the
fn_801EBF00 family, the fn_801DFF2C lazy statics, fn_8022A174 and the fn_8021D17C/fn_8021C31C size-setter.
Read but not written: fn_802291A8 (4 KB gradient draw with eight unrolled `fn_8017F68C` lerps per block and
`_savegpr_15`), fn_8023CD24, fn_8023E264/fn_8023E8EC (std::vector growth with exceptions), fn_8023BF78
(open-entry dispatcher, many inlined inc/dec chains), fn_801E7E1C (grid draw, `_savegpr_15`).

## Caveats on matches

- Names, the `DI`/`FI` structs and the inline split (`evict*`, `tail*`, `head*`, `nextMode`) are guesses;
  the per-site by-reference locals and their `/*P*/` order came from sw.py and say nothing about the source.
- `maxRead()` exists only to read `lbl_804CAA98` twice; the original may use a different construct.
- `fn_802396CC.cpp` and `fn_8023AC14.cpp` each re-declare the fn_fe.h statics, as fn_8023A0BC.cpp does.

## Lessons not in MATCHING.md

- **Per-site by-reference locals scale to whole families of 2.5 KB functions:** a function with eight inlined
  copies of the same allocator went from 97 words to 2 with one sw.py run. Try this first on any big
  function that repeats one inline.
- **Address arithmetic sinks to its first use.** If an `addi rX, base, off` sits earlier in the original than
  in ours, look for a store through that pointer (here `task->userData = e`, folded back to `e + 0x98`).
- **A global read twice for a `const&` min:** an inline accessor returning the global by value.
- **Conditional arguments are evaluated first.** An inline call with a branch in an argument list is hoisted
  before the other arguments; to get it last, move the call into a wrapper inline that takes the other
  arguments as parameters.
- **`a - b` loads `b` first** and puts the result in `b`'s register; `s = a; s -= b;` loads `a` first.
- **Tool note:** copied grid.py/tys.py compile every candidate as `.cpp`, and lib.origfn only reads
  `auto_03_*` asm files (told by another agent; it didn't matter in this region).
