#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80031B24(void *, void *, void *);
#else
M2C_UNK fn_80031B24();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB3E0;
FE10_PROTO extern void *lbl_804CB3E8;
#else
extern s32 lbl_804CB3E0;
extern u8 lbl_804CB3E8[0x8];
#endif

void fn_8004AEF0(s32 arg0) {
    fn_80031B24(lbl_804CB3E8, arg0, lbl_804CB3E0);
}
