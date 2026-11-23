#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int fn_8016D944(void *, unsigned int, unsigned int, short *, short *);
#else
M2C_UNK fn_8016D944();
#endif

#if TARGET_PC
s32 fn_8016E29C(void *arg0, s32 arg1, s16 *arg2, s16 *arg3) {
    return fn_8016D944(arg0, arg1, 0x2D, arg2, arg3);
}
#else
void fn_8016E29C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    fn_8016D944(arg0, arg1, 0x2D, arg2, arg3);
}
#endif

