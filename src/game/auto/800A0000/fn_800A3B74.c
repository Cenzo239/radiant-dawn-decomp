#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800846BC(void *);
#else
M2C_UNK fn_800846BC();
#endif
extern u8 lbl_80381BF0[0x2c];

void fn_800A3B74(void) {
    fn_800846BC(lbl_80381BF0);
}
