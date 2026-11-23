#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_80050994(void) {
    fn_800453B4(&lbl_803CA870, 0x15);
    return 0x5;
}

extern "C" const char* fn_800509C4(void) {
    return fn_800D0864(lbl_8037D6A0);
}

extern "C" const char* fn_800509D0(void) {
    return fn_800D0864(lbl_8037D694);
}

extern "C" int fn_800509DC(Bytes8* a) {
    int i;
    if (lbl_803CA870.b16) {
        return 3;
    }
    for (i = 0; i < 7; i++) {
        ItemSlot* s = cmdItem(i);
        if (s == 0 || s->data == 0) {
            break;
        }
        if ((fn_801116B8(s)->flags4 & 1) && (fn_801116B8(s)->flags4 & 0x10) == 0 &&
            fn_8012BA20(lbl_803CA870.unit, s->data)) {
            fn_80039C40(lbl_803CA870.unit, s->data);
            if (lbl_803E7320.i0) {
                a->b[4] = fn_800CFB4C(&lbl_803E7320);
                return 0;
            }
        }
    }
    return 3;
}

extern "C" int fn_80050AC4(void) {
    fn_800453B4(&lbl_803CA870, 0x28);
    return 0x5;
}

extern "C" const char* fn_80050AF4(Bytes8* p) {
    switch (p->b[4]) {
    case 0xb1:
        return fn_800D0864(lbl_8037D700);
    case 0xb6:
        return fn_800D0864(lbl_8037D6F4);
    case 0x71:
        return fn_800D0864(lbl_8037D6E8);
    default:
        return fn_800D0864(lbl_8037D6DC);
    }
}

extern "C" const char* fn_80050B4C(Bytes8* p) {
    switch (p->b[4]) {
    case 0xb1:
        return fn_800D0864(lbl_8037D6D0);
    case 0xb6:
        return fn_800D0864(lbl_8037D6C4);
    case 0x71:
        return fn_800D0864(lbl_8037D6B8);
    default:
        return fn_800D0864(lbl_8037D6AC);
    }
}

extern "C" int fn_80050BA4(void) {
    fn_800453B4(&lbl_803CA870, 0xf);
    return 0x5;
}

extern "C" const char* fn_80050BD4(void) {
    return fn_800D0864(lbl_8037D718);
}

extern "C" const char* fn_80050BE0(void) {
    return fn_800D0864(lbl_8037D70C);
}

extern "C" int fn_80050BEC(void) {
    fn_800453B4(&lbl_803CA870, 0x2);
    return 0x5;
}

extern "C" int fn_80050C1C(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (fn_8012BCB0(lbl_803CA870.unit)) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D73C)) {
        return 3;
    }
    return 0;
}

extern "C" const char* fn_80050DD0(void) {
    return fn_800D0864(lbl_804CA280);
}

extern "C" const char* fn_80050DD8(void) {
    return fn_800D0864(lbl_8037D730);
}
