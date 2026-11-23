#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO void * fn_800C3558(void);
FE10_PROTO void * fn_800C357C(void);
FE10_PROTO M2C_UNK fn_801D0E18(char *);
#else
M2C_UNK fn_80083B78();
M2C_UNK fn_800C3558();
s32 fn_800C357C();
M2C_UNK fn_801D0E18(M2C_UNK);
#endif

void fn_8009E328(s32 arg0) {
    fn_801D0E18(fn_800C3558());
    if (fn_800C357C() != 6) {
        fn_80083B78(arg0);
    }
}
