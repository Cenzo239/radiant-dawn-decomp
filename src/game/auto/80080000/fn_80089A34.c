#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80081A90(void *);
#else
M2C_UNK fn_80081A90(s32);
#endif

s32 fn_80089A34(s32 arg0) {
    fn_80081A90(arg0);
    return 1;
}
