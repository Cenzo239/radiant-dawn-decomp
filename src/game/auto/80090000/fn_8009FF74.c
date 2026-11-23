#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8009FC94(unsigned char *);
FE10_PROTO void * fn_800C3BC8(void *);
#else
s32 fn_8009FC94();
s8 * fn_800C3BC8();
#endif

s32 fn_8009FF74(void) {
    s8 *var_r31;

    var_r31 = fn_800C3BC8(NULL);
    goto loop_5;
block_1:
    if ((s32) M2C_FIELD(var_r31, u8 *, 0xC) != 8) {
        goto block_4;
    }
    if (fn_8009FC94(var_r31) == 0) {
        goto block_4;
    }
    return 1;
block_4:
    var_r31 = fn_800C3BC8(var_r31);
loop_5:
    if (var_r31 != NULL) {
        goto block_1;
    }
    return 0;
}
