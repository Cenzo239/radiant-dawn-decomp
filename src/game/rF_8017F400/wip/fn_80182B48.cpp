/* gmap: evaluate a curve at distance t (cubic Hermite between keys). */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct CKey { f32 x, y, z, tx, ty, tz; } CKey;
typedef struct CData { u8 pad[0x1c]; int len; int n; u8 pad24[8]; CKey* keys; } CData;
extern int fn_801D09F0(void);
static inline f32 H1(f32 u, f32 p0, f32 p1, f32 m0, f32 m1) {
    f32 u2 = u * u; f32 u3 = u2 * u;
    return p0 + ((-2.0f * u3 + 3.0f * u2) * (p1 - p0) + (u + (u3 - 2.0f * u2)) * m0 + (u3 - u2) * m1);
}
static inline f32 H2(f32 p0, f32 d, f32 m0, f32 m1, f32 u) {
    f32 u2 = u * u; f32 u3 = u2 * u; f32 h = -2.0f * u3 + 3.0f * u2; f32 h2 = u3 - u2; f32 h1 = u + (u3 - 2.0f * u2); return p0 + (h * d + h1 * m0 + h2 * m1);
}
static inline f32 H3(f32 u, f32 p0, f32 d, f32 m0, f32 m1) {
    f32 u2 = u * u; f32 u3 = u2 * u;
    return p0 + ((-2.0f * u3 + 3.0f * u2) * d + (u + (u3 - 2.0f * u2)) * m0 + (u3 - u2) * m1);
}
static inline void HV(CKey* a, CKey* b, f32 u, f32* out) {
    f32 u2 = u * u; f32 u3 = u2 * u;
    f32 h = -2.0f * u3 + 3.0f * u2; f32 h2 = u3 - u2; f32 h1 = u + (u3 - 2.0f * u2);
    out[0] = a->x + (h * (b->x - a->x) + h1 * a->tx + h2 * b->tx);
    out[1] = a->y + (h * (b->y - a->y) + h1 * a->ty + h2 * b->ty);
    out[2] = a->z + (h * (b->z - a->z) + h1 * a->tz + h2 * b->tz);
}
int fn_80182B48(f32 t, void* self, CData* d, f32* out) {
    /*P*/
    f32 x;
    f32 cx;
    int n;
    int i;
    f32 step;
    CKey* a;
    CKey* b;
    f32 u;
    f32 u2;
    f32 u3;
    f32 h;
    f32 h2;
    f32 h1;
/*E*/
    if (t < 0.0f) return 0;
    n = d->n;
    i = 0;
    step = (f32)d->len / (f32)(n - 1);
    for (; i < n; i++) {
        if ((f32)(i + 1) * step > t) break;
    }
    if (i == n) return 0;
    a = &d->keys[i];
    b = &d->keys[i + 1];
    cx = 304.0f;
    u = (t - step * (f32)i) / step;
    x = H2(a->x, b->x - a->x, a->tx, b->tx, u); out[0] = x; out[1] = H2(a->y, b->y - a->y, a->ty, b->ty, u); out[2] = H2(a->z, b->z - a->z, a->tz, b->tz, u);
    if (fn_801D09F0()) x = 0.7638191f * (x - cx) + cx;
    out[0] = x;
    return 1;
}
}
