#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
FE10_PROTO char * fn_800D0864(char *);
#else
s8 * fn_80060728();
M2C_UNK fn_800D0864();
#endif
extern u8 lbl_8037D2E0[0xa];
extern u8 lbl_803CAB38[0x988];
extern u8 lbl_804CA178[0x8];

void fn_8004B688(void) {
    if ((u8) M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11) == 2) {
        fn_800D0864(lbl_804CA178);
        return;
    }
    fn_800D0864(lbl_8037D2E0);
}
