#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004C954(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (lbl_803CA870.b28 & 2) {
        return 3;
    }
    fn_800399B0(lbl_803CA870.unit, lbl_803CA870.itemIdx);
    if (lbl_803E7320.i0 == 0) {
        return 3;
    }
    if (dataFlag4(fn_80044FD0(&lbl_803CA870)) || isUnusableA(fn_80044FD0(&lbl_803CA870))) {
        return 2;
    }
    return 0;
}
