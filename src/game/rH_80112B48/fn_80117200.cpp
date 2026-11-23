/* Height step between a tile and its neighbour across an edge, 80117200. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
static inline f32 H2(Map* m, s8 x, s8 y, int k) {
    if (x < 0 || x >= m->w || y < 0 || y >= m->h) {
        return -100.0f;
    }
    return m->scale * (f32)m->hgt2[(x + (y << 6)) * 4 + k];
}
static inline f32 Avg(Map* m, s8 x, s8 y, int i, int j) { f32 p = H2(m, x, y, i); f32 q = H2(m, x, y, j); return (p + q) / 2.0f; }
static inline f32 Avg2(Map* m, s8 x, s8 y, int i, int j) { return (H2(m, x, y, i) + H2(m, x, y, j)) / 2.0f; }
#define RET(xx, yy, i, j, k, l) { f32 a = Avg(m, xx, yy, i, j); return a - Avg2(m, x, y, k, l); }
f32 fn_80117200(Map* m, int x, int y, int dir) {
    switch (dir) {
    case 8:
        RET(x, (s8)y - 1, 2, 3, 0, 1)
    case 4:
        RET(x, (s8)y + 1, 0, 1, 2, 3)
    case 1:
        RET((s8)x - 1, y, 1, 3, 0, 2)
    case 2:
        RET((s8)x + 1, y, 0, 2, 1, 3)
    }
    return 0.0f;
}
}
