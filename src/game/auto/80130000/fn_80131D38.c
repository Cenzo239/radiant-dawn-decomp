#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80006EE0(void *);
#else
M2C_UNK fn_80006EE0();
#endif
extern u8 lbl_80413510[0x6d8];

void fn_80131D38(void) {
    s32 var_r31;
    s8 *var_r30;
    s8 *var_r29;

    var_r31 = 0;
    var_r30 = lbl_80413510 + 0x3B0;
    var_r29 = lbl_80413510 + 0x140;
    do {
        fn_80006EE0(var_r30);
        fn_80006EE0(var_r29);
        var_r31 += 1;
        var_r30 += 0x9C;
        var_r29 += 0x9C;
    } while (var_r31 < 4);
    fn_80006EE0(lbl_80413510 + 8);
    fn_80006EE0(lbl_80413510 + 0xA4);
    M2C_FIELD(lbl_80413510, s8 *, 0x6D5) = 0;
}

