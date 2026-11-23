#include "game/auto/m2c_prelude.h"
extern s8 *lbl_804CB598;

s32 fn_80077BF0(void) {
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(lbl_804CB598, s8 **, 4);
    return M2C_FIELD(temp_r4, u16 *, 8) + M2C_FIELD(temp_r4, u16 *, 0xA);
}
