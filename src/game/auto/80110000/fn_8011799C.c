#include "game/auto/m2c_prelude.h"
s32 fn_8011799C(s8 *arg0, s8 arg1, s8 arg2) {
    if (arg1 < (s8) M2C_FIELD(arg0, u8 *, 8)) {
        return 0;
    }
    if (arg1 >= (s8) M2C_FIELD(arg0, u8 *, 0xA)) {
        return 0;
    }
    if (arg2 < (s8) M2C_FIELD(arg0, u8 *, 9)) {
        return 0;
    }
    return arg2 < (s8) M2C_FIELD(arg0, u8 *, 0xB);
}
