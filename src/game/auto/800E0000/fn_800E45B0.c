#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_800893E4(void*, void*, void*); extern u8 fn_800E4594[0x1c]; extern u8 lbl_80384278[0x50];
#else
s32 fn_800893E4(void*, void*, void*); extern u8 fn_800E4594[0x1c]; extern u8 lbl_80384278[0x50];
#endif
s32
#if TARGET_PC
*
#endif
fn_800E45B0(s32 a){ u16 sp8 = a; if ((u16)a == 0) return 0; return fn_800893E4(lbl_80384278, fn_800E4594, &sp8); }
