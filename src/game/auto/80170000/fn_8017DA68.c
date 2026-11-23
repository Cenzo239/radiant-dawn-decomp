#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
#else
M2C_UNK fn_80083B78();
#endif
s32 fn_8023F880(void *);

void fn_8017DA68(s8 *arg0) {
    M2C_UNK (*temp_r12)(s32);
    u16 temp_r4;

    temp_r4 = M2C_FIELD(arg0, u16 *, 0x70);
    M2C_FIELD(arg0, u16 *, 0x70) = (u16) (temp_r4 + 1);
    if ((temp_r4 > 0x2A30U) || (fn_8023F880(arg0 + 0x30) != 0)) {
        temp_r12 = M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x78);
        if (temp_r12 != NULL) {
            temp_r12(M2C_FIELD(arg0, s32 *, 0x18));
        }
        fn_80083B78(arg0);
    }
}
