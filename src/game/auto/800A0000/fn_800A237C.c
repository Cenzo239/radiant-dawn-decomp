#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
M2C_UNK fn_80083B84();
#endif
extern u8 lbl_80381BF0[0x2c];

void
#if TARGET_PC
*
#endif
fn_800A237C(void) {
#if TARGET_PC
    return fn_80083B84(lbl_80381BF0);
#else
    fn_80083B84(lbl_80381BF0);
#endif
}
