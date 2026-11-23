#include "game/auto/m2c_prelude.h"
s32 * fn_80030CB4();
#if TARGET_PC
FE10_PROTO int fn_8010931C(void *);
#else
s32 fn_8010931C();
#endif
s8 * fn_801116B8(s32 *);

s32 fn_8002C774(s8 *arg0, s8 *arg1, s8 *arg2) {
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r31;

    if ((s32) *fn_80030CB4(arg1) == 0) {
        return 0;
    }
    temp_r3 = M2C_FIELD(arg1, s32 *, 0x3F0);
    if ((temp_r3 != 0) && (fn_8010931C(temp_r3 + 0x110) != 0)) {
        return 0;
    }
    var_r31 = 1;
    if (M2C_FIELD(fn_801116B8(fn_80030CB4(arg1)), s32 *, 4) & 0x100) {
        var_r31 = 2;
    }
    temp_r3_2 = M2C_FIELD(arg0, s32 *, 0x15EC);
    if (!(temp_r3_2 & 0x200) && !(temp_r3_2 & 0x8000) && ((s16) M2C_FIELD(arg1, s16 *, 0x44C) >= (s32) (M2C_FIELD(arg2, s16 *, 0x44C) + 4))) {
        var_r31 *= 2;
    }
    return var_r31;
}
