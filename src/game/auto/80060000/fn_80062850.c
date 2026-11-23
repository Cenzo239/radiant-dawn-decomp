#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_8010B094(int);
#else
s8 * fn_8010B094();
#endif
extern f32 lbl_804CCF20;
extern f32 lbl_804CCF40;

f32 fn_80062850(s8 *arg0) {
    f32 var_f1;
    u8 temp_r0;

    temp_r0 = M2C_FIELD(fn_8010B094(M2C_FIELD(arg0, u8 *, 0x10)), u8 *, 0x89);
    var_f1 = lbl_804CCF20;
    switch ((s32) temp_r0) {                        /* irregular */
    case 0:
        var_f1 += M2C_FIELD(arg0, f32 *, 0x24);
        break;
    case 1:
        var_f1 += M2C_FIELD(arg0, f32 *, 0x28);
        break;
    case 2:
        var_f1 += M2C_FIELD(arg0, f32 *, 0x2C);
        break;
    case 3:
        var_f1 += M2C_FIELD(arg0, f32 *, 0x28);
        var_f1 += M2C_FIELD(arg0, f32 *, 0x2C);
        break;
    case 4:
        var_f1 += M2C_FIELD(arg0, f32 *, 0x24);
        var_f1 += M2C_FIELD(arg0, f32 *, 0x28);
        var_f1 += M2C_FIELD(arg0, f32 *, 0x2C);
        break;
    }
    if (lbl_804CCF40 < var_f1) {
        var_f1 = lbl_804CCF40;
    }
    return var_f1;
}

