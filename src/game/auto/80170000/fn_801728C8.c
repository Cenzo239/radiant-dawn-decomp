#include "game/auto/m2c_prelude.h"
s32 fn_8009FF74();
#if TARGET_PC
FE10_PROTO void * fn_800CFC50(void *, char, char, unsigned char, void *);
FE10_PROTO s32 fn_8011EF14(void *, void *);
#else
M2C_UNK fn_800CFC50();
s32 fn_8011EF14(s32, void *);
#endif
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803E7320[0x1208];

void fn_801728C8(s8 *arg0, s8 *arg1) {
    if (fn_8011EF14(M2C_FIELD(arg0, s32 *, 4), arg1) != 0) {
        M2C_FIELD(lbl_803CA870, s8 **, 4) = arg1;
        if (fn_8009FF74(lbl_803CA870) != 0) {
            fn_800CFC50(lbl_803E7320, (s8) M2C_FIELD(arg1, u8 *, 0x102), (s8) M2C_FIELD(arg1, u8 *, 0x103), M2C_FIELD(arg1, u8 *, 0xFC), 0);
        }
    }
}
