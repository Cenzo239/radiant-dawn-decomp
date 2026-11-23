#include "game/rG_800A3D88/chr.h"
extern "C" {
struct FG { s16 x, y, fl; };
extern FG lbl_803E50F0[];
extern const f64 lbl_804CD550;
struct F43 { u8 p[0x38]; f32 m38, m3c; u8 p40[3]; s8 m43; u8 p44[4]; u32 m48; };
int fn_8007E9BC(int);

f32 fn_800081B4(Mdl*);
int fn_800B5AB8(Chr*);
static inline f32 Frame(Chr* c) { if (c->mdl == NULL) return 0.0f; return fn_800081B4(c->mdl); }
int fn_800B5D14(Chr* c) {
    if (c->mdl == NULL) return 1;
    if (c->m7c == NULL) return 1;
    if (c->m7c->flags & 1) return 1;
    if (c->mdl->flags & 2) return 1;
    f32 t = Frame(c);
    if (t >= (f32)fn_800B5AB8(c)) return 1;
    return 0;
}
struct WB { u8 p[0x18]; struct { u8 p[0x40]; f32 x, y; }* m18; u8 p1c[0x14]; f32 m30, m34, m38; int m38i; };
struct WC { u8 p[0x18]; struct { u8 p[0x40]; f32 x, y; }* m18; u8 p1c[0x14]; f32 m30, m34; int m38; f32 m3c, m40, m44; };
f64 fn_80295CF0(f64);
int fn_8017F990(int, int);
f64 fn_80295940(f64);
extern const f32 lbl_804CD270, lbl_804CD280;
struct T18 { u8 p[0x40]; f32 x, y; };

struct Ef { u8 p[0x38]; void* m38; int m3c; u8 p40[4]; s16 m44; u16 m46; f32 m48, m4c, m50; };
extern u8 lbl_803825A8[];
extern char lbl_80365B64[];
extern const f32 lbl_804CD470;
void fn_800829CC(Ef*, void*);
f32 fn_800A84A4(const char*);
Ef* fn_80081050(void*, Ef*);
void fn_800BF148(Ef*);
void fn_800C0F44(Ef*, int);
#pragma use_lmw_stmw on
void fn_800BF444(Ef* e, int n, int k) {
    fn_800829CC(e, lbl_803825A8);
    Ef* c; int i;
    f32 d = -fn_800A84A4(lbl_80365B64 + 0x1F);
    for (i = 0; i < n; i++) {
        f32 y = d * (f32)(i + 1);
        c = fn_80081050(lbl_803825A8, e);
        c->m38 = e->m38;
        fn_800BF148(c);
        s16 v = e->m44;
        c->m3c = e->m3c;
        c->m44 = v;
        c->m48 = lbl_804CD470;
        c->m4c = y;
        c->m50 = lbl_804CD470;
        c->m46 |= 0x10;
        fn_800C0F44(c, k);
    }
}
void fn_800BF608(Ef* e, int n, int k) {
    e->m46 |= 0x10;
    fn_800C0F44(e, k);
    if (n > 1) {
        fn_800829CC(e, lbl_803825A8);
        int i; Ef* c;
        f32 d = -fn_800A84A4(lbl_80365B64 + 0x1F);
        for (i = 0; i < n - 1; i++) {
            f32 y = d * (f32)(i + 1);
            c = fn_80081050(lbl_803825A8, e);
            c->m38 = e->m38;
            fn_800BF148(c);
            s16 v = e->m44;
            c->m3c = e->m3c;
            c->m44 = v;
            c->m48 = lbl_804CD470;
            c->m4c = y;
            c->m50 = lbl_804CD470;
            c->m46 |= 0x10;
            fn_800C0F44(c, k);
        }
    }
}
#pragma use_lmw_stmw off
extern FG lbl_dummy;
struct FadeG { u8 pad[0x32]; u16 m32; u8 m34, m35, m36, m37; s16 m38, m3a, m3c, m3e; };
extern FadeG* lbl_804CB6D8;
extern const f32 lbl_804CD5C8;
void fn_800C86D4(u8 r, u8 g, u8 b, int t0, int t1) {
    FadeG* f = lbl_804CB6D8;
    f->m32 = 1;
    u8 c[4] = {r, g, b, 0};
    f->m34 = r; f->m35 = g; f->m36 = b; f->m37 = c[3];
    f->m38 = 0;
    f->m3a = (f32)t0 / lbl_804CD5C8;
    f->m3c = 0;
    f->m3e = (f32)t1 / lbl_804CD5C8;
}
class VO {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* v9();
    virtual void* v10();
    virtual int v11();
    virtual int v12();
    void* m4;
};
#if TARGET_PC
FE10_PROTO void fn_80006B84(void*, void*, void*, ptr32<const void>, ptr32<const void>);
#else
void fn_80006B84(void*, void*, void*, void*, void*);
#endif
void fn_80305DB4(void*, int, int);
void fn_80022254(void*, int);
#if TARGET_PC
FE10_PROTO void fn_80306054(void*, ptr32<const void>);
#else
void fn_80306054(void*, void*);
#endif
void fn_8031292C(void*, f32, f32, f32);
void fn_80307F10(void*, int, int);
extern const f32 lbl_804CD610;
void fn_800C986C(VO* o) {
    u8 a[0x20]; u8 b[0x10];
    void* s = o->v9();
    fn_80006B84(o->m4, a, b, o->v10(), s);
    fn_80305DB4(a, 0, 0);
    fn_80022254(a, 1);
    fn_80306054(b, o->v10());
}

}
