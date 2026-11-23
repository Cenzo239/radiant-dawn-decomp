#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005E52C(ObjB4* a) {
    int r;
    switch (fn_80083B84(lbl_8037E248)->state40) {
    case 2:
    case 4:
    case 6:
        break;
    default:
        return 3;
    }
    if (fn_80085708(lbl_804CA368)) {
        return 3;
    }
    r = fn_802428AC();
    a->b4 = r;
    if (r == 0) {
        return 2;
    }
    return lbl_804CB550 == 0x90;
}

extern "C" char* fn_8005E5CC(void) {
    return lbl_8037F658;
}

extern "C" const char* fn_8005E5D8(void) {
    return fn_800D0864(lbl_8037F644);
}

extern "C" int fn_8005E5E4(void) {
    fn_800453B4(&lbl_803CA870, 0x8f);
    lbl_804CB550 = 0x8f;
    return 5;
}

extern "C" u8 fn_8005E61C(void) {
    return lbl_804CB550 == 0x8f;
}

extern "C" char* fn_8005E630(void) {
    return lbl_804CA360;
}

extern "C" const char* fn_8005E638(void) {
    return fn_800D0864(lbl_8037F634);
}
