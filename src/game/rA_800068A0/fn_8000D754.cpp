#include "game/rA_800068A0/types.h"
/* Node local matrix from its transform block: scale, rotation (euler or quaternion), pivots and translation. */
extern "C" {
typedef f32 Mtx[3][4];
typedef struct NVec { f32 x, y, z; } NVec;
typedef struct NQuat { f32 x, y, z, w; } NQuat;
typedef struct NXf {
    NVec scale;
    NVec rot;
    NVec trans;
    NVec rotOfs;
    NVec rotPivot;
    NVec sclPivot;
    NVec rotPivot2;
    NVec sclPivot2;
    NVec rotPost;
    NQuat quat;
} NXf;
typedef struct NObj { u8 x0[0xC]; u32 flags; } NObj;
typedef struct NNode { u8 x0[0xC]; u32 flags; u8 x10[0xEC - 0x10]; u32 mode : 28; u32 axis : 4; } NNode;
extern void fn_803129AC(Mtx m, const NQuat* q);
extern void fn_8001D748(Mtx m, int order, f32 x, f32 y, f32 z);
extern void fn_80312378(const void* a, const void* b, void* c);
extern void fn_803128AC(Mtx m, f32 x, f32 y, f32 z);
extern void fn_8031292C(Mtx m, f32 x, f32 y, f32 z);
extern void fn_80312318(Mtx m);
extern void fn_80312344(const void* a, void* b);
void fn_8000D754(NObj* o, NNode* n, u32 f, NXf* x, const NQuat* q, void* out) {
    Mtx s;
    Mtx m;
    Mtx t;
    NQuat k;
    if (f & 0x10) {
        if (q != 0) {
            fn_803129AC(m, q);
        } else if (o->flags & 1) {
            fn_8001D748(m, n->axis, x->rot.x, x->rot.y, x->rot.z);
        } else if (o->flags & 2) {
            k.x = x->quat.x;
            k.y = x->quat.y;
            k.z = x->quat.z;
            k.w = x->quat.w;
            fn_803129AC(m, &k);
        }
        if (f & 0x40) {
            fn_8001D748(t, n->axis, x->rotOfs.x, x->rotOfs.y, x->rotOfs.z);
            fn_80312378(t, m, m);
        }
        if (f & 0x800) {
            fn_8001D748(t, n->axis, x->rotPost.x, x->rotPost.y, x->rotPost.z);
            fn_80312378(m, t, m);
        }
        if (f & 0x80) {
            fn_803128AC(t, -x->rotPivot.x, -x->rotPivot.y, -x->rotPivot.z);
            fn_80312378(m, t, m);
            fn_803128AC(t, x->rotPivot.x, x->rotPivot.y, x->rotPivot.z);
            fn_80312378(t, m, m);
            if (f & 0x200) {
                fn_803128AC(t, x->rotPivot2.x, x->rotPivot2.y, x->rotPivot2.z);
                fn_80312378(t, m, m);
            }
        }
    } else {
        fn_80312318(m);
    }
    if (f & 8) {
        fn_8031292C(s, x->scale.x, x->scale.y, x->scale.z);
        if (f & 0x100) {
            fn_803128AC(t, -x->sclPivot.x, -x->sclPivot.y, -x->sclPivot.z);
            fn_80312378(s, t, s);
            fn_803128AC(t, x->sclPivot.x, x->sclPivot.y, x->sclPivot.z);
            fn_80312378(t, s, s);
            if (f & 0x400) {
                fn_803128AC(t, x->sclPivot2.x, x->sclPivot2.y, x->sclPivot2.z);
                fn_80312378(t, s, s);
            }
        }
        fn_80312378(m, s, m);
    }
    if (f & 0x20) {
        fn_803128AC(t, x->trans.x, x->trans.y, x->trans.z);
        fn_80312378(t, m, m);
    }
    fn_80312344(m, out);
    n->flags |= 0x4000000;
}
}
