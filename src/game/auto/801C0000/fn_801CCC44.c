#include "game/auto/m2c_prelude.h"
void fn_801CCC44(s8 *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0) & 1) {
        if (arg1 != 0) {
            M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & 0xF7FFFFFF);
            return;
        }
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x08000000);
        return;
    }
    if (arg1 != 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x08000000);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & 0xF7FFFFFF);
}
