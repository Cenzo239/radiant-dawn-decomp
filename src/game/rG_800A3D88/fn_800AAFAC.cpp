#include "game/rG_800A3D88/chr.h"
extern "C" {
struct Ch { u8 pad[0x30]; Mdl* mdl; u8 p34[0x78-0x34]; void* data; };
struct Sc { u8 p[0xB]; s8 mB; };
struct Bat {
    u8 p[0x3C];
    Ch* e[2];
    void* m44;
    u8 p48[7];
    u8 m4f;
    u8 p50[0x68-0x50];
    s8 m68, m69; u8 m6a, m6b;
    u8 p6c[4];
    Ch* m70;
    Ch* m74;
    s8 m78;
    u8 m79;
    s8 m7a;
    u8 p7b;
    u16 m7c;
    s16 m7e;
    u8 m80, m81, m82, m83, m84, m85;
    Sc* m88;
    u8 p8c[8];
    int m94;
};
extern char lbl_80365488[];
extern char lbl_803653B8[];
#define STR(n) (lbl_80365488 + (n))
long long OSGetTime();
void fn_800A947C(Bat*);
Sc* fn_801CE7F4();
void fn_801CE800(Sc*);
void fn_800AB1D0(Bat*);
void fn_800AB310(Bat*);
int fn_800AB41C(Bat*);
void fn_80083DC4(void*, int);
void fn_800A98C0(Bat*);
void fn_800A95F4(Bat*);
f32 fn_800A7370(void*, const char*);
void fn_800B2810(Ch*, int, f32);
void fn_800AB734(Bat*);
void fn_800AB988(Bat*);
int fn_800BD280(Ch*);
void* fn_800B1728(Ch*);
int fn_800B591C(Ch*);
void fn_800A6DE4(void*, int);
void fn_800EE77C();
static inline int IsR(Bat* b) {
    switch (b->m78) {
    case 0: case 2: return 1;
    case 1: default: return 0;
    }
}
static inline Ch* At(Bat* b, int i) { if (i < 0) return NULL; return b->e[i]; }
static inline void Upd(Ch* c) {
    if (fn_800BD280(c)) {
        void* s = fn_800B1728(c);
        if (s != NULL) fn_800A6DE4(s, fn_800B591C(c));
    }
}
static inline void Loop(Bat* b) { for (int i = 0; i < 2; i++) { Ch* c = At(b, i); if (fn_800BD280(c)) { void* s = fn_800B1728(c); if (s != NULL) fn_800A6DE4(s, fn_800B591C(c)); } } }
void fn_800ADA7C(Bat* b) {
    OSGetTime();
    fn_800A947C(b);
    b->m81 = 0;
    b->m82 = 0;
    b->m80 = 0;
    b->m83 = 1;
    b->m84 = 0;
    b->m7e = 0;
    b->m6b = 0;
    b->m6a = 0;
    b->m68 = -1;
    b->m69 = -1;
    b->m7a = -1;
    b->m7c = 400;
    b->m79 = 0;
    b->m94 = 0;
    b->m88 = fn_801CE7F4();
    fn_801CE800(b->m88);
    fn_800AB1D0(b);
    fn_800AB310(b);
    if (fn_800AB41C(b) == 0) {
        fn_80083DC4(b, 0xC);
        return;
    }
    fn_800A98C0(b);
    fn_800A95F4(b);
    if (0.0f != fn_800A7370(b->m70->data, STR(0x22D)) && IsR(b)) {
        f32 v = fn_800A7370(b->m70->data, STR(0x22D));
        fn_800B2810(b->m70, b->m78, v);
        fn_800B2810(b->m74, b->m78, v);
    }
    fn_800AB734(b);
    fn_800AB988(b);
    Loop(b);
    fn_800EE77C();
    OSGetTime();
}
int fn_801D0214(Sc*, int);
Ch* fn_800A93B8(Bat*, int);
int fn_801CFDEC(Sc*, int);
int fn_801CFA90(Sc*);
void fn_800A9E64(Bat*, int, int);
void fn_800A9FC8(Bat*, int, int);
void* fn_800A7D44(const char*);
void* fn_800A7E34(const char*);
const char* fn_801CFF0C(Sc*, int);
struct Fx { u8 p[8]; void* m8; };
void fn_800A6790(Fx*);
struct ExI { u8 p[0xC]; u8 mC; u8 p0d[0x98-0xD]; void* m98; void* m9c; };
struct Ex { u8 p[0x30]; ExI* m30; };
Ex* fn_800E3A10(void*, Bat*);
Ex* fn_800E3810(void*, Bat*);
f32 fn_800A84A4(const char*);
void fn_800AAE94(Ex*);
void fn_800AAF20(Ex*);
void fn_800E4904(Ex*, int, Ch*);
int fn_800A8208(const char*);
int fn_801CFE3C(Sc*, int);
int fn_800B1B48(Ch*, int, int, u16, int);
void fn_800A4B00(void*, Ch*);
void fn_800A5F08(void*, Ch*, int);
#pragma use_lmw_stmw on
static inline Fx* FindFx(Bat* b, int k) {
    if (k == 0x6F) {
        if (fn_801CFA90(b->m88) == 0) return (Fx*)fn_800A7D44(STR(0));
    } else {
        return (Fx*)fn_800A7E34(fn_801CFF0C(b->m88, k));
    }
    return NULL;
}
void fn_800AAFAC(Bat* b, int k) {
    Ch* c = fn_800A93B8(b, fn_801D0214(b->m88, k));
    if (fn_801CFDEC(b->m88, k) != 0) {
        if (b->m88->mB != 1) return;
    } else if (fn_801CFA90(b->m88) != 0) {
        if (b->m88->mB != 1) return;
    }
    fn_800A9E64(b, -1, -1);
    fn_800A9FC8(b, -1, -1);
    Fx* f = FindFx(b, k);
    if (f != NULL) {
        u8 t = 0;
        fn_800A6790(f);
        void* r = f->m8;
        Ex* e = NULL;
        if (fn_801CFDEC(b->m88, k) != 0) {
            if (r != NULL) e = fn_800E3810(r, b);
            t = fn_800A84A4(STR(5));
        } else if (r != NULL) {
            e = fn_800E3A10(r, b);
        }
        if (e != NULL) {
            e->m30->m98 = (void*)fn_800AAE94;
            e->m30->m9c = (void*)fn_800AAF20;
            fn_800E4904(e, 0, c);
            e->m30->mC = t;
        }
        int a = fn_800A8208(STR(0x14));
        if (fn_801CFE3C(b->m88, k) != 0) {
            if (c == b->m70) fn_800B1B48(c, a, -1, 0xFFFF, -1);
            fn_800A4B00(b->m44, c);
            fn_800A5F08(b->m44, c, a);
        }
    }
}
void fn_8017EA78(int, int, int, int, int, Bat*);
void fn_8017F194(int, int, int, Bat*);
void fn_800A9E64(Bat* b, int v, int t) {
    int a = v, c = v, e = v, d = v;
    if (v < 0) {
        a = fn_800A84A4(lbl_803653B8 + 0x2C);
        c = fn_800A84A4(lbl_803653B8 + 0x39);
        e = fn_800A84A4(lbl_803653B8 + 0x44);
        d = fn_800A84A4(lbl_803653B8 + 0x53);
    }
    if (t < 0) {
        t = fn_800A84A4(lbl_803653B8 + 0x64);
        if (v == 100) t *= 2;
    }
    if (v != b->m4f) {
        fn_8017EA78(0, a, a, t, 0, b);
        fn_8017EA78(1, a, a, t, 0, b);
        fn_8017EA78(3, c, c, t, 0, b);
        fn_8017EA78(2, d, 100, t, 0, b);
        fn_8017F194(e, t, 0, b);
        b->m4f = v;
    }
}

#define SG SceneGlobalY
struct SG { u8 p[0x3F0]; void* m3f0; u8 p3f4[0x890-0x3F4]; void* m890; u8 p894[0x15EC-0x894]; u32 flags; };
extern SG lbl_803C8E80;
void fn_8002BCC4(SG*);
u8* fn_8002C590(SG*);
int fn_8011F428(u16*);
#if TARGET_PC
FE10_PROTO void fn_8010301C(void*, void*, int, int, p32arg);
#else
void fn_8010301C(void*, void*, int, int, int);
#endif
u8* fn_8002C738(SG*);
void* fn_80134E30();
void fn_801868E8(void*, void*);
void fn_80081A90(void*);
#pragma use_lmw_stmw off
void fn_800AE774(void* p) {
    fn_8002BCC4(&lbl_803C8E80);
    void* x; void* y; u16* q;
    u8* a = fn_8002C590(&lbl_803C8E80);
    if (a != NULL) {
        q = *(u16**)(a + 0x3F0);
        if (q != NULL && fn_8011F428(q) == 0) *q |= 0x10;
    }
    x = lbl_803C8E80.m3f0;
    y = lbl_803C8E80.m890;
    if (x != NULL && y != NULL) {
        fn_8010301C(x, y, 0, 0, 0);
        fn_8010301C(y, x, 0, 0, 0);
    }
    u8* c = fn_8002C738(&lbl_803C8E80);
    if (c != NULL) {
        void* z = *(void**)(c + 0x3F0);
        if (z != NULL) {
            fn_80134E30();
            fn_801868E8(z, p);
        }
    }
    if (lbl_803C8E80.flags & 0x200000) fn_80081A90(p);
}
struct Pc { u8 p[0x3C]; u8* m3c; };
extern char lbl_803656F8[];
extern const f32 lbl_804CD3A0, lbl_804CD3A4, lbl_804CD3A8;
int fn_80007630(u8*, const char*);
void* fn_80010C18();
f32* fn_80010DA4(void*, int);
void fn_80312344(void*, void*);
void fn_80312318(void*);
Vec fn_800076E8(u8*, int);
void fn_803134C4(Vec*, Vec*);
void fn_8031356C(Vec*, Vec*, Vec*);
f32 fn_8031354C(Vec*, Vec*);
f64 fn_80295A90(f64);
void fn_80312830(void*, Vec*, f32);
u8* fn_800080B8(u8*);
void fn_80007EE4(u8*);
void fn_8001E694(void*, void*);
void fn_8001E6D0(void*, void*);
void fn_80312378(void*, void*, void*);
void fn_800AEC8C(Pc* p) {
    u8* t; int n = fn_80007630(p->m3c, lbl_803656F8 + 0x31);
    if (n < 0) return;
    f32* cam = fn_80010DA4(fn_80010C18(), 1);
    if (cam == NULL) return;
    u8 m0[0x30]; u8 m1[0x30]; u8 m2[0x30]; u8 m3[0x30];
    fn_80312344(p->m3c + 0x10, m0);
    fn_80312318(p->m3c + 0x10);
    Vec e;
    e = fn_800076E8(p->m3c, n);
    fn_803134C4(&e, &e);
    Vec f;
    f.x = -cam[2];
    f.y = -cam[3];
    f.z = -cam[4];
    fn_803134C4(&f, &f);
    Vec ax;
    fn_8031356C(&e, &f, &ax);
    f32 d = fn_8031354C(&e, &f);
    if (d >= lbl_804CD3A0) {
        fn_80312318(m1);
    } else if (d <= lbl_804CD3A4) {
        fn_80312830(m1, &ax, lbl_804CD3A8);
    } else {
        fn_80312830(m1, &ax, fn_80295A90(d));
    }
    t = fn_800080B8(p->m3c);
    fn_80007EE4(p->m3c);
    t = t + n * 0x30;
    fn_80312344(t, m3);
    fn_8001E694(m3, m2);
    fn_8001E6D0(m3, m3);
    fn_80312378(m1, m2, m2);
    fn_8001E694(m2, m2);
    fn_80312378(m2, m3, t);
    fn_80312344(m0, p->m3c + 0x10);
}
}
