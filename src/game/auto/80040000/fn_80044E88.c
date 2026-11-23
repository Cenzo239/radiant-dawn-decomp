#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800AE8E4(void *);
FE10_PROTO void * fn_800EDB70(void *);
#else
M2C_UNK fn_800AE8E4(s32);
M2C_UNK fn_800EDB70(s32);
#endif
extern u8 lbl_803C8E80[0x1648];

void fn_80044E88(s32 arg0) {
    if (M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) & 0x80000000) {
        fn_800EDB70(arg0);
        return;
    }
    fn_800AE8E4(arg0);
    M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) = (s32) (M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) | 0x20000000);
}
