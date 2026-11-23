#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800A05B0(int, int, int);
FE10_PROTO void * fn_800CFC50(void *, char, char, unsigned char, void *);
#else
s32 fn_800A05B0();
M2C_UNK fn_800CFC50();
#endif
extern u8 lbl_803E7320[0x1208];

void fn_80172DF4(s8 *arg0, s8 arg1, s8 arg2) {
    if (fn_800A05B0((u8) M2C_FIELD(arg0, s32 *, 4), arg1, arg2) != 0) {
        fn_800CFC50(lbl_803E7320, arg1, arg2, 0, M2C_FIELD(arg0, s32 *, 4));
    }
}
