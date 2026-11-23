#include "game/auto/m2c_prelude.h"
s32 fn_801D0374(u8 *arg0) {
    u8 temp_r0;

    temp_r0 = *arg0;
    if ((s8) temp_r0 >= 0) {
        return 1 - (s8) temp_r0;
    }
    return -1;
}
