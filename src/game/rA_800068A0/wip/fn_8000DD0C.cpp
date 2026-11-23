/* fn_8000DD0C: 81 of 513 words differ, registers only, in the inlined copy of 8000D228. Prelude and structure are right. */
#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct TrA { u16 id; u8 shift; u8 x3; u16 x4; u16 n; int ofs; } TrA;
typedef struct TrC { int id; int n; int ofs; int ofs2; f32 def; } TrC;
typedef struct KA { s16 f; s16 v; } KA;
typedef struct KC { int f; f32 v; f32 in; f32 out; } KC;
typedef struct NTrack NTrack;
typedef struct NAnm { u8 x0[0xC]; u32 flags; u8 x10[0x1C - 0x10]; int ntr; NTrack* trs; void* tracks; s16* idx; void* keys; } NAnm;
struct NTrack { u32 node; u32 flags; int first; int cnt; };
static inline void SetG5(register u32 v) { asm { mtspr 0x395, v } }
static inline f32 LD5(register const void* p) { register f32 r; asm { psq_l r, 0(p), 1, 5 } return r; }
#define GQR(s, t) ((((s) << 8) | (t)) | (((s) << 8) | (t)) << 16)
static inline int dec(u32 v) { return (v & 0x7FFFF) - (v & 0x80000); }
static inline int tailA(KA* keys, int lo, int s, int k) {
    if (lo > s) return s;
    s = lo - 1;
    if (keys[lo].f <= k) s = lo;
    return s;
}
static inline int tailB(u32* keys, int lo, int s, u32 k) {
    if (lo > s) return s;
    s = lo - 1;
    if ((keys[lo] >> 20) <= k) s = lo;
    return s;
}
static inline f32 evalC(TrC* e, NAnm* o, f32 t) {
/*P*/
    f32 h01;
    f32 v1;
    f32 s3;
    f32 s2;
    f32 dt;
    f32 m0;
    f32 s;
    KC* kc;
    f32 f0;
    f32 v;
    f32 h10;
    f32 r;
    int ix;
    f32 f1;
    f32 h11;
/*E*/
    if (e->n == 0) return e->def;
    kc = (KC*)o->keys + e->ofs2;
    ix = o->idx[e->ofs + (int)t];
    if (ix < 0) {
        f0 = 0.0f;
        v = e->def;
    } else {
        kc += ix;
        f0 = kc->f;
        v = kc->v;
        kc++;
    }
    if (ix == e->n - 1) return v;
    v1 = kc->v;
    f1 = kc->f;
    switch (e->id) {
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
        if (kc->out < 300000.0f) {
            dt = f1 - f0;
            m0 = dt * kc->in;
            s = (t - f0) / dt;
            dt = dt * kc->out;
            s2 = s * s;
            s3 = s * s2;
            h01 = -2.0f * s3 + 3.0f * s2;
            h10 = s + (s3 - 2.0f * s2);
            h11 = s3 - s2;
            r = h10 * m0;
            r = h01 * (v1 - v) + r;
            r = h11 * dt + r;
            return v + r;
        }
        return v;
    default:
        return (v1 - v) * ((t - f0) / (f1 - f0)) + v;
    }
}
static inline void sample(f32 t, NAnm* o, NTrack* tr, u32 k, f32* out) {
/*P*/
    f32 vb0;
    int kv2;
    f32 fa0;
    f32 va1;
    f32 va0;
    f32 fb1;
    f32 fb0;
    f32 vb1;
    f32 fa1;
    u32* keys2;
    int m;
    int s;
    int last;
    int m2;
    int mid;
    int i3;
    u32 q;
    KA* keys;
    TrA* a;
    u32 a0;
    int i;
    u16 n;
    int hi;
    int s2;
    TrA* b;
    int mid2;
    int lo;
    int i2;
    u16 n2;
    u32 a1;
    int lo2;
    TrC* e;
    int kv;
/*E*/
    if (o->flags & 0x10) {
        i = 0;
        a = (TrA*)o->tracks + tr->first;
        for (; i < tr->cnt; i++, a++) {
            f32 v;
            keys = (KA*)o->keys + a->ofs;
            q = a->shift << 8 | 7;
            SetG5(q | q << 16);
            n = a->n;
            if ((int)k >= keys[n - 1].f) {
                v = LD5(&(keys + (u16)n)[-1].v);
            } else if ((int)k < keys[0].f) {
                v = LD5(&keys[0].v);
            } else {
                KA* p;
                
if (n == 0) { s = -1; goto da; }
                m = n;
 hi = m - 1;
                lo = 0;
                while (lo <= hi) {
                    mid = lo + ((hi - lo) >> 1);
                    kv = *(u16*)&keys[mid].f;
                    if (kv < (int)k) {
                        lo = mid + 1;
                    } else if (kv > (int)k) {
                        hi = mid - 1;
                    } else {
                        s = mid;
                        goto da;
                    }
                }
                if (hi < 0) { s = -1; goto da; }
                s = (u16)m - 1;
                s = tailA(keys, lo, s, k);
da:
                p = &keys[s];
                va0 = LD5(&p[0].v);
                va1 = LD5(&p[1].v);
                SetG5(0x00070007);
                fa0 = LD5(&p[0].f);
                fa1 = LD5(&p[1].f);
                v = va0 + (va1 - va0) * (t - fa0) / (fa1 - fa0);
            }
            out[a->id] = v;
        }
    } else if (o->flags & 0x20) {
        i2 = 0;
        b = (TrA*)o->tracks + tr->first;
        for (; i2 < tr->cnt; i2++, b++) {
            f32 vb;
            keys2 = (u32*)o->keys + b->ofs;
            n2 = b->n;
            m2 = n2;
 last = m2 - 1;
            if (k >= keys2[last] >> 20) {
                vb = dec((keys2 + (u16)n2)[-1]);
            } else if (k < keys2[0] >> 20) {
                vb = dec(keys2[0]);
            } else {
                
if (n2 == 0) { s2 = -1; goto db; }
                                lo2 = 0;
                while (lo2 <= last) {
                    mid2 = lo2 + ((last - lo2) >> 1);
                    kv2 = keys2[mid2] >> 20;
                    if (kv2 < (int)k) {
                        lo2 = mid2 + 1;
                    } else if (kv2 > (int)k) {
                        last = mid2 - 1;
                    } else {
                        s2 = mid2;
                        goto db;
                    }
                }
                if (last < 0) { s2 = -1; goto db; }
                s2 = (u16)m2 - 1;
                s2 = tailB(keys2, lo2, s2, k);
db:

                a0 = keys2[s2];
                a1 = keys2[s2 + 1];
                vb0 = dec(a0);
                vb1 = dec(a1);
                fb0 = a0 >> 20;
                fb1 = a1 >> 20;
                vb = vb0 + (vb1 - vb0) * (t - fb0) / (fb1 - fb0);
            }
            vb /= (f32)(1 << b->shift);
            out[b->id] = vb;
        }
    } else {
        i3 = 0;
        e = (TrC*)o->tracks + tr->first;
        for (; i3 < tr->cnt; i3++, e++) {
            out[e->id] = evalC(e, o, t);
        }
    }
}
#pragma inline_max_size(20000)

