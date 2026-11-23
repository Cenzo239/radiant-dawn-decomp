#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800D5448(void *, void *, int);
#else
M2C_UNK fn_800D5448();
#endif
extern u8 lbl_804CBFC0[0x8];

void fn_8023FC40(s32 arg0) {
    fn_800D5448(lbl_804CBFC0, arg0, 0);
}
