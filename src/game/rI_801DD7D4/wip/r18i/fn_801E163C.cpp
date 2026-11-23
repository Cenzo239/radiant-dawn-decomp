/* WIP (round 18): class `other`, 111 of 112 instructions: the known colour-copy puzzle (the original
   takes the temporary's address into r4 before the byte copy and passes it with `mr r3,r4`; ours
   computes it once, after the copy). Same shape as wip/r13b/fn_8021F0E0.cpp. */
/* fn_801E163C: draw of a one-line text label, vertically centred, clipped to the widget. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
void fn_8007E74C(void (*)(void*, void*), void*);
void fn_8007E7B4(void);
int fn_800CB0FC(f32, int);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080330(f32, f32);
void fn_80080508(C4*);
void fn_80080C24(const char*);
void fn_801E2204(void*, void*, void*);
void fn_801E2104(void* p, void* arg);
}
struct XY { s16 x, y; };
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual C4* v34(); virtual int v38(); virtual int v3C();
    virtual const char* v40(); virtual int v44();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; void* parent; u8 p40[8]; XY a48; XY a4c;
};
static inline void setR(MV* o, s16 a, s16 b, s16 c, s16 d) { o->a48.x = a; o->a48.y = b; o->a4c.x = c; o->a4c.y = d; }
static inline C4* cp(C4* d, const C4* s) { d->r = s->r; d->g = s->g; d->b = s->b; d->a = s->a; return d; }
extern "C" void fn_801E163C(MV* o, void* a) {
    s16 x, y;
    s16 h;
    const char* s;
    o->v18(a);
    x = o->tx;
    y = o->ty;
    h = o->v44();
    y = y + ((h - fn_800CB0FC(1.0f, -1)) >> 1);
    s = o->v40();
    if (s != NULL) {
        C4 k;
        setR(o, 0, 0, o->ix1 - o->ix0, o->iy1 - o->iy0);
        fn_801E2204(o, &o->a48, &o->a48);
        fn_801E2204(o, &o->a4c, &o->a4c);
        fn_8007E154();
        fn_8007E74C(fn_801E2104, &o->a48);
        fn_8007E720(-1.0f);
        fn_8007E174(0, (u16)(o->flags | 3));
        fn_8007E164();
        fn_800800D4(5);
        fn_80080330(x, y);
        fn_80080508(cp(&k, o->v34()));
        fn_80080C24(s);
        fn_80080308();
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
    }
}
