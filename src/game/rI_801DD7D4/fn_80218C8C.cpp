#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
void fn_8007E720(f32);
void fn_8007E7E8(int);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
void fn_800CB3A8(f32, f32, int, int, int, int, int, const char*, ...);
void fn_800800D4(int);
void fn_80080ABC(int, f32);
void fn_80176F7C(int, int, int, int, int);
void fn_80080308(void);
C4* fn_800CD204(int);
void fn_80080508(C4);
void fn_80176EA8(int, int, int, const char*);
void fn_80080B00(int, void*, f32);
void fn_801D9E24(int, int, int, int);
void fn_801D8ADC(int, int, int, int);
int fn_8028DB44(int);
void fn_800712E8(int, int, int);
extern char lbl_80371974[];
extern int lbl_804CAA68;
class LW { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(int); virtual int v30(); virtual s16 v34(); virtual int v38(); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(); virtual int v64();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; u8 p3c[0x14]; s16 a50, a52, rowH;
};
struct Ctx { u8 p[0x2d]; u8 a2d; u8 a2e; u8 p2f[5]; int a34; struct { u8 p[8]; void* a8; }* a38; };
static inline int mn(const int& a, const int& b) { return *(b < a ? &b : &a); }
void fn_80218C8C(LW* o, int x, int y, s8 k, const char* name, int n, int d, int e) {
/*P*/
    s16 w;
    s16 h;
    int off;
    int ty;
    int rx;
    const char* s;
    s16 sw;
/*E*/
    w = o->ix1 - o->ix0;
    h = o->rowH;
    off = (h - fn_800CB0FC(1.0f, -1)) >> 1;
    s = fn_800D0864(lbl_80371974 + 0xce);
    sw = fn_800CA3DC(1.0f, s, -1);
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    ty = y + off;
    fn_800CB3A8(1.0f, 0.0f, (s16)(x + 8), (s16)ty, 0x1d, 1, 0, fn_800D0864(name));
    fn_800800D4(5);
    fn_80080ABC(1, 2.0f);
    fn_80176F7C(x + 0x80, ty, 0, 0, n);
    fn_80080308();
    fn_800800D4(5);
    fn_80080508(*fn_800CD204(0x1e));
    rx = x + w;
    fn_80176EA8(rx - o->tx, ty, 0, s);
    fn_80080308();
    fn_800800D4(5);
    {
        int ci = 0x1f;
        if (e > 0) ci = 0x23;
        fn_80080508(*fn_800CD204(ci));
    }
    fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
    fn_80176F7C(rx - o->tx - sw - 3, ty, 0, 0, e);
    fn_80080308();
    fn_800800D4(5);
    fn_80080ABC(1, 2.0f);
    fn_80080508(*fn_800CD204((u8)(d > 0 ? 4 : (d < 0 ? 3 : 1))));
    {
        int t = n + d;
        switch (k) {
        case 0: if (t < 1) t = 1; break;
        case 1: if (t < 1) t = 1; break;
        case 2: if (t < 0) t = 0; break;
        case 3: if (t < 1) t = 1; break;
        }
        fn_80176F7C(x + 0xdc, ty, 0, 0, mn(t, lbl_804CAA68));
    }
    fn_80080308();
    fn_8007E154();
    fn_8007E720(0.1f);
    fn_8007E164();
    fn_801D9E24((s16)(x + 0xa8), (s16)(y + ((h - 0x1a) >> 1)), o->v34() == k, 0x10);
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E164();
    fn_801D8ADC(x, (s16)(y + h - 0xa), 0x88, 0x10);
}
static inline BOOL ctxBusy(Ctx* c) { BOOL b = FALSE; if (c->a2d != 0 || c->a2e != 0) b = TRUE; return b; }
static inline void* ctxTop(Ctx* c) { return c->a34 != 0 ? c->a38->a8 : NULL; }
struct E28 { void* vt; u8 p4[8]; u8 ac; u8 pd; s16 x, y, z; u8 p14[0x14]; };
class EV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(u32); };
struct LE { u8 p[0x118]; E28 e[4]; };
void fn_8021991C(LW* o, Ctx* c) {
/*P*/
    int x1;
    int sel;
    int x0;
    s16 hh;
    s16 tx;
    s16 ax;
    s16 ay;
    s16 y;
    s16 h;
    int i;
    s16 yy;
/*E*/
    LE* l = (LE*)o;
    o->v18(c);
    h = o->rowH;
    i = ((VO0N*)o)->v34();
    tx = o->tx;
    y = o->ty;
    switch ((s16)i) {
    case 0: case 1: case 2: case 3:
        y += i * h;
        break;
    case 4: y = 0x98; break;
    case 5: y = 0xc4; break;
    case 6: y = 0xe5; break;
    }
    ax = o->a50;
    if (ax == -0x8000 || (ay = o->a52) == -0x8000 || (fn_8028DB44(ax - tx) <= 1 && fn_8028DB44(ay - y) <= 1)) {
        o->a50 = tx;
        o->a52 = y;
    } else {
        o->a50 = (ax + tx + 1) >> 1;
        o->a52 = (y + o->a52 + 1) >> 1;
    }
    if (((VO0N*)o)->v3C() != 0) {
        sel = 0;
        if (!ctxBusy(c)) { if (ctxTop(c) == o) sel = 1; }
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        {
            hh = o->rowH;
            fn_800712E8(o->a50, o->a52 + ((hh - fn_800CB0FC(1.0f, -1)) >> 1), sel);
        }
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
    {
        { int m = h * i; yy = m + o->ty; }
        switch ((s16)i) {
        case 0: case 1: case 2: case 3: {
            int cy = yy + (h >> 1);
            l->e[0].ac = 1;
            l->e[1].ac = 1;
            l->e[2].ac = 0;
            l->e[3].ac = 0;
            l->e[0].x = 0xb2; l->e[0].y = cy; l->e[0].z = 0;
            l->e[1].x = 0xf2; l->e[1].y = cy; l->e[1].z = 0;
            break;
        }
        case 4: {
            l->e[0].ac = 0;
            l->e[1].ac = 0;
            l->e[2].ac = 1;
            l->e[3].ac = 1;
            x0 = o->tx;
            l->e[3].x = x0 + ((VO0N*)o)->v64() * 0xe + 0x4d;
            l->e[3].y = 0x98;
            l->e[3].z = 0;
            x1 = o->tx;
            l->e[2].x = x1 + ((VO0N*)o)->v64() * 0xe + 0x4d;
            l->e[2].y = h + 0x98;
            l->e[2].z = 0;
            break;
        }
        default:
            l->e[0].ac = 0;
            l->e[1].ac = 0;
            l->e[2].ac = 0;
            l->e[3].ac = 0;
            break;
        }
    }
    ((EV*)&l->e[0])->v2C(o->flags);
    ((EV*)&l->e[1])->v2C(o->flags);
    ((EV*)&l->e[2])->v2C(o->flags);
    ((EV*)&l->e[3])->v2C(o->flags);
}
}
