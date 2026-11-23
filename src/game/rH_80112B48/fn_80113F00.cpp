/* Map surface height at a point, first height layer, 80113F00. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern void fn_8011843C(Map*, Vec*, Vec*, int, int, f32, f32);
extern void fn_8031356C(Vec*, Vec*, Vec*);
static inline f32 H(Map* m, s8 x, s8 y, int k) {
    return m->scale * (f32)m->hgt[(x + (y << 6)) * 4 + k];
}
static inline f32 HA(Map* m, s8 x, s8 y) {
    int i;
    if (x < 0 || x >= m->w || y < 0 || y >= m->h) {
        return -100.0f;
    }
    i = (x + (y << 6)) * 4;
    return m->scale * (f32)((m->hgt[i] + m->hgt[i + 1] + m->hgt[i + 2] + m->hgt[i + 3]) >> 2);
}
f32 fn_80113F00(Map* m, f32 fx, f32 fy) {
    /*P*/
    f32 dx;
    f32 dy;
    f32 h;
    int ix;
    int iy;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
/*E*/
    Vec p;
    Vec n;
    ix = (int)fx;
    iy = (int)fy;
    dx = fx - (f32)(s8)ix;
    dy = fy - (f32)(s8)iy;
    if (m->bits[((s8)ix + ((s8)iy << 6)) >> 3] & (1 << (ix & 7))) {
        a = H(m, ix, iy, 0);
        b = H(m, ix, iy, 1);
        c = H(m, ix, iy, 2);
        d = H(m, ix, iy, 3);
        { f32 x0 = a * (1.0f - dx) + b * dx; f32 x1 = c * (1.0f - dx) + d * dx; return x0 * (1.0f - dy) + x1 * dy; }
    }
    h = HA(m, ix, iy);
    fn_8011843C(m, &p, &n, 0, 0, fx, fy);
    fn_8031356C(&p, &n, &p);
    { f32 e = -(p.z * h + (p.x * (0.5f + (f32)(s8)ix) + p.y * (0.5f + (f32)(s8)iy))); return -(e + (p.x * fx + p.y * fy)) / p.z; }
}
}
