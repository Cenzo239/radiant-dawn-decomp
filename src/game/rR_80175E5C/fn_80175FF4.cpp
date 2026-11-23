/* fn_80175FF4: exact (round 18). Perp is an inline inferred from the two identical blocks and their stack slots. */
/* fn_80175FF4: closest point on the line a..b to the line p..d (written to out); returns whether that point
   lies inside both segments. */
#include "game/rR_80175E5C/types.h"
struct Vec { f32 x, y, z; };
extern "C" {
void fn_80313484(Vec*, Vec*, Vec*);   /* sub */
void fn_80313460(Vec*, Vec*, Vec*);   /* add */
void fn_8031356C(Vec*, Vec*, Vec*);   /* cross */
f32 fn_80313508(Vec*);                      /* length */
void fn_803134C4(Vec*, Vec*);               /* normalise */
f32 fn_8031354C(Vec*, Vec*);          /* dot */
void fn_803134A8(Vec*, Vec*, f32);          /* scale */
}
static inline f32 Perp(Vec* e, Vec* o, Vec* q, Vec* n) {
    Vec t;
    Vec b;
    Vec a;
    f32 r;
    f32 len;
    fn_80313484(e, o, &a);
    fn_80313484(q, o, &b);
    fn_8031356C(&a, &b, &b);
    fn_8031356C(&a, &b, n);
    len = fn_80313508(n);
    r = 0.0f;
    if (r == len) return r;
    fn_803134C4(n, n);
    fn_80313484(o, q, &t);
    return fn_8031354C(n, &t);
}
extern "C" BOOL fn_80175FF4(Vec* a, Vec* b, Vec* p, Vec* d, Vec* out) {
    Vec n1;
    Vec n2;
    Vec c;
    f32 d1;
    f32 d2;
    f32 l;
    d1 = Perp(d, p, a, &n1);
    fn_80313484(d, p, &c);
    fn_80313460(b, &c, &c);
    d2 = Perp(&c, b, a, &n2);
    if (0.0f == d2) {
        *out = *a;
    } else {
        d1 = d1 / d2;
        if (fn_8031354C(&n1, &n2) < 0.0f) {
            d1 *= -1.0f;
        }
        fn_80313484(b, a, out);
        fn_803134A8(out, out, d1);
        fn_80313460(out, a, out);
    }
    fn_80313484(b, out, &n1);
    fn_80313484(b, a, &n2);
    if (fn_8031354C(&n1, &n2) < 0.0f) return 0;
    l = fn_80313508(&n2);
    if (fn_80313508(&n1) > l) return 0;
    fn_80313484(d, out, &n1);
    fn_80313484(d, p, &n2);
    if (fn_8031354C(&n1, &n2) < 0.0f) return 0;
    l = fn_80313508(&n2);
    return !(fn_80313508(&n1) > l);
}
