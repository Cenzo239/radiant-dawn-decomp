#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int * fn_8009D948(char *, int);
FE10_PROTO int * fn_8010B1B4(int);
FE10_PROTO void * fn_8010B1D8(char *);
#else
M2C_UNK fn_8009D948();
u32 fn_8010B1B4();
u32 fn_8010B1D8(M2C_UNK);
#endif
extern u8 lbl_803E50B0[0x10];

s32 fn_800A0B1C(s8 *arg0) {
    u32 temp_r28;
    u32 temp_r29;
    u32 temp_r31;
    u32 temp_r3;

    if ((s16) M2C_FIELD(lbl_803E50B0, s16 *, 0) != (s16) M2C_FIELD(arg0, s16 *, 0x18)) {
        return 0;
    }
    temp_r28 = fn_8010B1D8(fn_8009D948(arg0, M2C_FIELD(arg0, u16 *, 0x14)));
    temp_r29 = fn_8010B1D8(fn_8009D948(arg0, M2C_FIELD(arg0, u16 *, 0x16)));
    temp_r31 = fn_8010B1B4(M2C_FIELD(lbl_803E50B0, s16 *, 6));
    temp_r3 = fn_8010B1B4(M2C_FIELD(lbl_803E50B0, s16 *, 8));
    if ((temp_r31 == temp_r28) && (temp_r3 == temp_r29)) {
        return 1;
    }
    if ((temp_r31 == temp_r29) && (temp_r3 == temp_r28)) {
        return 1;
    }
    return 0;
}

