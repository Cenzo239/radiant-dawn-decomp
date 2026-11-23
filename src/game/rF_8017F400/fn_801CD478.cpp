/* fn_801CD478: map object (bridge/plate) update: bend its bones under units standing on it, write the bone heights into
 * the map height tables, set the units' heights, then refresh the world matrices. */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw off
extern "C" {
typedef struct Mat34 { f32 m[12]; } Mat34;
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct BN { struct BN* x0; u8 pad4[4]; struct BN* x8; u32 xc; Mat34 x10; u8 pad40[0xEC - 0x40]; u32 xEC; u8 padF0[4]; } BN;
typedef struct BAnim { u8 pad[8]; int n; BN* nodes; } BAnim;
typedef struct MUnit { u8 pad[4]; f32 x, y, z; u8 pad10[0xEC - 0x10]; void* person; u8 padF0[4]; u8* team; u8 padF8[0x3F0 - 0xF8]; } MUnit;
typedef struct MObj { u8 x0; u8 pad1[3]; s8 x0l, y0l, x1l, y1l; u8 pad8[0x14 - 8]; u8 mdl[1]; } MObj;
typedef struct HMap {
    u8 pad[0x15422];
    s16 hA[0x1000][4];
    u8 pad1D422[0x1D424 - 0x1D422];
    f32 scale;
    u8 pad1D428[0x1D42C - 0x1D428];
    s16 hB[0x1000][4];
} HMap;
extern HMap lbl_803EC898;
extern MUnit* lbl_804CB810;
extern char lbl_8036E9AC[];
extern BAnim* fn_80007EE4(void*);
extern Mat34* fn_800080B8(void*);
extern Mat34* fn_800080E4(void*);
extern void fn_8010E41C(u8*, int);
extern void fn_801CD05C(void*, BN*, Mat34*, f32, f32);
extern void fn_80007860(void*, int, Mat34*);
extern void fn_8001E9E4(Mat34*, Vec3*);
extern int fn_80007630(void*, const char*);
extern f32 fn_80113F00(void*, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_8001CD78(void*);
static inline MUnit* UnitAt(int id) { return (u8)id ? &lbl_804CB810[(u8)id - 1] : 0; }
#define LIVE(nd) (((nd)->xc & 1) && (nd)->x8 && (nd)->x0)
void fn_801CD478(MObj* o) {
    /*P*/
    BAnim* an;
    Mat34* mB;
    void* a;
    BN* nd2;
    Mat34* mA;
    int x0;
    int y0;
    MUnit** p1;
    BN* nd1;
    int i1;
    int j1;
    int x1;
    int y1;
    int n;
    int i2;
    int i4;
    int j3;
    BN* nd4;
    MUnit** p3;
    int id;
/*E*/
    u8 tbl[0xB];
    MUnit* list[0x20];
    a = o->mdl;
    an = fn_80007EE4(a);
    mA = fn_800080B8(a);
    mB = fn_800080E4(a);
    x0 = o->x0l;
    y0 = o->y0l;
    x1 = o->x1l;
    y1 = o->y1l;
    n = 0;
    fn_8010E41C(tbl, 3);
    for (id = 1; id <= 0xFE; id++) {
        MUnit* u = UnitAt(id);
        if (u->person && tbl[u->team[8]]) {
            f32 fx = u->x; f32 fy = u->y;
            int ux = fx;
            int uy = fy;
            if (ux >= x0 && ux <= x1 && uy >= y0 && uy <= y1) list[n++] = u;
        }
    }
    if (n > 0) {
        for (i1 = 0, nd1 = an->nodes; i1 < an->n; i1++, nd1++) {
            if (LIVE(nd1)) {
                for (j1 = 0, p1 = list; j1 < n; p1++, j1++) fn_801CD05C(a, nd1, mA, (*p1)->x, (*p1)->y);
            }
        }
    }
    {
        for (i2 = 0, nd2 = an->nodes; i2 < an->n; i2++, nd2++) {
            if (LIVE(nd2)) {
                Mat34 t;
                Vec3 v;
                int tx, ty, h;
                fn_80007860(a, nd2->xEC >> 20, &t);
                fn_8001E9E4(&t, &v);
                { f32 sc = lbl_803EC898.scale; tx = 0.5f + v.x; ty = 0.5f + v.y; h = v.z / sc; }
                if (tx <= x1 && ty <= y1) {
                    lbl_803EC898.hA[(s8)tx + (s8)ty * 0x40][0] = h;
                    lbl_803EC898.hB[(s8)tx + (s8)ty * 0x40][0] = h;
                }
                if (tx > x0 && ty <= y1) {
                    lbl_803EC898.hA[(s8)(tx - 1) + (s8)ty * 0x40][1] = h;
                    lbl_803EC898.hB[(s8)(tx - 1) + (s8)ty * 0x40][1] = h;
                }
                if (tx > x0 && ty > y0) {
                    lbl_803EC898.hA[(s8)(tx - 1) + (s8)(ty - 1) * 0x40][3] = h;
                    lbl_803EC898.hB[(s8)(tx - 1) + (s8)(ty - 1) * 0x40][3] = h;
                }
                if (tx <= x1 && ty > y0) {
                    lbl_803EC898.hA[(s8)tx + (s8)(ty - 1) * 0x40][2] = h;
                    lbl_803EC898.hB[(s8)tx + (s8)(ty - 1) * 0x40][2] = h;
                }
            }
        }
    }
    {
    int j = fn_80007630(a, lbl_8036E9AC + 0x2E);
    if (j >= 0) {
        Mat34 t;
        Vec3 v;
        int tx, ty, h, k, idx;
        fn_80007860(a, an->nodes[j].xEC >> 20, &t);
        fn_8001E9E4(&t, &v);
        { f32 sc = lbl_803EC898.scale; tx = v.x; ty = v.y; h = v.z / sc; }
        idx = (s8)tx + (s8)ty * 0x40;
        for (k = 0; k < 4; k++) {
            ((s16*)lbl_803EC898.hA)[idx * 4 + k] = h;
            ((s16*)lbl_803EC898.hB)[idx * 4 + k] = h;
        }
    }
    }
    if (n > 0) {
        for (j3 = 0, p3 = list; j3 < n; p3++, j3++) {
            MUnit* u = *p3;
            u->z = fn_80113F00(&lbl_803EC898, u->x, u->y);
        }
    }
    if (mB) {
        for (i4 = 0, nd4 = an->nodes; i4 < an->n; i4++, nd4++) {
            if (LIVE(nd4)) fn_80312378(&mA[nd4->xEC >> 20], &nd4->x10, &mB[nd4->xEC >> 20]);
        }
        fn_8001CD78(a);
    }
}
}
