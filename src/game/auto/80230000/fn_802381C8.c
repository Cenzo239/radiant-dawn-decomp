#include "game/auto/m2c_prelude.h"
M2C_UNK DCInvalidateRange();
M2C_UNK fn_8031D284();
M2C_UNK fn_8031D34C();
M2C_UNK memmove();
extern u8 lbl_80423120[0x20];
extern u8 lbl_80423140[0x2338];

void fn_802381C8(void) {
    s8 *sp8;
    M2C_UNK (*temp_r12)(s32, s32, s32, s32);

    sp8 = NULL;
loop_1:
    fn_8031D34C(lbl_80423120, &sp8, 1);
    DCInvalidateRange(M2C_FIELD(sp8, s32 *, 0), M2C_FIELD(sp8, s32 *, 8));
    memmove(M2C_FIELD(sp8, s32 *, 0), M2C_FIELD(sp8, s32 *, 4), M2C_FIELD(sp8, s32 *, 8));
    temp_r12 = M2C_FIELD(sp8, M2C_UNK (**)(s32, s32, s32, s32), 0x10);
    if (temp_r12 != NULL) {
        temp_r12(M2C_FIELD(sp8, s32 *, 0), M2C_FIELD(sp8, s32 *, 4), M2C_FIELD(sp8, s32 *, 8), M2C_FIELD(sp8, s32 *, 0x14));
    }
    fn_8031D284(lbl_80423140, sp8, 1);
    goto loop_1;
}
