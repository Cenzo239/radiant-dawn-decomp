#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005DD3C(void) {
    if (!(lbl_804CB700 & 0x10) && fn_802450BC(fn_8024BC94()) == 0) {
        return 2;
    }
    return lbl_804CB550 == 0x99;
}

extern "C" char* fn_8005DD8C(void) {
    return lbl_8037F738;
}

extern "C" const char* fn_8005DD98(void) {
    return fn_800D0864(lbl_8037F72C);
}

extern "C" int fn_8005DDA4(void) {
    fn_800453B4(&lbl_803CA870, 0x98);
    lbl_804CB550 = 0x98;
    return 5;
}

extern "C" u8 fn_8005DDDC(void) {
    return lbl_804CB550 == 0x98;
}

extern "C" char* fn_8005DDF0(void) {
    return lbl_8037F720;
}

extern "C" const char* fn_8005DDFC(void) {
    return fn_800D0864(lbl_8037F710);
}

extern "C" int fn_8005DE08(void) {
    fn_800453B4(&lbl_803CA870, 0x97);
    lbl_804CB550 = 0x97;
    return 5;
}

extern "C" u8 fn_8005DE40(void) {
    switch (fn_80083B84(lbl_8037E248)->state40) {
    default:
        return 3;
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
        return lbl_804CB550 == 0x97;
    }
}

extern "C" char* fn_8005DEA8(void) {
    return lbl_8037F704;
}

extern "C" const char* fn_8005DEB4(void) {
    return fn_800D0864(lbl_8037F6F4);
}

extern "C" int fn_8005DEC0(void) {
    fn_800453B4(&lbl_803CA870, 0x96);
    lbl_804CB550 = 0x96;
    return 5;
}

extern "C" u8 fn_8005DEF8(void) {
    if (fn_80076F54(lbl_8037F6E8) == 0) {
        return 3;
    }
    if (fn_802912A4(fn_8006074C(&lbl_803CAB38)->name, lbl_804CA370, 5) == 0) {
        return 3;
    }
    if (fn_80060914(&lbl_803CAB38)) {
        return 3;
    }
    switch (fn_80083B84(lbl_8037E248)->state40) {
    default:
        return 3;
    case 1:
    case 6:
        return lbl_804CB550 == 0x96;
    }
}

extern "C" char* fn_8005DFB8(void) {
    return lbl_8037F6DC;
}

extern "C" const char* fn_8005DFC4(void) {
    return fn_800D0864(lbl_8037F6D0);
}
