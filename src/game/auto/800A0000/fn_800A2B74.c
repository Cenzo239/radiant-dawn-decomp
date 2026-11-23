#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8023F4EC(char *);
#else
M2C_UNK fn_8023F4EC(s32);
#endif

s32 fn_800A2B74(s32 arg0) {
    fn_8023F4EC(arg0);
    return 1;
}
