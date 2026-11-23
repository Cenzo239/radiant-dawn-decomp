#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80008F20(void *, unsigned char, ...);
#else
M2C_UNK fn_80008F20();
#endif

void fn_801CB190(s8 *arg0) {
    s32 temp_r5;

    temp_r5 = M2C_FIELD(arg0, s32 *, 0x30);
    fn_80008F20(temp_r5 + 0x14, M2C_FIELD(arg0, u8 *, 0x3D), temp_r5);
}
