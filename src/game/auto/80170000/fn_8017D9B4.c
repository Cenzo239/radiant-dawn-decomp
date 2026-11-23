#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int fn_80007630(void *, char *);
FE10_PROTO void * fn_80008110(void *, char *);
FE10_PROTO void * fn_80081050(void *, void *);
#else
s32 fn_80007630();
s32 fn_80008110();
s8 * fn_80081050();
#endif
extern u8 lbl_8036B4C8[0x150];
extern u8 lbl_80387B88[0x28];

void fn_8017D9B4(
#if TARGET_PC
void *arg0, void *arg1
#else
s32 arg0, s32 arg1
#endif
) {
    if ((fn_80007630(arg0, lbl_8036B4C8 + 0xC8) >= 0) && (fn_80008110(arg0, lbl_8036B4C8 + 0xC8) != 0)) {
        M2C_FIELD(fn_80081050(lbl_80387B88, arg1), s32 *, 0x30) = arg0;
    }
}

