#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_8006074C(void *);
FE10_PROTO char * fn_80092958(void *);
FE10_PROTO char * fn_800D0864(char *);
FE10_PROTO void fn_800D0B38(int, char *);
#else
M2C_UNK fn_8006074C();
s32 fn_80092958(M2C_UNK);
M2C_UNK fn_800D0864();
M2C_UNK fn_800D0B38();
#endif
extern u8 lbl_803CAB38[0x988];
extern u8 lbl_804CA150[0x7];

void fn_8004B648(void) {
    fn_800D0B38(0, fn_80092958(fn_8006074C(lbl_803CAB38)));
    fn_800D0864(lbl_804CA150);
}
