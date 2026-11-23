/* NOT MATCHING, not compiled. fn_80113F00: 103 words: first draft; not a paired-single function. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern void fn_8011843C(Map*, Vec*, Vec*, int, int, f32, f32);
extern void fn_8031356C(Vec*, Vec*, Vec*);
static inline f32 H(Map* m, s8 x, s8 y, int k) {
    return m->scale * (f32)m->hgt[k + (x + (y << 6)) * 4];
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
    int ix;
    int iy;
    f32 h;
    /*E*/
    Vec p;
    Vec n;
    f32 dx, dy;
    ix = (int)fx;
    iy = (int)fy;
    dx = fx - (f32)(s8)ix;
    dy = fy - (f32)(s8)iy;
    if (m->bits[((s8)ix + ((s8)iy << 6)) >> 3] & (1 << (ix & 7))) {
        return (H(m, ix, iy, 0) * (1.0f - dx) + H(m, ix, iy, 1) * dx) * (1.0f - dy) + (H(m, ix, iy, 2) * (1.0f - dx) + H(m, ix, iy, 3) * dx) * dy;
    }
    h = HA(m, ix, iy);
    fn_8011843C(m, &p, &n, 0, 0, fx, fy);
    fn_8031356C(&p, &n, &p);
    return -(p.x * fx + p.y * fy + -(p.z * h) + (p.x * (0.5f + (f32)(s8)ix) + p.y * (0.5f + (f32)(s8)iy))) / p.z;
}
}
