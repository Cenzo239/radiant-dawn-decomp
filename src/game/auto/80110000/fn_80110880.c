#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO short fn_80123998(void *);
#else
s16 fn_80123998();
#endif

u8 fn_80110880(
#if TARGET_PC
s8 *arg0, void *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    s16 temp_r3;
    u8 var_r3;

    var_r3 = M2C_FIELD(arg0, u8 *, 0x21);
    if (var_r3 == 0xFF) {
        temp_r3 = fn_80123998(arg1);
        var_r3 = (u8) ((u32) (((u32) temp_r3 >> 0x1FU) + temp_r3) >> 1U);
        if (var_r3 > 0xFU) {
            var_r3 = 0xF;
        }
        if (var_r3 < 5U) {
            var_r3 = 5;
        }
    }
    return var_r3;
}
