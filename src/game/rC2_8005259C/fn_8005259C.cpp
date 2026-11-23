#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8005259C(Cmd0* c) {
    lbl_803CA870.i18 = (u8)c->v58();
    fn_800310E4(c->vC(), 0, 0x28, 0);
    return 6;
}
