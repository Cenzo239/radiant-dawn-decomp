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
#if TARGET_PC
FE10_PROTO struct TileEntry * fn_800CFCB4(void* layer, s8 x, s8 y);
#else
int fn_800CFCB4(void* layer, s8 x, s8 y);
#endif
void fn_80114B44(MapState* m, int a, int b);
void fn_8013F1C4(void);

Item* fn_800406D0(void)
{
    fn_80110BB4(&lbl_803CA800, fn_8010B204(fn_80066130(lbl_803CB770, lbl_803CA870.x11, lbl_803CA870.x12, 7)->x4));
    return &lbl_803CA800;
}

#if TARGET_PC
FE10_PROTO void fn_80034F08(MapUnit* u, ptr32<const void>);
#else
void fn_80034F08(MapUnit* u, void* v);
#endif

void fn_80040738(Win* self, Ctx* c)
{
    int x, y, col;
    self->xc->x30->flags |= 0x10;
    if (c->x40 == 0) return;
    self->getPos(&x, &y, &col);
    fn_8007E154();
    fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f);
    fn_8007E7DC(col);
    fn_8007E164();
    fn_80034F08(fn_800CFB0C(c->x40), self->x8);
    self->xc->x30->flags &= ~0x10;
    fn_800E48AC(self->xc, x + 0xa4, y + 0x8a, 0.0f);
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
}

}
