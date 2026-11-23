#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800F39DC(void *);
FE10_PROTO void fn_80114D00(void *);
FE10_PROTO void fn_80126EB0(void *, char, char);
#else
M2C_UNK fn_800F39DC();
M2C_UNK fn_80114D00();
M2C_UNK fn_80126EB0();
#endif
extern u8 lbl_803EC898[0x15867];

void fn_80045548(s8 *arg0) {
    fn_80126EB0(M2C_FIELD(arg0, s32 *, 0), (s8) M2C_FIELD(arg0, u8 *, 0xF), (s8) M2C_FIELD(arg0, u8 *, 0x10));
    fn_800F39DC(M2C_FIELD(arg0, s32 *, 0));
    fn_80114D00(lbl_803EC898);
}
