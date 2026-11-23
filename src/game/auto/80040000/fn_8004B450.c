#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB3D8;
#else
extern s32 lbl_804CB3D8;
#endif

void fn_8004B450(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) lbl_804CB3D8;
}
