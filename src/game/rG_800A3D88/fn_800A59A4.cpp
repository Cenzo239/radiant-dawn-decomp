#include "game/rG_800A3D88/chr.h"
extern "C" {
struct K20 { u8 p[0x20]; u8 m20; };
u8 fn_800A6844(K20* k, int a) {
    u8 v = k->m20;
    switch (v) {
    case 8:
        if (a == 0) v = 1;
        else if (a == 2) v = 1;
        break;
    case 2: case 5:
        if (a == 0) v = 2;
        else if (a == 2) v = 2;
        else if (a == 1) v = 5;
        else if (a == 3) v = 5;
        else if (a == 4) v = 5;
        break;
    case 3: case 6:
        if (a == 0) v = 3;
        else if (a == 2) v = 3;
        else if (a == 1) v = 6;
        else if (a == 3) v = 6;
        else if (a == 4) v = 6;
        break;
    case 4: case 7:
        if (a == 0) v = 4;
        else if (a == 2) v = 4;
        else if (a == 1) v = 7;
        else if (a == 3) v = 4;
        else if (a == 4) v = 7;
        break;
    }
    return v;
}
struct Cam { u8 p[0xD4]; Vec eye; Vec at; u8 pec[0x14C-0xEC]; f32 m14c; };
struct Bo { u8 p[0x64]; f32 m64; u8 p68[0xA]; u16 m72; u8 p74[0x70-0x74+0x10]; };
struct BO { u8 p[0x64]; f32 m64; u8 p68[8]; u8 m70; u8 p71; u16 m72; u8 p74[4]; u8* m78; };
Cam* fn_8000F470();
void fn_8001E6AC(u8*, void*);
void fn_80312DB4(void*, Vec*, Vec*);
void fn_80313484(Vec*, Vec*, Vec*);
f32 fn_80313508(Vec*);
void fn_803134C4(Vec*, Vec*);
void fn_80312654(void*, int, f32);
void fn_80175FF4(Vec*, Vec*, Vec*, Vec*, Vec*);
void fn_803128AC(void*, f32, f32, f32);
void fn_800A4D88(Vec*, BO*);
f32 fn_800A84A4(const char*);
#if TARGET_PC
FE10_PROTO void fn_8000F954(Cam*, p32arg, int);
#else
void fn_8000F954(Cam*, int, int);
#endif
void fn_8000FA98(Cam*);
extern const f32 lbl_804CD298, lbl_804CD29C, lbl_804CD2BC, lbl_804CD2C0, lbl_804CD2C4;
extern char lbl_80365064[];
void fn_800A59A4(BO* b) {
    Cam* c = fn_8000F470();
    if (b->m70) {
        u8 m0[0x30];
        u8 m1[0x30];
        Vec e;
        Vec a;
        Vec f;
        Vec q;
        Vec w;
        Vec l;
        fn_8001E6AC(b->m78 + 0x10, m0);
        fn_80312DB4(m0, &c->eye, &e);
        fn_80312DB4(m0, &c->at, &a);
        e.y = lbl_804CD298;
        a.y = lbl_804CD298;
        fn_80313484(&a, &e, &f);
        if (lbl_804CD298 == fn_80313508(&f)) return;
        fn_803134C4(&f, &f);
        fn_80312654(m1, 0x79, lbl_804CD2BC);
        fn_80312DB4(m1, &f, &q);
        *(u32*)&w.x = 0; *(u32*)&w.y = 0; *(u32*)&w.z = 0;
        fn_80175FF4(&w, &q, &e, &a, &l);
        fn_803128AC(m0, lbl_804CD2C0 * -l.x, lbl_804CD2C0 * -l.y, lbl_804CD2C0 * -l.z);
        fn_80312DB4(m0, &c->at, &c->at);
        fn_80312DB4(m0, &c->eye, &c->eye);
    }
    f32 g = b->m64;
    c->m14c = c->m14c * g;
    if (c->m14c < lbl_804CD29C) c->m14c = lbl_804CD29C;
    if (c->m14c > lbl_804CD2C4) c->m14c = lbl_804CD2C4;
    if (b->m72 & 0x20) {
        Vec v;
        fn_800A4D88(&v, b);
        c->at = v;
        c->at.y += fn_800A84A4(lbl_80365064 + 0xCF);
    }
    fn_8000F954(c, 0, 1);
    fn_8000FA98(c);
}
struct ES { u8 p[0x30]; u8 m30; };
struct BC { u8 p[0x30]; ES* m30; u8 p34[8]; Chr* e[2]; u8 p44[9]; u8 m4d; u8 m4e; u8 m4f; int m50; };
struct GS { u8 p[0x30]; BC* m30; };
void fn_800A9A74(BC*);
int fn_800BD280(Chr*);
void fn_800BA2C8(Chr*);
void* fn_8028C1A0(f32);
void fn_800BE340(Chr*);
void fn_800BE2BC(Chr*);
void fn_80010788(int, int, void*, void*);
void fn_800AA360(u8);
void fn_800AA400();
void fn_80176A34(int);
extern char lbl_803653B8[];
static inline Chr* At(BC* b, int i) { if (i < 0) return NULL; return b->e[i]; }
#pragma use_lmw_stmw on
static inline int Cnt(BC* b) {
    int n = 0;
    int i;
    for (i = 0; i < 2; i++) {
        if (fn_800BD280(At(b, i))) n++;
    }
    return n;
}

#pragma use_lmw_stmw off
void fn_800A8660();
#if TARGET_PC
FE10_PROTO void* fn_800A6490(p32arg);
FE10_PROTO void* fn_800AAD1C(p32arg);
FE10_PROTO void* fn_800AF104(p32arg);
FE10_PROTO void* fn_80081050(void*, p32arg);
#else
void* fn_800A6490(int);
void* fn_800AAD1C(int);
void* fn_800AF104(int);
void* fn_80081050(void*, int);
#endif
struct EA { u8 p[0x54]; s8 m54, m55; };
#if TARGET_PC
FE10_PROTO Chr* fn_800BEEA0(p32arg);
#else
Chr* fn_800BEEA0(int);
#endif
void fn_800A4B30(void*, int, Chr*);
void fn_800A95F4(void*);
int fn_8030585C(int, int, int, int, int);
void fn_80020E7C(int);
extern u8 lbl_803821B0[], lbl_803821C8[];
struct B9 { u8 p[0x30]; void* m30; void* m34; void* m38; EA* e[2]; void* m44; int m48; u8 m4c, m4d, m4e, m4f; int m50; };
struct PE { u8 p[0x30]; B9* m30; };
static inline EA* EAt(B9* b, int i) { if (i < 0) return NULL; return b->e[i]; }
void fn_800A947C(B9* b) {
    fn_800A8660();
    b->m44 = fn_800A6490(4);
    b->m30 = fn_800AAD1C(4);
    b->m34 = fn_800AF104(4);
    b->m38 = fn_800AF104(4);
    ((PE*)fn_80081050(lbl_803821B0, 3))->m30 = b;
    for (int i = 0; i < 2; i++) {
        b->e[i] = (EA*)fn_800BEEA0(3);
        EAt(b, i)->m54 = i;
        EAt(b, i)->m55 = i;
        fn_800A4B30(b->m44, i, (Chr*)EAt(b, i));
    }
    ((PE*)fn_80081050(lbl_803821C8, 3))->m30 = b;
    fn_800A95F4(b);
    b->m4c = 1;
    b->m4d = 1;
    b->m48 = 0;
    b->m4e = 1;
    b->m4f = 100;
    b->m50 = 0;
    int s0 = fn_8030585C(0x260, 0x1C0, 6, 0, 0);
    int s1 = fn_8030585C(0x260, 0x1C0, 0x28, 0, 0);
    fn_80020E7C(s0 + s1);
}
}
