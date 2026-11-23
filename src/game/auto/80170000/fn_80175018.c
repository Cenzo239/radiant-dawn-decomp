#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
s32 fn_80083B84();
#endif
extern u8 lbl_80387860[0x18];

s32 fn_80175018(void) {
    return fn_80083B84(lbl_80387860) != 0;
}
