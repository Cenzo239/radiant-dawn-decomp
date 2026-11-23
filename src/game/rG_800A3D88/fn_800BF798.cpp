#include "game/rG_800A3D88/types.h"

// Walks two bone trees in step and combines their matrices.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct BoneT { u8 p[4]; BoneT* m4; BoneT* m8; u8 pc[4]; Mtx34 m10; u8 p40[0xEC - 0x40]; u32 ec; };
void fn_80312344(Mtx34*, Mtx34*);
void fn_80312378(Mtx34*, Mtx34*, Mtx34*);
#define IDX(b) ((b)->ec >> 20)
#pragma push
#pragma inline_depth(1)
#pragma use_lmw_stmw on
void fn_800BF798(BoneT* a, BoneT* b, Mtx34* mA, Mtx34* mB, Mtx34* out, int d) {
    Mtx34 t;
    fn_80312344(&mA[IDX(a)], &mB[IDX(b)]);
    fn_80312378(&mB[IDX(b)], &b->m10, &out[IDX(b)]);
    if (d > 0 && b->m4 != NULL && a->m4 != NULL) {
        fn_800BF798(a->m4, b->m4, mA, mB, out, d + 1);
    }
    if (b->m8 != NULL) {
        if (a->m8 != NULL) {
            fn_800BF798(a->m8, b->m8, mA, mB, out, d + 1);
        } else {
            fn_80312378(&mA[IDX(a)], &b->m10, &t);
            fn_80312378(&t, &mB[IDX(b->m8)], &mB[IDX(b->m8)]);
        }
    }
}
#pragma pop
}
