#include "game/auto/m2c_prelude.h"
s16 fn_800262F4(
#if TARGET_PC
u8 *arg0, u32 arg1
#else
s32 arg0, u32 arg1
#endif
) {
    u8 temp_r0;
    s8 *var_r3;

    var_r3 = (void *)(arg0 + 4);
loop_1:
    temp_r0 = M2C_FIELD(var_r3, u8 *, 0);
    if ((s32) temp_r0 != 0) {
        if (arg1 == temp_r0) {
            return M2C_FIELD(var_r3, s16 *, 2);
        }
        var_r3 += 4;
        goto loop_1;
    }
    return 0;
}
