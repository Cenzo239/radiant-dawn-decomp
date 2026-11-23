#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800620A8(void *, float, float);
#else
M2C_UNK fn_800620A8();
#endif
s8 * fn_8012D2B0(s32);
extern u8 lbl_803CAB38[0x988];

void fn_800432A4(void) {
    s8 *temp_r3;

    temp_r3 = fn_8012D2B0(M2C_FIELD(lbl_803CAB38, u8 *, 0x11));
    if ((temp_r3 != NULL) && !(M2C_FIELD(temp_r3, s32 *, 0x10C) & 0x010000DC)) {
        fn_800620A8(lbl_803CAB38, (f32) (s8) M2C_FIELD(temp_r3, u8 *, 0x102), (f32) (s8) M2C_FIELD(temp_r3, u8 *, 0x103));
    }
}
