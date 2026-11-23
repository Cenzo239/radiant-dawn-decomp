/* fn_8004DB80 (round 24): menu availability check. The last test is `>= 30 ? 0 : 3`; the old
 * near-miss draft had it inverted (`< 30 ? 0 : 3`), which is why its compare never matched. */
#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004DB80(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4EC)) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4F0)) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4F4)) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA5E0)) {
        return 0;
    }
    return fn_801284C4(lbl_803CA870.unit) >= 0x1e ? 0 : 3;
}
