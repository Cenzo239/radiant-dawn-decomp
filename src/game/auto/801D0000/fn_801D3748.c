#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
#else
M2C_UNK fn_80083B78();
#endif
void fn_80083DC4(s8*, int);
#if TARGET_PC
FE10_PROTO void fn_800893AC(void *);
FE10_PROTO void * fn_801E5640(void *, int, int);
#else
M2C_UNK fn_800893AC();
s8 * fn_801E5640();
#endif
extern u8 lbl_8038C17C[0x13];
extern u8 lbl_803CA870[0x130];

void fn_801D3748(s8 *arg0) {
    s8 *temp_r3;

    switch ((s32) M2C_FIELD(lbl_803CA870, u8 *, 0xC)) { /* irregular */
    case 0x81:
        fn_80083DC4(arg0, 0x19);
        return;
    case 0x80:
        fn_800893AC(M2C_FIELD(arg0, s32 *, 0x4C));
        temp_r3 = fn_801E5640(arg0, -0x1000, 0);
        if (temp_r3 != NULL) {
            M2C_FIELD(temp_r3, M2C_UNK **, 0x64) = lbl_8038C17C;
        }
        fn_80083B78(arg0);
        return;
    }
}

