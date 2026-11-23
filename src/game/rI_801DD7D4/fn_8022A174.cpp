/* fn_8022A174 (0x484): layout of a text/help window for one of 8 screen anchors.
 * kind 0/5 = left edge (top/bottom), 1/4 = right edge, 2/7 and 3/6 = inset left/right (middle rows).
 * The width is rounded up to a multiple of 48, clamped to 0x150..0x240; `big` reserves 0x80 on the left.
 * Field names of Lay are guesses (window pos, columns, three anchor points). */
#include "game/rI_801DD7D4/types.h"
extern "C" {
struct Lay { s16 x, y, n, bx, by, cx, cy, dx, dy; };
#define TL(Y) r.x = 0x10; r.y = Y; r.n = w / 0x30; r.bx = 0xc0; r.by = Y + 0xc; r.cx = w - 0x40; r.cy = Y + 0x58; r.dx = 0x70; r.dy = Y + 0x6e; if (big) r.bx = 0x40;
#define TR(Y) r.x = 0x250 - w; r.y = Y; r.n = w / 0x30; r.bx = r.x + 0x30; r.by = Y + 0xc; r.cx = r.x + (w - 0xd0); r.cy = Y + 0x58; r.dx = r.x + (w - 0x60); r.dy = Y + 0x6e;
#define ML(Y) { int d = 0x50; if (w + 0x50 > 0x240) d = 0x240 - w; r.x = d + 0x10; r.y = Y; r.n = w / 0x30; r.bx = r.x + 0xb0; r.by = Y + 0xc; r.cx = w + r.x - 0x50; r.cy = Y + 0x58; r.dx = r.x + 0x60; r.dy = Y + 0x6e; if (big) r.bx = r.bx - 0x80; }
#define MR(Y) { int d = 0x50; if (w + 0x50 > 0x240) d = 0x240 - w; r.x = 0x250 - w - d; r.y = Y; r.n = w / 0x30; r.bx = r.x + 0x30; r.by = Y + 0xc; r.cx = r.x + (w - 0xd0); r.cy = Y + 0x58; r.dx = r.x + (w - 0x60); r.dy = Y + 0x6e; }
Lay fn_8022A174(int kind, int w, int big) {
    Lay r;
    if (big) w -= 0x80;
    w = (w + 0x2f) / 0x30 * 0x30;
    if (w > 0x240) w = 0x240;
    if (w < 0x150) w = 0x150;
    switch (kind) {
    case 0: TL(0x14) break;
    case 1: TR(0x13c) break;
    case 2: ML(0x98) break;
    case 3: MR(0xbc) break;
    case 4: TR(0x14) break;
    case 5: TL(0x13c) break;
    case 6: MR(0x98) break;
    case 7: ML(0xbc) break;
    }
    return r;
}
}
