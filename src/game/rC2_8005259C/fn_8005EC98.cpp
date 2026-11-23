#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005EC98(void* p) {
    u8 r;
    if (fn_801E7114(p) == 0) {
        r = 2;
    } else {
        r = lbl_804CB550 == 0x89;
    }
    return r;
}

extern "C" char* fn_8005ECD8(void) {
    return lbl_8037F560;
}

extern "C" const char* fn_8005ECE4(void) {
    return fn_800D0864(lbl_8037F554);
}
