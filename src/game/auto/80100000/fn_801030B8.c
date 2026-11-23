#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO float fn_800FB100(void *, float, float);
FE10_PROTO void * fn_80102E10(void *, int, void *, float, void *);
#else
f32 fn_800FB100();
M2C_UNK fn_80102E10();
#endif
extern f32 lbl_804CDB50;

void fn_801030B8(
#if TARGET_PC
void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, M2C_UNK arg_sp0
#endif
) {
#if TARGET_PC
    fn_80102E10(arg0, arg3, (void *) (intptr_t) arg4, (f32) (s32) fn_800FB100(arg0, lbl_804CDB50 + (f32) arg1, lbl_804CDB50 + (f32) arg2), arg5);
#else
    fn_80102E10(arg0, arg3, arg4, arg5, (f32) (s32) fn_800FB100(lbl_804CDB50 + (f32) arg1, lbl_804CDB50 + (f32) arg2));
#endif
}
