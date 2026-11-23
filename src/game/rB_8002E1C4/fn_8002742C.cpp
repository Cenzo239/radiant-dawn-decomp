#include "game/rB_8002E1C4/battle.h"

struct Rec7 { u8 a, b, c, d, e; s8 f; u8 g; };
struct Roll {
    u8 x0[0x20];
    s16 x20[0x20];
    s16 x60[0x20];
    u8 xa0, xa1, xa2, xa3, xa4;
    s8 xa5;
    u8 xa6;
    u8 padA7[0xc8 - 0xa7];
    u32 xc8, xcc;
};
struct GS { u8 pad[0x11]; u8 x11; };
struct Vec3 { f32 x, y, z; };
extern Roll lbl_803C8DA0;

extern u8 lbl_803CAB38[];
extern u8 lbl_803EC898[];
extern void* lbl_804CA698;
extern void* lbl_804CA5A0;
extern void* lbl_804CA5A4;
extern "C" {
void fn_800282A0(Battle* b, BU* a, BU* d, int k);
void fn_800275C4(Battle* b, int a, int k);
f32 fn_80127868(BU* p);
Rec7 fn_801278B8(BU* p, f32 bio);
int fn_8011B77C(void* list, void* key);
void fn_8011B430(void* list, void* key);
void fn_8011A36C(void* list);
Slot* fn_80030CBC(BU* p);
s16 fn_80123AC4(BU* p);
int fn_80089D68(int n);
void fn_8002600C(void* log, int code, int v);
void fn_80026324(void* log, int code, int k, int v);
GS* fn_80060728(void* p);
Slot* fn_80030CF4(BU* p);
ItemD* fn_801116B8(Slot* it);
void fn_80112A3C(u8 a, u8 d, s16* p, s16* q);
int fn_801237EC(BU* p);
void fn_80027D9C(Battle* b, BU* a, BU* d, int k, int n);
void fn_8002C86C(Battle* b);
#if TARGET_PC
FE10_PROTO void * fn_80116A30(void* m, s8 x, s8 y);
#else
int fn_80116A30(void* m, s8 x, s8 y);
#endif
f32 fn_80117200(void* m, s8 x, s8 y, u8 d);

static inline int rollP(int n) {
    if (((Battle*)lbl_803C8E80)->f15ec & 0x4000) {
        if (lbl_803C8DA0.xa3) return 1;
        return 0;
    }
    return fn_80089D68(n);
}

void fn_8002742C(Battle* b, int a) {
    fn_800282A0(b, &b->a, &b->b, 0);
    fn_800275C4(b, a, 1);
    b->f15e4 = 0;
    fn_800282A0(b, &b->a, &b->b, 0);
    f32 bioA = fn_80127868(&b->a);
    fn_801278B8(&b->a, bioA);
    f32 bioB = fn_80127868(&b->b);
    {
    Rec7 r = fn_801278B8(&b->b, bioB);
    s8 f = r.f;
    if (fn_8011B77C(b->b.u.x12c, lbl_804CA698)) {
        if (fn_80030CBC(&b->b)->data) {
            if (rollP(f + fn_80123AC4(&b->b))) {
                fn_80026324(b->log, 0x3e, 0x3f, 0);
            } else {
                fn_80026324(b->log, 0x3e, 0x9b, 0);
                fn_8011B430(b->b.u.x12c, lbl_804CA698);
                fn_8011A36C(b->b.u.x12c);
            }
        }
    }
    }
    fn_8002600C(b->log, 0x72, 0);
}

static inline u8 wtype(BU* u) {
    Slot* s = fn_80030CF4(u);
    return s->data ? ((ItemD*)s->data)->x13 : 0x13;
}
static inline void neg(BU* u) {
    u->x476 -= u->x476 * 2;
    u->x474 -= u->x474 * 2;
}

void fn_8002A8A4(Battle* b, BU* a, BU* d) {
    a->x474 = 0;
    a->x476 = 0;
    d->x474 = 0;
    d->x476 = 0;
    if (fn_80060728(lbl_803CAB38)->x11 == 2) return;
    if (fn_80030CF4(a)->data == 0) return;
    if (fn_80030CF4(d)->data == 0) return;
    if (a->x47b || a->x47d) return;
    if (d->x47b || d->x47d) return;
    if (fn_801116B8(fn_80030CF4(a))->flags & 0x80) return;
    if (fn_801116B8(fn_80030CF4(d))->flags & 0x80) return;
    fn_80112A3C(wtype(a), wtype(d), &a->x474, &a->x476);
    fn_80112A3C(wtype(d), wtype(a), &d->x474, &d->x476);
    if (fn_801116B8(fn_80030CF4(a))->flags & 0x400) {
        neg(a);
        neg(d);
    }
    if (fn_801116B8(fn_80030CF4(d))->flags & 0x400) {
        neg(d);
        neg(a);
    }
}

void fn_8002B668(Battle* b) {
    fn_800282A0(b, &b->a, 0, 0);
    { int m = fn_801237EC(&b->b); fn_8002600C(b->log, 0xe, (s16)m); }
    fn_8002600C(b->log, 0xf, b->b.u.s114);
    fn_8002600C(b->log, 0x72, 0);
    b->f15e4 = 0;
    fn_80027D9C(b, &b->a, &b->b, 0x25, 0);
    lbl_803C8DA0.xa1 = 0;
    lbl_803C8DA0.xa2 = 0;
    lbl_803C8DA0.xa3 = 0;
    lbl_803C8DA0.xa4 = 0;
    lbl_803C8DA0.xa0 = 0;
    for (int i = 0; i < 0x20; i++) {
        lbl_803C8DA0.x0[i] = 0;
        lbl_803C8DA0.x20[i] = 0;
        lbl_803C8DA0.x60[i] = 0x3039;
    }
    lbl_803C8DA0.xa5 = -1;
    lbl_803C8DA0.xa6 = 0;
    lbl_803C8DA0.xc8 = 0;
    lbl_803C8DA0.xcc = 0;
    fn_8002C86C(b);
}

void fn_8002CD5C(Battle* b) {
    u32 f = b->f15ec;
    if (f & 1) return;
    if (b->b.u.ec == 0) return;
    if (!(f & 0x80000000)) {
        if (fn_8011B77C(b->a.u.u3f0->x12c, lbl_804CA5A0)) {
            b->f15ec |= 0x400000;
            goto A;
        }
        if (fn_8011B77C(b->b.u.u3f0->x12c, lbl_804CA5A0)) {
            b->f15ec |= 0x400000;
            goto B;
        }
        if (fn_8011B77C(b->a.u.u3f0->x12c, lbl_804CA5A4)) {
            b->f15ec |= 0x800000;
            goto A;
        }
        if (fn_8011B77C(b->b.u.u3f0->x12c, lbl_804CA5A4)) {
            b->f15ec |= 0x800000;
            goto B;
        }
    }
    {
        Vec3 pa = *(Vec3*)(b->a.u.u3f0->pad0 + 0x1c);
        Vec3 pb = *(Vec3*)(b->b.u.u3f0->pad0 + 0x1c);
        if (pa.x < pb.x) goto B;
    }
    goto A;
B:
    b->a.x48b = 1;
    b->b.x48b = 0;
    return;
A:
    b->a.x48b = 0;
    b->b.x48b = 1;
}

int fn_8002D218(Unit** v, Unit* u) {
    int c[3];
    s8 x = u->x102;
    s8 y = u->y103;
    int* o = c;
    int i;
    for (i = 0; i < 3; i++) {
        Unit* a = v[i];
        s8 ay = a->y103;
        s8 ax = a->x102;
        s8 ex, ey;
        Unit* n = v[(i + 1) % 3];
        ey = n->y103 - ay;
        ex = n->x102 - ax;
        *o++ = (s8)(y - ay) * ex - (s8)(x - ax) * ey;
    }
    if (c[0] == 0 && c[1] == 0) return 0;
    if (c[0] <= 0 && c[1] <= 0 && c[2] <= 0) return 1;
    if (c[0] >= 0 && c[1] >= 0 && c[2] >= 0) return 1;
    return 0;
}

#pragma use_lmw_stmw on
int fn_8002D348(Unit** v, int n, Unit* u) {
    switch (n) {
    case 2:
        break;
    case 3:
        return fn_8002D218(v, u);
    case 4: {
        Unit* t[4];
        int j = 0, k = 1;
        for (; k < n; k++) {
            int i;
            for (i = 0; i < n; i++) {
                if (k != i) t[j++] = v[i];
            }
            if (fn_8002D218(t, u)) {
                v[0] = t[0];
                v[1] = t[1];
                v[2] = t[2];
                return 1;
            }
        }
        break;
    }
    }
    return 0;
}
#pragma use_lmw_stmw reset
}
