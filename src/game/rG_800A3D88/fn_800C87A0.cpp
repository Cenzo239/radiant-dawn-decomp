#include "game/rG_800A3D88/types.h"

// Full-screen colour fade, drawn as one quad.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct Mtx44 { f32 m[4][4]; };
struct RGBA { u8 r, g, b, a; };
struct Wipe { u8 p[0x32]; u16 st; u16 t; u16 n; };
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
#define FIFO_B (*(volatile u8*)0xCC008000)
static inline void V(s16 x, s16 y, u8 a) {
    FIFO_S = x;
    FIFO_S = y;
    FIFO_S = 0;
    FIFO_B = 0;
    FIFO_B = 0;
    FIFO_B = 0;
    FIFO_B = a;
}
static inline void V2(s16 x, s16 y, u8 a) {
    FIFO_S = x;
    FIFO_S = y;
    FIFO_S = 0;
    FIFO_B = 0;
    FIFO_B = 0;
    FIFO_B = 0;
    FIFO_B = a;
}
void fn_800C87A0(Wipe* p) {
    Mtx34 v;
    Mtx44 pr;
    int dir;
    f32 x;
    f32 x2;
    u8 a0, a1;
    if (lbl_804CB700 & 0x8001) {
        switch (p->st) {
        case 0:
        case 2:
            return;
        case 1:
            p->st = 2;
            return;
        case 3:
            p->st = 0;
            return;
        }
    }
    switch (p->st) {
    case 0:
        return;
    case 1:
        p->t++;
        x = fn_8017F68C(0, 608.0f, -250.0f, p->t, p->n);
        dir = 0;
        if (p->t >= p->n) p->st = 2;
        break;
    case 2:
        x = -250.0f;
        dir = 0;
        break;
    case 3:
        p->t++;
        x = fn_8017F68C(0, 0.0f, -858.0f, p->t, p->n);
        dir = 1;
        if (p->t >= p->n) p->st = 0;
        break;
    }
    fn_80312F48(&pr, 0.0f, 448.0f, 0.0f, 608.0f, 0.0f, -1000.0f);
    fn_80307D98(&pr, 1);
    fn_803128AC(&v, 0.0f, 0.0f, 10.0f);
    fn_80307E48(&v, 0);
    fn_80021784(0);
    fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, 0.0f, 0.01f);
    fn_8002230C();
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 3, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021C34(0);
    fn_80021EF8(0, 4);
    fn_80021CB4(0, 0xFF, 0xFF, 4);
    fn_80021BF4(1);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021BA4(1, 4, 5, 0);
    fn_80021860(1, 3, 0);
    if (dir == 0) {
        a0 = 0;
        a1 = 0xFF;
        x2 = 250.0f + x;
    } else if (dir == 1) {
        x2 = x;
        a0 = 0xFF;
        a1 = 0;
        x = 608.0f + x;
    } else {
        return;
    }
    fn_80304314(0x98, 0, 4);
    V((int)x, 0, a0);
    V((int)(250.0f + x), 0, a1);
    V((int)x, 0x1C0, a0);
    V((int)(250.0f + x), 0x1C0, a1);
    fn_80304314(0x98, 0, 4);
    V2((int)x2, 0, 0xFF);
    V2((int)(608.0f + x2), 0, 0xFF);
    V2((int)x2, 0x1C0, 0xFF);
    V2((int)(608.0f + x2), 0x1C0, 0xFF);
}
}
