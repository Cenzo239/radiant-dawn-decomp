#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_801288D4(void *);
#else
M2C_UNK fn_801288D4();
#endif
extern u8 lbl_803CA870[0x130];

void fn_80204334(void) {
    fn_801288D4(M2C_FIELD(lbl_803CA870, s32 *, 4));
}
