#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80060754(void *);
FE10_PROTO char * fn_800D0864(char *);
#else
s32 fn_80060754();
M2C_UNK fn_800D0864();
#endif
extern u8 lbl_8037D2AC[0xd];
extern u8 lbl_8037D2BC[0xd];
extern u8 lbl_803CAB38[0x988];

void fn_8004B464(void) {
    if (fn_80060754(lbl_803CAB38) != 0) {
        fn_800D0864(lbl_8037D2BC);
        return;
    }
    fn_800D0864(lbl_8037D2AC);
}
