/* fn_8017FE30: trail ribbon and arrow head draw. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct Trail { u8 r, g, b, a; u8 pad4[2]; s16 x6; u8 count; u8 pad9; s16 n; f32 xc; u8 pad10[0x220 - 0x10]; Vec pts[(0x1a38 - 0x220) / 12]; Vec dirs[1]; } Trail;
union WG { volatile u8 u8v; volatile f32 f32v; };
#define GX (*(WG*)0xCC008000)
extern void* lbl_804CB900;
extern char lbl_8036B62C[];
extern void* fn_8001D3B4(const char*);
extern void fn_80021B68(int);
extern void fn_803128AC(f32*, f32, f32, f32);
extern f32* fn_8000FB88(void);
extern void fn_80312378(f32*, f32*, f32*);
extern void fn_80307E48(f32*, int);
extern void fn_80021784(int);
extern void fn_80021958(int, const GXColor*);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80021C34(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_80304314(int, int, u16);
static inline void pos3(f32 x, f32 y, f32 z) { GX.f32v = x; GX.f32v = y; GX.f32v = z; }
static inline void col4(u8 r, u8 g, u8 b, u8 a) { GX.u8v = r; GX.u8v = g; GX.u8v = b; GX.u8v = a; }
static inline u8 C8(int v) { return (u8)v; }
void fn_8017FE30(Trail* t) {
    /*P*/
    Vec* pp;
    Vec* dp;
    f32 sz;
    int a;
    int i;
    int cr;
    int cg;
    int cb;
/*E*/
    f32 mtx[3][4];
    if (t->count == 0) return;
    if (0.0f == t->xc) return;
    if (t->n == 0) return;
    if (lbl_804CB900 == 0) lbl_804CB900 = fn_8001D3B4(lbl_8036B62C);
    fn_80021B68(0);
    fn_803128AC(mtx[0], 0.0f, 0.0f, -0.01f);
    fn_80312378(fn_8000FB88(), mtx[0], mtx[0]);
    fn_80307E48(mtx[0], 0);
    fn_80021784(0);
    {
    GXColor c = { 0xff, 0xff, 0xff, 0xff };
    fn_80021958(4, &c);
    }
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021B2C(1);
    fn_80021BF4(1);
    fn_80021CB4(0, 0xff, 0xff, 4);
    fn_80021EF8(0, 4);
    fn_80021C34(0);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xb, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xb, 1, 5, 0);
    pp = t->pts;
    sz = 0.3f;
    dp = t->dirs;
    a = t->a;
    if (t->x6 > 0) {
        f32 v = fn_8001EF30(255.0f, 0.0f, 30.0f, t->x6);
        a = a * v / 255.0f;
    }
    fn_80304314(0x98, 0, t->n * 2);
    for (i = 0; i < t->n; i++) {
        cr = fn_8001EF30(t->r, 255.0f, t->n - 1, i);
        cg = fn_8001EF30(t->g, 255.0f, t->n - 1, i);
        cb = fn_8001EF30(t->b, 255.0f, t->n - 1, i);
        pos3(dp->x * sz + pp->x, dp->y * sz + pp->y, pp->z);
        col4(cr, cg, cb, C8(a));
        pos3(pp->x - dp->x * sz, pp->y - dp->y * sz, pp->z);
        col4(cr, cg, cb, C8(a));
        pp++;
        dp++;
    }
    {
    t = (Trail*)((u8*)t + (t->n - 1) * 12);
#define q t
    fn_80304314(0x90, 0, 9);
    const f32 k = 2.0f;
#define V(X, Y) pos3(X, Y, q->pts[0].z); col4(0xff, 0xff, 0xff, a);
    V(q->dirs[0].x * sz + q->pts[0].x, q->dirs[0].y * sz + q->pts[0].y)
    V(q->pts[0].x - q->dirs[0].x * sz, q->pts[0].y - q->dirs[0].y * sz)
    V(q->pts[0].x + k * (q->dirs[0].y * sz), q->pts[0].y - k * (q->dirs[0].x * sz))
    V(q->pts[0].x - q->dirs[0].x * sz, q->pts[0].y - q->dirs[0].y * sz)
    V(q->pts[0].x - k * (q->dirs[0].x * sz), q->pts[0].y - k * (q->dirs[0].y * sz))
    V(q->pts[0].x + k * (q->dirs[0].y * sz), q->pts[0].y - k * (q->dirs[0].x * sz))
    V(q->dirs[0].x * sz + q->pts[0].x, q->dirs[0].y * sz + q->pts[0].y)
    V(q->pts[0].x + k * (q->dirs[0].y * sz), q->pts[0].y - k * (q->dirs[0].x * sz))
    V(q->pts[0].x + k * (q->dirs[0].x * sz), q->pts[0].y + k * (q->dirs[0].y * sz))
    }
}
}
