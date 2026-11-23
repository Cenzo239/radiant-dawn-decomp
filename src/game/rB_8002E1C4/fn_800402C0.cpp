#include "game/rB_8002E1C4/types.h"

struct Sprite {
    u8 pad[8];
    s16 x8;
    u8 pada[0xc - 0xa];
    u8 xc;
    u8 padd[0x18 - 0xd];
    u32 flags;
};
struct Effect {
    u8 pad[0x30];
    Sprite* x30;
};
struct MapUnit;
struct Spot {
    u8 x0;
    u8 x1;
    u8 pad2[2];
    u32 x4;
};
struct Ctx {
    u8 pad[0x3e];
    s8 x3e;
    s8 x3f;
    Spot* x40;
};
struct RangeState {
    MapUnit* unit;
    u32 x4;
    u8 pad8[4];
    u8 xc;
    u8 padd[0x13 - 0xd];
    u8 x13;
    u8 x14;
    u8 pad[0x130 - 0x15];
};

class Win {
public:
    u32 x0;
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void* item(); /* +0x34 */
    Effect* x8[2];
    Effect* x10[2];
};

struct BState;

extern "C" {
extern RangeState lbl_803CA870;
extern BState lbl_803C8E80;
extern char lbl_80379E9C[0x17];
extern char lbl_804CA088[5];
extern char lbl_80379E90[0xb];
extern char lbl_80379E84[0xb];
void fn_8013F1C4(void);
void fn_801C6EAC(const char* a, const char* b, void* out);
void fn_8023F1A0(void* p, int n);
Effect* fn_800E3C04(const char* name, void* p);
MapUnit* fn_800CFB0C(Spot* p);
int fn_800CFE40(Win* self, Ctx* c);
#if TARGET_PC
FE10_PROTO void fn_801030B8(MapUnit* u, int x, int y, int a, int b, p32arg);
FE10_PROTO void fn_8010301C(MapUnit* a, MapUnit* b, int c, int d, p32arg);
#else
void fn_801030B8(MapUnit* u, int x, int y, int a, int b, int c);
void fn_8010301C(MapUnit* a, MapUnit* b, int c, int d, int e);
#endif
void fn_80026C44(BState* b, MapUnit* a, MapUnit* d);
void fn_80026E64(BState* b, void* it);
void fn_8002742C(BState* b, int n);

#pragma use_lmw_stmw on
void fn_800402C0(Win* self, void* a)
{
    u8 buf[0x68];
    int i;
    fn_8013F1C4();
    fn_801C6EAC(lbl_80379E9C, lbl_804CA088, buf);
    fn_8023F1A0(buf, 0);
    for (i = 0; i < 2; i++) {
        self->x8[i] = fn_800E3C04(lbl_80379E90, a);
        self->x8[i]->x30->flags |= 0x1004;
        self->x8[i]->x30->x8 = 0x5a;
        self->x8[i]->x30->xc = 1;
    }
    for (i = 0; i < 2; i++) {
        self->x10[i] = fn_800E3C04(lbl_80379E84, a);
        self->x10[i]->x30->flags |= 0x1004;
        self->x10[i]->x30->x8 = 0x5a;
        self->x10[i]->x30->xc = 1;
    }
}
#pragma use_lmw_stmw reset

static inline void setPos(RangeState* s, u8 x, u8 y)
{
    s->x13 = x;
    s->x14 = y;
}

int fn_800403C4(Win* self, Ctx* c)
{
    Spot* t = c->x40;
    if (t == 0) return 0x10;
    if (fn_800CFB0C(t) != 0) return fn_800CFE40(self, c);
    if (t->x4 != 0) {
        setPos(&lbl_803CA870, t->x0, t->x1);
        lbl_803CA870.x4 = 0;
        return 5;
    }
    return 0;
}

void fn_8004046C(Win* self, Ctx* c)
{
    Spot* t;
    MapUnit* u;
    u8 k;
    fn_801030B8(lbl_803CA870.unit, c->x3e, c->x3f, 8, 0, 0);
    t = c->x40;
    if (t == 0) return;
    if (fn_800CFB0C(t) == 0) return;
    fn_8010301C(fn_800CFB0C(t), lbl_803CA870.unit, 8, 0, 0);
    u = lbl_803CA870.unit;
    fn_80026C44(&lbl_803C8E80, u, fn_800CFB0C(t));
    fn_80026E64(&lbl_803C8E80, self->item());
    k = lbl_803CA870.xc;
    switch (k) {
    case 0x15:
    case 0x16:
    case 0x41:
        fn_8002742C(&lbl_803C8E80, k);
        break;
    default:
        fn_8002742C(&lbl_803C8E80, 0xf);
        break;
    }
}
}
