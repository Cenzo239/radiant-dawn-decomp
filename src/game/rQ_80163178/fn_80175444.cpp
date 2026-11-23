#include "game/rQ_80163178/base.h"
#pragma use_lmw_stmw on
struct GXC { u8 r, g, b, a; };
struct Mx { f32 m[3][4]; };
struct Mx4 { f32 m[4][4]; };
struct TO { u32 d[8]; };
struct TL { u32 d[3]; };
struct Mv { u8 pad[0x30]; void* res; u32 cur; u32 next; u8 pad3C[8]; u32 total; u32 left; };
extern "C" {
void fn_8002230C(void);
void fn_80308090(f32, f32, f32, f32, f32, f32);
void fn_80304C74(GXC, u32);
void fn_80307298(int, f32, f32, f32, f32, GXC);
void fn_80021FEC(int);
void fn_80021FE8(int);
void fn_80021860(int, int, int);
void fn_800217CC(int);
void fn_80021808(int, int, int, int, int);
void fn_80312F48(Mx4*, f32, f32, f32, f32, f32, f32);
void fn_80307D98(Mx4*, int);
void fn_80021B68(int);
void fn_803031CC(void);
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_800218A8(int, GXC);
void fn_80021958(int, GXC);
void fn_80021BF4(int);
void fn_80021CB4(int, int, int, int);
void fn_80021EF8(int, int);
void fn_8030708C(int, int, int);
void fn_80021C34(int);
void fn_80021F7C(int, int, int, int);
void fn_80021C74(int);
void fn_80306B24(int);
void fn_80312318(Mx*);
void fn_80307E48(Mx*, int);
void fn_80307E98(Mx*, int);
void fn_80021784(int);
void fn_80021BA4(int, int, int, int);
void fn_80006B84(void*, TO*, TL*, int, u32);
void fn_80022254(TO*, int);
void fn_80306054(TL*, int);
void fn_80304314(int, int, int);
}
static const GXC kA = {255, 255, 255, 0};
static const GXC kC0 = {255,255,255,255};
static const GXC kC1 = {255,255,255,255};
static const GXC kC2 = {255,255,255,255};
static const GXC kC3 = {255,255,255,255};
static inline void SetA(int a) {
    GXC c = kA;
    c.a = a;
    fn_80021958(4, c);
}
static inline void A1(int i, GXC c) {
    fn_800218A8(i, c);
}
static inline void A2(int i, GXC c) {
    fn_80021958(i, c);
}
static inline void Clr(int z) {
    GXC c;
    *(int*)&c = z;
    fn_80304C74(c, 0xFFFFFF);
}
static inline void Fog(int z) {
    GXC c;
    *(int*)&c = z;
    fn_80307298(0, 0.0f, 0.0f, 0.0f, 0.0f, c);
}
#define FIFO (*(volatile s16*)0xCC008000)
static inline void CaseA(Mv* s) {
    TL tl2;
    TL tl;
    TO to2;
    TO to;
    Mx mv;
    Mx4 pr;
    int z;
        fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
        z = 0;
         Clr(z);
         Fog(z);
        fn_80021FEC(1);
        fn_80021FE8(1);
        fn_80021860(1, 3, 1);
        fn_800217CC(1);
        fn_80021808(7, 0, 1, 7, 0);
        fn_80312F48(&pr, 0.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        fn_80307D98(&pr, 1);
        fn_80021B68(0);
        fn_803031CC();
        fn_80302B80(9, 1);
        fn_80302B80(0xd, 1);
        fn_80303200(0, 9, 1, 3, 0);
        fn_80303200(0, 0xd, 1, 3, 0);
        fn_80021B2C(1);
        fn_80021A08(4, 0, 0, 0, 0, 0, 2);
        fn_80021A08(5, 0, 0, 0, 0, 0, 2);
        A1(4, kC0);
        A1(5, kC1);
        A2(4, kC2);
        A2(5, kC3);
        fn_80021BF4(1);
        fn_80021CB4(0, 0, 0, 0xff);
        fn_80021EF8(0, 3);
        fn_80021808(7, 0, 0, 7, 0);
        fn_8030708C(0, 0x11, 0);
        fn_80021C34(1);
        fn_80021F7C(0, 1, 4, 0x3c);
        fn_80021C74(0);
        fn_80306B24(0);
        fn_80312318(&mv);
        fn_80307E48(&mv, 0);
        fn_80307E98(&mv, 0);
        fn_80021784(0);
        fn_80021BA4(1, 4, 5, 0);
        fn_80006B84(s->res, &to, &tl, 0, s->cur);
        fn_80022254(&to, 0);
        fn_80306054(&tl, 0);
        fn_80304314(0x80, 0, 4);
        FIFO = z; FIFO = z; FIFO = -100; FIFO = z; FIFO = z;
        FIFO = 0x260; FIFO = z; FIFO = -100; FIFO = 1; FIFO = z;
        FIFO = 0x260; FIFO = 0x1c0; FIFO = -100; FIFO = 1; FIFO = 1;
        FIFO = z; FIFO = 0x1c0; FIFO = -100; FIFO = z; FIFO = 1;
        if (s->next != s->cur) {
            int a;
            s->left--;
            a = 255.9f * ((f32)(s->total - s->left) / (f32)s->total);
            if (s->left == 0) {
                s->cur = s->next;
            }
                    SetA(a);
            fn_80021BF4(1);
            fn_80021CB4(0, 0, 0, 4);
            fn_80021EF8(0, 0);
            fn_80006B84(s->res, &to2, &tl2, 0, s->next);
            fn_80022254(&to2, 0);
            fn_80306054(&tl2, 0);
            fn_80304314(0x80, 0, 4);
            FIFO = 0; FIFO = 0; FIFO = -90; FIFO = 0; FIFO = 0;
            FIFO = 0x260; FIFO = 0; FIFO = -90; FIFO = 1; FIFO = 0;
            FIFO = 0x260; FIFO = 0x1c0; FIFO = -90; FIFO = 1; FIFO = 1;
            FIFO = 0; FIFO = 0x1c0; FIFO = -90; FIFO = 0; FIFO = 1;
        }
        }
extern "C" void fn_80175444(Mv* s) {
    Mx4 pr2;
    Mx mv2;
    TO to3;
    TL tl3;
    GXC d0;
    GXC d1;
    int z;
    fn_8002230C();
    switch (s->cur) {
    case 0:
    case 1:
        CaseA(s);
        break;
    case 2: {
        fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
        z = 0;
        *(int*)&d0 = z;
        fn_80304C74(d0, 0xFFFFFF);
        *(int*)&d1 = z;
        fn_80307298(0, 0.0f, 0.0f, 0.0f, 0.0f, d1);
        fn_80021FEC(1);
        fn_80021FE8(1);
        fn_80021860(1, 3, 1);
        fn_800217CC(1);
        fn_80021808(7, 0, 1, 7, 0);
        fn_80312F48(&pr2, 0.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        fn_80307D98(&pr2, 1);
        fn_80021B68(0);
        fn_803031CC();
        fn_80302B80(9, 1);
        fn_80302B80(0xd, 1);
        fn_80303200(0, 9, 1, 3, 0);
        fn_80303200(0, 0xd, 1, 3, 0);
        fn_80021B2C(1);
        fn_80021A08(4, 0, 0, 0, 0, 0, 2);
        fn_80021A08(5, 0, 0, 0, 0, 0, 2);
        fn_80021BF4(1);
        fn_80021CB4(0, 0, 0, 0xff);
        fn_80021EF8(0, 3);
        fn_80021808(7, 0, 0, 7, 0);
        fn_8030708C(0, 0x11, 0);
        fn_80021C34(1);
        fn_80021F7C(0, 1, 4, 0x3c);
        fn_80021C74(0);
        fn_80306B24(0);
        fn_80312318(&mv2);
        fn_80307E48(&mv2, 0);
        fn_80307E98(&mv2, 0);
        fn_80021784(0);
        fn_80021BA4(1, 4, 5, 0);
        fn_80006B84(s->res, &to3, &tl3, 0, s->cur);
        fn_80022254(&to3, 0);
        fn_80306054(&tl3, 0);
        fn_80304314(0x80, 0, 4);
        FIFO = z; FIFO = z; FIFO = -100; FIFO = z; FIFO = z;
        FIFO = 0x260; FIFO = z; FIFO = -100; FIFO = 1; FIFO = z;
        FIFO = 0x260; FIFO = 0x1c0; FIFO = -100; FIFO = 1; FIFO = 1;
        FIFO = z; FIFO = 0x1c0; FIFO = -100; FIFO = z; FIFO = 1;
        break;
    }
    }
}
