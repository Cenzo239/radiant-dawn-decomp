#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80084E64(void *);
#else
M2C_UNK fn_80084E64();
#endif
extern u8 lbl_80381DD0[0x18];

s32 fn_800A29F4(void) {
    fn_80084E64(lbl_80381DD0);
    return 0;
}
