#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
int fn_800CA7A4(f32, const char*, int);
void fn_800CB3A8(f32, f32, int, int, int, int, int, const char*, ...);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080508(C4);
void fn_80080ABC(int, f32);
void fn_80080A94(f32);
void fn_800804F4(u8);
C4* fn_800CD204(u8);
void fn_80176F7C(int, int, int, int, int);
void fn_80291CEC(int, char*, int);
void fn_801D8ADC(s16, s16, s16, int);
struct MV { void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; u8 p3c[0x18]; s16 a54; u8 p56[0x1e]; u8 a74; u8 p75[3]; f32 a78[4]; };
static inline int cm(int d) { if (d > 0) return 4; if (d < 0) return 3; return 1; }
void fn_8021A8F4(MV* o, int i, int x, int y, const char* l, int v, int d) {
    char buf[8];
/*P*/
    int yy;
    int xx;
    int m;
    s16 w;
    int c1;
    int dw;
    int dh;
    f32* fp;
    int t;
    int t2;
    int ty;
/*E*/
    ty = o->a54;
    w = (s16)(o->ix1 - o->ix0) - o->tx * 2;
    ty = (ty - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    yy = y + ty;
    fn_800CB3A8(1.0f, 0.0f, (s16)(x + 8), (s16)yy, 0x1d, 1, 0, fn_800D0864(l));
    fn_800800D4(5);
    fn_80080508(*fn_800CD204(cm(d)));
    fn_80080ABC(1, 2.0f);
    xx = x + w - 8;
    fn_80176F7C(xx, yy, 0, 0, v);
    fn_80080308();
    c1 = 1;
    m = c1 << i;
    if (m & o->a74) {
        fn_8007E154();
        fn_8007E720(-1.0f);
        fn_8007E164();
        fp = (f32*)((u8*)o + (u8)i * 4);
        fn_80291CEC(v, buf, 10);
        t = fn_800CA3DC(fp[0x78 / 4], buf, -1);
        dw = (s16)(t - fn_800CA3DC(1.0f, buf, -1));
        t2 = fn_800CA7A4(fp[0x78 / 4], buf, -1);
        dh = (s16)(t2 - fn_800CA7A4(1.0f, buf, -1));
        fn_800800D4(5);
        if (d > 0) c1 = 4; else if (d < 0) c1 = 3;
        fn_80080508(*fn_800CD204(c1));
        fn_80080A94(fp[0x78 / 4]);
        fn_800804F4(255.99f * (fp[0x78 / 4] - 1.0f));
        fn_80176F7C((dw >> 1) + xx, yy - (dh >> 1), 0, 0, v);
        fn_80080308();
        fn_8007E154();
        fn_8007E720(1.0f);
        fn_8007E164();
        fp[0x78 / 4] -= 0.05f;
        if (fp[0x78 / 4] <= 1.0f) {
            o->a74 &= ~m;
            fp[0x78 / 4] = 1.0f;
        }
    }
    fn_801D8ADC(x, y + o->a54 - 10, w, 0x10);
}
}
