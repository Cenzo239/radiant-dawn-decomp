#include "game/auto/m2c_prelude.h"
void fn_801791E0(s8 *arg0) {
    if ((s32) M2C_FIELD(arg0, u8 *, 0x5C) != 0) {
        M2C_FIELD(arg0, s32 *, 0x54) = 0x1E;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x54) = 1;
}
