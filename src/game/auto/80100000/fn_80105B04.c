#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80079210(void *);
#else
M2C_UNK fn_80079210();
#endif
#if TARGET_PC
FE10_PROTO void fn_8028C0D0(void *, void *, unsigned int, unsigned int);
#else
M2C_UNK fn_8028C0D0();
#endif
extern u8 fn_80111C24[0x54];

s32
#if TARGET_PC
*
#endif
fn_80105B04(
#if TARGET_PC
s8 *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
    if (arg0 != 0) {
        fn_8028C0D0(arg0 + 8, fn_80111C24, 0x28, 0x10);
        if (arg1 > 0) {
            fn_80079210(arg0);
        }
    }
    return arg0;
}
