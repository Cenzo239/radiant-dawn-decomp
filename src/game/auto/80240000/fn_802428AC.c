#include "game/auto/m2c_prelude.h"
s32 fn_800A06F8();
#if TARGET_PC
FE10_PROTO int fn_800A07B8(int);
FE10_PROTO int fn_800A08F0(int);
#else
s32 fn_800A07B8();
s32 fn_800A08F0();
#endif

s32 fn_802428AC(void) {
    s32 temp_r31;
    s32 var_r30;

    temp_r31 = fn_800A06F8();
    var_r30 = 0;
    goto loop_5;
block_1:
    if (fn_800A08F0(var_r30) == 0) {
        goto block_4;
    }
    if (fn_800A07B8(var_r30) != 0) {
        goto block_4;
    }
    return 1;
block_4:
    var_r30 += 1;
loop_5:
    if (var_r30 < temp_r31) {
        goto block_1;
    }
    return 0;
}
