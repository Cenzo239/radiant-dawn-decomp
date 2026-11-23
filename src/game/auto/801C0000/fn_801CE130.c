#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80078E24(void *);
#else
M2C_UNK fn_80078E24();
#endif

void fn_801CE130(s8 *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x60);
    if (temp_r0 != 0) {
        fn_80078E24(temp_r0);
        M2C_FIELD(arg0, s32 *, 0x60) = 0;
    }
}
