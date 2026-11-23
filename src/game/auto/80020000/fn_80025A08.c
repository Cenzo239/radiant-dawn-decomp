#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char);
FE10_PROTO int fn_8004A70C(char *, ...);
FE10_PROTO void * fn_800D5448(void *, void *, int);
#else
M2C_UNK fn_800453B4();
s32 fn_8004A70C();
M2C_UNK fn_800D5448();
#endif
extern u8 lbl_80361260[0xa8];
extern u8 lbl_803CA870[0x130];
extern u8 lbl_804CB160[0x8];

s32 fn_80025A08(s32 arg0) {
    if (fn_8004A70C(lbl_80361260 + 0x91, lbl_80361260) != 0) {
        return 0;
    }
    fn_800453B4(lbl_803CA870, 0);
    fn_800D5448(lbl_804CB160, arg0, 0);
    return 1;
}
