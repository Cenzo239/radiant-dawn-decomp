#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_800559CC(void* p) {
    s8* w = (s8*)fn_800CFD3C(&lbl_803E7320);
    if (w == 0) {
        fn_80083DC4(p, 0x63);
    } else {
        fn_800620A8(&lbl_803CAB38, w[0], w[1]);
    }
}
