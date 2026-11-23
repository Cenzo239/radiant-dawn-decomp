#include "game/rA_800068A0/types.h"

/* GModel.c (node hierarchy helpers) */

typedef f32 Mtx[3][4];

typedef struct GNode {
    struct GNode* parent;   /* 0x00 */
    u8 x4[8];
    u32 flags;              /* 0x0C */
    u8 x10[0x64 - 0x10];
    f32 rot[3];             /* 0x64 */
    u8 x70[0xEC - 0x70];
    u32 xEC_hi : 28;
    u32 mode : 4;           /* 0xEC low nibble */
    u8 xF0[4];
} GNode;

typedef struct GModel {
    u8 x0[0xC];
    GNode* nodes;
} GModel;

extern void fn_80312318(Mtx m);                     /* PSMTXIdentity */
extern void fn_80312378(Mtx a, Mtx b, Mtx ab);      /* PSMTXConcat */
extern u32 fn_80312494(Mtx src, Mtx inv);           /* PSMTXInverse */
extern void fn_8001D748(Mtx m, u32 mode, f32 x, f32 y, f32 z);

extern void* lbl_804CB080;
extern s8 lbl_804CA048;

/* GNode_GetRotChainMtx: product of the rotation matrices of the node and its
 * ancestors that have flag 0x40, inverted. */
Mtx* fn_8000F328(GNode* n, Mtx m) {
    BOOL found = 0;
    Mtx t;
    fn_80312318(m);
    for (; n != NULL; n = n->parent) {
        if (n->flags & 0x40) {
            fn_8001D748(t, n->mode, n->rot[0], n->rot[1], n->rot[2]);
            fn_80312378(t, m, m);
            found = 1;
        }
    }
    if (found) {
        fn_80312494(m, m);
    }
    return (Mtx*)m;
}

/* GModel_GetNodeRaw */
GNode* fn_8000F3D4(GModel* m, s32 idx) {
    return &m->nodes[idx];
}

/* GNode_ClearFlagsUp */
#pragma push
#pragma inline_depth(4)
void fn_8000F3E4(GNode* n, u32 mask) {
    if (n != NULL) {
        n->flags &= ~mask;
        fn_8000F3E4(n->parent, mask);
    }
}
#pragma pop

void fn_8000F468(void* p) {
    lbl_804CB080 = p;
}

void* fn_8000F470(void) {
    return lbl_804CB080;
}

s32 fn_8000F478(void) {
    return lbl_804CA048;
}

void fn_8000F484(s8 v) {
    lbl_804CA048 = v;
}