typedef struct NXf { f32 scale[3]; f32 rot[3]; f32 trans[3]; f32 rotOfs[3]; f32 rotPivot[3]; f32 sclPivot[3]; f32 rotPivot2[3]; f32 sclPivot2[3]; f32 rotPost[3]; f32 quat[4]; u8 x7C[0x30]; } NXf;
typedef struct NNode { u8 x0[0xC]; u32 flags; u8 x10[0x40 - 0x10]; NXf x; u32 id : 12; u32 rest : 20; } NNode;
extern NAnm* fn_80007F10(void* a);
extern f32 fn_800081B4(void* a);
extern void fn_8017F44C(void* d, int v, u32 n);
extern void fn_8017F480(void* d, const void* s, u32 n);
extern void fn_8017F4A0(void* d, const void* s, u32 n);
static inline void FastCast(void) {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr 0x392, r3
        li r3, 5
        oris r3, r3, 5
        mtspr 0x393, r3
        li r3, 6
        oris r3, r3, 6
        mtspr 0x394, r3
        li r3, 7
        oris r3, r3, 7
        mtspr 0x395, r3
    }
}
static inline s16 f2s(register f32 v) { u32 tmp; register u32* p = &tmp; register s16 out; asm { psq_st v, 0(p), 1, 5; lha out, 0(p) } return out; }
NTrack* fn_8000DD0C(f32 t, void* a, NNode* n, NXf* x) {
    NAnm* o;
    int k;
    NTrack* tr;
    u32 f;
    int c;
    o = fn_80007F10(a);
    if (o == 0) return 0;
    if (t < 0.0f) t = fn_800081B4(a);
    fn_8017F44C(x, 0, sizeof(NXf));
    x->scale[0] = 1.0f;
    x->scale[1] = 1.0f;
    x->scale[2] = 1.0f;
    FastCast();
    k = f2s(t);
    f = n->flags;
    if (f & 8) {
        fn_8017F480(x->scale, n->x.scale, 12);
        if (f & 0x100) {
            fn_8017F480(x->sclPivot, n->x.sclPivot, 12);
            if (f & 0x400) fn_8017F480(x->sclPivot2, n->x.sclPivot2, 12);
        }
    }
    if (f & 0x20) fn_8017F480(x->trans, n->x.trans, 12);
    if (f & 0x10) {
        fn_8017F480(x->rot, n->x.rot, 12);
        if (f & 0x40) fn_8017F480(x->rotOfs, n->x.rotOfs, 12);
        if (f & 0x800) fn_8017F480(x->rotPost, n->x.rotPost, 12);
        if (f & 0x80) {
            fn_8017F480(x->rotPivot, n->x.rotPivot, 12);
            if (f & 0x200) fn_8017F480(x->rotPivot2, n->x.rotPivot2, 12);
        }
    }
    c = o->ntr;
    tr = o->trs;
    for (; c > 0; c--, tr++) {
        if (tr->node == n->id) {
            u32 g = tr->flags | n->flags;
            if (g & 8) {
                fn_8017F480(x->scale, n->x.scale, 12);
                if (g & 0x100) {
                    fn_8017F480(x->sclPivot, n->x.sclPivot, 12);
                    if (g & 0x400) fn_8017F480(x->sclPivot2, n->x.sclPivot2, 12);
                }
            }
            if (g & 0x20) fn_8017F480(x->trans, n->x.trans, 12);
            if (g & 0x10) {
                fn_8017F480(x->rot, n->x.rot, 12);
                if (g & 0x40) fn_8017F480(x->rotOfs, n->x.rotOfs, 12);
                if (g & 0x800) fn_8017F480(x->rotPost, n->x.rotPost, 12);
                if (g & 0x80) {
                    fn_8017F480(x->rotPivot, n->x.rotPivot, 12);
                    if (g & 0x200) fn_8017F480(x->rotPivot2, n->x.rotPivot2, 12);
                }
                if (o != 0 && (o->flags & 2)) fn_8017F4A0(x->quat, n->x.quat, 16);
            }
            sample(t, o, tr, k, (f32*)x);
            return tr;
        }
    }
    return 0;
}
}
