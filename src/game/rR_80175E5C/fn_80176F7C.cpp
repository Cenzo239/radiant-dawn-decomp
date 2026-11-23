/* Signed number printing. */
#include "game/rR_80175E5C/types.h"
extern "C" {
f32 fn_8007E048();
int fn_800CA3DC(const char*, int, f32);
void fn_80080330(f32, f32);
void fn_80080C24(const char*);

void fn_80176F7C(int x, int y, int align, int sign, int v) {
    char b[0x20];
    int p = 0;
    int n = 0;
    if (sign != 0) {
        if (v < 0) {
            b[0] = '-';
            v -= v * 2;
        } else {
            b[0] = '+';
        }
        p = 1;
    } else if (v < 0) {
        b[0] = '-';
        b[1] = '-';
        b[2] = 0;
        goto draw;
    }
    {
        char* q = b + p;
        do {
            n++;
            *q++ = v % 10 + '0';
            v /= 10;
        } while (v != 0);
    }
    for (int i = 0; i < n >> 1; i++) {
        char t = b[p + i];
        b[p + i] = b[p + n - 1 - i];
        b[p + n - 1 - i] = t;
    }
    b[p + n] = 0;
draw:
    int w = fn_800CA3DC(b, -1, fn_8007E048());
    switch (align) {
    case 0:
        x -= w;
        break;
    case 2:
        x -= w / 2;
        break;
    case 1:
        break;
    }
    fn_80080330(x, y);
    fn_80080C24(b);
}

int fn_801D09F0();

void fn_80176B54(int x, int y, int align, const Color* col, int u, int v, int w, int h, int adv, int n) {
    f32 fx = x;
    f32 fy = y;
    f32 fw = w;
    f32 fa = adv;
    if (fn_801D09F0() != 0) {
        fw *= 0.7638191f;
        fa *= 0.7638191f;
    }
    int digits = 1;
    for (int k = n / 10; k > 0; k /= 10) digits++;
    f32 off;
    switch (align) {
    case 0:
        off = -fa;
        break;
    case 1:
        off = fa * digits;
        break;
    case 2:
        off = fa * digits / 2.0f - fa;
        break;
    }
    if (n == 0) {
        fn_800800D4(1);
        fn_80080388(fx + off, fy, fw, h);
        fn_800803C8(u, v, w, h);
        fn_80080578(0);
        fn_80080508(*col);
        fn_80080308();
    } else {
        while (n != 0) {
            fn_800800D4(1);
            fn_80080388(fx + off, fy, fw, h);
            fn_800803C8(u + w * (n % 10), v, w, h);
            fn_80080578(0);
            fn_80080508(*col);
            fn_80080308();
            off -= fa;
            n /= 10;
        }
    }
}
}
