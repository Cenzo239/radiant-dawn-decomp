#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800310E4(char *, unsigned char, int, unsigned int);
FE10_PROTO void * fn_801181E8(void *, char, char);
FE10_PROTO char * fn_80118C44(void *);
FE10_PROTO char * fn_8011D39C(void *);
#else
M2C_UNK fn_800310E4();
s32 fn_801181E8();
M2C_UNK fn_80118C44();
M2C_UNK fn_8011D39C(s32);
#endif
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803EC898[0x15867];

void fn_80044C64(void) {
    s32 temp_r3;

    if ((s8 *) M2C_FIELD(lbl_803CA870, s8 **, 4) != NULL) {
        fn_800310E4(fn_80118C44(M2C_FIELD(M2C_FIELD(lbl_803CA870, s8 **, 4), s32 *, 0xEC)), 0, 0x28, 0);
        return;
    }
    temp_r3 = fn_801181E8(lbl_803EC898, (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x13), (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x14));
    if (temp_r3 != 0) {
        fn_800310E4(fn_8011D39C(temp_r3), 0, 0x28, 0);
    }
}
