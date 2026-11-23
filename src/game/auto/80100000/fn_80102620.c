#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800F6604(void *, char *);
#else
M2C_UNK fn_800F6604();
#endif
extern u8 lbl_80367D50[0x140];

void fn_80102620(s8 *arg0) {
    fn_800F6604(M2C_FIELD(arg0, s32 *, 0x30), lbl_80367D50 + 0x11C);
}
