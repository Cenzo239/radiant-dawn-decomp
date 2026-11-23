# Round 17 (i): 0x801DD7D4..0x8023FC24

No new matches in this region this round. The time went to rH (fn_80133034 family, 3,736 bytes; see
rH_80112B48/NOTES.md, Round 17), and the round was cut short by a usage limit.

## Tried here

- **fn_801FE8BC family** (wip/r15a/fn_801FE8BC.cpp, 9 words): a grid of 84 spellings (x1e via an accessor or
  cast, product-first sums, a named `m`/`d`, PC vs PI) gets to 8 words at best, for example
  `PC p((s16)o->x1e, (s16)(o->b[i] - o->a[i]) * 0x1c + gy(o))` with `gy` returning `o->x20`. The original loads
  `x1e` first and puts `a[i]` in r8 and `b[i]` in r7. Not saved, since it is only one word better.
- **fn_802225E8** (1 word, `mr r5,r4` vs `li r6,0`): read again, not retried.
- **fn_8022130C:** the r13b wip no longer compiles to its old 6 words (it scores about 600 now, probably because
  fn_wf.h changed since round 13). It needs rebasing before anyone retries it.

## Still open, unchanged

fn_80227DFC, fn_8021F0E0, fn_801EA17C, fn_8021E23C, fn_8023DC38, fn_80201110, fn_802007E4, fn_801E7990,
fn_801E1D0C, and the std::advance list draws fn_80223CF4/fn_80222E34. The skip list from the brief was respected.

## Tool note

Copies of tools/perm/lib.py compute ROOT from their own path, so a copy outside the repo can't find wibo or
the compiler. Hardcode ROOT in the copy, and point every `mkdtemp` (sw.py and rr.py use the script's own
folder) at your build/tmp folder.
