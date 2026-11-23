#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800D5448(void *, void *, int);
#else
M2C_UNK fn_800D5448();
#endif
extern u8 lbl_803CAABC[0xc];

void fn_8004AB18(s32 arg0) {
    fn_800D5448(lbl_803CAABC, arg0, 0);
}
