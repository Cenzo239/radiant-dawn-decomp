#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
s32 fn_80083B84();
#endif
extern u8 lbl_8038A8A8[0xe8];

s32 fn_801C6E78(void) {
    return fn_80083B84(lbl_8038A8A8) != 0;
}
