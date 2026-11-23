#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s8 * fn_8023DCC0(char *);
#else
s8 * fn_8023DCC0(s32);
#endif

s32 fn_8023F8EC(
#if TARGET_PC
s8 *arg0
#else
s32 arg0
#endif
) {
    s8 *temp_r3;

    temp_r3 = fn_8023DCC0(arg0);
    if ((temp_r3 == NULL) || ((s32) M2C_FIELD(temp_r3, u16 *, 0x54) == 0)) {
        return 0;
    }
    return M2C_FIELD(temp_r3, s32 *, 0x60);
}
