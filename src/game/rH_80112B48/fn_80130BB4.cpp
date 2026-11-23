/* Apply camera script keys at time t, 80130BB4. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off
extern "C" {
struct View;
struct CamBase {
    View* view;
    Vec a;       /* 0x04 */
    Vec b;       /* 0x10 */
    int mode;    /* 0x1C */
    Vec mn;      /* 0x20 */
    Vec mx;      /* 0x2C */
    Vec cur;     /* 0x38 */
    Vec tgt;     /* 0x44 */
    Vec v50;     /* 0x50 */
    Vec col;     /* 0x5C */
    f32 v68;     /* 0x68 */
};
class Cam : public CamBase {
public:
    virtual void v0();
};
extern Cam* lbl_804CB81C;
extern f32 lbl_804CDD88;
struct Keyf { u8 pad[4]; Vec v; };
struct Ev {
    u8 kind;
    s16 key;
    Vec v;
    Keyf* d;
};
struct Evs {
    u8 pad[0x30];
    u32 v30;
    int t34;
    int maxk;
    u8 done;
    u8 pad3d[3];
    Ev* ev;
    u8 n;
    u8 pad45;
    u8 cnt[5];
    u8 pad4b;
    Ev* first[5];
};
extern Vec fn_8012FFD0(Ev*, int, f32);
extern void fn_8012F3A8(Vec*, const Vec*, const Vec*);
extern f32 fn_8001EF30(f32, f32, f32, f32);
struct W3 { u32 a, b, c; };
#define WC(d,s) *(W3*)&(d) = *(W3*)&(s)
static inline void SetT(Cam* c, Vec v) { c->cur = c->tgt = v; }
static inline Keyf* Seek(Evs* s, f32 t) {
    Ev* e;
    Keyf* r;
    int i;
    int n = s->cnt[3];
    if (n == 0) return 0;
    e = s->first[3];
    r = e->d;
    for (i = 0; i < n; i++) {
        if ((f32)e->key > t) break;
        r = e->d;
        e++;
    }
    return r;
}
static inline Vec E(Evs* s, int k, f32 t) { Vec r = fn_8012FFD0(s->first[k], s->cnt[k], t); Vec w = r; return w; }
static inline Vec F0(Evs* s, int k, f32 t) { return E(s, k, t); }
static inline Vec F(Evs* s, int k, f32 t) { return F0(s, k, t); }
static inline void L5(Vec* r, const Vec& a, Evs* s, f32 t) { Vec bb = E(s, 1, t); Vec aa = a; fn_8012F3A8(r, &aa, &bb); }
static inline Vec Look(Cam* c, Evs* s, f32 t) { Vec r; Vec a = c->cur; L5(&r, a, s, t); return r; }
void fn_80130BB4(Evs* s, f32 t) {
    Cam* c = lbl_804CB81C;
    if (s->cnt[0]) {
        SetT(c, F(s, 0, t));
    }
    if (s->cnt[3]) {
        Keyf* k = Seek(s, t);
        if (k) {
            Vec b = k->v;
            Vec a = c->cur;
            f32 kk = 0.1f;
            b.x = fn_8001EF30(a.x, b.x, lbl_804CDD88, kk);
            b.y = fn_8001EF30(a.y, b.y, lbl_804CDD88, kk);
            b.z = fn_8001EF30(a.z, b.z, lbl_804CDD88, kk);
            SetT(c, b);
        }
    }
    if (s->cnt[2]) {
        Vec v = F(s, 2, t);
        c->a = v;
    }
    if (s->cnt[1]) {
        Vec r = Look(c, s, t);
        {
        f32 q;
        q = r.x; c->a.x = q; c->b.x = q;
        q = r.y; c->a.y = q; c->b.y = q;
        q = r.z; c->a.z = q; c->b.z = q;
        }
    }
}
}
