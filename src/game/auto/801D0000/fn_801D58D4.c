#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80079210(void *);
#else
void fn_80079210(s32);
#endif

s32 fn_801D58D4(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg1 > 0)) {
        fn_80079210(arg0);
    }
    return arg0;
}
