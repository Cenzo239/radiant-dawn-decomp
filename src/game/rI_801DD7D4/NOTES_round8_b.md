# Round 8, part b: 0x80213000..0x8023FC24

16 new matches, 0x2BD4 bytes (11,220). The 35 KB target was not reached. Every file below prints MATCH from `python3 -I tools/check_func.py <file>`.

## Files

| file | new matches |
|---|---|
| fn_8023A0BC.cpp | 8023A0BC |
| fn_802355D4.cpp | 802355D4 802358B8 8023721C |
| fn_80236218.cpp | 80236218 |
| fn_80237B78.cpp | 80237B78 |
| fn_80235B18.cpp | 80235B18 80235FF4 |
| fn_80236E18.cpp | 80236E18 |
| fn_80234F1C.cpp | 80234F1C |
| fn_8023C9C8.cpp | 8023C9C8 8023D9B8 8023DE84 |
| fn_8023EF74.cpp | 8023EF74 8023F1A8 8023F4EC |

## Near misses (attempts are not in the tree)

- **fn_80238FB8:** structure is exact, 453 of 453 instructions, about 100 words of register rotation. Source shape is below. Moving the switch into `disp(m, e)` fixed `e`, and splitting the load into `allocA`/`allocB` inlines took it from 115 to 105. Still wrong: `src` wants r27 (gets r28), the heap id `h` wants r28 (gets r22), `hint` wants r21 (gets r27). Case 3 also wants `m->a` in r3 and the flags in r0.
- **fn_8023AC14:** 51 words. Fixed this round: declare `task` first, use `flg(e, 0x04000100)` for the mask test. Still wrong: `h` and `hint` swap between r23 and r25, and `addi r30,r26,0x6c` is scheduled two slots late. Moving the four allocation paths into inlines is worse in all 16 combinations.
- **fn_802384F0:** still 135 words. `flg()` and `allocA`/`allocB` don't change it. `src` wants r30 (the same register as `c`) and `size` wants r31.
- **fn_80236738:** structure exact, 32 words. A plain `for` over `rb[10]`, `ts[3]` and `ab[6]` unrolls correctly. Only the last block misses: it wants the size in r0, zero in r4 and the base in r5. A named zero, hand unrolling and a helper inline made no difference.
- **fn_8023DCC0:** 29 words. The local entry `FE t` has an inlined constructor and destructor, both matching `feInit`. The original stores `flags` first and uses the `found = 0` register for `name[0]` and `hash`.
- **fn_80225650:** 12 words, using a `newL84` inline around `l84Init`: only the `l44` and `l74` sentinels swap r26 and r27. Without the inline those are right but `o` and 0x260 swap. No spelling of the list init changed this.
- **fn_8023BB70:** about 70 lines. Needs `mn`/`mx` with `const&`, 0x804CAA98 read twice, `size` loaded before `pos`.
- **fn_80235098:** pairs need `lbz r5 [0]; lbz r0 [1]; stb; stb`. Named locals give the pair form with the registers swapped, whatever the declaration or load order.
- **fn_802352C8:** 24 words, mostly volatile temporaries in the first block. Direct global assignment gets the same score.
- **fn_8022FD08 (10 lines, 2 real words), fn_802307F4 (9), fn_8022E620 (2 real words):** unchanged. For fn_8022E620 the help string wants r29 and takes r28 in every form tried.
- **fn_8021F5C4 family:** still blocked. Local variables, inline returns, `const`, struct members, parameter forms and computed y values for 0x190 all leave -1 first.

```cpp
static inline void disp(Msg* m, FE* e) {
            switch (m->type) {
            case 0:
                fn_802384F0(e, m->a);
                break;
            case 1: {
                dec0(e->a98);
                if ((e->flags & 0x04000000) && !(e->flags & 0x00100000)) {
                    startLoad(e);
                } else {
                    if (e->flags & 0x08000000) fn_8023B6C4(e);
                    flush(e);
                    e->flags |= 0x200020;
                }
                break;
            }
            case 2: {
                FE* s = e->a98;
                u32 v = m->a;
                dec0(s);
                if ((s->flags & 0x04000000) && (s->flags & 0x00200000)) {
                    freeData(s, v);
                } else {
                    flush(s);
                    s->flags |= 0x200000;
                    s->flags &= ~4;
                }
                e->flags = (e->flags & ~4) | 0xa80000;
                break;
            }
            case 3: {
                u32 f = e->flags;
                u32 v = m->a;
                f &= ~2;
                f |= 0x100000;
                e->flags = f;
                if (!(f & 4)) freeData(e, v);
                if (e->flags & 0x08000000) fn_8023B6C4(e);
                flush(e);
                e->flags |= 0x200000;
                break;
            }
            }
        }
```

