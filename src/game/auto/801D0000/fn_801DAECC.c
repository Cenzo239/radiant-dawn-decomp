#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80006A64(void *, void *, unsigned int);
#else
M2C_UNK fn_80006A64();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CBDFC;
#else
extern s32 lbl_804CBDFC;
#endif

void fn_801DAECC(s32 arg0) {
    fn_80006A64(lbl_804CBDFC, arg0, 0);
}
