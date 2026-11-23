#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO s32 fn_80014DE4(void *, s32);
FE10_PROTO void * fn_80007F3C(void *);
#else
s32 fn_80014DE4(s32, s32);
s32 fn_80007F3C(void *);
#endif
void fn_80010788(int, int, void*, void*);
extern u8 fn_8001B040[0xf4];
void fn_8001B134(u8 *arg0) {
    if (arg0[0xB] != 0) {
        if (fn_80014DE4(fn_80007F3C(arg0), 4) != 0) {
            fn_80010788(5, arg0[0x82], fn_8001B040, arg0);
        }
    }
}
