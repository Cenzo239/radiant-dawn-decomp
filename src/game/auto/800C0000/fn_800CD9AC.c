#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
FE10_PROTO void fn_80109744(void *);
FE10_PROTO void fn_801097FC(void *);
#else
M2C_UNK fn_80060728();
M2C_UNK fn_80109744(M2C_UNK);
M2C_UNK fn_801097FC(M2C_UNK);
#endif
M2C_UNK fn_8019FABC();
extern u8 lbl_803CAB38[0x988];

void fn_800CD9AC(void) {
    fn_80109744(fn_80060728(lbl_803CAB38));
    fn_801097FC(fn_80060728(lbl_803CAB38));
    fn_8019FABC();
}
