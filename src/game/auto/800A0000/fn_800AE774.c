#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_8002BCC4(void *);
FE10_PROTO char * fn_8002C590(char *);
FE10_PROTO char * fn_8002C738(char *);
FE10_PROTO void fn_80081A90(void *);
FE10_PROTO int fn_8010301C(void *, void *, int, int, void *);
FE10_PROTO int fn_8011F428(void *);
#else
M2C_UNK fn_8002BCC4();
s8 * fn_8002C590();
s8 * fn_8002C738();
M2C_UNK fn_80081A90();
M2C_UNK fn_8010301C();
s32 fn_8011F428();
#endif
M2C_UNK fn_80134E30();
#if TARGET_PC
FE10_PROTO void fn_801868E8(void *, void *);
#else
M2C_UNK fn_801868E8();
#endif
extern u8 lbl_803C8E80[0x1648];

void fn_800AE774(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    u32 *temp_r3;
    s32 temp_r31;
    s32 temp_r30_2;
    u32 temp_r30_3;
    s32 *temp_r3_2;
    u16 *temp_r30;

    fn_8002BCC4(lbl_803C8E80);
    temp_r3 = fn_8002C590(lbl_803C8E80);
    if (temp_r3 != NULL) {
        temp_r30 = M2C_FIELD(temp_r3, u16 **, 0x3F0);
        if ((temp_r30 != NULL) && (fn_8011F428(temp_r30) == 0)) {
            *temp_r30 |= 0x10;
        }
    }
    temp_r31 = M2C_FIELD(lbl_803C8E80, s32 *, 0x3F0);
    temp_r30_2 = M2C_FIELD(lbl_803C8E80, s32 *, 0x890);
    if ((temp_r31 != 0) && (temp_r30_2 != 0)) {
        fn_8010301C(temp_r31, temp_r30_2, 0, 0, 0);
        fn_8010301C(temp_r30_2, temp_r31, 0, 0, 0);
    }
    temp_r3_2 = fn_8002C738(lbl_803C8E80);
    if (temp_r3_2 != NULL) {
        temp_r30_3 = M2C_FIELD(temp_r3_2, s32 *, 0x3F0);
        if (temp_r30_3 != 0) {
            fn_80134E30();
            fn_801868E8(temp_r30_3, arg0);
        }
    }
    if (M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) & 0x200000) {
        fn_80081A90(arg0);
    }
}
