#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80078E24(void *);
#else
M2C_UNK fn_80078E24();
#endif

void fn_8017D7E0(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    fn_80078E24(M2C_FIELD(arg0, s32 *, 0x60));
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
}
