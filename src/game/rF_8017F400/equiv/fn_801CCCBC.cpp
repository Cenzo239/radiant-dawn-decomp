/* functionally equal (check_regs: regs). fn_801CCCBC walks the bone chain through x8, fn_801CCE8C through x0;
   both recurse and are inlined to depth 2 (inline_depth(2)). Bodies from wip/fn_801CCCBC_r17.cpp. */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw off
extern "C" {
typedef struct Mat34 { f32 m[12]; } Mat34;
typedef struct BN { struct BN* x0; u8 pad[4]; struct BN* x8; u8 padC[0xE0]; u32 xEC; } BN;
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern void fn_803128AC(Mat34*, f32, f32, f32);
extern void fn_80312378(Mat34*, Mat34*, Mat34*);
#pragma push
#pragma inline_depth(2)
int fn_801CCCBC(BN* n, Mat34* mats, int d, f32 t) {
    /*P*/
    BN* k;
    int e;
    int c;
    Mat34 r;
/*E*/
    k = n->x8;
    if (k == 0) return d;
    e = d + 1;
    c = fn_801CCCBC(k, mats, e, t);
    t = fn_8001ECE4(2, t, 0.0f, c, d);
    fn_803128AC(&r, 0.0f, t, 0.0f);
    fn_80312378(&r, &mats[n->xEC >> 20], &mats[n->xEC >> 20]);
    return d;
}
int fn_801CCE8C(BN* n, Mat34* mats, int d, f32 t) {
    /*P*/
    BN* k;
    int e;
    int c;
    Mat34 r;
/*E*/
    k = n->x0;
    if (k == 0) return d;
    e = d + 1;
    c = fn_801CCE8C(k, mats, e, t);
    t = fn_8001ECE4(2, t, 0.0f, c, d);
    fn_803128AC(&r, 0.0f, t, 0.0f);
    fn_80312378(&r, &mats[n->xEC >> 20], &mats[n->xEC >> 20]);
    return d;
}
#pragma pop
}
