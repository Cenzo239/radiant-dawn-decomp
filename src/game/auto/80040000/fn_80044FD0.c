#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
u8 *fn_80044FD0(s8 *arg0) {
    return M2C_FIELD(arg0, u8 **, 0) + M2C_FIELD(arg0, s8 *, 0xE) * 0x28 + 0x1BC;
}
