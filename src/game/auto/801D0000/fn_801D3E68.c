#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
FE10_PROTO void fn_800893C4(void *);
FE10_PROTO void * fn_800D4228(char *);
#else
s8 * fn_80083B84();
M2C_UNK fn_800893C4(M2C_UNK);
M2C_UNK fn_800D4228();
#endif
M2C_UNK fn_801E5860();
M2C_UNK fn_801FBEB0();
#if TARGET_PC
FE10_PROTO void fn_80250E38(char, float, float);
#else
M2C_UNK fn_80250E38();
#endif
extern u8 lbl_8038B160[0x508];
extern f32 lbl_804CF798;
extern f32 lbl_804CF7A4;

void fn_801D3E68(void) {
    s8 *temp_r3;

    temp_r3 = fn_80083B84(lbl_8038B160);
    if (temp_r3 != NULL) {
        fn_801FBEB0();
        if (M2C_FIELD(temp_r3, s32 *, 0x40) != 0) {
            fn_800893C4(fn_800D4228(M2C_FIELD(temp_r3, s32 *, 0x40)));
        }
        fn_801E5860();
    }
    fn_80250E38(6, lbl_804CF798, lbl_804CF7A4);
}

