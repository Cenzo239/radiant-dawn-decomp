#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80257628(char *);
#else
s32 fn_80257628();
#endif
M2C_UNK fn_80257CC8();
M2C_UNK fn_80330018();
extern u8 lbl_80361098[0x50];
extern s8 lbl_804CB0F8;
extern s32 lbl_804CB700;

void fn_80022700(void) {
    goto loop_2;
block_1:
    fn_80330018();
loop_2:
    if (fn_80257628(lbl_80361098) == 0) {
        goto block_1;
    }
    lbl_804CB0F8 = 1;
loop_4:
    if (lbl_804CB700 & 0x100000) {
        goto block_6;
    }
    fn_80257CC8();
block_6:
    fn_80330018();
    goto loop_4;
}
