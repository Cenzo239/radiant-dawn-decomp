#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800893C4(void *);
FE10_PROTO void * fn_800D4228(char *);
#else
void fn_800893C4(s32);
s32 fn_800D4228(s32);
#endif
void fn_801E5880(void*);
void fn_802889AC(void*);
void fn_801D31DC(u8 *arg0) {
    s32 v;
    fn_800893C4(*(s32*)(arg0 + 0x4C));
    v = *(s32*)(arg0 + 0x40);
    if (v != 0) {
        v = fn_800D4228(v);
        fn_800893C4(v);
    }
    fn_801E5880(arg0);
    fn_802889AC(arg0);
}
