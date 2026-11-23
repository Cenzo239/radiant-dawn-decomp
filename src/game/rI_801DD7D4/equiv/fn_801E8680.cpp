/* fn_801E8680: d-pad navigation of a scrolling item grid (wraps on a fresh press, scrolls a row
   at a time and starts the row-scroll animation), then updates the scroll bar.
   The same body, for a class whose grid fields sit 4 bytes later, is fn_80224554 (see equiv/fn_80224554.cpp). */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_80253EE4(const char*, f32);
void fn_801E1CC0(void*, int);
extern char lbl_8036EEE0[];
}
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual int v3C(); virtual void v40(); virtual void v44(); virtual int v48(); };
extern "C" Pad* lbl_804CB5B8;
class Grid { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual int v4C();
    u8 p4[0x48]; void* bar; u8 p50[2]; s16 cur; u8 p54[6]; s16 top; s16 cols; s16 rowH; f32 scroll; u8 p64[0xc]; int n; };
#define SND fn_80253EE4(lbl_8036EEE0 + 0xa, 0.0f)
#define BODY(T, FN) \
extern "C" void FN(T* o) { \
    int vis = o->v4C(); \
    s16 cols = o->cols; \
    int m1 = cols - 1; \
    s16 n = o->n; \
    s16 rows = (n + m1) / cols; \
    s16 row; \
    s16 col; \
    if ((s16)vis > rows) vis = rows; \
    { \
        int q = o->cur / cols; \
        row = q; \
        col = o->cur - q * cols; \
    } \
    if (!inputBlocked()) { \
        int held = lbl_804CB5B8->v3C(); \
        int trig = lbl_804CB5B8->v48(); \
        s16 old = ((const T*)o)->cur; \
        if (cols > 1) { \
            int rem = n - row * cols; \
            if (rem > cols) rem = cols; \
            if (held & 0x100001) { \
                if (col > 0) { \
                    o->cur--; \
                } else if (held == trig) { \
                    o->cur = rem + o->cur - 1; \
                } \
            } else if (held & 0x200002) { \
                rem--; \
                if (col < rem) { \
                    o->cur++; \
                } else if (held == trig) { \
                    o->cur -= rem; \
                } \
            } \
        } \
        if ((s16)(int)o->scroll == 0) { \
            if (held & 0x800008) { \
                if (row == 0) { \
                    if (held == trig) { \
                        int d; \
                        o->cur += (rows - 1) * cols; \
                        d = rows - (s16)vis; \
                        o->top = d > 0 ? d : 0; \
                        if (o->cur > n - 1) o->cur = n - 1; \
                    } \
                } else { \
                    s16 c = o->cur -= cols; \
                    if (c > m1) { \
                        s16 r = c / cols; \
                        if (r - o->top == 0) { \
                            o->top--; \
                            o->scroll = -o->rowH; \
                        } \
                    } \
                } \
            } else if (held & 0x400004) { \
                if (row == rows - 1) { \
                    if (held == trig) { \
                        int k = (rows - 1) * cols; \
                        o->cur -= k; \
                        o->top = 0; \
                    } \
                } else { \
                    s16 r; \
                    o->cur += cols; \
                    if (o->cur > n - 1) o->cur = n - 1; \
                    r = o->cur / cols; \
                    if (r < rows - 1 && (s16)vis - 1 == r - o->top) { \
                        o->top++; \
                        o->scroll = o->rowH; \
                    } \
                } \
            } \
        } \
        if (old != o->cur) SND; \
    } \
    fn_801E1CC0(o->bar, (s16)(o->top * o->rowH - (int)o->scroll)); \
}
BODY(Grid, fn_801E8680)
