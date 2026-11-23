#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_801038D0(void *, void *);
#else
M2C_UNK fn_801038D0();
#endif
s8 fn_801284C4(s8*);
#if TARGET_PC
FE10_PROTO int fn_80128F64(void *);
#else
s32 fn_80128F64();
#endif
extern u8 lbl_803C8E80[0x1648];

s32 fn_80047750(s32 arg0) {
    s8 *temp_r31;

    temp_r31 = M2C_FIELD(lbl_803C8E80, s8 **, 0x3F0);
    if (temp_r31 == NULL) {
        return 0;
    }
    if ((s8) M2C_FIELD(temp_r31, u8 *, 0x114) == 0) {
        return 0;
    }
    if ((fn_80128F64(temp_r31) != 0) && (fn_801284C4(temp_r31) == 0)) {
        fn_801038D0(temp_r31, arg0);
        return 1;
    }
    return 0;
}
