#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "MMR_NAVI_SELECT"; p[1] = "%s%s %s%s %s%s"; p[2] = "MMR_SELECT"; p[3] = "MMR_END"; p[4] = "MMR_PLAY";
}
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
struct Ent { s16 x, y, z; };
typedef struct SData {
    u32 x0; int x4; s16 x8, xA, xC, xE; s16 x10, x12, x14, x16, x18; u8 p1A[2];
    f32 x1C; s16 x20, x22, x24, x26; u8 p28[2]; Ent ent[11]; u8 p6C_[0x6C - 0x2A - 66];
    void* arch; char buf[0x60]; void* xD0;
} SData;
struct Row { u32 x0; const char* x4; u8 x8; };
extern SData* lbl_804CB98C;
extern s8 lbl_804CB990;
extern s16 lbl_804CB998[4];
extern Row lbl_80389010[];
extern void fn_801AA1B4(void* p, void* arg);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void* fn_80006A0C(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern void fn_800CB278(int, s16, int, const char*, ...);
extern const char* fn_800D0864(const char*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_8007E7B4(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void (*)(void*, void*), s16*);
#endif
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);
extern void fn_80070688(f32, f32, f32, f32);
extern int fn_801D09F0(void);
extern void fn_80072ACC(int, int, int, int, int, int, int);
extern void fn_800712E8(int, int, int);
#if TARGET_PC
extern FE10_PROTO char * fn_800CEB4C(void);
extern FE10_PROTO char * fn_800CEC24(void);
extern FE10_PROTO char * fn_800CF3A4(void);
#else
extern int fn_800CEB4C(void);
extern int fn_800CEC24(void);
extern int fn_800CF3A4(void);
#endif
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_801C6D9C(char*, int, int, int);
extern void fn_80179888(void*, int);
extern void fn_8017985C(void*, int);
extern void fn_80179864(void*, int);
extern void fn_80179854(void*, f32);
extern void fn_80179A84(void*);

#define COL1(c) { const u8* cp = fn_800CD204(1); c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF; }
static inline void A1(int tile, f32 x, f32 y) {
    C4 t;
    C4 c;
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB98C->arch, tile);
    f32 w = q->x2;
    f32 h = q->x0;
    COL1(c);
    q = *(TexH**)fn_80006A0C(lbl_804CB98C->arch, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB98C->arch, tile, &t, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void A2(int tile, int x, int y) {
    C4 t;
    C4 c;
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB98C->arch, tile);
    f32 w = q->x2;
    f32 h = q->x0;
    COL1(c);
    q = *(TexH**)fn_80006A0C(lbl_804CB98C->arch, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB98C->arch, tile, &t, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void F1(int tile, int x, int y, f32 w, f32 h) {
    C4 c;
    C4 t;
    COL1(c);
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB98C->arch, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB98C->arch, tile, &t, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void F0(int tile, int xi, int yi, int w, int h) {
    f32 y = yi;
    f32 x = xi;
    C4 c;
    C4 t;
    COL1(c);
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB98C->arch, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB98C->arch, tile, &t, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void Last(int x, int y) {
    C4 c;
    C4 t;
    f32 sc, h, w;
    int tile;
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB98C->arch, lbl_80389010[lbl_804CB98C->x4].x8);
    w = q->x2;
    h = q->x0;
    if (fn_801D09F0()) sc = 0.764f; else sc = 1.0f;
    tile = lbl_80389010[lbl_804CB98C->x4].x8;
    COL1(c);
    q = *(TexH**)fn_80006A0C(lbl_804CB98C->arch, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB98C->arch, tile, &t, 0x11, 0, 0.5f * (w * (1.0f - sc)) + x, y, w * sc + (0.5f * (w * (1.0f - sc)) + x), y + h, 0.0f, 0.0f, tw, th);
}

void fn_801AA1CC(void) {
/*P*/
    int t;
    int xx;
    int yy;
    int i;
    int bx;
    int by;
    const char* s;
/*E*/
    if (!lbl_804CB990) lbl_804CB990 = 1;
    if (lbl_804CB98C->x0 & 1) return;
    if (lbl_804CB98C->x24 > 0) {
        lbl_804CB98C->x24--;
        lbl_804CB98C->x1C = fn_8017F68C(0, lbl_804CB98C->x20, lbl_804CB98C->x22, lbl_804CB98C->x26 - lbl_804CB98C->x24, lbl_804CB98C->x26);
    }
    if (lbl_804CB98C->x10 > 0) {
        int k = 4;
        lbl_804CB98C->x10--;
        t = k - lbl_804CB98C->x10;
        lbl_804CB98C->xC = (int)fn_8017F68C(k, lbl_804CB98C->x12, lbl_804CB98C->x16, t, k);
        lbl_804CB98C->xE = (int)fn_8017F68C(k, lbl_804CB98C->x14, lbl_804CB98C->x18, t, k);
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    A1(0, 0.0f, 0.0f);
    fn_801BCA5C(-1.0f);
    A1(1, 18.0f, 16.0f);
    A1(2, 0.0f, 62.0f);
    fn_801BCA5C(-1.0f);
    s = fn_800D0864("MMR_NAVI_SELECT");
    fn_801BCA94();
    fn_800CB3A8(0.8f, 0.0f, 0x130 - fn_800CA3DC(s, -1, 0.8f) / 2, 0x43, 0x3E, 0, 0, s);
    fn_801BCA5C(2.0f);
    bx = lbl_804CB98C->x8;
    by = lbl_804CB98C->xA;
    fn_801BCA5C(-1.0f);
    {
    int w = 0x18A, h = 0xFA;
    F0(3, lbl_804CB98C->x8 + 3, lbl_804CB98C->xA + 3, w, h);
    }
    fn_801BCA5C(-1.0f);
    {
    int w = 0x190, h = 0x100;
    fn_80070688(lbl_804CB98C->x8, lbl_804CB98C->xA, w, h);
    }
    fn_801BCA5C(-1.0f);
    lbl_804CB998[0] = 0;
    lbl_804CB998[1] = by + 6;
    lbl_804CB998[2] = 0x260;
    lbl_804CB998[3] = 0xF4;
    fn_8007E154();
    fn_8007E74C(fn_801AA1B4, lbl_804CB998);
    fn_8007E164();
    for (i = 0; i < 11; i++) {
        int x = lbl_804CB98C->ent[i].x;
        int y = (int)((f32)lbl_804CB98C->ent[i].y - 30.0f * lbl_804CB98C->x1C);
        fn_801BCA94();
        fn_800CB278(x, y, 1, fn_800D0864(lbl_80389010[i].x4));
        fn_801BCA5C(1.0f);
        A2(4, x - 8, y + 0x14);
        F1(5, x - 5, y + 0x14, 212.0f, 8.0f);
        A2(6, x + 0xCF, y + 0x14);
        fn_801BCA5C(-1.0f);
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    Last(bx + 0xF8, by + 0x10);
    fn_801BCA5C(3.0f);
    fn_801BCA5C(-2.5f);
    fn_80072ACC(lbl_804CB98C->xC + 0x68, lbl_804CB98C->xE + 0xC, 0xE4, 0x17, 0x28, 0x4B, 1);
    fn_801BCA5C(2.5f);
    fn_801BCA5C(-5.0f);
    fn_800712E8(lbl_804CB98C->xC, lbl_804CB98C->xE, 1);
    fn_801BCA5C(5.0f);
    fn_80290DDC(lbl_804CB98C->buf, "%s%s %s%s %s%s", fn_800CF3A4(), fn_800D0864("MMR_SELECT"), fn_800CEC24(), fn_800D0864("MMR_END"), fn_800CEB4C(), fn_800D0864("MMR_PLAY"));
    fn_801C6D9C(lbl_804CB98C->buf, 0xFF, 0xFF, 0);
    fn_80179888(lbl_804CB98C->xD0, (int)lbl_804CB98C->x1C);
    fn_8017985C(lbl_804CB98C->xD0, 0xB);
    fn_80179864(lbl_804CB98C->xD0, 8);
    fn_80179854(lbl_804CB98C->xD0, 95.0f);
    fn_80179A84(lbl_804CB98C->xD0);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
}
