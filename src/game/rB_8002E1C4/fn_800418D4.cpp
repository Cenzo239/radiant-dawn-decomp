#include "game/rB_8002E1C4/actwin.h"

/* window with a value at +8 and an arrow effect at +0xC */
class WinV {
public:
    u32 x0;
    virtual void getPos(int* x, int* y, int* col);
    int x8;
    Effect* xc;
};

struct BitUnit {
    u8 pad[0x112];
    u16 pad_b : 8;
    u16 x112_8 : 3;
    u16 pad_c : 5;
};
struct UnitF8 {
    u8 pad[0xf8];
    MapUnit* xf8;
};

extern "C" {
void fn_80034294(MapUnit* u, MapUnit* v);
static inline void fn_80034294_u(MapUnit* u) { fn_80034294(u, lbl_803CA870.unit); }
int fn_80120928(MapUnit* a, MapUnit* b);
void fn_800346D0(MapUnit* u, u8 v);
void fn_80033684(MapUnit* u, int a, int b);
void fn_80033454(MapUnit* u);
void fn_800350A4(MapUnit* u, int v);
void fn_8003311C(MapUnit* u, int v);
void fn_800341A0(MapUnit* u);
int fn_8012084C(MapUnit* a, MapUnit* b);
void fn_80034484(MapUnit* u, u8 v);
void fn_80032FA8(MapUnit* u);
void fn_800717E4(int a, int b, int c);
void fn_80033E9C(MapUnit* u);
void fn_80033D00(MapUnit* u, const char* s);
void fn_80033930(MapUnit* u);
void fn_80033B18(MapUnit* u);
extern char lbl_80379F08[0xe];
extern char lbl_80379F18[0xe];
extern char lbl_80379F28[0x10];

DRAW_FN(fn_800418D4, fn_80034294_u)

#define CMP_FN(name, calcA, calcB) \
    void name(Win8* self, Ctx* c) \
    { \
        int x, y, col; \
        MapUnit* u; \
        u8 r; \
        if (c->x40 == 0) return; \
        self->getPos(&x, &y, &col); \
        fn_8007E154(); \
        fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f); \
        fn_8007E7DC(col); \
        fn_8007E164(); \
        u = lbl_803CA870.unit; \
        r = calcA(u, fn_800CFB0C(c->x40)); \
        calcB(fn_800CFB0C(c->x40), r); \
        fn_8007E154(); \
        fn_8007E7DC(0xff); \
        fn_8007E164(); \
    }

CMP_FN(fn_800419A8, fn_80120928, fn_800346D0)

void fn_80041AA0(Win8* self, Ctx* c)
{
    int x, y, col;
    self->x8->x30->flags |= 0x10;
    if (c->x40 == 0) return;
    self->getPos(&x, &y, &col);
    fn_8007E154();
    fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f);
    fn_8007E7DC(col);
    fn_8007E164();
    {
        MapUnit* u = fn_800CFB0C(c->x40);
        fn_80033684(fn_800CFB0C(c->x40), 7, 7 - ((BitUnit*)u)->x112_8);
    }
    self->x8->x30->flags &= ~0x10;
    fn_800E48AC(self->x8, x + 0xa4, y + 0xa6, 0.0f);
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
}

DRAW8_FN(fn_80041C04, fn_80033454)

#define DRAWV_FN(name, body) \
    void name(WinV* self, Ctx* c) \
    { \
        int x, y, col; \
        self->xc->x30->flags |= 0x10; \
        if (c->x40 == 0) return; \
        self->getPos(&x, &y, &col); \
        fn_8007E154(); \
        fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f); \
        fn_8007E7DC(col); \
        fn_8007E164(); \
        body(fn_800CFB0C(c->x40), self->x8); \
        self->xc->x30->flags &= ~0x10; \
        fn_800E48AC(self->xc, x + 0xa4, y + 0x8a, 0.0f); \
        fn_8007E154(); \
        fn_8007E7DC(0xff); \
        fn_8007E164(); \
    }

DRAWV_FN(fn_80041D44, fn_800350A4)
DRAWV_FN(fn_80041E88, fn_8003311C)
DRAW_FN(fn_80041FCC, fn_800341A0)
CMP_FN(fn_80042098, fn_8012084C, fn_80034484)

void fn_80042190(Win8* self, Ctx* c)
{
    int x, y, col;
    if (c->x40 == 0) return;
    self->getPos(&x, &y, &col);
    fn_8007E154();
    fn_8007E7DC(col);
    fn_8007E164();
    fn_8007E154();
    fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f);
    fn_8007E164();
    fn_80032FA8(((UnitF8*)lbl_803CA870.unit)->xf8);
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
}

#define NOCOL
#define COL fn_8007E7DC(col);
#define PAIR_FN(name, calcA, y2, flag, y3, col3, calcB) \
    void name(Win8* self, Ctx* c) \
    { \
        int x, y, col; \
        if (c->x40 == 0) return; \
        self->getPos(&x, &y, &col); \
        fn_8007E154(); \
        fn_8007E7DC(col); \
        fn_8007E164(); \
        fn_8007E154(); \
        fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f); \
        fn_8007E164(); \
        calcA; \
        fn_8007E154(); \
        fn_8007E4E4(x + 0x20, y + y2, 119.0f, 1.0f); \
        fn_8007E164(); \
        fn_800717E4(0x76, 0, flag); \
        fn_8007E154(); \
        fn_8007E4E4(x + 0x20, y + y3, 120.0f, 1.0f); \
        col3 \
        fn_8007E164(); \
        calcB; \
        fn_8007E154(); \
        fn_8007E7DC(0xff); \
        fn_8007E164(); \
    }

PAIR_FN(fn_8004225C, fn_80033E9C(lbl_803CA870.unit), 0xd2, 0, 0xea, COL,
        fn_80033D00(fn_800CFB0C(c->x40), lbl_80379F08))
PAIR_FN(fn_800423F0, fn_80033D00(lbl_803CA870.unit, lbl_80379F18), 0xe8, 1, 0xfe, COL,
        fn_80033E9C(fn_800CFB0C(c->x40)))
PAIR_FN(fn_80042584, fn_80033D00(lbl_803CA870.unit, lbl_80379F28), 0xe8, 1, 0xfe, NOCOL,
        fn_80032FA8(fn_800CFB0C(c->x40)))
PAIR_FN(fn_8004270C, fn_80033930(lbl_803CA870.unit), 0xaa, 0, 0xc2, NOCOL,
        fn_80033B18(fn_800CFB0C(c->x40)))
}
