#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80081050(void *, void *);
FE10_PROTO void * fn_8008580C(void *, void *);
#else
s8 * fn_80081050();
s32 fn_8008580C();
#endif
extern u8 lbl_80387A58[0x20];

void
#if TARGET_PC
*
#endif
fn_801773BC(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    s8 *t;
#if TARGET_PC
    t = fn_8008580C(lbl_80387A58, arg0);
    if (t == 0) {
        t = fn_80081050(lbl_80387A58, arg0);
        M2C_FIELD(t, s32 *, 0x30) = 0;
    }
    return t;
#else
    if (fn_8008580C(lbl_80387A58, arg0) == 0) {
        t = fn_80081050(lbl_80387A58, arg0);
        M2C_FIELD(t, s32 *, 0x30) = 0;
    }
#endif
}

