/* NOT MATCHING, not compiled. fn_801335C4 (cursor model update; fn_80133034 and fn_80133B10 share the Root/Heights/Children parts): about 40 of 339 words.
   Stack layout and integer registers of Children are right. Left: in Heights the W base wants r31 and "same" r30 (ours swapped), loop-1 px/py want f28/f27 (ours f30/f31);
   in Children px/py/pz want f31/f30/f29 above the hoisted 90.0f/deg constants (ours constants on top). Declaration order, by-reference locals and named constants did not move them.
   Self-contained: the struct header is copied in. */
#include "game/rH_80112B48/types.h"
extern "C" {
typedef f32 Mtx[3][4];
struct Quat { f32 x, y, z, w; };
struct Obj {
    u32 flags;
    u8 pad4[0xc];
    Mtx mtx;
    void* p40;
    void* p44;
    void* p48;
    void* p4C;
    u8 pad50[0x9c - 0x50];
};
struct CamW {
    u8 pad0[8];
    Obj a;
    Obj b;
    Obj c[4];
    Obj d[4];
    u8 pad620[0x658 - 0x620];
    f32 f658;
    f32 f65C;
    f32 f660[4];
    Quat q[4];
    int i6B0;
    u8 b6B4;
    u8 pad6B5[0x6d4 - 0x6b5];
    u8 b6D4;
    u8 b6D5;
};
struct GmC {
    u8 pad0[0x934];
    f32 f934, f938;
    u8 pad93C[8];
    f32 x, y;
};
struct MapH {
    u8 pad0[0x1D428];
    f32 top;
};
extern CamW lbl_80413510;
extern GmC lbl_803CAB38;
extern MapH lbl_803EC898;
extern f32 lbl_80385F58[4];
extern f32 lbl_80385F68[4];
extern f32 fn_801142F0(MapH*, f32, f32);
extern void fn_80118B20(MapH*, Mtx, int, int, f32, f32);
extern void fn_8031292C(Mtx, f32, f32, f32);
extern void fn_80312654(Mtx, int, f32);
extern void fn_80312378(const Mtx, const Mtx, Mtx);
extern void fn_803128AC(Mtx, f32, f32, f32);
extern void fn_80312344(const Mtx, Mtx);
extern void fn_803135A8(Quat*, const Mtx);
extern void fn_80313774(const Quat*, const Quat*, Quat*, f32);
extern void fn_803129AC(Mtx, const Quat*);
extern void fn_800180F0(Obj*);
extern void fn_800081D4(Obj*);
extern void fn_80007C58(Obj*);
extern int fn_8017FA1C(void);
}
extern "C" {
#define W lbl_80413510
#define G lbl_803CAB38
#define M lbl_803EC898
static inline void Root(f32, f32) {
    f32 x, y; y = G.y; x = G.x;
    if (W.b6D5) {
        Mtx t, r, s, c;
        f32 h = fn_801142F0(&M, x, y);
        if (h > M.top) h = M.top;
        fn_8031292C(s, 0.2f, 0.2f, 0.2f);
        fn_80312654(r, 'X', 4.712389f);
        fn_80312378(r, s, c);
        fn_803128AC(t, x, y, h - 1.5f);
        fn_80312378(t, c, W.b.mtx);
        fn_800180F0(&W.b);
    }
}
static inline void Heights(BOOL& same) {
    if (W.b6D5) {
        same = fn_8017FA1C() - 1 == W.i6B0;
        int i;
        W.i6B0 = fn_8017FA1C();
        if (W.b6B4) {
            W.f658 = G.x - 0.5f;
            W.f65C = G.y - 0.5f;
        } else if (same) {
            W.f658 = 0.5f * (W.f658 + (s8)(int)G.x);
            W.f65C = 0.5f * (W.f65C + (s8)(int)G.y);
        } else {
            W.f658 = (s8)(int)G.x;
            W.f65C = (s8)(int)G.y;
        }
        for (i = 0; i < 4; i++) {
            f32 px, py, g, d;
            if (W.b6D5) {
                px = W.f658 + lbl_80385F58[i];
                py = W.f65C + lbl_80385F68[i];
            }
            g = fn_801142F0(&M, px, py);
            if (g > M.top) g = M.top;
            d = g - 0.1f;
            if (same) {
                W.f660[i] = 0.5f * (d + W.f660[i]);
            } else {
                W.f660[i] = d;
            }
        }
    }
}
static inline void QRot(int j, Mtx qm, Mtx m) {
    Quat q;
    fn_803135A8(&q, m);
    fn_80313774(&W.q[j], &q, &q, 0.2f);
    W.q[j] = q;
    fn_803129AC(qm, &q);
}
static inline void Children(void) {
    if (W.b6D5) {
        Mtx z, qm, t, r, s, m;
        /*P*/
        f32* ty;
        int j;
        f32* tx;
        f32 px;
        f32 py;
        f32 pz;
/*E*/
        fn_8031292C(s, 0.2f, 0.2f, 0.2f);
        fn_80312654(r, 'X', 4.712389f);
        for (j = 0, tx = lbl_80385F58, ty = lbl_80385F68; j < 4; tx++, ty++, j++) {
            if (W.b6D5) {
                px = W.f658 + *tx;
                py = W.f65C + *ty;
                pz = W.f660[j];
            }
            fn_80118B20(&M, m, 1, 1, px, py);
            QRot(j, qm, m);
            fn_80312654(z, 'Z', 0.017453292f * (90.0f * j));
            fn_803128AC(t, px, py, pz);
            fn_80312378(r, s, m);
            fn_80312378(z, m, m);
            fn_80312378(qm, m, m);
            fn_80312378(t, m, W.c[j].mtx);
            fn_80312344(W.c[j].mtx, W.d[j].mtx);
            fn_800180F0(&W.c[j]);
            fn_800180F0(&W.d[j]);
        }
    }
}
static inline void Root2(void) { Root(G.x, G.y); }
void fn_801335C4(void) {
    BOOL same;
    if (W.b6D5) {
        Root2();
        Heights(same);
        Children();
        W.b6D4 = 1;
    }
}
}
