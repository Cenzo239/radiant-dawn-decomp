#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_80052440(void) {
    fn_800620A8(&lbl_803CAB38, lbl_803CA870.x11, lbl_803CA870.y12);
    fn_8013F204();
}

extern "C" void fn_800524B4(MenuProc* b) {
    UnitCmdState* st = &lbl_803CA870;
    if (st->i18 == 3) {
        MenuProc* p = fn_80081194(lbl_8037D950, b);
        p->cursor = st->b0c == 0x33 ? fn_80062A9C(&lbl_803CAB38, 0) : fn_80062A9C(&lbl_803CAB38, 3);
    }
}
