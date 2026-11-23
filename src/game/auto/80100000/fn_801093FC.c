#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8008A43C(char *, int, void *);
#else
M2C_UNK fn_8008A43C();
#endif

void fn_801093FC(s32 arg0, s32 arg1) {
    fn_8008A43C(arg1, 4, arg0);
}
