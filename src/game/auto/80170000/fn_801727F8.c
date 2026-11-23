#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80066130(void *, char, char, unsigned int);
FE10_PROTO void * fn_800CFC50(void *, char, char, unsigned char, void *);
FE10_PROTO short fn_80115CD8(void *, char, char);
#else
s32 fn_80066130();
M2C_UNK fn_800CFC50();
s16 fn_80115CD8();
#endif
extern u8 lbl_803CB770[0x10];
extern u8 lbl_803E7320[0x1208];
extern u8 lbl_803EC898[0x15867];

void fn_801727F8(s8 *arg0, s8 arg1, s8 arg2) {
    s32 temp_r30;
    s8 *temp_r3;

    temp_r30 = arg1 + (arg2 << 6);
    temp_r3 = lbl_803EC898 + temp_r30;
    if (((s32) M2C_FIELD(temp_r3, u8 *, 0xD) == 0) && !(M2C_FIELD(temp_r3, u8 *, 0x300D) & 1) && (fn_80115CD8(lbl_803EC898, arg1, arg2) <= 0x7530) && (fn_80066130(lbl_803CB770, arg1, arg2, M2C_FIELD(arg0, u8 *, 8)) == 0) && ((s8) M2C_FIELD((lbl_803EC898 + 0x10000 + temp_r30), u8 *, -0xE72) == 0)) {
        fn_800CFC50(lbl_803E7320, arg1, arg2, 0, M2C_FIELD(arg0, u8 *, 8));
    }
}
