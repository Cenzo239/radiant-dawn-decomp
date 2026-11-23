#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800A19E4(unsigned char *);
FE10_PROTO void * fn_800C3BC8(void *, ...);
#else
s32 fn_800A19E4();
s8 * fn_800C3BC8();
#endif
extern u8 lbl_803E50B0[0x10];

s32 fn_800A1CB8(s8 *arg0) {
    s8 *var_r31;

    M2C_FIELD(lbl_803E50B0, s8 *, 0xA) = 0;
    M2C_FIELD(lbl_803E50B0, s16 *, 6) = (s16) M2C_FIELD(arg0, s16 *, 0x1C);
    var_r31 = fn_800C3BC8(NULL, lbl_803E50B0);
    goto loop_5;
block_1:
    if ((s32) M2C_FIELD(var_r31, u8 *, 0xC) != 0x14) {
        goto block_4;
    }
    if (fn_800A19E4(var_r31) == 0) {
        goto block_4;
    }
    return 1;
block_4:
    var_r31 = fn_800C3BC8(var_r31);
loop_5:
    if (var_r31 != NULL) {
        goto block_1;
    }
    return 0;
}
