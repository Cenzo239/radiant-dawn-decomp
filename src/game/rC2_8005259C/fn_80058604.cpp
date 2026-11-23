#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_80058604(void) {
    void* p = fn_80083B84(lbl_8037E248);
    if (p) {
        fn_80081A90(p);
    }
}

extern "C" void fn_80058638(void) {
    void* p = fn_80083B84(lbl_8037E248);
    if (p) {
        fn_801E5860(fn_801FBEB0(p));
    }
    p = fn_800D4228(lbl_80361F9C + 0x15);
    if (p) {
        fn_8008939C(p);
    }
}

extern "C" void fn_8005868C(void) {
    void* p = fn_80083B84(lbl_8037E248);
    int t;
    if (p) {
        fn_801E5870(fn_801FBF08(p));
    }
    p = fn_800D4228(lbl_80361F9C + 0x15);
    if (p) {
        fn_800893AC(p);
    }
    t = fn_800685B0(fn_8006074C(&lbl_803CAB38));
    if (fn_8024F7EC(t)) {
        fn_80251838(0, t, 500.0f);
    }
}

extern "C" int fn_80058718(void) {
    return fn_80083B84(lbl_8037E248) != 0;
}

extern "C" void fn_8005874C(void* parent) {
    u8* p = fn_801DFF2C(fn_800D0864(*(const char**)lbl_804CB554));
    p[0x24] = 1;
    fn_800D5448(p, parent, 0);
}

extern "C" void fn_80058798(void) {
    char buf[0x48];
    fn_8023F1A0(fn_801D5DC4(fn_801D5EC8()), 0x80);
    switch (((u8*)fn_80060728(&lbl_803CAB38))[0x11]) {
    case 0:
    case 3:
        strcpy(buf, lbl_80361F9C + 0x26);
        break;
    case 1:
        strcpy(buf, lbl_80361F9C + 0x3a);
        break;
    case 2:
        strcpy(buf, lbl_80361F9C + 0x4e);
        break;
    }
    fn_8023F1A0(buf, 0x80);
}
