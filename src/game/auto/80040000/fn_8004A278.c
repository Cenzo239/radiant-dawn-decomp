#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_801039E8(void *, void *);
#else
M2C_UNK fn_801039E8();
#endif
struct S870 { s32 a; s32 b; u8 pad[0x128]; };
extern struct S870 lbl_803CA870;

void fn_8004A278(s32 arg0) {
    fn_801039E8(lbl_803CA870.a, arg0);
}

