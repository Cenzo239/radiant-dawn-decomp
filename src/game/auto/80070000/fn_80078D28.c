#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80077F98(void *, s32); void fn_8031DD44(void*); void fn_8031DE20(void*);
#else
s32 fn_80077F98(s32,s32); void fn_8031DD44(void*); void fn_8031DE20(void*);
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_803CD868[16]; extern u8 lbl_803CD8A8[0x38];
#else
extern s32 lbl_803CD868[16]; extern u8 lbl_803CD8A8[0x38];
#endif
s32
#if TARGET_PC
*
#endif
fn_80078D28(s32 a, s32 b){
#if TARGET_PC
u8 *t; fn_8031DD44(lbl_803CD8A8+4); t = fn_80077F98(lbl_803CD868[a], b); fn_8031DE20(lbl_803CD8A8+4); return t + 0x20;
#else
s32 t; fn_8031DD44(lbl_803CD8A8+4); t = fn_80077F98(lbl_803CD868[a], b); fn_8031DE20(lbl_803CD8A8+4); return t + 0x20;
#endif
}
