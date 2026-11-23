/* Camera key interpolation, 8012FFD0. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
struct Ev { u8 kind; s16 key; Vec v; u32 d; };
extern f32 fn_8001EFE4(f32, f32, f32, f32, f32);
Vec fn_8012FFD0(Ev* e, int n, f32 t) {
    Ev* a;
    Ev* b;
    Ev* q;
    f32 s;
    int i;
    Vec r = {0.0f, 0.0f, 0.0f};
    if (n == 0) {
        return r;
    }
    q = e;
    for (i = 0; i < n; i++, q++) {
        if ((f32)q->key >= t) {
            if (i == 0) {
                r.x = q->v.x;
                r.y = q->v.y;
                r.z = q->v.z;
            } else {
                s16 p = q[-1].key; f32 d = (f32)(q->key - p); f32 w = t - (f32)p;
                if (0.0f == d) {
                    s = 1.0f;
                } else {
                    s = w / d;
                }
                if (i >= 2) {
                    a = q - 2;
                } else {
                    a = q - 1;
                }
                if (i < n - 1) {
                    b = q + 1;
                } else {
                    b = q;
                }
                r.x = fn_8001EFE4(a->v.x, q[-1].v.x, q->v.x, b->v.x, s);
                r.y = fn_8001EFE4(a->v.y, q[-1].v.y, q->v.y, b->v.y, s);
                r.z = fn_8001EFE4(a->v.z, q[-1].v.z, q->v.z, b->v.z, s);
            }
            return r;
        }
        
    }
    r.x = e[n - 1].v.x;
    r.y = e[n - 1].v.y;
    r.z = e[n - 1].v.z;
    return r;
}
}
