#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8028392C(void *, int, int, unsigned char, void *, int);
#else
M2C_UNK fn_8028392C();
#endif
extern u8 lbl_80361260[0xa8];

void fn_8002563C(s32 arg0) {
    fn_8028392C(lbl_80361260 + 0x32, 0, 0, 1, arg0, 1);
}
