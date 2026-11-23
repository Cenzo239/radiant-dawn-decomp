#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800614A8(void *);
#else
M2C_UNK fn_800614A8();
#endif
extern u8 lbl_803CAB38[0x988];

void fn_80043208(void) {
    fn_800614A8(lbl_803CAB38);
}
