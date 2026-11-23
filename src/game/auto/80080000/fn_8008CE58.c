#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO unsigned char fn_801D09F0(void);
#else
s32 fn_801D09F0();
#endif
#if TARGET_PC
FE10_PROTO s32 fn_8023F880(void *, ...);
#else
s32 fn_8023F880(s32, void*);
#endif
u8* fn_8024BC94();
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
#else
void fn_80083B78(s32);
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_80381300[6][2];
#else
extern u8 lbl_80381300[0x30];
#endif
void fn_8008CE58(s32 arg0) {
    s32 t = fn_801D09F0();
#if TARGET_PC
    if (fn_8023F880(lbl_80381300[(s8) fn_8024BC94()[0x1BC8]][t], lbl_80381300) != 0) {
        fn_80083B78(arg0);
    }
#else
    if (fn_8023F880(*(s32*)((t * 4) + (lbl_80381300 + ((s8) fn_8024BC94()[0x1BC8] * 8))), lbl_80381300) != 0) {
        fn_80083B78(arg0);
    }
#endif
}
