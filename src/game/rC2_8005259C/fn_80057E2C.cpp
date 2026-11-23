#include "game/rC2_8005259C/base.h"
/* Camera arc setup: control point above the midpoint, step count from distance. */
struct Nd { u8 p[4]; f32 x, y, z; };
struct Arc {
    u8 pad[0x30];
    Nd* n;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 cx, cy, cz;
    s8 tx, ty;
    s16 t;
    s16 end;
};
extern "C" {
extern u8 lbl_803EC898[];
f32 fn_80113F00(void*, f32, f32);
f64 fn_80295CF0(f64);
void fn_80057E2C(Arc* a) {
    /*P*/
    f32 cx; f32 cy; f32 dy; f32 dx; f32 d; f32 h; f32 r; f32 l1; f32 k; f32 byy; f32 bxx; f32 cy2; f32 ay2; f32 cz; f32 sx; f32 sz; f32 ez; f32 h2; f32 az2; f32 sy; f32 half; f32 cx2; f32 ax2; f32 ex; f32 ey; 
    /*E*/
    Nd* n = a->n;
    f32 x = n->x;
    a->ax = x;
    f32 y = n->y;
    a->ay = y;
    a->az = fn_80113F00(lbl_803EC898, x, y);
    a->cx = a->tx + 0.5f;
    a->cy = a->ty + 0.5f;
    a->cz = fn_80113F00(lbl_803EC898, a->tx, a->ty);
    ay2 = a->ay;
    h2 = a->cz;
    cy2 = a->cy;
    ax2 = a->ax;
    cx2 = a->cx;
    az2 = a->az;
    ey = cy2 - ay2;
    sy = ay2 + cy2;
    ex = cx2 - ax2;
    sz = az2 + h2;
    sx = ax2 + cx2;
    ez = h2 - az2;
    half = 0.5f;
    cx = half * sx;
    cy = half * sy;
    cz = half * sz;
    l1 = fn_80295CF0(ez * ez + (ex * ex + ey * ey));
    a->t = 0;
    a->end = (s16)(int)((12.0f * (32.0f - l1) + 48.0f * l1) / 32.0f);
    dy = -(a->cy - cy);
    dx = a->cx - cx;
    d = fn_80295CF0(dy * dy + dx * dx);
    h = d;
    if (d > 2.0f) h = 2.0f;
    r = h / d;
    dy *= r;
    dx *= r;
    k = 2.0f * h;
    k = cz - k;
    bxx = cx + dy;
    byy = cy + dx;
    a->bz = k;
    a->bx = bxx;
    a->by = byy;
    if (a->end > 0x30) a->end = 0x30;
}
}
