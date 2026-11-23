#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005F0A8(void) {
    u8 r;
    switch (fn_80083B84(lbl_8037E248)->state40) {
    case 4:
    case 6:
        break;
    default:
        return 3;
    }
    if (fn_801E7024() == 0) {
        r = 2;
    } else {
        r = lbl_804CB550 == 0x87;
    }
    return r;
}

extern "C" char* fn_8005F124(void) {
    return lbl_8037F4A0;
}

extern "C" const char* fn_8005F130(void) {
    return fn_800D0864(lbl_8037F494);
}

extern "C" int fn_8005F13C(void) {
    fn_800453B4(&lbl_803CA870, 0x86);
    lbl_804CB550 = 0x86;
    return 5;
}

extern "C" u8 fn_8005F174(void) {
    return lbl_804CB550 == 0x86;
}

extern "C" char* fn_8005F188(void) {
    return lbl_8037F488;
}

extern "C" const char* fn_8005F194(void) {
    return fn_800D0864(lbl_8037F478);
}
