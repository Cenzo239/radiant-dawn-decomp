#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" u8 fn_8005F304(void) {
    switch (fn_80083B84(lbl_8037E248)->state40) {
    default:
        return 3;
    case 2:
    case 3:
    case 4:
    case 6:
        return lbl_804CB550 == 0x85;
    }
}

extern "C" char* fn_8005F36C(void) {
    return lbl_8037F46C;
}

extern "C" const char* fn_8005F378(void) {
    return fn_800D0864(lbl_8037F460);
}
