/* r20: `regs` (check_regs.py, 11 words: f2/f3 of one conversion and r27/r28 in the x0 chain).
   Two changes against the r17 wip:
   - the six per-level rotation matrices are locals of fn_801CD05C, declared a3, a2, a1, b3, b2, b1 and passed to the
     LEVEL inlines by reference; that gives the original slot order (0x110, 0xE0, 0xB0, 0x80, 0x50, 0x20);
   - the easing mode of fn_8001ECE4 is declared `u8`, so the literal 2 is not merged with the depth value 2 and the
     original's separate `li r3,2` appears (with `int` the two were one register and the function two instructions
     short). `s16` does the same; the real parameter type is not known.
   The LEVEL macros still stand in for fn_801CCCBC / fn_801CCE8C inlined three levels deep (see caveat in the notes). */
/* fn_801CD05C: bend a bone chain towards (x, y): rotate the node by a falloff of the distance, then its x8 and x0 chains
 * (fn_801CCCBC and fn_801CCE8C, each inlined three levels deep here, written out as K1..K3 / J1..J3). */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw off
extern "C" {
typedef struct Mat34 { f32 m[12]; } Mat34;
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct BN { struct BN* x0; u8 pad4[4]; struct BN* x8; u8 padC[0xE0]; u32 xEC; } BN;
extern f32 fn_8001ECE4(u8, f32, f32, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_803128AC(Mat34*, f32, f32, f32);
extern void fn_80312378(Mat34*, Mat34*, Mat34*);
extern void fn_80007860(void*, int, Mat34*);
extern void fn_8001E9E4(Mat34*, Vec3*);
extern f32 fn_80313508(Vec3*);
extern int fn_801CCCBC(BN* n, Mat34* mats, int d, f32 t);
extern int fn_801CCE8C(BN* n, Mat34* mats, int d, f32 t);
#define LEVEL(NAME, NEXT, LINK, NR) \
static inline int NAME(BN* n, Mat34* mats, int d, f32 t, Mat34& r, Mat34& r2, Mat34& r3) { \
BN* k; int e; int c; k = n->LINK; if (k == 0) return d; e = d + 1; c = NEXT; t = fn_8001ECE4(2, t, 0.0f, c, d); fn_803128AC(&r, 0.0f, t, 0.0f); fn_80312378(&r, &mats[n->xEC >> 20], &mats[n->xEC >> 20]); return d; \
}
LEVEL(K3, fn_801CCCBC(k, mats, e, t), x8, 0)
LEVEL(K2, K3(k, mats, e, t, r2, r3, r3), x8, 0)
LEVEL(K1, K2(k, mats, e, t, r2, r3, r3), x8, 0)
LEVEL(J3, fn_801CCE8C(k, mats, e, t), x0, 0)
LEVEL(J2, J3(k, mats, e, t, r2, r3, r3), x0, 0)
LEVEL(J1, J2(k, mats, e, t, r2, r3, r3), x0, 0)
void fn_801CD05C(void* mdl, BN* n, Mat34* mats, f32 x, f32 y) {
    Mat34 m;
    Vec3 p;
    Vec3 dv;
    Mat34 r;
    f32 f, t;
    fn_80007860(mdl, n->xEC >> 20, &m);
    fn_8001E9E4(&m, &p);
    dv.x = p.x - x;
    dv.y = 0.0f;
    dv.z = p.y - y;
    f = fn_80313508(&dv);
    if (f < 1.0f) {
        { f32 w = 1.0f - f; t = fn_8001EF30(0.0f, -2.0f, 1.0f, w); }
        fn_803128AC(&r, 0.0f, t, 0.0f);
        fn_80312378(&r, &mats[n->xEC >> 20], &mats[n->xEC >> 20]);
        { int e = 1; Mat34 a3; Mat34 a2; Mat34 a1; Mat34 b3; Mat34 b2; Mat34 b1; if (n->x8) K1(n->x8, mats, e, t, a1, a2, a3); if (n->x0) J1(n->x0, mats, e, t, b1, b2, b3); }
    }
}
}
