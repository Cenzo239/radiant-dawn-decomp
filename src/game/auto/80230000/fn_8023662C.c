#include "game/auto/m2c_prelude.h"
M2C_UNK fn_802F69C4(void *);
extern u8 lbl_80420420[0x200];

s32 fn_8023662C(void) {
    if (((s32) M2C_FIELD(lbl_80420420, s32 *, 0xA0) != 0) && ((s32) M2C_FIELD(lbl_80420420, u8 *, 0xA4) == 0)) {
        M2C_FIELD(lbl_80420420, s32 *, 0xA0) = 0;
        fn_802F69C4(lbl_80420420);
        return 1;
    }
    return 0;
}
