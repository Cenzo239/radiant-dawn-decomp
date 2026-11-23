#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800A1274(unsigned char *);
FE10_PROTO void * fn_800C3BC8(void *);
#else
s32 fn_800A1274();
s8 * fn_800C3BC8();
#endif

s32 fn_800A1584(void) {
    s8 *var_r31;

    var_r31 = fn_800C3BC8(NULL);
    goto loop_5;
block_1:
    if ((s32) M2C_FIELD(var_r31, u8 *, 0xC) != 0x12) {
        goto block_4;
    }
    if (fn_800A1274(var_r31) == 0) {
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
