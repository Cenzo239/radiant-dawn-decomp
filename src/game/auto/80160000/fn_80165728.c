#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80075FB4(void *, int);
#else
s32 fn_80075FB4();
#endif
M2C_UNK fn_80161BA4();
M2C_UNK fn_80164CD0();
M2C_UNK fn_80169510();
extern u8 lbl_8036B0D0[0xf];
extern s32 lbl_804CB8C0;

void fn_80165728(void) {
    lbl_804CB8C0 = fn_80075FB4(lbl_8036B0D0, 0x20);
    fn_80169510();
    fn_80164CD0();
    fn_80161BA4();
}
