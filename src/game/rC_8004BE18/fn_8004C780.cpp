#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004C780(void) {
    ItemSlot* s = fn_80044FD0(&lbl_803CA870);
    return (dataFlagB(s) || slotF4(s)) ? 2 : 0;
}

extern "C" const char* fn_8004C7F0(void) {
    return fn_800D0864(lbl_8037D30C);
}

extern "C" const char* fn_8004C7FC(void) {
    return fn_800D0864(lbl_8037D300);
}

extern "C" const char* fn_8004C808(void) {
    return fn_800D0864(lbl_8037D494);
}

extern "C" const char* fn_8004C814(void) {
    return fn_800D0864(lbl_8037D488);
}
