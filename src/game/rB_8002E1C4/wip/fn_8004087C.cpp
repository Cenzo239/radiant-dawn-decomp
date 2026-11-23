/* NEAR MISS: 13 of 91 words. Only cy (want r27) and the map base (want r29)
 * are swapped. Tried without success: int parameters plus s8 locals in setTile, a MapState* local
 * (it fixes the base but moves others: 14 words), reusing cx/cy for the second tile, k/k2 locals,
 * and hill-climbing all the declarations. The clones 80040BE0, 80040F44, 800412A8 and 80041598 are
 * byte-identical apart from their addresses. */
#include "game/rB_8002E1C4/types.h"

/* Range-action windows (item use / stand-on-tile actions). The window
 * object is a C++ class with a member at +0 and its vtable at +4. */

struct Sprite {
    u8 pad[0x18];
    u32 flags;
};
struct Effect {
    u8 pad[0x30];
    Sprite* x30;
};
struct MapUnit;
struct Ctx {
    u8 pad[0x3e];
    s8 x3e;
    s8 x3f;
    void* x40;
};
struct RangeState {
    MapUnit* unit;
    u8 pad4[0x11 - 4];
    s8 x11;
    s8 x12;
    u8 pad[0x130 - 0x13];
};
struct MapThing { s8 x; s8 y; u8 b2; u8 b3; u8 x4; };
struct Pos { s8 x; s8 y; };
struct MapState {
    u8 pad[0x710e];
    s16 x710e[64 * 64];
    u8 pad910e[0xd18e - 0x910e];
    s16 xd18e[64 * 64];
};

class Win {
public:
    u32 x0;
    virtual void getPos(int* x, int* y, int* col);
    void* x8;
    Effect* xc;
};

class Win8 {
public:
    u32 x0;
    virtual void getPos(int* x, int* y, int* col);
    Effect* x8;
};

extern "C" {
extern RangeState lbl_803CA870;
extern u8 lbl_803CB770[];
extern Item lbl_803CA800;
extern MapState lbl_803EC898;
extern int lbl_803E7320[];
MapThing* fn_80066130(void* p, s8 x, s8 y, int n);
ItemData* fn_8010B204(u8 id);
void fn_80110BB4(Item* it, ItemData* d);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E4E4(f32 x, f32 y, f32 a, f32 b);
void fn_8007E7DC(u8 c);
MapUnit* fn_800CFB0C(void* p);
void fn_800E48AC(Effect* e, f32 x, f32 y, f32 z);
Pos* fn_800CFD18(void* layer, int i);
int fn_800CFCB4(void* layer, s8 x, s8 y);
void fn_80114B44(MapState* m, int a, int b);
void fn_8013F1C4(void);

static inline void setTile(s8 x, s8 y)
{
    int i = x + (y << 6);
    lbl_803EC898.x710e[i] = -1;
    lbl_803EC898.xd18e[i] = 1;
}


#pragma use_lmw_stmw on
void fn_8004087C(Win* self, Ctx* c)
{
    int i;
    for (i = 0; i < lbl_803E7320[0]; i++) {
        Pos* p = fn_800CFD18(lbl_803E7320, i);
        lbl_803EC898.x710e[p->x + (p->y << 6)] = 1;
        lbl_803EC898.xd18e[p->x + (p->y << 6)] = 0;
    }
    {
        s8 cy = c->x3f;
        s8 cx = c->x3e;
        s8 ux = lbl_803CA870.x11;
        s8 uy = lbl_803CA870.x12;
        if (fn_800CFCB4(lbl_803E7320, cx, cy) == 0) return;
        setTile(cx, cy);
        {
        s8 nx = ux * 2 - cx;
        s8 ny = uy * 2 - cy;
        if (fn_800CFCB4(lbl_803E7320, nx, ny) == 0) return;
        setTile(nx, ny);
        }
    }
}
#pragma use_lmw_stmw reset
}
