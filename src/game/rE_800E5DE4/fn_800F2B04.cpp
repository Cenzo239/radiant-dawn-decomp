#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct GMap { int w; int h; } GMap;
typedef union WGP { u8 u8; f32 f32; } WGP;
#define FIFO (*(volatile WGP*)0xCC008000)
extern "C" {
extern u8 lbl_803EC898[0x4000];
#define MP ((GMap*)lbl_803EC898)
extern u8 fn_80118098(GMap*, s8, s8);
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
void fn_800F2B04(int x, int y, int r, GXColor c, int chk) {
    if (x >= 0 && y >= 0 && x < MP->w && y < MP->h) {
        if (chk) {
            switch (fn_80118098(MP, x, y)) {
            case 0x60: case 0x73: case 0x85: case 0xA8: case 0xC6:
                return;
            }
        }
        {
        f32 dx[4] = {0.0f, 1.0f, 1.0f, 0.0f};
        f32 dy[4] = {0.0f, 0.0f, 1.0f, 1.0f};
        f32 h[4];
        int rem;
        int n;
        h[0] = fn_801146A8(MP, x, y, 0);
        h[1] = fn_801146A8(MP, x, y, 1);
        h[2] = fn_801146A8(MP, x, y, 3);
        h[3] = fn_801146A8(MP, x, y, 2);
        rem = r % 50;
        n = (r - 1) / 50;
        fn_80304314(0xA0, 0, (u16)(n + 3));
        Pos3(x + 0.5f, y + 0.5f, (h[0] + h[1] + h[2] + h[3]) * 0.25f);
        Col4(c.r, c.g, c.b, c.a);
        for (int i = 0; i < n + 1; i++) {
            int j = i & 3;
            Pos3(x + dx[j], y + dy[j], h[j]);
            Col4(c.r, c.g, c.b, c.a);
        }
        if (rem == 0) {
            int j = (r / 50) & 3;
            Pos3(x + dx[j], y + dy[j], h[j]);
            Col4(c.r, c.g, c.b, c.a);
        } else {
            int a = r / 50;
            int j = a & 3;
            int k = (a + 1) & 3;
            f32 px = ((50 - rem) * dx[j] + rem * dx[k]) / 50.0f;
            f32 py = ((50 - rem) * dy[j] + rem * dy[k]) / 50.0f;
            f32 pz = ((50 - rem) * h[j] + rem * h[k]) / 50.0f;
            Pos3(x + px, y + py, pz);
            Col4(c.r, c.g, c.b, c.a);
        }
        }
    }
}
}
