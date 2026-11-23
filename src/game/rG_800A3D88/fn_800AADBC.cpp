#include "game/rG_800A3D88/chr.h"
extern "C" {
struct SA { u8 pad[0x88]; void* m88; };
struct R54 { u8 pad[0x54]; s8 m54; };
struct R88 { u8 pad[0xB]; s8 mB; };
void* fn_801D0214(void*, int);
#if TARGET_PC
FE10_PROTO R54* fn_800A93B8(SA*, ptr32<const void>);
#else
R54* fn_800A93B8(SA*, void*);
#endif
int fn_801CFDEC(void*, int);
int fn_801D012C(void*, int);
void* fn_801D009C(void*, int);
void fn_801CE2F4(void*, int, SA*);
#define SceneGlobal SceneGlobalX
struct SceneGlobal { u8 p[0x15EC]; u32 flags; };
extern SceneGlobal lbl_803C8E80;
void fn_800AADBC(SA* p, int k) {
    int c = fn_800A93B8(p, fn_801D0214(p->m88, k))->m54;
    if ((fn_801CFDEC(p->m88, k) == 0 || ((R88*)p->m88)->mB == 1) && fn_801D012C(p->m88, k) != 0) {
        void* q = fn_801D009C(p->m88, k);
        int v = 0;
        if (c == 0) v = 5;
        if (c == 1) {
            v = 6;
            if (lbl_803C8E80.flags & 0xC00000) v = 10;
        }
        fn_801CE2F4(q, v, p);
    }
}
struct Hh { u16 pad0[4]; u16 m8; };
struct In { u8 pad[0x18]; u32 m18; f32 m1c, m20, m24; u8 p28[0x9C-0x28]; u32 m9c; u8 pa0[4]; Chr* a4; u8 pa8[8]; void* mb0; u8 pb4[0xC4-0xB4]; Hh* c4; };
struct PA { u8 pad[0x30]; In* m30; };
Vec fn_800B3824(Chr*, int);
Vec fn_800B377C(Chr*, int);
void fn_800E48C8(PA*, Vec*);
f32 fn_8001E064(s16);
void fn_800E49AC(PA*, f32);
void fn_800AAE94(PA* p) {
    Chr* c = p->m30->a4;
    if (p->m30->c4->m8 & 0x80) {
        Vec w = fn_800B3824(c, -1);
        fn_800E48C8(p, &w);
        fn_800E49AC(p, fn_8001E064(c->m58));
    }
}
void fn_800AAF20(PA* p) {
    Chr* c = p->m30->a4;
    if (!(p->m30->c4->m8 & 0x80)) {
        Vec w = fn_800B377C(c, -1);
        fn_800E48C8(p, &w);
        fn_800E49AC(p, fn_8001E064(c->m58));
    }
}
void fn_800E4904(PA*, int, AnimState*);
int fn_80007630(Mdl*, const char*);
int fn_800B4000(Chr*, int, Vec*, int, int);
void fn_800E48AC(PA*, f32, f32, f32);
extern char lbl_803657E8[];
static inline int NodeIdx(Chr* c, const char* nm) { if (c->mdl == NULL) return -1; return fn_80007630(c->mdl, nm); }
static inline Vec GetNode(Chr* c, const char* nm) {
    Vec b;
    *(u32*)&b.x = 0; *(u32*)&b.y = 0; *(u32*)&b.z = 0;
    int k; if (c->mdl == NULL) k = -1; else { int t = fn_80007630(c->mdl, nm); k = t; } fn_800B4000(c, k, &b, -1, 0);
    return b;
}
void fn_800BA1C0(PA* p) {
    In* n = p->m30;
    Chr* c = n->a4;
    if (c == NULL) return;
    AnimState* st = c->m7c;
    if (n->m18 & 0x80000000) {
        fn_800E4904(p, 3, st);
    } else if (st != n->mb0) {
        n->m9c = 0;
        return;
    }
    Vec a = *(Vec*)&p->m30->m1c;
    const char* nm = lbl_803657E8 + 0x26;
    Vec d = GetNode(c, nm);
    fn_800E48AC(p, d.x, a.y, d.z);
}
struct FE { u8 p[0x3C]; int m3c, m40, m44; };
int fn_8001CD78(Mdl*);
void fn_8001B254(Mdl*);
FE* fn_80007F3C(Mdl*);
void fn_80008F54(Mdl*, int);
void fn_800180F0(Mdl*);
#pragma use_lmw_stmw on
void fn_800BE940(Chr* c) {
    if (c->mdl == NULL) return;
    if (c->flags & 1) return;
    FE* f = fn_80007F3C(c->mdl);
    u8 v = ((u8*)c->mdl)[0x82];
    fn_8001CD78(c->mdl);
    fn_8001B254(c->mdl);
    int a = f->m3c;
    int b = f->m40;
    int d = f->m44;
    fn_80008F54(c->mdl, 0x87);
    f->m3c = a;
    f->m40 = b;
    f->m44 = 0;
    fn_800180F0(c->mdl);
    if (d != 0) {
        fn_80008F54(c->mdl, 0x8D);
        f->m3c = 0;
        f->m40 = 0;
        f->m44 = d;
        fn_800180F0(c->mdl);
    }
    f->m3c = a;
    f->m40 = b;
    f->m44 = d;
    fn_80008F54(c->mdl, v);
}
#pragma use_lmw_stmw off
struct FW { u8 p[0x34]; struct { u8 p[0x20]; u16 m20; }* m34; u8 p38[0x48-0x38]; u32 m48; };
extern const f32 lbl_804CD560;
void fn_800C4EDC(f32, FW*, int, int, int, int);
void fn_800C57B0(f32, FW*, int, int, int, int, int);
void fn_800C5A34(f32, FW*, int, int, int, int, int, int);

struct BB { u8 p[0x6C]; u8 m6c; u8 p6d[0xB]; Mdl* m78; u8 p7c[8]; s16 m84; s16 m86; };
void fn_800081D4(Mdl*);
void fn_800F199C(Mdl*, BB*);
f32 fn_8001EBC8(f32, f32, f32, f32, int);
void fn_80008B50(Mdl*);
void fn_800A53DC(BB*);
void fn_80007C58(Mdl*);
#if TARGET_PC
FE10_PROTO int fn_8000BF68(Mdl*, p32arg);
#else
int fn_8000BF68(Mdl*, int);
#endif
void fn_800A59A4(BB*);
extern const f32 lbl_804CD298, lbl_804CD29C;
void fn_800A6340(BB* p) {
    if (p->m6c == 0) return;
    if (p->m78 == NULL) return;
    fn_800081D4(p->m78);
    fn_800F199C(p->m78, p);
    if (p->m84 > 0) {
        p->m86++;
        *(f32*)((u8*)p->m78 + 0x78) = fn_8001EBC8(lbl_804CD298, lbl_804CD29C, p->m84, p->m86, 2);
        if (p->m86 >= p->m84) {
            fn_80008B50(p->m78);
            p->m84 = 0;
        }
    }
    fn_800A53DC(p);
    fn_80007C58(p->m78);
    if (fn_8000BF68(p->m78, 0)) fn_800A59A4(p);
}
struct Tri { int a, b; f32 c; };
struct LS { u8 p[0x40]; Mdl* m40; int m44; Tri* m48; };
void fn_80290DDC(char*, const char*, ...);
#if TARGET_PC
FE10_PROTO p32ret fn_80008110(Mdl*, const char*);
#else
int fn_80008110(Mdl*, const char*);
#endif
void* fn_800791B0(int);
u8* fn_800078E4(Mdl*, int);
extern char lbl_80365364[];
void fn_800A8B80(LS* p, Mdl* m) {
    char buf[0x18];
    p->m40 = m;
    p->m44 = 0;
    for (;;) {
        fn_80290DDC(buf, lbl_80365364, p->m44 + 1);
        int a = fn_80007630(p->m40, buf);
        int b = fn_80008110(p->m40, buf);
        if (a < 0 || b == 0) break;
        p->m44++;
    }
    if (p->m44 > 0) {
        p->m48 = (Tri*)fn_800791B0(p->m44 * 0xC);
        for (int i = 0; i < p->m44; i++) {
            fn_80290DDC(buf, lbl_80365364, i + 1);
            p->m48[i].a = fn_80007630(p->m40, buf);
            p->m48[i].b = fn_80008110(p->m40, buf);
            p->m48[i].c = *(f32*)(fn_800078E4(p->m40, p->m48[i].a) + 0x40);
        }
    }
}
}
