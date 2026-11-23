/* symcheck: r21 review, flag was an artefact. fn_80145980: (a) stale r6/r7 before fn_80021958 (reads r3, r4). See
   docs/SCHED_REVIEW.md. */
/* fn_80145980 (0x858): functionally equal at `sched` level (tools/check_regs.py, round 20): same size and blocks,
 * registers differ and a few instructions are scheduled in another order inside their block. Section of
 * wip/near3.cpp, unchanged. Moved instructions (checked with tools/equiv/dd.py, all independent):
 *   - `lwz r19,0x40(r29)` one slot later (between `mullw` and `slwi` that don't use it);
 *   - the vertex countdown `subi r12,r12,1` runs at the start of the fourth-vertex block instead of its end (r12 is
 *     not read in between; the block only writes the GX FIFO);
 *   - colour block after fn_80021B2C: the three `lbz` loads of lbl_804CE0D4 bytes, `slwi r,r28,5`, the `subi` of the
 *     0x80808081 constant and one `stb` to the stack colour are interleaved differently.
 */
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

