#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80062A9C(void *, unsigned int);
#else
s8 * fn_80062A9C();
#endif
extern u8 lbl_803CAB38[0x988];
s32 fn_80106ECC(u8 *a){ s8 *r = fn_80062A9C(lbl_803CAB38, *a); if (r == NULL) return -1; return *(u8*)(r+6); }
