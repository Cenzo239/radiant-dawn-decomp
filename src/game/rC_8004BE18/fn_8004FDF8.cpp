#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004FDF8(void) {
    Unit* u;
    MapThing* m;
    if (lbl_803CA870.b16) {
        return 3;
    }
    u = lbl_803CA870.unit;
    if (fn_8011B77C(u->x12c, lbl_804CA510) == 0) {
        return 3;
    }
    m = fn_80066130(lbl_803CB770, u->x102, u->y103, 7);
    if (m == 0) {
        return 3;
    }
    fn_80039D6C(lbl_803CA870.unit, m);
    if (lbl_803E7320.i0 == 0) {
        return 3;
    }
    return m->b5 == 0 ? 2 : 0;
}

extern "C" const char* fn_8004FECC(void) {
    return fn_800D0864(lbl_804CA278);
}

extern "C" const char* fn_8004FED4(void) {
    return fn_800D0864(lbl_804CA270);
}

extern "C" int fn_8004FEDC(void) {
    fn_8013F204();
    return 0x0;
}

extern "C" int fn_8004FF00(void) {
    fn_8006746C(lbl_803CA870.unit);
    fn_8013F1C4();
    return 0;
}

extern "C" int fn_8004FF30(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA630) == 0) {
        return 3;
    }
    fn_8003B574(lbl_803CA870.unit);
    return lbl_803E7320.i0 == 0 ? 3 : 0;
}

extern "C" int fn_8004FFB0(void) {
    fn_800453B4(&lbl_803CA870, 0x20);
    return 0x5;
}

extern "C" const char* fn_8004FFE0(void) {
    return fn_800D0864(lbl_8037D650);
}

extern "C" const char* fn_8004FFEC(void) {
    return fn_800D0864(lbl_8037D644);
}
