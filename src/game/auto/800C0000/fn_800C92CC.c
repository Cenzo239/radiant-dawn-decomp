#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK DCInvalidateRange();
#if TARGET_PC
FE10_PROTO void * fn_80079958(unsigned int, unsigned int);
FE10_PROTO void * fn_80081050(void *, void *);
#else
s32 fn_80079958();
s8 * fn_80081050();
#endif
s32 fn_8030585C();
#if TARGET_PC
FE10_PROTO void fn_80305A40(void *, void *, unsigned short, unsigned short, int, int, int, unsigned char);
FE10_PROTO void fn_80305C94(void *, int, int, float, float, float, unsigned char, unsigned char, int);
#else
M2C_UNK fn_80305A40();
M2C_UNK fn_80305C94();
#endif
extern u8 lbl_803829A0[0x28];
extern f32 lbl_804CD5A0;
extern f32 lbl_804CD5D8;
extern f32 lbl_804CD5FC;

void fn_800C92CC(s8 *arg0) {
    s32 temp_r31;
    f32 fb;
    f32 fa;

    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    temp_r31 = fn_8030585C(0x260, 0x1C0, 4, 0, 0);
    if ((s32) M2C_FIELD(arg0, s32 *, 0x48) == 0) {
        M2C_FIELD(arg0, s32 *, 0x48) = fn_80079958(temp_r31, 0x40);
    }
    DCInvalidateRange(M2C_FIELD(arg0, s32 *, 0x48), temp_r31);
    fn_80305A40(arg0 + 0x4C, M2C_FIELD(arg0, s32 *, 0x48), 0x260, 0x1C0, 4, 0, 0, 0);
    fn_80305C94(arg0 + 0x4C, 0, 0, 0, 0, 0, lbl_804CD5A0, lbl_804CD5A0, lbl_804CD5A0);
    M2C_FIELD(fn_80081050(lbl_803829A0, 6), s8 **, 0x54) = arg0;
    fa = lbl_804CD5D8;
    fb = lbl_804CD5FC;
    M2C_FIELD(arg0, f32 *, 0x38) = fa;
    M2C_FIELD(arg0, f32 *, 0x3C) = fb;
    M2C_FIELD(arg0, s16 *, 0x34) = 0;
    M2C_FIELD(arg0, s8 *, 0x30) = 0;
}

