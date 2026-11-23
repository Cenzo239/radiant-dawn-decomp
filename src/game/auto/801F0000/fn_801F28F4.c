#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s32 fn_8012BCB0(void *);
#else
s32 fn_8012BCB0(u32);
#endif

s32 fn_801F28F4(
#if TARGET_PC
void *arg0, void *arg1
#else
u32 arg0, u32 arg1
#endif
) {
    if (arg0 == arg1) {
        return 0;
    }
    if ((fn_8012BCB0(arg0) != 0) && (fn_8012BCB0(arg1) != 0)) {
        return 0;
    }
    return 1;
}
