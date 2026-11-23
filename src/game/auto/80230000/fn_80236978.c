#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_802359A8(void *);
FE10_PROTO void fn_80237C9C(int);
FE10_PROTO void fn_80238170(int);
#else
M2C_UNK fn_802359A8();
M2C_UNK fn_80237C9C();
M2C_UNK fn_80238170();
#endif
M2C_UNK fn_8031D224();
extern u8 lbl_80420420[0x200];
extern u8 lbl_80420660[0x20];
extern u8 lbl_804CBF54[0x4];

void fn_80236978(void) {
    s8 *var_r31_3;
    s8 *var_r31_2;
    s8 *var_r31;
    s32 var_r30_3;
    s32 var_r30_2;
    s32 var_r30;

    if ((s32) M2C_FIELD(lbl_80420420, s32 *, 0xB0) == 0) {
        var_r31 = lbl_80420420 + 0x104;
        var_r30 = 0;
        do {
            fn_80237C9C(var_r31);
            var_r30 += 1;
            var_r31 += 0xC;
        } while (var_r30 < 0xA);
    }
    var_r30_2 = 0;
    var_r31_2 = lbl_80420420 + 0x17C;
    do {
        fn_80238170(var_r31_2);
        var_r30_2 += 1;
        var_r31_2 += 0x10;
    } while (var_r30_2 < 3);
    if ((s32) M2C_FIELD(lbl_80420420, u8 *, 0xA7) != 0) {
        var_r31_3 = lbl_80420420 + 0x1AC;
        var_r30_3 = 0;
        do {
            fn_802359A8(var_r31_3);
            var_r30_3 += 1;
            var_r31_3 += 0xC;
        } while (var_r30_3 < 6);
    }
    fn_8031D224(lbl_80420660, lbl_804CBF54, 1);
}
