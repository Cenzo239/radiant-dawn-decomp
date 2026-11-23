/* fn_801CCCBC: 33/116 words. Self-recursive, inlined to depth 2 by inline_depth(2). The body is right, including "return d" and the separate e = d + 1. Registers for the inlined levels are still rotated. fn_801CCE8C is the same shape. */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw off
extern "C" {
typedef struct Mat34 { f32 m[12]; } Mat34;
typedef struct BN { u8 pad[8]; struct BN* x8; u8 padC[0xE0]; u32 xEC; } BN;
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern void fn_803128AC(Mat34*, f32, f32, f32);
extern void fn_80312378(Mat34*, Mat34*, Mat34*);
#pragma push
#pragma inline_depth(2)
int fn_801CCCBC(BN* n, Mat34* mats, int d, f32 t) {
    int e;
    BN* k = n->x8;
    int c;
    Mat34 r;
    f32 v;
    if (k == 0) return d;
    e = d + 1;
    c = fn_801CCCBC(k, mats, e, t);
    v = fn_8001ECE4(2, t, 0.0f, c, d);
    fn_803128AC(&r, 0.0f, v, 0.0f);
    fn_80312378(&r, &mats[n->xEC >> 20], &mats[n->xEC >> 20]);
    return d;
}
#pragma pop
}
