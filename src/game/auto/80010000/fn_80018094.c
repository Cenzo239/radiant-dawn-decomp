#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80014F64(void *, char *, void *);
FE10_PROTO void fn_80015174(void *);
FE10_PROTO void * fn_80075B90(void *);
FE10_PROTO void fn_800761F0(void *);
#else
M2C_UNK fn_80014F64();
M2C_UNK fn_80015174();
M2C_UNK fn_80075B90(M2C_UNK);
M2C_UNK fn_800761F0();
#endif
s32 fn_8023F8B8(M2C_UNK);
#if TARGET_PC
FE10_PROTO char * fn_8023F92C(M2C_UNK);
#else
M2C_UNK fn_8023F92C(M2C_UNK);
#endif

void fn_80018094(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    if (fn_8023F8B8(fn_8023F92C(fn_80075B90(arg0))) <= 1) {
        fn_80014F64(arg0, 0, 0);
    }
    fn_80015174(arg0);
    fn_800761F0(arg0);
}
