#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800846BC(void *);
#else
M2C_UNK fn_800846BC();
#endif
extern u8 lbl_80387B68[0x20];

void fn_8017C2E8(void) {
    fn_800846BC(lbl_80387B68);
}
