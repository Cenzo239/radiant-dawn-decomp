#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO void fn_800893D4(void *);
FE10_PROTO void fn_800D3D00(void *, unsigned char, float);
FE10_PROTO void * fn_800D4188(char *, void *);
FE10_PROTO void * fn_800D4228(char *);
FE10_PROTO void fn_800D42A0(char *);
FE10_PROTO void fn_801E5890(void *);
#else
M2C_UNK fn_80083B78();
M2C_UNK fn_800893D4(s32);
M2C_UNK fn_800D3D00();
s8 * fn_800D4188();
s32 fn_800D4228();
M2C_UNK fn_800D42A0();
M2C_UNK fn_801E5890();
#endif
extern u8 lbl_8036EA88[0x10];
extern f32 lbl_804CF780;
extern f32 lbl_804CF784;

void fn_801D2C5C(s8 *arg0) {
    M2C_UNK *temp_r31;
    M2C_UNK *t;
    s8 *temp_r31_2;
    s32 temp_r3;

    fn_800893D4(M2C_FIELD(arg0, s32 *, 0x4C));
    t = M2C_FIELD(arg0, M2C_UNK **, 0x40);
    if (t != NULL) {
        temp_r3 = fn_800D4228(t);
        if (temp_r3 == 0) {
            temp_r31 = M2C_FIELD(arg0, M2C_UNK **, 0x40);
            if (temp_r31 != NULL) {
                fn_800D42A0(temp_r31);
            }
            if (temp_r31 != NULL) {
                M2C_FIELD(arg0, M2C_UNK **, 0x40) = temp_r31;
                fn_800D3D00(temp_r31_2 = fn_800D4188(temp_r31, arg0), 2, lbl_804CF780);
                fn_800D3D00(fn_800D4188(lbl_8036EA88, temp_r31_2), 2, lbl_804CF784);
            }
        } else {
            fn_800893D4(temp_r3);
        }
    }
    fn_801E5890(arg0);
    fn_80083B78(arg0);
}

