#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
#else
M2C_UNK fn_80083B78();
#endif

void fn_80169294(s8 *arg0) {
    u32 (*temp_r12)();
    u32 var_r3;

    temp_r12 = M2C_FIELD(arg0, u32 (**)(), 0x30);
    if (temp_r12 != NULL) {
        var_r3 = temp_r12();
    } else {
        var_r3 = 1U;
    }
    if (var_r3 == 1U) {
        fn_80083B78(arg0);
    }
}
