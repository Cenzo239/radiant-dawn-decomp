#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
int fn_8028DB44(int);
void fn_801D6F1C(s16, s16, s16, s16, u32, const C4&);
struct P3 { u8 p[0x70]; int a70; };
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; P3* a3c; u8 p40[0xc]; s16 a4c, a4e, a50, a52;
};
static inline void box(MV* o, s16 x, s16 y, const C4& k2) {
    s16 x2 = x + 0x30;
    s16 y2 = y + 0x30;
    fn_801D6F1C(x, y - 1, x2, y - 1, o->flags, k2);
    fn_801D6F1C(x, y2, x2, y2, o->flags, k2);
    fn_801D6F1C(x - 1, y, x - 1, y2, o->flags, k2);
    fn_801D6F1C(x2, y, x2, y2, o->flags, k2);
    fn_801D6F1C(x, y, x2, y, o->flags, k2);
    fn_801D6F1C(x, y2 - 1, x2, y2 - 1, o->flags, k2);
    fn_801D6F1C(x, y, x, y2, o->flags, k2);
    fn_801D6F1C(x2 - 1, y, x2 - 1, y2, o->flags, k2);
}
void fn_8022ADF0(MV* o) {
/*P*/
    int r;
    int cw;
    s16 tx;
    s16 ty;
    int ch;
    int on;
    int cx;
    s16 cy;
    int k;
    s16 xd;
    s16 yd;
/*E*/
    o->v18();
    cx = o->a4c;
    cy = (s16)(o->a4e - o->v38());
    cw = o->v30();
    ch = o->v34();
    tx = cx * cw;
    ty = cy * ch;
    r = o->a50;
    if ((r == -0x8000 && o->a52 == -0x8000) || (fn_8028DB44(r - tx) <= 1 && fn_8028DB44(o->a52 - ty) <= 1)) {
        o->a50 = tx;
        o->a52 = ty;
    } else {
        o->a50 = (r + tx) >> 1;
        o->a52 = (o->a52 + ty) >> 1;
    }
    xd = o->a50;
    yd = o->a52;
    on = o->a3c->a70 == 1;
    if (on) {
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        {
            C4 k2;
            k2.r = 0x9c;
            k2.g = 0x2f;
            k2.b = 0x12;
            k2.a = on ? 0xff : 0x80;
            box(o, xd + (((s16)cw - 0x30) >> 1), yd + (((s16)ch - 0x30) >> 1), k2);
        }
    }
}
}
