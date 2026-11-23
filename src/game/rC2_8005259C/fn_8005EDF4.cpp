#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005EDF4(void* p) {
    u8 r;
    if (fn_801E70C4(p) == 0) {
        r = 2;
    } else {
        r = lbl_804CB550 == 0x88;
    }
    return r;
}

extern "C" char* fn_8005EE34(void) {
    return lbl_8037F534;
}

extern "C" const char* fn_8005EE40(void) {
    return fn_800D0864(lbl_8037F528);
}
