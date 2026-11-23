/* fn_8004CA34 (round 16): help box written out (y sum before the x call) and refreshProc expanded; uses _savegpr_27, so no use_lmw_stmw. */
#include "game/rC_8004BE18/helpbox.h"
extern "C" int fn_8004CA34(void* a, Menu* b, MenuEntry* c) {
/*P*/
    u8 s;
    int oy;
    s16 y;
    const char* t;
    s16 x;
    MenuOwner* o;
    MenuProc* p;
/*E*/
    if (c->active) {
        y = c->y;
        o = b->owner;
        x = c->x;
        t = fn_800D0864(lbl_804CA1E8);
        oy = o->v64() - -y;
        fn_801A23E0(o->v60() - -x, oy - 0x3c, t, b);
        return 0;
    }
    fn_80253EE4(lbl_8037D330, 0.0f);
    *((s8*)fn_80044FD0(&lbl_803CA870) + 5) &= ~0x80;
    if (fn_801116B8(fn_80044FD0(&lbl_803CA870))->flags0 & 0x100) {
        fn_80081194(lbl_8037B348, b->proc);
    }
    p = b->proc;
    s = p->a6;
    fn_800D56E8(p);
    p->a6 = s;
    return 5;
}
