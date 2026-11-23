#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char);
FE10_PROTO void * fn_800D4188(char *, void *);
#else
M2C_UNK fn_800453B4();
M2C_UNK fn_800D4188();
#endif
extern u8 lbl_80366184[0xb4];
extern u8 lbl_803CA870[0x130];

void fn_800CD888(s32 arg0) {
    fn_800453B4(lbl_803CA870, 0);
    fn_800D4188(lbl_80366184, arg0);
}
