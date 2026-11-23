#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80079210(void *);
FE10_PROTO void fn_80110D38(void *);
#else
M2C_UNK fn_80079210();
M2C_UNK fn_80110D38(s32);
#endif

s32
#if TARGET_PC
*
#endif
fn_80111C24(
#if TARGET_PC
void *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
    if (arg0 != 0) {
        fn_80110D38(arg0);
        if (arg1 > 0) {
            fn_80079210(arg0);
        }
    }
    return arg0;
}
