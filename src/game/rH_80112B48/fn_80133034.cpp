/* fn_80133034, fn_801335C4, fn_80133B10: cursor/camera model update (lbl_80413510 work area).
   fn_80133034 = Reset + Update, fn_801335C4 = Update, fn_80133B10 = Reset + heights at a given tile + Children.
   Matched in round 17. The float locals of both loops are uninitialised on one path, so they live from
   function entry: they are declared in each caller and passed by reference (order cx, cy, cz, hx, hy).
   ChildrenB is a copy of Children with its locals declared in a different order (needed by fn_80133B10). */
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
#if TARGET_PC
extern FE10_PROTO void fn_80118B20(MapH*, Mtx, p32arg, p32arg, f32, f32);
#else
extern void fn_80118B20(MapH*, Mtx, int, int, f32, f32);
#endif
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
static inline s8 cs(f32 v) { return (int)v; }
static inline void Heights(f32& px, f32& py) {
    if (W.b6D5) {
        bool same = fn_8017FA1C() - 1 == W.i6B0;
        int i;
        W.i6B0 = fn_8017FA1C();
        if (W.b6B4) {
            f32 x = G.x; f32 y = G.y;
            W.f658 = x - 0.5f;
            W.f65C = y - 0.5f;
        } else if (same) {
            W.f658 = 0.5f * (W.f658 + (s8)(int)G.x);
            W.f65C = 0.5f * (W.f65C + (s8)(int)G.y);
        } else {
            W.f658 = cs(G.x);
            W.f65C = cs(G.y);
        }
        for (i = 0; i < 4; i++) {
            f32 g, d;
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
static inline void HeightsAt(int x, int y, f32& px, f32& py) {
    int i;
    W.f658 = x;
    W.f65C = y;
    for (i = 0; i < 4; i++) {
        f32 g;
        if (W.b6D5) {
            px = W.f658 + lbl_80385F58[i];
            py = W.f65C + lbl_80385F68[i];
        }
        g = fn_801142F0(&M, px, py);
        if (g > M.top) g = M.top;
        W.f660[i] = g - 0.1f;
    }
}
static inline void QRot(int j, Mtx qm, Mtx m) {
    Quat q;
    fn_803135A8(&q, m);
    fn_80313774(&W.q[j], &q, &q, 0.2f);
    W.q[j] = q;
    fn_803129AC(qm, &q);
}
static inline void Children(f32& px, f32& py, f32& pz) {
    if (W.b6D5) {
        Mtx z, qm, t, r, s, m;
        f32* ty;
        int j;
        f32* tx;
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
static inline void ChildrenB(f32& px, f32& py, f32& pz) {
    if (W.b6D5) {
        Mtx z, qm, t, r, s, m;
        f32* ty;
        f32* tx;
        int j;
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
static inline void Update(f32& cx, f32& cy, f32& cz, f32& hx, f32& hy) {
    if (W.b6D5) {
        Root2();
        Heights(hx, hy);
        Children(cx, cy, cz);
        W.b6D4 = 1;
    }
}
static inline void Reset(void) {
    if (W.b6D5) {
        fn_800081D4(&W.b);
        fn_80007C58(&W.b);
        fn_800081D4(&W.a);
        fn_80007C58(&W.a);
    }
}
void fn_80133034(void) {
    f32 cx; f32 cy; f32 cz; f32 hx; f32 hy;
    Reset();
    Update(cx, cy, cz, hx, hy);
}
void fn_801335C4(void) {
    f32 cx; f32 cy; f32 cz; f32 hx; f32 hy;
    Update(cx, cy, cz, hx, hy);
}
void fn_80133B10(int x, int y) {
    f32 hy; f32 hx; f32 cx; f32 cy; f32 cz;
    Reset();
    if (W.b6D5) {
        HeightsAt(x, y, hx, hy);
        ChildrenB(cx, cy, cz);
        W.b6D4 = 1;
    }
}
}
