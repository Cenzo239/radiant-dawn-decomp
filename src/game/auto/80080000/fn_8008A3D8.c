#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO char * fn_802910CC(char *, char *, unsigned int);
#else
M2C_UNK fn_802910CC();
#endif
s32 strlen();

s32
#if TARGET_PC
*
#endif
fn_8008A3D8(
#if TARGET_PC
s8 *arg0, s8 *arg1, s32 arg2
#else
s8 *arg0, s32 arg1, s32 arg2
#endif
) {
#if TARGET_PC
    u8 *temp_r30;
#else
    s32 temp_r30;
#endif
    s32 temp_r31;

    temp_r30 = M2C_FIELD(arg0, s32 *, 4);
    temp_r31 = strlen(temp_r30);
    fn_802910CC(arg1, temp_r30, arg2);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_r31 + M2C_FIELD(arg0, s32 *, 4) + 1);
    return arg1;
}
