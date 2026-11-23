#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void *, void *);
#else
s32 fn_8011B77C();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4D8;
#else
extern s32 lbl_804CA4D8;
#endif

void fn_80106DD0(u8 *arg0, s8 *arg1) {
    if (fn_8011B77C(arg1 + 0x12C, lbl_804CA4D8) != 0) {
        *arg0 = 1;
        return;
    }
    *arg0 = M2C_FIELD(M2C_FIELD(arg1, s8 **, 0xF4), u8 *, 8);
}
