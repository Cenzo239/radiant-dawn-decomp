#include "game/auto/m2c_prelude.h"
s8 *fn_8017C298(s8 *arg0, u16 *arg1) {
    if ((u16) *arg1 != (u16) M2C_FIELD(arg0, u16 *, 0x3C)) {
        return NULL;
    }
    return arg0;
}
