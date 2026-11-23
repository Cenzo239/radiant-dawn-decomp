#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8017F44C(unsigned int *, unsigned int, unsigned int);
#else
M2C_UNK fn_8017F44C();
#endif

void fn_800450A4(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 0xF) = -1;
    M2C_FIELD(arg0, s8 *, 0x10) = -1;
    M2C_FIELD(arg0, s8 *, 0x15) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0xE) = -1;
    M2C_FIELD(arg0, s8 *, 0x11) = -1;
    M2C_FIELD(arg0, s8 *, 0x12) = -1;
    M2C_FIELD(arg0, s8 *, 0x13) = -1;
    M2C_FIELD(arg0, s8 *, 0x14) = -1;
    M2C_FIELD(arg0, s8 *, 0x16) = 0;
    fn_8017F44C(arg0 + 0x18, 0, 0x10);
    M2C_FIELD(arg0, s8 *, 0x28) = 0;
}
