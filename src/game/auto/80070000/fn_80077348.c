#include "game/auto/m2c_prelude.h"
void
#if TARGET_PC
*
#endif
fn_80077348(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
#if TARGET_PC
    return arg0;
#endif
}
