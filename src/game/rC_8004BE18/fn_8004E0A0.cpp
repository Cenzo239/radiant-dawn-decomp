#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on

/* The unit is read through an accessor inline: as a named local or a direct
 * global read it took r28 instead of r29. */
static inline Unit* curUnit() { return lbl_803CA870.unit; }

extern "C" int fn_8004E0A0(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA658) == 0) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D47C)) {
        return 3;
    }
    fn_8003A664(curUnit(), fn_8010B228(lbl_8037D470));
    return lbl_803E7320.i0 == 0 ? 3 : 0;
}
