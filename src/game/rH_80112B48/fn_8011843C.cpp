/* Two edge vectors of the map triangle under a point, 8011843C. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
static inline f32 H1(Map* m, s8 x, s8 y, int k) {
    return m->scale * (f32)m->hgt[(x + (y << 6)) * 4 + k];
}
static inline f32 H2(Map* m, s8 x, s8 y, int k) {
    if (x < 0 || x >= m->w || y < 0 || y >= m->h) {
        return -100.0f;
    }
    return m->scale * (f32)m->hgt2[(x + (y << 6)) * 4 + k];
}
static inline f32 A1(Map* m, s8 x, s8 y) {
    int i;
    if (x < 0 || x >= m->w || y < 0 || y >= m->h) {
        return -100.0f;
    }
    i = (x + (y << 6)) * 4;
    return m->scale * (f32)((m->hgt[i] + m->hgt[i + 1] + m->hgt[i + 2] + m->hgt[i + 3]) >> 2);
}
static inline f32 A2(Map* m, s8 x, s8 y) {
    int i;
    if (x < 0 || x >= m->w || y < 0 || y >= m->h) {
        return -100.0f;
    }
    i = (x + (y << 6)) * 4;
    return m->scale * (f32)((m->hgt2[i] + m->hgt2[i + 1] + m->hgt2[i + 2] + m->hgt2[i + 3]) >> 2);
}
#define TOP(m) (*(f32*)(m)->pad1D428)
void fn_8011843C(Map* m, Vec* p, Vec* n, int layer, int clamp, f32 fx, f32 fy) {
    /*P*/
    int ix;
    f32 dy;
    f32 v;
    int d;
    f32 dx;
    int iy;
/*E*/
    f32 h[5];
    ix = (int)fx;
    iy = (int)fy;
    v = layer ? H2(m, ix, iy, 0) : H1(m, ix, iy, 0);
    if (clamp && v > TOP(m)) v = TOP(m);
    h[0] = v;
    v = layer ? H2(m, ix, iy, 1) : H1(m, ix, iy, 1);
    if (clamp && v > TOP(m)) v = TOP(m);
    h[1] = v;
    v = layer ? H2(m, ix, iy, 2) : H1(m, ix, iy, 2);
    if (clamp && v > TOP(m)) v = TOP(m);
    h[2] = v;
    v = layer ? H2(m, ix, iy, 3) : H1(m, ix, iy, 3);
    if (clamp && v > TOP(m)) v = TOP(m);
    h[3] = v;
    v = layer ? A2(m, ix, iy) : A1(m, ix, iy);
    if (clamp && v > TOP(m)) v = TOP(m);
    h[4] = v;
    dx = fx - (f32)(s8)(int)fx;
    dy = fy - (f32)(s8)(int)fy;
    if (dx > dy) {
        d = dy < 1.0f - dx ? 8 : 2;
    } else {
        d = dy < 1.0f - dx ? 1 : 4;
    }
    switch (d) {
    case 8:
        p->x = 0.5f; p->y = -0.5f; p->z = h[1] - h[4];
        n->x = -0.5f; n->y = -0.5f; n->z = h[0] - h[4];
        break;
    case 2:
        p->x = 0.5f; p->y = 0.5f; p->z = h[3] - h[4];
        n->x = 0.5f; n->y = -0.5f; n->z = h[1] - h[4];
        break;
    case 4:
        p->x = -0.5f; p->y = 0.5f; p->z = h[2] - h[4];
        n->x = 0.5f; n->y = 0.5f; n->z = h[3] - h[4];
        break;
    case 1:
        p->x = -0.5f; p->y = -0.5f; p->z = h[0] - h[4];
        n->x = -0.5f; n->y = 0.5f; n->z = h[2] - h[4];
        break;
    default:
        p->x = -0.5f; p->y = -0.5f; p->z = 0.0f;
        n->x = 0.5f; n->y = 0.5f; n->z = 0.0f;
        break;
    }
}
}
