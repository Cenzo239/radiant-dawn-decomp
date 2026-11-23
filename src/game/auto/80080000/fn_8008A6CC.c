#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_802910CC(char *, char *, unsigned int);
#else
M2C_UNK fn_802910CC();
#endif

void fn_8008A6CC(s8 *arg0, s32 arg1, s32 arg2) {
    fn_802910CC(M2C_FIELD(arg0, s32 *, 4), arg2, arg1);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + arg1);
}
