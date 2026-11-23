/* Sword trail ribbon and small process helpers. */
#include "game/rR_80175E5C/types.h"
#include "game/rR_80175E5C/strpool.h"
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))

struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct C4 { u8 r, g, b, a; };

struct Seg {
    Vec a;
    Vec b;
    u8 pad[0x28 - 0x18];
};

struct Vtx {
    Vec a;
    Vec b;
    Vec c;
    u8 alpha;
    u8 pad25;
    s16 t;
};

struct Trail {
    u8 pad0[0x30];
    void* arch;
    void* tex;
    u8 c0[4];
    u8 c1[4];
    Seg* segs;
    Vtx* verts;
    u16 head;
    u16 x4A;
    u16 count;
    u16 cap;
    u8 flags;
    u8 pad51;
    u8 sub;
    u8 x53;
    u8 x54;
    u8 fade;
    s16 speed;
    char name0[8];
    char name1[8];
};

typedef void (*Fn2)(void*, void*);

extern "C" {
extern u8 lbl_80387BE8[];
void* fn_80078CCC(int, const char*, int);
int fn_8001AAB4();
void fn_80020E7C(int);
int fn_80007630(void*, const char*);
Vec fn_800076E8(void*, int);
f32 fn_8001E064(int);
void fn_80313484(const Vec*, const Vec*, Vec*);
f32 fn_80313508(const Vec*);
void fn_803134C4(const Vec*, Vec*);
void fn_803134A8(f32, const Vec*, Vec*);
void fn_80313460(const Vec*, const Vec*, Vec*);
void fn_80178254(Trail*);
void fn_80178364(Trail*);
void fn_80010788(int, int, void*, void*);
void fn_8017751C(Trail*);
void fn_803031CC();
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021C34(int);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_80021BF4(int);
void fn_80021CB4(int, int, int, int);
void fn_80021EF8(int, int);
void fn_80021BA4(int, int, int, int);
void fn_80021B68(int);
void fn_80304314(int, int, u16);
void fn_80011838(int);
void fn_80022254(void*, int);
void fn_80021F7C(int, int, int, int);
void fn_80010980();
void* fn_8000FB88();
void fn_80307E48(void*, int);
void fn_80021784(int);
f32 fn_8001EBC8(f32, f32, f32, f32, int);
void fn_80083B78(void*);
void* fn_80081050(void*, void*);

void fn_80177270(u8* o) {
    (*F(o, Fn2, 0x30))(F(o, void*, 0x18), o);
}

void fn_801772D8(u8* o) {
    (*F(o, Fn2, 0x30))(F(o, void*, 0x34), o);
}

void fn_80178CC0(Trail* t) {
    t->segs = (Seg*)fn_80078CCC(t->cap * 0x28, "", 0);
    t->verts = (Vtx*)fn_80078CCC(t->cap * t->sub * 0x28, "", 0);
    if (t->flags & 8) {
        fn_80020E7C(fn_8001AAB4());
    }
}

#pragma push
#pragma auto_inline off
void fn_80178254(Trail* t) {
    if (!(t->flags & 0x10) && 0.0f != fn_8001E064(t->speed)) {
        f32 v = fn_8001E064(t->speed);
        Vec d;
        for (int i = 0; i < t->count; i++) {
            Seg* s = &t->segs[(t->head + i) % t->cap];
            fn_80313484(&s->a, &s->b, &d);
            if (fn_80313508(&d) > 0.0f) {
                fn_803134C4(&d, &d);
                fn_803134A8(v, &d, &d);
                fn_80313460(&s->a, &d, &s->a);
            }
        }
    }
}

#pragma pop
static inline Vec Get(Trail* t, int i) {
    return fn_800076E8(t->arch, i);
}

static inline void Push(Trail* t, const Vec& a, Vec b) {
    Seg* p = t->segs;
    Vec lb = b;
    Vec la = a;
    if (p != 0 && !(t->flags & 0x10) && t->fade == 0) {
        Seg* s = &p[(t->head + t->count) % t->cap];
        s->a = la;
        s->b = lb;
        if (t->count == t->cap) {
            t->head = (t->head + 1) % t->cap;
        } else {
            t->count++;
        }
        t->x4A = t->count * t->sub;
    }
}

void fn_801780B8(Trail* t) {
    int a = fn_80007630(t->arch, t->name0);
    int b = fn_80007630(t->arch, t->name1);
    if (a < 0 || b < 0) return;
    Vec va = Get(t, a);
    Vec vb = fn_800076E8(t->arch, b);
    Push(t, va, vb);
}

typedef void (*GetFn)(Vec*, void*, int);
void fn_80178DB4(Trail* t) {
    Vec lb;
    Vec la;
    Vec vb;
    Vec ta;
    Vec bp;
    Vec va;
    if (t->flags & 0x20) {
        fn_80178254(t);
        int a = fn_80007630(t->arch, t->name0);
        int b = fn_80007630(t->arch, t->name1);
        if (a >= 0 && b >= 0) {
            ((GetFn)fn_800076E8)(&ta, t->arch, a);
            *(W3*)&va = *(W3*)&ta;
            ((GetFn)fn_800076E8)(&vb, t->arch, b);
            Seg* p = t->segs;
            *(W3*)&bp = *(W3*)&vb;
            *(W3*)&lb = *(W3*)&vb;
            *(W3*)&la = *(W3*)&va;
            if (p != 0 && !(t->flags & 0x10) && t->fade == 0) {
                Seg* s = &p[(t->head + t->count) % t->cap];
                s->a = la;
                s->b = lb;
                if (t->count == t->cap) {
                    t->head = (t->head + 1) % t->cap;
                } else {
                    t->count++;
                }
                t->x4A = t->count * t->sub;
            }
        }
        fn_80178364(t);
        int layer = 3;
        if (t->flags & 8) layer = 4;
        fn_80010788(layer, 0x97, fn_8017751C, t);
    }
}

void fn_80178F8C(Trail* t) {
    int f = t->fade + 1;
    t->fade = f;
    if ((int)(u8)f >= 0x10) {
        t->fade = 0x10;
        fn_80083B78(t);
    }
    int z = 0x10;
    t->c0[3] = fn_8001EBC8(t->c1[3], 0.0f, z, t->fade, 2);
}

void
#if TARGET_PC
*
#endif
fn_8017E3B4(void* parent) {
    u8* p = (u8*)fn_80081050(lbl_80387BE8, parent);
    F(p, int, 0x44) = 0;
    F(p, int, 0x4C) = 0;
    F(p, int, 0x48) = 8;
    F(p, f32, 0x40) = 0.0f;
    p[0x54] = 0;
    C4 c = {0xFF, 0xFF, 0xFF, 0xFF};
    Vec v;
    p[0x55] = c.r;
    p[0x56] = c.g;
    p[0x57] = c.b;
    p[0x58] = c.a;
    *(u32*)&v.x = 0;
    *(u32*)&v.y = 0;
    *(u32*)&v.z = 0;
    F(p, Vec, 0x30) = v;
    F(p, int, 0x64) = 0;
    F(p, int, 0x68) = 0;
    F(p, int, 0x6C) = 0;
#if TARGET_PC
    return p;
#endif
}

#define FIFOF (*(volatile f32*)0xCC008000)
#define FIFOB (*(volatile u8*)0xCC008000)
static inline void Pos(f32 x, f32 y, f32 z) {
    FIFOF = x;
    FIFOF = y;
    FIFOF = z;
}
static inline void Col(u8 r, u8 g, u8 b, u8 a) {
    FIFOB = r;
    FIFOB = g;
    FIFOB = b;
    FIFOB = a;
}
static inline void Tc(f32 s, f32 tt) {
    FIFOF = s;
    FIFOF = tt;
}

void fn_8017751C(Trail* t) {
    u8 obj[0x20];
    if (t->count < 2) return;
    fn_80010980();
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    if (t->flags & 1) {
        fn_80021BA4(1, 4, 1, 0);
    } else {
        fn_80021BA4(1, 4, 5, 0);
    }
    fn_80021BF4(1);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021B68(0);
    fn_80307E48(fn_8000FB88(), 0);
    fn_80021784(0);
    int base = t->count * t->sub - t->x4A;
    if (t->tex != 0) {
        fn_80302B80(0xD, 1);
        fn_80303200(0, 0xD, 1, 4, 0);
        fn_80006A64(t->tex, obj, t->x53);
        fn_80022254(obj, 0);
        fn_80021C34(1);
        fn_80021EF8(0, 0);
        fn_80021CB4(0, 0, 0, 4);
        fn_80021F7C(0, 1, 4, 0x3C);
        fn_80304314(0x98, 0, (t->x4A & 0x7FFF) * 2);
        for (int i = 0; i < t->x4A; i++) {
            Vtx* v = &t->verts[i + base];
            f32 tv = 0.00390625 * v->t;
            Pos(v->a.x, v->a.y, v->a.z);
            Col(t->c0[0], t->c0[1], t->c0[2], v->alpha);
            Tc(0.0f, tv);
            Pos(v->b.x, v->b.y, v->b.z);
            Col(t->c0[0], t->c0[1], t->c0[2], v->alpha);
            Tc(1.0f, tv);
        }
    } else {
        fn_80021EF8(0, 4);
        fn_80021CB4(0, 0xFF, 0xFF, 4);
        fn_80021C34(0);
        fn_80304314(0x98, 0, (t->x4A & 0x7FFF) * 2);
        for (int i = 0; i < t->x4A; i++) {
            Vtx* v = &t->verts[i + base];
            Pos(v->c.x, v->c.y, v->c.z);
            Col(t->c0[0], t->c0[1], t->c0[2], v->alpha);
            Pos(v->b.x, v->b.y, v->b.z);
            Col(t->c0[0], t->c0[1], t->c0[2], 0);
        }
        fn_80304314(0x98, 0, (t->x4A & 0x7FFF) * 2);
        for (int i = 0; i < t->x4A; i++) {
            Vtx* v = &t->verts[i + base];
            Pos(v->a.x, v->a.y, v->a.z);
            Col(t->c0[0], t->c0[1], t->c0[2], 0);
            Pos(v->c.x, v->c.y, v->c.z);
            Col(t->c0[0], t->c0[1], t->c0[2], v->alpha);
        }
    }
    fn_80011838(-1);
}
}
