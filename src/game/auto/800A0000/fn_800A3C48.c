#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80081050(void *, void *);
#else
M2C_UNK fn_80081050();
#endif
M2C_UNK fn_800C9718();
#if TARGET_PC
FE10_PROTO void * fn_800D5448(void *, void *, int);
#else
M2C_UNK fn_800D5448();
#endif
extern u8 lbl_80381EB8[0x10];
extern u8 lbl_803E50C0[0x10];
extern s8 lbl_804CB630;
extern s32 lbl_804CB700;

void fn_800A3C48(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x6C) = (s32) lbl_804CB700;
    fn_800C9718();
    lbl_804CB630 = 0x63;
    fn_800D5448(lbl_803E50C0, arg0, 0);
    fn_80081050(lbl_80381EB8, arg0);
}
