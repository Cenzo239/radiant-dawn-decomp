/* Near misses for region rC_8004BE18. Not part of the matched build.
 * Compile against ../decls.h; each block says how close it got. */
#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on

/* fn_8004CB40: "if (flag & 4) return 2; return 0;" compiles branchless; target keeps branches */
extern "C" int fn_8004CB40(void) {
    ItemSlot* s = fn_80044FD0(&lbl_803CA870);
    if (!s->f7) {
        return 3;
    }
    if (dataFlag4(s)) {
        return 2;
    } else {
        return 0;
    }
}

/* fn_8004DB80: final "s8 < 0x1e" compare: target materialises 0x1e in a register (xoris/addc), 5 words */
static inline bool lessThan(int a, int b) { return a < b; }
static inline bool lessThan2(Unit* u, int b) { return fn_801284C4(lbl_803CA870.unit) < 0x1e ? 0 : 3; }
extern "C" int fn_8004DB80(void) {
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
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA5E0)) {
        return 0;
    }
    return fn_801284C4(lbl_803CA870.unit) < 0x1e ? 0 : 3;
}

/* fn_8004DE70: u held in r28 instead of r29 (2 words) */
extern "C" int fn_8004DE70(void) {
    Unit* u;
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA654) == 0) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D464)) {
        return 3;
    }
    u = lbl_803CA870.unit;
    fn_8003A3BC(u, fn_8010B228(lbl_8037D458));
    return lbl_803E7320.i0 == 0 ? 3 : 0;
}

/* fn_8004E0A0: u held in r28 instead of r29 (2 words) */
extern "C" int fn_8004E0A0(void) {
    Unit* u;
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA658) == 0) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D47C)) {
        return 3;
    }
    u = lbl_803CA870.unit;
    fn_8003A664(u, fn_8010B228(lbl_8037D470));
    return lbl_803E7320.i0 == 0 ? 3 : 0;
}

/* fn_8004FC10: register allocation of b0/b1/u differs (7 words) */
extern "C" int fn_8004FC10(void) {
    Unit* u;
    u8 v1;
    MapThing* r;
    s8 b1;
    s8 b0;
    ItemData* x;
    u8 v2;
    fn_80114B44(lbl_803EC898, 6, -1);
    fn_80114B44(lbl_803EC898, 9, 0);
    fn_80114888(lbl_803EC898, 7);
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

/* fn_8004FFF8: item loop: register allocation differs; inline version adds bool conversion */
extern "C" int fn_8004FFF8(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA69C) == 0) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D724)) {
        return 3;
    }
    return tryUseItems() ? 0 : 3;
}

/* fn_80050248: same as fn_8004FFF8 */
extern "C" int fn_80050248(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D724)) {
        return 3;
    }
    return tryUseItems() ? 0 : 3;
}

/* fn_800504AC: same as fn_8004FFF8 */
extern "C" int fn_800504AC(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA6F0) == 0) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D724)) {
        return 3;
    }
    return tryUseItems() ? 0 : 3;
}

/* fn_80050744: same as fn_8004FFF8 */
extern "C" int fn_80050744(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA6F4) == 0) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D724)) {
        return 3;
    }
    return tryUseItems() ? 0 : 3;
}

/* fn_8005211C: register allocation of u vs CSE of lbl_803EC898 */
extern "C" void fn_8005211C(MenuProc* p) {
    Unit* u = lbl_803CA870.unit;
    u8* m = lbl_803EC898;
    CursorRef* c;
    s8 x;
    s8 y;
    fn_80114B44(m, 9, 0);
    fn_80114888(m, 6);
    fn_801151BC(m, u);
    fn_8011567C(m, 0);
    fn_80115764(m, u->x102, u->y103, 200);
    fn_8013F1C4();
    c = p->cursor;
    p->saved = *c;
    if ((x = c->x) < 0 || (y = c->y) < 0 || ((s16*)(m + 0x710e))[x + (y << 6)] < 0) {
        x = u->x102;
        y = u->y103;
    }
    fn_800620A8(&lbl_803CAB38, x, y);
}

/* fn_8004C820: 14 words. Same help box twice (lbl_804CA1E0, lbl_804CA1D8) with helpBoxY from ../helpbox.h.
 * The original uses r26..r31 (c in r26) and different registers in each branch; ours uses r27..r31.
 * 576 declaration orders across the two copies reached 11 words at best. */
extern "C" int fn_8004C820(void* a, Menu* b, MenuEntry* c) {
    if (c->active) {
        if (fn_801116B8(fn_80044FD0(&lbl_803CA870))->flags4 & 4) {
            helpBoxY(b, c, lbl_804CA1E0);
        } else {
            helpBoxY(b, c, lbl_804CA1D8);
        }
        return 0;
    }
    fn_800453B4(&lbl_803CA870, 0x29);
    return 6;
}

/* fn_8004CA34: 2 words (no use_lmw_stmw, it uses _savegpr_27). refreshProc's saved a6 is in r29; the original has r31.
 * The bit clear only matches through s8: "*((s8*)slot + 5) &= ~0x80". */
extern "C" int fn_8004CA34(void* a, Menu* b, MenuEntry* c) {
    if (c->active) {
        helpBoxY(b, c, lbl_804CA1E8);
        return 0;
    }
    fn_80253EE4(lbl_8037D330, 0.0f);
    *((s8*)fn_80044FD0(&lbl_803CA870) + 5) &= ~0x80;
    if (fn_801116B8(fn_80044FD0(&lbl_803CA870))->flags0 & 0x100) {
        fn_80081194(lbl_8037B348, b->proc);
    }
    refreshProc(b->proc);
    return 5;
}

/* fn_80051FF4: 12 words. Only the &lbl_803CAB38 materialisation order and i/b registers differ. */

class CmdV {
public:
    VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    VPAD(16) VPAD(17) VPAD(18) VPAD(19)
    virtual int v58();
};
typedef struct MCEntry {
    u8 pad0[0x34];
    CmdV* cmd;
    u8 pad38[3];
    u8 b3b;
} MCEntry;
extern "C" MCEntry* fn_80085EF8(u8 id);
extern char lbl_80361B38[];
extern u8 lbl_804CB3F8;
extern u8 lbl_804CB410[8];
static inline int slotKind(void) {
    int k = 3;
    if (lbl_804CB3F8 == 0x33) {
        k = 0;
    }
    return k;
}
extern "C" void fn_80051FF4(void* parent) {
    int i;
    u8* p;
    CursorRef* slot;
    lbl_804CB3F8 = lbl_803CA870.b0c;
    if (lbl_804CB3F8 == 0x33) {
        fn_800310E4((void*)fn_800D0864(lbl_80361B38), 0, 0x28, 0);
    } else {
        fn_800310E4((void*)fn_800D0864(lbl_80361B38 + 0xa), 0, 0x28, 0);
    }
    p = (u8*)fn_800D5448(lbl_804CB410, parent, 0);
    if (p) {
        slot = fn_80062A9C(&lbl_803CAB38, slotKind());
        if (slot) {
            for (i = 0; i < *(s8*)(p + 0xa4); i++) {
                MCEntry* e = fn_80085EF8(p[0x40 + i]);
                u8 b = slot->b4;
                if (b == (u8)e->cmd->v58()) {
                    p[0xa6] = p[0xa7] = e->b3b;
                    break;
                }
            }
        }
    }
}
