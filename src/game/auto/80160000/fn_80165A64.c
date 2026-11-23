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
void fn_80115764(void *, s8, s8, u16);
extern u8 lbl_803EC898[0x15867];

void fn_80165A64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fn_80114888(lbl_803EC898, arg3);
    fn_8011540C(lbl_803EC898, arg2);
    fn_8011567C(lbl_803EC898, 0);
    fn_80115764(lbl_803EC898, arg0, arg1, arg4);
}

