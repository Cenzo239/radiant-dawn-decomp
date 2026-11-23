#include "game/auto/m2c_prelude.h"
s32 fn_80108F68(s8 *arg0) {
    u16 temp_r3;
    u16 temp_r4;

    temp_r4 = M2C_FIELD(arg0, u16 *, 0);
    if ((temp_r4 >> 0xDU) & 7) {
        return 1;
    }
    if ((temp_r4 >> 7U) & 7) {
        return 1;
    }
    if ((temp_r4 >> 4U) & 7) {
        return 1;
    }
    if ((temp_r4 >> 0xAU) & 7) {
        return 1;
    }
    if ((temp_r4 >> 1U) & 7) {
        return 1;
    }
    if (temp_r4 & 1) {
        return 1;
    }
    temp_r3 = M2C_FIELD(arg0, u16 *, 2);
    if ((temp_r3 >> 0xEU) & 3) {
        return 1;
    }
    if ((temp_r3 >> 0xCU) & 3) {
        return 1;
    }
    if ((temp_r3 >> 0xAU) & 3) {
        return 1;
    }
    return ((temp_r3 >> 8U) & 3) != 0;
}
