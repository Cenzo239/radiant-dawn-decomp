#include "game/auto/m2c_prelude.h"
s32
#if TARGET_PC
*
#endif
fn_80245878(
#if TARGET_PC
s8 *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
    return arg0 + (arg1 * 0x18) + 0x18F8;
}