## Skipped

fn_802396CC, fn_8023BF78 and fn_8023CD24 (same allocation shape, blocked by the rotation above). fn_802291A8, fn_8022130C, fn_80219018, fn_802328F8, fn_8023E264 and fn_8023E8EC (read at most). fn_8021BB04, fn_80222E34 and the other large widget and draw functions were not attempted.

## Caveats on matches

- **Volatile casts:** fn_8023A0BC reads `src->size` and `src->data` through `*(volatile u32*)&` inside a comma expression, purely to put `size` first. It is not likely source. There is probably a real cause not yet found, since `DCFlushRange(e->data, e->size)` in fn_80238FB8 shows the same size-first load.
- **Volatile store:** fn_8023DE84 writes the terminator through `*(volatile char*)(p + 1)` to stop a later load moving above it.
- **Dead reads:** fn_8023DE84 has `e->flags;` and a volatile read of `e->size`. They are probably the remains of a debug print compiled out.
- **Stand-ins:** `int p = h;` in the allocation inlines of fn_8023A0BC is inherited from round 7. The early `return` in fn_8023C9C8 exists only to stop two identical branches merging, and its `touch()` helper is unused. `u32 q = p; if (p != 0) q = p;` in fn_8023EF74.cpp stands for the dead compare.
- **Splits:** fn_802358B8 keeps `AB* msg = m;` in the case block, and fn_8023721C uses `const C4*`, only for colouring and scheduling.
- **Statics:** fn_80236218.cpp and fn_80237B78.cpp declare file statics by size. fn_8023C9C8.cpp and fn_8023EF74.cpp use the `fn_fe.h` order. The checker compares offsets but not the base, so I compared the base with the asm by eye through the scratch diff.
- **Names:** struct, field and helper names are guesses.
- **Hard-coded address:** fn_80235FF4 writes the GX FIFO through a literal `0xCC008000`.

## Lessons

- **Size-first loads:** when a later argument loads first, try `volatile` casts on the loads that must keep their order, with the first one assigned in a comma expression. Inlines, temporaries and casts don't move it.
- **Accessor for masks:** `lwz r0; rlwinm rN,r0; rlwimi. rN,r0` instead of `lwz rN; rlwinm r0,rN` comes from a test through an int-returning inline (`flg(e, m)`). The direct `e->flags & m` colours the other way.
- **Identical arms:** a plain `if` with identical arms is folded. `if (c) { X; return; } X;` keeps both copies.
- **`u16 n = e->rc - 1; e->rc = n; if (n == 0)`** gives `subi r0; clrlwi. r3,r0,16; sth r0`. `--e->rc == 0` colours differently.
- **Modulo compare:** `u32 k = (i + a) % b; if (k == b - 1)` gives lhs r3 and rhs r0, where the direct compare swaps them. The same goes for `u32 k = a + b; if (k == c)`.
- **Const colour pointer:** `const C4* col` passed as `*col` to a by-value parameter hoists the four `lbz` above the argument setup. Non-const loads and stores alternate.
- **Unrolled init loops:** `for (i = 0; i < 10; i++) { rb[i].ptr = q; q += AL(size); }` unrolls exactly with each field reloaded. Try the loop before hand-writing.
- **Popped messages:** a saved register holding a popped message comes from a small `pop()` inline returning a local. The inline's result gets a saved register, where a function-level `&msg` local is reloaded.
- **Name a value late:** `AB* m; ... case 1: { AB* msg = m; ...}` swapped two saved registers no declaration order could.
- **THP and file-manager code is the cheap part of this range.** Sixteen matches came from it with little searching, while the widget functions and the allocation family took most of the session. Read the asm first: Ghidra dropped the FIFO writes in fn_80235FF4, merged `T.a9c` in fn_80236738 and hid a 0x5b store in fn_8023DE84.
