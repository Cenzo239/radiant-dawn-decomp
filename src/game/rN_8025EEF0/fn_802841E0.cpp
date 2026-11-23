/* Unit record screen: frame draw and page switch */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

f32 fn_8017F68C(f32 a, f32 b, f32 t, f32 d, int mode);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080940(C4* a, C4* b, C4* c, C4* d);
void fn_800804D4(int r, int g, int b, int a);
void fn_8007E7B4(void);
void fn_802845C8(void* p);
void fn_8028530C(void* p);

static C4 kc = {0, 0, 0, 0xFF};

struct Rec {
    u8 pad[0x30];
    u8 m30;
    u8 pad31;
    u16 m32;
    u8 pad34[4];
    void* tex;
    u8 pad3C[8];
    int m44;
    u8 pad48[2];
    u8 m4A;
    s8 m4B;
    u8 pad4C[2];
    u8 m4E;
    u8 pad4F;
    u16 m50;
};

static inline void step(Rec* o) {
    switch (o->m30) {
    case 1:
        if (o->m4A > o->m4E) {
            o->m4E++;
        } else {
            o->m4E = 0;
            o->m44 -= o->m4B;
        }
        break;
    case 3:
        if (o->m32 < 0x28F) {
            o->m44 = (int)fn_8017F68C((f32)o->m44, 0.0f, 1.0f, 90.0f, 6);
        } else {
            o->m44 = (int)fn_8017F68C((f32)o->m44, -60.0f, 1.0f, 90.0f, 6);
        }
        break;
    }
}

void fn_802841E0(Rec* o) {
    C4 a1; C4 b1; C4 c1; C4 d1;
    C4 a2; C4 b2; C4 c2; C4 d2;
    C4 c = kc;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E174(0, 2);
    fn_8007E164();
    fn_800800D4(3);
    fn_80080388(0.0f, 0.0f, 608.0f, 24.0f);
    *(u32*)&d1 = *(u32*)&c; *(u32*)&c1 = *(u32*)&c; *(u32*)&b1 = *(u32*)&c; *(u32*)&a1 = *(u32*)&c;
    fn_80080940(&a1, &b1, &c1, &d1);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(3);
    fn_80080388(0.0f, 424.0f, 608.0f, 24.0f);
    *(u32*)&d2 = *(u32*)&c; *(u32*)&c2 = *(u32*)&c; *(u32*)&b2 = *(u32*)&c; *(u32*)&a2 = *(u32*)&c;
    fn_80080940(&a2, &b2, &c2, &d2);
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 950.0f, 1.0f);
    fn_8007E164();
    {
        void* tex = o->tex;
        u8 a = o->m50;
        fn_8007E154();
        fn_8007E374(tex, 0, 1);
        fn_8007E7DC(0xFF);
        fn_8007E164();
        fn_800800D4(1);
        fn_800804D4(a, a, a, 0xFF);
        fn_80080430(0.0f, 24.0f, 0.0f, 0.0f, 608.0f, 400.0f);
        fn_80080578(0);
        fn_80080308();
    }
    switch (o->m30) {
    case 1:
        step(o);
        fn_802845C8(o);
        break;
    case 0:
    case 2:
        fn_802845C8(o);
        break;
    case 3:
        step(o);
        fn_8028530C(o);
        break;
    case 4:
    case 5:
        fn_8028530C(o);
        break;
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}

}
