#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80043DE8(int);
FE10_PROTO void fn_80252738(int, float);
#else
M2C_UNK fn_80043DE8();
M2C_UNK fn_80252738();
#endif
extern f32 lbl_804CD258;

void fn_800A230C(void) {
    fn_80043DE8(0x12C);
    fn_80252738(1, lbl_804CD258);
    fn_80252738(2, lbl_804CD258);
}
