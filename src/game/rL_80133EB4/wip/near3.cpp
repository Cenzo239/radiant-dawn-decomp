/* Near misses from round 11, not compiled together; each section was a standalone test file. Word counts are from check_func. */

/* ===== fn_80141334: 4 words: only the template base register (r5, want r4). The camera form works in fn_80141DCC.cpp ===== */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct Mtx { f32 m[12]; };
struct Tex { u8 p[0x20]; };
struct MM {
    u8 pad0[0x14];
    u8* x14;
    u8 pad18[0x58 - 0x18];
    f32 x58;
    u8 pad5c[0x61 - 0x5C];
    s8 x61;
    u8 x62;
    u8 pad63[0xAD - 0x63];
    s8 xad, xae;
    u8 xaf;
    u8 padb0[0xCC - 0xB0];
    u8 xcc;
    u8 padcd[0xD0 - 0xCD];
    f32 scale;
    Vec xd4;
    u8 pade0[4];
    u8 xe4[0x30];
};
struct Cam { Vec e, t, u; Cam(const Vec& a, const Vec& b, const Vec& c) : e(a), t(b), u(c) {} };
struct Cam2 { Vec e, t, u; };
struct W3 { u32 a, b, c; };
inline Vec Z() { Vec z = {0.0f, 0.0f, 0.0f}; return z; }
inline W3 Z3() { W3 z = {0, 0, 0}; return z; }
struct F { Mtx mo; Mtx mq; Mtx mv; Mtx ml; Mtx mp; };
struct Lit { Vec a; Vec b; };
extern "C" {
extern MM* fn_8013B9A8(void);
extern void fn_8001E6D0(void*, void*);
extern void fn_80312494(void*, void*);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312A50(void*, Vec*, Vec*);
extern void fn_80312AC0(void*, Vec*, Vec*, Vec*);
extern void fn_80312D2C(void*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80019D9C(void*);
extern int fn_800120A0(void);
extern void* fn_80012048(void);
extern void* fn_80011F38(void);
extern void* fn_80011EB4(void);
extern void* fn_80011FC4(void);
extern void fn_8001E51C(void*);
extern void fn_803067E0(int, void*, int);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern void fn_80307F10(void*, void*, int);
extern void fn_80021F7C(void*, int, int, void*);
extern void fn_80022254(void*, void*);
extern void fn_80306A38(void*, void*, void*);
extern void fn_80306934(void*, int, int);
extern void fn_80306B6C(void*, void*, int, int, int);

static inline Vec Eye(f32 x, f32 z) { Vec e = {0.0f, 1.0f, 0.0f}; e.x = x; e.z = z; return e; }
static inline Vec Tgt(f32 x, f32 z) { Vec t = {0.0f, 0.0f, 0.0f}; t.x = x; t.z = z; return t; }
static inline Vec Up() { Vec u = {0.0f, 0.0f, -1.0f}; return u; }
static inline void View(MM* mm, F* f, Vec u, Vec t, Vec e) {
    fn_8001E6D0(mm->xe4, &f->mv);
    fn_80312DB4(mm->xe4, &e, &e);
    fn_80312DB4(mm->xe4, &t, &t);
    fn_80312DB4(&f->mv, &u, &u);
    fn_80312AC0(&f->mo, &e, &u, &t);
}
static inline const Vec& T(Vec& t, f32 x, f32 z) { *(int*)&t.x = 0; *(int*)&t.y = 0; *(int*)&t.z = 0; t.x = x; t.z = z; return t; }
int fn_80141334(void* out) {
    MM* mm = fn_8013B9A8();
    if (mm == 0) return 0;
    u8* w = mm->x14;
    if (w == 0) return 0;
    if (*(void**)(w + 0x48) == 0) return 0;
    int idx = mm->x61;
    f32 y;
    f32 s = mm->x62 / 2.0f;
    s *= 5.0f * mm->scale;
    if (0.0f == s) return 0;
    void* a = (void*)fn_800120A0();
    if ((int)a == 4) {
        F f;
        u8 m3[0x18];
        Tex tex;
        fn_80019D9C(&f.ml);
        fn_80305A40(&tex, *(void**)(w + 0x48), 0x20, 0x20, 3, 1, 1, 0);
        fn_80305C94(&tex, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
        a = fn_80012048();
        void* b = fn_80011F38();
        void* c = fn_80011EB4();
        void* d = fn_80011FC4();
        fn_8001E51C(m3);
        fn_803067E0(2, m3, idx);
        y = s;
        Vec t;
        Vec e = {0.0f, 1.0f, 0.0f};
        e.x = 0.0f;
        e.z = 0.0f;
        View(mm, &f, Up(), T(t, 0.0f, 0.0f), e);
        if (mm->xcc) { f32 k = -1.0f; y = s * k; }
        fn_80312D2C(&f.mq, -s, s, -y, y, 0.5f, 0.5f, 0.5f, 0.5f);
        fn_80312378(&f.mo, &f.ml, &f.mo);
        fn_80312378(&f.mq, &f.mo, &f.mp);
        fn_80307F10(&f.mp, d, 0);
        fn_80021F7C(b, 0, 0, d);
        fn_80022254(&tex, c);
        fn_80306A38(a, b, c);
        fn_80306934(a, 0, 0);
    }
    fn_80306B6C(out, a, 1, 0, 2);
    return 1;
}
}

/* ===== fn_80141650: about 51 words: params must rank above t1/r1 (r19, r20), plus a few FP temporaries ===== */
#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct Tex { u8 p[0x20]; };
struct Color { u8 r, g, b, a; };
struct F { Mtx mo; Mtx mq; Mtx mv; Mtx ml; Mtx mp; };
struct Ent { u8 pad[4]; u16 x4; };
struct Tbl { u8 pad[0x14]; Ent* x14; };
struct Wk { u8 pad[0x30]; int x30; };
struct Obj { u8 pad[8]; u8 r, g, b, a; };
struct MM {
    u8 pad0[0x14];
    Wk* x14;
    u8 pad18[0x64 - 0x18];
    u8 x64, x65;
    Color x66;
    u8 pad6a[0xAB - 0x6A];
    s8 xab, xac;
    u8 pad[0xCC - 0xAD];
    u8 xcc;
    u8 padcd[0xD0 - 0xCD];
    f32 scale;
    u8 padd4[0xE4 - 0xD4];
    u8 xe4[0x30];
};
extern "C" {
extern MM* fn_8013B9A8(void);
extern void fn_8001E6D0(void*, void*);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312AC0(void*, Vec*, Vec*, Vec*);
extern void fn_80312D2C(void*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80019D9C(void*);
extern void* fn_80011E28(void);
extern void* fn_80011F38(void);
extern void* fn_80011EB4(void);
extern void* fn_80011FC4(void);
extern void* fn_800120D4(void);
extern int fn_8001212C(void*);
extern void* fn_80012170(void);
extern void* fn_800121C8(void*);
extern void fn_80307F10(void*, void*, int);
extern void fn_80021F7C(void*, int, int, void*);
extern void fn_80022254(void*, void*);
extern void fn_80006A64(void*, void*, int);
extern void fn_80021CB4(void*, void*, void*, int);
extern void fn_80021D18(void*, int, int, int, int, void*);
extern void fn_80021E20(void*, int, int, int, int);
extern void fn_80021D9C(void*, int, int, int, int, void*);
extern void fn_80021E8C(void*, int, int, int, int);
extern void fn_80021958(int, Color*);
extern f32 fn_8001EF44(int, int, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_80306EA0(void*, Color*);
extern void fn_80021FF0(void*, void*);
extern void fn_800140A0(void*, void*);
extern void fn_80013CF0(void*, void*, void*);

static inline void View(MM* mm, F* f, Vec u, Vec t, Vec e) {
    fn_8001E6D0(mm->xe4, &f->mv);
    fn_80312DB4(mm->xe4, &e, &e);
    fn_80312DB4(mm->xe4, &t, &t);
    fn_80312DB4(&f->mv, &u, &u);
    fn_80312AC0(&f->mo, &e, &u, &t);
}
static inline const Vec& T(Vec& t, f32 x, f32 z) { *(int*)&t.x = 0; *(int*)&t.y = 0; *(int*)&t.z = 0; t.x = x; t.z = z; return t; }
static inline Vec Up1() { Vec u = {0.0f, 0.0f, -1.0f}; return u; }
static inline void SetK(Color c) { fn_80021958(4, &c); }

static inline Color GetC1(MM* mm) { Color k = mm->x66; return k; }
static inline Color GetC2(MM* mm) { return GetC1(mm); }
static inline void Set0(void* v, Color c) { fn_80306EA0(v, &c); }
static inline void Set1(void* v, Color* c) { Set0(v, *c); }
static inline void Set2(void* v, Color* c) { Set1(v, c); }
void fn_80141650(Obj* a0, void* b0, Tbl* c0, void* d0) {
    F f;
    Tex tex;
    Color col;
/*P*/
    void* t1;
    void* g2;
    Wk* w;
    void* r2;
    void* t3;
    int k2;
    void* v3;
    void* g1;
    void* t2;
    void* u3;
    void* h4;
    int k1;
    void* h1;
    void* h2;
    void* q;
    void* g4;
    void* t4;
    int n;
    Obj* a2;
    void* b2;
    Tbl* c2;
    void* d2;
    MM* mm;
    int ka;
    int v;
    void* r1;
/*E*/
    a2 = a0; b2 = b0; c2 = c0; d2 = d0;
    mm = fn_8013B9A8();
    if (mm == 0) return;
    w = mm->x14;
    if (w == 0) return;
    fn_80019D9C(&f.ml);
    f32 k5 = 5.0f * mm->scale;
    f32 y; f32 s; f32 z; f32 x; z = 0x40 - mm->xac; x = 0x40 - mm->xab; z = k5 * z; s = 64.0f * k5; x = k5 * x;
    y = s;
    {
        Vec t;
        Vec e = {0.0f, 1.0f, 0.0f};
        e.x = x;
        e.z = z;
        View(mm, &f, Up1(), T(t, x, z), e);
    }
    if (mm->xcc) { f32 k = -1.0f; y = s * k; }
    fn_80312D2C(&f.mq, -s, s, -y, y, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_80312378(&f.mo, &f.ml, &f.mo);
    fn_80312378(&f.mq, &f.mo, &f.mp);
    col.r = a2->r * 255 / 128;
    col.g = a2->g * 255 / 128;
    col.b = a2->b * 255 / 128;
    col.a = a2->a * 255 / 255;
    SetK(col);
    n = c2->x14->x4;
    fn_80006A64(d2, &tex, n);
    g1 = fn_80011F38();
    t1 = fn_80011E28();
    h1 = fn_80011EB4();
    r1 = fn_800120D4();
    fn_80022254(&tex, h1);
    fn_80021CB4(t1, g1, h1, 4);
    fn_80021F7C(g1, 0, 4, (void*)0x3C);
    fn_80021D18(t1, 0, 0, 0, 1, r1);
    fn_80021E20(t1, 0xF, 8, 0xA, 0xF);
    fn_80021D9C(t1, 0, 0, 0, 1, r1);
    fn_80021E8C(t1, 7, 7, 7, 7);
    g2 = fn_80011F38();
    t2 = fn_80011E28();
    h2 = fn_80011EB4();
    r2 = fn_800120D4();
    fn_80022254(&tex, h2);
    fn_80021CB4(t2, g2, h2, 4);
    fn_80021F7C(g2, 0, 5, (void*)0x3C);
    fn_80021D18(t2, 0, 0, 0, 1, r2);
    fn_80021E20(t2, 0xF, 8, 0xA, 0xF);
    fn_80021D9C(t2, 0, 0, 0, 1, r2);
    fn_80021E8C(t2, 7, 7, 7, 7);
    if (mm->x64 == 1) {
        fn_80011F38();
        t3 = fn_80011E28();
        ka = fn_8001212C(r2);
        v3 = fn_80012170();
        u3 = fn_800121C8(v3);
        col = GetC2(mm);
        v = fn_8001EF44(0x1000, w->x30, 0.0f, 255.0f);
        if (v >= 0x80) {
            v -= 0x80;
            fn_80021D18(t3, 0, 0, 0, 1, r2);
        } else {
            v = 0x80 - v;
            col.r = (int)col.r >> 1;
            col.g = (int)col.g >> 1;
            col.b = (int)col.b >> 1;
            fn_80021D18(t3, 1, 0, 0, 1, r2);
        }
        col.r = fn_8001EF30(0.0f, col.r, 128.0f, v);
        col.g = fn_8001EF30(0.0f, col.g, 128.0f, v);
        col.b = fn_8001EF30(0.0f, col.b, 128.0f, v);
        {
            Set2(v3, &col);
        }
        fn_80021FF0(t3, u3);
        fn_80021CB4(t3, (void*)0xFF, (void*)0xFF, 4);
        fn_80021E20(t3, 0xF, ka, 0xE, ka);
        fn_80021D9C(t3, 0, 0, 0, 1, r2);
        fn_80021E8C(t3, 7, 7, 7, 7);
    }
    q = fn_80011FC4();
    fn_80307F10(&f.mp, q, 0);
    g4 = fn_80011F38();
    fn_80021F7C(g4, 0, 0, q);
    t4 = fn_80011E28();
    h4 = fn_80011EB4();
    k1 = fn_8001212C(r1);
    k2 = fn_8001212C(r2);
    fn_80006A64(d2, &tex, n + 1);
    fn_80022254(&tex, h4);
    fn_80021CB4(t4, g4, h4, 4);
    fn_80021D18(t4, 0, 0, 0, 1, 0);
    fn_80021E20(t4, k1, k2, 8, 0xF);
    fn_80021D9C(t4, 0, 0, 0, 1, 0);
    fn_80021E8C(t4, 7, 7, 7, 6);
    fn_800140A0(a2, b2);
    fn_80013CF0(a2, b2, c2);
}
}

/* ===== fn_80145980: about 62 words: volatile registers in the frame loop, and subi r12 belongs in the 4th vertex ===== */
#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct Tex { u8 p[0x20]; };
struct Color { u8 r, g, b, a; };
struct Part { s16 x, y, z; };
struct Ent { f32 rot, y; };
struct WP {
    u8 pad[0x32]; u8 x32; u8 pad33; u8 x34; u8 pad35[0x54 - 0x35];
    f32 x54, x58, x5c, x60, x64, x68;
};
struct RP { u8 pad[0x31]; s8 x31; u8 x32; u8 pad33; u16 x34, x36; u8 pad38[4]; void* x3c; Part* x40; void* x44; Ent* x48; };
struct MM { u8 pad[0xE4]; u8 xe4[0x30]; };
union Fifo { volatile s16 s; volatile u8 b; };
#define FIFO (*(Fifo*)0xCC008000)
extern "C" {
extern u8 lbl_80386540[];
extern WP* fn_80083B84(void*);
extern void fn_80006A64(void*, void*, int);
extern u32 fn_8017FA1C(void);
extern MM* fn_8013B9A8(void);
extern void fn_80312344(void*, void*);
extern void fn_80312318(void*);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312654(void*, int, f32);
extern void* fn_8000FB88(void);
extern void fn_80307E48(void*, int);
extern void fn_80021784(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021C34(int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80022254(void*, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021860(int, int, int);
extern void fn_80021B68(int);
extern void fn_80304314(int, int, int);
extern void fn_803035E4(int, void*, int);
extern void fn_80021958(int, Color*);
extern void fn_800218A8(int, Color*);
extern void fn_80304538(int, int);
extern Color lbl_804CE0D4;
extern Color lbl_804CE0D8;
static inline void V(Part* e, int dx, int dz, u8 ca, u8 s, u8 t) {
    int x = e->x + dx;
    int z = e->z + dz;
    s16 y = e->y;
    FIFO.s = x; FIFO.s = y; FIFO.s = z;
    FIFO.b = 0xFF; FIFO.b = 0xFF; FIFO.b = 0xFF; FIFO.b = ca;
    FIFO.b = s; FIFO.b = t;
}
static inline void SetK(Color c) { fn_80021958(4, &c); }
static inline void SetC(Color c) { fn_800218A8(4, &c); }

static inline void Quad(Part* e, int i, int sz, u8 ca) { for (; i >= 0; i--, e++) { V(e, -sz, -sz, ca, 0, 0); V(e, sz, -sz, ca, 1, 0); V(e, sz, sz, ca, 1, 1); V(e, -sz, sz, ca, 0, 1); } }
void fn_80145980(RP* p) {
    Mtx mB;
    Mtx mR;
    Mtx mG;
    Mtx mF;
    Mtx mE;
    Mtx mC;
    Mtx mD;
    Tex tex;
/*P*/
    int a;
    int b;
    int c;
    int dx;
    int dz;
    int al;
    int fr;
    int n;
    int n2;
    s16 sz;
    Ent* en;
    int j;
    int k;
    int cnt;
    WP* w;
/*E*/
    w = fn_80083B84(lbl_80386540);
    if (w == 0) return;
    a = w->x54;
    b = w->x58;
    c = w->x5c;
    dx = w->x60 - w->x54;
    dz = w->x68 - w->x5c;
    al = w->x34;
    fn_80006A64(p->x3c, &tex, 7);
    fr = fn_8017FA1C() & 7;
    n = p->x34;
    n2 = p->x36;
    cnt = p->x32;
    switch (w->x32) {
    case 0:
        fn_80312344(fn_8013B9A8()->xe4, &mG);
        break;
    default:
        fn_80312318(&mG);
        break;
    }
    fn_8031292C(&mB, p->x31, p->x31, p->x31);
    fn_80312378(&mG, &mB, &mB);
    fn_80312378(fn_8000FB88(), &mB, &mB);
    fn_8031292C(&mC, 0.00390625f, -0.00390625f, 0.00390625f);
    fn_803128AC(&mD, a, b, c);
    fn_80312378(&mD, &mC, &mE);
    fn_80312378(&mB, &mE, &mE);
    fn_80307E48(&mE, 0);
    fn_80021784(0);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 3, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80303200(0, 0xD, 1, 0, 0);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80022254(&tex, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021EF8(0, 0);
    fn_80021BA4(1, 4, 5, 0);
    fn_80021860(1, 3, 0);
    fn_80021B68(0);
    fn_80304314(0x80, 0, (u16)(n * 0x20));
    for (k = 7; k >= 0; k--) {
        u8 ca = al * (u8)(0xFF - k * 0x1F) / 0xFF; Part* e = p->x40 + n * fr; sz = (k + 1) * 4;
        for (int i = n - 1; i >= 0; i--) { V(e, -sz, -sz, ca, 0, 0); V(e, sz, -sz, ca, 1, 0); V(e, sz, sz, ca, 1, 1); V(e, -sz, sz, ca, 0, 1); e++; }
        fr = (fr + 1) & 7;
    }
    fn_803031CC();
    fn_80302B80(9, 3);
    fn_80303200(0, 9, 1, 3, 0);
    fn_803035E4(9, p->x44, 6);
    fn_80021B2C(1);
    {
        int aa = al * 0x20 / 0xFF;
        {
        Color p1;
        Color m1 = lbl_804CE0D4;
        m1.a = aa;
        *(u32*)&p1 = *(u32*)&m1;
        fn_80021958(4, &p1);
        }
        {
        Color p2;
        Color m2 = lbl_804CE0D8;
        m2.a = aa;
        *(u32*)&p2 = *(u32*)&m2;
        fn_800218A8(4, &p2);
        }
    }
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    fn_80021C34(0);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0xFF, 4);
    fn_80021EF8(0, 4);
    en = p->x48;
    fn_8031292C(&mC, 0.00390625f, -0.00390625f, 0.00390625f);
    fn_803128AC(&mF, -(dx / 2.0f), 0.0f, -(dz / 2.0f));
    fn_803128AC(&mG, dx / 2.0f, 0.0f, dz / 2.0f);
    fn_80304538(6, 0);
    for (j = 0; j < cnt; j++, en++) {
        if (!(en->y < 0.0f)) {
            fn_803128AC(&mD, a, b + en->y, c);
            fn_80312654(&mR, 0x59, 0.017453292f * en->rot);
            fn_80312378(&mF, &mC, &mE);
            fn_80312378(&mR, &mE, &mE);
            fn_80312378(&mG, &mE, &mE);
            fn_80312378(&mD, &mE, &mE);
            fn_80312378(&mB, &mE, &mE);
            fn_80307E48(&mE, 0);
            fn_80021784(0);
            fn_80304314(0xA8, 0, (u16)(n2 * 2));
            for (int q = n2 * 2 - 1; q >= 0; q--) FIFO.s = q;
            en->y -= 1.0f;
        }
    }
}
}

/* ===== fn_80137BC8: 23 words: volatile registers in the tile copy ===== */
#include "game/rL_80133EB4/types.h"
struct MM { u8 pad[0x4C]; u8 x4c, x4d; u8 pad4e[0x8A - 0x4E]; char name[1]; };
struct N { s16 v[4]; void* x8; };
struct Map { u8 p[0x20000]; };
extern "C" {
extern const char lbl_803694D4[];
extern u8 lbl_803EC898[];
extern void fn_80290DDC(char*, const char*, ...);
extern int fn_80076F54(char*);
extern void* fn_80077064(char*);
extern u8 fn_8011D1E4(void*);
extern f32 fn_801146A8(void*, int, int, int);
extern void fn_80114818(void*, int, int);
extern void fn_80114850(void*, int, int);
extern void fn_8031356C(Vec*, Vec*, Vec*);
extern void fn_803134C4(Vec*, Vec*);
extern f32 fn_8031354C(Vec*, Vec*);
static const u8 sPad[0x48] = {0x46};
static const Vec sA = {1.0f, 0.0f, 0.0f};
static const Vec sB = {0.0f, 1.0f, 0.0f};
static const Vec sC = {-1.0f, 0.0f, 0.0f};
static const Vec sD = {0.0f, -1.0f, 0.0f};
struct Mp { u8 p[0x15422]; s16 h[0x4005]; s16 l[1]; };
static inline void Put(Mp* g, int idx, s16 a, s16 b) {
    u8* p = (u8*)g + idx * 2;
    *(s16*)(p + 0x15422) = a;
    *(s16*)(p + 0x1D42C) = b;
}
void fn_80137BC8(MM* mm) {
    char path[0x40];
/*P*/
    Mp* g;
    int ofs;
    int y2;
    u8* row;
    int x2;
    N* base;
    N* extra;
    u16* a;
    u16* bb;
    int x;
    int y;
    N* n1;
    N* n2;
    const char* s;
    u16* b;
/*E*/
    base = 0;
    a = 0;
    fn_80290DDC(path, lbl_803694D4 + 0x104, mm->name);
    if (fn_80076F54(path)) base = (N*)fn_80077064(path);
    fn_80290DDC(path, lbl_803694D4 + 0x113, mm->name);
    if (fn_80076F54(path)) a = (u16*)fn_80077064(path);
    s = lbl_803694D4;
    fn_80290DDC(path, s + 0x121, mm->name);
    if (fn_80076F54(path)) {
        extra = (N*)fn_80077064(path);
        fn_80290DDC(path, s + 0x12E, mm->name);
        b = (u16*)fn_80077064(path);
    } else {
        extra = base;
        b = a;
    }
    if (base) {
        bb = b;
        y = 0;
        g = (Mp*)lbl_803EC898;
        for (; y < mm->x4d; y++) {
            ofs = (s8)y * 0x40;
            row = (u8*)g + ofs;
            for (x = 0; x < mm->x4c; x++) {
                n1 = &base[*a++];
                n2 = &extra[*bb++];
                u8 m = fn_8011D1E4(n1->x8);
                int xx = (s8)x;
                int i;
                u8* rr;
                rr = row + xx;
                i = xx + ofs;
                rr[0x100D] = m;
#define H(e) (*(s16*)((u8*)g + (e) * 2 + 0x15422))
#define L(e) (*(s16*)((u8*)g + (e) * 2 + 0x1D42C))
                /*A*/ /*B*/
            }
        }
        for (y2 = 0; y2 < mm->x4d; y2++) {
            for (x2 = 0; x2 < mm->x4c; x2++) {
                f32 h[4];
                h[0] = fn_801146A8(lbl_803EC898, (s8)x2, (s8)y2, 0);
                h[1] = fn_801146A8(lbl_803EC898, (s8)x2, (s8)y2, 1);
                h[2] = fn_801146A8(lbl_803EC898, (s8)x2, (s8)y2, 2);
                h[3] = fn_801146A8(lbl_803EC898, (s8)x2, (s8)y2, 3);
                if (h[0] == h[1] && h[1] == h[2] && h[2] == (f32)(f64)h[3]) {
                    fn_80114818(lbl_803EC898, (s8)x2, (s8)y2);
                } else {
                    Vec p0 = *(Vec*)&sA; p0.z = h[1] - h[0];
                    Vec p1 = *(Vec*)&sB; p1.z = h[2] - h[0];
                    Vec n0;
                    Vec q0 = *(Vec*)&sC; q0.z = h[2] - h[3];
                    Vec q1 = *(Vec*)&sD; q1.z = h[1] - h[3];
                    Vec nn;
                    fn_8031356C(&p0, &p1, &n0);
                    fn_8031356C(&q0, &q1, &nn);
                    fn_803134C4(&n0, &n0);
                    fn_803134C4(&nn, &nn);
                    f32 d = fn_8031354C(&n0, &nn);
                    if (d < 1.001f && d > 0.999f) {
                        fn_80114818(lbl_803EC898, (s8)x2, (s8)y2);
                    } else {
                        fn_80114850(lbl_803EC898, (s8)x2, (s8)y2);
                    }
                }
            }
        }
    }
}
}

/* ===== fn_80148D44: 12 words: li r28 must be hoisted last, and t must take r23/r24 ===== */
#include "game/rL_80133EB4/talk.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct SB { u8 l : 1; u8 n : 7; };
static inline void F18(Talk* t) { if (t->x18) { fn_800D42A0(t->x18); t->x18 = 0; } }
static inline void F14(Talk* t) { if (t->x14) { fn_80081A90(t->x14); t->x14 = 0; } }
extern u8 lbl_80413F10[];
extern void fn_8014B244(Talk*);

struct TF { u32 f; u16 ctr; };
#define CUR (*(u8**)&lbl_804181AC.cur)
static inline BOOL IsSjisB(u8 c, const u8* p) {
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        c = p[1];
        if ((c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFC)) return 1;
    }
    return 0;
}
extern u8 lbl_80386B70[], lbl_80386B64[];
extern int fn_80149434(Talk*, char**);
extern int fn_80085708(void*);
extern int fn_801513E4(void*);
extern void fn_80151818(void*, void*);
extern void fn_80151CC4(void*, void*);
extern int fn_800CAB40(u8*);
extern void fn_8014EE28(void*, int);
extern void fn_80151360(void*, int);
extern void fn_8014EF58(void*);
static inline u8* CurP(Talk* t) {
    u8* r;
    if (t->x1e8) return (u8*)t->x21c[0];
    r = (u8*)t->x240;
    if (r == 0) r = (u8*)t->x21c[0];
    return r;
}

struct SF { u32 a : 3; u32 b : 2; u32 c : 21; u32 d : 1; u32 e : 5; };
extern u8 lbl_803CAB38[];
extern u8 lbl_80386B30[];
extern u8 lbl_80386C3C[], lbl_80386C4C[], lbl_80386C5C[], lbl_80386C6C[];
extern u32 lbl_804CA738;
extern u32 fn_80331194(void);
extern SF* fn_80060728(void*);
extern int fn_800C7F90(void);
extern int fn_80148634(void);
extern void fn_8014D220(u32*);
extern u8* fn_80081194(void*, void*);
extern void fn_80253EE4(void*, f32);
extern void fn_800C642C(void*);
extern void fn_800C63F0(void*, int);
#define U1EC (*(u16*)&t->x1ec)
#define U1EE (*(u16*)&t->x1ee)
#define U1F0 (*(u16*)&t->x1f0)
static inline void Inc() { ((TF*)&lbl_804CB878)->ctr = ((TF*)&lbl_804CB878)->ctr + 1; }
static inline void Inc3(TF* f) { f->ctr = f->ctr + 1; }
static inline int Step(void) {
    int n;
    int i;
retry:
    ((TF*)&lbl_804CB878)->ctr = ((TF*)&lbl_804CB878)->ctr + 1;
    switch (fn_80149434(&lbl_804181AC, &lbl_804181AC.cur)) {
    case 0:
        return 0;
    case 2:
        return 2;
    case 1:
        goto retry;
    case 4:
    default:
        break;
    }
    if (fn_80085708(lbl_80386B70) || fn_80085708(lbl_80386B64)) return 2;
    if (fn_801513E4(CurP(&lbl_804181AC))) {
        fn_80151818(CurP(&lbl_804181AC), lbl_804181AC.proc);
        return 2;
    }
    if (!(lbl_804CB700 & 3) && CurP(&lbl_804181AC)[0x80] == 0) {
        fn_80151CC4(CurP(&lbl_804181AC), lbl_804181AC.proc);
        return 2;
    }
    fn_8014B244(&lbl_804181AC);
    {
        u8 c = *CUR;
        if ((s32)c == 0x23) {
            n = fn_800CAB40(CUR);
            for (i = 0; i < n; i++) {
                fn_8014EE28(lbl_80413F10, (s8)*CUR);
                fn_80151360(CurP(&lbl_804181AC), (s8)*CUR++);
            }
            goto retry;
        } else {
            if (!IsSjisB(c, CUR)) {
                fn_80151360(CurP(&lbl_804181AC), (s8)c);
                fn_8014EE28(lbl_80413F10, (s8)*CUR++);
            } else {
                fn_80151360(CurP(&lbl_804181AC), (s8)c);
                fn_8014EE28(lbl_80413F10, (s8)*CUR++);
                fn_80151360(CurP(&lbl_804181AC), (s8)*CUR);
                fn_8014EE28(lbl_80413F10, (s8)*CUR++);
            }
            *(u16*)&lbl_804181AC.x1ec = *(u16*)&lbl_804181AC.x1f0;
        }
    }
    return 3;
}
static inline u8* CurActor(Talk* t) {
    int c = t->cur200;
    if (c < 0) return 0;
    c = t->x19c[c];
    if (c < 0) return 0;
    return t->actor[c];
}
static inline void Run(int limit) {
    int i;
    for (i = 0; i < limit; i++) {
        int r = Step();
        if (r == 0) {
            fn_80083B78(lbl_804181AC.proc);
            break;
        }
        if (r != 3) break;
    }
}
void fn_80148D44(void) {
/*P*/
    int limit;
    Talk* t1;
    Talk* t2;
    Talk* t3;
/*E*/
    fn_8014D220(&lbl_804CB878);
    t1 = &lbl_804181AC;
    if (t1->x1ea) {
        if (fn_800C7F90()) return;
        t1->x1ea = 0;
    }
    {
        Talk* t = &lbl_804181AC;
        if (t->x1e9 && fn_800C7F90()) return;
    }
    {
        Talk* t = &lbl_804181AC;
        u32 a = *(volatile u32*)&lbl_804CB878;
        u32 f = lbl_804CB878;
        t->x1f4--;
        if (a & 0x20000) {
            limit = 0xFFFF;
        } else if (f & 0x40000) {
            limit = 1;
        } else {
            SF* q = fn_80060728(lbl_803CAB38);
            limit = 1;
            if (q->b == 3) limit = 0xFFFF;
        }
    }
    if ((lbl_804CB878 & 4) && !(lbl_804CB700 & 3)) {
        u8* r = fn_80081194(lbl_80386B30, lbl_804181AC.proc);
        *(Talk**)(r + 0x30) = &lbl_804181AC;
        *(int*)(r + 0x34) = 0;
        return;
    }
    if (fn_80148634()) {
        Talk* t = &lbl_804181AC;
        int z = 0;
        limit = 0xFFFF;
        t->x1f4 = z;
    }
    if (lbl_804CB700 & 3) {
        fn_80083B78(lbl_804181AC.proc);
        return;
    }
    {
        Talk* t = &lbl_804181AC;
        if (t->x1f4 != 0) return;
    }
    {
        int d;
        if (lbl_804CB878 & 0x40000) {
            d = 6;
        } else {
            switch (fn_80060728(lbl_803CAB38)->b) {
            case 0: d = 10; break;
            case 1: d = 4; break;
            case 2: d = 1; break;
            case 3: d = 1; break;
            default: d = 4; break;
            }
        }
        lbl_804181AC.x1f4 = d;
    }
    Run(limit);
    {
#define t t2
        t2 = &lbl_804181AC;
        if (U1EC == 0 && !(lbl_804CB878 & 0x10000) && lbl_804CA738 != fn_80331194() - 1) {
            lbl_804CA738 = fn_80331194();
            if (fn_80060728(lbl_803CAB38)->d == 0) {
                switch (t->x1f3) {
                case 0: break;
                case 1: fn_80253EE4(lbl_80386C6C, 0.0f); break;
                case 2: fn_80253EE4(lbl_80386C5C, 0.0f); break;
                case 3: fn_80253EE4(lbl_80386C4C, 0.0f); break;
                case 4: fn_80253EE4(lbl_80386C3C, 0.0f); break;
                }
            }
        }
#undef t
    }
    {
        u8* a = CurActor(&lbl_804181AC);
        if (a) {
            Talk* t = &lbl_804181AC;
            u16 c = U1EC;
            if (c != U1EE) {
                switch (c) {
                case 0: fn_800C642C(a); break;
                case 0x20: fn_800C642C(a); fn_800C63F0(a, 0x20); break;
                case 8: fn_800C642C(a); fn_800C63F0(a, 8); break;
                }
            }
        }
    }
    {
        Talk* t = &lbl_804181AC;
        U1EE = U1EC;
    }
}
}

/* ===== fn_80139A7C: tail only: the outer count loop must not fold (li r0,4; addi r3,0x15; bdnz), and two li 2 must stay separate ===== */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct QT {
    u8 split, vis;
    u16 count;
    u8 pad4[0x1C - 4];
    void* a, *b;
    QT* child[4];
};
struct Cam { u8 pad[0xC]; f32 xc, x10; u8 pad14[0x148 - 0x14]; f32 x148, x14c; };
struct Grp { u8 p[0xC0]; };
struct MM {
    void* x0;
    void* x4;
    Grp* x8;
    void* xc;
    void* x10;
    void* x14;
    void* x18;
    u8 pad1c[0x50 - 0x1C];
    s16 x50, x52;
    u8 pad54[0x7C - 0x54];
    void* x7c;
    QT* x80;
    QT* x84;
    s16 x88;
    char name[0xB1 - 0x8A];
    u8 xb1;
    u8 padb2[2];
    u32 xb4;
    u8 padb8[0xC4 - 0xB8];
    f32 xc4, xc8;
    u8 padcc[4];
    f32 xd0;
};
extern "C" {
extern long long OSGetTime(void);
extern char* strcpy(char*, const char*);
extern u8 lbl_80386148[];
extern const char lbl_803694D4[];
extern u8 lbl_803EC898[];
extern void fn_8013A054(MM*);
extern void* fn_80081050(void*, int);
extern void fn_80290DDC(char*, const char*, ...);
extern void* fn_8017F37C(char*, const char*, const char*);
extern u32 fn_8023F9F4(void*);
extern void* fn_8023F1A4(void*, void*);
extern void* fn_80075D78(void*);
extern void fn_8010DB48(char*);
extern void fn_80136164(MM*);
extern void fn_80136348(MM*);
extern void fn_8013677C(MM*);
extern void fn_801369BC(MM*);
extern int fn_80076F54(char*);
extern void* fn_80077064(char*);
extern void* fn_800791B0(int);
extern void* fn_801C9FC4(Grp*, void*, char*);
extern void fn_8013608C(MM*);
extern void fn_801379F8(MM*, int);
extern void fn_801475F4(void);
extern void fn_8013AC48(MM*);
extern void fn_8013A8D8(MM*, int);
extern void fn_8013AF10(MM*);
extern Cam* fn_8000F470(void);
extern void fn_8000FA18(int, f32, f32);
extern void* fn_8001D3B4(const char*);
extern void* fn_801436DC(void*);
extern void* fn_80146A4C(void*);
extern void fn_8013A638(MM*);

static inline QT* Alloc(MM* mm, u8 kind) {
    QT* q = &mm->x84[mm->x88++];
    q->split = kind;
    q->a = 0;
    q->b = 0;
    q->count = 0;
    q->vis = 0;
    q->child[0] = 0;
    q->child[1] = 0;
    q->child[2] = 0;
    q->child[3] = 0;
    return q;
}

static inline QT* B0(MM* mm, int k) { QT* q = Alloc(mm, k); return q; }
static inline QT* B1(MM* mm, int k) { QT* q = Alloc(mm, k); if (k > 0) { for (int i = 0; i < 4; i++) q->child[i] = B0(mm, k - 1); } return q; }
static inline QT* B2(MM* mm, int k) { QT* q = Alloc(mm, k); if (k > 0) { for (int i = 0; i < 4; i++) q->child[i] = B1(mm, k - 1); } return q; }
static inline QT* B3(MM* mm, int k) { QT* q = Alloc(mm, k); if (k > 0) { for (int i = 0; i < 4; i++) q->child[i] = B2(mm, k - 1); } return q; }
static inline int C0(int k) { return 1; }
static inline int C1(int k) { int n = 1; if (k > 0) { for (int i = 0; i < 4; i++) n += C0(k - 1); } return n; }
static inline int C2(int k) { int n = 1; if (k > 0) { for (int i = 0; i < 4; i++) n += C1(k - 1); } return n; }
static inline int C3(int k) { int n = 1; if (k > 0) { for (int i = 0; i < 4; i++) n += C2(k - 1); } return n; }
int fn_80139A7C(MM* mm, const char* name, void* heap) {
    char path[0x40];
    char p2[0x40];
    char p3[0x40];
    /*P*/
    void* a;
    const char* s;
    Grp* g;
    int i;
    void* d;
    /*E*/
    OSGetTime();
    fn_8013A054(mm);
    mm->x10 = fn_80081050(lbl_80386148, 4);
    strcpy(mm->name, name);
    switch (mm->xb1) {
    case 0: {
        s = lbl_803694D4;
        fn_80290DDC(path, s + 0x167, s + 0x155, name);
        a = fn_8017F37C(path, s + 0x15B, s + 0x16D);
        if (fn_8023F9F4(a) == 0x40000) a = fn_8017F37C(path, s + 0x15B, s + 0x172);
        if (fn_8023F9F4(a) == 0x40000) return 0;
        mm->x0 = fn_8023F1A4(a, heap);
        {
            s = lbl_803694D4;
            mm->x4 = fn_80075D78(fn_8017F37C(path, s + 0x177, 0));
            mm->xd0 = 0.2f;
            fn_8010DB48(mm->name);
            fn_80136164(mm);
            *(f32*)(lbl_803EC898 + 0x1D424) = mm->xc4;
            *(f32*)(lbl_803EC898 + 0x1D428) = mm->xc8;
            fn_80136348(mm);
            fn_8013677C(mm);
            fn_801369BC(mm);
            fn_80290DDC(p2, s + 0x99, mm->name);
        }
        if (fn_80076F54(p2)) {
            d = fn_80077064(p2);
            if (mm->x50 > 0) mm->x8 = (Grp*)fn_800791B0(mm->x50 * 0xC0);
            else mm->x8 = 0;
            g = mm->x8;
            for (i = 0; i < mm->x50; i++, g++) d = fn_801C9FC4(g, d, path);
        }
        fn_8013608C(mm);
        fn_801379F8(mm, 1);
        fn_801475F4();
        break;
    }
    case 1:
    case 2:
    case 3: {
        s = lbl_803694D4;
        fn_80290DDC(path, s + 0x167, s + 0x15F, name);
        a = fn_8017F37C(path, s + 0x164, s + 0x16D);
        if (fn_8023F9F4(a) == 0x40000) a = fn_8017F37C(path, s + 0x164, s + 0x172);
        if (fn_8023F9F4(a) == 0x40000) return 0;
        mm->x0 = fn_8023F1A4(a, heap);
        {
            s = lbl_803694D4;
            mm->x4 = fn_80075D78(fn_8017F37C(path, s + 0x177, 0));
            mm->xd0 = 3.0f;
            fn_80136164(mm);
            fn_80136348(mm);
            fn_8013677C(mm);
            fn_801369BC(mm);
            fn_80290DDC(p3, s + 0x99, mm->name);
        }
        if (fn_80076F54(p3)) {
            d = fn_80077064(p3);
            if (mm->x50 > 0) mm->x8 = (Grp*)fn_800791B0(mm->x50 * 0xC0);
            else mm->x8 = 0;
            g = mm->x8;
            for (i = 0; i < mm->x50; i++, g++) d = fn_801C9FC4(g, d, path);
        }
        fn_8013608C(mm);
        break;
    }
    case 4:
        mm->x0 = 0;
        mm->x4 = 0;
        mm->x8 = 0;
        mm->xc = 0;
        mm->x50 = 0;
        mm->x52 = 0;
        mm->xd0 = 3.0f;
        break;
    }
    fn_8013AC48(mm);
    fn_8013A8D8(mm, 0);
    mm->x84 = (QT*)fn_800791B0(C3(3) * 0x34);
    mm->x88 = 0;
    mm->x80 = B3(mm, 3);
    fn_8013AF10(mm);
    {
        Cam* c = fn_8000F470();
        c->x14c = 30.0f;
        c->x148 = c->xc / c->x10;
        fn_8000FA18(0, 2.0f, 2000.0f);
    }
    {
        s = lbl_803694D4;
        fn_8023F1A4((void*)(s + 0x17F), 0);
        mm->x7c = fn_8001D3B4(s + 0x18F);
    }
    mm->x14 = fn_801436DC(mm->x10);
    mm->x18 = fn_80146A4C(mm->x10);
    fn_8013A638(mm);
    mm->xb4 |= 0x40000000;
    OSGetTime();
    return 1;
}
}

/* ===== fn_80135C44: register ranks only: n r31, need r30, params above i/e ===== */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw on
extern "C" {
extern int fn_801CA274(Mesh*, int, int);
int fn_80135C44(MapModel* mm, Mesh* m, Mesh** list, int n);
static inline Mesh* Find(MapModel* mm, u32 need, int a, int b) {
    int i;
    Mesh* e;
    for (i = mm->nMesh - 1; i >= 0; i--) {
        e = &mm->mesh[i];
        u32 g = e->group->flags;
        if (!(g & 0x10) && (need == 0 || need == (need & g)) && fn_801CA274(e, a, b)) return e;
    }
    return 0;
}
static inline int Body(MapModel* mm, Mesh* m, Mesh** list, int n) {
    u32 need;
    if (m == 0) return n;
    {
        Mesh** q = list;
        int k;
        for (k = 0; k < n; k++, q++) {
            if (*q == m) return n;
        }
    }
    list[n++] = m;
    need = m->group->flags | 0x200000;
    n = fn_80135C44(mm, Find(mm, need, m->x0 - 1, (m->y0 + m->y1) / 2), list, n);
    n = fn_80135C44(mm, Find(mm, need, m->x1 + 1, (m->y0 + m->y1) / 2), list, n);
    n = fn_80135C44(mm, Find(mm, need, (m->x0 + m->x1) / 2, m->y0 - 1), list, n);
    return fn_80135C44(mm, Find(mm, need, (m->x0 + m->x1) / 2, m->y1 + 1), list, n);
}
#pragma push
#pragma auto_inline off
int fn_80135C44(MapModel* mm, Mesh* m, Mesh** list, int n) { return Body(mm, m, list, n); }
#pragma pop
}

/* ===== fn_8013AE18: 14 words: volatile FP order ===== */
#include "game/rL_80133EB4/map3d.h"
struct Env { u8 pad[0x6A]; u8 x6a, x6b; f32 x6c, x70, x74; };
extern "C" {
extern void fn_8025095C(f32, f32);
extern void fn_80250A08(f32, f32);
extern void fn_80257AC0(f32, f32);
extern void fn_80257B6C(f32, f32);
extern void fn_80257A14(f32, f32);
static inline void Set5(f32 c, f32 b, f32 x, f32 y, f32 z) { fn_8025095C(c, 0.0f); fn_80250A08(b, 0.0f); fn_80257AC0(x, 0.0f); fn_80257B6C(y, 0.0f); fn_80257A14(z, 0.0f); }
void fn_8013AE18(MapModel* mm) {
    Env* e = (Env*)mm;
/*A*/ /*B*/
}
}

/* ===== fn_8013E77C/fn_801386AC/fn_80143374: volatile register order (the rest of this file matched) ===== */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
struct Wx { u8 pad[0x31]; u8 x31; };
struct MA { u8 pad[0x18]; Wx* x18; };
class VO { public: u8 pad[0x6C]; virtual void v(Vec*); };
struct H44 { u8 pad[0x44]; VO* x44; };
struct Grid { s32 w, h; u8 pad[0x20000]; };
struct P14 { u8 pad[8]; f32 x8, xc; };
struct C5 { u8 pad[0x14]; P14* x14; };
struct Cm { f32 x0, x4, x8, xc, x10; };
extern "C" {
extern u8 lbl_804CB834;
extern void fn_80146BAC(Wx*, int);
extern void fn_80146B40(Wx*);
void fn_8013B8D0(MA* m) {
    Wx* w = m->x18;
    if (w) {
        int cur = lbl_804CB834;
        if (cur != w->x31) fn_80146BAC(w, cur);
        fn_80146B40(w);
    }
}
void fn_8013C0F8(H44* h) {
    Vec a = {0.0f, 0.0f, 0.0f};
    Vec b = {0.0f, 0.0f, 0.0f};
    VO* o = h->x44;
    o->v(&a);
}
extern u8 lbl_804CB84C;
extern s8 lbl_804CB84D, lbl_804CB84E, lbl_804CB84F, lbl_804CB850;
extern u8 lbl_804CB852;
extern Grid lbl_803EC898;
static inline void Mv(u8 h, u8 w, s8 dx, s8 y) {
    s8 x = lbl_804CB84D;
    s8 dy = lbl_804CB850;
    lbl_804CB852 = 1;
    int a = x + w - dx;
    int b = y + h - dy;
    lbl_804CB84D = a % w;
    lbl_804CB84E = b % h;
}
void fn_8013E77C(void) {
    if (lbl_804CB84C) {
        Mv(lbl_803EC898.h, lbl_803EC898.w, lbl_804CB84F, lbl_804CB84E);
    }
}
extern f32 lbl_804CB854, lbl_804CB858;
static inline void Set4(C5* c, f32 k, f32 n) { P14* p = c->x14; p->x8 = k; p->xc = -n; }
void fn_80143374(void* a, void* b, C5* c) {
    Set4(c, lbl_804CB854, lbl_804CB858);
}
extern Cm* lbl_804CB85C;
int fn_801386AC(void* a, int x, int y, f32* o) {
    Cm* c = lbl_804CB85C;
    f32 py;
    f32 px;
    f32 oy;
    f32 ox;
    f32 s;
    f32 w;
    f32 h;
    h = c->x10;
    w = c->x8;
    s = h / w;
    px = 0.5f + (f32)x;
    py = 0.5f + (f32)y;
    ox = c->x0 - w * 0.5f;
    oy = c->x4 - c->xc * 0.5f;
    o[2] = 0.0f;
    f32 ax = s * (px - ox);
    f32 ay = s * (py - oy);
    o[0] = ax;
    o[1] = ay;
    if (ax < 0.0f || ay < 0.0f || ax > h || ay > h) return 0;
    return 1;
}
}

/* ===== fn_80138000: 45 words, lis base must take r18 below the params ===== */
void fn_80138000(MapModel* mm, int x0, int y0, int x1, int y1, int both) {
    char path[0x40];
/*P*/
    u16* ids;
    N* nodes;
    int ofs;
    u8* row;
    u16* q;
    int x;
    N* n;
/*E*/
    u8* base = (u8*)lbl_803694D4;
    fn_80290DDC(path, (char*)base + 0x13B, mm->name);
    if (fn_80076F54(path)) {
        nodes = (N*)fn_80077064(path);
        fn_80290DDC(path, (char*)base + 0x148, mm->name);
        ids = (u16*)fn_80077064(path);
        base = (u8*)&lbl_803EC898;
        for (; y0 <= y1; y0++) {
            ofs = (s8)y0 * 0x40;
            row = base + ofs;
            x = x0;
            q = &ids[x0 + y0 * mm->x4c];
            for (; x <= x1; x++) {
                n = &nodes[*q++];
                u8 m = fn_8011D1E4(n->x8);
                int xx = (s8)x;
                row[0x100D + xx] = m;
                u8* b = base + (xx + ofs) * 8;
                s16 v = n->v[0];
                H(b) = v;
                if (both) L(b) = v;
                u8* b1 = b + 2;
                v = n->v[1];
                H(b1) = v;
                if (both) L(b1) = v;
                u8* b2 = b + 4;
                v = n->v[2];
                H(b2) = v;
                if (both) L(b2) = v;
                u8* b3 = b + 6;
                v = n->v[3];
                H(b3) = v;
                if (both) L(b3) = v;
            }
        }
    }
}
