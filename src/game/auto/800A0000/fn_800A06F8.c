#include "game/auto/m2c_prelude.h"
s8 * fn_800C3BC8(s8 *);

s32 fn_800A06F8(void) {
    s32 var_r31;
    s8 *var_r3;

    var_r31 = 0;
    var_r3 = fn_800C3BC8(0);
    goto loop_4;
block_1:
    if ((s32) M2C_FIELD(var_r3, u8 *, 0xC) != 0xE) {
        goto block_3;
    }
    var_r31 += 1;
block_3:
    var_r3 = fn_800C3BC8(var_r3);
loop_4:
    if (var_r3 != NULL) {
        goto block_1;
    }
    return var_r31;
}
