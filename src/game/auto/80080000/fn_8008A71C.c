#include "game/auto/m2c_prelude.h"
M2C_UNK strcpy();
s32 strlen();

void fn_8008A71C(
#if TARGET_PC
s8 *arg0, s8 *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    s32 temp_r31;

    temp_r31 = strlen(arg1);
    strcpy(M2C_FIELD(arg0, s32 *, 4), arg1);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_r31 + M2C_FIELD(arg0, s32 *, 4) + 1);
}
