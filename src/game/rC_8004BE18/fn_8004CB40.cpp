/* fn_8004CB40 (round 24): menu availability check. The flag test is a switch with `default`
 * first, which keeps the branches (`if (x) return 2; return 0;` compiles branchless). */
#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004CB40(void) {
    ItemSlot* s = fn_80044FD0(&lbl_803CA870);
    if (!s->f7) {
        return 3;
    }
    switch (dataFlag4(s)) {
    default:
        return 2;
    case 0:
        return 0;
    }
}
