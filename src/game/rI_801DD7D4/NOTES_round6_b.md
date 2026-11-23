# Round 6, part b: 0x80213000..0x8023FC24

73 new matches, 0x4A60 bytes (19,040). The target of 100 was not reached. Every file below prints MATCH from `python3 -I tools/check_func.py <file>`.

## Files

| file | new matches |
|---|---|
| fn_802373BC.cpp | 802373BC 80237590 80237958 80236CDC 80236680 802370F4 |
| fn_802356BC.cpp | 802356BC |
| fn_80237A80.cpp | 80237A80 80237B20 |
| fn_80237CF8.cpp | 80237CF8 80237DCC 80237E24 80237EF0 80238020 |
| fn_8023825C.cpp | 8023825C 8023835C |
| fn_80238EDC.cpp | 80238EE8 8023AB4C |
| fn_802383F4.cpp | 802383F4 8023B5B0 8023B6C4 8023B894 8023B9D8 8023BE08 8023BE80 8023F0C8 8023F8B8 8023F92C 8023FB24 8023FBF4 |
| fn_80230EDC.cpp | 80230EDC 80231130 802311CC 80231968 80232590 80232864 802338A0 80233DB4 80233E7C 80233F44 80234000 802340AC 802341A0 80234288 8023437C 802344EC |
| fn_80231090.cpp | 80231090 80231AF8 80233AF4 |
| fn_80231C4C.cpp | 80231C4C |
| fn_8022E7A0.cpp | 8022E7A0 8022E9A0 8022F064 8022FC44 80230288 80230410 802305AC 80230688 |
| fn_80228DC4.cpp | 80228DC4 80228F8C 8022A5F8 8022D404 |
| fn_802137B8.cpp | 802137B8 8021D42C 8021F4A8 8021F8C8 80220F28 80222C68 |
| fn_80225470.cpp | 80225470 80233BB8 802346C8 |
| fn_80226C14.cpp | 80226C14 80227358 |

`fn_thp.h` is the shared THP player struct. fn_80238EDC.cpp also emits fn_80238EDC and fn_80238FB0, which were already matched, because the recursive inlining needs their definitions.

## Subsystems identified

- **0x802356BC..0x802383F4, THP movie player.** It has the shape of the DolphinSDK THPPlayer sample: read thread, video and audio decode threads, MixAudio (fn_80237590), SetVolume (fn_80237958), Play (fn_80236CDC), CalcNeedMemory (fn_80236680), and DrawDone (fn_802373BC). `lbl_80420420` is the player state. The names are guesses from that sample.
- **0x802383F4..0x8023FBF4, archive and file entry manager.** Each entry has a 0x3F-byte path, a hash, volatile flags at +0x50, a reference count at +0x54 that runs up the parent chain, and data at +0x60. Entries sit on two lists at `lbl_80425478` (+0x00, and +0x0C for MEM2 addresses), with a lock object at +0x24 and a loader thread.

## Caveats on matches

- **fn_80237590:** `*(volatile u16*)&lbl_80390B58[100]` only stops the load being hoisted out of the loop. It's unlikely to be the original source.
- **fn_802383F4.cpp:** `FE::flags` is declared `volatile`. That reproduces the reloads on every test, and it may or may not be original.
- **fn_80236CDC..fn_802370F4 and fn_8023B6C4:** `fn_8028C418` is called explicitly as a function taking `u64`/`s64` arguments. It's really the compiler's 64-bit divide helper, so the original was probably a plain `/`.
- **File statics:** `sThread`, `sQ1` and similar statics are laid out from asm offsets. The checker compares offsets from `...bss.0` but not the base address or references to named statics. I checked those against the asm by eye. The objects' sizes past the last referenced offset are unverified.
- **Stand-ins:** `RO`, `V38`, `VD`, `MB`, `GX` and the local struct names are stand-ins. Register-shaping choices include reused locals, `int` temporaries, flat declarations in fn_8023B894/fn_8023B9D8, and the hand-unfolded `animY`/`chainY`/`chainZ` macros with their declaration order. These say nothing about the original source.
- **Hidden arguments:** those on fn_801E59A8, fn_801E5D60, fn_8021C278 and fn_8022DE0C come from register evidence only.

