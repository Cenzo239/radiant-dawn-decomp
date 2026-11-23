#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004C6D0(void* a, Menu* b, MenuEntry* c) {
    if (c->active) {
        helpBoxY(b, c, lbl_804CA1D0);
        return 0;
    }
    fn_800D5448(lbl_803CAA68, b, 0);
    return 4;
}
