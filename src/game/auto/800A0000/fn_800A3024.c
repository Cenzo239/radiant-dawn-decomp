#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80085708(char *);
FE10_PROTO void * fn_801D3D78(void *);
#else
M2C_UNK fn_80085708();
M2C_UNK fn_801D3D78(M2C_UNK);
#endif
extern u8 lbl_80364C1C[0x424];

s32 fn_800A3024(void) {
    fn_801D3D78(fn_80085708(lbl_80364C1C + 0x2D));
    return 1;
}
