#include "game/rB_8002E1C4/types.h"

/* Range-action window drawing (heal preview etc.). The window object is a
 * C++ class with a member at +0 and its vtable at +4. */

struct Sprite {
    u8 pad[8];
    s16 x8;
    u8 pada[0x18 - 0xa];
    u32 flags;
};
struct Effect {
    u8 pad[0x30];
    Sprite* x30;
};
struct MapUnit {
    u8 pad[0x114];
    s8 hp;
};
struct Ctx {
    u8 pad[0x40];
    void* x40;
    u8 pad44[4];
    s8 x48;
    s8 x49;
};

class Win {
public:
    u32 x0;
    virtual void getPos(int* x, int* y, int* col);
    int x8;
    Effect* xc;
    Effect* x10;
    void* x14;
};

struct RangeState { MapUnit* unit; u8 pad[0x130 - 4]; };

extern "C" {
extern RangeState lbl_803CA870;
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E4E4(f32 x, f32 y, f32 a, f32 b);
void fn_8007E7DC(u8 c);
MapUnit* fn_800CFB0C(void* p);
int fn_801209D0(MapUnit* a, MapUnit* b);
void fn_80034964(MapUnit* u, u8 v);
s16 fn_801237EC(MapUnit* u);
void fn_800332B8(MapUnit* u, int v);
void fn_8003311C(MapUnit* u, int v);
void fn_800E48AC(Effect* e, f32 x, f32 y, f32 z);
void fn_800716F8(int a, int b, int c);

void fn_8003FE10(Win* self, Ctx* c)
{
    int x, y, col;
    MapUnit* u;
    u8 r;
    if (c->x40 == 0) return;
    self->getPos(&x, &y, &col);
    fn_8007E154();
    fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f);
    fn_8007E7DC(col);
    fn_8007E164();
    u = lbl_803CA870.unit;
    r = fn_801209D0(u, fn_800CFB0C(c->x40));
    fn_80034964(fn_800CFB0C(c->x40), r);
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
}

static inline const int& imin(const int& a, const int& b)
{
    return (a < b) ? a : b;
}

void fn_8003FF08(Win* self, Ctx* c)
{
    int x, y, col;
    int heal;
    MapUnit* u;
    self->xc->x30->flags |= 0x10;
    self->x10->x30->flags |= 0x10;
    if (c->x40 == 0) return;
    u = fn_800CFB0C(c->x40);
    {
        int hp = u->hp;
        int d = fn_801237EC(u) - hp;
        heal = imin(self->x8, d);
        self->getPos(&x, &y, &col);
    }
    fn_8007E154();
    fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f);
    fn_8007E7DC(col);
    fn_8007E164();
    fn_800332B8(u, heal);
    self->x10->x30->flags &= ~0x10;
    fn_800E48AC(self->x10, x + 0xa4, y + 0x8a, 0.0f);
    fn_8007E154();
    fn_8007E4E4(x + 0x20, y + 0xc4, 119.0f, 1.0f);
    fn_8007E164();
    fn_800716F8(0x76, 0, 1);
    fn_8007E154();
    fn_8007E4E4(x + 0x20, y + 0xdc, 120.0f, 1.0f);
    fn_8007E7DC(col);
    fn_8007E164();
    fn_8003311C(lbl_803CA870.unit, -heal);
    self->xc->x30->flags &= ~0x10;
    fn_800E48AC(self->xc, x + 0xa4, y + 0x136, 0.0f);
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
}

struct GameState;
extern GameState lbl_803CAB38;
extern char lbl_80379EB4[0x17];
extern char lbl_804CA090[5];
void fn_8013F204(void);
void fn_800620A8(GameState* g, f32 x, f32 y);
void fn_801C6EAC(const char* a, const char* b, void* out);
int fn_8023F8EC(void* p);
void fn_80040288(void);
#if TARGET_PC
FE10_PROTO void fn_80011CBC(void (*f)(void), p32arg);
#else
void fn_80011CBC(void (*f)(void), int n);
#endif
void fn_80081A90(void* p);

void fn_800401B0(Win* self, Ctx* c)
{
    u8 buf[0x60];
    fn_8013F204();
    fn_800620A8(&lbl_803CAB38, c->x48, c->x49);
    fn_801C6EAC(lbl_80379EB4, lbl_804CA090, buf);
    if (fn_8023F8EC(buf)) fn_80011CBC(fn_80040288, 0);
    fn_80081A90((void*)self->x8);
    fn_80081A90(self->xc);
    fn_80081A90(self->x10);
    fn_80081A90(self->x14);
}
}
