#include "game/auto/m2c_prelude.h"
s8 *fn_80025FA4(s8 *arg0) {
    if ((s8) M2C_FIELD(arg0, u8 *, 0xA6) == 0) {
        return NULL;
    }
    return arg0 + 0xA6;
}
