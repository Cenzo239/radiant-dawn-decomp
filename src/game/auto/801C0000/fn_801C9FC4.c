#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80006E94(void *);
FE10_PROTO void fn_80006F20(void *);
FE10_PROTO void fn_80007ABC(void *, int);
FE10_PROTO void fn_80008F6C(void *, void *);
FE10_PROTO void * fn_8000EB68(void *);
FE10_PROTO void * fn_80017F10(void *);
#else
M2C_UNK fn_80006E94();
M2C_UNK fn_80006F20();
M2C_UNK fn_80007ABC();
M2C_UNK fn_80008F6C();
s32 fn_8000EB68(s32);
s32 fn_80017F10(s32);
#endif
#if TARGET_PC
FE10_PROTO int * fn_8001D3B4(char *);
#else
s32 fn_8001D3B4(s32);
#endif
#if TARGET_PC
FE10_PROTO unsigned char fn_80109A18(unsigned char **);
FE10_PROTO unsigned short fn_80109A2C(unsigned char **);
FE10_PROTO unsigned int fn_80109A50(unsigned char **);
FE10_PROTO unsigned int fn_80109A88(unsigned char **);
FE10_PROTO float fn_80109AD0(unsigned char **);
FE10_PROTO int * fn_8017F37C(char *, char *, char *);
#else
s8 fn_80109A18();
M2C_UNK fn_80109A2C();
s32 fn_80109A50();
s8 * fn_80109A88();
f32 fn_80109AD0();
s32 fn_8017F37C();
#endif
#if TARGET_PC
FE10_PROTO s32 fn_8023F838(char *);
#else
s32 fn_8023F838(s32);
#endif
extern u8 lbl_8036E9AC[0x3c];

s32
#if TARGET_PC
*
#endif
fn_801C9FC4(
#if TARGET_PC
s8 *arg0, u8 *arg1, s8 *arg2
#else
s8 *arg0, s32 arg1, s32 arg2
#endif
) {
#if TARGET_PC
    u8 *sp8;
#else
    s32 sp8;
#endif
    s8 *temp_r30;
    s8 *temp_r3;

    sp8 = arg1;
    M2C_FIELD(arg0, f32 *, 0xA0) = fn_80109AD0(&sp8);
    M2C_FIELD(arg0, f32 *, 0xA4) = fn_80109AD0(&sp8);
    M2C_FIELD(arg0, f32 *, 0xA8) = fn_80109AD0(&sp8);
    M2C_FIELD(arg0, f32 *, 0xAC) = fn_80109AD0(&sp8);
    M2C_FIELD(arg0, f32 *, 0xB0) = fn_80109AD0(&sp8);
    M2C_FIELD(arg0, f32 *, 0xB4) = fn_80109AD0(&sp8);
    M2C_FIELD(arg0, s32 *, 0xB8) = fn_80109A50(&sp8);
    temp_r3 = fn_80109A88(&sp8);
    M2C_FIELD(arg0, s8 **, 0) = temp_r3;
    M2C_FIELD(arg0, s8 *, 0xBC) = fn_80109A18(&sp8);
    M2C_FIELD(arg0, s8 *, 0xBD) = fn_80109A18(&sp8);
    fn_80109A2C(&sp8);
    temp_r30 = arg0 + 4;
    fn_80006E94(temp_r30);
    M2C_FIELD(temp_r30, s32 *, 0x40) = fn_8000EB68(fn_8017F37C(arg2, temp_r3, lbl_8036E9AC));
    M2C_FIELD(temp_r30, s32 *, 0x48) = fn_80017F10(fn_8017F37C(arg2, temp_r3, lbl_8036E9AC + 3));
    if (fn_8023F838(fn_8017F37C(arg2, lbl_8036E9AC + 7, lbl_8036E9AC + 0xF)) != 0) {
        M2C_FIELD(temp_r30, s32 *, 0x4C) = fn_8001D3B4(fn_8017F37C(arg2, lbl_8036E9AC + 7, lbl_8036E9AC + 0xF));
    }
    if (M2C_FIELD(arg0, s32 *, 0xB8) & 0x200) {
        fn_80008F6C(temp_r30, fn_8017F37C(arg2, temp_r3, lbl_8036E9AC + 0x14));
    }
    fn_80006F20(temp_r30);
    fn_80007ABC(temp_r30, 1);
    return sp8;
}
