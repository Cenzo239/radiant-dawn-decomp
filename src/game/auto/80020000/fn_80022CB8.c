#include "game/auto/m2c_prelude.h"
void fn_80022CB8(s8 *arg0, s8 *arg1) {
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg1, s8 **, 0x2C);
    M2C_FIELD(arg1, s8 **, 0x2C) = arg0;
    *temp_r5 = 1;
}
