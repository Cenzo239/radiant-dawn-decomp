#include "game/auto/m2c_prelude.h"
s8 *fn_80104AA4(s8 *arg0, s8 *arg1) {
    if ((u32) M2C_FIELD(arg0, u32 *, 0x30) != (u32) M2C_FIELD(arg1, u32 *, 0x30)) {
        return NULL;
    }
    return arg0;
}
