#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800581F4(void *);
FE10_PROTO void * fn_80085708(char *);
#else
M2C_UNK fn_800581F4(M2C_UNK);
M2C_UNK fn_80085708();
#endif
extern u8 lbl_80364C1C[0x424];

s32 fn_800A2FCC(void) {
    fn_800581F4(fn_80085708(lbl_80364C1C + 0x2D));
    return 1;
}
