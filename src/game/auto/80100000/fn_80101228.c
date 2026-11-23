#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800F3F08(void *, int);
FE10_PROTO void fn_800F4B94(void *, int);
#else
M2C_UNK fn_800F3F08();
M2C_UNK fn_800F4B94();
#endif

void fn_80101228(s8 *arg0) {
    fn_800F4B94(M2C_FIELD(arg0, s32 *, 0x34), -1);
    fn_800F3F08(M2C_FIELD(arg0, s32 *, 0x34), 0);
}
