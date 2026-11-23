#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char fn_8008A1A0(char *);
#else
u8 fn_8008A1A0();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB810;
#else
extern s32 lbl_804CB810;
#endif

void fn_8010E914(s8 *arg0, s32 arg1) {
    s32 var_r0;
    u8 temp_r3;

    temp_r3 = fn_8008A1A0(arg1);
    if (temp_r3 != 0) {
        var_r0 = lbl_804CB810 + ((temp_r3 - 1) * 0x3F0);
    } else {
        var_r0 = 0;
    }
    M2C_FIELD(arg0, s32 *, 0) = var_r0;
    M2C_FIELD(arg0, u8 *, 4) = fn_8008A1A0(arg1);
    M2C_FIELD(arg0, u8 *, 5) = fn_8008A1A0(arg1);
    M2C_FIELD(arg0, u8 *, 6) = fn_8008A1A0(arg1);
    M2C_FIELD(arg0, u8 *, 7) = fn_8008A1A0(arg1);
}
