#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct Mtx { f32 m[12]; };
struct Color { u8 r, g, b, a; };
struct Part { Part* next; u8 pad4[8]; u8 xc; u8 padd[7]; Vec pos; };
struct PList { u8 pad[0xC]; Part* head; };
struct RP { u8 pad[0x38]; void* tex; PList* list; };
struct WP { u8 pad[0x32]; u8 x32; u8 pad33[5]; f32 x38; u8 pad3c[0x78 - 0x3C]; u8 x78, x79, x7a; };
struct MM { u8 pad0[0xD0]; f32 scale; u8 padd4[0xE4 - 0xD4]; u8 xe4[0x30]; };
union Fifo { volatile f32 f; volatile u8 b; };
#define FIFO (*(Fifo*)0xCC008000)
extern "C" {
extern u8 lbl_80386540[];
extern MM* fn_8013B9A8(void);
extern WP* fn_80083B84(void*);
extern void fn_80312344(void*, void*);
extern void fn_80312318(void*);
extern void fn_80006A64(void*, void*, int);
extern void fn_80022254(void*, int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021C34(int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021860(int, int, int);
extern void fn_80021B68(int);
extern void* fn_8000FB88(void);
extern void fn_80312378(void*, void*, void*);
extern void fn_80307E48(void*, int);
extern void fn_80021784(int);
extern void fn_803045A0(int, int, int);
extern void fn_8030456C(u8, int);
extern void fn_80312444(void*, void*);
extern void fn_80312494(void*, void*);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void fn_80304314(int, int, int);
extern void fn_80011838(int);

static inline Part* Next(PList* l, Part* p) { return p == 0 ? l->head : p->next; }
static inline Color Mk(u8 a, u8 b, u8 c, u8 d) { Color k; k.r = a; k.g = b; k.b = c; k.a = d; return k; }
static inline void Xf(Mtx* m, Vec* out, int n) { Vec* in; int i; in = out; for (i = 0; i < n; i++) { fn_80312DB4(m, in, out); in++; out++; } }
static inline void DrawP(Vec v, Color c) {
    fn_80304314(0xB8, 0, 1);
    FIFO.f = v.x;
    FIFO.f = v.y;
    FIFO.f = v.z;
    FIFO.b = c.r;
    FIFO.b = c.g;
    FIFO.b = c.b;
    FIFO.b = c.a;
    FIFO.f = 0.0f;
    FIFO.f = 0.0f;
}
void fn_80144CD0(RP* r) {
    MM* mm = fn_8013B9A8();
    if (mm == 0) return;
    WP* w = fn_80083B84(lbl_80386540);
    if (w == 0) return;
    Mtx mf;
    Mtx mc;
    Mtx ma;
    Mtx m7;
    u8 tex[0x20];
    switch (w->x32) {
    case 0:
        fn_80312344(fn_8013B9A8()->xe4, &mc);
        break;
    default:
        fn_80312318(&mc);
        break;
    }
    fn_80006A64(r->tex, tex, 6);
    fn_80022254(tex, 0);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021EF8(0, 0);
    fn_80021BA4(1, 4, 5, 0);
    fn_80021860(1, 3, 0);
    fn_80021B68(0);
    fn_80312378(fn_8000FB88(), &mc, &mf);
    fn_80307E48(&mf, 0);
    fn_80021784(0);
    f32 s = 42.0f * w->x38;
    fn_803045A0(0, 0, 1);
    fn_8030456C(s, 5);
    Part* p = 0;
    fn_80312444(fn_8000FB88(), &ma);
    fn_80312494(&mc, &m7);
    fn_80312378(&m7, &ma, &mf);
    {
f32 n; f32 z = mm->scale; f32 k = 0.125f * z; n = -k;
        Vec q[4] = {{n, n, 0.0f}, {k, n, 0.0f}, {k, k, 0.0f}, {n, k, 0.0f}};
Vec* o = q; Vec* b = o; for (int i = 0; i < 4; i++, o++, b++) { fn_80312DB4(&mf, b, o); }
    }
    while ((p = Next(r->list, p)) != 0) {
        Color c;
        c.r = w->x78;
        c.g = w->x79;
        c.b = w->x7a;
        c.a = p->xc;
        DrawP(p->pos, c);
    }
    fn_803045A0(0, 0, 0);
    fn_80011838(-1);
}
}
