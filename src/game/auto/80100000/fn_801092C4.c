#include "game/auto/m2c_prelude.h"
s32 fn_801092C4(u16 *arg0) {
    u16 temp_r3;

    temp_r3 = *arg0;
    if ((temp_r3 >> 0xDU) & 7) {
        return 1;
    }
    if ((temp_r3 >> 7U) & 7) {
        return 1;
    }
    if ((temp_r3 >> 4U) & 7) {
        return 1;
    }
    if ((temp_r3 >> 0xAU) & 7) {
        return 1;
    }
    return ((temp_r3 >> 1U) & 7) != 0;
}
