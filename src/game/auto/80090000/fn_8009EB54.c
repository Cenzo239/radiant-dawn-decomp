#include "game/auto/m2c_prelude.h"
extern u8 lbl_803CAB38[0x988];

s32 fn_8009EB54(s8 *arg0) {
    s16 temp_r0;
    s16 temp_r5;

    temp_r5 = M2C_FIELD(arg0, s16 *, 0x18);
    if ((temp_r5 >= 0) && (temp_r5 != (s32) M2C_FIELD(lbl_803CAB38, u8 *, 0x11))) {
        return 0;
    }
    temp_r0 = M2C_FIELD(arg0, s16 *, 0x14);
    if (temp_r0 == 0) {
        return 1;
    }
    if (temp_r0 > (s16) M2C_FIELD(lbl_803CAB38, s16 *, 0x12)) {
        return 0;
    }
    return M2C_FIELD(lbl_803CAB38, s16 *, 0x12) <= M2C_FIELD(arg0, s16 *, 0x16);
}
