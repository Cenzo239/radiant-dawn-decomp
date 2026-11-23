#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800F3B50(void *, float, float);
FE10_PROTO void fn_800F4B94(void *, int);
#else
M2C_UNK fn_800F3B50();
M2C_UNK fn_800F4B94();
#endif
extern f32 lbl_804CDB50;

void fn_80100978(s8 *arg0) {
    if ((s32) M2C_FIELD(arg0, u8 *, 0x48) == 0) {
        fn_800F4B94(M2C_FIELD(arg0, s32 *, 0x30), -1);
    }
    fn_800F3B50(M2C_FIELD(arg0, s32 *, 0x30), lbl_804CDB50 + (f32) M2C_FIELD(arg0, s32 *, 0x40), lbl_804CDB50 + (f32) M2C_FIELD(arg0, s32 *, 0x44));
}
