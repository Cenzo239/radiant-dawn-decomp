#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_8006074C(void *);
FE10_PROTO unsigned int fn_80068424(char **, int);
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO s8 fn_8024F7EC(char *);
#else
M2C_UNK fn_8006074C();
M2C_UNK fn_80068424();
M2C_UNK fn_80083B78();
s8 fn_8024F7EC(M2C_UNK);
#endif
extern u8 lbl_803CAB38[0x988];

void fn_80044180(s32 arg0) {
    s8 temp_r3;

    temp_r3 = fn_8024F7EC(fn_80068424(fn_8006074C(lbl_803CAB38), M2C_FIELD(lbl_803CAB38, u8 *, 0x11)));
    if ((u32) ((u32) ((-1 - temp_r3) | (temp_r3 + 1)) >> 0x1FU) == 1) {
        fn_80083B78(arg0);
    }
}

