#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800C3584(void *);
#else
M2C_UNK fn_800C3584();
#endif

s32 fn_801D0BAC(
#if TARGET_PC
s8 *arg0, s32 arg1, void *arg2
#else
s8 *arg0, s32 arg1, s32 arg2
#endif
) {
    fn_800C3584(0);
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 0x18) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    return 1;
}
