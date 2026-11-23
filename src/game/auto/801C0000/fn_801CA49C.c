#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_80008F20(void*, int);
#if TARGET_PC
FE10_PROTO void * fn_8013B9A8(void);
FE10_PROTO void fn_801379F8(void *, int);
#else
s32 fn_8013B9A8();
void fn_801379F8(int, int);
#endif
void fn_8012D908(void);
void fn_801CA49C(u8 *arg0, s32 arg1) {
    s32 t;
    *arg0 &= 0xFFFFFFF3;
    fn_80008F20(arg0 + 0x14, 0xFF);
    if (arg1 != 0) {
        t = fn_8013B9A8();
        if (t != 0) {
            fn_801379F8(t, 1);
        }
        fn_8012D908();
    }
}
