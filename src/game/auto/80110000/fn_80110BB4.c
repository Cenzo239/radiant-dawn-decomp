#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80110D38(void *);

s32 fn_80110BB4(s8 *arg0, s8 *arg1) {
    fn_80110D38(arg0);
    M2C_FIELD(arg0, s8 **, 0) = arg1;
    M2C_FIELD(arg0, u8 *, 4) = (u8) M2C_FIELD(arg1, u8 *, 0x1B);
    return 1;
}
