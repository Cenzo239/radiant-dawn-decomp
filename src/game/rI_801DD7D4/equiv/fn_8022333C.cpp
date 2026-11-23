/* fn_8022333C: draw of a vertical menu's cursor (eased towards the selected row) and, when a second
   selection is pinned, a dimmed cursor on that row. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
int fn_800CB0FC(f32, int);
void fn_800712E8(int, int, int);
int fn_8028DB44(int);
}
struct Nd { u8 p[8]; void* x8; };
struct Ctx { u8 p[0x2d]; u8 x2d, x2e; u8 p2f[5]; int x34; Nd* x38; };
class Menu { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(Ctx*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C();
    virtual int v40(int, int, int, int, int);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; u8 p40[0xc]; u8 a4c, a4d; u8 p4e[2]; s16 sel, pin; s16 cx, cy; s16 rowH;
};
static inline void* front(Ctx* c) { if (c->x34 != 0) return c->x38->x8; return 0; }
static inline BOOL active(Menu* o, Ctx* c) {
    BOOL r = FALSE;
    BOOL b = FALSE;
    if (c->x2d != 0 || c->x2e != 0) b = TRUE;
    if (!b) {
        if (front(c) == o) r = TRUE;
    }
    return r;
}
static inline int gx(Menu* o) { return o->tx; }
extern "C" void fn_8022333C(Menu* o, Ctx* c) {
    s16 rowH;
    int x;
    s16 y;
    o->v18(c);
    if (o->sel >= 0) {
        s16 cx;
        rowH = o->rowH;
        cx = o->cx;
        y = o->sel * rowH + o->ty;
        x = gx(o);
        if ((cx == -0x8000 && o->cy == -0x8000) || (fn_8028DB44(cx - x) <= 1 && fn_8028DB44(o->cy - y) <= 1)) {
            o->cx = x;
            o->cy = y;
        } else {
            o->cx = (cx + x + 1) >> 1;
            o->cy = (y + o->cy + 1) >> 1;
        }
        if (o->a4c) {
            BOOL act = active(o, c);
            s16 h;
            fn_8007E154();
            fn_8007E720(-2.0f);
            fn_8007E164();
            h = o->rowH;
            fn_800712E8(o->cx, o->cy + ((h - fn_800CB0FC(1.0f, -1)) >> 1), act);
            fn_8007E154();
            fn_8007E720(1.0f);
            fn_8007E164();
            o->v40(0, y, (s16)(o->ix1 - o->ix0), rowH, act);
        }
    }
    if (o->a4d) {
        s16 y2;
        s16 h;
        int d;
        o->v18(c);
        fn_8007E154();
        fn_8007E720(-1.0f);
        fn_8007E164();
        y2 = o->pin * rowH + o->ty;
        h = o->rowH;
        d = (h - fn_800CB0FC(1.0f, -1)) >> 1;
        fn_8007E154();
        fn_8007E7E8(0x40);
        fn_8007E164();
        fn_800712E8((s16)x, y2 + d, 0);
        fn_8007E154();
        fn_8007E7E8(0x80);
        fn_8007E164();
    }
}
