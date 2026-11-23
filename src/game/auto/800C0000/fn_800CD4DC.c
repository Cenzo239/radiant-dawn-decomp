#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
s8 * fn_80083B84();
#endif
extern u8 lbl_803832E0[0x680];

s32 fn_800CD4DC(void) {
    return M2C_FIELD(fn_80083B84(lbl_803832E0), s32 *, 0x60);
}
