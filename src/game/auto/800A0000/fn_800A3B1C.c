#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80062598(void *, void *);
FE10_PROTO void * fn_80083B84(void *);
#else
M2C_UNK fn_80062598();
s32 fn_80083B84();
#endif
M2C_UNK fn_800E1D94();
M2C_UNK strcpy();
extern u8 lbl_80381BF0[0x2c];
extern u8 lbl_803CAB38[0x988];

void fn_800A3B1C(s32 arg0) {
    fn_800E1D94();
    strcpy(arg0 + 0x30, fn_80083B84(lbl_80381BF0) + 0x30);
    fn_80062598(lbl_803CAB38, arg0);
}
