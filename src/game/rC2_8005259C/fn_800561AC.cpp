#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_800561AC(void) {
    u8* b = fn_800CFB0C(fn_800CFD3C(&lbl_803E7320));
    fn_8002BCC4(&lbl_803C8E80);
    fn_80102928(b, -1, 0x10, 0, 0);
}

extern "C" void fn_80056208(void) {
    Unit* u = lbl_803CA870.unit;
    fn_800620A8(&lbl_803CAB38, u->x102, u->y103);
}

extern "C" void fn_80056278(void) {
}

extern "C" void fn_8005627C(void* parent) {
    fn_80081194(lbl_8037E048, parent);
}

typedef struct UnitCtx4 {
    u32 f0;
    Unit2* u;
} UnitCtx4;
extern "C" void fn_8005628C(UnitCtx4* c, Unit2* b) {
    Unit2* a = c->u;
    if (b->f4->b8 == a->f4->b8 && b->pers->wdc) {
        if (fn_8012E944(b, a->pers) >= 0) {
            fn_8012E944(c->u, b->pers);
            if (c->u->f8 != b) {
                fn_8011996C(c->u, b, 1);
            } else {
                fn_8011996C(c->u, b, 2);
            }
        }
    }
}
