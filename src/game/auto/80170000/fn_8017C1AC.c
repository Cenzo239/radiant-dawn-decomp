#include "game/auto/m2c_prelude.h"
void fn_8017C1AC(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x38) = (s16) M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), u8 *, 0x26);
    M2C_FIELD(arg0, s16 *, 0x3A) = 0;
    M2C_FIELD(arg0, s16 *, 0x34) = 0;
    if (arg1 < 0) {
        M2C_FIELD(arg0, s16 *, 0x36) = 0x10;
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x36) = arg1;
}
