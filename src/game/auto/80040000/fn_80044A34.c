#include "game/auto/m2c_prelude.h"
s32 fn_8007857C();
#if TARGET_PC
FE10_PROTO int fn_800785FC(char *, unsigned int, ...);
#else
M2C_UNK fn_800785FC();
#endif
M2C_UNK fn_800787E4();
#if TARGET_PC
FE10_PROTO void * fn_80081194(void *, void *);
#else
M2C_UNK fn_80081194();
#endif
extern u8 lbl_80361684[0xbc];

void fn_80044A34(s8 *arg0) {
    fn_800787E4();
    fn_800785FC(lbl_80361684 + 0xA6, fn_8007857C(), lbl_80361684);
    fn_80081194(M2C_FIELD(arg0, s32 *, 0x54), arg0);
}
