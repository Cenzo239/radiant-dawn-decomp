#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on

extern "C" int fn_80050DE4(void* a, Menu* b, MenuEntry* c) {
    if (c->active) {
        helpBox(b, c, lbl_8037D760);
        return 0;
    }
    fn_800453B4(&lbl_803CA870, 0x4e);
    return 5;
}
