#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class V { public:
 virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5();
 virtual int s6(); virtual int s7(); virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); };
extern "C" {
#if TARGET_PC
FE10_PROTO s8 * fn_80081194(void *, p32arg);
#else
s8 * fn_80081194(void *, s32);
#endif
void fn_801E4094(s8 *);
void fn_801E5448(s8 *, V *);
extern u8 lbl_8038DDC0[0x38];
void fn_801FE520(V *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s8 *temp_r3;
    if (arg2 != arg0->s11()) {
        temp_r3 = fn_80081194(lbl_8038DDC0, arg1);
        if (temp_r3 != NULL) {
            fn_801E4094(temp_r3);
        }
        fn_801E5448(temp_r3, arg0);
        M2C_FIELD(arg0, s8 *, 0x50) = 1;
        M2C_FIELD(temp_r3, s16 *, 0x42) = 4;
        M2C_FIELD(temp_r3, s32 *, 0x44) = arg2;
        M2C_FIELD(temp_r3, s32 *, 0x48) = arg3;
    }
}
}
