#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_801288D4(void *);
#else
M2C_UNK fn_801288D4();
#endif
extern u8 lbl_803C8E80[0x1648];

void fn_800477E8(void) {
    fn_801288D4(M2C_FIELD(lbl_803C8E80, s32 *, 0x3F0));
}
