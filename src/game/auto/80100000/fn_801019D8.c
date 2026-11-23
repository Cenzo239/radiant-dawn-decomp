#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_800E3A10(char *, void *);
#else
s8 * fn_800E3A10();
#endif
#if TARGET_PC
FE10_PROTO void fn_800E48AC(void *, float, float, float);
#else
M2C_UNK fn_800E48AC();
#endif
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void *, void *);
FE10_PROTO void fn_8017DB90(int, int, char, int, void *);
#else
s32 fn_8011B77C();
M2C_UNK fn_8017DB90();
#endif
extern u8 fn_801018F8[0xe0];
extern u8 lbl_80367D50[0x140];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA524;
#else
extern s32 lbl_804CA524;
#endif

void fn_801019D8(s8 *arg0) {
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    u8 var_r3;
    s8 *temp_r31;
    s8 *temp_r3;
    s8 *var_r3_2;

    temp_r31 = M2C_FIELD(arg0, s8 **, 0x30);
    temp_f31 = M2C_FIELD(temp_r31, f32 *, 4);
    temp_f30 = M2C_FIELD(temp_r31, f32 *, 8);
    temp_f29 = M2C_FIELD(temp_r31, f32 *, 0xC);
    if (fn_8011B77C(temp_r31 + 0x12C, lbl_804CA524) != 0) {
        var_r3 = M2C_FIELD(temp_r31, u8 *, 0x118);
        if ((s8) var_r3 == -1) {
            var_r3 = M2C_FIELD(M2C_FIELD(temp_r31, s8 **, 0xEC), u8 *, 0xE1);
        }
        switch ((s8) var_r3) {                      /* irregular */
        case 1:
            var_r3_2 = lbl_80367D50 + 0x53;
            break;
        case 2:
            var_r3_2 = lbl_80367D50 + 0x67;
            break;
        case 3:
            var_r3_2 = lbl_80367D50 + 0x7B;
            break;
        default:
            var_r3_2 = lbl_80367D50 + 0x8F;
            break;
        }
    } else {
        var_r3_2 = lbl_80367D50 + 0xA1;
    }
    temp_r3 = fn_800E3A10(var_r3_2, arg0);
    if (temp_r3 != NULL) {
#if TARGET_PC
        fn_800E48AC(temp_r3, temp_f31, temp_f30, temp_f29);
#else
        fn_800E48AC(temp_f31, temp_f30, temp_f29);
#endif
        M2C_FIELD(M2C_FIELD(temp_r3, s8 **, 0x30), M2C_UNK **, 0x9C) = fn_801018F8;
        if (M2C_FIELD(arg0, u16 *, 0x34) & 0x10) {
            fn_8017DB90((s32) temp_f31, (s32) temp_f30, 0, 0, temp_r3);
        }
    }
}

