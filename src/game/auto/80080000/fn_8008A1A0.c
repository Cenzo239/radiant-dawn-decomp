#include "game/auto/m2c_prelude.h"
u8 fn_8008A1A0(s8 *arg0) {
    u8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, u8 **, 4);
    M2C_FIELD(arg0, u8 **, 4) = (u8 *) (temp_r4 + 1);
    return *temp_r4;
}
