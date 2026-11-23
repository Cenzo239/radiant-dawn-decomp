#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
u8 fn_80325A2C();

s32 fn_801099A0(void) {
    switch (fn_80325A2C()) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 2;
    default:
        return 1;
    }
}
