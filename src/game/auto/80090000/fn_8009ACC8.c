#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s8 * fn_8024BCA0();
#if TARGET_PC
FE10_PROTO void fn_8026D01C(void **, unsigned char *);
FE10_PROTO unsigned char * fn_8026D02C(void *, unsigned char *);
#else
M2C_UNK fn_8026D01C();
s8 * fn_8026D02C();
#endif

s32 fn_8009ACC8(s32 arg0) {
    M2C_UNK sp8;
    s8 *temp_r3;
    s8 *temp_r3_2;

    temp_r3_2 = fn_8024BCA0();
    if (!(M2C_FIELD(temp_r3_2, s32 *, 0x40) & 1)) {
        return 0;
    }
    fn_8026D01C(&sp8, temp_r3_2 + 0x70);
    temp_r3 = fn_8026D02C(&sp8, arg0);
    if (temp_r3 != NULL) {
        return *temp_r3;
    }
    return 0;
}

