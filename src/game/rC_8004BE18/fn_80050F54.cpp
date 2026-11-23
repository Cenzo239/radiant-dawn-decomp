#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on

extern "C" int fn_80050F54(void* a, Menu* b, MenuEntry* c) {
    if (c->active) {
        helpBox(b, c, lbl_804CA288);
        return 0;
    }
    fn_800453B4(&lbl_803CA870, 7);
    return 5;
}
