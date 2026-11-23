#include "hdr.h"
extern "C" {
extern char lbl_8036EF28[];
extern C4 lbl_804CF9CC;
s8 fn_8012401C(void*);
s8 fn_80124144(void*);
s8 fn_8012408C(void*);
int fn_8012C250(void*, u8);
int fn_800CEABC(u8);
const char* fn_801113DC(s16);
}
struct UF { u8 p[0xd0]; s16 a[12]; };
struct UO { u8 p[0xf0]; UF* xf0; };
class WO { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(void*); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual int v30(); virtual int v34();
  u32 x4; u8 p8[0xa]; s16 x12, x14, x16, x18; u8 p1a[4]; s16 x1e, x20; u8 p22[0x38 - 0x22]; u32 x38; u8 p3c[4]; UO* x40; u8 p44[2]; s16 x46, x48, x4a, x4c; };
static inline void ZS(WO* o) { fn_8007E154(); fn_8007E174(0, (u16)(o->x38 | 3)); fn_8007E164(); }
#define TXT(x, y, s) fn_800CB3A8((s16)(x), (s16)(y), 0x1d, 1, 0, 1.0f, 0.0f, fn_800D0864(s))
static inline void row(s16 x, int y0, const char* s, s8 (*f)(void*), UO* u) {
    int y = y0 - 2;
    TXT(x + 0x8e, y, s);
    fn_800800D4(5);
    fn_80080ABC(1, 2.0f);
    fn_80176F7C(x + 0xee, y, 0, 0, f(u));
    fn_80080308();
}
extern "C" void fn_801EB490(WO* o, void* a) {
/*P*/
    int yb;
    int w;
    int dy2;
    int dy;
    UO* u;
    s16 x;
    int i;
    int yy;
    int h;
    int n;
    int e;
    int y1;
    int rx;
    int ry;
    const char* base;
/*E*/
    u = o->x40;
    o->v34();
    o->v18(a);
    {
    s16 hh = o->x18 - o->x14;
    s16 ww = o->x16 - o->x12;
    o->x46 = 0;
    o->x48 = 0;
    o->x4a = ww;
    o->x4c = hh;
    }
    fn_801E2204(o, &o->x46, &o->x46);
    fn_801E2204(o, &o->x4a, &o->x4a);
    fn_8007E154();
    fn_8007E74C(fn_801E2104, &o->x46);
    fn_8007E164();
    ALPHA(-1.0f);
    x = o->x1e;
    yb = o->x20;
    h = o->v30();
    dy = ((s16)h - fn_800CB0FC(-1, 1.0f)) >> 1;
    dy2 = ((s16)h - FONT->v50()) >> 1;
    ZS(o);
    fn_800800D4(5);
    y1 = yb + dy;
    fn_80080330(x, y1);
    fn_80080508(lbl_804CF9CC);
    fn_80080ABC(1, 2.0f);
    base = lbl_8036EF28;
    fn_80080C24(fn_800D0864(base + 0x55));
    fn_80080308();
    row(x, y1, base + 0x5e, fn_8012401C, u);
    yy = yb + h;
    row(x, (s16)yy + dy, base + 0x67, fn_80124144, u);
    yy += h;
    row(x, (s16)yy + dy, base + 0x6e, fn_8012408C, u);
    yy = (s16)(h + o->x20);
    n = 0;
    for (i = 0; i < 12; i++) {
        w = fn_8012C250(u, i);
        if ((s16)w == 0) continue;
        if (n >= 4) break;
        ry = (s16)(yy + h * (n >> 1));
        rx = (s16)(x + (n & 1) * 0x39);
        e = u->xf0->a[(u8)i];
        FONT->v18(rx + 4, ry + dy2, (u16)fn_800CEABC(i));
        ZS(o);
        fn_800800D4(5);
        fn_80080ABC(1, 2.0f);
        {
            int ci = 1;
            if (e <= (s16)w) ci = 0x27;
            fn_80080508(*fn_800CD204(ci));
        }
        fn_80176EA8(rx + 0x2c, ry + dy, 2, fn_801113DC(w));
        fn_80080308();
        n++;
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
