/* fn_8019A82C: difficulty select window draw. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct DEnt { s16 flags; s16 x2; s16 x4; s16 x6; s16 x8; s16 xa; s16 xc; u8 pade[0x1a-0xe]; s16 x1a; f32 x1c; void* x20; void* x24; } DEnt;
typedef struct TexH { u16 x0, x2; } TexH;
typedef struct Sys { u8 pad[0x20]; u32 x20; } Sys;
extern void* lbl_804CB92C;
extern char lbl_80388874[];
extern void* fn_80006A0C(void*, int);
extern u8* fn_800CD204(int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void fn_801BC88C(void* a, int b, GXColor c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB278(s16, s16, int, const char*, ...);
extern char* fn_800D0864(const char*);
extern Sys* fn_8024BC94(void);
extern void fn_800800D4(int);
extern void fn_80080308(void);
extern void fn_80080330(f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080508(GXColor);
extern void fn_80080B00(int, void*, f32);
extern void fn_80080C24(const char*);
extern void* memcpy(void*, const void*, u32);
extern void fn_80075124(int, int, int, int);
extern void fn_8017918C(void*, int, int);
extern void fn_80179214(void*);
static inline GXColor mk(const u8* p, u8 a) { GXColor c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
static inline void DrawC(void* arch, int tile, GXColor c, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(lbl_804CB92C, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void Sprite2(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    DrawC(lbl_804CB92C, tile, mk(fn_800CD204(col), alpha), fl, x, y, w, h);
}
void fn_8019A82C(DEnt* e) {
    /*P*/
    Sys* sys;
    f32 w;
    f32 h;
    f32 hw;
    f32 hh;
    int tw;
    int cnt;
    int i;
    char* p;
    char* start;
    char* dst;
    int n;
    char* s;
    char* s2;
    int tw2;
    int j;
/*E*/
    char lines[7][0x41];
    w = 416.0f;
    h = 343.0f;
    hw = 0.5f * w;
    hh = 0.5f * h;
    sys = fn_8024BC94();
    if (!(e->flags & 1)) return;
    fn_8007E154();
    fn_8007E4E4(e->x6 + hw, e->x8 + hh, 120.0f, e->x1c);
    fn_8007E164();
    fn_801BCA5C(-9.0f);
    Sprite2(1, 0xFF, 0x14, 0, -hw, -hh, w, h);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    s = fn_800D0864(lbl_80388874);
    tw = fn_800CA3DC(s, -1, 1.0f);
    {f32 q = tw/2; int x = 208.0f + -hw - q; fn_800CB278(x, 30.0f + -hh, 8, s);}
    {
    const char* t[3] = { "FM_NORMAL", "FM_HARD", "FM_MANIAC" };
    for (i = 0; i < 3; i++) {
        s2 = fn_800D0864(t[i]);
        fn_800800D4(5);
        tw2 = fn_800CA3DC(s2, -1, 1.0f);
        {f32 m = tw2/2; fn_80080330(85.0f + -hw + i*0x73 - m, 80.0f + -hh);}
        if (i == 2 && !(sys->x20 & 4)) fn_800804D4(0x5a, 0x50, 0x40, 0xff);
        else fn_80080508(*(GXColor*)fn_800CD204(8));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        fn_80080C24(s2);
        fn_80080308();
    }
    }
    {
    const char* t2[3] = { "FM_NORMAL_EX", "FM_HARD_EX", "FM_MANIAC_EX" };
    p = fn_800D0864(t2[e->x1a]);
    start = p;
    dst = lines[0];
    n = 0;
    cnt = 0;
    for (;;) {
        if (*p == 0 || *p == '\n') {
            if (n > 0) memcpy(dst, start, n);
            dst[n] = 0;
            dst += 0x41;
            cnt++;
            if (*p == 0) break;
            p++;
            n = 0;
            start = p;
        } else {
            p++;
            n++;
        }
    }
    }
    for (j = 0; j < cnt; j++) {
        fn_800CB278(40.0f + -hw, 140.0f + -hh + j * 24, 8, lines[j]);
    }
    fn_801BCA5C(10.0f);
    if (e->x2 == 3) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 120.0f, 1.0f);
        fn_8007E164();
        fn_801BCA5C(-11.0f);
        fn_80075124(e->xa - 0x37, e->xc - 0xe, 0x6e, 0x1c);
        fn_801BCA5C(11.0f);
        fn_8017918C(e->x20, e->xa - 0x37, e->xc);
        fn_8017918C(e->x24, e->xa + 0x37, e->xc);
        fn_80179214(e->x20);
        fn_80179214(e->x24);
    }
}
}
