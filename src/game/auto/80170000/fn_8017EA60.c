#include "game/auto/m2c_prelude.h"
s8 *fn_8017EA60(s8 *arg0, s32 *arg1) {
    if ((s32) *arg1 != (s16) M2C_FIELD(arg0, s16 *, 0x30)) {
        return NULL;
    }
    return arg0;
}
