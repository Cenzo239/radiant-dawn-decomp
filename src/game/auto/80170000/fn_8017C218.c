#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80081050(void*, void *); FE10_PROTO void fn_8017ABE4(void *, u8);
#else
s32 fn_80081050(void*, int); void fn_8017ABE4(s32, u8);
#endif
extern u8 lbl_80387B68[0x20];
s32
#if TARGET_PC
*
#endif
fn_8017C218(
#if TARGET_PC
s32 a, void *b
#else
s32 a, s32 b
#endif
){
#if TARGET_PC
void *t; if (a < 0 || a >= 0xD) return 0; if (b == 0) b = (void *)3; t = fn_80081050(lbl_80387B68, b); fn_8017ABE4(t, (u8)a); return t;
#else
s32 t; if (a < 0 || a >= 0xD) return 0; if (b == 0) b = 3; t = fn_80081050(lbl_80387B68, b); fn_8017ABE4(t, (u8)a); return t;
#endif
}
