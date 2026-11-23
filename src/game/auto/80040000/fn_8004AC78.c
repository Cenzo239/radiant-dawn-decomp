#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80110D38(void *);
#else
M2C_UNK fn_80110D38();
#endif
extern u8 lbl_803CAAE0[0x28];

void fn_8004AC78(void) {
    fn_80110D38(lbl_803CAAE0);
}
