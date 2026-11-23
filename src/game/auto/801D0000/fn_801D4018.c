#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80062380(char *, char *);
#else
M2C_UNK fn_80062380();
#endif
extern u8 lbl_803CAB38[0x988];

void fn_801D4018(void) {
    fn_80062380(lbl_803CAB38, lbl_803CAB38 + 0x914);
}
