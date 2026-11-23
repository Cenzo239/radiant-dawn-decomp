#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
#else
s8 * fn_80060728();
#endif
extern u8 lbl_803CAB38[0x988];

u8 fn_800A34D8(void) {
    return M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0xE);
}
