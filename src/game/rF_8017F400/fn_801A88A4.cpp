#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
struct Holder { u8 pad[0xEC]; void* xEC; };
struct Win { u8 pad[0x10]; int x10; Holder* x14; void* arch; u8 p1C[0x12C]; int x148; };
extern s8 lbl_804CB968;
extern s16 lbl_804CB970[4];
extern void fn_801A7D34(void* p, void* arg);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void* fn_80006A0C(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E7B4(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void (*)(void*, void*), s16*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_800C4DDC(int, int, int, p32arg);
#else
extern void fn_800C4DDC(int, int, int, int);
#endif
extern const char* fn_80118C44(void*);
extern void fn_801C6DA0(f32, f32, int, const char*);

static inline void Tile(Win* p, int tile, f32 x, f32 y, f32 ax, f32 ay, f32 sx, f32 sy) {
    C4 t;
    C4 c;
    const u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF;
    TexH* q = *(TexH**)fn_80006A0C(p->arch, tile);
    f32 w = q->x2;
    f32 h = q->x0;
    f32 x1 = ax * (0.5f * w) + x;
    f32 y1 = ay * (0.5f * h) + y;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(p->arch, tile, &t, 0x11, 0, x1, y1, w * sx + x1, h * sy + y1, 0.0f, 0.0f, w, h);
}

void fn_801A88A4(Win* p, f32 x, f32 y) {
/*P*/
    int t1;
    int t2;
    int a;
    const char* s;
    int c;
    int d;
    int b;
/*E*/
    if (!lbl_804CB968) {
        lbl_804CB970[0] = (int)(x - 128.0f);
        lbl_804CB970[1] = 0;
        lbl_804CB970[2] = 0x10C;
        lbl_804CB970[3] = 0x1C0;
        lbl_804CB968 = 1;
    }
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E74C(fn_801A7D34, lbl_804CB970);
    fn_8007E164();
    fn_800C4DDC((int)x, (int)y, 0xFF, p->x148);
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    {
    int m = p->x10;
    if (m == 0) { t1 = 8; t2 = 9; a = (int)(x - 195.0f); b = (int)(y - 10.0f); c = (int)(75.0f + x); d = (int)(y - 149.0f); }
    if (m == 1) { t1 = 10; t2 = 11; a = (int)(x - 196.0f); b = (int)(y - 8.0f); c = (int)(76.0f + x); d = (int)(y - 147.0f); }
    if (m == 2) { t1 = 12; t2 = 13; a = (int)(11.0f + (x - 200.0f)); b = (int)y; c = (int)(11.0f + (47.0f + x)); d = (int)(y - 140.0f); }
    }
    fn_801BCA5C(-10.0f);
    Tile(p, t1, a, b, 0.0f, 0.0f, 1.0f, 1.0f);
    fn_801BCA5C(-1.0f);
    Tile(p, t2, c, d, 0.0f, 0.0f, 1.0f, 1.0f);
    s = fn_80118C44(p->x14->xEC);
    if (p->x10 != 2) {
        Tile(p, 1, x - 98.0f, 2.0f + y, 0.0f, 0.0f, 1.0f, 1.0f);
        fn_801BCA5C(-1.0f);
        fn_801BCA94();
        fn_801C6DA0(x - (f32)(fn_800CA3DC(s, -1, 1.0f) / 2), 7.0f + y, 0x39, s);
    } else {
        fn_801BCA5C(-1.0f);
        fn_801BCA94();
        fn_800CB3A8(1.0f, 0.0f, (x - 3.0f) - (f32)(fn_800CA3DC(s, -1, 1.0f) / 2), 18.0f + y, 0x3A, 1, 0, s);
    }
    fn_801BCA5C(13.0f);
}
}
