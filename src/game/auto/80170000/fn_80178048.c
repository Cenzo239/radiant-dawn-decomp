#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800096E4(void *, int);
FE10_PROTO void fn_800097B0(void *, int);
#else
M2C_UNK fn_800096E4();
M2C_UNK fn_800097B0();
#endif

void fn_80178048(s8 *arg0, s32 arg1) {
    if (arg1 != 0) {
        fn_800097B0(M2C_FIELD(arg0, s32 *, 0x30), 6);
    } else {
        fn_800096E4(M2C_FIELD(arg0, s32 *, 0x30), 6);
    }
    M2C_FIELD(arg0, u8 *, 0x50) = (u8) (M2C_FIELD(arg0, u8 *, 0x50) | 4);
}
