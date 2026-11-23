#include "game/auto/m2c_prelude.h"
void fn_800453B4(s8 *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC) = arg1;
    if ((s8) M2C_FIELD(arg0, u8 *, 0x16) == 0) {
        M2C_FIELD(arg0, s8 *, 0xD) = arg1;
    }
}
