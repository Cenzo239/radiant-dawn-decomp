#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004DC68(void) {
    fn_800453B4(&lbl_803CA870, 0x3d);
    return 0x5;
}

extern "C" const char* fn_8004DC98(void) {
    return fn_800D0864(lbl_8037D424);
}

extern "C" const char* fn_8004DCA4(void) {
    return fn_800D0864(lbl_8037D418);
}

extern "C" int fn_8004DCB0(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA62C) == 0) {
        return 3;
    }
    fn_8003B514(lbl_803CA870.unit);
    return lbl_803E7320.i0 == 0 ? 3 : 0;
}

extern "C" int fn_8004DD30(void) {
    fn_800453B4(&lbl_803CA870, 0x3c);
    return 0x5;
}

extern "C" const char* fn_8004DD60(void) {
    return fn_800D0864(lbl_8037D440);
}

extern "C" const char* fn_8004DD6C(void) {
    return fn_800D0864(lbl_8037D430);
}
