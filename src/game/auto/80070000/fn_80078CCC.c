#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80077F98(void *, int);
#else
s32 fn_80077F98();
#endif
#if TARGET_PC
FE10_PROTO void fn_8031DD44(void *);
FE10_PROTO void fn_8031DE20(void *);
#else
M2C_UNK fn_8031DD44();
M2C_UNK fn_8031DE20();
#endif
extern u8 lbl_803CD8A8[0x38];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB5B0;
#else
extern s32 lbl_804CB5B0;
#endif

s32
#if TARGET_PC
*
#endif
fn_80078CCC(s32 arg0) {
#if TARGET_PC
    u8 *temp_r31;
#else
    s32 temp_r31;
#endif

    fn_8031DD44(lbl_803CD8A8 + 4);
    temp_r31 = fn_80077F98(lbl_804CB5B0, arg0);
    fn_8031DE20(lbl_803CD8A8 + 4);
    return temp_r31 + 0x20;
}
