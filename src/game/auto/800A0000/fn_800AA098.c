#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO void fn_800AABEC(void *);
FE10_PROTO void fn_800AAC14(void *);
FE10_PROTO void fn_800AEBD4(void *);
FE10_PROTO void fn_800AEC54(void *);
FE10_PROTO void fn_800AEC70(void *);
FE10_PROTO int fn_800BD280(void *);
FE10_PROTO s8 * fn_8017C2B0(short);
#else
M2C_UNK fn_80083B78();
M2C_UNK fn_800AABEC();
M2C_UNK fn_800AAC14();
M2C_UNK fn_800AEBD4();
M2C_UNK fn_800AEC54();
M2C_UNK fn_800AEC70();
s32 fn_800BD280();
s8 * fn_8017C2B0();
#endif

void fn_800AA098(s8 *arg0) {
    s32 var_r31;
    s32 temp_r0;
    s32 var_r31_2;
    s8 *temp_r3;
    s32 *var_r30;
    s32 *var_r30_2;
    s8 *var_r29;

    var_r29 = M2C_FIELD(arg0, s8 **, 0x18);
    temp_r3 = fn_8017C2B0(M2C_FIELD(arg0, u16 *, 0x34));
    if (temp_r3 != NULL) {
        if ((s32) M2C_FIELD(M2C_FIELD(temp_r3, s8 **, 0x30), u8 *, 0x2A) == 0) {
            temp_r0 = M2C_FIELD(arg0, s32 *, 0x30);
            switch (temp_r0) {                      /* irregular */
            case 0:
                fn_800AAC14(M2C_FIELD(var_r29, s32 *, 0x30));
                fn_800AEC70(M2C_FIELD(var_r29, s32 *, 0x34));
                fn_800AEC54(M2C_FIELD(var_r29, s32 *, 0x38));
                var_r31 = 0;
                do {
                    if (var_r31 < 0) {
                        var_r30 = NULL;
                    } else {
                        var_r30 = M2C_FIELD(var_r29, s8 **, 0x3C);
                    }
                    if (fn_800BD280(var_r30) != 0) {
                        M2C_FIELD(var_r30, s32 *, 0x50) = (s32) (M2C_FIELD(var_r30, s32 *, 0x50) | 0x8000);
                    }
                    var_r31 += 1;
                    var_r29 += 4;
                } while (var_r31 < 2);
                break;
            case 1:
                fn_800AABEC(M2C_FIELD(var_r29, s32 *, 0x30));
                fn_800AEC54(M2C_FIELD(var_r29, s32 *, 0x34));
                fn_800AEC70(M2C_FIELD(var_r29, s32 *, 0x38));
                fn_800AEBD4(M2C_FIELD(var_r29, s32 *, 0x38));
                var_r31_2 = 0;
                do {
                    if (var_r31_2 < 0) {
                        var_r30_2 = NULL;
                    } else {
                        var_r30_2 = M2C_FIELD(var_r29, s8 **, 0x3C);
                    }
                    if (fn_800BD280(var_r30_2) != 0) {
                        M2C_FIELD(var_r30_2, s32 *, 0x50) = (s32) (M2C_FIELD(var_r30_2, s32 *, 0x50) & 0xFFFF7FFF);
                    }
                    var_r31_2 += 1;
                    var_r29 += 4;
                } while (var_r31_2 < 2);
                break;
            }
            goto block_21;
        }
    } else {
block_21:
        fn_80083B78(arg0);
    }
}
