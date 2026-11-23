#include "game/rB_8002E1C4/range.h"

int fn_8011EDC4(MapUnit* u, MapUnit* r);

void fn_8003C4F0(Functor* self, MapUnit* t)
{
    if (self->u->xf4 != t->xf4) return;
    if (t->x10c & 6) return;
    if (fn_8011EDC4(t, self->u->xf8) == 0) return;
    markT(t, self->u->xf8->xfc);
}

extern u8 lbl_803EC898[];
extern u8 lbl_803CB770[];
s16 fn_80115CD8(void* map, s8 x, s8 y);
void* fn_80066130(void* p, s8 x, s8 y, u8 n);

void fn_8003C584(Functor* self, s8 x, s8 y)
{
    u8* m = lbl_803EC898;
    int idx = x + (y << 6);
    if ((m + idx)[0xd] != 0) return;
    if ((m + idx)[0x300d] & 1) return;
    if (fn_80115CD8(m, x, y) > 30000) return;
    if ((s8)(m + idx)[0xf18e] != 0) return;
    if (fn_80066130(lbl_803CB770, x, y, 0xc) != 0) return;
    fn_800CFC50(lbl_803E7320, x, y, 0, 0);
}

void fn_8003C668(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) == 1) return;
    if (fn_8011EDC4(self->u, t) == 0) return;
    if (t->x10c & 6) return;
    markT(t, 0);
}

int fn_80121DEC(MapUnit* t);
int fn_8011ED4C(MapUnit* u, MapUnit* t);

void fn_8003C6FC(Functor* self, MapUnit* t)
{
    if (sameSide(self, t) != 1) return;
    if (fn_80121DEC(t) != 0) return;
    if (fn_8011ED4C(self->u, t) == 0) return;
    if (t->x10c & 6) return;
    markT(t, 0);
}

typedef struct FunctorN {
    void* vt;
    MapUnit* u;
    int n;
} FunctorN;

int fn_8011EE3C(MapUnit* u, MapUnit* t);
int fn_80118098(void* map, s8 x, s8 y);
void fn_801151BC(void* map, MapUnit* t);
int fn_80116DB8(void* map, s8 a, s8 b, s8 c, s8 d);

#pragma use_lmw_stmw on
/* shove / push check: the tiles behind the target must be free */
void fn_8003C7A0(FunctorN* self, MapUnit* t)
{
    u8* m;
    int cx, cy;
    s8 dx, dy, tx, ty;
    int i;
    if (fn_8011EE3C(self->u, t) == 0) return;
    if ((u8)fn_80118098(lbl_803EC898, t->x, t->y) == 0x73) return;
    tx = t->x;
    dx = tx - self->u->x;
    ty = t->y;
    dy = ty - self->u->y;
    fn_801151BC(lbl_803EC898, t);
    m = lbl_803EC898;
    cx = tx + dx;
    cy = ty + dy;
    for (i = 0; i < self->n; i++) {
        s8 x = cx;
        s8 y = cy;
        u8* p = (y << 6) + (m + x);
        if (p[0xd] != 0) return;
        if (p[0x300d] & 1) return;
        if (fn_80115CD8(m, x, y) > 30000) return;
        if (fn_80116DB8(m, tx, ty, cx, cy) == 0) return;
        if ((s8)p[0xf18e] != 0) return;
        if (fn_80066130(lbl_803CB770, cx, cy, 0xc) != 0) return;
        cx += dx;
        tx += dx;
        cy += dy;
        ty += dy;
    }
    markT(t, 0);
}
#pragma use_lmw_stmw reset

int fn_8011F1A8(MapUnit* u, MapUnit* t);

void fn_8003C924(Functor* self, MapUnit* t)
{
    if (fn_8011F1A8(self->u, t) == 0) return;
    if (sameSide(self, t) != 1) return;
    markT(t, 0);
}

typedef struct MapThing { s8 x; s8 y; u8 b2; u8 b3; u8 x4; } MapThing;

void fn_8003C9A8(Functor* self, s8 x, s8 y)
{
    MapThing* p = fn_80066130(lbl_803CB770, x, y, 4);
    if (p == 0) return;
    if (p->x4 == 0) return;
    fn_800CFC50(lbl_803E7320, p->x, p->y, 0, 4);
}
