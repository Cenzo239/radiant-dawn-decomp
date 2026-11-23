#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_801507A0(void *, void *);
#else
void fn_801507A0(int, int);
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CC070;
#else
extern s32 lbl_804CC070;
#endif

void fn_80272F8C(
#if TARGET_PC
void *a
#else
int a
#endif
) {
    fn_801507A0(a, lbl_804CC070);
}
