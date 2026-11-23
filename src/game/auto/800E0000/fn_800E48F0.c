#include "game/auto/m2c_prelude.h"
void fn_800E48F0(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD((M2C_FIELD(arg0, s32 *, 0x30) + (arg1 * 4)), s32 *, 0xA4) = arg2;
}
