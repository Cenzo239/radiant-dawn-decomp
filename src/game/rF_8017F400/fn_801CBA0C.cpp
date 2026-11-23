#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* kills the map object processes; lbl_8038ACF8: pooled file statics, the classes themselves are not reproduced here */
extern void fn_800846BC(void*);
static u8 c0[0x40], c1[0x28], c2[0x48], c3[0x28], c4[0x28];
void fn_801CBA0C(void) {
    fn_800846BC(c2);
    fn_800846BC(c3);
    fn_800846BC(c4);
    fn_800846BC(c1);
    fn_800846BC(c0);
}
}
