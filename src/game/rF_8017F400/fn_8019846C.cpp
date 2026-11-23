/* fn_801986C4: save slot header window draw. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct HEnt { s16 flags; s16 x2; s16 x4; s16 x6; s16 x8; u8 pada[0x18-0xa]; s16 x18; u8 pad1a[0x24-0x1a]; const char* x24; } HEnt;
typedef struct TexH { u16 x0, x2; } TexH;
extern void* lbl_804CB92C;
extern void* fn_80006A0C(void*, int);
extern u8* fn_800CD204(int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_8007E7E8(int);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void fn_801BC88C(void* a, int b, GXColor c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
static inline GXColor mk(const u8* p, u8 a) { GXColor c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
static inline void DrawC(void* arch, int tile, GXColor c, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(lbl_804CB92C, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void Sprite2(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    DrawC(lbl_804CB92C, tile, mk(fn_800CD204(col), alpha), fl, x, y, w, h);
}
static inline void Sprite(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(col);
    GXColor c;
    TexH** t;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    t = (TexH**)fn_80006A0C(lbl_804CB92C, tile);
    {
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(lbl_804CB92C, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
    }
}
static inline void Tile(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB92C, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    Sprite(col, alpha, tile, fl, x, y, w, h);
}
typedef struct BEnt { s16 x0, x2; u8 pad4[0x10-4]; s16 x10; } BEnt;
void fn_8019846C(BEnt* e) {
    u16 t = e->x10 + 2; Tile(1, 0xFF, t, 0, e->x0, e->x2);
}
}
