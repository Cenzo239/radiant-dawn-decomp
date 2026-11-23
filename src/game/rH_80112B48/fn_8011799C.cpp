/* Tile bounds tests, tile position to world position, 8011799C, 80117A0C, 80118380. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
static inline BOOL In(Map* m, s8 x, s8 y) {
    if (x < m->x0 || x >= m->x1 || y < m->y0 || y >= m->y1) return 0;
    return 1;
}
BOOL fn_8011799C(Map* m, s8 x, s8 y) {
    if (x < m->x0) return 0;
    if (x >= m->x1) return 0;
    if (y < m->y0) return 0;
    return y < m->y1;
}

static inline BOOL Ins(Map* m, s8 x, s8 y) {
    if (x < m->x0) return 0;
    if (x >= m->x1) return 0;
    if (y < m->y0) return 0;
    return y < m->y1;
}
BOOL fn_80117A0C(Map* m, s8 x, s8 y) {
    return Ins(m, x, y) == 0;
}
extern f32 fn_801142F0(Map*, f32, f32);
extern void fn_802549C4(void*, Vec*, f32);
void fn_80118380(Map* m, s8 x, s8 y, void* o) {
    Vec v;
    Vec r;
    v.x = 0.5f + (f32)x; v.y = 0.5f + (f32)y; v.z = fn_801142F0(m, (f32)x, (f32)y); r = v;
    fn_802549C4(o, &r, 0.0f);
}
}
