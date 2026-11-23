#include "game/auto/m2c_prelude.h"
void fn_80006A2C(void *);
#if TARGET_PC
FE10_PROTO void fn_80079978(void *);
#else
M2C_UNK fn_80079978();
#endif

void fn_800CE1B4(s8 *arg0) {
    if ((s32) M2C_FIELD(arg0, s32 *, 0) != 0) {
        fn_80006A2C(arg0);
        if ((s32) M2C_FIELD(arg0, u8 *, 0x40) != 0) {
            fn_80079978(M2C_FIELD(arg0, s32 *, 0x3C));
            M2C_FIELD(arg0, s32 *, 0x3C) = 0;
        }
    }
}
