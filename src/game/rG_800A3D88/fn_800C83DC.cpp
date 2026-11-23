#include "game/rG_800A3D88/types.h"

// Full-screen colour fade, drawn as one quad.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct Mtx44 { f32 m[4][4]; };
struct RGBA { u8 r, g, b, a; };
struct Blink { u8 p[0x32]; u16 m32; RGBA m34; u16 t1, n1, t2, n2; };
extern u32 lbl_804CB700;
f32 fn_8017F68C(int, f32, f32, f32, f32);
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
void fn_800C83DC(Blink* p) {
    Mtx34 v;
    Mtx44 pr;
    if (lbl_804CB700 & 0x8001) {
        p->m34.a = 0;
        p->m32 = 0;
        return;
    }
    switch (p->m32) {
    case 0:
        p->m34.a = 0;
        break;
    case 1:
        p->t1++;
        p->m34.a = (int)fn_8017F68C(0, 0.0f, 255.0f, p->t1, p->n1);
        if (p->t1 >= p->n1) p->m32 = 2;
        break;
    case 2:
        p->t2++;
        p->m34.a = (int)fn_8017F68C(0, 255.0f, 0.0f, p->t2, p->n2);
        if (p->t2 >= p->n2) p->m32 = 0;
        break;
    }
    if (p->m34.a == 0) return;
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
    fn_80021C34(0);
    fn_80021EF8(0, 4);
    fn_80021CB4(0, 0xFF, 0xFF, 4);
    fn_80021BF4(1);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    fn_80021958(4, p->m34);
    fn_80021BA4(1, 4, 5, 0);
    fn_80021860(1, 3, 0);
    fn_80304314(0x98, 0, 4);
    GX3(0, 0, 0);
    GX3(0x260, 0, 0);
    GX3(0, 0x1C0, 0);
    GX3(0x260, 0x1C0, 0);
}
}
