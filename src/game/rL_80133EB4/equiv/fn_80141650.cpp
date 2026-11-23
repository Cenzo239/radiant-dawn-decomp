/* symcheck: r21 review, flag was an artefact. fn_80141650: (a) templates `@20`/`@99` are lbl_80369934/lbl_8036991C
   (12 bytes each equal); stale float temp before fn_8001E6D0. See docs/SCHED_REVIEW.md. */
/* fn_80141650 (0x77C): functionally equal at `sched` level (tools/check_regs.py, round 20): same size and blocks,
 * registers differ and a few instructions are scheduled in another order inside their block. Section of
 * wip/near3.cpp, unchanged. Moved instructions (checked with tools/equiv/dd.py, all independent):
 *   - prologue block: the two template word loads `lwz 0(r5)`, `lwz 8(r5)` (lbl_8036991C) and one `fmuls` sit one or
 *     two slots away from the original's position between float subtractions; none feeds another moved line.
 *   - colour block (about +0x454): `lwz r4,0x30(r30)` and one `lfs` constant load swap places around byte stores to
 *     the stack colour.
 */
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

