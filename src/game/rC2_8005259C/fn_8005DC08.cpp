#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8005DC08(void* a, Menu* m, MenuEntry* e) {
    if (e->active == 2) {
        HELP_XY();
        if (!(lbl_804CB700 & 0x10) && !fn_802450BC(fn_8024BC94())) {
            fn_801E6B64(lbl_8037F744, m, x, y);
        }
        return 0;
    }
    fn_800453B4(&lbl_803CA870, 0x99);
    lbl_804CB550 = 0x99;
    return 5;
}
