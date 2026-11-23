/* fn_80182D24 (0xC20): complete draft, class `other` (round 21). 776 of 776 instructions, same frame size
 * (0x320), same calls, constants and branches. What differs from the original:
 *   1. The arrow-head size 32.0f. The original keeps it as an unnamed loop-hoisted constant spilled as a double
 *      (`stfd f0,0x1B8(r1)` before the loop, `lfd` at both uses) and does NOT fold `0.5f * 32.0f`. Here it is the
 *      named block local `sz`, which gives the same instructions with a float spill (`stfs`/`lfs` at 0x190(r1));
 *      that shifts five neighbouring spill slots (pi, sx and the constants 608, 760, 896, 100) by 4 or 8 bytes.
 *      Tried without success: inline parameter (Half(32.0f), a HalfWH and a Quad inline: all fold to 16.0f),
 *      inline returning 32.0f, `const f32`, file-level `static const f32`, `extern const f32 lbl_804CE684`, int and
 *      u8 size, f64 size, function-level `sz` assigned at three places, `hh = 32.0f; hh *= 0.5f` (right spill,
 *      but a second `lfs` and swapped `fmuls` operands).
 *   2. Two argument set-ups are scheduled differently: before the first fn_80182B48 call the original loads
 *      `ln->d` before `mr r3,r20` and the 0.0f; after the atan call the original does `frsp f14,f1` before the
 *      `fcmpo` and keeps the angle in f14 (ours: f2, then f14 at the fmadds).
 *   3. Saved registers are numbered differently throughout (regs-level differences only).
 * The eight colour constants are separate anonymous 4-byte objects here; the original reads them from
 * lbl_804CE63C + 0..0x1F (same bytes, compared by hand).
 * Notes for a port:
 *   - The per-case `C4 a, b` locals and the six u8 copies only reproduce the original's dead stack stores; a 4x2
 *     colour table indexed by `kind` (default: black/white) is what it means.
 *   - Colour blend: timer < 1500 eases a->b (fn_8017F68C mode 4), else b->a with timer - 1500 (mode 1); each
 *     channel is scaled by ln->bright / 100.
 *   - `pl`/`pr` (left/right strip edge of the previous point) are 12-byte vectors whose z is never written.
 *   - `s = 1.0f - c` is computed before the branches as in the original; nx/ny is the unit normal of the segment
 *     scaled by half the line width from lbl_8041C9D8[wid][0] (a table of doubles loaded from
 *     gmap/curve/linedefine%d.bin; fn_80181788.cpp declares it `void*[8]`).
 *   - If a line has n <= 1 the arrow-head block reads dx/dy uninitialised (as the original does; n > 3 is
 *     required there, so it cannot happen).
 *   - WGPIPE is the GX FIFO at 0xCC008000; Pos3/Col4/Tex2 are GXPosition3f32/GXColor4u8/GXTexCoord2f32.
 *   - GMap/Line/CData are local views of the structs in fn_801820CC.cpp and equiv/fn_80182B48.cpp.
 */
/* fn_80182D24: world map: draws the up to eight animated route lines of the map object. Each active line is a
 * textured triangle strip along its curve (fn_80182B48 evaluates the curve at distance k), coloured by a blend of
 * two colours over a 3000-tick cycle, with an arrow head quad at the end when the line has more than 3 points.
 * Names guessed. */
#pragma auto_inline off
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct V3 { f32 x, y, z; } V3;
typedef struct P2 { f32 x, y; } P2;
typedef struct Mtx34 { f32 m[3][4]; } Mtx34;
typedef struct CData { u8 pad[0x1c]; int len; int n; int wid; int kind; void* keys; } CData;
typedef struct Line { u8 p0[4]; u16 flags; u16 n; s16 alpha; s16 bright; CData* d; } Line;   /* 0x10 */
typedef struct GMode { u8 p0[4]; u16 mode; } GMode;
typedef struct GMap {
    void* x0; void* x4; u8 pad8[0x10 - 8]; f32 x10, x14, x18, x1c, x20, x24; u8 x28; u8 pad29[0x30 - 0x29];
    GMode* x30; u8 pad34[0x194 - 0x34]; Line line[8]; u8 pad214[0x240 - 0x214]; u32 timer; f32 x244;
} GMap;
typedef union Fifo { u8 u8; f32 f32; } Fifo;
volatile Fifo WGPIPE : 0xCC008000;
extern f64* lbl_8041C9D8[8];              /* gmap/curve/linedefine%d.bin: {width, length} as doubles */
extern void fn_80021860(int, int, int);
extern void fn_80021808(int, int, int, int, int);
extern void fn_800217CC(int);
extern void fn_80021784(int);
extern void fn_80021B68(int);
extern void fn_80006A64(void*, void*, int);
extern void fn_80305D98(void*, int, int);
extern void fn_80022254(void*, int);
extern void fn_803128AC(void*, f32, f32, f32);      /* translation matrix */
extern void fn_8031292C(void*, f32, f32, f32);      /* scale matrix */
extern void fn_80312654(void*, int, f32);           /* rotation matrix about an axis */
extern void fn_80312378(void*, void*, void*);       /* concat */
extern void fn_80307E48(void*, int);
extern void fn_80304314(int, int, int);             /* GXBegin */
extern double fn_80295CF0(double);                  /* sqrt */
extern double fn_802952C8(double);                  /* atan */
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern int fn_80182B48(f32 t, void* self, CData* d, f32* out);
void fn_80182D24(GMap* m);
}
static inline void Pos3(f32 x, f32 y, f32 z) { WGPIPE.f32 = x; WGPIPE.f32 = y; WGPIPE.f32 = z; }
static inline void Col4(u8 r, u8 g, u8 b, u8 a) { WGPIPE.u8 = r; WGPIPE.u8 = g; WGPIPE.u8 = b; WGPIPE.u8 = a; }
static inline void Tex2(f32 s, f32 t) { WGPIPE.f32 = s; WGPIPE.f32 = t; }