## Near misses, not committed

- **fn_80237B78 (Reader):** 26 words, all register rotation. `frame` should be r31. Declaration changes had no effect.
- **fn_8023580C:** the same problem at 19 words, with a frame 0x10 larger than ours. An unknown inline local is probably missing.
- **fn_802358B8:** 13 words. The popped buffer and the player base register are swapped.
- **fn_8022E2D0:** only the help string register differs (r30, want r29). **fn_802326F0, fn_802327A4:** the same (r31, want r29).
- **fn_8022DFE0:** 28 words, register choice inside the inlined base constructors.
- **fn_802167C8:** the base constructor's dead vtable stores are eliminated when `this` is a parameter. Even `volatile` writes left 45 words wrong.
- **fn_8022A6E4, fn_8022A7CC, fn_8022B9B8, fn_8022BA6C:** 10 to 20 words of register choice.
- **fn_80232334:** 24 words. **fn_8023126C:** 66 words. **fn_80232428:** 41 words (a colour struct copied through the stack).
- **fn_8022EF60:** a shared `li r5,1` isn't reproduced. **fn_8023DC38:** 15 words, a zero and vtable register swap.
- **fn_8023BB70:** argument order and a `const&` min/max temporary.
- **fn_80236384:** 155 of 168 words, because the base register and induction variable are wrong.
- **fn_802384F0, fn_80238FB8, fn_802396CC, fn_8023A0BC, fn_8023AC14, fn_8023BF78, fn_8023CD24:** large functions with repeated inlined retry loops, not attempted.

## Skipped

fn_80213F8C, fn_80214C00, fn_80215490, fn_8021773C and fn_8021876C (widget constructors from NOTES.md) were not attempted, because the time went to the THP and dialog families first. fn_8021E734 uses a variable-length stack buffer and was also skipped.

## Lessons

- **Triage first:** running `m2c_draft.py` plus the checker over a whole range takes about 30 seconds. It finds drafts that need one fix, and file statics.
- **`addi rN, rBase, 0x0` plus an SDK shape** means file statics. A file per static block keeps offsets right, because the checker compares from `...bss.0`.
- **Recursive inlines through accessors:** `inline` non-static definitions of the real `fn_` accessors with `#pragma inline_depth(4)` reproduce the 4-level chain and the out-of-line accessor calls at the deepest level.
- **Hoisted unlock with an unhoisted lock:** `k = (VO0N*)sLock` declared outside the loop, unlocking through `k` and locking through the fresh expression, gave `addi r3,r31,0x24` and `mr r3,r29` together.
- **Flat declarations at the top of the function** fixed whole-function rotations in the list walkers, where block-scoped ones couldn't.
- **`lwz rN; cmpwi cr1,rN,0; beq cr1` release:** `if (p) { if (--p->rc == 0 && p) p->destroy(1); o->f = 0; }` matches directly, and solved 5 functions.
- **Member destructors:** `addic. r0,r3,off; beq; beq; stw r4,off(r3)` needs a real member array (`MB* m = &o->m[i]; ... o->m[i].vt = ...`). A cast offset folds to `0(r3)`.
- **`cmpw r0,r31` right after `li r0,0`** is a store-forwarded field compare: `r->a31 = 0; if (r->a31 == k)`.
- **Scoped `s16 x = p.x;`** forwards a stack `XY` field into one register for two stores, where direct `p.x` reloads it.
- **Tools:** `tools/perm/lib.py` derives its root from its own location, so a scratch copy needs `ROOT` set by hand. macOS has no `timeout` command.
