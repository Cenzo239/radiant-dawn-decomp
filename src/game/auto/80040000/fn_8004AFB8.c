#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083DC4(void *, int);
#else
M2C_UNK fn_80083DC4();
#endif
M2C_UNK fn_8011A36C();
#if TARGET_PC
FE10_PROTO unsigned char fn_8011AB30(void *);
FE10_PROTO int fn_8011B8A4(void *);
FE10_PROTO unsigned int fn_80127A90(void *);
#else
u8 fn_8011AB30();
s32 fn_8011B8A4();
s32 fn_80127A90();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB3E0;
#else
extern s32 lbl_804CB3E0;
#endif

void fn_8004AFB8(s32 arg0) {
    s32 temp_r30;
    s32 temp_r31;

    temp_r30 = lbl_804CB3E0;
    if (fn_8011AB30(temp_r30 + 0x12C) <= 6U) {
        temp_r31 = fn_80127A90(temp_r30);
        if ((temp_r31 - fn_8011B8A4(temp_r30 + 0x12C)) >= 0) {
            fn_8011A36C(temp_r30 + 0x12C);
            return;
        }
    }
    fn_80083DC4(arg0, 0xA);
}
