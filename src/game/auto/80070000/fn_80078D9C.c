#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80077F98(void *, s32);
#else
s32 fn_80077F98(s32, s32);
#endif
s32 fn_8023FBF4();
#if TARGET_PC
FE10_PROTO void fn_8031DD44(void *);
FE10_PROTO void fn_8031DE20(void *);
#else
M2C_UNK fn_8031DD44();
M2C_UNK fn_8031DE20();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_803CD868[16];
#else
extern u8 lbl_803CD868[0x40];
#endif
extern u8 lbl_803CD8A8[0x38];

s32
#if TARGET_PC
*
#endif
fn_80078D9C(s32 arg0) {
#if TARGET_PC
    u8 *temp_r31;
#else
    s32 temp_r31;
#endif
    s32 temp_r31_2;

    fn_8031DD44(lbl_803CD8A8 + 4);
    temp_r31_2 = fn_8023FBF4();
    fn_8031DD44(lbl_803CD8A8 + 4);
#if TARGET_PC
    temp_r31 = fn_80077F98(lbl_803CD868[temp_r31_2], arg0);
#else
    temp_r31 = fn_80077F98(*(s32*)(lbl_803CD868 + (temp_r31_2 * 4)), arg0);
#endif
    fn_8031DE20(lbl_803CD8A8 + 4);
    fn_8031DE20(lbl_803CD8A8 + 4);
    return temp_r31 + 0x20;
}

