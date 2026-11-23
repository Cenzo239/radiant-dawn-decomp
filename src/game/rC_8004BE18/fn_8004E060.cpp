#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" const char* fn_8004E060(void) {
    return fn_800D0864(lbl_804CA21C);
}

extern "C" const char* fn_8004E068(void) {
    return fn_800D0864(lbl_804CA218);
}

extern "C" int fn_8004E070(void) {
    fn_800453B4(&lbl_803CA870, 0x23);
    return 0x5;
}
