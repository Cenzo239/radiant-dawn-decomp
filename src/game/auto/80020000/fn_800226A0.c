#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB0F4;
#else
extern s32 lbl_804CB0F4;
#endif

s32 fn_800226A0(void) {
    return lbl_804CB0F4;
}
