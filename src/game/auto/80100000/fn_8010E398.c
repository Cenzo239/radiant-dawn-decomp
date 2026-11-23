#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 * fn_80060728();
extern u8 lbl_803CAB38[0x988];

s32 fn_8010E398(s8 *arg0, s8 *arg1) {
    u8 temp_r31;
    u8 temp_r30;

    temp_r31 = M2C_FIELD(arg1, u8 *, 8);
    temp_r30 = M2C_FIELD(arg0, u8 *, 8);
    if (temp_r30 == temp_r31) {
        return 0;
    }
    if ((u32) (*fn_80060728(lbl_803CAB38) & 3) == 2) {
        return 1;
    }
    if ((temp_r30 == 1) || (temp_r31 == 1)) {
        return 1;
    }
    return 2;
}

