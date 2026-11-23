#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004C3F4(void* a, void* b, u32 idx) {
    ItemSlot* s = &lbl_803CA870.unit2->items[idx];
    if (s->data == 0) {
        return 3;
    }
    return fn_8011F0E0(lbl_803CA870.unit, s) == 0 ? 2 : 0;
}

extern "C" int fn_8004C454(void) {
    return 9;
}

extern "C" int fn_8004C45C(void) {
    return 1;
}

extern "C" const char* fn_8004C464(void) {
    return fn_800D0864(lbl_804CA160);
}

extern "C" int fn_8004C46C(void) {
    fn_800453B4(&lbl_803CA870, 0);
    return 9;
}

extern "C" int fn_8004C49C(void) {
    return 1;
}

extern "C" const char* fn_8004C4A4(void) {
    return fn_800D0864(lbl_804CA168);
}

extern "C" int fn_8004C4AC(void) {
    return 6;
}

extern "C" int fn_8004C4B4(void) {
    return 0;
}

extern "C" const char* fn_8004C4BC(void) {
    return fn_800D0864(lbl_804CA170);
}

extern "C" int fn_8004C4C4(void) {
    fn_80253EE4(lbl_8037D2F0, 0.0f);
    return 1;
}

extern "C" int fn_8004C4F4(void) {
    return 1;
}

extern "C" const char* fn_8004C4FC(void) {
    return fn_800D0864(lbl_804CA1B8);
}

extern "C" int fn_8004C504(void* a, MenuProc* b) {
    int f = 0;
    if ((fn_801116B8(fn_80044FD0(&lbl_803CA870))->flags0 & 0x100) &&
        (lbl_803CA870.unit->flags10c & 0x800000)) {
        f = 1;
    }
    fn_8012A80C(lbl_803CA870.unit, lbl_803CA870.itemIdx);
    if (fn_8012BCB0(lbl_803CA870.unit)) {
        fn_800453B4(&lbl_803CA870, 0);
        if (f) {
            fn_80081194(lbl_8037B348, fn_800D569C(b)->f18);
        }
        return 6;
    }
    fn_800D56E8(b->f18->f18);
    fn_80083B78(b->f18);
    if (f) {
        fn_80081194(lbl_8037B348, b->f18);
    }
    return 5;
}

extern "C" int fn_8004C608(void) {
    return 0;
}

extern "C" const char* fn_8004C610(void) {
    return fn_800D0864(lbl_804CA1C0);
}

extern "C" int fn_8004C618(void* a, void* b, MenuEntry* c) {
    ProcXY* p;
    lbl_803CA870.itemIdx = c->index;
    fn_8012CAD8(lbl_803CA870.unit);
    p = (ProcXY*)fn_800D5448(lbl_804CB3B0, b, 0);
    p->x = 0x180;
    p->y = 0x46;
    return 4;
}

extern "C" int fn_8004C67C(void* a, void* b, u32 idx) {
    ItemData* d = lbl_803CA870.unit->items[idx].data;
    if (d == 0) {
        return 3;
    }
    return fn_8012B35C(lbl_803CA870.unit, d) == 0 ? 2 : 0;
}
