#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_801E5640(void *, int, int);
FE10_PROTO void fn_8021C278(unsigned char *, char, int, void *, int);
FE10_PROTO int fn_80253EE4(char *, float);
#else
s8 * fn_801E5640();
M2C_UNK fn_8021C278();
M2C_UNK fn_80253EE4();
#endif
extern u8 lbl_80372600[0xa8];
extern f32 lbl_804CFF58;

void fn_80231BE0(s32 arg0) {
    s8 *temp_r3;

    temp_r3 = fn_801E5640(arg0, 0xC, 0);
    fn_8021C278(M2C_FIELD((temp_r3 + (M2C_FIELD(temp_r3, s16 *, 0x6A) * 4)), s32 *, 0x4C), 2, 0x78, arg0, 1);
    fn_80253EE4(lbl_80372600 + 0x8F, lbl_804CFF58);
}

