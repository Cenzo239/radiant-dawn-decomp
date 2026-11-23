#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct XY { s16 x, y; };
XY* fn_801E2204(void*, XY*, XY*);
class GW { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); };
struct GD { void* vt; u8 p4[0x48]; s16 a4c, a4e; };
XY fn_8022A7CC(GD* o) {
    s16 x = o->a4c;
    GW* g = (GW*)o;
    s16 y = o->a4e - g->v38();
    int w = g->v30();
    int h = g->v34();
    XY out; XY p;
    p.x = x * w; p.y = y * h;
    return *fn_801E2204(g, &out, &p);
}

}
