#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800106AC(int, void *, void *);
#else
M2C_UNK fn_800106AC();
#endif
M2C_UNK fn_80083B78(void *);
#if TARGET_PC
FE10_PROTO float fn_801146A8(void *, char, char, int);
#else
f32 fn_801146A8();
#endif
extern u8 fn_800DFD3C[0x2d0];
extern u8 lbl_803EC898[0x15867];

void fn_800E01A0(s8 *arg0) {
    u8 temp_r4;

    temp_r4 = M2C_FIELD(arg0, u8 *, 0x37);
    if (temp_r4 <= 4U) {
        fn_80083B78(arg0);
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x37) = (u8) (temp_r4 - 4);
    M2C_FIELD(arg0, f32 *, 0x40) = fn_801146A8(lbl_803EC898, (s8) M2C_FIELD(arg0, s16 *, 0x30), (s8) M2C_FIELD(arg0, s16 *, 0x32), 0);
    M2C_FIELD(arg0, f32 *, 0x44) = fn_801146A8(lbl_803EC898, (s8) M2C_FIELD(arg0, s16 *, 0x30), (s8) M2C_FIELD(arg0, s16 *, 0x32), 1);
    M2C_FIELD(arg0, f32 *, 0x48) = fn_801146A8(lbl_803EC898, (s8) M2C_FIELD(arg0, s16 *, 0x30), (s8) M2C_FIELD(arg0, s16 *, 0x32), 2);
    M2C_FIELD(arg0, f32 *, 0x4C) = fn_801146A8(lbl_803EC898, (s8) M2C_FIELD(arg0, s16 *, 0x30), (s8) M2C_FIELD(arg0, s16 *, 0x32), 3);
    fn_800106AC(3, fn_800DFD3C, arg0);
}
