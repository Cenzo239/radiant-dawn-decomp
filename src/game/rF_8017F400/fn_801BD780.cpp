#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
extern void fn_801BD170(int, int, int, int, f32, f32, f32);
extern void fn_801BD2EC(int, int, int, int, f32, f32, f32, f32);
#define A fn_801BD170
#define B fn_801BD2EC
void fn_801BD780(int p, f32 x, f32 y, f32 w, f32 h, f32 t) {
/*P*/
    f32 y1;
    f32 ww;
    f32 y1b;
    f32 hhb;
    f32 a2;
    f32 b2;
    f32 w2;
    f32 hh;
    f32 y2;
    f32 a3;
    f32 a;
    f32 b3;
    f32 b;
/*E*/
    if (w < 64.0f) w = 64.0f;
    if (h < 80.0f) h = 80.0f;
    if (t < 48.0f) t = 48.0f;
    if (t > w - 48.0f) t = w - 48.0f;
    if (w < 96.0f) t = -1.0f;
    if (-1.0f == t) {
        w2 = w - 64.0f;
        A(1, p, 2, 0, x, y, 1.0f);
        B(1, p, 5, 8, 32.0f + x, y, w2, 8.0f);
        B(1, p, 1, 0, 32.0f + x, 8.0f + y, w2, 32.0f);
        A(1, p, 2, 1, 32.0f + x + w2, y, 1.0f);
        {
        y1 = 40.0f + y;
        ww = w - 16.0f;
        hh = h - 80.0f;
        B(1, p, 5, 0, x, y1, 8.0f, hh);
        B(1, p, 1, 0, 8.0f + x, y1, ww, hh);
        B(1, p, 5, 0, 8.0f + x + ww, y1, 8.0f, hh);
        y = 40.0f + y + hh;
        w = w - 64.0f;
        A(1, p, 2, 2, x, y, 1.0f);
        B(1, p, 1, 0, 32.0f + x, y, w, 32.0f);
        B(1, p, 5, 8, 32.0f + x, 32.0f + y, w, 8.0f);
        A(1, p, 2, 3, 32.0f + x + w, y, 1.0f);
        }
    } else {
        a = t - 48.0f;
        b = w - t - 48.0f;
        A(1, p, 2, 0, x, y, 1.0f);
        B(1, p, 5, 8, 32.0f + x, y, a, 8.0f);
        B(1, p, 1, 0, 32.0f + x, 8.0f + y, a, 32.0f);
        A(1, p, 3, 0, 32.0f + x + a, y, 1.0f);
        B(1, p, 1, 0, 32.0f + x + a, 24.0f + y, 14.0f, 16.0f);
        B(1, p, 6, 0, 14.0f + (32.0f + x + a), 24.0f + y, 8.0f, 16.0f);
        B(1, p, 1, 0, 22.0f + (32.0f + x + a), 24.0f + y, 10.0f, 16.0f);
        B(1, p, 5, 8, 32.0f + (32.0f + x + a), y, b, 8.0f);
        B(1, p, 1, 0, 32.0f + (32.0f + x + a), 8.0f + y, b, 32.0f);
        A(1, p, 2, 1, b + (32.0f + (32.0f + x + a)), y, 1.0f);
        {
        y1b = 40.0f + y;
        hhb = h - 80.0f;
        a2 = t - 8.0f - 2.0f;
        b2 = w - t - 8.0f - 6.0f;
        B(1, p, 5, 0, x, y1b, 8.0f, hhb);
        B(1, p, 1, 0, 8.0f + x, y1b, a2, hhb);
        B(1, p, 6, 0, 8.0f + x + a2, y1b, 8.0f, hhb);
        B(1, p, 1, 0, 8.0f + (8.0f + x + a2), y1b, b2, hhb);
        B(1, p, 5, 0, b2 + (8.0f + (8.0f + x + a2)), y1b, 8.0f, hhb);
        {
        y2 = 40.0f + y + hhb;
        a3 = t - 48.0f;
        b3 = w - t - 48.0f;
        A(1, p, 2, 2, x, y2, 1.0f);
        B(1, p, 1, 0, 32.0f + x, y2, a3, 32.0f);
        B(1, p, 5, 8, 32.0f + x, 32.0f + y2, a3, 8.0f);
        B(1, p, 1, 0, 32.0f + x + a3, y2, 14.0f, 16.0f);
        B(1, p, 6, 0, 14.0f + (32.0f + x + a3), y2, 8.0f, 16.0f);
        B(1, p, 1, 0, 22.0f + (32.0f + x + a3), y2, 10.0f, 16.0f);
        A(1, p, 4, 0, 32.0f + x + a3, 16.0f + y2, 1.0f);
        B(1, p, 1, 0, 32.0f + (32.0f + x + a3), y2, b3, 32.0f);
        B(1, p, 5, 8, 32.0f + (32.0f + x + a3), 32.0f + y2, b3, 8.0f);
        A(1, p, 2, 3, b3 + (32.0f + (32.0f + x + a3)), y2, 1.0f);
        }
        }
    }
}
}
