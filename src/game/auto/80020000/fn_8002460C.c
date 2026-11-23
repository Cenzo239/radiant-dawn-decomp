#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
s32 fn_80083B84();
#endif
extern u8 lbl_803789A0[0x170];

s32 fn_8002460C(void) {
    return fn_80083B84(lbl_803789A0) != 0;
}
