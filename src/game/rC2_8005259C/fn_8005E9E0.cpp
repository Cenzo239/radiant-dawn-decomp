#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005E9E0(void* p) {
    u8 r;
    if (fn_801E71B4(p) == 0) {
        r = 2;
    } else {
        r = lbl_804CB550 == 0x8b;
    }
    return r;
}

extern "C" char* fn_8005EA20(void) {
    return lbl_8037F5B8;
}

extern "C" const char* fn_8005EA2C(void) {
    return fn_800D0864(lbl_8037F5AC);
}
