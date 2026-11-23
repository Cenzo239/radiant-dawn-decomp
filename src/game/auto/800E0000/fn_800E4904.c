#include "game/auto/m2c_prelude.h"
void fn_800E4904(
#if TARGET_PC
s8 *arg0, s32 arg1, void *arg2
#else
s8 *arg0, s32 arg1, s32 arg2
#endif
) {
    M2C_FIELD((M2C_FIELD(arg0, s32 *, 0x30) + (arg1 * 4)), s32 *, 0xA4) = arg2;
}
