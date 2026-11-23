#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004FD00(void* a, Menu* b, MenuEntry* c) {
    if (c->active) {
        helpBox(b, c, lbl_8037D638);
        return 0;
    }
    if (fn_801116B8(fn_80066D18(fn_80066130(lbl_803CB770, lbl_803CA870.unit->x102,
                                            lbl_803CA870.unit->y103, 7)))->flags0 & 0x200) {
        fn_800453B4(&lbl_803CA870, 0x32);
    } else {
        fn_800453B4(&lbl_803CA870, 0x2b);
    }
    return 5;
}
