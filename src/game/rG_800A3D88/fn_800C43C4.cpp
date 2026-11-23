#include "game/rG_800A3D88/types.h"

// Draws a textured quad at (x, y) with the size and colour mode set in the record.
extern "C" {
typedef f32 Mt[3][4];
struct Col { u8 r, g, b, a; };
struct Quad { int x, y, w, h; u8 p10[4]; Mt m14; void* m44; int m48; int m4c; u8 m50; };
void fn_80006A64(void*, void*, int);
void fn_80022254(void*, int);
void fn_80021784(int);
void fn_803128AC(Mt, f32, f32, f32);
void fn_80312378(const void*, const void*, void*);
void fn_80307E48(Mt, int);
void fn_80021C34(int);
void fn_80021F7C(int, int, int, int);
void fn_80021BF4(int);
void fn_80306DDC(int, Col);
void fn_80306FD8(int, int, int, int, int);
void fn_80021CB4(int, int, int, int);
void fn_80022158(int, int, int);
void fn_80021D18(int, int, int, int, int, int);
void fn_80021D9C(int, int, int, int, int, int);
void fn_80021E20(int, int, int, int, int);
void fn_80021E8C(int, int, int, int, int);
void fn_80304314(int, int, int);
#define FIFO_F (*(volatile f32*)0xCC008000)
#define FIFO_B (*(volatile u8*)0xCC008000)
static inline void Cp(Col* d, Col s) { *d = s; }
static const Col K1 = {0x55, 0x55, 0x55, 0xFF};
static const Col K2 = {0x55, 0x4F, 0x35, 0xFF};
void fn_800C43C4(Quad* q) {
    Mt m1, m0;
    u8 tex[0x20];
    Col c;
    int w, h;
    int x, y;
    f32 u0, u1;
    x = q->x;
    y = q->y;
    w = q->w;
    h = q->h;
    fn_80006A64(q->m44, tex, q->m48);
    fn_80022254(tex, 0);
    fn_80021784(0);
    fn_803128AC(m0, x, y, 0.0f);
    fn_80312378(q->m14, m0, m1);
    fn_80307E48(m1, 0);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021BF4(3);
    if (q->m4c == 1) Cp(&c, K1);
    else if (q->m4c == 2) Cp(&c, K2);
    fn_80306DDC(1, c);
    fn_80306FD8(1, 0, 0, 0, 3);
    fn_80306FD8(2, 1, 1, 1, 3);
    fn_80306FD8(3, 2, 2, 2, 3);
    fn_80021CB4(0, 0, 0, 255);
    fn_80022158(0, 0, 1);
    fn_80021D18(0, 0, 0, 0, 1, 0);
    fn_80021D9C(0, 0, 0, 0, 1, 0);
    fn_80021E20(0, 15, 2, 8, 15);
    fn_80021E8C(0, 7, 7, 7, 4);
    fn_80021CB4(1, 0, 0, 255);
    fn_80022158(1, 0, 2);
    fn_80021D18(1, 0, 0, 0, 1, 0);
    fn_80021D9C(1, 0, 0, 0, 1, 0);
    fn_80021E20(1, 15, 2, 8, 0);
    fn_80021E8C(1, 7, 7, 7, 4);
    fn_80021CB4(2, 0, 0, 255);
    fn_80022158(2, 0, 3);
    fn_80021D18(2, 0, 0, 0, 1, 0);
    fn_80021D9C(2, 0, 0, 0, 1, 0);
    fn_80021E20(2, 15, 2, 8, 0);
    fn_80021E8C(2, 7, 7, 7, 4);
    if (q->m50 != 0) {
        u0 = 1.0f;
        u1 = 0.0f;
    } else {
        u0 = 0.0f;
        u1 = 1.0f;
    }
    fn_80304314(0x80, 0, 4);
#define VTX(a, b, s, t) FIFO_F = a; FIFO_F = b; FIFO_F = 0.0f; FIFO_B = 0xFF; FIFO_B = 0xFF; FIFO_B = 0xFF; FIFO_B = 0xFF; FIFO_F = s; FIFO_F = t
    VTX(0.0f, 0.0f, u0, 0.0f);
    VTX((f32)w, 0.0f, u1, 0.0f);
    VTX((f32)w, (f32)h, u1, 1.0f);
    VTX(0.0f, (f32)h, u0, 1.0f);
    fn_80021BF4(1);
    fn_80022158(0, 0, 0);
    fn_80022158(1, 0, 0);
    fn_80022158(2, 0, 0);
}
}
