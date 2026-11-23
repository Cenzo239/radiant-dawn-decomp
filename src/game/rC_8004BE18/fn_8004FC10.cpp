#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on

/* The two tile coordinates go through s8 accessors: read directly they took
 * r26/r27 with the unit in r28 instead of r27/r28 with the unit in r26. */
static inline s8 rb0(MapThing* r) { return r->b0; }
static inline s8 rb1(MapThing* r) { return r->b1; }

extern "C" int fn_8004FC10(void) {
    Unit* u;
    u8 v1;
    MapThing* r;
    s8 b1;
    s8 b0;
    ItemData* x;
    u8 v2;
    fn_80114B44(lbl_803EC898, 6, -1);
    fn_80114B44(lbl_803EC898, 9, 0);
    fn_80114888(lbl_803EC898, 7);
    r = fn_80066130(lbl_803CB770, lbl_803CA870.x11, lbl_803CA870.y12, 7);
    x = fn_8010B204(r->b4);
    u = lbl_803CA870.unit;
    b1 = rb1(r);
    b0 = rb0(r);
    v1 = fn_801107C0(x, u);
    v2 = fn_801107A0(x, u);
    fn_80115DEC(lbl_803EC898, b0, b1, v2, v1);
    fn_80117E30(lbl_803EC898, r->b0, r->b1, r->b3);
    fn_8013F1C4();
    return 0;
}
