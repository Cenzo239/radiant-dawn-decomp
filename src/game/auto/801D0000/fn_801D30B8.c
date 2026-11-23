#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800893C4(void *); FE10_PROTO void * fn_800D4228(char *); void fn_801E5880(s8*);
#else
void fn_800893C4(s32); s32 fn_800D4228(s32); void fn_801E5880(s8*);
#endif
void fn_801D30B8(s8 *p){ s32 t; fn_800893C4(*(s32*)(p+0x4C)); t = *(s32*)(p+0x40); if (t != 0) { fn_800893C4(fn_800D4228(t)); } fn_801E5880(p); }
