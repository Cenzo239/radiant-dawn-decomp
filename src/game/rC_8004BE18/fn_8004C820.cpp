/* fn_8004C820 (round 16): both helpBoxY copies written out with their own locals; the y sum is taken before the x call. */
#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on
extern "C" int fn_8004C820(void* a, Menu* b, MenuEntry* c) {
/*P*/
    int oy2;
    const char* t1;
    int oy1;
    s16 y1;
    s16 x1;
    MenuOwner* o1;
    s16 x2;
    s16 y2;
    const char* t2;
    MenuOwner* o2;
/*E*/
    if (c->active) {
        if (fn_801116B8(fn_80044FD0(&lbl_803CA870))->flags4 & 4) {
            y1 = c->y;
            o1 = b->owner;
            x1 = c->x;
            t1 = fn_800D0864(lbl_804CA1E0);
            oy1 = o1->v64() - -y1;
            fn_801A23E0(o1->v60() - -x1, oy1 - 0x3c, t1, b);
        } else {
            y2 = c->y;
            o2 = b->owner;
            x2 = c->x;
            t2 = fn_800D0864(lbl_804CA1D8);
            oy2 = o2->v64() - -y2;
            fn_801A23E0(o2->v60() - -x2, oy2 - 0x3c, t2, b);
        }
        return 0;
    }
    fn_800453B4(&lbl_803CA870, 0x29);
    return 6;
}
