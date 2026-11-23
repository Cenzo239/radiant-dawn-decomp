#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO int fn_8012FD80(int);
#else
M2C_UNK fn_80083B78();
s32 fn_8012FD80();
#endif

void fn_8017DB38(s8 *arg0) {
    M2C_UNK (*temp_r12)(s32);

    if (fn_8012FD80(M2C_FIELD(arg0, u8 *, 0x34)) == 0) {
        temp_r12 = M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x30);
        if (temp_r12 != NULL) {
            temp_r12(M2C_FIELD(arg0, s32 *, 0x18));
        }
        fn_80083B78(arg0);
    }
}
