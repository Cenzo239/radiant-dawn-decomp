#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800F0994(char *);
FE10_PROTO void * fn_80102928(void *, int, int, unsigned short, void *);
#else
s32 fn_800F0994();
M2C_UNK fn_80102928();
#endif

void fn_80102C6C(
#if TARGET_PC
void *arg0, s8 *arg1, s32 arg2, s32 arg3, s32 arg4
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4
#endif
) {
    fn_80102928(arg0, fn_800F0994(arg1), arg2, arg3, arg4);
}
