#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800106AC(int, void *, void *);
#else
M2C_UNK fn_800106AC();
#endif

s32 fn_80089504(s8 *arg0) {
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, s8 **, 4);
    fn_800106AC((s16) ((u32) M2C_FIELD(temp_r4, u32 *, 0) >> 0x10U), M2C_FIELD(temp_r4, s32 *, 4), arg0);
    M2C_FIELD(arg0, s8 **, 4) = (s8 *) (M2C_FIELD(arg0, s8 **, 4) + 8);
    return 1;
}
