#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s8 * fn_8024BC94();
#if TARGET_PC
FE10_PROTO extern void *lbl_8038C244[7];
#else
extern s32 lbl_8038C244[7];
#endif
s32
#if TARGET_PC
*
#endif
fn_801D5DC4(void){ return lbl_8038C244[*(s8*)(fn_8024BC94()+0x1BC8)]; }
