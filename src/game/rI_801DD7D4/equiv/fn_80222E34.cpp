/* fn_80222E34: draw of a unit's skill/item list panel (18 slots, 8 bytes each, at unit+0x12c) with a
   6-row backdrop, an insert/remove animation (mode 1: rows below the cursor slide, mode 2: the cursor
   row fades), and the unit's map sprite on top when enabled. Sibling of fn_801E9CA8. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_801D74B4(int, int, int, int, int, int);
void fn_801D8ADC(int, int, int, int);
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
struct Skl { u8 p[0x1f]; u8 x1f; };
struct Slot { Skl* s; int x4; };
struct Unit { u8 p[0xf4]; Job* xf4; u8 pf8[0x34]; Slot slot[18]; };
class Inv { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(Slot*); virtual int v3C(int, int, int, int, Slot*, int);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; u8 p40[0xe]; u8 a4e; u8 p4f[9]; s16 a58; u8 p5a[2]; Unit* a5c; u8 a60; u8 p61[3];
    int mode; s16 cur; u8 p6a[2]; f32 t; s16 a70, a72, a74, a76;
};
static inline void setR(Inv* o, s16 a, s16 b, s16 c, s16 d) { o->a70 = a; o->a72 = b; o->a74 = c; o->a76 = d; }
static inline int lti(s16 a, s16 b) { return a < b; }
static inline void setFi(Spr* p, int v) { p->x48 = (p->x48 & ~1) | (s16)v; }
static inline int fade(f32 t) { return 255.99f * t; }
static inline void put(Spr* p, s16 w, s16 h) { fn_800C4DDC((s16)(w >> 1), (s16)(h + p->x34->x26), 0x4c, p); }
static inline BOOL used(Slot* it) { return it != NULL && it->s != NULL && it->s->x1f != 0; }
extern "C" void fn_80222E34(Inv* o, void* c) {
    int dy;
    s16 rowH;
    Slot* it;
    int off;
    int yo;
    s16 x;
    int alpha, sh;
    s16 n;
    int i;
    o->v14();
    fn_801D74B4(0, 0, (s16)(o->x1 - o->x0), (s16)(o->y1 - o->y0), o->a5c->xf4->x8, 0x10);
    switch (o->a60) {
    case 1:
        fn_800720F4(o->a5c, -0xc, -0x69);
        break;
    }
    o->v18(c);
    setR(o, 0, 0, o->ix1 - o->ix0, o->iy1 - o->iy0);
    fn_801E2204(o, &o->a70, &o->a70);
    fn_801E2204(o, &o->a74, &o->a74);
    fn_8007E154();
    fn_8007E74C(fn_801E2104, &o->a70);
    fn_8007E164();
    rowH = o->a58;
    x = o->tx;
    dy = (rowH - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_8007E154();
    fn_8007E720(0.5f);
    fn_8007E164();
    for (off = 0, yo = 0; off < 6; off++, yo += rowH) {
        fn_801D8ADC(x, (s16)(rowH + (s16)(o->ty + (dy + yo)) - 0xc), (s16)((s16)(o->ix1 - o->ix0) - o->tx * 2), 0x10);
    }
    fn_8007E154();
    fn_8007E720(-0.5f);
    fn_8007E164();
    alpha = 0xff;
    sh = 0;
    switch (o->mode) {
    case 1:
        sh = (f32)rowH * o->t;
        break;
    case 2:
        alpha = fade(o->t);
        break;
    }
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    n = 0;
    for (i = 0, off = 0, yo = 0; i < 18; i++, off += 8) {
        it = (Slot*)((u8*)o->a5c + off + 0x12c);
        if (it != NULL && it->s != NULL && it->s->x1f != 0) {
            s16 y = o->ty + (dy + yo);
            switch (o->mode) {
            case 1:
                if (n < o->cur) {
                    o->v3C(x, y, 0, 0xff, it, o->v38(it));
                } else {
                    o->v3C(x, (s16)(y + (u8)sh), 0, 0xff, it, o->v38(it));
                }
                break;
            case 2:
                if (n != o->cur) {
                    o->v3C(x, y, 0, 0xff, it, o->v38(it));
                } else {
                    o->v3C(x, y, 0, (u8)alpha, it, o->v38(it));
                }
                break;
            default:
                o->v3C(x, y, 0, 0xff, it, o->v38(it));
                break;
            }
            yo += rowH;
            n++;
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
