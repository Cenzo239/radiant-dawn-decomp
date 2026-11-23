#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_801109FC(char *);
#else
s32 fn_801109FC();
#endif

s32 fn_801109B8(
#if TARGET_PC
u16 *arg0, char *arg1
#else
u16 *arg0, s32 arg1
#endif
) {
    return (*arg0 & fn_801109FC(arg1)) != 0;
}
