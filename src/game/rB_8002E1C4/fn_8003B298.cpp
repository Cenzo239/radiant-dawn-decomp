#include "game/rB_8002E1C4/types.h"

/* Visit the tiles next to a position with a stack functor. */

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
    u8 pad100d[0x508e - 0x100d];
    u16 x508e[64 * 64];
};

class TileFunctor {
public:
    virtual void v0();
    virtual void visit(s8 x, s8 y);
};

struct FObj {
    void* vt;
    MapUnit* u;
    s8 x10;
};

extern "C" {
extern u8 lbl_803E7320[];
extern MapState lbl_803EC898;
extern u8 lbl_80379548[];
extern u8 lbl_80379538[];
void fn_800CFB34(void* layer);
#if TARGET_PC
FE10_PROTO void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, p32arg);
#else
void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, int mode);
#endif
void fn_801151BC(MapState* m, MapUnit* u);

static inline void visit4(TileFunctor* f, s8 y, s8 x)
{
    int n;
    if ((n = y - 1) >= 0) f->visit(x, n);
    if ((n = x + 1) < lbl_803EC898.w) f->visit(n, y);
    if ((n = y + 1) < lbl_803EC898.h) f->visit(x, n);
    if ((n = x - 1) >= 0) f->visit(n, y);
}

void fn_8003B298(s8 x, s8 y)
{
    void* vt;
    u8 id;
    vt = lbl_80379548;
    fn_800CFB34(lbl_803E7320);
    id = *(x + (y << 6) + lbl_803EC898.grid);
    if (id != 0) fn_800CFC50(lbl_803E7320, x, y, id, 1);
    visit4((TileFunctor*)&vt, y, x);
}

void fn_8003B3DC(MapUnit* u, s8 n)
{
    FObj f;
    s8 y, x;
    u16* p;
    f.vt = lbl_80379538;
    f.u = u;
    f.x10 = n;
    fn_800CFB34(lbl_803E7320);
    fn_801151BC(&lbl_803EC898, f.u);
    y = f.u->y;
    x = f.u->x;
    p = &lbl_803EC898.x508e[x + (y << 6)];
    if (*p & 8) ((TileFunctor*)&f)->visit(x, y - 1);
    if (*p & 2) ((TileFunctor*)&f)->visit(x + 1, y);
    if (*p & 4) ((TileFunctor*)&f)->visit(x, y + 1);
    if (*p & 1) ((TileFunctor*)&f)->visit(x - 1, y);
}
}
