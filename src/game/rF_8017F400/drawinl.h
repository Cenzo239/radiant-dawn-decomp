/* Shared declarations and inlines for the 0x801BD420..0x801C5874 draw functions.
   fn_801BCA5C, fn_801BCA94, fn_801BD170 and fn_801BD2EC were auto-inlined by the original
   compiler in later functions of their file, so they appear here as static inlines. */
#ifndef RF_DRAWINL_H
#define RF_DRAWINL_H
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct GXColor2 { u8 r,g,b,a; } GXColor2;
typedef struct TexH { u16 x0, x2; } TexH;
extern void* lbl_804CB588;
extern char lbl_8036E118[];
extern void* fn_80006A0C(void*, int);
extern u8* fn_800CD204(int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E720(f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E7DC(int);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_801BC88C(void* a, int b, GXColor2 c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern int fn_801D09F0(void);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern int fn_800CA3DC(const char*, int, f32);
extern int fn_80291188(const char*, const char*);
extern char* strcpy(char*, const char*);
extern const char* fn_800D0864(const char*);
extern int fn_80290DDC(char*, const char*, ...);
extern char* fn_80291110(char*, const char*);
extern void fn_800800D4(int);
extern void fn_80080308(void);
extern void fn_80080330(f32, f32);
extern void fn_80080348(f32, f32, f32, f32);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_80080508(GXColor2);
extern void fn_80080578(int);
extern void fn_800804F4(int);
extern void fn_80080A94(f32);
extern void fn_80080B00(int, void*, f32);
extern void fn_80080C24(const char*);

static inline void SetScale(f32 v) { fn_8007E154(); fn_8007E720(v); fn_8007E164(); }
static inline void FontReset(void) { fn_8007E154(); fn_8007E174(0, 0x13); fn_8007E164(); }
static inline GXColor2 mk(const u8* p, u8 a) { GXColor2 c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
static inline void DrawC(void* arch, int tile, GXColor2 c, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
/* fn_801BD2EC, inlined (c first, then the by-value temp) */
static inline void Sprite(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    DrawC(lbl_804CB588, tile, mk(fn_800CD204(col), alpha), fl, x, y, w, h);
}
/* Same code; the stack temp comes before c. Inline depth sets the stack order. */
static inline void Sprite2(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(col);
    GXColor2 c;
    void* arch;
    TexH** t;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    arch = lbl_804CB588;
    t = (TexH**)fn_80006A0C(arch, tile);
    {
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
    }
}
static inline void Sprite4(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) { Sprite2(col, alpha, tile, fl, x, y, w, h); }
static inline void Sprite3(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) { Sprite4(col, alpha, tile, fl, x, y, w, h); }
/* fn_801BD170, inlined */
static inline void Tile(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    Sprite(col, alpha, tile, fl, x, y, w * sc, h * sc);
}
/* Other forms of the same code: the nesting only changes the stack slot order. */
static inline void Tile1(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    DrawC(lbl_804CB588, tile, mk(fn_800CD204(col), alpha), fl, x, y, w * sc, h * sc);
}
static inline void TileF(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    Sprite2(col, alpha, tile, fl, x, y, w * sc, h * sc);
}
static inline void TileG(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    Sprite3(col, alpha, tile, fl, x, y, w * sc, h * sc);
}
static inline void SpriteE(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    GXColor2 c = mk(fn_800CD204(col), alpha);
    DrawC(lbl_804CB588, tile, c, fl, x, y, w, h);
}
static inline void SpriteM(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    GXColor2 c = mk(fn_800CD204(col), alpha);
    void* arch = lbl_804CB588;
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void DrawP(void* arch, int tile, GXColor2 c, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    TexH** t;
    t = (TexH**)fn_80006A0C(arch, tile);
    {
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
    }
}
static inline void SpriteN(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(col);
    GXColor2 c;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    DrawP(lbl_804CB588, tile, c, fl, x, y, w, h);
}
static inline void SpriteO(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(col);
    GXColor2 c;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    {
    void* arch = lbl_804CB588;
    DrawC(arch, tile, c, fl, x, y, w, h);
    }
}
static inline void SpriteP(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    DrawP(lbl_804CB588, tile, mk(fn_800CD204(col), alpha), fl, x, y, w, h);
}
static inline void TileE(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    SpriteE(col, alpha, tile, fl, x, y, w * sc, h * sc);
}
#define WRAPT(N, B) static inline void N(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc) { B(col, alpha, tile, fl, x, y, sc); }
#define WRAPS(N, B) static inline void N(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) { B(col, alpha, tile, fl, x, y, w, h); }
WRAPT(TileW, Tile) WRAPT(Tile1W, Tile1) WRAPT(TileFW, TileF) WRAPT(TileGW, TileG) WRAPT(TileEW, TileE)
WRAPS(SpriteMW, SpriteM) WRAPS(SpriteNW, SpriteN) WRAPS(SpriteOW, SpriteO) WRAPS(SpritePW, SpriteP) WRAPS(SpriteW, Sprite) WRAPS(Sprite2W, Sprite2) WRAPS(Sprite3W, Sprite3) WRAPS(SpriteEW, SpriteE)
static inline void Hdr(int tile, f32 x, f32 y) {
    f32 w, h;
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, tile);
    u16 a, b; a = (*t)->x2; b = (*t)->x0;
    if (fn_801D09F0()) w = 0.764f * a; else w = a;
    h = b;
    DrawC(lbl_804CB588, tile, mk(fn_800CD204(1), 0xFF), 0, x - 0.5f * w, y, w, h);
}
static inline void Bar(u8 a, f32 x, f32 y, f32 w, int tile) {
    TileG(1, a, tile, 0, x, y, 1.0f);
    SpriteW(1, a, tile + 1, 0, 3.0f + x, y, w, 8.0f);
    TileF(1, a, tile + 2, 0, 3.0f + x + w, y, 1.0f);
}
/* outlined text run */
static inline void TextCol(const char* s, f32 x, f32 y, int col) {
    fn_800800D4(5);
    fn_80080330(x, y);
    fn_80080508(*(GXColor2*)fn_800CD204(col));
    fn_80080B00(1, fn_800CD204(0x2A), 1.0f);
    fn_80080C24(s);
    fn_80080308();
}
}
#endif
