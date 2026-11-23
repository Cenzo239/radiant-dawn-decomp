/* symcheck: r21 review, flag was an artefact. fn_801420B0: (a) `...data.0` is lbl_80369910 (0x78 bytes equal);
   other blocks: stale f1-f5 before fn_8001E6D0 (reads r3, r4); stack bytes equal. See docs/SCHED_REVIEW.md. */
/* fn_801420B0 (0xB94): functionally equal at `sched` level (tools/check_regs.py, round 20). New this round.
 * Draws a map-model layer by texture projection in up to three passes (names guessed): pass 1 and 2 project the
 * two scrolling layers (offsets animated through fn_8000AE38, scaled by the work object's x34), pass 3 (only when
 * mm->x55 != 0 and the table has more than one entry) projects the map-origin layer with one of four TEV set-ups.
 * Sibling of fn_80141650 (same projection block, same helpers).
 *
 * Moved instructions (tools/equiv/dd.py): only inside the three long straight-line blocks that build the eye /
 * target / up vectors (float multiplies, `fneg`, template word loads and the stack stores/copies of e, t, u), at
 * instructions 153-202, 336-378 and 485-536 of 741. Every moved store goes to its own stack slot and each slot is read back only after its store in
 * both versions; the rest of the function (all 100 calls and their arguments) is in the original order.
 *
 * Caveats a port must undo:
 *   - The ten vectors below are non-const file statics so that the compiler neither drops the unused ones nor
 *     reuses their words across calls. In the original they are compiler-made templates of local initialisers in
 *     .rodata (`Vec e = {0,1,0};` and so on); with local initialisers this file is 1 word from the original apart
 *     from the pool offsets (the pool then starts with this function's templates instead of the three vectors of
 *     fn_80141334/fn_80141650 that come first in the real translation unit). sE0, sU0, sU1, sU2 belong to those
 *     other functions and are here only to keep the real offsets.
 *   - PROJ is a macro with explicit copies of t and e because that reproduces the stack layout (t, e, u, t copy,
 *     e copy per pass); the source most likely passes the vectors by value to an inline (see `View` in
 *     equiv/fn_80141650.cpp). `View` in this file is unused.
 *   - T() zeroes the vector through int stores, a codegen device from the sibling's draft.
 */
