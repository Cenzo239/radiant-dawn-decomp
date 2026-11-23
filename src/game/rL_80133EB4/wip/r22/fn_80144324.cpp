/* fn_80144324 (round 22, agent r22b): complete draft, class `other` (0x188 bytes, original 0x194).
 * Cloud layer scroll: if the weather proc (fn_80083B84(lbl_80386540)) is active and
 * fn_80068D74() allows it, advance the cloud texture offset (+0x30, +0x34) by
 * wind (+0x48, +0x4C) * speed (+0x3C), build a look-at matrix from eye
 * (32 + x, 32 + y, 10) to target (32 + x, 32 + y, -10) with up (0, -1, 0)
 * (C_MTXLookAt = fn_80312AC0(m, eye, up, target)), a light-space ortho
 * (fn_80312D2C(m, -32, 32, -32, 32, 0.5, 0.5, 0.5, 0.5)) and store ortho * view at +0x3C
 * (fn_80312378 = PSMTXConcat).
 * sTab is the real .rodata table lbl_80369A08 (four Vecs; [2] is unused here), mapped by
 * fn_80144324.symbols.json.
 *
 * What differs: scheduling and registers. The stack layout, word copies and the re-read
 * of c->x30/c->x34 for the eye (the aliasing store through T's reference) now follow the
 * original, but the original keeps the three hoisted table addresses (addi r9/r8/r7,
 * base+0/0xC/0x24) and copies the target before loading the eye's table words, holding
 * the target's z in r30 after the proc pointer dies; this draft loads the table words
 * directly and early (3 instructions fewer). Values passed to every call are the same:
 * eye (32 + x, 32 + y, 10), up (0, -1, 0), target (32 + x, 32 + y, -10).
 * Searched: Look parameter orders, by-value vs const& parameters with local copies,
 * Mk-by-value vs reference builders, Vec and Mtx declaration order.
 */
/* Cloud layer scroll: moves the texture offset and rebuilds its projection matrix. */
#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct Mtx44 { f32 m[12]; };
struct Cloud {
    u8 pad0[0x30];
    f32 x30, x34;
    u8 pad38[4];
    Mtx x3c;
};
struct WxP {
    u8 pad0[0x30];
    u8 x30;
    u8 pad31[0x3C - 0x31];
    f32 x3c;
    u8 pad40[8];
    f32 x48, x4c;
};
static const Vec sTab[4] = {{0.0f, 0.0f, -10.0f}, {0.0f, 0.0f, 10.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}};
extern "C" {
extern u8 lbl_80386540[];
extern WxP* fn_80083B84(void*);
extern int fn_80068D74(void);
extern void fn_80312AC0(Mtx*, Vec*, Vec*, Vec*);
extern void fn_80312D2C(Mtx*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80312378(Mtx*, Mtx*, Mtx*);

static inline Vec& T(Vec& t, f32 x, f32 y) { t.x = x; t.y = y; return t; }
static inline Vec Mk(const Vec& s, f32 x, f32 y) { Vec t = s; t.x = x; t.y = y; return t; }
static inline void Look(Mtx* m, Vec u, Vec e, Vec t) { fn_80312AC0(m, &e, &u, &t); }

void fn_80144324(Cloud* c) {
    const Vec* tab = sTab;
    WxP* w = fn_80083B84(lbl_80386540);
    if (w->x30 == 0) return;
    if (fn_80068D74() == 0) return;
    Mtx mp;
    Mtx mv;
    c->x30 += w->x48 * w->x3c;
    f32 k = 32.0f;
    f32 tx = k + c->x30;
    c->x34 += w->x4c * w->x3c;
    f32 ty = k + c->x34;
    Vec e = tab[1], t = tab[0]; Look(&mv, tab[3], T(e, k + c->x30, k + c->x34), T(t, tx, ty));
    fn_80312D2C(&mp, -k, k, -k, k, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_80312378(&mp, &mv, &c->x3c);
}
}
