#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8005E644(void* a, Menu* m, MenuEntry* e) {
    if (e->active == 2) {
        MenuBox* b = (MenuBox*)m;
        fn_801E6B64(lbl_8037F61C, m, b->x + e->x, b->y + e->y);
        return 0;
    }
    fn_800453B4(&lbl_803CA870, 0x8e);
    lbl_804CB550 = 0x8e;
    return 5;
}
