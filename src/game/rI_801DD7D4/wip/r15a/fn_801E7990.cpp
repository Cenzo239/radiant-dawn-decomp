#include "game/rI_801DD7D4/types.h"
struct Pt { s16 x, y; };
extern "C" Pt* fn_801E2204(void*, Pt*, Pt*);
struct W { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual int v44();
  u8 p4[0x1a]; s16 x1e, x20; u8 p22[0x30]; s16 x52; u8 p54[6]; s16 x5a, x5c, x5e; };
extern "C" Pt fn_801E7990(W* o) {
    Pt out;
    Pt p;
/*P*/
    s16 cols;
    s16 cur;
    s16 top;
    s16 h;
    int q;
    int w;
    s16 x;
    s16 y;
/*E*/
    w = o->v44();
    {
    cols = o->x5c;
    cur = o->x52;
    top = o->x5a;
    h = o->x5e;
    { int m = w * (s16)(cur % cols); x = m + o->x1e; }
    q = cur / cols;
    { int m2 = h * (s16)((s16)q - top); y = m2 + o->x20; }
    }
    p.x = x;
    p.y = y;
    return *fn_801E2204(o, &out, &p);
}
