#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s8 * fn_800E45B0(int);
void fn_800E4B20(s8*, int);
void fn_801CDA9C(void){ s8 *r = fn_800E45B0(3); if (r != NULL) { fn_800E4B20(r, -1); *(s16*)(*(s8**)(r+0x30)+4) = 0; } }
