#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO int fn_800FAE98(void *);
#else
M2C_UNK fn_80083B78();
s32 fn_800FAE98();
#endif

void fn_80104908(s8 *arg0) {
    if (fn_800FAE98(M2C_FIELD(arg0, s32 *, 0x30)) != 0) {
        fn_80083B78(arg0);
    }
}
