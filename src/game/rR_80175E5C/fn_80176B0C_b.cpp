/* fn_80176B0C: 2D distance between (x0,y0) and (x1,y1); 0 when the points coincide.
 * Proposed name: Distance2D. fn_80295CF0 is sqrt (f64). Exact (round 22): the sqrt
 * call must go through a float-returning inline, which puts the result straight in f1. */
#include "game/rR_80175E5C/types.h"
extern "C" {
f64 fn_80295CF0(f64);
}
static inline f32 sq(f32 x) { return (f32)fn_80295CF0(x); }
extern "C" {
f32 fn_80176B0C(f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 dy = y1 - y0;
    f32 dx = x1 - x0;
    f32 d = dx * dx + dy * dy;
    if (0.0f == d) return 0.0f; return sq(d);
}
}
