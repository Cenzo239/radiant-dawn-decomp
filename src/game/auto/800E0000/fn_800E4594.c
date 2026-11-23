#include "game/auto/m2c_prelude.h"
s8 *fn_800E4594(s8 *arg0, u16 *arg1) {
    if ((u16) *arg1 != (u16) M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), u16 *, 4)) {
        return NULL;
    }
    return arg0;
}
