#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80007F3C(void *);
FE10_PROTO int fn_80014E24(void *, char *, void *, void *);
#else
M2C_UNK fn_80007F3C(void *);
M2C_UNK fn_80014E24();
#endif
extern u8 fn_8010830C[0x30c];
extern u8 lbl_80367F40[0x28];

void fn_80108618(
#if TARGET_PC
s8 *arg0, void *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 0x88) = arg1;
        fn_80014E24(fn_80007F3C(arg0), lbl_80367F40 + 0x20, fn_8010830C, 1);
    }
}
