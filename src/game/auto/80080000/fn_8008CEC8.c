#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
#if TARGET_PC
FE10_PROTO unsigned char fn_801D09F0(void); FE10_PROTO void fn_8023F1A0(s8 *, int, ...); s8 * fn_8024BC94();
#else
FE10_PROTO unsigned char fn_801D09F0(void); void fn_8023F1A0(s32, int, void*); s8 * fn_8024BC94();
#endif
#else
s32 fn_801D09F0(); void fn_8023F1A0(s32, int, void*); s8 * fn_8024BC94();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_80381300[6][2];
#else
extern s32 lbl_80381300[6][2];
#endif
void fn_8008CEC8(void){ s32 i = fn_801D09F0(); fn_8023F1A0(lbl_80381300[*(s8*)(fn_8024BC94()+0x1BC8)][i], 0, lbl_80381300); }
