#include "game/rG_800A3D88/chr.h"
extern "C" {
extern char lbl_803657E8[];
int fn_80007630(Mdl*, const char*);
int fn_800B4000(Chr*, int, Vec*, int, int);
void fn_800B33F4(Chr*, int);
extern const f32 lbl_804CD3B8;
struct Cx { u8 p[0x30]; Mdl* mdl; u8 p34[0x10]; f32 m44; u8 p48[8]; u32 m50; };
static inline int NodeIdx(Chr* c, const char* nm) { if (c->mdl == NULL) return -1; return fn_80007630(c->mdl, nm); }
static inline Vec GetNode(Chr* c, const char* nm) {
    Vec b;
    *(u32*)&b.x = 0; *(u32*)&b.y = 0; *(u32*)&b.z = 0;
    int k; if (c->mdl == NULL) k = -1; else { int t = fn_80007630(c->mdl, nm); k = t; } fn_800B4000(c, k, &b, -1, 0);
    return b;
}
int fn_800B93F8(Chr* c, f32* lo, f32* hi) {
    if (!(((Cx*)c)->m50 & 4)) return 0;
    f32 d = lbl_804CD3B8;
    const char* nm = lbl_803657E8 + 0x26;
    Vec v = GetNode(c, nm);
    if (v.x < *lo) d = *lo - v.x;
    if (v.x > *hi) d = *hi - v.x;
    if (lbl_804CD3B8 != d) {
        ((Cx*)c)->m44 += d;
        fn_800B33F4(c, 0);
        return 1;
    }
    return 0;
}
int fn_80008C98(Mdl*, int);
s16 fn_80008CF0(Mdl*, int);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(ChrData*, const char*);
#else
void* fn_800A7460(ChrData*, const char*);
#endif
f32 fn_800A84A4(const char*);
extern const f32 lbl_804CD43C;
struct Pt { u8 p[0x50]; u32 m50; u8 p54[0x78-0x54]; ChrData* m78; u8 p7c[8]; f32 m84, m88; };
struct C7 { u8 p[0x30]; Mdl* mdl; u8 p34[0x80-0x34]; Pt* m80; };
static inline int Mov(C7* c, int k) { if (c->mdl == NULL) return 0; return fn_80008C98(c->mdl, k); }
static inline s16 Frm(C7* c, int k) { if (c->mdl == NULL) return -1; return fn_80008CF0(c->mdl, k); }
int fn_800B7F98(C7* c) {
    int f1;
    int f2;
    Pt* p2;
    Pt* p1;
    int r;
    char* sb;

    if (c->m80 == NULL) return 0;
    r = 0;
    if (Mov(c, 0x3F)) {
        if (c->mdl == NULL) f1 = -1; else { int t = fn_80008CF0(c->mdl, 0x3F); f1 = t; }
        p1 = c->m80;
        if (p1->m78 != NULL) {
            sb = lbl_803657E8;
            if (fn_800A7460(p1->m78, sb + 0xFF) == NULL) {
                p1->m84 = (f32)f1 * fn_800A84A4(sb + 0x251) / lbl_804CD43C;
                p1->m50 |= 0x200;
            }
        }
        r = 1;
    }
    if (Mov(c, 0x40)) {
        if (c->mdl == NULL) f2 = -1; else { int t = fn_80008CF0(c->mdl, 0x40); f2 = t; }
        p2 = c->m80;
        if (p2->m78 != NULL && fn_800A7460(p2->m78, lbl_803657E8 + 0x25E) == NULL) {
            p2->m88 = (f32)f2 * fn_800A84A4(lbl_803657E8 + 0x267) / lbl_804CD43C;
            p2->m50 |= 0x400;
        }
        r = 1;
    }
    return r;
}
struct M2 { u8 p[0x58]; f32 frame; };
struct Ch3 { u8 p[0x30]; M2* m30; u8 p34[0x1C]; u32 m50; };
struct E3 { u8 p[0x3C]; Ch3* m3c; u8 p40[4]; s16 m44; u16 m46; };
struct T3 { u8 p[0x18]; E3* m18; };
void fn_80178254(T3*);
void* fn_800078E4(M2*, int);
void fn_80007A00(M2*, u32);
void fn_8000F3E4(void*, u32);
f32 fn_80006CF8();
void fn_80007DE8(M2*);
void fn_800BFA4C(E3*);
void fn_801780B8(T3*);
void fn_80007A5C(M2*, u32);
void fn_80178364(T3*);
void fn_80178C98(T3*);
extern const f32 lbl_804CD460;
#pragma use_lmw_stmw off
void fn_800C0A88(T3* t) {
    Ch3* c;
    int n;
    int i;
    void* h;
    f32 sv;
    E3* e;
    M2* m;

    e = t->m18;
    c = e->m3c;
    n = e->m44;
    m = c->m30;
    fn_80178254(t);
    if (!(c->m50 & 0x100) && !(e->m46 & 2)) {
        h = fn_800078E4(m, n);
        fn_80007A00(m, 0x10000000);
        fn_8000F3E4(h, 0x10000000);
        sv = m->frame;
        m->frame = sv - lbl_804CD460;
        int d = 4;
        f32 step = fn_80006CF8() / (f32)d;
        for (i = 0; i < 3; i++) {
            m->frame += step;
            fn_80007DE8(m);
            fn_800BFA4C(e);
            fn_801780B8(t);
        }
        m->frame = sv;
        fn_80007DE8(m);
        fn_800BFA4C(e);
        fn_80007A5C(m, 0x10000000);
    }
    fn_801780B8(t);
    fn_80178364(t);
    fn_80178C98(t);
}
}
