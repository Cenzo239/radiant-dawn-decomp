#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8014C2AC(void *, ...);
FE10_PROTO void * fn_801E5640(void *, int, int, ...);
#else
M2C_UNK fn_8014C2AC();
s8 * fn_801E5640();
#endif

void fn_8020411C(s8 *arg0) {
    s32 temp_r31;
    s8 *temp_r3;
    s8 *temp_r4;
    s8 *temp_r6;

    temp_r4 = M2C_FIELD(arg0, s8 **, 0x48);
    fn_8014C2AC(M2C_FIELD(temp_r4, s32 *, 0x20), temp_r4);
    temp_r6 = M2C_FIELD(arg0, s8 **, 0x48);
    temp_r31 = M2C_FIELD(temp_r6, s32 *, 0x38);
    temp_r3 = fn_801E5640(arg0, -0x1000, 0, temp_r6);
    if (temp_r3 != NULL) {
        M2C_FIELD(temp_r3, s32 *, 0x64) = temp_r31;
    }
}
