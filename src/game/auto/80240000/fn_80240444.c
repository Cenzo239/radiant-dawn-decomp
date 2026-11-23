#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800A07B8(int);
#else
M2C_UNK fn_800A07B8();
#endif

void fn_80240444(s8 *arg0) {
    fn_800A07B8(M2C_FIELD(arg0, s32 *, 8));
}
