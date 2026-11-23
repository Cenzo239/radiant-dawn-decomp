#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800610F4(void *);
#else
M2C_UNK fn_800610F4();
#endif
extern u8 lbl_803CAB38[0x988];

s32 fn_800A25A0(void) {
    fn_800610F4(lbl_803CAB38);
    return 1;
}
