#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8005E3C0(void* a, Menu* m, MenuEntry* e) {
    if (e->active == 2) {
        MenuBox* b = (MenuBox*)m;
        fn_801E6B64(lbl_8037F664, m, b->x + e->x, b->y + e->y);
        return 0;
    }
    fn_800453B4(&lbl_803CA870, 0x90);
    lbl_804CB550 = 0x90;
    return 5;
}
