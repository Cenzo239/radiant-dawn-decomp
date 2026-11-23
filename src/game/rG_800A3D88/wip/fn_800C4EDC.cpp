// WIP, does not match: 15/565 lines, right size. Only the leftover colour pointer pa in the second edge block (r25 wanted). Reusing parameter x as pa fixes the first block only. Statement and declaration order found by sw.
#include "game/rG_800A3D88/types.h"

// Face portrait frame: draws the texture as six slices with optional fading edges and a scissor for wide screens.
extern "C" {
struct GXC { u8 r, g, b, a; };
struct Dim { u16 m0, m2; };
struct Face { u8 p[0x30]; void* m30; u8 p34[0xC]; u8 m40, m41; u8 p42[6]; u32 m48; };
Dim** fn_80006A0C(void*, int);
void fn_8007E154();
void fn_8007E164();
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E41C(void*, int, int, int);
int fn_801D09F0();
void fn_8007E74C(void*, u32);
void fn_800C43B0(void*, u32);
void fn_800800D4(int);
void fn_80080348(f32, f32, f32, f32);
void fn_80080538(f32, f32, f32, f32);
void fn_80080558(f32, f32, f32, f32);
void fn_80080368(f32, f32, f32, f32);
void fn_80080940(GXC*, GXC*, GXC*, GXC*);
void fn_80080308();
void fn_8007E7B4();
static inline Dim** Tex(Face* f) {
    if (f->m48 & 0x1000) return fn_80006A0C(f->m30, 1);
    return fn_80006A0C(f->m30, 0);
}
static inline void Col(GXC a, GXC b, GXC c, GXC d) { fn_80080940(&a, &b, &c, &d); }
void fn_800C4EDC(Face* f, int x, int y, int a, int flag, f32 z) {
u8 g;
int x0;
int y0;
int tw;
const GXC* qb;
f32 py0;
f32 u0;
f32 px0;
f32 px1;
f32 px2;
f32 px3;
f32 py1;
f32 py2;
f32 u1;
f32 u2;
f32 u3;
f32 v0;
f32 v1;
f32 v2;
int ca;
int cb;
int zero;
const GXC* pd;
const GXC* pb;
const GXC* pc;
const GXC* qd;
int th;
const GXC* qc;
    g = f->m41;
    if (x < 0 || x > 0x260) return;
    if (f->m30 == NULL) return;
    Dim* t = *Tex(f);
    tw = t->m2;
    th = t->m0;
    x0 = x - (tw >> 1);
    y0 = y - th;
    fn_8007E154();
    if (flag != 0) fn_8007E4E4(0.0f, 0.0f, 96.0f + z, 1.0f);
    if ((f->m48 & 0x1000) == 0) fn_8007E41C(f->m30, 0, f->m40, 0x11);
    else fn_8007E41C(f->m30, 1, f->m40, 0x11);
    if (f->m48 & 0x8000) {
        ca = 0x4C;
        cb = 0x58;
        if (fn_801D09F0()) {
            ca = (int)(608.0f * ca / 796.0f);
            cb = (int)(608.0f * cb / 796.0f);
        }
        int l = x - ca;
        if (f->m48 & 1) l = x - cb;
        int w = ca + cb;
        if (l < 0) w = (int)((u8*)cb + (l + ca));
        if (l < 0) l = 0;
        fn_8007E74C((void*)fn_800C43B0, (l << 16) | w);
    }
    fn_8007E164();
    GXC k;
    GXC n;
    zero = 0;
    *(u32*)&n = zero;
    px0 = x0;
    px1 = 32.0f + px0;
    px2 = px1 + (f32)(tw - 0x40);
    px3 = 32.0f + px2;
    py0 = y0;
    py1 = py0 + (f32)(th - 0x10);
    py2 = 16.0f + py1;
    u0 = zero;
    u1 = 32.0f + u0;
    u2 = u1 + (f32)(tw - 0x40);
    u3 = 32.0f + u2;
    v0 = zero;
    v1 = v0 + (f32)(th - 0x10);
    v2 = 16.0f + v1;
    k.r = g;
    k.g = g;
    k.b = g;
    k.a = a;
    n.r = g;
    n.g = g;
    n.b = g;
    if (f->m48 & 1) {
        f32 t1;
        f32 t0;
        t0 = u0;
        t1 = u1;
        u0 = u3;
        u1 = u2;
        u3 = t0;
        u2 = t1;
    }
    fn_800800D4(3);
    fn_80080348(px0, py0, u0, v0);
    fn_80080538(px1, py0, u1, v0);
    fn_80080558(px0, py1, u0, v1);
    fn_80080368(px1, py1, u1, v1);
    if (f->m48 & 0x4000) Col(n, k, n, k);
    else Col(k, k, k, k);
    fn_80080308();
    fn_800800D4(3);
    fn_80080348(px1, py0, u1, v0);
    fn_80080538(px2, py0, u2, v0);
    fn_80080558(px1, py1, u1, v1);
    fn_80080368(px2, py1, u2, v1);
    Col(k, k, k, k);
    fn_80080308();
    fn_800800D4(3);
    fn_80080348(px2, py0, u2, v0);
    fn_80080538(px3, py0, u3, v0);
    fn_80080558(px2, py1, u2, v1);
    fn_80080368(px3, py1, u3, v1);
    if (f->m48 & 0x4000) Col(k, n, k, n);
    else Col(k, k, k, k);
    fn_80080308();
    fn_800800D4(3);
    fn_80080348(px0, py1, u0, v1);
    fn_80080538(px1, py1, u1, v1);
    fn_80080558(px0, py2, u0, v2);
    fn_80080368(px1, py2, u1, v2);
    {
        pd = &k;
        pc = &k;
        pb = &k;
        x = (int)&k;
        if (f->m48 & 0x4000) { pc = &n; x = (int)pc; }
        if (f->m48 & 0x2000) pc = pd = &n;
        Col(*(const GXC*)x, *pb, *pc, *pd);
    }
    fn_80080308();
    fn_800800D4(3);
    fn_80080348(px1, py1, u1, v1);
    fn_80080538(px2, py1, u2, v1);
    fn_80080558(px1, py2, u1, v2);
    fn_80080368(px2, py2, u2, v2);
    if (f->m48 & 0x2000) Col(k, k, n, n);
    else Col(k, k, k, k);
    fn_80080308();
    fn_800800D4(3);
    fn_80080558(px2, py1, u2, v1);
    fn_80080348(px3, py1, u3, v1);
    fn_80080368(px2, py2, u2, v2);
    fn_80080538(px3, py2, u3, v2);
    {
        qd = &k;
        qc = &k;
        qb = &k;
        x = (int)&k;
        if (f->m48 & 0x4000) { qb = &n; x = (int)qb; }
        if (f->m48 & 0x2000) qb = qd = &n;
        Col(*(const GXC*)x, *qb, *qc, *qd);
    }
    fn_80080308();
    if (f->m48 & 0x8000) {
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
    }
}
}