#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct Tex { u8 p[0x20]; };
struct Color { u8 r, g, b, a; };
struct F3 { Mtx mo3; Mtx mq3; Mtx mv3; Mtx mo2; Mtx mq2; Mtx mv2; Mtx mo1; Mtx mq1; Mtx mv1; Mtx ml; Mtx mp; };
struct Ent { u8 pad[4]; u16 x4; };
struct Tbl { u8 pad[6]; u8 x6; u8 pad7[0x14 - 7]; Ent* x14; };
struct Wk { u8 pad[0x34]; f32 x34; };
struct Obj { u8 pad[8]; u8 r, g, b, a; u8 padc[0x81 - 0xC]; s8 x81; };
struct MM {
    u8 pad0[0x14];
    Wk* x14;
    u8 pad18[0x54 - 0x18];
    u8 x54, x55;
    u8 pad56[0x60 - 0x56];
    u8 x60;
    u8 pad61[0xAB - 0x61];
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
extern void* fn_80007F10(Obj*);
extern u8* fn_80010C18(int);
extern u8* fn_80010BB0(int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021958(int, Color*);
extern void fn_800218A8(int, Color*);
extern void fn_80011280(u8*);
extern void fn_8000AE38(f32, void*, int, f32*);
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
extern void* fn_80012170(void);
extern void* fn_80012218(void*);
extern void fn_80307F10(void*, void*, int);
extern void fn_80021F7C(void*, int, int, void*);
extern void fn_80022254(void*, void*);
extern void fn_80006A64(void*, void*, int);
extern void fn_80021CB4(void*, void*, void*, int);
extern void fn_80021D18(void*, int, int, int, int, void*);
extern void fn_80021E20(void*, int, int, int, int);
extern void fn_80021D9C(void*, int, int, int, int, void*);
extern void fn_80021E8C(void*, int, int, int, int);
extern void fn_80022050(void*, void*);
extern f32 fn_80140BA4(void);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_80306EA0(void*, Color*);
extern void fn_80141334(void*);
extern void fn_800140A0(void*, void*);

/* This translation unit's .rodata from lbl_80369910 on (real values, checked against the DOL; the function
 * addresses them from one base register, so the offsets must be right). See the caveat in the header. */
static Vec sE0 = {0.0f, 1.0f, 0.0f};   /* +0x00, fn_80141334 */
static Vec sE = {0.0f, 1.0f, 0.0f};    /* +0x0C, eye template, also fn_80141650 */
static Vec sU0 = {0.0f, 0.0f, -1.0f};  /* +0x18, fn_80141334 */
static Vec sU1 = {0.0f, 0.0f, -1.0f};  /* +0x24, fn_80141650 */
static Vec sU2 = {0.0f, 0.0f, -1.0f};  /* +0x30 */
static Vec sS1 = {1.0f, 0.5f, 0.0f};   /* +0x3C */
static Vec sS2 = {0.5f, 1.0f, 0.0f};   /* +0x48 */
static Vec sU3 = {0.0f, 0.0f, -1.0f};  /* +0x54 */
static Vec sU4 = {0.0f, 0.0f, -1.0f};  /* +0x60 */
static Vec sU5 = {0.0f, 0.0f, -1.0f};  /* +0x6C */

static inline void View(MM* mm, Mtx* mv, Mtx* mo, Vec u, Vec t, Vec e) {
    fn_8001E6D0(mm->xe4, mv);
    fn_80312DB4(mm->xe4, &e, &e);
    fn_80312DB4(mm->xe4, &t, &t);
    fn_80312DB4(mv, &u, &u);
    fn_80312AC0(mo, &e, &u, &t);
}
static inline const Vec& T(Vec& t, f32 x, f32 z) { *(int*)&t.x = 0; *(int*)&t.y = 0; *(int*)&t.z = 0; t.x = x; t.z = z; return t; }
#define PROJ(MV, MO, U, X, Z) { \
    Vec t; \
    Vec e = sE; \
    e.x = X; \
    e.z = Z; \
    T(t, X, Z); \
    Vec u = U; \
    Vec tc = t; \
    Vec ec = e; \
    fn_8001E6D0(mm->xe4, MV); \
    fn_80312DB4(mm->xe4, &ec, &ec); \
    fn_80312DB4(mm->xe4, &tc, &tc); \
    fn_80312DB4(MV, &u, &u); \
    fn_80312AC0(MO, &ec, &u, &tc); \
}
static inline void SetK(Color c) { fn_80021958(4, &c); }
static inline void SetA(Color c) { fn_800218A8(4, &c); }
static inline void Set0(void* v, Color c) { fn_80306EA0(v, &c); }

void fn_801420B0(Obj* a, void* b, Tbl* c, void* d) {
    F3 f;
    Tex tex;
    Color col;
    MM* mm;
    Wk* w;
    void* an;
    u8* m;
    int n;
    f32 k5;
    f32 s;
    f32 y;
    mm = fn_8013B9A8();
    if (mm == 0) return;
    w = mm->x14;
    if (w == 0) return;
    an = fn_80007F10(a);
    {
        if (a->x81 < 0) m = fn_80010C18(a->x81);
        else m = fn_80010BB0(a->x81);
    }
    Vec sc = sS1;
    Vec sc2 = sS2;
    f32 r = 3.2f;
    n = c->x14->x4;
    fn_80021B2C(1);
    fn_80021A08(0, 1, 0, 0, 1, 2, 2);
    fn_80021A08(2, 0, 0, 0, 0, 2, 2);
    col.r = a->r * 255 / 128;
    col.g = a->g * 255 / 128;
    col.b = a->b * 255 / 128;
    col.a = a->a * 255 / 255;
    SetK(col);
    SetA(*(Color*)(m + 2));
    fn_80011280(m);
    fn_80019D9C(&f.ml);
    if (an) {
        fn_8000AE38(0.0f, an, 0, &sc.x);
        fn_8000AE38(1.0f, an, 0, &sc.y);
        fn_8000AE38(2.0f, an, 0, &sc2.x);
        fn_8000AE38(3.0f, an, 0, &sc2.y);
    }
    {
        f32 k = w->x34;
        sc.x *= k;
        sc.y *= k;
        sc2.x *= k;
        sc2.y *= k;
    }
    k5 = 5.0f * mm->scale;
    {
        f32 x = -sc.x * k5;
        f32 z = -sc.y * k5;
        s = r * k5;
        y = s;
        PROJ(&f.mv1, &f.mo1, sU3, x, z)
    }
    if (mm->xcc) y = s * -1.0f;
    fn_80312D2C(&f.mq1, -s, s, -y, y, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_80312378(&f.mo1, &f.ml, &f.mo1);
    fn_80312378(&f.mq1, &f.mo1, &f.mp);
    {
        void* q = fn_80011FC4();
        fn_80307F10(&f.mp, q, 0);
        void* g = fn_80011F38();
        void* t = fn_80011E28();
        void* h = fn_80011EB4();
        fn_80006A64(d, &tex, n);
        fn_80022254(&tex, h);
        fn_80021F7C(g, 0, 0, q);
        fn_80021CB4(t, g, h, 4);
        {
            u32 al = mm->x54;
            col.a = al;
            if (al < 0xFF) {
                col.a = fn_8001EF30(al, 0.8f * al, 1.0f, fn_80140BA4());
            }
        }
        void* v = fn_80012170();
        void* u = fn_80012218(v);
        Set0(v, col);
        fn_80022050(t, u);
        fn_80021E20(t, 0xF, 8, 0xA, 0xF);
        fn_80021D18(t, 0, 0, 0, 1, 0);
        fn_80021E8C(t, 7, 7, 7, 6);
        fn_80021D9C(t, 0, 0, 0, 1, 0);
        if (mm->x60 & 1) fn_80141334(t);
    }
    {
        f32 x = -sc2.x * k5;
        f32 z = -sc2.y * k5;
        s = r * k5;
        y = s;
        PROJ(&f.mv2, &f.mo2, sU4, x, z)
    }
    s *= -1.0f;
    if (mm->xcc) y *= -1.0f;
    fn_80312D2C(&f.mq2, -s, s, -y, y, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_80312378(&f.mo2, &f.ml, &f.mo2);
    fn_80312378(&f.mq2, &f.mo2, &f.mp);
    {
        void* q = fn_80011FC4();
        fn_80307F10(&f.mp, q, 0);
        void* g = fn_80011F38();
        void* t = fn_80011E28();
        void* h = fn_80011EB4();
        fn_80022254(&tex, h);
        fn_80021F7C(g, 0, 0, q);
        fn_80021CB4(t, g, h, 4);
        fn_80021E20(t, 0xF, 8, 0xA, 0);
        fn_80021D18(t, 0, 0, 3, 1, 0);
        fn_80021E8C(t, 7, 7, 7, 0);
        fn_80021D9C(t, 0, 0, 0, 1, 0);
        if (mm->x60 & 1) fn_80141334(t);
    }
    if (mm->x55 != 0 && c->x6 > 1) {
        {
            f32 z = 0x40 - mm->xac;
            f32 x = 0x40 - mm->xab;
            s = 64.0f * k5;
            y = s;
            z = k5 * z;
            x = k5 * x;
            PROJ(&f.mv3, &f.mo3, sU5, x, z)
        }
        if (mm->xcc) y = s * -1.0f;
        fn_80312D2C(&f.mq3, -s, s, -y, y, 0.5f, 0.5f, 0.5f, 0.5f);
        fn_80312378(&f.mo3, &f.ml, &f.mo3);
        fn_80312378(&f.mq3, &f.mo3, &f.mp);
        void* q = fn_80011FC4();
        fn_80307F10(&f.mp, q, 0);
        void* g = fn_80011F38();
        void* t = fn_80011E28();
        void* h = fn_80011EB4();
        fn_80006A64(d, &tex, n + 1);
        fn_80022254(&tex, h);
        fn_80021F7C(g, 0, 0, q);
        fn_80021CB4(t, g, h, 4);
        switch (mm->x55) {
        case 1:
            fn_80021E20(t, 0xF, 9, 0xD, 0);
            fn_80021D18(t, 0, 0, 0, 1, 0);
            fn_80021E8C(t, 7, 4, 6, 0);
            fn_80021D9C(t, 1, 0, 0, 1, 0);
            break;
        case 2:
            fn_80021E20(t, 0xF, 9, 0xD, 0);
            fn_80021D18(t, 0, 0, 0, 1, 0);
            fn_80021E8C(t, 7, 7, 7, 0);
            fn_80021D9C(t, 0, 0, 0, 1, 0);
            break;
        case 3:
            fn_80021E20(t, 0xF, 9, 0xD, 0);
            fn_80021D18(t, 1, 0, 0, 1, 0);
            fn_80021E8C(t, 7, 7, 7, 0);
            fn_80021D9C(t, 0, 0, 0, 1, 0);
            break;
        case 4:
            fn_80021E20(t, 0, 0xF, 9, 0xF);
            fn_80021D18(t, 0, 0, 0, 1, 0);
            fn_80021E8C(t, 0, 7, 4, 7);
            fn_80021D9C(t, 0, 0, 0, 1, 0);
            break;
        }
    }
    fn_800140A0(a, b);
}
}
