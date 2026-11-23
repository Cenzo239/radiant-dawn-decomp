#include "game/rP_80105B04/rp.h"
struct Color { u8 r, g, b, a; };
struct CSlot {
    void* item;
    u8 uses;
    u8 f80 : 1;
    u8 f40 : 1;
    u8 f20 : 1;
    u8 f10 : 1;
    u8 f08 : 1;
    u8 f04 : 1;
    u8 f02 : 1;
    u8 f01 : 1;
    char name[0x18];
    s8 mt, hit, crt, wt;
    Color col;
    u8 x26;
};
extern "C" {
void fn_80110D38(CSlot* s) {
    s->item = 0;
    s->uses = 0;
    s->f80 = 0;
    s->f40 = 0;
    s->f10 = 0;
    s->f08 = 0;
    s->f04 = 0;
    s->f02 = 0;
    s->f01 = 0;
    s->f20 = 0;
    s->name[0] = 0;
    s->mt = 0;
    s->hit = 0;
    s->crt = 0;
    s->wt = 0;
    {
        Color c = {0x80, 0x80, 0x80, 0xFF};
        s->col = c;
    }
    s->x26 = 0xFF;
}
}
