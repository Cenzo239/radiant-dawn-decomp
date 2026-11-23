#include "game/rB_8002E1C4/types.h"

/* Map-range helpers that visit the four tiles next to the unit with a
 * stack functor (vtable at +0, visit at slot +0xC). */

struct MapUnit {
    u8 pad[0x102];
    s8 x;
    s8 y;
};
struct MapDims {
    int w;
    int h;
    u8 pad[0x100];
};

class TileFunctor {
public:
    virtual void v0();
    virtual void visit(s8 x, s8 y);
};

struct FObj {
    void* vt;
    u8 xc;
};

extern "C" {
extern u8 lbl_803E7320[];
extern MapDims lbl_803EC898;
void fn_800CFB34(void* layer);
void fn_8010F598(u8* p);

static inline void visit4(TileFunctor* f, s8 y, s8 x)
{
    int n;
    if ((n = y - 1) >= 0) f->visit(x, n);
    if ((n = x + 1) < lbl_803EC898.w) f->visit(n, y);
    if ((n = y + 1) < lbl_803EC898.h) f->visit(x, n);
    if ((n = x - 1) >= 0) f->visit(n, y);
}

extern u8 lbl_803795F8[];

void fn_8003AA60(MapUnit* u, u8* p)
{
    FObj f;
    f.xc = 0;
    {
        u8 v = *p;
        f.vt = lbl_803795F8;
        f.xc = v;
    }
    fn_8010F598(&f.xc);
    fn_800CFB34(lbl_803E7320);
    if (f.xc & 3) visit4((TileFunctor*)&f, u->y, u->x);
}

#define SET_FN(name, v) \
    void name(MapUnit* u) \
    { \
        FObj f; \
        f.vt = lbl_803795F8; \
        f.xc = v; \
        fn_8010F598(&f.xc); \
        fn_800CFB34(lbl_803E7320); \
        if (f.xc & 3) visit4((TileFunctor*)&f, u->y, u->x); \
    }

SET_FN(fn_8003AB90, 2)
SET_FN(fn_8003ACB8, 1)

#define ADJ_FN(name, vtbl) \
    extern u8 vtbl[]; \
    void name(MapUnit* u) \
    { \
        FObj f; \
        f.vt = vtbl; \
        fn_800CFB34(lbl_803E7320); \
        visit4((TileFunctor*)&f, u->y, u->x); \
    }

ADJ_FN(fn_8003ADE0, lbl_803795E8)
ADJ_FN(fn_8003AEEC, lbl_803795D8)
}
