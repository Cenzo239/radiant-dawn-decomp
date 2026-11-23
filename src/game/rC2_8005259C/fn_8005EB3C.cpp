#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005EB3C(void* p) {
    u8 r;
    if (fn_801E7164(p) == 0) {
        r = 2;
    } else {
        r = lbl_804CB550 == 0x8a;
    }
    return r;
}

extern "C" char* fn_8005EB7C(void) {
    return lbl_8037F58C;
}

extern "C" const char* fn_8005EB88(void) {
    return fn_800D0864(lbl_8037F580);
}
