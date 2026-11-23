#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80081050(void *, void *);
#else
M2C_UNK fn_80081050();
#endif
extern u8 lbl_80381DD0[0x18];

s32 fn_800A29C4(void) {
    fn_80081050(lbl_80381DD0, 4);
    return 0;
}
