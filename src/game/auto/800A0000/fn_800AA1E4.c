#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80081194(void *, void *);
#else
s8 * fn_80081194();
#endif
f32 fn_800A84A4();
#if TARGET_PC
FE10_PROTO int fn_800AE8F4(void *, char *);
#else
M2C_UNK fn_800AE8F4();
#endif
s16 fn_80175E5C();
#if TARGET_PC
FE10_PROTO void fn_8017C1AC(char *, short);
FE10_PROTO int * fn_8017C218(int, void *);
#else
M2C_UNK fn_8017C1AC();
s8 * fn_8017C218();
#endif
extern u8 lbl_803653B8[0x88];
extern u8 lbl_803821E0[0x18];

void fn_800AA1E4(s8 *arg0, s32 arg1) {
    s16 temp_r31;
    s32 var_r30;
    s8 *temp_r3;
    s8 *temp_r3_2;

    temp_r31 = fn_80175E5C();
    if (arg1 != 0) {
        if ((s32) M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x38), u8 *, 0x30) == 0) {
            fn_800AE8F4(M2C_FIELD(arg0, s8 **, 0x38), arg1);
            var_r30 = 0;
            goto block_5;
        }
    } else if ((s32) M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x38), u8 *, 0x30) != 0) {
        var_r30 = 1;
block_5:
        temp_r3 = fn_80081194(lbl_803821E0, arg0);
        M2C_FIELD(temp_r3, s16 *, 0x34) = temp_r31;
        M2C_FIELD(temp_r3, s32 *, 0x30) = var_r30;
        temp_r3_2 = fn_8017C218(2, arg0);
        if (temp_r3_2 != NULL) {
            fn_8017C1AC(temp_r3_2, (s32) fn_800A84A4(lbl_803653B8 + 0x7C));
            M2C_FIELD(temp_r3_2, s16 *, 0x3C) = temp_r31;
        }
    }
}

