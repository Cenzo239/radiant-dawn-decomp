#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_800D4228(char *);
FE10_PROTO void fn_800893C4(void *);
#else
int fn_800D4228(int);
void fn_800893C4(int);
#endif
void fn_801D237C(u8 *arg0) {
    s32 v = *(s32*)(arg0 + 0x40);
    if (v != 0) {
        fn_800893C4(fn_800D4228(v));
    }
}
