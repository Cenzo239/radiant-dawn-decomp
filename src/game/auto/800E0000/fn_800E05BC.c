#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800F39DC(void *);
FE10_PROTO void fn_80114D00(void *);
FE10_PROTO void fn_8011E294(void *, void *);
#else
M2C_UNK fn_800F39DC();
M2C_UNK fn_80114D00();
M2C_UNK fn_8011E294();
#endif
extern u8 lbl_803EC898[0x15867];

void fn_800E05BC(s8 *arg0) {
    s32 temp_r31;

    temp_r31 = M2C_FIELD(arg0, s32 *, 0x58);
    fn_8011E294(M2C_FIELD(arg0, s32 *, 0x54), temp_r31);
    fn_800F39DC(temp_r31);
    fn_80114D00(lbl_803EC898);
}
