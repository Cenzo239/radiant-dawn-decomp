#include "game/rG_800A3D88/types.h"

// Battle character: footstep and attack-hit event handling from the animation's event track.
extern "C" {
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct Mo { u8 p[0x14]; int m14; };
struct Mdl {
    u8 p[0x58];
    f32 m58, m5c;
    u8 p60[0x8C - 0x60];
    u16 m8c; s16 m8e; u16 m90; s16 m92; u16 m94; s16 m96; u16 m98; s16 m9a;
};
struct Dat { u8 p[0x14C]; u8 m14c; };
struct ChrU { u8 p[0x30]; Mdl* mdl; u8 p34[0x50 - 0x34]; u32 m50; u8 p54[4]; s16 m58, m5a; u8 p5c[0x78 - 0x5C]; Dat* data; };
struct Ct { u8 p[0xE]; u8 me; u8 pf[0x9C - 0xF]; void* m9c; };
struct Eo { u8 p[0x30]; Ct* m30; };
struct Sfx { u8 p[4]; void* m4; void* m8; void* mc; void* m10; };
class Snd {
public:
    virtual int v0(int);
    virtual int v1(int);
    virtual int v2();
    virtual int v3(int);
    virtual int v4(int);
    virtual int v5(int);
    virtual int v6(int);
    virtual int v7(int);
    virtual int v8(int);
    virtual int v9(int);
    virtual int v10(int);
    virtual int v11(int);
    virtual int v12(int);
    virtual int v13(int);
    virtual int v14(int);
    virtual int v15(int);
    virtual int v16(int);
    virtual int v17(int);
    virtual int v18(int);
    virtual int v19(int);
    virtual int v20(int);
    virtual int v21(int);
    virtual int v22(int);
};
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
void fn_800BA1C0(void*);
void* fn_800AAD2C();
void* fn_800AABB4(void*);
f32 fn_8001E064(int);
int fn_800AAC3C(void*);
f32 fn_800AAAF8(void*);
f32 fn_800A84A4(const char*);
Mo* fn_80007F10(Mdl*);
f32 fn_8001EF30(f32, f32, f32, f32);
void fn_8000A22C(Mo*, void*, f32, f32);
int fn_80008EB4(Mdl*);
int fn_80008D48(Mdl*, const u16*);
void* fn_800A6578(void*, int);
int fn_80008CF0(Mdl*, int);
Eo* fn_800E3810(void*, ChrU*);
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChrU*, int, Vec*, int, int);
void fn_800E48C8(Eo*, Vec*);
void fn_800E49AC(Eo*, f32);
void fn_800E4AD4(Eo*, f32);
void fn_800E4904(Eo*, int, ChrU*);
int fn_800AABD0(void*);
Sfx* fn_800A85CC(int, int);
s8 fn_802549C4(void*, Vec*, f32);
Snd* fn_8024F50C(int);
static inline int Node(ChrU* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline s16 Val(ChrU* c, int k) {
    if (c->mdl == NULL) return -1;
    return fn_80008CF0(c->mdl, k);
}
#define ZERO(v) *(u32*)&v.x = 0; *(u32*)&v.y = 0; *(u32*)&v.z = 0
static inline void PosY(ChrU* c, Vec* out) {
    Vec v, t;
    ZERO(t);
    fn_800B4000(c, Node(c, STR(0x26)), &t, -1, 0);
    *(W3*)&v = *(W3*)&t;
    v.y = fn_8001E064(c->m5a);
    *(W3*)out = *(W3*)&v;
}
static inline void PosN(ChrU* c, Vec* out) {
    Vec t;
    ZERO(t);
    fn_800B4000(c, Node(c, STR(0x26)), &t, -1, 0);
    *(W3*)out = *(W3*)&t;
}
static inline void Place(Eo* o, ChrU* c, f32 y) {
    Vec tmp, d;
    PosY(c, &d);
    d.y = y;
    *(W3*)&tmp = *(W3*)&d;
    fn_800E48C8(o, &tmp);
}
static inline s8 Play1(void* e, ChrU* c) {
    Vec a, b;
    PosY(c, &a);
    b = a;
    return fn_802549C4(e, &b, 0.0f);
}
static inline void Play(void* e, ChrU* c) {
    Vec a, b;
    PosN(c, &a);
    b = a;
    fn_802549C4(e, &b, 0.0f);
}
static inline int Look3(ChrU* c) {
    u16 k[4] = {0x32, 0x4A, 0x4B, 0xFFFF};
    return fn_80008D48(c->mdl, k);
}
static inline int Look2(ChrU* c) { return Look3(c); }
void fn_800BA2C8(ChrU* c) {
    u16 a0; s16 a1; u16 a2; s16 a3; u16 a4; s16 a5; u16 a6; s16 a7;
    void* sc;
    void* bd;
    int blend;
    Mo* q;
    if (c->mdl == NULL) return;
    sc = fn_800AAD2C();
    if (sc == NULL) return;
    bd = fn_800AABB4(sc);
    if (bd == NULL) return;
    f32 yy; f32 f0; f32 pct;
    yy = fn_8001E064(c->m5a);
    blend = 0;
    if (fn_800AAC3C(sc)) {
        yy = fn_800AAAF8(sc);
        blend = (int)fn_800A84A4(STR(0x2BD));
    }
    if (blend > 0) {
        a0 = c->mdl->m8c;
        a1 = c->mdl->m8e;
        a2 = c->mdl->m90;
        a3 = c->mdl->m92;
        a4 = c->mdl->m94;
        a5 = c->mdl->m96;
        a6 = c->mdl->m98;
        a7 = c->mdl->m9a;
        q = fn_80007F10(c->mdl);
        if (q != NULL) {
            f0 = c->mdl->m58 - (f32)q->m14 - c->mdl->m5c;
            pct = c->mdl->m58 - (f32)q->m14;
            if (f0 < (f32)blend) {
                f0 = (f32)blend * fn_8001EF30(0.0f, 1.0f, (f32)blend, f0) + f0;
                pct = (f32)blend * fn_8001EF30(0.0f, 1.0f, (f32)blend, pct) + pct;
            } else {
                f0 += (f32)blend;
                pct += (f32)blend;
            }
            f0 += (f32)q->m14;
            pct += (f32)q->m14;
            fn_8000A22C(q, &c->mdl->m8c, f0, pct);
        }
    }
    if (fn_80008EB4(c->mdl)) {
    u16 ids[5] = {0x2B, 0x2C, 0x2D, 0x2E, 0xFFFF};
    if (!(c->m50 & 0x8000)) {
        void* e = NULL;
        void* cb = NULL;
        switch ((u16)fn_80008D48(c->mdl, ids)) {
        case 0x2B:
            e = fn_800A6578(bd, 0);
            bd = (void*)(u16)Val(c, 0x2B);
            break;
        case 0x2C:
            e = fn_800A6578(bd, 1);
            bd = (void*)(u16)Val(c, 0x2C);
            break;
        case 0x2D:
            e = fn_800A6578(bd, 2);
            bd = (void*)(u16)Val(c, 0x2D);
            break;
        case 0x2E:
            e = fn_800A6578(bd, 3);
            bd = (void*)(u16)Val(c, 0x2E);
            cb = (void*)fn_800BA1C0;
            break;
        }
        if (e != NULL) {
            Eo* o = fn_800E3810(e, c);
            if (o != NULL) {
                if (bd == NULL) pct = 1.0f;
                else pct = (f32)(u32)bd / 100.0f;
                Place(o, c, yy);
                fn_800E49AC(o, fn_8001E064(c->m58));
                o->m30->me = 3;
                fn_800E4AD4(o, pct);
                fn_800E4904(o, 0, c);
                o->m30->m9c = cb;
            }
        }
    }
    }
    if (blend > 0) {
        Mdl* m = c->mdl;
        m->m8c = a0;
        m->m8e = a1;
        m = c->mdl;
        m->m90 = a2;
        m->m92 = a3;
        m = c->mdl;
        m->m94 = a4;
        m->m96 = a5;
        m = c->mdl;
        m->m98 = a6;
        m->m9a = a7;
    }
    if (fn_80008EB4(c->mdl)) {
        int id = Look2(c);
        if ((u16)id == 0xFFFF) return;
        int dd = c->data->m14c;
        Sfx* s = fn_800A85CC(dd, fn_800AABD0(sc));
        if (s == NULL) return;
        switch ((u16)id) {
        case 0x32: {
            void* e = s->m4;
            if (e != NULL) {
                s8 k = Play1(e, c);
                if (k >= 0) {
                    Snd* n = fn_8024F50C(k);
                    if (n != NULL && n->v2()) n->v22(0);
                }
            }
            void* e8 = s->m8;
            if (e8 != NULL) Play(e8, c);
            break;
        }
        case 0x4A:
            if (s->mc != NULL) Play(s->mc, c);
            break;
        case 0x4B:
            if (s->m10 != NULL) Play(s->m10, c);
            break;
        }
    }
}
}
