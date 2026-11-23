#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_800526C8(void) {
    return 0x4;
}

extern "C" const char* fn_800526D0(void) {
    if (lbl_804CB3F8 == 0x33) {
        return fn_800D0864(lbl_804CA2D8);
    }
    return fn_800D0864(lbl_804CA2D0);
}

extern "C" const char* fn_800526EC(void) {
    if (lbl_804CB3F8 == 0x33) {
        return fn_800D0864(lbl_804CA2C8);
    }
    return fn_800D0864(lbl_804CA2C0);
}

extern "C" int fn_80052708(void) {
    return 0x3;
}

extern "C" const char* fn_80052710(void) {
    if (lbl_804CB3F8 == 0x33) {
        return fn_800D0864(lbl_804CA2F8);
    }
    return fn_800D0864(lbl_804CA2F0);
}

extern "C" const char* fn_8005272C(void) {
    if (lbl_804CB3F8 == 0x33) {
        return fn_800D0864(lbl_804CA2E8);
    }
    return fn_800D0864(lbl_804CA2E0);
}

extern "C" int fn_80052748(void) {
    return 0x0;
}

extern "C" const char* fn_80052750(void) {
    if (lbl_804CB3F8 == 0x33) {
        return fn_800D0864(lbl_804CA318);
    }
    return fn_800D0864(lbl_804CA310);
}

extern "C" const char* fn_8005276C(void) {
    if (lbl_804CB3F8 == 0x33) {
        return fn_800D0864(lbl_804CA308);
    }
    return fn_800D0864(lbl_804CA300);
}

extern "C" int fn_80052788(void) {
    return lbl_804CB3F8 == 0x34 ? 0 : 3;
}

extern "C" int fn_800527A8(void) {
    return 0x1;
}

extern "C" const char* fn_800527B0(void) {
    return fn_800D0864(lbl_804CA328);
}

extern "C" const char* fn_800527B8(void) {
    return fn_800D0864(lbl_804CA320);
}

extern "C" int fn_800527C0(void) {
    return lbl_804CB3F8 == 0x33 ? 0 : 3;
}

extern "C" int fn_800527E0(void) {
    return 0x2;
}

extern "C" const char* fn_800527E8(void) {
    return fn_800D0864(lbl_804CA338);
}

extern "C" const char* fn_800527F0(void) {
    return fn_800D0864(lbl_804CA330);
}

extern "C" void fn_800527F8(void) {
    if (fn_80068D74() && !(lbl_804CB700 & 0x80)) {
        fn_80131DE4();
        fn_80133034();
    }
}

extern "C" void fn_80052834(void) {
    s8 y;
    s8 x;
    fn_80131DE4();
    fn_80133034();
    y = lbl_803CAB38.f938;
    x = lbl_803CAB38.f934;
    fn_80140864(x, y);
    fn_80140880();
}
