#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char fn_8008A1A0(char *);
FE10_PROTO int fn_8008A1B4(void *);
#else
s8 fn_8008A1A0();
s16 fn_8008A1B4();
#endif

void fn_80106D3C(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0) = fn_8008A1B4(arg1);
    M2C_FIELD(arg0, s16 *, 2) = fn_8008A1B4(arg1);
    M2C_FIELD(arg0, s16 *, 4) = fn_8008A1B4(arg1);
    M2C_FIELD(arg0, s16 *, 6) = fn_8008A1B4(arg1);
    M2C_FIELD(arg0, s16 *, 8) = fn_8008A1B4(arg1);
    M2C_FIELD(arg0, s16 *, 0xA) = fn_8008A1B4(arg1);
    M2C_FIELD(arg0, s8 *, 0xC) = fn_8008A1A0(arg1);
    M2C_FIELD(arg0, s8 *, 0xD) = fn_8008A1A0(arg1);
}
