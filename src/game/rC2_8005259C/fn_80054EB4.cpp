#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_80054EB4(void* p) {
    fn_80054D98(p, 1);
}

extern "C" void fn_80054EBC(void* p) {
    fn_80054D98(p, 0);
}

typedef struct Proc30 {
    u8 pad0[0x30];
    Unit2* u30;
    s16 h34;
    s16 h36;
    s16 h38;
    u8 b3a;
} Proc30;
extern "C" void fn_80054EC4(Proc30* p) {
    fn_8003B298(lbl_803CA870.pos13.x, lbl_803CA870.pos13.y);
    p->u30 = lbl_803C8E80.p3f0;
    p->h34 = lbl_803C8E80.h448;
    p->h36 = lbl_803C8E80.h44e;
    p->h38 = lbl_803C8E80.h454;
    p->b3a = 0;
    p->u30->h382++;
    fn_800EB3D8(p);
}
