#include "game/rB_8002E1C4/battle.h"

/* Decides whether this battle plays the long animation, plus one scripted Ike vs Ashera case. */
struct VObjB {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual u32 buttons();
};
struct ItemL { u64 flags; };
extern const char lbl_80361338[];
extern void* lbl_804CA5AC;
extern void* lbl_804CA59C;
extern void* lbl_804CA588;
extern VObjB* lbl_804CB5B8;
struct GSF { u32 pad : 27; u32 f10 : 1; u32 low : 4; };
extern u8 lbl_803CAB38[];
extern "C" {
GSF* fn_80060728(void* p);
int fn_80030D84(BU* p);
const char* fn_801283C0(BU* p);
int fn_80291188(const char* a, const char* b);
Slot* fn_80030CF4(BU* p);
int fn_80030CFC(BU* p);
ItemL* fn_801116B8(Slot* it);
void fn_8011B060(void* list, void* key, int a, int b);
int fn_8011B77C(void* list, void* key);
int fn_800D7D74(void);
int fn_8011F680(Unit* u);
int fn_801220A0(BU* p);

static inline BU* pick(Battle* b) {
    if (b->a.u.ec == 0 && b->b.u.ec == 0) return 0;
    if (b->f15ec & 0x100) return 0;
    if (b->f15ec & 1) {
        if (fn_80030D84(&b->a)) return &b->a;
        return 0;
    }
    if (fn_80030D84(&b->b)) return &b->b;
    if (fn_80030D84(&b->a)) return &b->a;
    return 0;
}
static inline BU* other(Battle* b, BU* x) {
    if (x == 0) return 0;
    if (x == &b->a) return &b->b;
    if (x == &b->b) return &b->a;
    return 0;
}
static inline const char* itemName(Slot* s) {
    if (s->data) return *(const char**)s->data;
    return 0;
}
static inline int diff(Battle* b) {
    BU* s;
    if (b->a.u.u3f0 && fn_8011F680(b->a.u.u3f0)) return 2;
    s = 0;
    if (b->a.u.u3f0 && b->a.u.f4[8] == 0) s = &b->a;
    if (b->b.u.u3f0 && b->b.u.f4[8] == 0) s = &b->b;
    if (s) return fn_801220A0(s);
    if (b->a.u.u3f0) return fn_801220A0(&b->a);
    return 2;
}

void fn_8002C86C(Battle* b) {
    BU* o = other(b, pick(b));
    BU* p = pick(b);
    if (o && p
        && fn_80291188(fn_801283C0(o), lbl_80361338 + 1) == 0
        && fn_80291188(fn_801283C0(p), lbl_80361338 + 9) == 0) {
        Slot* w = fn_80030CF4(o);
        if (w && fn_80291188(itemName(w), lbl_80361338 + 0x15) == 0) {
            fn_8011B060(o->u.x12c, lbl_804CA5AC, 2, 0);
            {
            u32 f = b->f15ec;
            b->f15e8 = 1;
            b->f15ec = f | 0x200000;
            }
            goto E;
        }
    }
    if (!(b->f15ec & 0x01008305)) {
        if (fn_80030CF4(&b->a)->data && (fn_801116B8(fn_80030CF4(&b->a))->flags & 0x800000001080ULL)) goto L;
        if (*(u16*)b->a.u.x110 & 1) goto L;
        if (*(u16*)b->b.u.x110 & 1) goto L;
        if (fn_8011B77C(b->a.u.x12c, lbl_804CA59C)) goto L;
        if (fn_8011B77C(b->b.u.x12c, lbl_804CA59C)) goto L;
        if (fn_80030CFC(&b->a)) goto L;
        if (fn_80030CFC(&b->b)) goto L;
        if (b->a.u.f4[8] != 0 && b->b.u.f4[8] != 0) goto L;
        if (fn_8011B77C(b->a.u.x12c, lbl_804CA588)) goto L;
        if (fn_8011B77C(b->b.u.x12c, lbl_804CA588)) goto L;
        if (fn_800D7D74() == 0 && (lbl_804CB5B8->buttons() & 0x10)) goto E;
        if (diff(b) == 0) goto E;
    }
L:
    if (diff(b) == 2) b->f15ec |= 0x40000000;
    b->f15ec |= 0x80000000;
    return;
E:
    if (fn_800D7D74() == 0 && !fn_80060728(lbl_803CAB38)->f10) b->f15ec |= 0x10000000;
    b->f15ec &= 0x7fffffff;
}
}
