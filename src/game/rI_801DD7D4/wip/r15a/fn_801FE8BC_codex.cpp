/* Round 15 continuation: 9/31 words differ; scalar loads made explicit. */
#include "game/rI_801DD7D4/types.h"
struct Pt { s16 x, y; };
extern "C" Pt* fn_801E2204(void*, Pt*, Pt*);
struct W { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual int v34(); u8 p[0x1a]; s16 x1e, x20; u8 p22[0x36]; s16 a[12]; s16 b[12]; };
struct PC { s16 x, y; PC(s16 a, s16 b) { x = a; y = b; } };
struct PI { s16 x, y; PI(int a, int b) { x = a; y = b; } };
static inline Pt* pp(W* o, Pt* out, const PC& p) { return fn_801E2204(o, out, (Pt*)&p); }
static inline Pt* pp(W* o, Pt* out, const PI& p) { return fn_801E2204(o, out, (Pt*)&p); }
extern "C" Pt fn_801FE8BC(W* o) {
    int x;
    int y;
    int b;
    int a;
    int i = o->v34();
    Pt out;
x = o->x1e;
y = o->x20;
a = o->a[i];
b = o->b[i];
    PC p(x, (s16)(b - a) * 0x1c + y);
    return *fn_801E2204(o, &out, (Pt*)&p);
}
