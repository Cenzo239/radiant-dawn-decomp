/* symcheck: r21 review, flag was an artefact. fn_80223900: (a) stale temporaries in r7-r9 before fn_801E2204
   (reads r3-r5); the stack pair passed is equal. See docs/SCHED_REVIEW.md. */
/* fn_80223900: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct XY { s16 x, y; };
XY* fn_801E2204(void*, XY*, XY*);
class GW { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); };
struct GD { void* vt; u8 p4[0x1a]; s16 a1e, a20; u8 p22[0x34]; s16 a56; u8 p58[6]; s16 a5e, a60, a62; };
static inline XY mk(s16 x, s16 y) { XY p; p.x = x; p.y = y; return p; }
static inline void st(XY& p, s16 x, s16 y) { p.x = x; p.y = y; }
static inline XY cell(GW* g, s16 col, s16 row) { GD* o = (GD*)g; int w = g->v44(); XY p; p.x = w * col + o->a1e; p.y = o->a62 * row + o->a20; return p; }
XY fn_80223900(GW* g) {
    GD* o = (GD*)g;
    int w = g->v44();
    XY out; XY p;
s16 h = o->a62; s16 c = o->a60; s16 y0 = o->a20; s16 b = o->a5e; s16 n = o->a56; s16 x0 = o->a1e; int q = n / c;
    st(p, w * (s16)(n - q * c) + x0, h * (s16)((s16)q - b) + y0);
    return *fn_801E2204(g, &out, &p);
}

}
