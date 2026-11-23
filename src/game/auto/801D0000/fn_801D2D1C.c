#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800893C4(void *);
FE10_PROTO void * fn_800D4228(char *);
FE10_PROTO void fn_8019F85C(void *, ...);
FE10_PROTO void fn_801E5880(void *);
#else
M2C_UNK fn_800893C4();
M2C_UNK fn_800D4228();
M2C_UNK fn_8019F85C();
M2C_UNK fn_801E5880();
#endif
extern u8 lbl_803CAB38[0x988];

void fn_801D2D1C(s8 *arg0) {
    fn_800893C4(M2C_FIELD(arg0, s32 *, 0x4C));
    if (M2C_FIELD(arg0, s32 *, 0x40) != 0) {
        fn_800893C4(fn_800D4228(M2C_FIELD(arg0, s32 *, 0x40)));
    }
    fn_801E5880(arg0);
    M2C_FIELD(lbl_803CAB38, s8 *, 0x9C) = 1;
    fn_8019F85C(arg0, lbl_803CAB38);
}

