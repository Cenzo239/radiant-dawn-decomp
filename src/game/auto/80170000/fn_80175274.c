#include "game/auto/m2c_prelude.h"
void fn_80175274(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0x26) = (u8) (M2C_FIELD(arg0, u8 *, 0x26) | arg1);
}
