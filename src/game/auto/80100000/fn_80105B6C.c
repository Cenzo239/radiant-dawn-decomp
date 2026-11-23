#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8028C0D0(void *, void *, unsigned int, unsigned int);
#else
M2C_UNK fn_8028C0D0();
#endif
extern u8 fn_80111C24[0x54];
extern u8 lbl_803E92A0[0x2ee0];

void fn_80105B6C(void) {
    fn_8028C0D0(lbl_803E92A0, fn_80111C24, 0x28, 0x12C);
}
