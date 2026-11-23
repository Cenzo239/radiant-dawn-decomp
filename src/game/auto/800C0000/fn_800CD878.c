#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80067EA8(int);
#else
M2C_UNK fn_80067EA8();
#endif
extern u8 lbl_803CAB38[0x988];

void fn_800CD878(void) {
    fn_80067EA8(M2C_FIELD(lbl_803CAB38, u8 *, 0x10));
}
