/* fn_8017E470 (round 17): 8 of 347 words differ. Material colour fade step, two channels lerped like fn_8017EE1C.
   Only the stack slots of the first Eq() call's two by-value colours are swapped (to wants 0x1C, max 0x18); the second call is right.
   Done1..Done5/EqR/EqW are unused experiments. Not compiled. */
#include "game/rR_80175E5C/types.h"
struct C4 { u8 r, g, b, a; };
struct MFade {
    u8 pad0[0x30];
    s16 id;
    s16 dur;
    s16 delay;
    s16 t;
    C4 cur;
    C4 to;
    C4 from;
    C4 max;
    C4 cur2;
    C4 to2;
    C4 from2;
    C4 max2;
};
extern "C" {
f32 fn_8001EBC8(int, f32, f32, f32, f32);
f32 fn_8001EF30(f32, f32, f32, f32);
u8* fn_80010BB0(int);
u8* fn_80010DA4(u8*, int);
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
    if (b.r != a.r) return 0;
    if (b.g != a.g) return 0;
    if (b.b != a.b) return 0;
    return b.a == a.a;
}
static inline BOOL EqR(C4 b, C4 a) {
    if (b.r != a.r) return 0;
    if (b.g != a.g) return 0;
    if (b.b != a.b) return 0;
    return b.a == a.a;
}
static inline BOOL EqW(C4 a, C4 b) {
    return Eq(a, b);
}
static inline BOOL Done5(MFade* o) {
    BOOL d = Eq(o->max, o->to);
    if (d) d = Eq(o->max2, o->to2);
    return d;
}
static inline BOOL Done1(MFade* o) {
    if (!Eq(o->to, o->max)) return 0;
    return Eq(o->to2, o->max2);
}
static inline BOOL Done2(MFade* o) {
    return Eq(o->to, o->max) && Eq(o->to2, o->max2);
}
static inline BOOL Done3(MFade* o) {
    if (Eq(o->to, o->max)) return Eq(o->to2, o->max2);
    return 0;
}
static inline BOOL Done4(MFade* o) {
    if (Eq(o->to, o->max) && Eq(o->to2, o->max2)) return 1;
    return 0;
}
extern "C" void fn_8017E470(MFade* o) {
    f32 k;
    u8* a;
    if (o->delay > 0) {
        o->delay--;
        return;
    }
    o->t++;
    if (o->t >= o->dur) {
        o->t = o->dur;
    }
    k = Ease(o->t, o->dur);
    o->cur = Lerp(o->from, o->to, k);
    o->cur2 = Lerp(o->from2, o->to2, k);
    a = fn_80010BB0(o->id);
    a[2] = o->cur.r;
    a[3] = o->cur.g;
    a[4] = o->cur.b;
    a[5] = o->cur.a;
    a = fn_80010DA4(a, 1);
    if (a) {
        a[4] = o->cur2.r;
        a[5] = o->cur2.g;
        a[6] = o->cur2.b;
        a[7] = o->cur2.a;
    }
    if (o->t >= o->dur) {
        BOOL d;
        d = Eq(o->max, o->to);
        if (d) d = Eq(o->max2, o->to2);
        if (d) {
            fn_80081A90(o);
        } else {
            fn_80083B78(o);
        }
    }
}
