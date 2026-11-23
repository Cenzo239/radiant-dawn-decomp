#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800F4B94(void *, int);
#else
M2C_UNK fn_800F4B94();
#endif

void fn_80100F40(s8 *arg0) {
    M2C_UNK (*temp_r12)(s32);

    if ((s32) M2C_FIELD(arg0, u8 *, 0x54) == 0) {
        fn_800F4B94(M2C_FIELD(arg0, s32 *, 0x30), -1);
    }
    if ((s32) M2C_FIELD(arg0, u8 *, 0x55) == 0) {
        temp_r12 = M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x4C);
        if (temp_r12 != NULL) {
            temp_r12(M2C_FIELD(arg0, s32 *, 0x50));
        }
    }
}
