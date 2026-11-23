#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800893E4(void *, void *(*)(void *, void *), void *);
#else
M2C_UNK fn_800893E4();
#endif
extern u8 fn_8017C298[0x18];
extern u8 lbl_80387B68[0x20];

void
#if TARGET_PC
*
#endif
fn_8017C2B0(s16 arg0) {
    s16 sp8;

    sp8 = arg0;
#if TARGET_PC
    return fn_800893E4(lbl_80387B68, fn_8017C298, &sp8);
#else
    fn_800893E4(lbl_80387B68, fn_8017C298, &sp8);
#endif
}
