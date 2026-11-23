#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80061808(void *, float, ...);
FE10_PROTO void * fn_8010B094(int);
#else
M2C_UNK fn_80061808();
s8 * fn_8010B094();
#endif

void fn_8006198C(s8 *arg0, f32 farg0) {
    f32 temp_f2;
    u8 temp_r0;

    temp_r0 = M2C_FIELD(fn_8010B094(M2C_FIELD(arg0, u8 *, 0x10)), u8 *, 0x89);
    switch ((s32) temp_r0) {                        /* irregular */
    case 0:
        fn_80061808(arg0, M2C_FIELD(arg0, f32 *, 0x24) + farg0);
        return;
    case 1:
        fn_80061808(arg0, M2C_FIELD(arg0, f32 *, 0x28) + farg0);
        return;
    case 2:
        fn_80061808(arg0, M2C_FIELD(arg0, f32 *, 0x2C) + farg0);
        return;
    case 3:
        fn_80061808(arg0, farg0 + (M2C_FIELD(arg0, f32 *, 0x28) + M2C_FIELD(arg0, f32 *, 0x2C)));
        return;
    case 4:
        temp_f2 = M2C_FIELD(arg0, f32 *, 0x24);
        fn_80061808(arg0, farg0 + (M2C_FIELD(arg0, f32 *, 0x2C) + (temp_f2 + M2C_FIELD(arg0, f32 *, 0x28))), temp_f2);
        return;
    }
}
