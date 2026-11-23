#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_8009DA7C(int, int);
FE10_PROTO int fn_800A05B0(int, int, int);
FE10_PROTO void * fn_800CFC50(void *, char, char, unsigned char, void *);
FE10_PROTO int fn_80129A8C(void *);
#else
s32 fn_8009DA7C();
s32 fn_800A05B0();
M2C_UNK fn_800CFC50();
u32 fn_80129A8C();
#endif
extern u8 lbl_803E7320[0x1208];

void fn_80172B18(s8 *arg0, s8 arg1, s8 arg2) {
    s32 temp_r31;
    s32 var_r0;

    if ((M2C_FIELD(arg0, u8 *, 8) & 2) && (fn_800A05B0(0xB, arg1, arg2) != 0)) {
        fn_800CFC50(lbl_803E7320, arg1, arg2, 0, 0xB);
    }
    if ((M2C_FIELD(arg0, u8 *, 8) & 1) && (fn_800A05B0(0xC, arg1, arg2) != 0)) {
        temp_r31 = M2C_FIELD(arg0, s32 *, 4);
        if (fn_8009DA7C(arg1, arg2) != 0) {
            var_r0 = (fn_80129A8C(temp_r31) >> 0x1FU) ^ 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            fn_800CFC50(lbl_803E7320, arg1, arg2, 0, 0xC);
        }
    }
}
