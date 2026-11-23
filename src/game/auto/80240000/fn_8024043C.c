#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800A08F0(int);
#else
M2C_UNK fn_800A08F0();
#endif

void fn_8024043C(s8 *arg0) {
    fn_800A08F0(M2C_FIELD(arg0, s32 *, 8));
}
