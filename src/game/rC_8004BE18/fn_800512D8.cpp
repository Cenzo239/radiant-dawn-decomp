/* fn_800512D8 (round 16): menu-command effect that sets action 5 from the command and picks the item slot. Locals ordered by sw.py. */
#include "game/rC_8004BE18/decls.h"
#pragma use_lmw_stmw on
class CmdM {
public:
    VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    VPAD(16) VPAD(17) VPAD(18) VPAD(19)
    virtual const char* v58();               /* 0x58 */
    virtual int v5C();                       /* 0x5C */
    virtual Mask v60();                      /* 0x60 */
};
extern "C" void fn_800482F8(UnitCmdState* st, Mask m);
extern "C" int fn_8012C6C4(Unit* u, const Mask& m);
extern "C" void fn_801A23E0(int x, int y, const char* t, Menu* b);

extern "C" int fn_800512D8(CmdM* a, Menu* b, MenuEntry* c) {
/*P*/
    int oy;
    const char* t;
    int ox;
    s16 y;
    s16 x;
    Unit* u;
    MenuOwner* o;
    int r;
    int k;
/*E*/
    if (c->active) {
        y = c->y;
        o = b->owner;
        x = c->x;
        t = a->v58();
        oy = o->v64();
        ox = o->v60();
        fn_801A23E0(ox + x, oy + y, t, b);
        return 0;
    }
    k = a->v5C();
    fn_800453B4(&lbl_803CA870, (u8)k);
    {
        Mask m = fn_8012C5D8(lbl_803CA870.unit);
        fn_800482F8(&lbl_803CA870, m);
    }
    u = lbl_803CA870.unit;
    r = fn_8012C6C4(u, a->v60());
    lbl_803CA870.itemIdx = r >= 0 ? r : -1;
    return 5;
}
