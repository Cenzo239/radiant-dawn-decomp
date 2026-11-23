#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" const char* fn_8004CB98(void) {
    return fn_800D0864(lbl_8037D324);
}

extern "C" const char* fn_8004CBA4(void) {
    return fn_800D0864(lbl_8037D318);
}

extern "C" int fn_8004CBB0(void* a, Menu* b, MenuEntry* c) {
    if (c->active) {
        return 0x10;
    }
    fn_80253EE4(lbl_8037D35C, 0.0f);
    fn_8012A088(lbl_803CA870.unit, lbl_803CA870.itemIdx);
    if (lbl_803CA870.itemIdx < 7) {
        MenuProc* p = b->proc;
        p->a6 = fn_80127520(lbl_803CA870.unit);
    }
    if ((lbl_803CA870.unit->flags10c & 0x800000) ||
        (fn_801116B8(fn_80044FD0(&lbl_803CA870))->flags0 & 0x100)) {
        fn_80081194(lbl_8037B348, b->proc);
    }
    refreshProc(b->proc);
    return 5;
}

extern "C" int fn_8004CC98(void) {
    ItemSlot* s = fn_80044FD0(&lbl_803CA870);
    ItemData* d = s->data;
    Unit* u = lbl_803CA870.unit;
    if (s->f7) {
        return 3;
    }
    return fn_8012C998(u, d) ? 0 : 3;
}

extern "C" const char* fn_8004CCFC(void) {
    return fn_800D0864(lbl_8037D350);
}

extern "C" const char* fn_8004CD08(void) {
    return fn_800D0864(lbl_8037D344);
}

extern "C" int fn_8004CD14(void* a, void* b, MenuEntry* c) {
    if (c->active) {
        return 0x10;
    }
    fn_800453B4(&lbl_803CA870, 4);
    return 6;
}

extern "C" int fn_8004CD58(void) {
    ItemSlot* s = fn_80044FD0(&lbl_803CA870);
    ItemData* d = s->data;
    Unit* u = lbl_803CA870.unit;
    if (getItemType(d) == 0xb) {
        return 3;
    }
    if (fn_8012C8BC(u, d)) {
        return 0;
    }
    return fn_8012BC2C(u, d) ? 2 : 3;
}

extern "C" const char* fn_8004CDF4(void) {
    return fn_800D0864(lbl_8037D37C);
}

extern "C" const char* fn_8004CE00(void) {
    return fn_800D0864(lbl_8037D370);
}

extern "C" int fn_8004CE0C(void* a, void* b, MenuEntry* c) {
    if (c->active == 2) {
        return 0x10;
    }
    fn_8012A088(lbl_803CA870.unit, c->index);
    lbl_803CA870.itemIdx = fn_80127520(lbl_803CA870.unit);
    return 5;
}

extern "C" int fn_8004CE68(void* a, void* b, u32 idx) {
    ItemSlot* s = &lbl_803CA870.unit->items[idx];
    if (s == 0 || s->data == 0) {
        return 3;
    }
    if ((fn_801116B8(s)->flags4 & 0x11) == 0) {
        return 3;
    }
    return (fn_8012C7BC(lbl_803CA870.unit, s->data) == 0) + 1;
}

extern "C" int fn_8004CEF4(void) {
    fn_8013F204();
    return 0x0;
}

extern "C" int fn_8004CF18(void) {
    Unit* u;
    u8 v1;
    MapThing* r;
    s8 b1;
    s8 b0;
    ItemData* x;
    u8 v2;
    fn_8006A144();
    r = fn_80066130(lbl_803CB770, lbl_803CA870.x11, lbl_803CA870.y12, 7);
    x = fn_8010B204(r->b4);
    u = lbl_803CA870.unit;
    b1 = r->b1;
    b0 = r->b0;
    v1 = fn_801107C0(x, u);
    v2 = fn_801107A0(x, u);
    fn_80115DEC(lbl_803EC898, b0, b1, v2, v1);
    fn_80117E30(lbl_803EC898, r->b0, r->b1, r->b3);
    fn_8013F1C4();
    return 0;
}

extern "C" void fn_8004CFE0(void) {
    fn_80066D18(fn_80066130(lbl_803CB770, lbl_803CA870.unit->x102, lbl_803CA870.unit->y103, 7));
}

extern "C" int fn_8004D028(void* a, void* b, MenuEntry* c) {
    if (c->active == 2) {
        return 0x10;
    }
    return 5;
}

extern "C" int fn_8004D040(void) {
    fn_80066130(lbl_803CB770, lbl_803CA870.unit->x102, lbl_803CA870.unit->y103, 7);
    return 0;
}

extern "C" int fn_8004D088(void) {
    fn_8013F204();
    return 0x0;
}

extern "C" int fn_8004D0AC(void* a, void* b, MenuEntry* c) {
    Unit* u;
    u8 v2;
    u8 v1;
    fn_8006A144();
    if (c->active) {
        return 0;
    }
    u = lbl_803CA870.unit;
    {
        ItemSlot* s = &u->items[c->index];
        v2 = itemStatA(s->data, u);
        v1 = itemStatB(s->data, u);
    }
    fn_80114B44(lbl_803EC898, 6, -1);
    fn_80114B44(lbl_803EC898, 9, 0);
    fn_80114888(lbl_803EC898, 7);
    fn_80115DEC(lbl_803EC898, u->x102, u->y103, v2, v1);
    fn_8013F1C4();
    return 0;
}

