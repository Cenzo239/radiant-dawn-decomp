#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80010788(int, unsigned char, void *, void *);
#else
M2C_UNK fn_80010788();
#endif
extern u8 fn_801769F4[0x40];

void fn_80176A34(s32 arg0) {
    fn_80010788(3, arg0, fn_801769F4, 0);
}
