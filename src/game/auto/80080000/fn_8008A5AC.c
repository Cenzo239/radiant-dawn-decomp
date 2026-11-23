#include "game/auto/m2c_prelude.h"
void fn_8008A5AC(s8 *arg0, s8 arg1) {
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 4);
    *temp_r5 = arg1;
    M2C_FIELD(arg0, s8 **, 4) = (s8 *) (temp_r5 + 1);
}
