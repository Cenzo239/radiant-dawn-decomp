#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80257340(char *, unsigned int);
#else
M2C_UNK fn_80257340();
#endif
extern u8 lbl_80366184[0xb4];

void fn_800CDF00(void) {
    fn_80257340(lbl_80366184 + 0x84, 0x10000);
    fn_80257340(lbl_80366184 + 0x9C, 0x10000);
}
