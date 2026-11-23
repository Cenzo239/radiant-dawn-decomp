#include "game/rA_800068A0/types.h"
/* Per-frame node animation: updates the local matrix of every node from one animation or from blended event layers. */
extern "C" {
typedef f32 Mtx[3][4];
typedef struct NQuat { f32 x, y, z, w; } NQuat;
typedef struct NXf {
    f32 s[3];
    f32 rx, ry, rz;
    u8 x18[0x6C - 0x18];
    NQuat quat;
    u8 world[0x30];
} NXf;
typedef struct NTrack { int node; u32 flags; u32 x8; u32 xC; } NTrack;
typedef struct NAnm { u8 x0[0xC]; u32 flags; u8 x10[0x1C - 0x10]; int count; NTrack* tracks; } NAnm;
typedef struct NNode {
    u8 x0[0xC];
    u32 flags;
    u8 x10[0x40 - 0x10];
    NXf xf;
    u32 idx : 12;
    u32 x : 16;
    u32 axis : 4;
    u8 xF0[4];
} NNode;
typedef struct NModel { u8 x0[8]; int count; NNode* nodes; } NModel;
typedef struct NEv { u32 x0; u32 f; } NEv;
typedef struct NLay { void* a; NAnm* anim; u32 x8, xC; } NLay;
typedef struct NActor { u8 x0[0x78]; f32 weight; } NActor;
extern NModel* fn_80007EE4(NActor* a);
extern NAnm* fn_80007F10(NActor* a);
extern Mtx* fn_800080B8(NActor* a);
extern f32 fn_800081B4(void* a);
extern f32 fn_800081BC(void* a);
extern void fn_8000E974(void);
extern void fn_8000E9C4(int, int);
extern void fn_8000E9A8(f32* a, s16* b);
extern NNode* fn_8000F3D4(NModel* m, int i);
#if TARGET_PC
extern FE10_PROTO void fn_8000D0E0(NAnm* o, ptr32<const void>, u32 f, ptr32<const void>);
#else
extern void fn_8000D0E0(NAnm* o, NNode* n, u32 f, NXf* x);
#endif
extern void fn_8000D228(f32 t, NAnm* o, NTrack* tr, int k, NXf* x);
extern void fn_8000D754(NAnm* o, NNode* n, u32 f, NXf* x, NQuat* q, void* out);
extern void fn_8001D748(Mtx m, int order, f32 x, f32 y, f32 z);
extern void fn_803135A8(NQuat* q, Mtx m);
extern void fn_80313774(NQuat* a, NQuat* b, NQuat* c, f32 t);
extern int fn_8000BE24(NActor* a, NLay* out);
extern int fn_8000BEA8(int n, NLay* l, NEv** out);
extern void fn_8001E008(const char* file, int line, const char* msg);
extern char lbl_80360B08[];
extern void fn_8000DA14(f32 t, int i, NXf* a, NXf* b);
extern void fn_8000DA60(void* m, NNode* n, NXf* k, NQuat* out, f32 t);
extern void fn_8000DB10(NModel* m, NAnm* o, Mtx* out, f32 t);
extern void fn_80312344(const void* a, void* b);
void fn_8000C920(NActor* a) {
    NXf x;
    NXf xb;
    NXf x1;
    NXf x2;
    NLay lay[4];
    Mtx r;
    NEv* ev[4];
    NQuat q;
    NQuat q1;
    NQuat q2;
    f32 ft;
    f32 lt;
    s16 fi;
    s16 li;
    NLay* lp;
    int i2;
    NEv** ep;
    u32 rf;
    int k2;
    NNode* nd2;
    int i;
    NQuat* qp2;
    NTrack* tr;
    u32 f2;
    u32 f;
    NModel* md;
    NAnm* an;
    int k;
    NNode* nd;
    int j;
    Mtx* out;
    int cnt;
    int frac;
    NAnm* la;
    NEv* e;
    int m;
    f32 a0;
    f32 a1;
    f32 w;
    NQuat* qp;
    NNode* n;
    NNode* n2;
    int fr;
    md = fn_80007EE4(a);
    an = fn_80007F10(a);
    out = fn_800080B8(a);
    n = md->nodes;
    for (i = 0; i < md->count; i++, n++) {
        n->flags &= ~0x4000000;
    }
    if (an != 0) {
        ft = fn_800081B4(a);
        f32 t0 = ft;
        f32 z = 0.0f;
        fr = t0;
        frac = 0;
        if (z != t0 - (f32)fr) {
            frac = 1;
        }
        fn_8000E974();
        if (1.0f == a->weight) {
            fn_8000E9A8(&ft, &fi);
            tr = an->tracks;
            for (j = 0; j < an->count; j++, tr++) {
                nd = fn_8000F3D4(md, tr->node);
                if (!(nd->flags & 0x10000000)) {
                    f = tr->flags | nd->flags;
                    qp = 0;
                    fn_8000D0E0(an, nd, f, &x);
                    if (frac) {
                        if (f & 0x8000000) {
                            fn_8000D228((f32)fi, an, tr, fi, &x);
                        } else {
                            if (f & 0x10) {
                                a0 = (int)ft;
                                a1 = (int)ft + 1;
                                w = ft - a0;
                                fn_8000D0E0(an, nd, f, &x1);
                                fn_8000D0E0(an, nd, f, &x2);
                                fn_8000D228(a0, an, tr, fi, &x1);
                                fn_8000D228(a1, an, tr, fi, &x2);
                                if (an->flags & 1) {
                                    fn_8001D748(r, nd->axis, x1.rx, x1.ry, x1.rz);
                                    fn_803135A8(&q1, r);
                                    fn_8001D748(r, nd->axis, x2.rx, x2.ry, x2.rz);
                                    fn_803135A8(&q2, r);
                                } else if (an->flags & 2) {
                                    q1 = x1.quat;
                                    q2 = x2.quat;
                                }
                                fn_80313774(&q1, &q2, &q, w);
                                qp = &q;
                            }
                            fn_8000D228(ft, an, tr, fi, &x);
                        }
                    } else {
                        fn_8000D228(ft, an, tr, fi, &x);
                    }
                    fn_8000D754(an, nd, f, &x, qp, out[nd->idx]);
                }
            }
        } else {
            cnt = fn_8000BE24(a, lay);
            if (cnt > 4) {
                fn_8001E008(lbl_80360B08, 0x7D5, lbl_80360B08 + 0x80);
            }
            for (;;) {
                int id = fn_8000BEA8(cnt, lay, ev);
                if (id < 0) break;
                nd2 = fn_8000F3D4(md, id);
                if (!(nd2->flags & 0x10000000)) {
                    f2 = 0;
                                        for (k = 0; k < cnt; k++) {
                        if (ev[k] != 0) {
                            f2 |= ev[k]->f;
                        }
                    }
                    f2 |= nd2->flags;
                    for (k = 0; k < 43; k++) {
                        ((f32*)&x)[k] = ((f32*)nd2 + 0x10)[k];
                    }
                    rf = f2 & 0x10;
                                        if (rf != 0) {
                        if (an->flags & 1) {
                            fn_8001D748(r, nd2->axis, nd2->xf.rx, nd2->xf.ry, nd2->xf.rz);
                            fn_803135A8(&q, r);
                        } else if (an->flags & 2) {
                            q = nd2->xf.quat;
                        }
                        qp2 = &q;
                    } else {
                        qp2 = 0;
                    }
                    k2 = cnt - 1;
                    lp = &lay[k2];
                    ep = &ev[k2];
                    for (; k2 >= 0; lp--, ep--, k2--) {
                        f32 w2;
                        fn_8000E9C4(7, 0);
                        la = lp->anim;
                        e = *ep;
                        lt = fn_800081B4(lp->a);
                        w2 = fn_800081BC(lp->a);
                        fn_8000E9A8(&lt, &li);
                        if (0.0f != w2) {
                            if (nd2->flags & 0x20000000) {
                                w2 = 1.0f;
                            }
                                                        for (m = 0; m < 43; m++) {
                                ((f32*)&xb)[m] = ((f32*)nd2 + 0x10)[m];
                            }
                            if (e != 0) {
                                fn_8000D228(lt, la, (NTrack*)e, li, &xb);
                            }
                            m = 0;
                            do {
                                fn_8000DA14(w2, m, &x, &xb);
                                m++;
                            } while (m < 43);
                            if (rf != 0) {
                                fn_8000DA60(la, nd2, &xb, &q, w2);
                            }
                        }
                    }
                    fn_8000D754(an, nd2, f2, &x, qp2, out[nd2->idx]);
                }
            }
        }
        fn_8000DB10(md, an, out, ft);
    }
    n2 = md->nodes;
    for (i2 = 0; i2 < md->count; i2++, n2++) {
        if (!(n2->flags & 0x14000000)) {
            fn_80312344(n2->xf.world, *out);
        }
        out++;
    }
}
}
