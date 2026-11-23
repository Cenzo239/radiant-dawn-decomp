/* fn_8001F1D4: 52 of 193 words differ, float registers and FP scheduling in the blend; integer registers are right. */
#include "game/rA_800068A0/types.h"
/* Catmull-Rom subdivision of a Vec polyline. Returns the number of points written. */
extern "C" {
typedef struct Vec { f32 x, y, z; } Vec;
extern void fn_8001F0A4(Vec* a, Vec* b, Vec* c, Vec* d);
static inline void put(Vec* o, int k, Vec* in){ o[k].x = in->x; o[k].y = in->y; o[k].z = in->z; }
static inline void put2(Vec* q, Vec* in){ q->x = in->x; q->y = in->y; q->z = in->z; }
static inline f32 ev(f32 b, f32 c, f32 a, f32 d, f32 h00, f32 h01, f32 h10, f32 h11) {
    return h00 * b + h01 * c + h10 * (0.5 * (c - a)) + h11 * (0.5 * (d - b));
}
int fn_8001F1D4(Vec* in0, Vec* out, int n, int seg, int smooth) {
/*P*/
    Vec* p0;
    Vec* in;
    f32 t;
    Vec* p2;
    f32 h00;
    f32 t1;
    f32 h10;
    int i;
    int k;
    Vec* o;
    Vec* p3;
    f32 h01;
    f32 h11;
    int j;
    f32 u;
/*E*/
    f32 dt;
    Vec d;
    Vec c;
    Vec b;
    Vec a;
    in = in0;
    k = 0;
    dt = 1.0f / (f32)seg;
    { Vec* q = out; q += k++; q->x = in->x; q->y = in->y; q->z = in->z; }
    i = 0;
    for (; i < n - 1; i++, in++) {
        p0 = in;
        p2 = in;
        p3 = in;
        if (i > 0) p0 = in - 1;
        if (i < n - 1) {
            p2 = in + 1;
            p3 = p2;
        }
        if (i < n - 2) p3 = p3 + 1;
        a.x = p0->x;
        a.y = p0->y;
        a.z = p0->z;
        b.x = in->x;
        b.y = in->y;
        b.z = in->z;
        c.x = p2->x;
        c.y = p2->y;
        c.z = p2->z;
        d.x = p3->x;
        d.y = p3->y;
        d.z = p3->z;
        if (smooth != 0) fn_8001F0A4(&a, &b, &c, &d);
        o = &out[k];
        for (j = 1; j < seg; j++, o++) {
            t = (f32)j * dt;
            t1 = t - 1.0f;
            h01 = (3.0f - 2.0f * t) * (t * t);
            u = 1.0f - t;
            h00 = (2.0f * t + 1.0f) * (t1 * t1);
            h10 = t * (u * u);
            h11 = t * (t1 * t);
            k++;
            o->x = ev(b.x, c.x, a.x, d.x, h00, h01, h10, h11);
            o->y = ev(b.y, c.y, a.y, d.y, h00, h01, h10, h11);
            o->z = ev(b.z, c.z, a.z, d.z, h00, h01, h10, h11);
        }
        out[k].x = c.x;
        out[k].y = c.y;
        out[k].z = c.z;
        k++;
    }
    return k;
}
}
