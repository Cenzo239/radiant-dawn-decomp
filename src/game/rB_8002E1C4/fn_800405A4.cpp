#include "game/rB_8002E1C4/types.h"

struct Sprite { u8 pad[0x18]; u32 flags; };
struct Effect { u8 pad[0x30]; Sprite* x30; };
struct MapUnit;
struct Ctx { u8 pad[0x40]; void* x40; };

class Win {
public:
    u32 x0;
    virtual void getPos(int* x, int* y, int* col);
    Effect* x8;
    Effect* xc;
    Effect* x10;
    Effect* x14;
};

extern "C" {
extern u8 lbl_803CA7C0[];
MapUnit* fn_800CFB0C(void* p);
void fn_8003DD6C(void* p, MapUnit* u, int a, int b, int c);

void fn_800405A4(Win* self, Ctx* c)
{
    int x, y, col;
    self->x8->x30->flags |= 0x10;
    self->xc->x30->flags |= 0x10;
    self->x10->x30->flags |= 0x10;
    self->x14->x30->flags |= 0x10;
    if (c == 0) return;
    if (c->x40 == 0) return;
    if (fn_800CFB0C(c->x40) == 0) return;
    self->getPos(&x, &y, &col);
    fn_8003DD6C(lbl_803CA7C0, fn_800CFB0C(c->x40), x, y, col);
}
}
