/* fn_801E9CA8 (round 19, `regs`). Fixes over the round 18 draft: the scale before the map sprite is
   0.5f (was 1.0f), the item pointer is taken through the item array, and the halved width is cast to
   s16 before the call. */
/* fn_801E9CA8: draw of a unit's 7-slot inventory panel, with the unit's map sprite on top when enabled. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_801D74B4(int, int, int, int, int, int);
void fn_800720F4(void*, int, int);
u32* fn_801E2204(void*, s16*, s16*);
void fn_801E2104(void* p, void* arg);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E74C(void*, void*);
void fn_8007E7B4(void);
int fn_800CB0FC(f32, int);
void* fn_8012486C(void*);
struct Spr { u8 p[0x34]; struct { u8 p[0x26]; s16 x26; }* x34; u8 p38[0x10]; u32 x48; };
Spr* fn_800C6210(void*, int);
void fn_800C4DDC(int, int, int, Spr*);
void fn_800C429C(Spr*);
}
struct Job { u8 p[8]; u8 x8; };
struct Unit { u8 p[0xf4]; Job* xf4; u8 pf8[0xc4]; int item[7][10]; };
class Inv { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(int*); virtual int v3C(int, int, int, int*, int);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; u8 p40[0xe]; u8 a4e; u8 p4f[9]; s16 a58; u8 p5a[2]; Unit* a5c; u8 p60[8]; u8 a68; u8 p69; s16 a6a, a6c, a6e, a70;
};
static inline void setR(Inv* o, s16 a, s16 b, s16 c, s16 d) { o->a6a = a; o->a6c = b; o->a6e = c; o->a70 = d; }
static inline s16 lt(s16 a, s16 b) { return a < b; }
static inline int lti(s16 a, s16 b) { return a < b; }
static inline void setF(Spr* p, s16 v) { p->x48 = (p->x48 & ~1) | v; }
static inline void setFi(Spr* p, int v) { p->x48 = (p->x48 & ~1) | (s16)v; }
static inline int idOf(const int* it) { return *it; }
extern "C" void fn_801E9CA8(Inv* o, void* c) {
    s16 rowH;
    s16 x;
    int dy;
    int i, yo, off;
    o->v14();
    fn_801D74B4(0, 0, (s16)(o->x1 - o->x0), (s16)(o->y1 - o->y0), o->a5c->xf4->x8, 0x10);
    switch (o->a68) {
    case 1:
        fn_800720F4(o->a5c, -0xc, -0x69);
        break;
    }
    o->v18(c);
    setR(o, 0, 0, o->ix1 - o->ix0, o->iy1 - o->iy0);
    fn_801E2204(o, &o->a6a, &o->a6a);
    fn_801E2204(o, &o->a6e, &o->a6e);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E74C(fn_801E2104, &o->a6a);
    fn_8007E164();
    rowH = o->a58;
    x = o->tx;
    dy = (rowH - fn_800CB0FC(1.0f, -1)) >> 1;
    for (i = 0, yo = 0; i < 7; i++, yo += rowH) {
        s16 y = o->ty + (dy + yo);
        int* it;
        it = o->a5c->item[i];
        if (*it != 0) {
            o->v3C(x, y, 0, it, o->v38(it));
        }
    }
    if (o->a4e != 0) {
        Spr* p;
        fn_8007E154();
        fn_8007E720(0.5f);
        fn_8007E164();
        p = fn_800C6210(fn_8012486C(o->a5c), 0x200);
        setFi(p, lti(o->x0 + ((s16)(o->x1 - o->x0) >> 1), 0x130));
        { s16 w, h; w = o->ix1 - o->ix0; h = o->iy1 - o->iy0; fn_800C4DDC((s16)(w >> 1), (s16)(h + p->x34->x26), 0x4c, p); }
        fn_800C429C(p);
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
