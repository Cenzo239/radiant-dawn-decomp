#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_801A2224(void*);
void* fn_80083B84(void*);
void fn_80083DC4(void*, int);
extern u8 lbl_8038B160[0x508];
extern u8 lbl_8041EB20[0x128];
s32 fn_801D56F0(void) {
    if (fn_801A2224(lbl_8041EB20) != 0) {
        return 0x40;
    }
    fn_80083DC4(fn_80083B84(lbl_8038B160), 0x18);
    return 8;
}
