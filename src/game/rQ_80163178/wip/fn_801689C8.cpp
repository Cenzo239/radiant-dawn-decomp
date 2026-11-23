/* fn_801689C8: 1 register (p should be r8, ours r7). fn_80168A90: fctiwz f0/f1 swap and one load register. */
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
