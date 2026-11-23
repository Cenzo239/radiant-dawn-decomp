#include "game/auto/m2c_prelude.h"
s32 fn_80068D74();
#if TARGET_PC
FE10_PROTO void fn_800E515C(void *);
FE10_PROTO void fn_800E56B8(char *);
#else
M2C_UNK fn_800E515C();
M2C_UNK fn_800E56B8();
#endif

void fn_800E3614(s8 *arg0) {
    s32 temp_r3;
    s32 var_r0;

    temp_r3 = M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), s32 *, 0x18);
    if (!(temp_r3 & 0x30)) {
        var_r0 = 1;
    } else if (temp_r3 & 0x10) {
        var_r0 = 0;
    } else if ((temp_r3 & 0x20) && (fn_80068D74() == 0)) {
        var_r0 = 0;
    } else {
        var_r0 = 1;
    }
    if (var_r0 != 0) {
        fn_800E515C(arg0);
        fn_800E56B8(arg0);
    }
}
