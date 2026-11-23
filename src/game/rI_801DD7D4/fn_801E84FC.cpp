#include "game/rI_801DD7D4/types.h"
extern "C" {
int fn_800CB0FC(int, f32);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
void fn_8007E7B4(void);
void fn_800712E8(int, int, int);
}
struct W { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual int v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(s16, s16, s16, s16, int);
  u8 p4[0xe]; s16 x12, x14, x16, x18; u8 p1a[4]; s16 x1e, x20; u8 p22[0x2f]; u8 x51; s16 x52, x54; u8 p56[4]; s16 x5a, x5c, x5e; u8 p60[4]; s16 x64; };
extern "C" void fn_801E84FC(W* o) {
/*P*/
    int w;
    s16 h;
    s16 x;
    int yy;
    int ty;
    s16 y;
/*E*/
    if (o->x51) {
        o->v18();
        fn_8007E154();
        fn_8007E720(-0.5f);
        fn_8007E164();
        w = o->v44();
        {
        s16 cols = o->x5c;
        s16 cur = o->x54;
        s16 top = o->x5a;
        h = o->x5e;
        { int m = w * (s16)(cur % cols); x = m + o->x1e; }
        { int m2 = h * (s16)((s16)(cur / cols) - top); y = m2 + o->x20; }
        }
        {
        int fh = fn_800CB0FC(-1, 1.0f);
        yy = o->x64 + y;
        s16 d = (h - fh) >> 1;
        ty = d + yy;
        if (ty >= o->x20 && (s16)(o->x18 - o->x14) - o->x20 >= h + yy - d) {
            fn_8007E154();
            fn_8007E7E8(0x40);
            fn_8007E164();
            fn_800712E8(x, ty, 0);
            fn_8007E154();
            fn_8007E720(2.0f);
            fn_8007E164();
            o->v58(x - o->x1e, yy, w, h, 0);
        }
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7E8(0x80);
    fn_8007E164();
}