void fn_80182D24(GMap* m) {
    u8 tex[0x20];
    Mtx34 mA, mC, mE, mB, mD;
    V3 cur, prev;
    V3 pl, pr;
    Line* ln;
    int i;
    CData* d;
    int k;
    u8 ar, ag, ab, br, bg, bb;
    int cr, cg, cb;
    u8 al;
    f32 z;
    f32 pi;
    f32 sx, sy;
    f32 bri;
    f32 v, dv;
    f32 pdx, pdy, dx, dy;
    f32 c, s, nx, ny, w;
    f32 ang;
    f32 hw, hh;

    z = m->x244 - 8.0f;
    pi = 3.141592f;
    fn_80021860(1, 1, 1);
    fn_80021808(4, 0x20, 0, 7, 0);
    fn_800217CC(0);
    for (i = 0, ln = m->line; i < 8; i++, ln++) {
        d = ln->d;
        if (!(ln->flags & 1)) continue;
        sx = m->x18 * m->x20 / 608.0f;
        if (m->x30->mode == 0) sy = 760.0f * m->x1c / 448.0f;
        else if (m->x30->mode == 3) sy = 896.0f * m->x1c / 448.0f;
        else sy = m->x1c * m->x24 / 448.0f;
        switch (d->kind) {
        case 0: {
            C4 a = {0x60, 0x2E, 0x13, 0xFF}; C4 b = {0xA0, 0x41, 0x0D, 0xFF};
            ar = a.r; ag = a.g; ab = a.b; br = b.r; bg = b.g; bb = b.b;
            break;
        }
        case 1: {
            C4 a = {0x00, 0xA3, 0x76, 0xFF}; C4 b = {0x0E, 0xDB, 0xAF, 0xFF};
            ar = a.r; ag = a.g; ab = a.b; br = b.r; bg = b.g; bb = b.b;
            break;
        }
        case 2: {
            C4 a = {0x00, 0x34, 0x71, 0xFF}; C4 b = {0x00, 0x72, 0xBC, 0xFF};
            ar = a.r; ag = a.g; ab = a.b; br = b.r; bg = b.g; bb = b.b;
            break;
        }
        default: {
            C4 a = {0x00, 0x00, 0x00, 0xFF}; C4 b = {0xFF, 0xFF, 0xFF, 0xFF};
            ar = a.r; ag = a.g; ab = a.b; br = b.r; bg = b.g; bb = b.b;
            break;
        }
        }
        bri = ln->bright / 100.0f;
        if (m->timer < 1500) {
            cr = bri * fn_8017F68C(4, ar, br, m->timer, 1500.0f);
            cg = bri * fn_8017F68C(4, ag, bg, m->timer, 1500.0f);
            cb = bri * fn_8017F68C(4, ab, bb, m->timer, 1500.0f);
        } else {
            cr = bri * fn_8017F68C(1, br, ar, m->timer - 1500, 1500.0f);
            cg = bri * fn_8017F68C(1, bg, ag, m->timer - 1500, 1500.0f);
            cb = bri * fn_8017F68C(1, bb, ab, m->timer - 1500, 1500.0f);
        }
        al = ln->alpha * (m->x28 * 255) / (255 * 255);
        fn_80006A64(m->x0, tex, d->wid);
        fn_80305D98(tex, 1, 0);
        fn_80022254(tex, 0);
        fn_803128AC(&mA, m->x10, m->x14, 0.0f);
        fn_8031292C(&mB, sx, sy, 1.0f);
        fn_80312378(&mA, &mB, &mA);
        fn_80021784(0);
        fn_80307E48(&mA, 0);
        fn_80182B48(0.0f, m, ln->d, &cur.x);
        pdy = pdx = v = 0.0f;
        fn_80021B68(0);
        for (k = 0; k < ln->n - 1; k++) {
            prev = cur;
            fn_80182B48(k, m, ln->d, &cur.x);
            dy = cur.y - prev.y;
            dx = cur.x - prev.x;
            c = dx * dx / (0.000001f + (dx * dx + dy * dy));
            s = 1.0f - c;
            if (dx * dy > 0.0f) {
                if (dx > 0.0f) {
                    nx = fn_80295CF0(s);
                    ny = -(f32)fn_80295CF0(c);
                } else {
                    nx = -(f32)fn_80295CF0(s);
                    ny = fn_80295CF0(c);
                }
            } else {
                if (dx > 0.0f) {
                    nx = fn_80295CF0(s);
                    ny = fn_80295CF0(c);
                } else {
                    nx = -(f32)fn_80295CF0(s);
                    ny = -(f32)fn_80295CF0(c);
                }
            }
            w = 0.5f * (f32)lbl_8041C9D8[d->wid][0];
            nx *= w;
            ny *= w;
            if (k == 0) {
                pl.x = prev.x + nx; pl.y = prev.y + ny;
                pr.x = prev.x - nx; pr.y = prev.y - ny;
            }
            dv = 0.1f * (1.0f / (f32)lbl_8041C9D8[d->wid][1] * (f32)fn_80295CF0(dx * dx + dy * dy));
            fn_80304314(0x98, 0, 4);
            Pos3(pl.x, pl.y, z); Col4(cr, cg, cb, al); Tex2(v, 0.0f);
            if (!(pdx * dx < 0.0f) && !(pdy * dy < 0.0f)) {
                Pos3(cur.x + nx, cur.y + ny, z);
            } else {
                Pos3(cur.x - nx, cur.y - ny, z);
            }
            Col4(cr, cg, cb, al);
            Tex2(v + dv, 0.0f);
            Pos3(pr.x, pr.y, z); Col4(cr, cg, cb, al); Tex2(v, 1.0f);
            if (!(pdx * dx < 0.0f) && !(pdy * dy < 0.0f)) {
                Pos3(cur.x - nx, cur.y - ny, z);
            } else {
                Pos3(cur.x + nx, cur.y + ny, z);
            }
            Col4(cr, cg, cb, al);
            Tex2(v + dv, 1.0f);
            pdx = dx;
            pdy = dy;
            v += dv;
            pl.x = cur.x + nx; pl.y = cur.y + ny;
            pr.x = cur.x - nx; pr.y = cur.y - ny;
        }
        fn_80021B68(2);
        if (ln->n > 3) {
            fn_80006A64(m->x0, tex, 8);
            fn_80022254(tex, 0);
            if (0.0f == dx) dx = 0.000000001f;
            ang = fn_802952C8(dy / dx);
            if (dx < 0.0f) ang += pi;
            ang = 0.5f * pi + ang;
            fn_803128AC(&mC, -cur.x, -cur.y, 0.0f);
            fn_80312654(&mD, 'z', ang);
            fn_803128AC(&mE, cur.x, cur.y, 0.0f);
            fn_80312378(&mD, &mC, &mA);
            fn_80312378(&mE, &mA, &mA);
            fn_803128AC(&mC, m->x10, m->x14, 0.0f);
            fn_8031292C(&mB, sx, sy, 1.0f);
            fn_80312378(&mB, &mA, &mA);
            fn_80312378(&mC, &mA, &mA);
            fn_80021784(0);
            fn_80307E48(&mA, 0);
            fn_80304314(0x98, 0, 4);
            {
                f32 sz = 32.0f;
                hh = 0.5f * sz;
                hw = 0.5f * (sz * (f32)lbl_8041C9D8[d->wid][0] / 10.0f);
            }
            Pos3(cur.x - hw, cur.y - hh, z); Col4(cr, cg, cb, al); Tex2(0.0f, 0.0f);
            Pos3(cur.x + hw, cur.y - hh, z); Col4(cr, cg, cb, al); Tex2(1.0f, 0.0f);
            Pos3(cur.x - hw, cur.y + hh, z); Col4(cr, cg, cb, al); Tex2(0.0f, 1.0f);
            Pos3(cur.x + hw, cur.y + hh, z); Col4(cr, cg, cb, al); Tex2(1.0f, 1.0f);
        }
    }
    fn_80021860(1, 3, 0);
    fn_800217CC(1);
    fn_80021808(7, 0, 1, 7, 0);
}
