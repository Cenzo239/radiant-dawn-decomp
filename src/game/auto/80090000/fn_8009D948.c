#include "game/auto/m2c_prelude.h"
s32
#if TARGET_PC
*
#endif
fn_8009D948(s8 *arg0, s32 arg1) {
#if TARGET_PC
    return (s8 *)M2C_FIELD(M2C_FIELD(arg0, s8 **, 8), s32 *, 0x24) + arg1;
#else
    return M2C_FIELD(M2C_FIELD(arg0, s8 **, 8), s32 *, 0x24) + arg1;
#endif
}
