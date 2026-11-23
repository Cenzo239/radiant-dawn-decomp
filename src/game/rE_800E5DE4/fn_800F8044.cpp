#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef f32 Mtx34[3][4];
struct V : Vec { V(const Vec& o) { x = o.x; y = o.y; z = o.z; } };
union Fifo { volatile f32 f; volatile u8 b; };
#define FIFO (*(Fifo*)0xCC008000)
extern "C" {
extern void fn_8001E9E4(void*, Vec*);
extern void fn_800076E8(Vec*, void*, int);
extern void fn_80313460(const Vec*, const Vec*, Vec*);
extern void fn_803128AC(f32*, f32, f32, f32);
extern f32* fn_8000FB88(void);
extern void fn_80312444(f32*, f32*);
extern void fn_80312378(f32*, f32*, f32*);
extern void fn_80307E48(f32*, int);
extern void fn_80021784(int);
extern void fn_80304314(int, int, int);
static inline void Pos3(f32 x, f32 y, f32 z) { FIFO.f = x; FIFO.f = y; FIFO.f = z; }
static inline void Col4(u8 r, u8 g, u8 b, u8 a) { FIFO.b = r; FIFO.b = g; FIFO.b = b; FIFO.b = a; }
static inline void Tex2(f32 u, f32 v) { FIFO.f = u; FIFO.f = v; }
typedef struct W2 { u32 a, b; } W2; typedef struct W3 { W2 ab; u32 c; } W3;
static inline Vec GP(MapUnit* m) {
    Vec v;
    Vec o;
    Vec t;
    Vec p;
    if (m->flags & 2) {
        void* mdl = m->model;
        if (m->unkC8 < 0) {
            fn_8001E9E4((u8*)mdl + 0x10, &v);
            v.z -= 0.5f;
        } else {
            fn_800076E8(&t, mdl, m->unkC8);
            v.x = t.x;
            v.y = t.y;
            v.z = t.z;
        }
    } else {
        *(W3*)&p = *(W3*)&m->x;
        v.x = p.x;
        v.y = p.y;
        v.z = p.z - 0.5f;
        *(W3*)&o = *(W3*)&m->offX;
        fn_80313460(&v, &o, &v);
    }
    return v;
}
void fn_800F8044(MapUnit* m, f32 s) {
    f32 t[3][4];
    f32 u[3][4];
    Vec w = GP(m);
    fn_803128AC(&t[0][0], w.x, w.y, w.z);
    fn_80312444(fn_8000FB88(), &u[0][0]);
    fn_80312378(&t[0][0], &u[0][0], &u[0][0]);
    fn_80312378(fn_8000FB88(), &u[0][0], &u[0][0]);
    fn_80307E48(&u[0][0], 0);
    fn_80021784(0);
    {
        u8 a = m->unk33;
        fn_80304314(0x98, 0, 4);
        f32 k;
        f32 n;
        n = -s;
        k = 1.25f * s;
        Pos3(n, n, 0.0f); Col4(a, a, a, 0xFF); Tex2(0.0f, 0.0f);
        Pos3(s, n, 0.0f); Col4(a, a, a, 0xFF); Tex2(1.0f, 0.0f);
        Pos3(n, k, 0.0f); Col4(a, a, a, 0xFF); Tex2(0.0f, 1.0f);
        Pos3(s, k, 0.0f); Col4(a, a, a, 0xFF); Tex2(1.0f, 1.0f);
    }
}
}
