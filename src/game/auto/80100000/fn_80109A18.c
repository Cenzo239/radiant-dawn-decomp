#include "game/auto/m2c_prelude.h"
u8 fn_80109A18(u8 **arg0) {
    u8 *temp_r4;

    temp_r4 = *arg0;
    *arg0 = temp_r4 + 1;
    return *temp_r4;
}
