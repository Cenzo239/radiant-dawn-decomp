/* symcheck: r21 review, flag was an artefact. fn_80168A90: (a) two float-to-int temporaries in each other's stack
   slot (0x8/0x10); same index computed. See docs/SCHED_REVIEW.md. */
/* symcheck --xargs: fn_801689C8 (c) fixed in the round 21 regs review, now exact (was regs, 3 words). fn_801030B8 has six
   arguments (rB_8002E1C4/fn_800402C0.cpp); the draft passed five and r8 was never set, the original passes p in r8. */
/* fn_801689C8 (0xC8, exact) and fn_80168A90 (0xC4, `sched`): functionally equal per tools/check_regs.py
 * (round 20). From wip/fn_801689C8.cpp with its stray closing brace removed (that file did not compile).
 * fn_80168A90, moved instructions (dd.py): the second `stfd` of the two float-to-int conversions and the first
 * `lwz` of the converted words are swapped; they use different stack slots (0x8 and 0x10).
 */
/* AI: proc steps that move the camera to the target tile (names guessed). */
#include "game/rQ_80163178/common.h"
extern "C" {
extern u8 lbl_804CB830;
extern u8 lbl_803CAB38[];
void fn_801030B8(Unit*, int, int, int, int, void*);
void fn_800620A8(void*, f32, f32);
void fn_80083DC4(void*, int);

static inline BOOL IsM() { BOOL b = 1; u8 m = lbl_804CB830; if (m != 1 && m != 2) b = 0; return b; }
static inline BOOL IsM2(u8 m) { BOOL b = 1; if (m != 1 && m != 2) b = 0; return b; }
void fn_801689C8(f32* p) {
    Unit* a = lbl_803CA870.unit;
    BOOL b = 1;
    u32 mode = lbl_804CB830;
    if (mode != 1 && mode != 2) {
        b = 0;
    }
    if (b && lbl_803CAB38[0x11] == 1 && lbl_803EC898.ter[2][lbl_803CA870.x + lbl_803CA870.y * 0x40] == 0) {
        return;
    }
    fn_801030B8(a, (int)p[12], (int)p[13], 0x10, 0, p);
}

void fn_80168A90(f32* p) {
    BOOL b = IsM();
    if (b && lbl_803CAB38[0x11] == 1 && lbl_803EC898.ter[2][(s8)(int)p[12] + (s8)(int)p[13] * 0x40] == 0) {
        fn_80083DC4(p, 99);
        return;
    }
    fn_800620A8(lbl_803CAB38, p[12], p[13]);
}
}
