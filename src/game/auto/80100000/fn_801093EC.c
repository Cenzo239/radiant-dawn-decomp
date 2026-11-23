#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8008A780(char *, int, void *);
#else
M2C_UNK fn_8008A780();
#endif

void fn_801093EC(s32 arg0, s32 arg1) {
    fn_8008A780(arg1, 4, arg0);
}
