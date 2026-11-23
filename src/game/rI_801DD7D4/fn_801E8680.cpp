/* fn_801E8680: d-pad navigation of a scrolling item grid (wraps on a fresh press, scrolls a row
   at a time and starts the row-scroll animation), then updates the scroll bar.
   The same body, for a class whose grid fields sit 4 bytes later, is fn_80224554 (fn_80224554.cpp).
   Exact (round m13): the BODY macro written out, every block local at the top (hill-climbed order), the
   inputBlocked() inline expanded with function-level f1/f2/bb, `cr = o->cur; row = cr / cols; col = cr % cols;`,
   `o->cur = c = o->cur - cols;`, and the top clamp `(rows - (s16)vis) > 0 ? (rows - (s16)vis) : 0` without a local. */
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
extern "C" void fn_801E8680(Grid* o) {
        s16 col;
    BOOL bb;
    s16 c;
    u32 f1;
    s16 cols;
    int m1;
    s16 r;
    int vis;
    s16 n;
    int cr;
    s16 old;
    int trig;
    int k;
    s16 rows;
    u32 f2;
    s16 row;
    int held;
    int rem;
    vis = o->v4C();
    cols = o->cols;
    m1 = cols - 1;
    n = o->n;
    rows = (n + m1) / cols;
    if ((s16)vis > rows) vis = rows;
    {
        cr = o->cur;
        row = cr / cols;
        col = cr % cols;
    }
    f1 = lbl_804CB700;
    f2 = lbl_804CB700;
    bb = FALSE;
    if ((f1 & 0x10) && !(f2 & 0x20)) {
        bb = TRUE;
    }
    if (!bb) {
        held = lbl_804CB5B8->v3C();
        trig = lbl_804CB5B8->v48();
        old = ((const Grid*)o)->cur;
        if (cols > 1) {
            rem = n - row * cols;
            if (rem > cols) rem = cols;
            if (held & 0x100001) {
                if (col > 0) {
                    o->cur--;
                } else if (held == trig) {
                    o->cur = rem + o->cur - 1;
                }
            } else if (held & 0x200002) {
                rem--;
                if (col < rem) {
                    o->cur++;
                } else if (held == trig) {
                    o->cur -= rem;
                }
            }
        }
        if ((s16)(int)o->scroll == 0) {
            if (held & 0x800008) {
                if (row == 0) {
                    if (held == trig) {
                        o->cur += (rows - 1) * cols;
                        o->top = (rows - (s16)vis) > 0 ? (rows - (s16)vis) : 0;
                        if (o->cur > n - 1) o->cur = n - 1;
                    }
                } else {
                    o->cur = c = o->cur - cols;
                    if (c > m1) {
                        r = c / cols;
                        if (r - o->top == 0) {
                            o->top--;
                            o->scroll = -o->rowH;
                        }
                    }
                }
            } else if (held & 0x400004) {
                if (row == rows - 1) {
                    if (held == trig) {
                        k = (rows - 1) * cols;
                        o->cur -= k;
                        o->top = 0;
                    }
                } else {
                    o->cur += cols;
                    if (o->cur > n - 1) o->cur = n - 1;
                    r = o->cur / cols;
                    if (r < rows - 1 && (s16)vis - 1 == r - o->top) {
                        o->top++;
                        o->scroll = o->rowH;
                    }
                }
            }
        }
        if (old != o->cur) SND;
    }
    fn_801E1CC0(o->bar, (s16)(o->top * o->rowH - (int)o->scroll));
}

