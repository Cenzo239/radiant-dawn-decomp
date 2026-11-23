#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8013BE90(void *, int);
#else
M2C_UNK fn_8013BE90();
#endif
M2C_UNK fn_8013BED8();
s32 fn_80171494();

s32 fn_801719A4(
#if TARGET_PC
void *arg0, s32 arg1, s16 *arg2, s16 *arg3
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3
#endif
) {
    s32 temp_r31;

    fn_8013BE90(0, 9);
    temp_r31 = fn_80171494(arg0, 1, arg1, arg2, arg3);
    fn_8013BED8();
    return temp_r31;
}
