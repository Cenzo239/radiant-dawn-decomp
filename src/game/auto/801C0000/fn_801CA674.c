#include "game/auto/m2c_prelude.h"
s8 *fn_801CA674(
#if TARGET_PC
s8 *arg0, void *arg1
#else
s8 *arg0, u32 arg1
#endif
) {
#if TARGET_PC
    if ((u32) M2C_FIELD(arg0, u32 *, 0x30) != (u32) FE10_PTRINT(arg1)) {
        return NULL;
    }
#else
    if ((u32) M2C_FIELD(arg0, u32 *, 0x30) != arg1) {
        return NULL;
    }
#endif
    return arg0;
}
