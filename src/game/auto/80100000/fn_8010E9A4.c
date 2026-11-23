#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_800D0864(char *);
#else
M2C_UNK fn_800D0864();
#endif

void
#if TARGET_PC
*
#endif
fn_8010E9A4(s8 *arg0) {
#if TARGET_PC
    return fn_800D0864(M2C_FIELD(arg0, s32 *, 8));
#else
    fn_800D0864(M2C_FIELD(arg0, s32 *, 8));
#endif
}
