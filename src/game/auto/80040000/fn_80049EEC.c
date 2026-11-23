#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800262D8(unsigned char *);
#else
M2C_UNK fn_800262D8();
#endif
#if TARGET_PC
FE10_PROTO void fn_80026C44(void *, void *, void *);
FE10_PROTO void fn_8002B2AC(void *, int, int);
FE10_PROTO void fn_8002C53C(void *, char);
FE10_PROTO void fn_8006C440(void *);
FE10_PROTO void fn_8006DE18(void *);
FE10_PROTO void * fn_80081194(void *, void *);
#else
M2C_UNK fn_80026C44();
M2C_UNK fn_8002B2AC();
M2C_UNK fn_8002C53C();
M2C_UNK fn_8006C440();
M2C_UNK fn_8006DE18();
M2C_UNK fn_80081194();
#endif
extern u8 lbl_8037AF80[0xd8];
extern u8 lbl_803C8E80[0x1648];
extern u8 lbl_803CA870[0x130];

void fn_80049EEC(s32 arg0, s32 arg1) {
    fn_80026C44(lbl_803C8E80, M2C_FIELD(lbl_803CA870, s32 *, 0), M2C_FIELD(lbl_803CA870, s32 *, 4));
    fn_8002C53C(lbl_803C8E80, (s8) M2C_FIELD(lbl_803CA870, u8 *, 0xE));
    fn_8002B2AC(lbl_803C8E80, 0xF, 0);
    fn_8006C440(lbl_803C8E80);
    fn_8006DE18(lbl_803C8E80);
    fn_800262D8(lbl_803C8E80 + 0xDE0);
    fn_80081194(lbl_8037AF80, arg1);
}

