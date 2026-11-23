#include "game/auto/m2c_prelude.h"
extern u8 lbl_803C8E80[0x1648];

s32 fn_801D04AC(void) {
    return M2C_FIELD(lbl_803C8E80, s32 *, 0x15E8) <= 1;
}
