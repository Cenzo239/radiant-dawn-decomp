#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8004BE18(void) {
    return 0;
}

extern "C" int fn_8004BE20(MenuCmd* a, void* b, MenuEntry* c) {
    ItemRef* r;
    if (c->active) {
        return 0x10;
    }
    r = a->v5c(c);
    lbl_804CB3E8.data = r->data;
    lbl_804CB3E8.b4 = r->b4;
    lbl_804CB3E8.b5 = r->b5;
    fn_800D5448(lbl_803CAB20, b, 0);
    return 4;
}

extern "C" int fn_8004BEA4(MenuCmd* a) {
    ItemRef* r = a->v58(lbl_804CB3E0);
    ItemData* d;
    if (r == 0 || (d = r->data) == 0) {
        return 3;
    }
    if (r->b5 & 1) {
        return 2;
    }
    if (lbl_804CB3E8.data != 0 && d->id1c == lbl_804CB3E8.data->id1c) {
        return 1;
    }
    return 0;
}

extern "C" ItemSlot* fn_8004BF2C(void* a, MenuEntry* c) {
    return getSlot(c->index);
}

extern "C" int fn_8004BF58(void) {
    return 0;
}

extern "C" int fn_8004BF60(void) {
    return 0;
}

extern "C" void fn_8004BF68(MenuCmd* a, void* b, MenuEntry* c) {
    a->v50();
    fn_80107C80(getSlot(c->index), !c->active, c->x, c->y);
}

extern "C" int fn_8004BFE0(void* a, void* b, MenuEntry* c) {
    if (c->active) {
        return 0x10;
    }
    lbl_803CA870.itemIdx = c->index;
    fn_800D5448(lbl_803CAB08, b, 0);
    return 4;
}

extern "C" int fn_8004C034(void* a, void* b, u32 idx) {
    if ((fn_801116B8(getSlot(idx))->flags4 & 4) || isUnusableA(getSlot(idx))) {
        return 2;
    }
    if (!fn_80060754(&lbl_803CAB38) && isUnusableB(getSlot(idx))) {
        return 2;
    }
    if (idx == 7) {
        return 1;
    }
    return 0;
}

extern "C" int fn_8004C180(void* a, void* b, MenuEntry* c) {
    if (c->active) {
        return 0x10;
    }
    lbl_803CA870.i18 = c->index;
    return 5;
}

extern "C" void fn_8004C1AC(MenuCmd* a, Menu* b, MenuEntry* c) {
    a->v50();
    fn_80107C80(&b->owner->unit->items[c->index], !c->active, c->x, c->y);
}

extern "C" int fn_8004C220(void* a, void* b, u32 idx) {
    ItemSlot* s = &lbl_803CA870.unit2->items[idx];
    if (s->data == 0) {
        return 3;
    }
    return fn_80111F5C(s) == 0 ? 2 : 0;
}

extern "C" void fn_8004C278(MenuCmd* a, Menu* b, MenuEntry* c) {
    a->v50();
    fn_80107C80(&b->owner->unit->items[c->index], !c->active, c->x, c->y);
}
