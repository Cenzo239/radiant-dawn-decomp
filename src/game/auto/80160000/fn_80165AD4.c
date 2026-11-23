#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80114888(void *, int);
FE10_PROTO void fn_8011540C(void *, void *);
FE10_PROTO void fn_8011567C(void *, unsigned char *);
#else
M2C_UNK fn_80114888();
M2C_UNK fn_8011540C();
M2C_UNK fn_8011567C();
#endif
void fn_80115764(u8*, s32, s32, s32);
extern u8 lbl_803EC898[0x15867];

void fn_80165AD4(
#if TARGET_PC
s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4, s32 arg5
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5
#endif
) {
    fn_80114888(lbl_803EC898, arg4);
    fn_8011540C(lbl_803EC898, arg2);
    fn_8011567C(lbl_803EC898, arg3);
    fn_80115764(lbl_803EC898, (s8) arg0, (s8) arg1, (u16) arg5);
}

