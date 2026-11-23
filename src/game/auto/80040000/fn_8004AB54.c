#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800D5448(void *, void *, int);
FE10_PROTO void fn_8012CAD8(void *);
#else
M2C_UNK fn_800D5448();
M2C_UNK fn_8012CAD8();
#endif
extern u8 lbl_803CAB14[0xc];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB3D8;
#else
extern s32 lbl_804CB3D8;
#endif

void fn_8004AB54(s32 arg0) {
    fn_8012CAD8(lbl_804CB3D8);
    fn_800D5448(lbl_803CAB14, arg0, 0);
}
