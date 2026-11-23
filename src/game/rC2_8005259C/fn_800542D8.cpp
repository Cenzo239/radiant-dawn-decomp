#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

typedef struct UnitVisitor {
    void* vt;
    Unit2* u;
} UnitVisitor;
extern "C" int fn_800542D8(void) {
    UnitVisitor v;
    Unit2* u;
    v.vt = lbl_8037E0F8;
    u = *(Unit2**)(lbl_804CB814 + lbl_803CAB38.b11 * 0xc);
    while (u) {
        if (u->pers->wdc) {
            v.u = u;
            if (!((u32)u->flags108 & 4)) {
                fn_800392FC(&v, u->x102, u->y103);
            }
            fn_80039990(&v, u);
        }
        u = u->next;
    }
    return 0;
}
