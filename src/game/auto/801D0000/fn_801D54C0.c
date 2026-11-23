#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_801DDDE8(void);
void* fn_80083B84(void*);
u8* fn_801E5640(void*, int, int);
extern u8 lbl_8038B160[0x508];
extern u8 lbl_8038BDBC[0x13];
void fn_801D54C0(void) {
    u8 *t;
    fn_801DDDE8();
    t = fn_801E5640(fn_80083B84(lbl_8038B160), -0x1000, 0);
    if (t != NULL) {
        *(void**)(t + 0x64) = lbl_8038BDBC;
    }
}
