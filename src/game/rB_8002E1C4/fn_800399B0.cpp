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
#if TARGET_PC
FE10_PROTO void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, p32arg);
#else
void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, int mode);
#endif
void fn_800392FC(void* f, s8 x, s8 y);
int fn_8012BCB0(MapUnit* u);
int fn_80118098(MapState* m, s8 x, s8 y);
void fn_801151BC(MapState* m, MapUnit* u);
extern u8 lbl_80379718[];

void fn_800399B0(MapUnit* u, s8 n)
{
    FObjB f;
    f.vt = lbl_80379718;
    f.u = u;
    f.x10 = n;
    fn_800CFB34(lbl_803E7320);
    fn_800392FC(&f, u->x, u->y);
    if (u->x10c & 2) ((RangeFunctor*)&f)->visitUnit(u->xf8);
}

void fn_80039A34(RangeFunctor* self, MapUnit* t)
{
    if (t->xf4 == self->u->xf4) {
        if (fn_8012BCB0(self->u) == 0 || fn_8012BCB0(t) == 0)
            fn_800CFC50(lbl_803E7320, t->x, t->y, t->xfc, 0);
    }
    if (t->x10c & 2) self->visitUnit(t->xf8);
}
}
