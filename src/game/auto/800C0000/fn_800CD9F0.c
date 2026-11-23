#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800620A8(void *, float, float);
FE10_PROTO void fn_80062380(char *, char *);
FE10_PROTO void fn_80062454(void *);
FE10_PROTO void * fn_80083B84(void *);
#else
M2C_UNK fn_800620A8();
M2C_UNK fn_80062380();
M2C_UNK fn_80062454();
s8 * fn_80083B84();
#endif
M2C_UNK fn_8012D620();
M2C_UNK fn_8012D908();
M2C_UNK fn_8012FF30();
extern u8 lbl_803832E0[0x680];
extern u8 lbl_803CAB38[0x988];

void fn_800CD9F0(void) {
    s8 *t;
    fn_80062380(lbl_803CAB38, lbl_803CAB38 + 0x914);
    fn_80062454(lbl_803CAB38);
    fn_8012D620();
    fn_8012D908();
    fn_800620A8(lbl_803CAB38, (f32) (s8) M2C_FIELD(lbl_803CAB38, u8 *, 0x9A), (f32) (s8) M2C_FIELD(lbl_803CAB38, u8 *, 0x9B));
    fn_8012FF30();
    t = fn_80083B84(lbl_803832E0);
    M2C_FIELD(t, s32 *, 0x60) = 0xD;
}

