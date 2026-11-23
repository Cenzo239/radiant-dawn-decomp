#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" const char* fn_8004E290(void) {
    return fn_800D0864(lbl_804CA228);
}

extern "C" const char* fn_8004E298(void) {
    return fn_800D0864(lbl_804CA224);
}

extern "C" int fn_8004E2A0(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (lbl_803CA870.b28 & 2) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D4A0)) {
        return 3;
    }
    fn_800399B0(lbl_803CA870.unit, -1);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" int fn_8004E478(void) {
    fn_800453B4(&lbl_803CA870, 0x6);
    return 0x5;
}

extern "C" int fn_8004E4A8(void* a, void* b) {
    fn_800453B4(&lbl_803CA870, 0x21);
    fn_800D5448(lbl_803CAA98, b, 0);
    return 4;
}

extern "C" int fn_8004E4F8(void) {
    return 0x3;
}

extern "C" const char* fn_8004E500(void) {
    return fn_800D0864(lbl_804CA230);
}

extern "C" const char* fn_8004E508(void) {
    return fn_800D0864(lbl_8037D4AC);
}

extern "C" int fn_8004E514(void) {
    fn_800453B4(&lbl_803CA870, 0x11);
    return 0x5;
}

extern "C" int fn_8004E544(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA5C0) == 0) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D4D0)) {
        return 3;
    }
    fn_8003A368(lbl_803CA870.unit);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" const char* fn_8004E724(void) {
    return fn_800D0864(lbl_8037D4C4);
}

extern "C" const char* fn_8004E730(void) {
    return fn_800D0864(lbl_8037D4B8);
}

extern "C" int fn_8004E73C(ProcBase* a, void* b) {
    fn_800310E4(a->v0c(), 0, 0x28, 0);
    fn_8023FC40(b);
    return 4;
}

extern "C" const char* fn_8004E790(void) {
    return fn_800D0864(lbl_8037D4DC);
}

extern "C" int fn_8004E79C(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D4F4)) {
        return 3;
    }
    return fn_8023FC50() ? 0 : 3;
}

extern "C" const char* fn_8004E94C(void) {
    return fn_800D0864(lbl_8037D4E8);
}

extern "C" int fn_8004E958(void) {
    fn_800453B4(&lbl_803CA870, 0x1d);
    return 0x5;
}

extern "C" int fn_8004E988(void) {
    if (lbl_803CA870.b28 & 4) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (lbl_803CA870.unit->flags10c & 2) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D50C)) {
        return 3;
    }
    fn_8003A250(lbl_803CA870.unit);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" const char* fn_8004EB74(void) {
    return fn_800D0864(lbl_804CA238);
}

extern "C" const char* fn_8004EB7C(void) {
    return fn_800D0864(lbl_8037D500);
}

extern "C" int fn_8004EB88(void) {
    return 0x0;
}

extern "C" int fn_8004EB90(void) {
    fn_800453B4(&lbl_803CA870, 0x1c);
    return 0x5;
}

extern "C" int fn_8004EBC0(void) {
    Unit* u;
    u32 f;
    if (lbl_803CA870.b28 & 4) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D524)) {
        return 3;
    }
    u = lbl_803CA870.unit;
    f = u->flags10c;
    if ((f & 2) == 0) {
        return 3;
    }
    if (f & 0x100000) {
        return 3;
    }
    fn_8003A1FC(u);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" const char* fn_8004EDB8(void) {
    return fn_800D0864(lbl_804CA240);
}

extern "C" const char* fn_8004EDC0(void) {
    return fn_800D0864(lbl_8037D518);
}

extern "C" int fn_8004EDCC(void) {
    return 0x0;
}

extern "C" int fn_8004EDD4(void) {
    fn_800453B4(&lbl_803CA870, 0x10);
    return 0x5;
}

extern "C" int fn_8004EE04(void) {
    Unit* u;
    int i;
    ItemSlot* s;
    if (lbl_803CA870.b16) {
        return 3;
    }
    u = lbl_803CA870.unit;
    if (flagExists(&lbl_803CAB38, lbl_804CA258)) {
        return 3;
    }
    for (i = 0, s = u->items; i < 7; i++, s++) {
        if (s == 0 || s->data == 0) {
            break;
        }
        if (fn_8012BB48(u, s->data) && fn_801118C0(lbl_803CA870.unit, s->data)) {
            return 0;
        }
    }
    return 3;
}

