#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_801038D0(void *, void *);
FE10_PROTO int fn_8012CA88(void *);
#else
M2C_UNK fn_801038D0();
s32 fn_8012CA88();
#endif
extern s8 *lbl_804CB3D8;

void fn_8004AC84(s32 arg0) {
    if ((M2C_FIELD(lbl_804CB3D8, s32 *, 0x10C) & 0x800000) && (fn_8012CA88(lbl_804CB3D8) == 0)) {
        fn_801038D0(lbl_804CB3D8, arg0);
    }
}
