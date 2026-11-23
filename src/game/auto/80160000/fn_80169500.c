#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8004559C(void *, int);
#else
M2C_UNK fn_8004559C();
#endif
extern u8 lbl_803CA870[0x130];

void fn_80169500(void) {
    fn_8004559C(lbl_803CA870, 1);
}
