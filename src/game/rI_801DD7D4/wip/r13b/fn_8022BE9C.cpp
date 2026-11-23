#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
int fn_8028DB44(int);
int fn_8017F990(int, int);
double fn_80295940(double);
void fn_801D6F1C(s16, s16, s16, s16, u32, const C4&);
struct Ctx { u8 p[0x34]; int a34; struct { u8 p[8]; void* a8; }* a38; };
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(void*); virtual int v18(void*);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; void* a3c; u8 p40[0x34]; s16 a74, a76, a78;
};
void fn_8022BE9C(MV* o, Ctx* c) {
/*P*/
    s16 cur;
    s16 v78;
    s16 x;
    s16 y;
    s16 t;
    s16 x2;
    s16 y2;
    void* cu;
    void* me;
    f32 f;
/*E*/
    o->v18(c);
    fn_8007E154();
    fn_8007E720(-0.2f);
    fn_8007E164();
    t = o->a74 * 0xe;
    cur = o->a76;
    if (cur == -0x8000 || (v78 = o->a78) == -0x8000 || (fn_8028DB44(cur - t) <= 1 && fn_8028DB44(v78) <= 1)) {
        o->a76 = t;
        o->a78 = 0;
    } else {
        o->a76 = (cur + t) >> 1;
        o->a78 = o->a78 >> 1;
    }
    x = o->a76;
    y = o->a78;
    fn_8007E154();
    fn_8007E720(0.1f);
    fn_8007E164();
    me = o->a3c;
    if (c->a34 != 0) cu = c->a38->a8;
    else cu = NULL;
    f = fn_8017F990(0, 0x1f4) / 500.0f;
    if (cu == me) f = 0.5f * (f32)fn_80295940(6.2831855f * f) + 0.5f;
    else f = 1.0f;
    {
        C4 k;
        k.r = 0x9c;
        k.g = 0x80;
        k.b = 0x12;
        k.a = 255.9f * f;
        x2 = x + o->tx;
        y2 = (s16)(y + o->ty) + 0x19;
        fn_801D6F1C(x2, y2 - 1, x2 + 0xe, y2 - 1, o->flags, k);
        fn_801D6F1C(x2, y2, x2 + 0xe, y2, o->flags, k);
    }
}
}
