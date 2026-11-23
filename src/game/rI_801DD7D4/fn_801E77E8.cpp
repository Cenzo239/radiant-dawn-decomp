#include "game/rI_801DD7D4/types.h"
class Wv { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual int v4C();
  u8 p4[0x4e]; s16 x52; u8 p54[2]; s16 x56, x58, x5a, x5c; u8 p5e[0x12]; int x70; };
extern "C" void fn_801E77E8(Wv* o, int t) {
    int vis;
    s16 cols;
    int m1;
    s16 n;
    s16 rows;
    if (t == o->x52) return;
    vis = o->v4C();
    cols = o->x5c;
    m1 = cols - 1;
    n = o->x70;
    rows = (n + m1) / cols;
    if (t < 0 || !(n > t)) return;
    if ((s16)vis > rows) vis = rows;
    if (t < o->x52) {
        do {
            o->x52--; { s16 c = o->x52; if (c > m1) { s16 r = c / cols; if (r - o->x5a == 0) o->x5a--; } }
        } while (t < o->x52);
    } else {
        do {
            if (++o->x52 > n - 1) o->x52 = n - 1; { s16 r = o->x52 / cols; if (r < rows - 1 && (s16)vis - 1 == r - o->x5a) o->x5a++; }
        } while (o->x52 < t);
    }
    o->x56 = -0x8000;
    o->x58 = -0x8000;
}
