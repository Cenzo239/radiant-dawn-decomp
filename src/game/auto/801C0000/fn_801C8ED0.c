#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8010904C(void *);
#else
M2C_UNK fn_8010904C();
#endif
extern u8 lbl_803C8E80[0x1648];

void fn_801C8ED0(void) {
    fn_8010904C(lbl_803C8E80 + 0x5B0);
    fn_8010904C(M2C_FIELD(lbl_803C8E80, s32 *, 0x890) + 0x110);
}
