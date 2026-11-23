#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80062598(void *, void *);
FE10_PROTO void fn_800846BC(void *);
#else
M2C_UNK fn_80062598();
M2C_UNK fn_800846BC();
#endif
M2C_UNK fn_800E1D94();
extern u8 lbl_80381BF0[0x2c];
extern u8 lbl_803CAB38[0x988];

void fn_800A3A1C(s32 arg0) {
    fn_800E1D94();
    fn_800846BC(lbl_80381BF0);
    fn_80062598(lbl_803CAB38, arg0);
}
