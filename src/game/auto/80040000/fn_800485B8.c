#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800E85B8(void *, void*);
#else
void fn_800E85B8(int, void*);
#endif
extern u8 fn_80048548[0x70];
void fn_800485B8(int a) { fn_800E85B8(a, fn_80048548); }
