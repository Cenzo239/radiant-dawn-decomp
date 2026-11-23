#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s32 fn_8023F87C(void);
#else
s32 fn_8023F87C();
#endif

s32 fn_80089970(s8 *arg0) {
    if (fn_8023F87C() == 0) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 4);
    return 1;
}
