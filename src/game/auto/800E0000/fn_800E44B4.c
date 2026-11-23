#include "game/auto/m2c_prelude.h"
s8 *fn_800E44B4(s8 *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), s32 *, 0x18) & 0x08000000) {
        return NULL;
    }
    return arg0;
}
