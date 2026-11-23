#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800E3A10(char *, void *, ...);
FE10_PROTO void fn_800E4904(char *, int, void *, ...);
FE10_PROTO void fn_800E5878(void *, void *);
#else
s8 * fn_800E3A10();
M2C_UNK fn_800E4904();
M2C_UNK fn_800E5878();
#endif
M2C_UNK fn_800F7790();
extern u8 fn_80101EEC[0x144];
extern u8 fn_80102030[0x1a8];
extern u8 lbl_80367D50[0x140];

void fn_801024F4(s8 *arg0) {
    M2C_UNK sp8;
    s8 *temp_r3;
    s8 *temp_r6;

    temp_r3 = fn_800E3A10(lbl_80367D50 + 0x10C, arg0, lbl_80367D50);
    if (temp_r3 != NULL) {
        fn_800F7790(&sp8, M2C_FIELD(arg0, s32 *, 0x30));
        fn_800E5878(temp_r3, M2C_FIELD(arg0, s32 *, 0x30));
        M2C_FIELD(M2C_FIELD(temp_r3, s8 **, 0x30), M2C_UNK **, 0x98) = fn_80101EEC;
        temp_r6 = M2C_FIELD(temp_r3, s8 **, 0x30);
        M2C_FIELD(temp_r6, M2C_UNK **, 0x9C) = fn_80102030;
        fn_800E4904(temp_r3, 0, arg0, temp_r6, fn_80102030);
    }
}
