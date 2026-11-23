#include "game/rB_8002E1C4/types.h"

struct Spot {
    u8 x0;
    u8 x1;
};
struct Ctx {
    u8 pad[0x40];
    Spot* x40;
};
struct RangeState {
    u8 pad[0x13];
    u8 x13;
    u8 x14;
    u8 pad15[0x130 - 0x15];
};

extern "C" {
extern RangeState lbl_803CA870;

static inline void setPos(RangeState* s, u8 x, u8 y)
{
    s->x13 = x;
    s->x14 = y;
}

int fn_80041894(void* self, Ctx* c)
{
    Spot* p = c->x40;
    if (p == 0) return 0x10;
    setPos(&lbl_803CA870, p->x0, p->x1);
    return 5;
}
}
