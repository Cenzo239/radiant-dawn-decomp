#include "game/rG_800A3D88/types.h"

// Character effect hook: aim the effect at its bone, stretch it to the opponent, hand over on hit.
extern "C" {
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct Mdl { u32 flags; };
struct Bone { u8 p[0x60]; f32 m60; };
struct ChrU { u8 p[0x30]; Mdl* mdl; u8 p34[0x58 - 0x34]; s16 m58, m5a; u8 p5c[0x78 - 0x5C]; void* data; u8 p7c[4]; void* m80; };
struct Ev { u8 p[2]; s16 m2; };
struct Ctx {
    Mdl* m0;
    u16 m4;
    u8 p6[8];
    u8 me;
    u8 pf[0x28 - 0xF];
    Vec m28;
    Vec m34;
    u8 p40[0x54 - 0x40];
    f32 m54;
    u8 p58[0xA4 - 0x58];
    ChrU* mA4;
    int mA8;
    int mAC;
    Ev* mB0;
    u8 pb4[0xC4 - 0xB4];
    void* mC4;
};
struct Pr { u8 p[0x30]; Ctx* m30; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_800B4000(ChrU*, int, Vec*, int, int);
void fn_800E48C8(Pr*, Vec*);
void fn_803134C4(Vec*, Vec*);
f32 fn_8001EA74(const Vec*, Vec*);
void fn_800E4918(Pr*, f32);
void fn_80313484(Vec*, Vec*, Vec*);
f32 fn_80313508(Vec*);
int fn_80007630(Mdl*, const char*);
Bone* fn_800078E4(Mdl*, int);
void fn_800E49AC(Pr*, f32);
int fn_800E46C4(Pr*, int);
int fn_801CFC58(Ev*);
void* fn_800E1FA0(void*);
Pr* fn_800E3810(void*, Pr*);
f32 fn_8001E064(int);
void* fn_800A64A0();
void fn_800A4B18(void*);
void fn_800A47AC(void*, int);
void fn_800E4B20(Pr*, int);
void fn_800E240C(Vec*, Pr*);
void fn_800A4AE4(void*, Vec*);
static inline int Node(ChrU* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline void Stretch(Pr* p, Mdl* m, f32 d) {
    int k = fn_80007630(m, STR(0x30B));
    if (d > 0.0f && k >= 0) {
        Bone* b = fn_800078E4(m, k);
        if (b->m60 > 0.0f) p->m30->m54 = d / b->m60;
    }
}
static inline void Send(Pr* p, const Vec& v) {
    Vec a;
    *(W3*)&a = *(W3*)&v;
    fn_800E48C8(p, &a);
}
static inline void Cur(W3* out, Pr* p) {
    Vec r;
    fn_800E240C(&r, p);
    *out = *(W3*)&r;
}
static inline void Send3(void* b, const Vec& v) {
    Vec a;
    *(W3*)&a = *(W3*)&v;
    fn_800A4AE4(b, &a);
}
static inline void Hand2(Pr* o, ChrU* c, Vec* a) {
    Vec v8, r;
    *(u32*)&r.x = 0;
    *(u32*)&r.y = 0;
    *(u32*)&r.z = 0;
    fn_800B4000(c, Node(c, STR(0x26)), &r, -1, 0);
    *(W3*)&v8 = *(W3*)&r;
    v8.y = fn_8001E064(c->m5a);
    f32 f = fn_8001E064(c->m58);
    *(W3*)a = *(W3*)&v8;
    fn_800E48C8(o, a);
    fn_800E49AC(o, f);
}
static inline void Hand(Pr* o, ChrU* c) {
    Vec a;
    Hand2(o, c, &a);
}
void fn_800BB520(Pr* p) {
    Ctx* x = p->m30;
    Mdl* m;
    ChrU* c;
    int kind;
    Ev* ev;
    Vec h;
    c = x->mA4;
    m = x->m0;
    int nd = x->mA8;
    kind = x->mAC;
    ev = x->mB0;
    if (c->data != NULL) {
    switch (kind) {
    case 9:
    case 13:
        if (fn_800B4000(c, nd, &h, -1, 0)) {
            Send(p, h);
            if (c->m80 != NULL) {
                Vec q = p->m30->m34;
                Vec kv = {1.0f, 0.0f, 0.0f};
                Vec dir;
                *(u32*)&dir.x = 0;
                *(u32*)&dir.y = 0;
                *(u32*)&dir.z = 0;
                dir.x = q.x - h.x;
                dir.y = q.y - h.y;
                fn_803134C4(&dir, &dir);
                if (dir.x < 0.0f) dir.x *= -1.0f;
                fn_800E4918(p, 57.29578f * fn_8001EA74(&kv, &dir));
                fn_80313484(&q, &h, &h);
                Stretch(p, m, fn_80313508(&h));
            }
        }
        if (kind == 13) {
            Vec v98, v8c;
            if (fn_800B4000(c, Node(c, STR(0x2B)), &v98, -1, 0)) {
                if (fn_800B4000(c, Node(c, STR(0x30)), &v8c, -1, 0)) {
                    fn_80313484(&v8c, &v98, &h);
                    Vec kz = {0.0f, 0.0f, 1.0f};
                    Vec d;
                    *(u32*)&d.x = 0;
                    *(u32*)&d.y = 0;
                    *(u32*)&d.z = 0;
                    d.x = h.x;
                    d.z = h.z;
                    fn_803134C4(&d, &d);
                    f32 r = 57.29578f * fn_8001EA74(&kz, &d);
                    if (d.x < 0.0f) r *= -1.0f;
                    fn_800E49AC(p, r);
                }
            }
        }
        break;
    case 8: {
        Vec a = x->m28;
        Vec b = p->m30->m34;
        fn_80313484(&b, &a, &h);
        Stretch(p, m, fn_80313508(&h));
        break;
    }
    }
    if (ev != NULL) {
        switch (ev->m2) {
        case 0x6E:
        case 0x6F:
            if (fn_800E46C4(p, 5)) {
                Pr* o;
                if (fn_801CFC58(ev)) {
                    void* s = fn_800E1FA0(p->m30->mC4);
                    if (s != NULL) {
                        o = fn_800E3810(s, p);
                        if (o != NULL) {
                            Hand(o, c);
                            o->m30->me = 3;
                            o->m30->m4 = p->m30->m4;
                            p->m30->m4 = 0;
                            void* bd = fn_800A64A0();
                            if (bd != NULL) {
                                fn_800A4B18(bd);
                                fn_800A47AC(bd, 0);
                            }
                            break;
                        }
                    }
                }
                p->m30->m4 = 2;
                if (c->mdl != NULL) c->mdl->flags &= ~8;
            }
            break;
        case 0x70:
            if (fn_800E46C4(p, 1)) fn_800E4B20(p, -1);
            break;
        }
    }
    }
    Vec t;
    Cur((W3*)&t, p);
    if (fn_80313508(&t) > 0.0f) {
        void* bd = fn_800A64A0();
        if (bd != NULL) Send3(bd, t);
    }
}
}
