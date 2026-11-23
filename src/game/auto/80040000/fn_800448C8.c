#include "game/auto/m2c_prelude.h"
s32 fn_8007857C();
#if TARGET_PC
FE10_PROTO int fn_800785FC(char *, unsigned int);
FE10_PROTO void fn_80078C2C(char *);
#else
M2C_UNK fn_800785FC();
M2C_UNK fn_80078C2C();
#endif
M2C_UNK fn_8012D58C();
extern u8 lbl_80361684[0xbc];

void fn_800448C8(void) {
    fn_800785FC(lbl_80361684 + 0x8B, fn_8007857C());
    fn_80078C2C(lbl_80361684 + 0x59);
    fn_8012D58C();
}
