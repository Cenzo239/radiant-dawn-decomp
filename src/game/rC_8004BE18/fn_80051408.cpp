#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" const char* fn_80051408(void) {
    return fn_800D0864(lbl_804CA2A8);
}

extern "C" int fn_80051410(void) {
    return 0xc;
}

extern "C" Mask fn_80051418(void) {
    Mask m;
    m.v = 0;
    m.v |= 1;
    return m;
}

extern "C" int fn_80051428(MaskObj* a) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    Mask m = fn_8012C5D8(lbl_803CA870.unit);
    if ((m.v & 0x38) == 0 && !m.test(a->v60())) {
        return 3;
    }
    {
        Unit* u = lbl_803CA870.unit;
        fn_8003AA60(u, a->v60());
    }
    if (lbl_803E7320.i0 == 0) {
        return 3;
    }
    if ((m.v & 0x20) && !m.test(a->v60())) {
        return 2;
    }
    return 0;
}

extern "C" Mask fn_80051540(void) {
    Mask m;
    m.v = 0;
    m.v |= 2;
    return m;
}

extern "C" int fn_80051550(void) {
    return 0xb;
}

extern "C" const char* fn_80051558(void) {
    return fn_800D0864(lbl_804CA298);
}

extern "C" const char* fn_80051560(void) {
    return fn_800D0864(lbl_804CA290);
}

extern "C" const char* fn_80051568(void) {
    return fn_800D0864(lbl_8037D7C0);
}

extern "C" const char* fn_80051574(void) {
    return fn_800D0864(lbl_804CA2A0);
}

extern "C" const char* fn_8005157C(void) {
    return fn_800D0864(lbl_8037D7CC);
}

extern "C" int fn_80051588(void) {
    fn_800453B4(&lbl_803CA870, 0x9);
    return 0x5;
}

extern "C" int fn_800515B8(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D7F0)) {
        return 3;
    }
    return fn_800A05B0(9, lbl_803CA870.unit->x102, lbl_803CA870.unit->y103) == 0 ? 3 : 0;
}

extern "C" const char* fn_80051780(void) {
    return fn_800D0864(lbl_8037D7E4);
}

extern "C" const char* fn_8005178C(void) {
    return fn_800D0864(lbl_8037D7D8);
}

extern "C" int fn_80051798(void* a, void* b) {
    fn_800453B4(&lbl_803CA870, 0xe);
    fn_800D5448(lbl_803CAA8C, b, 0);
    return 4;
}

extern "C" int fn_800517E8(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D808)) {
        return 3;
    }
    return fn_800A05B0(0xe, lbl_803CA870.unit->x102, lbl_803CA870.unit->y103) == 0 ? 3 : 0;
}

extern "C" const char* fn_800519B0(void) {
    return fn_800D0864(lbl_8037D7FC);
}

extern "C" const char* fn_800519BC(void) {
    return fn_800D0864(lbl_804CA2B0);
}

extern "C" int fn_800519C4(void* a, void* b) {
    fn_800453B4(&lbl_803CA870, 0x2a);
    fn_800D5448(lbl_803CAA80, b, 0);
    return 4;
}

extern "C" int fn_80051A14(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D820)) {
        return 3;
    }
    return fn_800A0ED4(0x2a, lbl_803CA870.unit->x102, lbl_803CA870.unit->y103) == 0 ? 3 : 0;
}

extern "C" const char* fn_80051BDC(void) {
    return fn_800D0864(lbl_8037D814);
}

extern "C" const char* fn_80051BE8(void) {
    return fn_800D0864(lbl_804CA2B8);
}

extern "C" int fn_80051BF0(void* a, void* b) {
    fn_800453B4(&lbl_803CA870, 0xd);
    fn_800D5448(lbl_803CAA74, b, 0);
    return 4;
}

extern "C" int fn_80051C40(void) {
    Unit* u;
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D844)) {
        return 3;
    }
    u = lbl_803CA870.unit;
    if (fn_8011B560(u->x12c, lbl_804CA4D8) == 0) {
        return 3;
    }
    return fn_800A05B0(0xd, u->x102, u->y103) == 0 ? 3 : 0;
}

extern "C" const char* fn_80051E24(void) {
    return fn_800D0864(lbl_8037D838);
}

extern "C" const char* fn_80051E30(void) {
    return fn_800D0864(lbl_8037D82C);
}

extern "C" int fn_80051E3C(void) {
    fn_800453B4(&lbl_803CA870, 0x1);
    return 0x5;
}

extern "C" const char* fn_80051E6C(void) {
    return fn_800D0864(lbl_8037D85C);
}

extern "C" const char* fn_80051E78(void) {
    return fn_800D0864(lbl_8037D850);
}

extern "C" int fn_80051E84(void) {
    return 0x0;
}

extern "C" int fn_80051E8C(void) {
    return 0x0;
}

extern "C" int fn_80051E94(void) {
    return 0xb4;
}

extern "C" int fn_80051E9C(void) {
    return 0x28;
}

extern "C" int fn_80051EA4(void) {
    return 0x20;
}

extern "C" int fn_80051EAC(void) {
    return 0x10a;
}

extern "C" int fn_80051EB4(void) {
    return 0xc;
}

extern "C" int fn_80051EBC(void) {
    return 0x1a;
}

extern "C" void fn_80051EC4(void) {
}

extern "C" int fn_80051EC8(void) {
    return 0x20;
}

extern "C" void* fn_80051ED0(void) {
    return lbl_8037D8A0;
}

extern "C" void* fn_80051EDC(void) {
    return lbl_8037D884;
}

extern "C" void* fn_80051EE8(void) {
    return lbl_8037D868;
}

extern "C" f32 fn_80051EF4(void) {
    return lbl_804CCEA0;
}

extern "C" int fn_80051EFC(void) {
    return 0x80;
}

extern "C" int fn_80051F04(void) {
    return 0x110;
}

extern "C" int fn_80051F0C(void) {
    return 0x42;
}

extern "C" int fn_80051F14(MenuOwner* o) {
    return (0x1c0 - o->v54()) >> 1;
}

extern "C" int fn_80051F4C(MenuOwner* o) {
    return (0x260 - o->v50()) >> 1;
}

extern "C" int fn_80051F84(void) {
    return 0x50;
}

extern "C" int fn_80051F8C(void) {
    return 0xb4;
}

extern "C" int fn_80051F94(void) {
    return 0x28;
}

extern "C" int fn_80051F9C(void) {
    return 0x1c;
}

extern "C" int fn_80051FA4(void) {
    return 0x10a;
}

extern "C" int fn_80051FAC(void) {
    return 0xc;
}

extern "C" int fn_80051FB4(void) {
    return 0x1a;
}

extern "C" int fn_80051FBC(void) {
    return 0x18;
}

extern "C" int fn_80051FC4(void) {
    return 0x44;
}

extern "C" int fn_80051FCC(void) {
    return 0x60;
}

extern "C" int fn_80051FD4(void) {
    return 0x190;
}

extern "C" int fn_80051FDC(void) {
    return 0x14;
}

extern "C" int fn_80051FE4(void) {
    return 0x78;
}

extern "C" int fn_80051FEC(void) {
    return 0x0;
}
