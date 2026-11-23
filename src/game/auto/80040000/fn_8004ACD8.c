#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_801288D4(void *);
#else
M2C_UNK fn_801288D4();
#endif
#if TARGET_PC
FE10_PROTO s32 fn_8012CA88(void *);
#else
s32 fn_8012CA88();
#endif
extern s8 *lbl_804CB3D8;

void fn_8004ACD8(void) {
#if TARGET_PC
    if ((M2C_FIELD(lbl_804CB3D8, s32 *, 0x10C) & 0x800000) && (fn_8012CA88(lbl_804CB3D8) == 0)) {
        fn_801288D4(lbl_804CB3D8);
    }
#else
    if ((M2C_FIELD(lbl_804CB3D8, s32 *, 0x10C) & 0x800000) && (fn_8012CA88() == 0)) {
        fn_801288D4(lbl_804CB3D8);
    }
#endif
}
