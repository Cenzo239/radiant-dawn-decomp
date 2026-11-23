#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800C3C3C(char *, void *, unsigned char);
#else
M2C_UNK fn_800C3C3C();
#endif
extern u8 fn_801D0AE0[0x28];
extern u8 lbl_8036EA60[0xd];

void fn_801D0B08(void) {
    fn_800C3C3C(lbl_8036EA60, fn_801D0AE0, 0);
}
