#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct GMap { int w; int h; } GMap;
typedef union WGP { u8 u8; f32 f32; } WGP;
#define FIFO (*(volatile WGP*)0xCC008000)
extern "C" {
extern u8 lbl_803EC898[0x4000];
#define MP ((GMap*)lbl_803EC898)
extern u8 fn_80118130(GMap*, s8, s8);
extern u8 fn_801147E4(GMap*, s8, s8);
extern f32 fn_801146A8(GMap*, s8, s8, int);
extern f32 fn_80114728(GMap*, s8, s8);
extern void fn_80304314(int, int, int);
static inline void Pos3(f32 x, f32 y, f32 z) {
    FIFO.f32 = x;
    FIFO.f32 = y;
    FIFO.f32 = z;
}
static inline void Col4(u8 r, u8 g, u8 b, u8 a) {
    FIFO.u8 = r;
    FIFO.u8 = g;
    FIFO.u8 = b;
    FIFO.u8 = a;
}
void fn_800F22E8(int x, int y, GXColor c, int chk) {
    if (x >= 0 && y >= 0 && x < MP->w && y < MP->h) {
        if (chk) {
            switch (fn_80118130(MP, x, y)) {
            case 0x60: case 0x73: case 0x85: case 0xA8: case 0xC6:
                return;
            }
        }
        if (fn_801147E4(MP, x, y)) {
            fn_80304314(0x98, 0, 4);
            Pos3(x, y, fn_801146A8(MP, x, y, 0)); Col4(c.r, c.g, c.b, c.a);
            Pos3(x + 1, y, fn_801146A8(MP, x, y, 1)); Col4(c.r, c.g, c.b, c.a);
            Pos3(x, y + 1, fn_801146A8(MP, x, y, 2)); Col4(c.r, c.g, c.b, c.a);
            Pos3(x + 1, y + 1, fn_801146A8(MP, x, y, 3)); Col4(c.r, c.g, c.b, c.a);
        } else {
            fn_80304314(0xA0, 0, 6);
            Pos3(x + 0.5f, y + 0.5f, fn_80114728(MP, x, y)); Col4(c.r, c.g, c.b, c.a);
            Pos3(x, y, fn_801146A8(MP, x, y, 0)); Col4(c.r, c.g, c.b, c.a);
            Pos3(x + 1, y, fn_801146A8(MP, x, y, 1)); Col4(c.r, c.g, c.b, c.a);
            Pos3(x + 1, y + 1, fn_801146A8(MP, x, y, 3)); Col4(c.r, c.g, c.b, c.a);
            Pos3(x, y + 1, fn_801146A8(MP, x, y, 2)); Col4(c.r, c.g, c.b, c.a);
            Pos3(x, y, fn_801146A8(MP, x, y, 0)); Col4(c.r, c.g, c.b, c.a);
        }
    }
}
}
