/* Colour fade process step: optional delay, eased lerp of the current colour, end when the target is reached (fn_8017EE1C). */
#include "game/rR_80175E5C/types.h"
struct C4 { u8 r, g, b, a; };
struct Fade {
    u8 pad0[0x30];
    s16 dur;
    s16 delay;
    s16 t;
    C4 cur;
    C4 to;
    C4 from;
    C4 max;
};
extern "C" {
f32 fn_8001EBC8(int, f32, f32, f32, f32);
f32 fn_8001EF30(f32, f32, f32, f32);
void* fn_80010960();
void fn_80010B8C(void*, C4);
void fn_80010AE4();
void fn_80083B78(void*);
void fn_80081A90(void*);
}
static inline C4 Lerp(C4 from, C4 to, f32 k) {
    C4 c;
    if (k < 0.0f) {
        k = 0.0f;
    }
    if (k > 1.0f) {
        k = 1.0f;
    }
    c.r = (int)fn_8001EF30(from.r, to.r, 1.0f, k);
    c.g = (int)fn_8001EF30(from.g, to.g, 1.0f, k);
    c.b = (int)fn_8001EF30(from.b, to.b, 1.0f, k);
    c.a = (int)fn_8001EF30(from.a, to.a, 1.0f, k);
    return c;
}
static inline f32 Ease(f32 t, f32 n) {
    return fn_8001EBC8(2, 0.0f, 1.0f, n, t);
}
static inline BOOL Eq(C4 a, C4 b) {
    if (a.r != b.r) return 0;
    if (a.g != b.g) return 0;
    if (a.b != b.b) return 0;
    return a.a == b.a;
}
extern "C" void fn_8017EE1C(Fade* o) {
    if (o->delay > 0) {
        o->delay--;
        return;
    }
    o->t++;
    if (o->t >= o->dur) {
        o->t = o->dur;
    }
    o->cur = Lerp(o->from, o->to, Ease(o->t, o->dur));
    void* g = fn_80010960();
    fn_80010B8C(g, o->cur);
    fn_80010AE4();
    if (o->t >= o->dur) {
        if (Eq(o->to, o->max)) {
            fn_80081A90(o);
        } else {
            fn_80083B78(o);
        }
    }
}
