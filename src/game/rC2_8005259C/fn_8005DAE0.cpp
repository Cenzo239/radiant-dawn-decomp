#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005DAE0(void) {
    switch (fn_80083B84(lbl_8037E248)->state40) {
    case 4:
    case 5:
        break;
    default:
        return 3;
    }
    return lbl_804CB550 == 0x9a;
}

extern "C" char* fn_8005DB34(void) {
    return lbl_8037F784;
}

extern "C" const char* fn_8005DB40(void) {
    return fn_800D0864(lbl_8037F774);
}

extern "C" int fn_8005DB4C(void* a, Menu* m) {
    u8 one = 1;
    ((u8*)m->proc)[0x50] = one;
    fn_800453B4(&lbl_803CA870, 0x9a);
    lbl_804CB550 = 0x9a;
    return 5;
}
