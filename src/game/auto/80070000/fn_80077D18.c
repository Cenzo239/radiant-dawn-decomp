#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char * fn_80077524(void *, unsigned char *, void **, unsigned int *, unsigned int *, int *, ...);
#else
M2C_UNK fn_80077524();
#endif
#if TARGET_PC
FE10_PROTO extern s8 *lbl_804CB598;
#else
extern s32 lbl_804CB598;
#endif

void
#if TARGET_PC
*
#endif
fn_80077D18(
#if TARGET_PC
s8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4
#endif
) {
#if TARGET_PC
    return fn_80077524(lbl_804CB598, arg0, arg1, arg2, arg3, arg4, arg2, arg1);
#else
    fn_80077524(lbl_804CB598, arg0, arg1, arg2, arg3, arg4, arg2, arg1);
#endif
}
