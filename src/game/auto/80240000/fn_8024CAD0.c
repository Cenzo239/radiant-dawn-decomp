#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s32 fn_8008A1DC(void *);
#else
s32 fn_8008A1DC(s32);
#endif

s32 fn_8024CAD0(s32 arg0, s32 *arg1) {
    *arg1 = fn_8008A1DC(arg0);
    return arg0;
}
