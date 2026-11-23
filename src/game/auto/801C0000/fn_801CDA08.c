#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_800E3810(char *, void *, ...);
FE10_PROTO void fn_800E4904(char *, int, void *);
FE10_PROTO void fn_800E4AF0(unsigned char *, int, ...);
#else
s8 * fn_800E3810();
M2C_UNK fn_800E4904();
M2C_UNK fn_800E4AF0();
#endif
extern u8 fn_801CD994[0x74];
extern u8 lbl_8036EA00[0x40];

void fn_801CDA08(s32 arg0) {
    s8 *temp_r3;
    s8 *temp_r5;
    s8 *temp_r6;

    temp_r3 = fn_800E3810(lbl_8036EA00 + 7, arg0, lbl_8036EA00);
    if (temp_r3 != NULL) {
        fn_800E4904(temp_r3, 0, arg0);
        M2C_FIELD(M2C_FIELD(temp_r3, s8 **, 0x30), M2C_UNK **, 0x9C) = fn_801CD994;
        temp_r6 = M2C_FIELD(temp_r3, s8 **, 0x30);
        M2C_FIELD(temp_r6, s32 *, 0x18) = (s32) (M2C_FIELD(temp_r6, s32 *, 0x18) | 4);
        temp_r5 = M2C_FIELD(temp_r3, s8 **, 0x30);
        M2C_FIELD(temp_r5, s16 *, 4) = 3;
        fn_800E4AF0(temp_r3, -1, temp_r5, temp_r6);
    }
}

