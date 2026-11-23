#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80025FE0(char *);
#else
M2C_UNK fn_80025FE0();
#endif
M2C_UNK fn_8002E3D4(void *);

void fn_8002697C(s8 *arg0) {
    fn_8002E3D4(arg0);
    fn_8002E3D4(arg0 + 0x4A0);
    fn_8002E3D4(arg0 + 0x940);
    fn_80025FE0(arg0 + 0xDE0);
    M2C_FIELD(arg0, s32 *, 0x15E8) = 0;
    M2C_FIELD(arg0, s32 *, 0x15EC) = 0;
    M2C_FIELD(arg0, s32 *, 0x15F0) = 0;
    M2C_FIELD(arg0, s32 *, 0x15F4) = 0;
    M2C_FIELD(arg0, s32 *, 0x15F8) = 0;
    M2C_FIELD(arg0, s8 *, 0x15FC) = -1;
    M2C_FIELD(arg0, s8 *, 0x1604) = 0;
}
