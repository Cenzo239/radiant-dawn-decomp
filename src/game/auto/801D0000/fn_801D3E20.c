#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80068C08();
#if TARGET_PC
FE10_PROTO void fn_80081A90(void *);
FE10_PROTO void * fn_80083B84(void *);
#else
M2C_UNK fn_80081A90();
s32 fn_80083B84();
#endif
extern u8 lbl_8038B160[0x508];

void fn_801D3E20(void) {
    s32 temp_r3;

    temp_r3 = fn_80083B84(lbl_8038B160);
    if (temp_r3 != 0) {
        fn_80068C08();
        fn_80081A90(temp_r3);
    }
}
