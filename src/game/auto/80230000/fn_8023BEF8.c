#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8031D284();
M2C_UNK fn_8031D34C();
extern u8 lbl_804254B8[0x20];
extern u8 lbl_804254D8[0x2338];

void fn_8023BEF8(
#if TARGET_PC
s8 *arg0, void *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    s8 *sp8;

    M2C_FIELD(arg0, s32 *, 0x68) = (s32) M2C_FIELD(arg0, s32 *, 0x64);
    fn_8031D34C(lbl_804254D8, &sp8, 1);
    M2C_FIELD(sp8, s8 *, 0) = 3;
    M2C_FIELD(sp8, s8 **, 4) = arg0;
    M2C_FIELD(sp8, s32 *, 8) = arg1;
    fn_8031D284(lbl_804254B8, sp8, 1);
}
