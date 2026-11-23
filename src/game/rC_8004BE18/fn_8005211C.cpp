#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on

/* The body is an inline taking the unit from a caller local: written in place,
 * the unit ranked below the lbl_803EC898 address temporary (r30/r31 swapped). */
#define m lbl_803EC898
static inline void body(MenuProc* p, Unit* u) {
    CursorRef* c;
    s8 x;
    s8 y;
    fn_80114B44(m, 9, 0);
    fn_80114888(m, 6);
    fn_801151BC(m, u);
    fn_8011567C(m, 0);
    fn_80115764(m, u->x102, u->y103, 200);
    fn_8013F1C4();
    c = p->cursor;
    p->saved = *c;
    if ((x = c->x) < 0 || (y = c->y) < 0 || ((s16*)(m + 0x710e))[x + (y << 6)] < 0) {
        x = u->x102;
        y = u->y103;
    }
    fn_800620A8(&lbl_803CAB38, x, y);
}

extern "C" void fn_8005211C(MenuProc* p) {
    Unit* u = lbl_803CA870.unit;
    body(p, u);
}

