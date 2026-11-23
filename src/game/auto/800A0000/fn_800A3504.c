#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void* fn_80060728(void*);
void fn_801097FC(void*);
extern u8 lbl_803CAB38[0x988];
void fn_800A3504(int arg0) {
    u8 v = (u8)arg0;
    ((u8*)fn_80060728(lbl_803CAB38))[0xE] = v;
    fn_801097FC(fn_80060728(lbl_803CAB38));
}
