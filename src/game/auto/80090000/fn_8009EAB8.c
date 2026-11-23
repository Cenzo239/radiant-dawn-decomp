#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800C3BC8(void *);
#else
s8 * fn_800C3BC8();
#endif

s32 fn_8009EAB8(s32 arg0, s32 (*arg1)(s8 *)) {
    s32 var_r31;
    s8 *var_r30;

    var_r31 = 0;
    var_r30 = fn_800C3BC8(NULL);
    goto loop_5;
block_1:
    if ((s8) M2C_FIELD(var_r30, u8 *, 0xC) != arg0) {
        goto block_4;
    }
    if (arg1(var_r30) == 0) {
        goto block_4;
    }
    var_r31 += 1;
block_4:
    var_r30 = fn_800C3BC8(var_r30);
loop_5:
    if (var_r30 != NULL) {
        goto block_1;
    }
    return var_r31;
}
