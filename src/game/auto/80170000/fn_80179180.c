#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800846BC(void *);
#else
M2C_UNK fn_800846BC();
#endif
extern u8 lbl_80387AC8[0x38];

void fn_80179180(void) {
    fn_800846BC(lbl_80387AC8);
}
