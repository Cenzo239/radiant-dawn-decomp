/* near miss (round 17): fn_801CD05C, ~168 lines. The fn_801CCCBC/fn_801CCE8C chains are inlined three levels deep in the original (the compiler will not inline the real recursive function, so LEVEL macros stand in). Left: constant 2 is CSEd with the literal argument here, the original keeps separate li; slot order of the level matrices is reversed. */
/* fn_801CD05C: bend a bone chain towards (x, y): rotate the node by a falloff of the distance, then its x8 and x0 chains
 * (fn_801CCCBC and fn_801CCE8C, each inlined three levels deep here, written out as K1..K3 / J1..J3). */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw off
extern "C" {
typedef struct Mat34 { f32 m[12]; } Mat34;
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct BN { struct BN* x0; u8 pad4[4]; struct BN* x8; u8 padC[0xE0]; u32 xEC; } BN;
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_803128AC(Mat34*, f32, f32, f32);
extern void fn_80312378(Mat34*, Mat34*, Mat34*);
extern void fn_80007860(void*, int, Mat34*);
extern void fn_8001E9E4(Mat34*, Vec3*);
extern f32 fn_80313508(Vec3*);
extern int fn_801CCCBC(BN* n, Mat34* mats, int d, f32 t);
extern int fn_801CCE8C(BN* n, Mat34* mats, int d, f32 t);
#define LEVEL(NAME, NEXT, LINK) \
static inline int NAME(BN* n, Mat34* mats, int d, f32 t) { \
BN* k; int e; int c; Mat34 r; k = n->LINK; if (k == 0) return d; e = d + 1; c = NEXT(k, mats, e, t); t = fn_8001ECE4(2, t, 0.0f, c, d); fn_803128AC(&r, 0.0f, t, 0.0f); fn_80312378(&r, &mats[n->xEC >> 20], &mats[n->xEC >> 20]); return d; \
}
LEVEL(K3, fn_801CCCBC, x8)
LEVEL(K2, K3, x8)
LEVEL(K1, K2, x8)
LEVEL(J3, fn_801CCE8C, x0)
LEVEL(J2, J3, x0)
LEVEL(J1, J2, x0)
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
        { int e = 1; if (n->x8) K1(n->x8, mats, e, t); if (n->x0) J1(n->x0, mats, e, t); }
    }
}
}
