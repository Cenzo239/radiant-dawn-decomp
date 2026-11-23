#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005F4F0(ObjB4* a) {
    int r;
    switch (fn_80083B84(lbl_8037E248)->state40) {
    case 5:
    case 6:
        break;
    default:
        return 3;
    }
    r = fn_802428AC();
    a->b4 = r;
    if (r == 0) {
        return 2;
    }
    return lbl_804CB550 == 0x84;
}

extern "C" char* fn_8005F568(void) {
    return lbl_8037F448;
}

extern "C" const char* fn_8005F574(void) {
    return fn_800D0864(lbl_8037F434);
}

extern "C" int fn_8005F580(void) {
    fn_800453B4(&lbl_803CA870, 0x83);
    lbl_804CB550 = 0x83;
    return 5;
}

extern "C" u8 fn_8005F5B8(void) {
    switch (fn_80083B84(lbl_8037E248)->state40) {
    default:
        return 3;
    case 1:
    case 5:
    case 6:
        return lbl_804CB550 == 0x83;
    }
}

extern "C" char* fn_8005F61C(void) {
    return lbl_8037F428;
}

extern "C" const char* fn_8005F628(void) {
    return fn_800D0864(lbl_8037F418);
}

extern "C" int fn_8005F634(void) {
    fn_800453B4(&lbl_803CA870, 0x82);
    lbl_804CB550 = 0x82;
    return 5;
}

extern "C" int fn_8005F66C(void) {
    return 0x3;
}

extern "C" char* fn_8005F674(void) {
    return lbl_8037F408;
}

extern "C" const char* fn_8005F680(void) {
    return fn_800D0864(lbl_8037F3FC);
}

extern "C" int fn_8005F68C(void) {
    fn_800453B4(&lbl_803CA870, 0x81);
    lbl_804CB550 = 0x81;
    return 5;
}

extern "C" u8 fn_8005F6C4(void) {
    switch (fn_80083B84(lbl_8037E248)->state40) {
    default:
        return 3;
    case 1:
    case 2:
    case 3:
    case 6:
        return lbl_804CB550 == 0x81;
    }
}

extern "C" char* fn_8005F724(void) {
    return lbl_8037F3EC;
}

extern "C" const char* fn_8005F730(void) {
    return fn_800D0864(lbl_8037F3DC);
}

extern "C" int fn_8005F73C(void) {
    fn_800453B4(&lbl_803CA870, 0x80);
    lbl_804CB550 = 0x80;
    return 5;
}

extern "C" u8 fn_8005F774(void) {
    switch (fn_80083B84(lbl_8037E248)->state40) {
    default:
        return 3;
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
        return lbl_804CB550 == 0x80;
    }
}

extern "C" char* fn_8005F7DC(void) {
    return lbl_8037F3CC;
}

extern "C" const char* fn_8005F7E8(void) {
    return fn_800D0864(lbl_8037F3BC);
}
