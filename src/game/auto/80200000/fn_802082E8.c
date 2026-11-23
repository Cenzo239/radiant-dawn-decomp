#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083DC4(void *, int);
FE10_PROTO void fn_8014C2AC(void *);
FE10_PROTO void * fn_801E5640(void *, int, int, ...);
#else
M2C_UNK fn_80083DC4();
M2C_UNK fn_8014C2AC();
s8 * fn_801E5640();
#endif
extern u8 lbl_803CA870[0x130];

void fn_802082E8(s8 *arg0) {
    s32 temp_r31;
    s8 *temp_r3;
    s8 *temp_r6;

    switch ((s32) M2C_FIELD(lbl_803CA870, u8 *, 0xC)) { /* irregular */
    case 0x81:
        fn_8014C2AC(M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x64), s32 *, 0x28));
        return;
    case 0x80:
        fn_8014C2AC(M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x64), s32 *, 0x14));
        temp_r6 = M2C_FIELD(arg0, s8 **, 0x64);
        temp_r31 = M2C_FIELD(temp_r6, s32 *, 0x64);
        temp_r3 = fn_801E5640(arg0, -0x1000, 0, temp_r6);
        if (temp_r3 != NULL) {
            M2C_FIELD(temp_r3, s32 *, 0x64) = temp_r31;
        }
        fn_80083DC4(arg0, 8);
        return;
    }
}
