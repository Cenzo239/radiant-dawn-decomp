/* Battle-speed/bgm-like process at the end of the region, 801313E4..80131534. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {

extern u8 lbl_80385E68[];
extern char lbl_803692C0[];
extern void* fn_80081050(void*, void*);
extern void* fn_80083B84(void*);
extern void fn_80083DC4(void*, int);
extern void fn_800846BC(void*);
extern void* fn_80078CCC(int, char*, int);
extern void fn_8013067C(void*, int);
extern void fn_80130BB4(void*, f32);

struct Fx {
    u8 pad0[0x34];
    void* v34;
    int v38;
    u8 v3C;
    u8 pad3D[3];
    void* v40;
    u8 v44;
    u8 v45;
};

void fn_801313E4(void* parent) {
    Fx* p = (Fx*)fn_80081050(lbl_80385E68, parent);
    p->v40 = fn_80078CCC(0xa00, lbl_803692C0 + 0x17, 0);
    p->v44 = 0;
    p->v45 = 0;
    p->v34 = 0;
    p->v3C = 0;
}

void fn_8013144C(u32 k) {
    void* p = fn_80083B84(lbl_80385E68);
    if (p) {
        fn_8013067C(p, (u8)k);
    }
}

void fn_80131490(void) {
    Fx* p = (Fx*)fn_80083B84(lbl_80385E68);
    if (p) {
        p->v44 = 0;
        p->v3C = 0;
        fn_80083DC4(p, 0);
    }
}

void fn_801314D4(void) {
    fn_800846BC(lbl_80385E68);
}

void fn_801314E0(void) {
    Fx* p = (Fx*)fn_80083B84(lbl_80385E68);
    if (p) {
        fn_80130BB4(p, p->v38);
    }
}

BOOL fn_80131534(void) {
    Fx* p = (Fx*)fn_80083B84(lbl_80385E68);
    if (p && p->v3C == 0) {
        return 1;
    }
    return 0;
}

}
