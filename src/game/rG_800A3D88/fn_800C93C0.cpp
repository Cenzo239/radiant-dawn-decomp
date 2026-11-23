#include "game/rG_800A3D88/types.h"

// Full-screen colour fade, drawn as one quad.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct Mtx44 { f32 m[4][4]; };
struct RGBA { u8 r, g, b, a; };
struct Tx { u8 p[0x30]; u8 m30; u8 p31[3]; u16 m34; u8 p36[0x4C - 0x36]; u8 tex[1]; };
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
void fn_800C93C0(Tx* p) {
    Mtx34 v;
    Mtx44 pr;
    u8 al;
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
    fn_80302B80(0xB, 1);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 0xD, 1, 3, 0);
    fn_80021E20(0, 0xF, 10, 8, 0xF);
    fn_80021D18(0, 0, 0, 0, 1, 0);
    fn_80021E8C(0, 7, 7, 7, 5);
    fn_80021D9C(0, 0, 0, 0, 1, 0);
    fn_80021CB4(0, 0, 0, 4);
    fn_80022254(p->tex, 0);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021BF4(1);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021BA4(1, 4, 5, 0);
    fn_80021860(1, 3, 0);
    al = p->m34;
    fn_80304314(0x98, 0, 4);
    GXT(0, 0, 0x3DD, al, 0, 0);
    GXT(0x260, 0, 0x3DD, al, 1, 0);
    GXT(0, 0x1C0, 0x3DD, al, 0, 1);
    GXT(0x260, 0x1C0, 0x3DD, al, 1, 1);
    if (p->m30 == 0x7B) {
        fn_80303CB4();
        fn_80081A90(p);
    }
}
}
