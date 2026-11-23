#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on

/* Locals must be declared at the top: declared inside the if-block they get other registers. */
extern "C" int fn_8004C2EC(void* a, Menu* b, MenuEntry* c) {
    const char* t;
    s16 y;
    s16 x;
    MenuOwner* o;
    char* str;
    int ox;
    if (c->active) {
        str = 0;
        switch (fn_8011F024(lbl_803CA870.unit, &b->owner->unit->items[c->index])) {
        case 1:
            str = lbl_804CA130;
            break;
        case 2:
            str = lbl_804CA128;
            break;
        case 3:
            str = lbl_804CA120;
            break;
        case 4:
            str = lbl_804CA118;
            break;
        }
        y = c->y;
        x = c->x;
        o = b->owner;
        t = fn_800D0864(str);
        ox = o->v60();
        fn_801A23E0(ox + x, y, t, b);
        return 0;
    }
    lbl_803CA870.itemIdx = c->index;
    return 5;
}
