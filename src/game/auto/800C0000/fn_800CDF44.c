#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80081050(void *, void *);
#else
M2C_UNK fn_80081050();
#endif
extern u8 lbl_803832E0[0x680];

void fn_800CDF44(void) {
    fn_80081050(lbl_803832E0, 3);
}
