/* fn_800167B0: draft, not matching. Stack and calls are right except the C4 colour at 0x1C, which must stay in memory yet CSE across the vertices; a struct {k[5], C4} (size 0x18) sorts above the Vecs. The float block, v, cols, w order is the target; centre and dir are corner[4], corner[5]. */
#include "game/rA_800068A0/types.h"
/* Particle quads with an optional directional light tint. */
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct GPart { Vec pos; Vec vel; f32 x18; f32 x1C; f32 x20; f32 x24; f32 x28; u8 r, g, b, a; } GPart;
typedef struct GSeg { u8 x0[0xA]; s16 id; u8 xC[0x1C - 0xC]; u16 node; u16 count; } GSeg;
typedef struct GEnt { u8 x0[0xC]; GPart* parts; } GEnt;
typedef struct GLay { u8 x0[8]; f32 x8, xC, x10, x14, x18; } GLay;
typedef struct GMatL { u8 x0[4]; u16 x4; u8 x6[0x14 - 6]; GLay* layers; } GMatL;
typedef struct GAnm { u32 x0; u8 x4[0x10]; int t0; int t1; } GAnm;
extern GAnm* fn_80007F10(u8* a);
extern void* fn_80007EE4(u8* a);
extern void* fn_8000F3D4(void* m, u16 i);
extern int fn_80016568(GSeg* s, GMatL* m, void* e, GAnm* an);
extern void fn_80021B68(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80304314(int, int, int);
extern void* fn_8000FB88(void);
extern void fn_80307E48(const void* m, int id);
extern void fn_80021784(int);
extern void fn_8001D44C(const void* a, void* b);
extern void fn_80312444(const void* a, void* b);
extern void fn_8001E638(const void* a, void* b);
extern void fn_80016368(GSeg* s, void* n, void* a, void* b);
extern void* fn_80010BB0(int);
extern u8* fn_80010DA4(void*, int);
extern void fn_80312DB4(const void* m, const Vec* a, Vec* b);
extern int fn_8000AE38(GAnm* b, int id, f32* out, f32 frame);
extern int fn_8000B100(GAnm* b, int id, f32* out, f32 frame);
extern int fn_8000B3C8(GAnm* b, int id, f32* out, f32 frame);
extern int fn_8000B690(GAnm* b, int id, f32* out, f32 frame);
extern int fn_8000B958(GAnm* b, int id, f32* out, f32 frame);
extern void fn_80312318(void* m);
extern void fn_803128AC(void* m, f32 x, f32 y, f32 z);
extern void fn_8031292C(void* m, f32 x, f32 y, f32 z);
extern void fn_80312654(void* m, int axis, f32 a);
extern void fn_80312378(const void* a, const void* b, void* c);
extern void fn_80307F10(const void* m, u32 id, u32 type);
extern void fn_80313484(const Vec* a, const Vec* b, Vec* c);
extern void fn_803134C4(const Vec* a, Vec* b);
extern f32 fn_8031354C(const void* a, const Vec* b);
#define WGF (*(volatile f32*)0xCC008000)
#define WGB (*(volatile u8*)0xCC008000)
static inline C4 mkc(const GPart* p) { C4 c; c.r = p->r; c.g = p->g; c.b = p->b; c.a = p->a; return c; }
static inline void pos3(const Vec& v) {
    f32 x, y, z;
    z = v.z;
    y = v.y;
    x = v.x;
    WGF = x;
    WGF = y;
    WGF = z;
}
static inline void col4(u8 r, u8 g, u8 b, u8 a) {
    WGB = r;
    WGB = g;
    WGB = b;
    WGB = a;
}
static inline void tex2(f32 s, f32 t) {
    WGF = s;
    WGF = t;
}
static inline void setc(C4* c, u8 a, u8 b, u8 g, u8 r) { c->r = r; c->g = g; c->b = b; c->a = a; }
void fn_800167B0(u8* a, GEnt* st, GSeg* s, GMatL* m, void* e) {
    GAnm* an;
    void* nd;
    int tm;
    GPart* p;
    GLay* l;
    int i;
    int j;
    u8* lit;
    Vec* pc;
    C4* pk;
    u32 cr, cg, cb;
    f32 t, sx, sy, d;
    Vec corner[6];
    Mtx q;
    Mtx view;
    Mtx inv;
    Mtx tr;
    Mtx rot33;
    Mtx rz;
    Mtx tex;
    Mtx mt;
    Mtx mr;
    Mtx ms;
    Vec w;
    C4 cols[4];
    Vec v;
    struct KA { f32 kr, ktx, kty, ksx, ksy; C4 c; } ka;
#define kr ka.kr
#define ktx ka.ktx
#define kty ka.kty
#define ksx ka.ksx
#define ksy ka.ksy
#define col ka.c
    if (m->layers == 0) return;
    p = st->parts;
    an = fn_80007F10(a);
    nd = fn_80007EE4(a);
    tm = fn_80016568(s, m, e, an);
    fn_80021B68(0);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    fn_80307E48(fn_8000FB88(), 0);
    fn_80021784(0);
    fn_8001D44C(a + 0xC, view);
    fn_80312444(fn_8000FB88(), inv);
    fn_8001E638(view, rot33);
    fn_80312378(inv, rot33, inv);
    fn_80016368(s, fn_8000F3D4(nd, s->node), view, view);
    lit = 0;
    if (m->x4 & 0x800) {
        u8* li = fn_80010DA4(fn_80010BB0(((s8*)a)[0x81]), 1);
        if (li != 0) {
            lit = li + 8;
        }
    }
    for (i = 0; i < s->count; i++, p++) {
        if (!(p->x18 < 0.0f) && p->a != 0) {
            if (tm != 0x3C) {
                l = m->layers;
                kr = l->x18;
                ktx = l->x8;
                kty = l->xC;
                ksx = l->x10;
                ksy = l->x14;
                if (an->x0 != 0) {
                    t = p->x1C * (f32)(an->t1 - an->t0) + (f32)an->t0;
                    fn_8000B3C8(an, s->id, &kr, t);
                    fn_8000AE38(an, s->id, &ktx, t);
                    fn_8000B100(an, s->id, &kty, t);
                    fn_8000B690(an, s->id, &ksx, t);
                    fn_8000B958(an, s->id, &ksy, t);
                }
                fn_80312318(tex);
                if (0.0f != kr) {
                    fn_803128AC(mt, -0.5f, -0.5f, 0.0f);
                    fn_80312654(mr, 0x7A, 0.017453292f * -kr);
                    fn_80312378(mr, mt, mr);
                    fn_803128AC(mt, 0.5f, 0.5f, 0.0f);
                    fn_80312378(mt, mr, tex);
                }
                if (1.0f != ksx || 1.0f != ksy) {
                    fn_803128AC(mt, 0.0f, -1.0f, 0.0f);
                    fn_8031292C(ms, ksx, ksy, 1.0f);
                    fn_80312378(ms, mt, ms);
                    fn_803128AC(mt, 0.0f, 1.0f, 0.0f);
                    fn_80312378(mt, ms, ms);
                    fn_80312378(ms, tex, tex);
                }
                if (0.0f != ktx || 0.0f != kty) {
                    fn_803128AC(mt, ktx, -kty, 0.0f);
                    fn_80312378(mt, tex, tex);
                }
                fn_80307F10(tex, tm, 1);
            }
            fn_80312DB4(view, &p->pos, &w);
            fn_803128AC(tr, w.x, w.y, w.z);
            fn_80312378(tr, inv, q);
            if (0.0f != p->x28) {
                fn_80312654(rz, 0x7A, 0.017453292f * p->x28);
                fn_80312378(q, rz, q);
            }
            sx = 0.5f * p->x20;
            sy = 0.5f * p->x24;
            setc(&col, p->a, p->b, p->g, p->r);
            v.x = -sx;
            v.y = -sy;
            v.z = 0.0f;
            fn_80312DB4(q, &v, &corner[0]);
            v.x = sx;
            v.z = 0.0f;
            v.y = -sy;
            fn_80312DB4(q, &v, &corner[1]);
            v.x = sx;
            v.y = sy;
            v.z = 0.0f;
            fn_80312DB4(q, &v, &corner[2]);
            v.y = sy;
            v.z = 0.0f;
            v.x = -sx;
            fn_80312DB4(q, &v, &corner[3]);
            fn_80304314(0x80, 0, 4);
            if (lit != 0) {
#define center corner[4]
#define dir corner[5]
                pc = corner;
                pk = cols;
                cg = col.g;
                cb = col.b;
                center.x = 0.25f * (corner[3].x + (corner[2].x + (corner[0].x + corner[1].x)));
                center.y = 0.25f * (corner[3].y + (corner[2].y + (corner[0].y + corner[1].y)));
                cr = col.r;
                center.z = 0.25f * (corner[3].z + (corner[2].z + (corner[0].z + corner[1].z)));
                for (j = 0; j < 4; j++, pc++, pk++) {
                    fn_80313484(pc, &center, &dir);
                    fn_803134C4(&dir, &dir);
                    d = 1.0f - 0.5f * (1.0f + fn_8031354C(lit, &dir));
                    if (d < 0.0f) d = 0.0f;
                    if (d > 1.0f) d = 1.0f;
                    pk->r = (f32)cr * d;
                    pk->g = (f32)cg * d;
                    pk->b = (f32)cb * d;
                }
                pos3(corner[0]); col4(cols[0].r, cols[0].g, cols[0].b, col.a); tex2(0.0f, 0.0f);
                pos3(corner[1]); col4(cols[1].r, cols[1].g, cols[1].b, col.a); tex2(1.0f, 0.0f);
                pos3(corner[2]); col4(cols[2].r, cols[2].g, cols[2].b, col.a); tex2(1.0f, 1.0f);
                pos3(corner[3]); col4(cols[3].r, cols[3].g, cols[3].b, col.a); tex2(0.0f, 1.0f);
            } else {
                pos3(corner[0]); col4(col.r, col.g, col.b, col.a); tex2(0.0f, 0.0f);
                pos3(corner[1]); col4(col.r, col.g, col.b, col.a); tex2(1.0f, 0.0f);
                pos3(corner[2]); col4(col.r, col.g, col.b, col.a); tex2(1.0f, 1.0f);
                pos3(corner[3]); col4(col.r, col.g, col.b, col.a); tex2(0.0f, 1.0f);
            }
        }
    }
}
}
