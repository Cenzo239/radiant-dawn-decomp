#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800D5448(void *, void *, int);
#else
M2C_UNK fn_800D5448();
#endif
extern u8 lbl_803CAB2C[0xc];

void fn_8004AF00(s32 arg0) {
    fn_800D5448(lbl_803CAB2C, arg0, 0);
}
