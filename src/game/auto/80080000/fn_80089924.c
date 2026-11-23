#include "game/auto/m2c_prelude.h"
s32 fn_80011E20();

s32 fn_80089924(s8 *arg0) {
    if (fn_80011E20() != 0) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 4);
    return 1;
}
