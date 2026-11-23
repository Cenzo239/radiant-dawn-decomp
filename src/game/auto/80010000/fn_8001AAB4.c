#include "game/auto/m2c_prelude.h"
s32 fn_8030585C();

s32 fn_8001AAB4(void) {
    s32 temp_r31;

    temp_r31 = fn_8030585C(0x130, 0xE0, 6, 0, 0);
    return temp_r31 + fn_8030585C(0x260, 0x1C0, 6, 0, 0);
}
