# Round 10: 0x8017F400..0x801D09F8

11 functions, 12,652 bytes.

| file | function | bytes | what it is |
|---|---|---|---|
| fn_801B486C.cpp | 801B486C | 3,880 | cursor unit window draw |
| fn_801B10B0.cpp | 801B10B0 | 2,656 | picture list input |
| fn_801A7150.cpp | 801A7150 | 1,616 | fullscreen overlay input |
| fn_801A6BFC.cpp | 801A6BFC | 856 | overlay: group units per army, link cursor list |
| fn_801B1B10.cpp | 801B1B10 801B1EE4 | 696, 620 | picture list: open selected, mark seen |
| fn_801BC29C.cpp | 801BC29C | 684 | unit list stat column text |
| fn_801B01E4.cpp | 801B01E4 | 564 | load check |
| fn_801B46B4.cpp | 801B46B4 | 440 | std::advance on a list iterator |
| fn_801AF104.cpp | 801AF104 | 420 | title bars and caption |
| fn_801B0850.cpp | 801B0850 | 220 | picture list teardown |

## Near misses, by what is left

- wip/fn_801AF2A8.cpp (3,080 bytes, 53 words): registers in the lang 0 branch only. Adding a use of `r` after the join makes that whole branch match, so r30 is live across it in the original although nothing visible reads it. `if (0)`, code after `return`, and self assignments have no effect. Find a use that emits nothing and this matches.
- wip/fn_801B05F8.cpp (600 bytes, 3 words): scheduling of the list store against `lis`/`addi` of `__files`.
- wip/fn_801A32BC.cpp (1,500 bytes, about 45 words): volatile registers in `ScrollTo` and the last two blocks. Saved registers and shape are right.
- wip/fn_801B3D3C_ends.cpp (9 words): e2 and j swapped. The tail must recompute `End(b)`.
- wip/fn_801B09D0.cpp (392 bytes, 57 words): volatile registers only.
- Unchanged: fn_801B78F0 (6, rect copy; a dozen forms and nested structs tried), fn_801BFB58 (2; temporaries and scopes around `m` change nothing), fn_801C4F0C (73, float registers, `sw` is stuck), fn_801CB1A0 (2), fn_801BC88C (2, parameter copies order), fn_801C6114 (2), fn_801CF040 (6), fn_801C8300 (3).

Read but not attempted: fn_801A8E20 (twelve float saved registers), fn_801A6220 (matrix code at the end), fn_801AC084. Not retried: fn_801875CC, fn_8019AEA8.

## What unlocked these

- **`s16` parameters on `fn_800CB3A8`, with the float expression passed directly,** give `lwz r3; extsh r3,r3`. That finished fn_801AF104 and every text call in fn_801B486C.
- **`(u8*)d + 0x10 + i * 0xC4`** gets a compiler-hoisted base, where `Page* pg = d->pages` as a variable leaves the base and induction registers swapped (fn_801A7150).
- **A 4-iteration loop can be unrolled 2x.** `ctr = 2` with `addi 4` twice and an otherwise dead `addi r8,r8,1` is `for (i = 0; i < 4; i++)` over `order[0][i]`, not nested 2x2 loops (fn_801A6BFC). The same loop with an early return gives `addi r3,r5,8` before the fourth test (fn_801A7150).
- **`std::advance`:** `if (n >= 0) { for (int k = n; k > 0; k--) ... } else { for (int k = n; k < 0; k++) ... }` reproduces the long signed range checks of the unrolled loops. A loop on `n` itself does not.
- **Bit array loop in an inline taking `u32* w, u32 k`** fixes the base and word registers (fn_801B1B10).
- **Float to int to float:** `f32 fx = (int)(k + pos.x); ... p->x44 = fx - 130.0f;` with `f32 k = 0.5f` gives `fadds f2,f2,f0` and in-place `lwz r4; xoris r4,r4`. Named int temporaries add a register (fn_801B486C).
- **Three nested `if (l)`** give the triple `beq` of an inlined list destructor. Function-level `l`, `b`, `a` then gets the registers (fn_801B0850).
- **An `s8` return compared to an int:** `s8 v = f(); if (v == last)` keeps `cmpw r0,r31`. A direct compare flips it (fn_801B10B0).
- **Moving a cursor block into an inline** taking `held` changed the base register of the enclosing `switch` (fn_801A7150).
- **Functor slots ascending across cases:** nest case 0 two inlines deeper and case 1 one deeper, with `{ E t; f(l, t); }` at the bottom (wip/fn_801B05F8.cpp).

## Caveats

- fn_801B10B0's function-level `a1..a6`, `b1..b6` stand in for what were probably iterator temporaries, chosen to give the stack slots. `Pad` has guessed slot names.
- fn_801A7150's `First(Page*& p)` takes `p` by reference only to rank it, and the base is written as a byte offset. The `order` array is 2x2 in the struct but indexed flat.
- fn_801A6BFC keeps all locals at function level, in an order from `sw2`. The `/*P*/ /*E*/` markers are still there. The increment order `c++, j++` is a fix, not evidence.
- fn_801B486C's `f32 fx`, `fy` and `k` are guesses at the source. The local struct `T` copying the table from `lbl_8036DE28` is also a guess, and it is a struct assignment where the source may have used an initialiser.
- fn_801B1B10.cpp's `Adv`, `Bit`, `Lk` are guessed inlines; the bit array is at `lbl_803CAB38 + 0xDC` for the test and `+ 0xF0` for the set, as in the original.
- fn_801B0850's three nested `if (l)` flatten an inlined destructor, which the source would not spell out.
- Strings are `lbl + offset`, matched by address. All prototypes outside the region are guessed from call sites. `fn_800CB3A8`'s `s16` coordinates differ from the `int` prototype in older files, so the files can't merge into one object as they stand.
