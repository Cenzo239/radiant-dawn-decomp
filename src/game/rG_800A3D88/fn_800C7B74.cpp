#include "game/rG_800A3D88/types.h"

// Full-screen colour fade, drawn as one quad.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct Mtx44 { f32 m[4][4]; };
struct RGBA { u8 r, g, b, a; };
struct Fd { u8 p[0x30]; u8 m30; u8 p31; u16 m32; u16 m34; u16 m36; f32 m38; f32 m3c; RGBA m40; u8 p44[4]; u8* m48; u8 tex[1]; };
extern u32 lbl_804CB700;
void fn_80312F48(Mtx44*, f32, f32, f32, f32, f32, f32);
void fn_80307D98(Mtx44*, int);
void fn_803128AC(Mtx34*, f32, f32, f32);
void fn_80307E48(Mtx34*, int);
void fn_80021784(int);
void fn_80308090(f32, f32, f32, f32, f32, f32);
void fn_8002230C();
void fn_80021958(int, RGBA);
void fn_803031CC();
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021BF4(int);
void fn_80021EF8(int, int);
void fn_80021CB4(int, int, int, int);
void fn_80021C34(int);
void fn_80021F7C(int, int, int, int);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_80021BA4(int, int, int, int);
void fn_80021860(int, int, int);
void fn_80304314(int, int, int);
#define FIFO_S (*(volatile s16*)0xCC008000)
static inline void GX3(s16 x, s16 y, s16 z) {
    FIFO_S = x;
    FIFO_S = y;
    FIFO_S = z;
}
void fn_80021E20(int, int, int, int, int);
void fn_80021D18(int, int, int, int, int, int);
void fn_80021E8C(int, int, int, int, int);
void fn_80021D9C(int, int, int, int, int, int);
void fn_80022254(void*, int);
void fn_80303CB4();
void fn_80081A90(void*);
void fn_80079978(void*);
f32 fn_8001EBC8(f32, f32, f32, f32, int);
#define FIFO_B (*(volatile u8*)0xCC008000)
static inline void GXT(s16 x, s16 y, s16 z, u8 a, s16 u, s16 w) {
    FIFO_S = x;
    FIFO_S = y;
    FIFO_S = z;
    FIFO_B = 0xFF;
    FIFO_B = 0xFF;
    FIFO_B = 0xFF;
    FIFO_B = a;
    FIFO_S = u;
    FIFO_S = w;
}
static inline void GX2(s16 x, s16 y, s16 u, s16 w) {
    FIFO_S = x;
    FIFO_S = y;
    FIFO_S = 0;
    FIFO_S = u;
    FIFO_S = w;
}
void fn_800C7B74(Fd* p) {
    Mtx34 v;
    Mtx44 pr;
    if (p->m34 >= p->m36 || (lbl_804CB700 & 0x8001)) {
        p->m32 = (p->m32 & 0xFFFE) | 2;
        p->m40.a = (int)(255.99f * p->m3c);
        if (p->m48 != NULL) {
            fn_80079978(p->m48);
            p->m48 = NULL;
        }
    }
    if (p->m32 & 1) {
        p->m34++;
        p->m40.a = (int)(255.99f * fn_8001EBC8(p->m38, p->m3c, 1.0f, (f32)p->m34 / (f32)p->m36, 2));
    }
    if (p->m40.a == 0) return;
    fn_80312F48(&pr, 0.0f, 448.0f, 0.0f, 608.0f, 0.0f, -1000.0f);
    fn_80307D98(&pr, 1);
    fn_803128AC(&v, 0.0f, 0.0f, 10.0f);
    fn_80307E48(&v, 0);
    fn_80021784(0);
    fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, 0.0f, 0.01f);
    fn_8002230C();
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80303200(0, 9, 1, 3, 0);
    if (p->m30 == 7) {
        fn_80302B80(0xD, 1);
        fn_80303200(0, 0xD, 1, 3, 0);
        fn_80021E20(0, 0xF, 10, 8, 0xF);
        fn_80021D18(0, 0, 0, 0, 1, 0);
        fn_80021E8C(0, 7, 7, 7, 5);
        fn_80021D9C(0, 0, 0, 0, 1, 0);
        fn_80021BF4(1);
        fn_80021CB4(0, 0, 0, 4);
        fn_80022254(p->tex, 0);
        fn_80021C34(1);
        fn_80021F7C(0, 1, 4, 0x3C);
    } else {
        fn_80021BF4(1);
        fn_80021EF8(0, 4);
        fn_80021CB4(0, 0xFF, 0xFF, 4);
        fn_80021C34(1);
        fn_80021F7C(0, 1, 0, 0x3C);
    }
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    fn_80021958(4, p->m40);
    fn_80021BA4(1, 4, 5, 0);
    fn_80021860(1, 3, 0);
    if (p->m30 != 7) {
        fn_80304314(0x98, 0, 4);
        GX3(0, 0, 0);
        GX3(0x260, 0, 0);
        GX3(0, 0x1C0, 0);
        GX3(0x260, 0x1C0, 0);
    } else {
        fn_80304314(0x98, 0, 4);
        GX2(0, 0, 0, 0);
        GX2(0x260, 0, 1, 0);
        GX2(0, 0x1C0, 0, 1);
        GX2(0x260, 0x1C0, 1, 1);
    }
}
}
