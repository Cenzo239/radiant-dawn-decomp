#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80006A2C(void **);
#else
M2C_UNK fn_80006A2C();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CBDF8;
FE10_PROTO extern void *lbl_804CBDFC;
FE10_PROTO extern void *lbl_804CBE00;
FE10_PROTO extern void *lbl_804CBE04;
FE10_PROTO extern void *lbl_804CBE08;
#else
extern u8 lbl_804CBDF8[0x4];
extern u8 lbl_804CBDFC[0x4];
extern u8 lbl_804CBE00[0x4];
extern u8 lbl_804CBE04[0x4];
extern u8 lbl_804CBE08[0x4];
#endif
extern s32 lbl_804CBE0C;

void fn_801D607C(void) {
    s32 temp_r0;

    temp_r0 = lbl_804CBE0C - 1;
    lbl_804CBE0C = temp_r0;
    if (temp_r0 == 0) {
        fn_80006A2C(lbl_804CBDF8);
        fn_80006A2C(lbl_804CBDFC);
        fn_80006A2C(lbl_804CBE00);
        fn_80006A2C(lbl_804CBE04);
        fn_80006A2C(lbl_804CBE08);
    }
}
