/* fn_80020F04: near miss, about 44 words of float registers only. In the z test the target loads 0.0f into f0 first and z into f1, ours has them the other way, and that shifts every later float by one. */
#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct Vec { f32 x, y, z; } Vec;
extern void* fn_8000FB94(void);
extern void fn_803133E8(void* m, const Vec* a, Vec* b);
static inline int inside(Vec* v) {
    fn_803133E8(fn_8000FB94(), v, v);
    if (v->x * v->x < 1.0f && v->y * v->y < 1.0f && v->z > -1.0f && v->z < 0.0f) {
        return 0;
    }
    return 1;
}
int fn_80020F04(const Vec* a, const Vec* b) {
    Vec c[8];

    f32 miny;
    Vec* p;
    f32 maxx;
    f32 maxy;
    f32 x;
    f32 minx;
    f32 zero;
    f32 z;
    int i;
    f32 y;

    c[0].x = a->x; c[0].y = a->y; c[0].z = a->z;
    if (!inside(&c[0])) return 0;
    c[1].x = b->x; c[1].y = a->y; c[1].z = a->z;
    if (!inside(&c[1])) return 0;
    c[2].x = b->x; c[2].y = b->y; c[2].z = a->z;
    if (!inside(&c[2])) return 0;
    c[3].x = a->x; c[3].y = b->y; c[3].z = a->z;
    if (!inside(&c[3])) return 0;
    c[4].x = a->x; c[4].y = a->y; c[4].z = b->z;
    if (!inside(&c[4])) return 0;
    c[5].x = b->x; c[5].y = a->y; c[5].z = b->z;
    if (!inside(&c[5])) return 0;
    c[6].x = b->x; c[6].y = b->y; c[6].z = b->z;
    if (!inside(&c[6])) return 0;
    c[7].x = a->x; c[7].y = b->y; c[7].z = b->z;
    if (!inside(&c[7])) return 0;
    zero = 0.0f;
    if (!((z = c[0].z) < zero || (z = c[1].z) < zero || (z = c[2].z) < zero || (z = c[3].z) < zero || (z = c[4].z) < zero || (z = c[5].z) < zero || (z = c[6].z) < zero || (z = c[7].z) < zero)) {
        return 1;
    }
    minx = 10000.0f;
    miny = 10000.0f;
    maxx = -10000.0f;
    maxy = -10000.0f;
    p = c;
    for (i = 0; i < 8; p++, i++) {
        x = p->x;
        y = p->y;
        if (p->z > 0.0f) {
            x *= -1.0f;
            y *= -1.0f;
        }
        if (minx > x) minx = x;
        if (miny > y) miny = y;
        if (maxx < x) maxx = x;
        if (maxy < y) maxy = y;
    }
    if (minx < -1.0f && maxx > 1.0f && miny < -1.0f && maxy > 1.0f) return 0;
    if (minx * minx < 1.0f && miny * miny < 1.0f) return 0;
    if (maxx * maxx < 1.0f && miny * miny < 1.0f) return 0;
    if (maxx * maxx < 1.0f && maxy * maxy < 1.0f) return 0;
    if (minx * minx < 1.0f && maxy * maxy < 1.0f) return 0;
    if (minx < -1.0f && maxx > 1.0f) {
        if (miny * miny < 1.0f) return 0;
        if (maxy * maxy < 1.0f) return 0;
    }
    if (miny < -1.0f && maxy > 1.0f) {
        if (minx * minx < 1.0f) return 0;
        if (maxx * maxx < 1.0f) return 0;
    }
    return 1;
}
}