extern "C" int fn_8004D1B0(void* a, void* b, MenuEntry* c) {
    if (c->active == 2) {
        return 0x10;
    }
    fn_8012A088(lbl_803CA870.unit, c->index);
    return 5;
}

extern "C" int fn_8004D1F4(void* a, void* b, u32 idx) {
    ItemSlot* s = &lbl_803CA870.unit->items[idx];
    if (s == 0 || s->data == 0) {
        return 3;
    }
    if ((fn_801116B8(s)->flags4 & 0x11) == 0) {
        return 3;
    }
    if (fn_8012BA20(lbl_803CA870.unit, s->data) == 0) {
        return 2;
    }
    if (lbl_803CA870.b0c == 0x28) {
        fn_80039C40(lbl_803CA870.unit, s->data);
    } else {
        fn_80039AE4(lbl_803CA870.unit, s->data);
    }
    if (lbl_803E7320.i0 == 0) {
        return 2;
    }
    return 1;
}

extern "C" int fn_8004D2CC(void* a, void* b) {
    fn_800453B4(&lbl_803CA870, 0x34);
    fn_80051FF4(b);
    return 4;
}

extern "C" void fn_8004D310(void) {
    Bytes4 v = *fn_800CD204(6);
    fn_80080508(&v);
}

extern "C" int fn_8004D35C(void) {
    if ((fn_80060728(&lbl_803CAB38)->w0 & 3) == 2) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4D8) == 0) {
        return 3;
    }
    if (fn_8010E2F4((u8*)lbl_804CB814 + 0x24) == 0) {
        return 3;
    }
    if (fn_80060780(&lbl_803CAB38) == 0) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D3A0)) {
        return 3;
    }
    return 0;
}

extern "C" const char* fn_8004D554(void) {
    return fn_800D0864(lbl_8037D394);
}

extern "C" const char* fn_8004D560(void) {
    return fn_800D0864(lbl_8037D388);
}

extern "C" int fn_8004D56C(void* a, void* b) {
    fn_800453B4(&lbl_803CA870, 0x33);
    fn_80051FF4(b);
    return 4;
}

extern "C" void fn_8004D5B0(void) {
    Bytes4 v = *fn_800CD204(7);
    fn_80080508(&v);
}

extern "C" int fn_8004D5FC(void) {
    if ((fn_80060728(&lbl_803CAB38)->w0 & 3) == 2) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4D8) == 0) {
        return 3;
    }
    if (fn_8010E2F4(lbl_804CB814) <= 1) {
        return 3;
    }
    if (fn_80060780(&lbl_803CAB38) == 0) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D3C4)) {
        return 3;
    }
    return 0;
}

extern "C" const char* fn_8004D7F0(void) {
    return fn_800D0864(lbl_8037D3B8);
}

extern "C" const char* fn_8004D7FC(void) {
    return fn_800D0864(lbl_8037D3AC);
}

extern "C" int fn_8004D808(void) {
    fn_800453B4(&lbl_803CA870, 0x2f);
    return 0x5;
}

extern "C" int fn_8004D838(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (fn_8011EF78(lbl_803CA870.unit) == 0) {
        return 3;
    }
    return fn_80066130(lbl_803CB770, lbl_803CA870.x11, lbl_803CA870.y12, 10) ? 0 : 3;
}

extern "C" const char* fn_8004D8C4(void) {
    return fn_800D0864(lbl_804CA1F8);
}

extern "C" const char* fn_8004D8CC(void) {
    return fn_800D0864(lbl_804CA1F0);
}

extern "C" int fn_8004D8D4(void) {
    fn_8013F204();
    return 0x0;
}

extern "C" int fn_8004D8F8(void) {
    fn_800677E0(lbl_803CA870.unit);
    fn_8013F1C4();
    return 0;
}

extern "C" int fn_8004D928(void* a, void* b, MenuEntry* c) {
    if (c->active) {
        return 0x10;
    }
    fn_800453B4(&lbl_803CA870, 0x1e);
    return 5;
}

extern "C" int fn_8004D96C(void) {
    return 0x3;
}

extern "C" const char* fn_8004D974(void) {
    return fn_800D0864(lbl_804CA200);
}

extern "C" const char* fn_8004D97C(void) {
    return fn_800D0864(lbl_8037D3D0);
}

extern "C" int fn_8004D988(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4F0)) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4F4)) {
        return 3;
    }
    return fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4EC) ? 0 : 3;
}

extern "C" int fn_8004DA2C(void) {
    fn_800453B4(&lbl_803CA870, 0x3f);
    return 0x5;
}

extern "C" const char* fn_8004DA5C(void) {
    return fn_800D0864(lbl_8037D3EC);
}

extern "C" const char* fn_8004DA68(void) {
    return fn_800D0864(lbl_8037D3DC);
}

extern "C" int fn_8004DA74(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4EC)) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4F0)) {
        return 3;
    }
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4F4)) {
        return 3;
    }
    return fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA650) ? 0 : 3;
}

extern "C" int fn_8004DB38(void) {
    fn_800453B4(&lbl_803CA870, 0x3e);
    return 0x5;
}

extern "C" const char* fn_8004DB68(void) {
    return fn_800D0864(lbl_8037D40C);
}

extern "C" const char* fn_8004DB74(void) {
    return fn_800D0864(lbl_8037D3FC);
}
