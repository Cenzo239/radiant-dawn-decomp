#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80081194(void *, void *);
FE10_PROTO int fn_800A1274(unsigned char *);
FE10_PROTO void * fn_800C3BC8(void *);
#else
s8 * fn_80081194();
s32 fn_800A1274();
s8 * fn_800C3BC8();
#endif
extern u8 lbl_80381BD4[0x1c];
extern u8 lbl_803E50B0[0x10];

s32 fn_800A14C0(s32 arg0) {
    s32 var_r0;
    s8 *temp_r3;
    s8 *var_r31;

    var_r31 = fn_800C3BC8(NULL);
    goto loop_5;
block_1:
    if ((s32) M2C_FIELD(var_r31, u8 *, 0xC) != 0x12) {
        goto block_4;
    }
    if (fn_800A1274(var_r31) == 0) {
        goto block_4;
    }
    var_r0 = 1;
    goto block_7;
block_4:
    var_r31 = fn_800C3BC8(var_r31);
loop_5:
    if (var_r31 != NULL) {
        goto block_1;
    }
    var_r0 = 0;
block_7:
    if (var_r0 != 0) {
        goto block_9;
    }
    return 0;
block_9:
    M2C_FIELD(lbl_803E50B0, s8 *, 0xA) = 0;
    temp_r3 = fn_80081194(lbl_80381BD4, arg0);
    M2C_FIELD(temp_r3, s32 *, 0x34) = 0x12;
    M2C_FIELD(temp_r3, s32 (**)(s8 *), 0x38) = fn_800A1274;
    return 1;
}
