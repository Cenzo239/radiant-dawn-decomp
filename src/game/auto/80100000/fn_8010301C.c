#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO f32 fn_800FB08C(void *, void *);
#else
f32 fn_800FB08C(s32, s32);
#endif
#if TARGET_PC
FE10_PROTO void * fn_80102E10(void *, int, void *, float, void *);
#else
s32 fn_80102E10();
#endif

s32 fn_8010301C(
#if TARGET_PC
void *arg0, void *arg1, s32 arg2, s32 arg3, void *arg4
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4
#endif
) {
    if (arg1 == 0) {
        return 0;
    }
#if TARGET_PC
    return (s32) FE10_PTRINT(fn_80102E10(arg0, arg2, (void *) (intptr_t) arg3, (f32) (s32) fn_800FB08C(arg0, arg1), arg4));
#else
    return fn_80102E10(arg0, arg2, arg3, arg4, (f32) (s32) fn_800FB08C(arg0, arg1));
#endif
}
