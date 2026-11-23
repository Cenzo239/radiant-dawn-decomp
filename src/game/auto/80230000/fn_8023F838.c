#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s8 * fn_8023DCC0(char *);
#else
s8 * fn_8023DCC0(s32);
#endif

s32 fn_8023F838(
#if TARGET_PC
s8 *arg0
#else
s32 arg0
#endif
) {
    s32 var_r3;
    s8 *temp_r3;

    temp_r3 = fn_8023DCC0(arg0);
    if (temp_r3 == NULL) {
        var_r3 = 0;
    } else {
        var_r3 = M2C_FIELD(temp_r3, s32 *, 0x50) & 0x200000;
    }
    return var_r3 != 0;
}
