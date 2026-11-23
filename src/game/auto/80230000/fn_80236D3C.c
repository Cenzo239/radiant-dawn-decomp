#include "game/auto/m2c_prelude.h"
M2C_UNK fn_802357A8();
M2C_UNK fn_80237B3C();
M2C_UNK fn_80237DE8();
M2C_UNK fn_802FAED4();
s32 fn_8031D34C();
M2C_UNK fn_8032F774();
extern u8 lbl_80420420[0x200];
extern u8 lbl_80420680[0x40];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CBF58;
#else
extern s32 lbl_804CBF58;
#endif

void fn_80236D3C(void) {
    s32 sp8;
    s32 var_r0;

    if (((s32) M2C_FIELD(lbl_80420420, s32 *, 0xA0) != 0) && ((s32) M2C_FIELD(lbl_80420420, u8 *, 0xA4) != 0)) {
        M2C_FIELD(lbl_80420420, s8 *, 0xA5) = 0;
        M2C_FIELD(lbl_80420420, u8 *, 0xA4) = 0U;
        fn_8032F774(lbl_804CBF58);
        if ((s32) M2C_FIELD(lbl_80420420, s32 *, 0xB0) == 0) {
            fn_802FAED4(lbl_80420420);
            fn_80237B3C();
        }
        fn_80237DE8();
        if ((s32) M2C_FIELD(lbl_80420420, u8 *, 0xA7) != 0) {
            fn_802357A8();
        }
        do {
            if (fn_8031D34C(lbl_80420680, &sp8, 0) == 1) {
                var_r0 = sp8;
            } else {
                var_r0 = 0;
            }
        } while (var_r0 != 0);
        M2C_FIELD(lbl_80420420, s32 *, 0xE8) = 0;
        M2C_FIELD(lbl_80420420, f32 *, 0xDC) = (f32) M2C_FIELD(lbl_80420420, f32 *, 0xE0);
        M2C_FIELD(lbl_80420420, s32 *, 0xA8) = 0;
        M2C_FIELD(lbl_80420420, s32 *, 0xAC) = 0;
    }
}
