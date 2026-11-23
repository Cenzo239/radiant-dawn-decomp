#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
#else
s8 * fn_80060728();
#endif
M2C_UNK strcpy();
extern u8 lbl_803CAB38[0x988];
extern s8 *lbl_804CB608;

s32 fn_8008DA3C(s32 arg0, s32 arg1) {
    s32 var_r31;

    var_r31 = arg1;
    if (arg1 < 0) {
        M2C_FIELD(lbl_804CB608, s32 *, 0x120) = (s32) (M2C_FIELD(lbl_804CB608, s32 *, 0x120) + 1);
        return 0;
    }
    if ((u8) M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11) == 2) {
        var_r31 = var_r31 / 2;
    }
    if ((u8) M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11) == 3) {
        var_r31 += var_r31 / 2;
    }
    if (var_r31 == 0) {
        M2C_FIELD(lbl_804CB608, s32 *, 0x120) = (s32) (M2C_FIELD(lbl_804CB608, s32 *, 0x120) + 1);
        return 0;
    }
    strcpy(lbl_804CB608 + (M2C_FIELD(lbl_804CB608, s32 *, 0x124) << 5), arg0);
    M2C_FIELD((lbl_804CB608 + (M2C_FIELD(lbl_804CB608, s32 *, 0x124) * 4)), s32 *, 0x100) = var_r31;
    M2C_FIELD(lbl_804CB608, s32 *, 0x124) = (s32) (M2C_FIELD(lbl_804CB608, s32 *, 0x124) + 1);
    M2C_FIELD(lbl_804CB608, s32 *, 0x120) = (s32) (M2C_FIELD(lbl_804CB608, s32 *, 0x120) + 1);
    return 1;
}