extern "C" const char* fn_8004EFF8(void) {
    return fn_800D0864(lbl_8037D530);
}

extern "C" const char* fn_8004F004(void) {
    return fn_800D0864(lbl_804CA250);
}

extern "C" int fn_8004F00C(void) {
    return 0x0;
}

extern "C" char* fn_8004F014(void) {
    return lbl_804CA248;
}

extern "C" int fn_8004F01C(void) {
    fn_800453B4(&lbl_803CA870, 0x1b);
    return 0x5;
}

extern "C" int fn_8004F04C(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (lbl_803CA870.unit->f8 == 0) {
        return 3;
    }
    if (lbl_803CA870.unit->flags10c & 0x100000) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D560)) {
        return 3;
    }
    fn_8003A0C4(lbl_803CA870.unit);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" const char* fn_8004F238(void) {
    return fn_800D0864(lbl_8037D554);
}

extern "C" const char* fn_8004F244(void) {
    return fn_800D0864(lbl_8037D548);
}

extern "C" int fn_8004F250(void) {
    return 0x0;
}

extern "C" void* fn_8004F258(void) {
    return lbl_8037D53C;
}

extern "C" int fn_8004F264(void) {
    fn_800453B4(&lbl_803CA870, 0x1a);
    return 0x5;
}

extern "C" int fn_8004F294(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (lbl_803CA870.unit->flags10c & 6) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D5A8)) {
        return 3;
    }
    fn_8003A03C(lbl_803CA870.unit);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" const char* fn_8004F46C(void) {
    if (unitHas(lbl_804CA6D8)) {
        return fn_800D0864(lbl_8037D59C);
    }
    return fn_800D0864(lbl_8037D590);
}

extern "C" const char* fn_8004F4C0(void) {
    if (unitHas(lbl_804CA6D8)) {
        return fn_800D0864(lbl_8037D584);
    }
    return fn_800D0864(lbl_8037D578);
}

extern "C" int fn_8004F514(void) {
    return 0x0;
}

extern "C" void* fn_8004F51C(void) {
    return lbl_8037D56C;
}

extern "C" int fn_8004F528(void) {
    fn_800453B4(&lbl_803CA870, 0x19);
    return 0x5;
}

extern "C" int fn_8004F558(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA678) == 0) {
        return 3;
    }
    if (lbl_803CA870.unit->flags10c & 6) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D5D8)) {
        return 3;
    }
    fn_80039FB4(lbl_803CA870.unit);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" const char* fn_8004F750(void) {
    return fn_800D0864(lbl_8037D5CC);
}

extern "C" const char* fn_8004F75C(void) {
    return fn_800D0864(lbl_8037D5C0);
}

extern "C" int fn_8004F768(void) {
    return 0x0;
}

extern "C" void* fn_8004F770(void) {
    return lbl_8037D5B4;
}

extern "C" int fn_8004F77C(void) {
    fn_800453B4(&lbl_803CA870, 0x14);
    return 0x5;
}

extern "C" int fn_8004F7AC(void) {
    if (unitHas(lbl_804CA6F8) == 0) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D600)) {
        return 3;
    }
    fn_80039F2C(lbl_803CA870.unit, 2);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" const char* fn_8004F990(void) {
    return fn_800D0864(lbl_804CA260);
}

extern "C" const char* fn_8004F998(void) {
    return fn_800D0864(lbl_8037D5F4);
}

extern "C" int fn_8004F9A4(void) {
    return 0x0;
}

extern "C" void* fn_8004F9AC(void) {
    return lbl_8037D5E8;
}

extern "C" int fn_8004F9B8(void) {
    fn_800453B4(&lbl_803CA870, 0x13);
    return 0x5;
}

extern "C" int fn_8004F9E8(void) {
    if (unitHas(lbl_804CA5BC) == 0) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D628)) {
        return 3;
    }
    fn_80039F2C(lbl_803CA870.unit, 1);
    return lbl_803E7320.i0 ? 0 : 3;
}

extern "C" const char* fn_8004FBCC(void) {
    return fn_800D0864(lbl_804CA268);
}

extern "C" const char* fn_8004FBD4(void) {
    return fn_800D0864(lbl_8037D61C);
}

extern "C" void* fn_8004FBE0(void) {
    return lbl_8037D610;
}

extern "C" int fn_8004FBEC(void) {
    fn_8013F204();
    return 0x0;
}
