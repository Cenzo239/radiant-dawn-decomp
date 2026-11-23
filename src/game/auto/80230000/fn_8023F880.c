#include "game/auto/m2c_prelude.h"
s8 * fn_8023DCC0(void *);

s32 fn_8023F880(void *arg0) {
    s8 *temp_r3;

    temp_r3 = fn_8023DCC0(arg0);
    if (temp_r3 == NULL) {
        return 1;
    }
    return ((u32) M2C_FIELD(temp_r3, u32 *, 0x50) >> 0x15U) & 1;
}
