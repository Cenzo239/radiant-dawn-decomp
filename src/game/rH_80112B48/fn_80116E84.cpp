/* Slope across a tile in a direction, 80116E84. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
static inline f32 H(Map* m, s8 x, s8 y, int k) {
    return m->scale * (f32)m->hgt[k + (x + (y << 6)) * 4];
}
static inline f32 Avg(Map* m, s8 x, s8 y, int a, int b) {
    return (H(m, x, y, a) + H(m, x, y, b)) / 2.0f;
}
#define R(a,b,c,d) {f32 p=Avg(m,x,y,a,b); f32 q=Avg(m,x,y,c,d); return p-q;}
f32 fn_80116E84(Map* m, s8 x, s8 y, int d) {
    switch (d) {
    case 8:
        R(0,1,2,3)
    case 4:
        R(2,3,0,1)
    case 1:
        R(0,2,1,3)
    case 2:
        R(1,3,0,2)
    }
    return 0.0f;
}
}
