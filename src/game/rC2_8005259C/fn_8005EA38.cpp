#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8005EA38(void* a, Menu* m, MenuEntry* e) {
    if (e->active == 2) {
        HELP_XY();
        fn_801E6B64(lbl_8037F598, m, x, y);
        return 0;
    }
    fn_800453B4(&lbl_803CA870, 0x8a);
    lbl_804CB550 = 0x8a;
    return 5;
}
