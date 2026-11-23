#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800C835C(int, int);
#else
M2C_UNK fn_800C835C();
#endif

u32 fn_8008956C(s8 *arg0) {
    u8 temp_r31;
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, s8 **, 4);
    temp_r31 = (u8) ((u32) M2C_FIELD(temp_r4, u32 *, 0) >> 0x10U);
    fn_800C835C(temp_r31, M2C_FIELD(temp_r4, s32 *, 4));
    M2C_FIELD(arg0, s8 **, 4) = (s8 *) (M2C_FIELD(arg0, s8 **, 4) + 8);
    return (u32) ((7 - temp_r31) | (temp_r31 - 7)) >> 0x1FU;
}
