#include "game/rB_8002E1C4/types.h"

/* Item range helpers: mark every unit within the item's range (distance
 * map at map+0x15190) with a stack functor {vtable, unit}. */

struct MapUnit {
    u8 pad[0x102];
    s8 x;
    s8 y;
};
struct MapState {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0x15190 - 0x100d];
    s16* dist;
};

class UnitFunctor {
public:
    virtual void visit(MapUnit* u);
};

struct FObjU {
    void* vt;
    MapUnit* u;
};

extern "C" {
extern u8 lbl_803E7320[];
extern MapState lbl_803EC898;
extern u8* lbl_804CB810;
void fn_800CFB34(void* layer);
void fn_80114888(MapState* m, int n);
int fn_80110880(void* it, MapUnit* u); /* max range */
int fn_801107B8(void* it, MapUnit* u); /* min range */
void fn_80115DEC(MapState* m, s8 x, s8 y, u8 a, u8 b);

static inline MapUnit* GetUnit(u8 id)
{
    if (id != 0) {
        return (MapUnit*)(lbl_804CB810 + (id - 1) * 0x3f0);
    }
    return 0;
}

/* lim0 must be int and lim a separate s8 local, declared first: that is what puts
 * the limit in r26 and the row counter in r28. */
static inline void scan(UnitFunctor* f, int lim0)
{
    s8 lim;
    u8 id;
    s8 i;
    s8 j;

    lim = lim0;
    for (j = 0; j < lbl_803EC898.h; j++) {
        for (i = 0; i < lbl_803EC898.w; i++) {
            if (lbl_803EC898.dist[i + j * 64] < lim) continue;
            id = lbl_803EC898.grid[i + j * 64];
            if (id == 0) continue;
            f->visit(GetUnit(id));
        }
    }
}

#pragma use_lmw_stmw on
#define ITEM_RANGE_FN(name, vtbl) \
    extern u8 vtbl[]; \
    void name(MapUnit* u, void* it) \
    { \
        FObjU f; \
        f.vt = vtbl; \
        f.u = u; \
        fn_800CFB34(lbl_803E7320); \
        fn_80114888(&lbl_803EC898, 7); \
        { \
            s8 y = f.u->y; \
            s8 x = f.u->x; \
            int mx = fn_80110880(it, f.u); \
            int mn = fn_801107B8(it, f.u); \
            fn_80115DEC(&lbl_803EC898, x, y, mn, mx); \
        } \
        scan((UnitFunctor*)&f, fn_801107B8(it, f.u)); \
    }

ITEM_RANGE_FN(fn_8003A3BC, lbl_80379648)
ITEM_RANGE_FN(fn_8003A510, lbl_80379638)
ITEM_RANGE_FN(fn_8003A664, lbl_80379628)
ITEM_RANGE_FN(fn_8003A7B8, lbl_80379618)
ITEM_RANGE_FN(fn_8003A90C, lbl_80379608)
#pragma use_lmw_stmw reset
}
