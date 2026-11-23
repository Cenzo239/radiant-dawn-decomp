#include "game/auto/m2c_prelude.h"
s32 fn_80245DFC(s8 *);
s8 * fn_8024BCA0();

s32 fn_8009ADD8(s32 arg0) {
    s8 *temp_r31;

    temp_r31 = fn_8024BCA0();
    if (fn_80245DFC(temp_r31) == 0) {
        return 0;
    }
    if (arg0 != 0) {
        M2C_FIELD(temp_r31, s32 *, 0x40) = (s32) (M2C_FIELD(temp_r31, s32 *, 0x40) | 0x40);
    } else {
        M2C_FIELD(temp_r31, s32 *, 0x40) = (s32) (M2C_FIELD(temp_r31, s32 *, 0x40) & 0xFFFFFFBF);
    }
    return 1;
}
