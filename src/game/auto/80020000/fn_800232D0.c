#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int * fn_801D5DC4(void);
FE10_PROTO void fn_8023F1A0(char *, int);
#else
int fn_801D5DC4();
void fn_8023F1A0(int, int);
#endif
void fn_801D5EC8();
void fn_800232D0(void) {
    fn_8023F1A0(fn_801D5DC4(), 0x80);
    fn_801D5EC8();
}
