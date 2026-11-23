#include "game/rI_801DD7D4/types.h"
struct Pt { s16 x, y; };
extern "C" Pt* fn_801E2204(void*, Pt*, Pt*);
struct W { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual int v34(); u8 p[0x1a]; s16 x1e, x20; u8 p22[0x36]; s16 a[12]; s16 b[12]; };
struct PC { s16 x, y; PC(s16 a, s16 b) { x = a; y = b; } };
struct PI { s16 x, y; PI(int a, int b) { x = a; y = b; } };
static inline Pt* pp(W* o, Pt* out, const PC& p) { return fn_801E2204(o, out, (Pt*)&p); }
static inline Pt* pp(W* o, Pt* out, const PI& p) { return fn_801E2204(o, out, (Pt*)&p); }
extern "C" Pt fn_801FE8BC(W* o) {
    int i = o->v34();
    Pt out;

    PC p(o->x1e, (s16)(o->b[i] - o->a[i]) * 0x1c + o->x20);
    return *fn_801E2204(o, &out, (Pt*)&p);
}
