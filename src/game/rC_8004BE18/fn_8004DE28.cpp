#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004DE28(void) {
    return 0x3;
}

extern "C" const char* fn_8004DE30(void) {
    return fn_800D0864(lbl_804CA210);
}

extern "C" const char* fn_8004DE38(void) {
    return fn_800D0864(lbl_804CA208);
}

extern "C" int fn_8004DE40(void) {
    fn_800453B4(&lbl_803CA870, 0x22);
    return 0x5;
}
