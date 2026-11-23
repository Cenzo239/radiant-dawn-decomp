/* Equipment bonus at item +0x2A, 80126934. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern int fn_80060828(void*, Unit*);
extern u8 lbl_803CAB38[];
extern void* lbl_804CA6D4;
static inline int EquipIdx(Unit* u) {
    Inv* it = u->inv;
    int i;
    for (i = 0; i < 7; i++) {
        if (it->item == 0) {
            break;
        }
        if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) {
            return (s8)i;
        }
        it++;
    }
    return -1;
}
#pragma use_lmw_stmw on
s8 fn_80126934(Unit* u) {
    Inv* base;
    int r;
    Inv* e;
    int i;
    r = 0;
    if (fn_8011B77C(u->skills, lbl_804CA6D4)) { r = 2; }
    r += (s8)fn_80060828(lbl_803CAB38, u);
    base = u->inv;
    {
        int idx = EquipIdx(u);
        if (idx < 0) { e = 0; } else { e = &u->inv[idx]; }
    }
    if (e) { r += (s8)e->item[0x2a]; }
    for (i = 0; i < 7; i++) {
        if (base == 0 || base->item == 0) break;
        u32 t = base->item ? base->item[0x12] : 0x13;
        if (t == 0xe) {
            if (base->equipped || (*(u32*)fn_801116B8(base) & 0x2000000)) {
                r += (s8)base->item[0x2a];
            }
        }
        base++;
    }
    if (r > 0x7f) r = 0x7f;
    if (r < -0x80) r = -0x80;
    return r;
}
}
