#include "game/auto/m2c_prelude.h"
s32 fn_801CE010(s8 *arg0, s8 *arg1) {
    if (((u16) M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), u16 *, 4) == 4) && (arg0 != arg1) && ((s16) M2C_FIELD(arg0, s16 *, 0x3A) == (s16) M2C_FIELD(arg1, s16 *, 0x3A))) {
        if ((s32) M2C_FIELD(arg0, u8 *, 0x3E) != 0) {
            M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(arg0, s16 *, 0x36) - 1);
        } else {
            M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(arg0, s16 *, 0x36) + 1);
        }
    }
    return 0;
}
