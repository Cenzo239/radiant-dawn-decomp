/* Add missing start keys to a camera script and start it, 8013067C. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_804CB820;
extern u8 lbl_804CB838;
extern u8 lbl_804CB818;
extern u8 lbl_804CB819;
extern u8 lbl_803CAB38[];
struct View {
    u16 flags;
    u8 pad[0xd2];
    Vec d4; Vec e0; Vec ec; Vec f8;
    f32 v104; f32 v108; f32 v10c;
};
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
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual f32 v4(int);
    virtual void v5();
};
extern Cam* lbl_804CB81C;
struct Fl { u8 pad[0x93c]; f32 x; f32 y; u8 pad2[8]; f32 z; };
struct Ev {
    u8 kind;
    s16 key;
    Vec v;
    u32 d;
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
extern u8 lbl_8041349C[];
extern u32 lbl_804CB700;
extern void fn_801301DC(Evs*);
extern void fn_80130BB4(Evs*, f32);
extern void fn_80083DC4(Evs*, int);
static inline BOOL Has(Evs* s, int k, f32 z) {
    int n = s->cnt[k];
    Ev* p;
    int i;
    if (n == 0) return 0;
    p = s->first[k];
    for (i = 0; i < n; i++) {
        if ((f32)p->key == z) return 1;
        p++;
    }
    return 0;
}
static inline void Add(Evs* s, int k, Vec v) {
    s->ev[s->n].kind = k;
    s->ev[s->n].key = 0;
    s->ev[s->n].v = v;
    s->ev[s->n].d = 0;
    s->n++;
}
struct W3 { u32 a, b, c; };
#define WC(d,s) *(W3*)&(d) = *(W3*)&(s)
static inline void AddZ(Evs* s) { Vec z = {0.0f, 0.0f, 0.0f}; Add(s, 3, z); }
static inline void AddV(Evs* s, Cam* c) { Add(s, 1, c->v50); }
static inline void AddV2(Evs* s, Cam* c) { AddV(s, c); }
static inline void AddZ2(Evs* s) { AddZ(s); }
static inline void AddQ(Evs* s, const Vec* q) { Add(s, 3, *q); }
static inline void AddZ3(Evs* s) { Vec z = {0.0f, 0.0f, 0.0f}; AddQ(s, &z); }
static inline void AddZ4(Evs* s) { Vec z = {0.0f, 0.0f, 0.0f}; { Vec y = z; Add(s, 3, y); } }
static inline Vec MkZ() { Vec z = {0.0f, 0.0f, 0.0f}; return z; }
static inline void Rst(Cam* c) {
    c->mn.x = -1000.0f;
    c->mx.x = -1000.0f;
    c->col.x = 0.0f;
    c->col.y = 0.0f;
    c->col.z = 0.0f;
    c->v68 = 1.0f;
}
void fn_8013067C(Evs* s, u32 x) {
    Vec t2;
    Vec t1;
    Cam* c = lbl_804CB81C;
    s->v30 = x;
    fn_801301DC(s);
    Rst((Cam*)lbl_8041349C);
    if (s->cnt[0] == 0) {
        WC(t1, c->cur);
        ((Cam*)lbl_8041349C)->tgt = t1;
        ((Cam*)lbl_8041349C)->cur = t1;
    } else if (!Has(s, 0, 0.0f)) {
        Add(s, 0, c->cur);
    }
    if (s->cnt[2] == 0) {
        Cam* k = (Cam*)lbl_8041349C;
        f32 q;
        q = c->a.x; k->a.x = q; k->b.x = q;
        q = c->a.y; k->a.y = q; k->b.y = q;
        q = c->a.z; k->a.z = q; k->b.z = q;
    } else {
        {f32 x,y,z; x=c->a.x; y=c->a.y; z=c->a.z; t2.x=x; t2.y=y; t2.z=z;}
        if (!Has(s, 2, 0.0f)) {
            Add(s, 2, t2);
        }
    }
    if (s->cnt[3] != 0 && !Has(s, 3, 0.0f)) {
        Add(s, 3, MkZ());
    }
    if (s->cnt[1] != 0 && !Has(s, 1, 0.0f)) {
        Add(s, 1, c->v50);
    }
    fn_801301DC(s);
    lbl_804CB820 = 3;
    lbl_804CB81C = (Cam*)lbl_8041349C;
    if (lbl_804CB700 & 0x8001) {
        s->t34 = s->maxk;
    }
    fn_80130BB4(s, (f32)s->t34);
    if (s->t34 >= s->maxk) {
        s->done = 1;
        fn_80083DC4(s, 0);
    } else {
        fn_80083DC4(s, 10);
    }
}
}
