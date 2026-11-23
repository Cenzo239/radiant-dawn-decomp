#include "game/auto/m2c_prelude.h"
s32 fn_80079E00(void *);
M2C_UNK fn_801062C0();
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB778;
#else
extern u8 lbl_804CB778[0x8];
#endif

void fn_801060B0(s8 *arg0) {
    if (fn_80079E00(arg0) == 0) {
        fn_801062C0(lbl_804CB778, M2C_FIELD(arg0, s32 *, 0x60) != 0);
    }
}
