/* fn_8000D228: 21 of 331 words differ, float registers in the Hermite case only. Fixed-GQR psq via OSFastCast-style inline asm works. */
#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct TrA { u16 id; u8 shift; u8 x3; u16 x4; u16 n; int ofs; } TrA;
typedef struct TrC { int id; int n; int ofs; int ofs2; f32 def; } TrC;
typedef struct KA { s16 f; s16 v; } KA;
typedef struct KC { int f; f32 v; f32 in; f32 out; } KC;
typedef struct NAnm { u8 x0[0xC]; u32 flags; u8 x10[0x24 - 0x10]; void* tracks; s16* idx; void* keys; } NAnm;
typedef struct NTrack { u8 x0[8]; int first; int cnt; } NTrack;
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
    f32 v;
    f32 m0;
    int ix;
    f32 s3;
    f32 h11;
    f32 h01;
    f32 dt;
    f32 f0;
    f32 s2;
    f32 h10;
    f32 r;
    f32 f1;
    f32 s;
    KC* kc;
    f32 v1;
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
void fn_8000D228(f32 t, NAnm* o, NTrack* tr, u32 k, f32* out) {
/*Q*/
    u32 a1;
    int m;
    int mid;
    int last;
    int m2;
    int s;
    int i3;
    u32 q;
    int kv;
    TrA* a;
    int i;
    int hi;
    int lo;
    int s2;
    TrA* b;
    int kv2;
    int mid2;
    u32 a0;
    u16 n;
    int i2;
    u16 n2;
    u32* keys2;
    int lo2;
    TrC* e;
    KA* keys;
/*F*/
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
                f32 v0 = LD5(&p[0].v);
                f32 v1 = LD5(&p[1].v);
                SetG5(0x00070007);
                {
                f32 f0 = LD5(&p[0].f);
                f32 f1 = LD5(&p[1].f);
                v = v0 + (v1 - v0) * (t - f0) / (f1 - f0);
                }
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
                {
                f32 v0 = dec(a0);
                f32 v1 = dec(a1);
                f32 f0 = a0 >> 20;
                f32 f1 = a1 >> 20;
                vb = v0 + (v1 - v0) * (t - f0) / (f1 - f0);
                }
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
}
