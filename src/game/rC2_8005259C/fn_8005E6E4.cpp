#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005E6E4(void) {
    switch (fn_80083B84(lbl_8037E248)->state40) {
    case 3:
        return 2;
    default:
        return 3;
    case 2:
    case 6:
        return lbl_804CB550 == 0x8e;
    }
}

extern "C" char* fn_8005E754(void) {
    return lbl_8037F610;
}

extern "C" const char* fn_8005E760(void) {
    return fn_800D0864(lbl_8037F600);
}

extern "C" int fn_8005E76C(void) {
    fn_800453B4(&lbl_803CA870, 0x8d);
    lbl_804CB550 = 0x8d;
    return 5;
}

extern "C" u8 fn_8005E7A4(void) {
    return lbl_804CB550 == 0x8d;
}

extern "C" char* fn_8005E7B8(void) {
    return lbl_804CA358;
}

extern "C" const char* fn_8005E7C0(void) {
    return fn_800D0864(lbl_8037F5F0);
}
