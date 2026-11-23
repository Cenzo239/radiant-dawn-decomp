/* NEAR MISS: 6 of 75 words with the best declaration order. Only `it` (want r24)
 * and x (want r26) are swapped. Hill-climbing the declarations, and an extra local
 * copy of `it`, did not change it. */
#include "game/rB_8002E1C4/types.h"

/* Map-range functors. A functor is a stack object {vtable, unit, arg};
 * slot +8 visits a unit and slot +0xC visits a tile. */

struct MapUnit {
    u8 pad[0xf4];
    void* xf4;
    MapUnit* xf8;
    u8 xfc;
    u8 padfd[0x102 - 0xfd];
    s8 x;
    s8 y;
    u8 pad104[0x10c - 0x104];
    u32 x10c;
};

class RangeFunctor {
public:
    virtual void visitUnit(MapUnit* u);
    virtual void visitTile(s8 x, s8 y);
    MapUnit* u;
};

struct FObjB {
    void* vt;
    MapUnit* u;
    s8 x10;
};
struct FObjU {
    void* vt;
    MapUnit* u;
};
struct FObjI {
    void* vt;
    MapUnit* u;
    int x10;
};

struct MapState {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0x508e - 0x100d];
    u16 x508e[64 * 64];
    u8 pad[0x15190 - 0x508e - 0x2000];
    s16* dist;
};

extern "C" {
extern u8 lbl_803E7320[];
extern MapState lbl_803EC898;
void fn_800CFB34(void* layer);
void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, int mode);
void fn_800392FC(void* f, s8 x, s8 y);
int fn_8012BCB0(MapUnit* u);
int fn_80118098(MapState* m, s8 x, s8 y);
void fn_801151BC(MapState* m, MapUnit* u);
extern u8* lbl_804CB810;
void fn_80114888(MapState* m, int n);
int fn_801107C0(void* it, MapUnit* u);
int fn_801107A0(void* it, MapUnit* u);
void fn_80115DEC(MapState* m, s8 x, s8 y, u8 a, u8 b);
void fn_80116098(MapState* m, s8 x, s8 y, u8 a, u8 b);
extern u8 lbl_80379708[];
extern u8 lbl_803796F8[];

static inline MapUnit* GetUnit(u8 id)
{
    if (id != 0) {
        return (MapUnit*)(lbl_804CB810 + (id - 1) * 0x3f0);
    }
    return 0;
}

static inline void scanUnits(RangeFunctor* f, int lim0)
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
            f->visitUnit(GetUnit(id));
        }
    }
}

static inline void scanTiles(RangeFunctor* f, int lim0)
{
    s8 lim;
    s8 i;
    s8 j;

    lim = lim0;
    for (j = 0; j < lbl_803EC898.h; j++) {
        for (i = 0; i < lbl_803EC898.w; i++) {
            if (lbl_803EC898.dist[i + j * 64] < lim) continue;
            f->visitTile(i, j);
        }
    }
}

#pragma use_lmw_stmw on
void fn_80039C40(MapUnit* u, void* it)
{
    FObjI f;
    f.vt = lbl_803796F8;
    f.u = u;
    fn_800CFB34(lbl_803E7320);
    fn_80114888(&lbl_803EC898, 7);
    {
        s8 y = f.u->y;
        s8 x = f.u->x;
        int mx = fn_801107C0(it, f.u);
        int mn = fn_801107A0(it, f.u);
        fn_80116098(&lbl_803EC898, x, y, mn, mx);
    }
    f.x10 = (u8)fn_801107A0(it, f.u);
    scanTiles((RangeFunctor*)&f, f.x10);
}
#pragma use_lmw_stmw reset
}
