#include "game/rB_8002E1C4/range.h"

void fn_8003B8EC(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) == 1) return;
    {
        int hp = t->x114;
        if (hp >= fn_801237EC(t) && fn_80108F68(&t->x110) == 0) return;
    }
    markT(t, 0);
}

extern void* lbl_804CA4E8;

void fn_8003B988(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) == 1) return;
    if (fn_8011B77C(t->x12c, lbl_804CA4E8) == 0) return;
    markT(t, 0);
}

extern void* lbl_804CA4F8;
extern void* lbl_804CA4FC;

void fn_8003BA04(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) != 1) return;
    if (fn_8011B77C(t->x12c, lbl_804CA4F8) != 0) return;
    if (fn_8011B77C(t->x12c, lbl_804CA4FC) != 0) return;
    markT(t, 0);
}

void fn_8003BA94(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) == 1) return;
    markT(t, 0);
}

void fn_8003BAFC(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) != 0) return;
    if (!(t->x10c & 1)) return;
    markT(t, 0);
}

void fn_8003BB6C(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) != 1) return;
    if (fn_8011B77C(t->x12c, lbl_804CA4F8) != 0) return;
    if (fn_8011B77C(t->x12c, lbl_804CA4FC) != 0) return;
    markT(t, 0);
}

void fn_8003BBFC(Functor* self, MapUnit* t)
{
    int i;
    Item* s;
    if (sameSide(self, t) == 1) return;
    for (i = 0; i < 7; i++) {
        s = &t->items[i];
        if (s == 0) return;
        if (s->data == 0) return;
        if (fn_80111F5C(s)) {
            markT(t, i);
            return;
        }
    }
}

void fn_8003BCB4(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) == 1) return;
    markT(t, 0);
}

typedef struct MapPos { u8 x0; u8 x; u8 y; } MapPos;
#if TARGET_PC
FE10_PROTO int fn_800A05B0(int id, s8 x, s8 y);
#else
void* fn_800A05B0(int id, s8 x, s8 y);
#endif
void* fn_8013B9A8(void);
MapPos* fn_80135800(void* p, s8 x, s8 y, u32 mask, int n);
void* fn_80066130(void* p, s8 x, s8 y, u8 n);
extern u8 lbl_803CB770[];

void fn_8003BD1C(Functor* self, s8 x, s8 y)
{
    void* p;
    MapPos* q;
    if (fn_800A05B0(0x3b, x, y) == 0) return;
    p = fn_8013B9A8();
    if (p != 0) {
        q = fn_80135800(p, x, y, 0x10000000, 0);
        if (q != 0) {
            x = q->x;
            y = q->y;
        }
    }
    if (fn_80066130(lbl_803CB770, x, y, 6) == 0) return;
    fn_800CFC50(lbl_803E7320, x, y, 0, 0);
}

void fn_8003BDDC(Functor* self, s8 x, s8 y)
{
    void* p;
    MapPos* q;
    if (fn_800A05B0(0x37, x, y) == 0) return;
    p = fn_8013B9A8();
    if (p != 0) {
        q = fn_80135800(p, x, y, 0x10000000, 0);
        if (q != 0) {
            x = q->x;
            y = q->y;
        }
    }
    if (fn_80066130(lbl_803CB770, x, y, 6) != 0) return;
    fn_800CFC50(lbl_803E7320, x, y, 0, 0);
}

typedef struct FunctorF {
    void* vt;
    u8 x4;
} FunctorF;

void fn_8003BE9C(FunctorF* self, s8 x, s8 y)
{
    if ((self->x4 & 2) && fn_800A05B0(0xb, x, y) != 0)
        fn_800CFC50(lbl_803E7320, x, y, 0, 2);
    if ((self->x4 & 1) && fn_800A05B0(0xc, x, y) != 0)
        fn_800CFC50(lbl_803E7320, x, y, 0, 1);
}

int fn_80120928(MapUnit* u, MapUnit* t);

void fn_8003BF5C(Functor* self, MapUnit* t)
{
    u8 v;
    s8 y;
    s8 x;
    if (sameSide(self, t) == 1) return;
    v = t->xfc;
    y = t->y;
    x = t->x;
    fn_800CFC50(lbl_803E7320, x, y, v, (u8)fn_80120928(self->u, t));
}

int fn_8011F1A8(MapUnit* u, MapUnit* t);

void fn_8003BFF0(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) != 1) return;
    if (fn_8011F1A8(self->u, t) == 0) return;
    markT(t, 0);
}

void fn_8003C078(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) == 1) return;
    if (fn_80108F68(&t->x110) == 0) return;
    markT(t, 0);
}

f32 fn_801072E4(MapUnit* t);

void fn_8003C0F0(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) == 1) return;
    {
        int hp = t->x114;
        if (hp == fn_801237EC(t)) {
            u16 v = t->x37c;
            if ((f32)v == fn_801072E4(t)) return;
        }
    }
    markT(t, 0);
}

void fn_8003C1A8(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) == 1) return;
    {
        int hp = t->x114;
        if (hp == fn_801237EC(t)) return;
    }
    markT(t, 0);
}

int fn_8011EFC8(MapUnit* u, MapUnit* t);
int fn_8012BCB0(MapUnit* t);
int fn_8011F0E0(MapUnit* u, Item* s);

void fn_8003C234(Functor* self, MapUnit* t)
{
    int i;
    Item* s;
    if (sameSide(self, t) != 1) return;
    if (fn_8011EFC8(self->u, t) == 0) return;
    if (fn_8012BCB0(t) != 0) return;
    for (i = 0; i < 7; i++) {
        s = &t->items[i];
        if (s == 0 || s->data == 0) return;
        if (fn_8011F0E0(self->u, s)) break;
    }
    markT(t, 0);
}

#if TARGET_PC
FE10_PROTO int fn_8011EF14(MapUnit* t, void *);
#else
int fn_8011EF14(MapUnit* t, int n);
#endif
void* fn_8012E390(MapUnit* u);
int fn_8012E9B4(MapUnit* u, MapUnit* t);
int fn_8012E8BC(MapUnit* u, s8 a);
int fn_8012E618(MapUnit* u, s8 a, u8 b);

void fn_8003C320(Functor* self, MapUnit* t)
{
    void* j;
    int a;
    int b;
    if (fn_8011EF14(t, 0) == 0) return;
    j = t->xec;
    if (fn_8012E390(self->u) != j) return;
    a = fn_8012E9B4(self->u, t);
    b = (u8)fn_8012E8BC(self->u, a);
    if (b < 1) return;
    if (fn_8012E618(self->u, a, b) != 0) return;
    markT(t, b);
}

typedef struct RangeState { MapUnit* unit; u32 x4; u8 pad[0x130 - 8]; } RangeState;
extern RangeState lbl_803CA870;
int fn_8009FF74(RangeState* s);

void fn_8003C3F0(Functor* self, MapUnit* t)
{
    if (fn_8011EF14(t, 0) == 0) return;
    lbl_803CA870.x4 = (u32)t;
    if (fn_8009FF74(&lbl_803CA870) == 0) return;
    markT(t, 0);
}

int fn_8011EDC4(MapUnit* u, MapUnit* r);

void fn_8003C468(Functor* self, MapUnit* t)
{
    if (self->u->xf4 != t->xf4) return;
    if (!(t->x10c & 2)) return;
    if (t->x10c & 0x100000) return;
    if (fn_8011EDC4(self->u, t->xf8) == 0) return;
    markT(t, t->xf8->xfc);
}
