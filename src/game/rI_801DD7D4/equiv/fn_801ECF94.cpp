/* symcheck: r21 review, flag was an artefact. fn_801FE8BC, fn_801EEFA4, fn_801EDF9C, fn_801ECF94: (a) stale
   temporaries before fn_801E2204 (reads r3-r5); the stack pair passed is equal. See docs/SCHED_REVIEW.md. */
/* fn_801ECF94: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
/* fn_801ECF94: screen position of the selected row of the active list column
   (x = text origin, y = (cur - top) * 0x1c + text origin y, mapped through fn_801E2204). */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
struct P2 { s16 x, y; };
extern "C" u32* fn_801E2204(void*, P2*, P2*);
class LV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 p22[0x36]; s16 top[8]; s16 cur[8];
};
#define F16(p, off) (*(s16*)((u8*)(p) + (off)))
static inline void setP(P2* p, s16 x, s16 y) { p->x = x; p->y = y; }
#define POS(fn, CU) \
extern "C" u32 fn(LV* o) { \
    P2 out; \
    P2 in; \
    u8* c = (u8*)o + o->v34() * 2; \
    setP(&in, o->tx, (s16)(F16(c, CU) - F16(c, 0x58)) * 0x1c + o->ty); \
    return *fn_801E2204(o, &out, &in); \
}
POS(fn_801ECF94, 0x68)
POS(fn_801EDF9C, 0x5e)
POS(fn_801EEFA4, 0x64)
POS(fn_801FE8BC, 0x70)
