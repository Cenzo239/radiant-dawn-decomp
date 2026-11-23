#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_80055C30(void) {
    U5* a;
    U5* b;
    Word* w = fn_800CFD3C(&lbl_803E7320);
    a = (U5*)lbl_803CA870.unit;
    b = (U5*)fn_800CFB0C(w);
    fn_8002BCC4(&lbl_803C8E80);
    if (!b->b114) {
        addStat(b->f4->b8, a);
    }
}
