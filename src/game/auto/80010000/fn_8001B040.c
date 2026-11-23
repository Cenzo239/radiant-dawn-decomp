#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s8 * fn_80007F3C(void *);
s32 fn_80015070(s8*, s32, s32);
#if TARGET_PC
FE10_PROTO void fn_80017D94(void *);
FE10_PROTO int fn_80018208(void *, int);
FE10_PROTO void fn_80018888(unsigned int *, int);
#else
M2C_UNK fn_80017D94();
s32 fn_80018208();
M2C_UNK fn_80018888();
#endif

void fn_8001B040(s8 *arg0) {
    s8 *temp_r31;

    temp_r31 = fn_80007F3C(arg0);
    if (fn_80015070(temp_r31, 4, 0x400) > 0) {
        if (((s32) M2C_FIELD(temp_r31, s32 *, 0x3C) != 0) && (fn_80018208(arg0, 1) == 0)) {
            fn_80018888(arg0, 1);
        }
        if (((s32) M2C_FIELD(temp_r31, s32 *, 0x40) != 0) && (fn_80018208(arg0, 2) == 0)) {
            fn_80018888(arg0, 2);
        }
        if (((s32) M2C_FIELD(temp_r31, s32 *, 0x44) != 0) && (fn_80018208(arg0, 3) == 0)) {
            fn_80018888(arg0, 3);
        }
        if ((s32) M2C_FIELD(arg0, s32 *, 0x54) != 0) {
            fn_80017D94(arg0);
        }
    }
    fn_80015070(temp_r31, 0, 4);
}

