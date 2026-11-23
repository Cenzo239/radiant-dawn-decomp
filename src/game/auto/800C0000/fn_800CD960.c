#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80061524(void *);
#else
M2C_UNK fn_80061524();
#endif
extern u8 lbl_803CAB38[0x988];

void fn_800CD960(void) {
    fn_80061524(lbl_803CAB38);
}
