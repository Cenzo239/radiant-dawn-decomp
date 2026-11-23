#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_8002600C(void *, unsigned int, short);
#else
M2C_UNK fn_8002600C();
#endif

void fn_8002C06C(
#if TARGET_PC
s8 *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {

    fn_8002600C(arg0 + 0xDE0, 0x24, 0);
    fn_8002600C(arg0 + 0xDE0, 0x25, 0);
    fn_8002600C(arg0 + 0xDE0, arg1 != 0 ? 0x6E : 0x70, 0);
    fn_8002600C(arg0 + 0xDE0, 0x2A, 0);
}

