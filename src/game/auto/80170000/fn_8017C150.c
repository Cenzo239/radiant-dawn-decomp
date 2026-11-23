#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80011CBC(void*, void *);
#else
void fn_80011CBC(void*, s32);
#endif
void fn_80020EEC(void);
extern u8 fn_8017AFF4[0x4c];
void fn_8017C150(u8 *arg0) {
    s32 *p = (s32*)(arg0 + 0x30);
    if (*p != 0) {
        fn_80011CBC(fn_8017AFF4, *p);
        *p = 0;
    }
    if (arg0[0x40] != 0) {
        fn_80020EEC();
    }
}
