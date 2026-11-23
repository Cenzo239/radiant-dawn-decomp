#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80089388(int, void **);
#else
M2C_UNK fn_80089388();
#endif
extern u8 lbl_80381058[0x58];

void fn_80089A98(void) {
    fn_80089388(1, lbl_80381058);
}
