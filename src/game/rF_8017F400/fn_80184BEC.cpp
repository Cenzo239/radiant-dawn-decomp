/* fn_80184BEC: framed box with two sprites and a number. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct TexH { u16 x0, x2; } TexH;
extern void* fn_80006A0C(void*, int);
extern u8* fn_800CD204(int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_8007E7E8(int);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void fn_801BC88C(void* a, int b, GXColor c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern void fn_800800D4(int);
extern void fn_80080308(void);
extern void fn_80080330(f32, f32);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080508(GXColor);
extern void fn_80080578(int);
extern void fn_80080A94(f32);
extern void fn_80080C24(const char*);
extern int fn_801D09F0(void);
extern int fn_80290DDC(char*, const char*, ...);
typedef struct BoxD { u8 pad[0x50]; int x50; u8 pad54[0x60-0x54]; void* arch; } BoxD;
extern char lbl_8036BC00[];
static inline void Fill(f32 x, f32 y, f32 w, f32 h, int r, int g, int b, int a) {
    fn_800800D4(2);
    fn_80080388(x, y, w, h);
    fn_800804D4(r, g, b, a);
    fn_80080578(0);
    fn_80080308();
}
static inline void Box(f32 x, f32 y) {
    s16 w = 0x13a, h = 0x42;
    Fill(1.0f + x, 1.0f + y, w - 2, h - 2, 0, 0, 0, 0x80);
    fn_801BCA5C(-1.0f);
    Fill(x, y, w, 1.0f, 0xff, 0xff, 0xff, 0x40);
    Fill(x, y + h - 1.0f, w, 1.0f, 0xff, 0xff, 0xff, 0x40);
    Fill(x, 1.0f + y, 1.0f, h - 2, 0xff, 0xff, 0xff, 0x40);
    Fill(x + w - 1.0f, 1.0f + y, 1.0f, h - 2, 0xff, 0xff, 0xff, 0x40);
}
static inline GXColor mk(const u8* p, u8 a) { GXColor c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
static inline void DrawC(void* arch, int tile, GXColor c, f32 x, f32 y, f32 w, f32 h) {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void Tile(void* arch, int tile, f32 x, f32 y) {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    DrawC(arch, tile, mk(fn_800CD204(1), 0xFF), x, y, w, h);
}
void fn_80184BEC(BoxD* p, f32 x, f32 y) {
    char buf[0x10];
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    Box(x, y);
    Tile(p->arch, 2, 18.0f + x, 14.0f + y);
    Tile(p->arch, 3, 276.0f + x, 16.0f + y);
    fn_80290DDC(buf, lbl_8036BC00, p->x50);
    fn_801BCA94();
    fn_800800D4(5);
    if (fn_801D09F0() == 0) fn_80080330(150.0f + x, 14.0f + y);
    else fn_80080330(172.0f + x, 14.0f + y);
    fn_800804D4(0xd2, 0xb4, 0x6c, 0xff);
    fn_80080A94(1.5f);
    fn_80080C24(buf);
    fn_801BCA5C(2.0f);
}
}
