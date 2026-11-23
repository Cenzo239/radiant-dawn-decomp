#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO char * fn_800D0AE4(int, int, ...);
FE10_PROTO int fn_80111074(char *, ...);
FE10_PROTO void fn_8014C2AC(void *);
#else
M2C_UNK fn_80083B78();
M2C_UNK fn_800D0AE4();
s32 fn_80111074();
M2C_UNK fn_8014C2AC();
#endif

void fn_80208A04(s8 *arg0) {
    f32 temp_f1;
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, s8 **, 0x58);
    temp_f1 = (f32) fn_80111074(M2C_FIELD(temp_r4, s32 *, 0x44), temp_r4);
    fn_800D0AE4(0, (s32) (M2C_FIELD(arg0, f32 *, 0x60) * temp_f1), temp_f1);
    fn_8014C2AC(M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x64), s32 *, 0x20));
    fn_80083B78(arg0);
}
