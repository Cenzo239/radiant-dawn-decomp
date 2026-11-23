#include "game/rG_800A3D88/chr.h"

// Battle character: react to the animation events of the current frame.
extern "C" {
struct ChI { u8 p[0x30]; Mdl* mdl; u8 p34[0x50 - 0x34]; u32 m50; u8 p54[0x58 - 0x54]; s16 m58; u8 p5a[0x5F - 0x5A]; u8 m5f; };
struct EffI { u8 p[0x30]; struct EffD* m30; };
struct EffD { u8 p[0xE]; u8 mE; u8 pf[0x98 - 0xF]; void* m98; void* m9c; u8 pa0[4]; u32 mA4; };
struct W3 { u32 a, b, c; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_80008EB4(Mdl*);
int fn_80007630(Mdl*, const char*);
void fn_800B4000(ChI*, int, W3*, int, int);
void fn_800F172C(Mdl*, W3*);
void fn_800F1F88(Mdl*);
int fn_80008C98(Mdl*, int);
u16 fn_80008CF0(Mdl*, int);
f32 fn_800A84A4(const char*);
void* fn_800A64A0();
void fn_800A4B40(void*, int, int, f32);
void fn_800A4BBC(void*);
EffI* fn_800F1820(Mdl*, ChI*);
char* strcpy(char*, const char*);
int fn_80290DDC(char*, const char*, ...);
f32 fn_8000793C(Mdl*, int);
void fn_800E4904(EffI*, int, ChI*);
void fn_800E48F0(EffI*, int, int);
void fn_800E4AD4(EffI*, f32);
void fn_800B9CA8(void*);
f32 fn_8001E064(int);
void fn_800E49AC(EffI*, f32);
#if TARGET_PC
FE10_PROTO void fn_801CDA08(ptr32<const void>);
#else
void fn_801CDA08(ChI*);
#endif
void fn_801CDA9C();
void fn_801CDAF8(ChI*);
void fn_800F199C(Mdl*, ChI*);
static inline int Ev(ChI* c, int k) {
    if (c->mdl == NULL) return 0;
    return fn_80008C98(c->mdl, k);
}
static inline int NodeOf(ChI* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline int NodeB(ChI* c, const char* n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline s16 EvVal(ChI* c, int k) {
    if (c->mdl == NULL) return -1;
    return fn_80008CF0(c->mdl, k);
}
static inline f32 Len(ChI* c, int k) {
    f32 v;
    if (k < 0) v = 1.0f;
    else if (c->mdl == NULL) v = 1.0f;
    else { f32 t = fn_8000793C(c->mdl, k); v = t; }
    return v;
}
static inline void Shake(ChI* c, int ev, int dir) {
    int t = (int)fn_800A84A4(STR(0x293));
    f32 a = fn_800A84A4(STR(0x2A2));
    s16 v = fn_80008CF0(c->mdl, ev);
    if (v != 0) a = a * (f32)v / 100.0f;
    fn_800A4B40(fn_800A64A0(), (s16)t, dir, a);
}
void fn_800B9D18(ChI* c) {
    W3 t; W3 r;
    char buf[0x20];
    if (!fn_80008EB4(c->mdl)) return;
    r.a = 0;
    r.b = 0;
    r.c = 0;
    fn_800B4000(c, NodeOf(c, STR(0x26)), &r, -1, 0);
    t = r;
    fn_800F172C(c->mdl, &t);
    fn_800F1F88(c->mdl);
    if (Ev(c, 0x17)) {
        c->m5f = EvVal(c, 0x17);
    }
    if (Ev(c, 9)) Shake(c, 9, 1);
    if (Ev(c, 10)) {
        Shake(c, 10, -1);
        c->m50 |= 0x4000;
    }
    if (Ev(c, 0xB) && (c->m50 & 0x4000)) {
        fn_800A4BBC(fn_800A64A0());
        c->m50 &= ~0x4000;
    }
    EffI* e = fn_800F1820(c->mdl, c);
    if (e != NULL) {
        u32 id = e->m30->mA4 & 0xFFFF;
        if (id == 0) strcpy(buf, STR(0x2B3));
        else fn_80290DDC(buf, STR(0x2B7), id);
        int k = NodeB(c, buf);
        if (k >= 0) {
            f32 f = Len(c, k);
            fn_800E4904(e, 0, c);
            fn_800E48F0(e, 1, k);
            fn_800E4AD4(e, f);
            if (id == 0) e->m30->m98 = (void*)fn_800B9CA8;
            else e->m30->m9c = (void*)fn_800B9CA8;
        }
        fn_800E49AC(e, fn_8001E064(c->m58));
        e->m30->mE = 3;
    }
    if (c->m50 & 0x200000) {
        if (Ev(c, 0x37)) {
            c->mdl->flags |= 4;
            c->m50 = (c->m50 | 0x400000) & ~0x200000;
        }
    }
    if (Ev(c, 0x14)) fn_801CDA08(c);
    if (Ev(c, 0x15)) fn_801CDA9C();
    if (Ev(c, 0x16)) fn_801CDAF8(c);
    fn_800F199C(c->mdl, c);
}
}
