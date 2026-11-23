#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef struct W2 { u32 a, b; } W2;
typedef struct W3 { W2 ab; u32 c; } W3;
struct V : Vec { V(const Vec& o) { x = o.x; y = o.y; z = o.z; } };
typedef struct Mdl { u8 pad[0x78]; f32 f78; } Mdl;
typedef struct AP { u8 pad[0x30]; MapUnit* u; u8 pad34[4]; int dur; int t; u16 h40; } AP;
extern "C" {
extern f32 fn_8001EDF8(int, f32, f32, f32, f32);
extern f32 fn_8001EBC8(int, f32, f32, f32, f32);
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern Vec fn_800F7790(MapUnit*);
extern void fn_800F7A98(MapUnit*);
extern void fn_80007DE8(Mdl*);
extern void fn_80313484(const Vec*, const Vec*, Vec*);
extern void fn_80313460(const Vec*, const Vec*, Vec*);
extern void fn_80083B78(void*);
static inline f32 C0(f32 d, f32 t) { return fn_8001EDF8(2, 0.0f, 1.0f, d, t); }
static inline f32 C1(f32 d, f32 t) { return fn_8001EBC8(2, 0.0f, 1.0f, d, t); }
static inline f32 C3(f32 d, f32 t) { return fn_8001ECE4(2, 0.0f, 1.0f, d, t); }
static inline void Cpy(Vec& e, Vec t) { e = t; }
static inline void SetO(MapUnit* u, f32 x, f32 y, f32 z) { u->offX = x; u->offY = y; u->offZ = z; }
static inline void Fade(AP* p, Mdl* m, int t) {
    switch (p->h40 & 3) {
    case 0: m->f78 = C0(p->dur, t); break;
    case 1: m->f78 = C1(p->dur, t); break;
    case 2: m->f78 = fn_8001EF30(0.0f, 1.0f, p->dur, t); break;
    case 3: m->f78 = C3(p->dur, t); break;
    }
}
void fn_800FC270(AP* p) {
    Mdl* m = (Mdl*)p->u->model;
    int t = ++p->t;
    Fade(p, m, t);
    if (p->h40 & 0x40) m->f78 *= 0.5f;
    if (p->h40 & 0x80) m->f78 *= 0.25f;
    if (p->h40 & 0xE000) {
        Vec a;
        Vec b;
        Vec e;
        Vec d;
        a = fn_800F7790(p->u);
        fn_800F7A98(p->u);
        fn_80007DE8(m);
        b = fn_800F7790(p->u);
        fn_80313484(&a, &b, &d);
        Cpy(e, *(Vec*)&p->u->offX);
        fn_80313460(&e, &d, &e);
        if (!(p->h40 & 0x2000)) e.x = 0.0f;
        if (!(p->h40 & 0x4000)) e.y = 0.0f;
        if (!(p->h40 & 0x8000)) e.z = 0.0f;
        SetO(p->u, e.x, e.y, e.z);
        fn_800F7A98(p->u);
    }
    if (p->t >= p->dur) fn_80083B78(p);
}
}
