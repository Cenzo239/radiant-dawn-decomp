#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005525C(P6* p) {
    int i = p->h6e++;
    if (!getV(p, i)) {
        fn_80083DC4(p, 0x63);
        return;
    }
    fn_80045120(&lbl_803CA870, getV(p, i));
    switch (getB(p, i)) {
    case 1: fn_800485C4(&lbl_803CA870, p); break;
    case 2: fn_800484B8(&lbl_803CA870, p); break;
    }
}
