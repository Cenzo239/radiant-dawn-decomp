#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO s8 fn_8012408C(void *);
FE10_PROTO s32 fn_80171E5C(void *, void *, s32, s32, s32, s32);
#else
s8 fn_8012408C(s32);
void fn_80171E5C(s32, s32, s32, s32, s32, s32);
#endif
#if TARGET_PC
s32 fn_801723A8(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0) {
    f32 v = (f32) fn_8012408C(arg1);
    return fn_80171E5C(arg0, arg1, (s32) (v * farg0), arg2, arg3, arg4);
}
#else
void fn_801723A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0) {
    f32 v = (f32) fn_8012408C(arg1);
    fn_80171E5C(arg0, arg1, (s32) (v * farg0), arg2, arg3, arg4);
}
#endif
