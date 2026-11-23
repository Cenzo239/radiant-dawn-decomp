#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
void* fn_8024BC94(); FE10_PROTO void fn_80245368(void*, char *);
#else
void* fn_8024BC94(); void fn_80245368(void*, s32);
#endif
void fn_8009AC94(s32 a){ fn_80245368(fn_8024BC94(), a); }
