#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80035218(int, int, char *, char *, char *);
FE10_PROTO void fn_8006A240(void *, void *);
#else
M2C_UNK fn_80035218();
M2C_UNK fn_8006A240(s32, s32);
#endif
extern u8 lbl_804CA0D0[0x7];
extern u8 lbl_804CA0D8[0x7];
extern u8 lbl_804CA0E0[0x7];

void fn_8004B2A8(s32 arg0, s32 arg1) {
    fn_8006A240(arg0, arg1);
    fn_80035218(0x138, 0xA0, lbl_804CA0E0, lbl_804CA0D8, lbl_804CA0D0);
}
