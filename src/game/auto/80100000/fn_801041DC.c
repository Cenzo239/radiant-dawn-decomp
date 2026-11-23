#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800F3F14(void *, float);
#else
M2C_UNK fn_800F3F14();
#endif
#if TARGET_PC
FE10_PROTO void fn_80102928(void *, s32, s32, s32, void *);
#else
void fn_80102928(s32, s32, s32, s32, s32);
#endif
extern f32 lbl_804CDB4C;
extern f32 lbl_804CDB94;

void fn_801041DC(s8 *arg0) {
    s32 t = M2C_FIELD(arg0, s8 *, 0x6A);
    fn_80102928(M2C_FIELD(arg0, s32 *, 0x30), t, 8, 0, 0);
    if ((s32) M2C_FIELD(arg0, u8 *, 0x6C) != 0) {
        fn_800F3F14(M2C_FIELD(arg0, s32 *, 0x30), lbl_804CDB94);
        return;
    }
    fn_800F3F14(M2C_FIELD(arg0, s32 *, 0x30), lbl_804CDB4C);
}

