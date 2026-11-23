#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80081050(void *, void *);
FE10_PROTO void fn_80083DC4(void *, int);
FE10_PROTO void * fn_800893E4(void *, void *(*)(void *, void *), void *);
#else
s8 * fn_80081050();
M2C_UNK fn_80083DC4();
M2C_UNK fn_800893E4();
#endif
extern u8 fn_800EFE88[0x30];
extern u8 lbl_80384F18[0x28];

void fn_800EFEB8(
#if TARGET_PC
s8 *arg0, s32 arg1, void *arg2
#else
s8 *arg0, s32 arg1, s32 arg2
#endif
) {
    s32 temp_r3_2;
    s32 temp_r4;
    s8 *temp_r3;

    if (arg0 != NULL) {
        fn_800893E4(lbl_80384F18, fn_800EFE88, arg0);
        temp_r3 = fn_80081050(lbl_80384F18, arg2);
        M2C_FIELD(temp_r3, s8 **, 0x30) = arg0;
        M2C_FIELD(temp_r3, f32 *, 0x40) = (f32) M2C_FIELD(arg0, s16 *, 6);
        M2C_FIELD(temp_r3, f32 *, 0x44) = (f32) (arg1 + M2C_FIELD(M2C_FIELD(temp_r3, s8 **, 0x30), s16 *, 6));
        M2C_FIELD(temp_r3, s32 *, 0x34) = 0;
        M2C_FIELD(temp_r3, s32 *, 0x38) = arg1;
        if (arg1 > 0) {
            M2C_FIELD(temp_r3, s32 *, 0x38) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x38) * 4);
        }
        temp_r4 = M2C_FIELD(temp_r3, s32 *, 0x38);
        if (temp_r4 > 0x32) {
            M2C_FIELD(temp_r3, s32 *, 0x38) = temp_r4 / 2;
        }
        if ((s32) M2C_FIELD(temp_r3, s32 *, 0x38) == 0) {
            fn_80083DC4(temp_r3, 0x63);
        }
        temp_r3_2 = M2C_FIELD(temp_r3, s32 *, 0x38);
        if (temp_r3_2 < 0) {
            M2C_FIELD(temp_r3, s32 *, 0x38) = (s32) (temp_r3_2 - (temp_r3_2 * 2));
        }
    }
}

