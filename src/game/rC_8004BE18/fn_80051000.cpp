#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_80051000(void) {
    if (lbl_803CA870.b28 & 1) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    fn_8003A2A4(lbl_803CA870.unit);
    if (lbl_803E7320.i0 == 0) {
        return 3;
    }
    return fn_8011EF14(lbl_803CA870.unit, 0) ? 0 : 2;
}

extern "C" const char* fn_80051094(void) {
    return fn_800D0864(lbl_8037D778);
}

extern "C" const char* fn_800510A0(void) {
    return fn_800D0864(lbl_8037D76C);
}

extern "C" int fn_800510AC(void) {
    fn_8003AEEC(lbl_803CA870.unit);
    {
        Pos8* p = fn_800CFD18(&lbl_803E7320, 0);
        u8 y = p->y;
        u8 x = p->x;
        lbl_803CA870.pos13.x = x;
        lbl_803CA870.pos13.y = y;
    }
    fn_800453B4(&lbl_803CA870, 0x3b);
    return 5;
}

extern "C" int fn_80051110(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    fn_8003AEEC(lbl_803CA870.unit);
    return lbl_803E7320.i0 == 0 ? 3 : 0;
}

extern "C" const char* fn_80051168(void) {
    return fn_800D0864(lbl_8037D798);
}

extern "C" const char* fn_80051174(void) {
    return fn_800D0864(lbl_8037D784);
}

extern "C" int fn_80051180(void) {
    fn_8003ADE0(lbl_803CA870.unit);
    {
        Pos8* p = fn_800CFD18(&lbl_803E7320, 0);
        u8 y = p->y;
        u8 x = p->x;
        lbl_803CA870.pos13.x = x;
        lbl_803CA870.pos13.y = y;
    }
    fn_800453B4(&lbl_803CA870, 0x37);
    return 5;
}

extern "C" int fn_800511E4(Bytes8* a) {
    u8 k;
    if (lbl_803CA870.b16) {
        return 3;
    }
    fn_8003ADE0(lbl_803CA870.unit);
    if (lbl_803E7320.i0 == 0) {
        return 3;
    }
    k = a->b[4] = fn_800CFB4C(&lbl_803E7320);
    switch (k) {
    case 0xaa:
        if (lbl_803CA870.unit->f4->b8 != 0) {
            return 3;
        }
        break;
    case 0x80:
        if (lbl_803CA870.unit->f4->b8 == 0) {
            return 3;
        }
        break;
    case 0x2c:
        break;
    }
    return 0;
}

extern "C" const char* fn_800512C0(void) {
    return fn_800D0864(lbl_8037D7B4);
}

extern "C" const char* fn_800512CC(void) {
    return fn_800D0864(lbl_8037D7A8);
}
