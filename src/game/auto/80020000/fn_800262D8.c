#include "game/auto/m2c_prelude.h"
void fn_800262D8(
#if TARGET_PC
u8 *arg0
#else
s32 arg0
#endif
) {
    u8 *var_r3;

    var_r3 = (void *)(arg0 + 4);
loop_1:
    if ((s32) *var_r3 != 0) {
        var_r3 += 4;
        goto loop_1;
    }
}
