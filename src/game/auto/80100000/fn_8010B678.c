#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char fn_8010B5AC(void *, int);
#else
s32 fn_8010B5AC();
#endif

s32 fn_8010B678(s32 arg0) {
    s32 var_r31;

    var_r31 = 0;
loop_1:
    if (fn_8010B5AC(arg0, var_r31) & 8) {
        return 1;
    }
    var_r31 += 1;
    if (var_r31 >= 7) {
        return 0;
    }
    goto loop_1;
}
