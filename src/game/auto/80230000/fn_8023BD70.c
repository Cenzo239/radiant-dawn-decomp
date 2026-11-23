#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8031D284();
M2C_UNK fn_8031D34C();
extern u8 lbl_804254B8[0x20];
extern u8 lbl_804254D8[0x2338];

void fn_8023BD70(s32 arg0, s8 *arg1) {
    s8 *sp8;
    s8 *temp_r31;

    temp_r31 = M2C_FIELD(arg1, s8 **, 0x2C);
    if (arg0 < 0) {
        M2C_FIELD(temp_r31, s32 *, 0x50) = (s32) (M2C_FIELD(temp_r31, s32 *, 0x50) | 0x20000);
        return;
    }
    M2C_FIELD(temp_r31, s32 *, 0x68) = (s32) M2C_FIELD(temp_r31, s32 *, 0x64);
    fn_8031D34C(lbl_804254D8, &sp8, 1);
    M2C_FIELD(sp8, s8 *, 0) = 0;
    M2C_FIELD(sp8, s8 **, 4) = temp_r31;
    M2C_FIELD(sp8, s32 *, 8) = arg0;
    fn_8031D284(lbl_804254B8, sp8, 1);
}
