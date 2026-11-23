#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80075D78(void *);
#else
M2C_UNK fn_80075D78(s32);
#endif

s32 fn_800A2B50(s32 arg0) {
    fn_80075D78(arg0);
    return 1;
}
