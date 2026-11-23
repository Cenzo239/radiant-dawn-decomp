#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s16 fn_80123998(void *);
#else
s16 fn_80123998(s32);
#endif

u8 fn_801108F8(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    s16 temp_r3;
    u8 var_r3;

    temp_r3 = fn_80123998(arg0);
    var_r3 = (u8) ((u32) (((u32) temp_r3 >> 0x1FU) + temp_r3) >> 1U);
    if (var_r3 < 3U) {
        var_r3 = 3;
    }
    if (var_r3 > 0x14U) {
        var_r3 = 0x14;
    }
    return var_r3;
}
