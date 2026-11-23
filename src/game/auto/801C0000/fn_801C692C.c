#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80027088(void *, void *, char);
FE10_PROTO void fn_800C429C(void *);
FE10_PROTO void * fn_800C6210(char *, unsigned int);
FE10_PROTO int fn_8011799C(char *, char, char);
FE10_PROTO char * fn_801246A4(void *);
FE10_PROTO void fn_801C6114(void *);
#else
M2C_UNK fn_80027088();
M2C_UNK fn_800C429C();
s32 fn_800C6210();
s32 fn_8011799C();
M2C_UNK fn_801246A4();
M2C_UNK fn_801C6114();
#endif
extern u8 lbl_803C8E80[0x1648];
extern u8 lbl_803EC898[0x15867];
extern s8 *lbl_804CB814;

void fn_801C692C(s8 *arg0) {
    s32 temp_r0;
    s32 temp_r0_14;
    s32 temp_r0_2;
    s32 temp_r0_5;
    u8 temp_r0_11;
    u8 temp_r0_7;
    s8 **temp_r4;
    s8 **temp_r4_2;
    s8 *temp_r0_10;
    s8 *temp_r0_12;
    s8 *temp_r0_13;
    s8 *temp_r0_15;
    s8 *temp_r0_16;
    s8 *temp_r0_3;
    s8 *temp_r0_4;
    s8 *temp_r0_6;
    s8 *temp_r0_8;
    s8 *temp_r0_9;
    s8 *temp_r31;
    s8 *temp_r3;
    s8 *temp_r3_2;
    s8 *temp_r3_3;
    s8 *temp_r3_4;
    s8 *temp_r3_5;
    s8 *temp_r3_6;
    s8 *temp_r5;

    temp_r31 = M2C_FIELD(arg0, s8 **, 0x30);
    temp_r0 = M2C_FIELD(temp_r31, s32 *, 4);
    switch (temp_r0) {                              /* switch 1; irregular */
        do {
        case 0:                                     /* switch 1 */
loop_7:
            temp_r0_2 = M2C_FIELD(temp_r31, s32 *, 0x10);
            if (temp_r0_2 == 1) {
                temp_r3 = M2C_FIELD(temp_r31, s8 **, 0x44);
                temp_r0_3 = M2C_FIELD(temp_r3, s8 **, 0xE8);
                if (temp_r0_3 != NULL) {
                    M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_3;
                } else {
                    M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) *M2C_FIELD(temp_r3, s8 ***, 0xF4);
                }
            } else if (temp_r0_2 == -1) {
                temp_r3_2 = M2C_FIELD(temp_r31, s8 **, 0x44);
                temp_r0_4 = M2C_FIELD(temp_r3_2, s8 **, 0xE4);
                if (temp_r0_4 != NULL) {
                    M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_4;
                } else {
                    M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(M2C_FIELD(temp_r3_2, s8 ***, 0xF4), s8 **, 4);
                }
            } else {
                M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(M2C_FIELD(temp_r31, s8 **, 0x44), s8 **, 0xF8);
            }
            temp_r5 = M2C_FIELD(temp_r31, s8 **, 0x44);
            if (M2C_FIELD(temp_r5, s32 *, 0x10C) & 0x100000D8) {
                goto loop_7;
            }
        } while (fn_8011799C(lbl_803EC898, (s8) M2C_FIELD(temp_r5, u8 *, 0x102), (s8) M2C_FIELD(temp_r5, u8 *, 0x103)) == 0);
        break;
    case 1:                                         /* switch 1 */
        temp_r0_5 = M2C_FIELD(temp_r31, s32 *, 0x10);
        if (temp_r0_5 == 1) {
            temp_r3_3 = M2C_FIELD(temp_r31, s8 **, 0x44);
            temp_r0_6 = M2C_FIELD(temp_r3_3, s8 **, 0xE8);
            if (temp_r0_6 != NULL) {
                M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_6;
            } else {
                temp_r4 = M2C_FIELD(temp_r3_3, s8 ***, 0xF4);
                temp_r0_7 = M2C_FIELD(temp_r4, u8 *, 8);
                switch ((s32) temp_r0_7) {          /* switch 2; irregular */
                case 0:                             /* switch 2 */
                    temp_r0_8 = M2C_FIELD(lbl_804CB814, s8 **, 0x3C);
                    if (temp_r0_8 != NULL) {
                        M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_8;
                    } else {
                        M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(temp_r4, s8 **, 0);
                    }
                    break;
                case 5:                             /* switch 2 */
                    temp_r0_9 = M2C_FIELD(lbl_804CB814, s8 **, 0);
                    if (temp_r0_9 != NULL) {
                        M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_9;
                    } else {
                        M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(temp_r4, s8 **, 0);
                    }
                    break;
                default:                            /* switch 2 */
                    M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(temp_r4, s8 **, 0);
                    break;
                }
            }
        } else if (temp_r0_5 == -1) {
            temp_r3_4 = M2C_FIELD(temp_r31, s8 **, 0x44);
            temp_r0_10 = M2C_FIELD(temp_r3_4, s8 **, 0xE4);
            if (temp_r0_10 != NULL) {
                M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_10;
            } else {
                temp_r4_2 = M2C_FIELD(temp_r3_4, s8 ***, 0xF4);
                temp_r0_11 = M2C_FIELD(temp_r4_2, u8 *, 8);
                switch ((s32) temp_r0_11) {         /* switch 3; irregular */
                case 0:                             /* switch 3 */
                    temp_r0_12 = M2C_FIELD(lbl_804CB814, s8 **, 0x40);
                    if (temp_r0_12 != NULL) {
                        M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_12;
                    } else {
                        M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(temp_r4_2, s8 **, 4);
                    }
                    break;
                case 5:                             /* switch 3 */
                    temp_r0_13 = M2C_FIELD(lbl_804CB814, s8 **, 4);
                    if (temp_r0_13 != NULL) {
                        M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_13;
                    } else {
                        M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(temp_r4_2, s8 **, 4);
                    }
                    break;
                default:                            /* switch 3 */
                    M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(temp_r4_2, s8 **, 4);
                    break;
                }
            }
        } else {
            M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(M2C_FIELD(temp_r31, s8 **, 0x44), s8 **, 0xF8);
        }
        break;
    case 2:                                         /* switch 1 */
        temp_r0_14 = M2C_FIELD(temp_r31, s32 *, 0x10);
        if (temp_r0_14 == 1) {
            temp_r3_5 = M2C_FIELD(temp_r31, s8 **, 0x44);
            temp_r0_15 = M2C_FIELD(temp_r3_5, s8 **, 0xE8);
            if (temp_r0_15 != NULL) {
                M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_15;
            } else {
                M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) *M2C_FIELD(temp_r3_5, s8 ***, 0xF4);
            }
        } else if (temp_r0_14 == -1) {
            temp_r3_6 = M2C_FIELD(temp_r31, s8 **, 0x44);
            temp_r0_16 = M2C_FIELD(temp_r3_6, s8 **, 0xE4);
            if (temp_r0_16 != NULL) {
                M2C_FIELD(temp_r31, s8 **, 0x44) = temp_r0_16;
            } else {
                M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(M2C_FIELD(temp_r3_6, s8 ***, 0xF4), s8 **, 4);
            }
        } else {
            M2C_FIELD(temp_r31, s8 **, 0x44) = (s8 *) M2C_FIELD(M2C_FIELD(temp_r31, s8 **, 0x44), s8 **, 0xF8);
        }
        break;
    }
    if ((s32) M2C_FIELD(temp_r31, s32 *, 0x48) != 0) {
        fn_800C429C(M2C_FIELD(temp_r31, s32 *, 0x48));
    }
    M2C_FIELD(temp_r31, s32 *, 0x48) = fn_800C6210(fn_801246A4(M2C_FIELD(temp_r31, s8 **, 0x44)), 0);
    fn_80027088(lbl_803C8E80, M2C_FIELD(temp_r31, s8 **, 0x44), -1);
    fn_801C6114(temp_r31);
    M2C_FIELD(temp_r31, s16 *, 8) = 7;
}

