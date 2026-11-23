#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_8006074C(void *);
FE10_PROTO unsigned int fn_80068424(char **, int);
FE10_PROTO void fn_80252418(char *, float);
#else
s32 fn_8006074C();
s32 fn_80068424();
M2C_UNK fn_80252418();
#endif
extern u8 lbl_803CAB38[0x988];

void fn_80043DE8(s32 arg0) {
    fn_80252418(fn_80068424(fn_8006074C(lbl_803CAB38), M2C_FIELD(lbl_803CAB38, u8 *, 0x11)), (f32) arg0);
}
