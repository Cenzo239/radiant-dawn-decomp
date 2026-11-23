#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80171494();

#if TARGET_PC
s32 fn_80171988(void *p0, s32 arg1, s16 *arg2, s16 *arg3) {
    return fn_80171494(p0, 2, arg1, arg2, arg3);
}
#else
void fn_80171988(s32 p0, s32 arg1, s32 arg2, s32 arg3) {
    fn_80171494(p0, 2, arg1, arg2, arg3, arg1);
}
#endif
