/* Config menu line draw and frame draw. StringPool is scaffolding: it sets the pool offsets and is not game code. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%s %s %s";
    p[1] = "MCFG_SELE_ITEMS";
    p[2] = "MCFG_SELE_CONTENTS";
    p[3] = "MCFG_RETURN";
}
typedef struct GXColor2 { u8 r,g,b,a; } GXColor2;
typedef struct TexH { u16 x0, x2; } TexH;
typedef struct Cfg { u8 pad[0x30]; void* arch; u8 x34; u8 pad35[7]; f32 x3c; u8 pad40[8]; u8 x48; u8 pad49[0x58-0x49]; int x58; int x5C; void* x60; u8 pad64[0x7D-0x64]; u8 x7D[1]; } Cfg;
extern u8 lbl_803881E8[];
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(u8, u8, u8, u8);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern void fn_8007E7DC(int);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void* fn_80006A0C(void*, int);
extern u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, GXColor2* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern void fn_8018732C(Cfg*);
extern void fn_8018E6B0(Cfg*);
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_801C6D9C(char*, int, int, int);
extern void fn_80179888(void*, int);
extern void fn_80179A84(void*);

void fn_80186FA4(f32 x0, f32 y0, f32 x1, f32 y1, const GXColor2* c) {
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    if (x0 > x1) {
        f32 ty, tx; tx = x0; ty = y0;
        x0 = x1; y0 = y1; x1 = tx; y1 = ty;
    }
    fn_800800D4(4);
    fn_80080388(x0, y0, x1 - x0, y1 - y0);
    fn_800804D4(c->r, c->g, c->b, c->a);
    fn_80080578(0);
    fn_80080308();
}
static inline void Dr2(void* arch, int tile, GXColor2* c, GXColor2* t, f32 x1, f32 y1, f32 x2, f32 y2, u16 th, u16 tw) {
    *(u32*)t = *(u32*)c;
    fn_801BC88C(arch, tile, t, 0x11, 0, x1, y1, x2, y2, 0.0f, 0.0f, tw, th);
}
static inline u8* EntAt(int k) { u8* p; if (k < 0) return 0; p = lbl_803881E8 + (k << 4); if (k >= 0x1D) p = 0; return p; }
void fn_8018708C(Cfg* c) {
    GXColor2 kt;
    GXColor2 k;
    if (c->x34 & 1) return;
    c->x58 = -1;
    c->x5C = -1;
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E4E4(0.0f, 0.0f, 140.0f, 1.0f);
    fn_8007E164();
    {
    u16 w;
    u16 h;
    void* arch = c->arch;
    TexH** t = (TexH**)fn_80006A0C(arch, 0);
    w = (*t)->x2; h = (*t)->x0;
    u8* pp = fn_800CD204(1);
    k.r = pp[0]; k.g = pp[1]; k.b = pp[2]; k.a = 0xFF;
    TexH** t2 = (TexH**)fn_80006A0C(arch, 0);
    {f32 x=0.0f; f32 y=0.0f; Dr2(arch, 0, &k, &kt, x, y, x + (f32)w, y + (f32)h, (*t2)->x0, (*t2)->x2);}
    }
    fn_801BCA5C(-1.0f);
    {
    const char* s = fn_800D0864(*(const char**)(EntAt(c->x7D[c->x48]) + 0xc));
    int w;
    fn_801BCA94();
    w = fn_800CA3DC(s, -1, 0.9f) / 2;
    fn_800CB3A8(0.9f, 0.0f, 0x130 - w, 0x42, 1, 0, 0, s);
    }
    fn_801BCA5C(1.0f);
    fn_8018732C(c);
    fn_801BCA5C(-5.0f);
    {
    char b[0x80];
    fn_80290DDC(b, "%s %s %s", fn_800D0864("MCFG_SELE_ITEMS"), fn_800D0864("MCFG_SELE_CONTENTS"), fn_800D0864("MCFG_RETURN"));
    fn_801C6D9C(b, 0xff, 0xff, 0);
    }
    fn_801BCA5C(5.0f);
    fn_8018E6B0(c);
    {f32 a=c->x3c; fn_80179888(c->x60, (int)(32.0f * a));}
    fn_80179A84(c->x60);
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
}
}
