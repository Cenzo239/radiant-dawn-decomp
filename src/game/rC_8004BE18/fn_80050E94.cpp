#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_80050E94(void) {
    u8 v;
    if (lbl_803CA870.b16) {
        return 3;
    }
    v = lbl_803CAB38.b10;
    if (v != 0 && v < 5) {
        return 3;
    }
    fn_8003A30C(lbl_803CA870.unit);
    if (lbl_803E7320.i0 == 0) {
        return 3;
    }
    return fn_8011EF14(lbl_803CA870.unit, 0) ? 0 : 2;
}

extern "C" const char* fn_80050F3C(void) {
    return fn_800D0864(lbl_8037D754);
}

extern "C" const char* fn_80050F48(void) {
    return fn_800D0864(lbl_8037D748);
}
