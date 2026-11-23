#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_80008F20(void*, int);
#if TARGET_PC
FE10_PROTO void * fn_8013B9A8(void);
FE10_PROTO void fn_801379F8(void *, int);
#else
int fn_8013B9A8(void);
void fn_801379F8(int, int);
#endif
void fn_8012D908(void);
void fn_801CA444(u8 *arg0, s32 arg1) {
    *arg0 |= 0xC;
    fn_80008F20(arg0 + 0x14, 0);
    if (arg1 != 0) {
        fn_801379F8(fn_8013B9A8(), 1);
        fn_8012D908();
    }
}
