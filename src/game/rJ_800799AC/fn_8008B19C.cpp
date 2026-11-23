/* Draw a string with the cached 24x24 glyphs (see fn_8008A868) as GX quads. Names guessed. */
#include "game/rJ_800799AC/types.h"

struct C4 { u8 r, g, b, a; };
struct Tex { u8 d[0x20]; };
struct Glyph {
    u8 pix[0x120];
    u16 code;  /* 0x120 */
    u16 w;     /* 0x122 */
    u8 pad[0x140 - 0x124];
};
struct GlyphCache {
    Glyph* buf;
    int count;
};
union WGPipe { volatile u8 u8; volatile s16 s16; volatile u16 u16; volatile u32 u32; volatile f32 f32; };

extern "C" {
extern GlyphCache lbl_804CB5E8;
u16 fn_8031C044(void);
void fn_803031CC(void);
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_80021958(int, C4);
void fn_80021BF4(int);
void fn_80021CB4(int, int, int, int);
void fn_80021E20(int, int, int, int, int);
void fn_80021D18(int, int, int, int, int, int);
void fn_80021E8C(int, int, int, int, int);
void fn_80021D9C(int, int, int, int, int, int);
void fn_80021C34(int);
void fn_80021F7C(int, int, int, int);
void fn_80021C74(int);
void fn_80306B24(int);
void fn_80305A40(Tex*, void*, int, int, int, int, int, int);
void fn_80022254(Tex*, int);
void fn_80304314(int prim, int fmt, int n);
}

static inline BOOL isSjis(const u8* s) {
    if (((s[0] >= 0x81 && s[0] <= 0x9F) || (s[0] >= 0xE0 && s[0] <= 0xFC))
        && ((s[1] >= 0x40 && s[1] <= 0x7E) || (s[1] >= 0x80 && s[1] <= 0xFC))) {
        return 1;
    }
    return 0;
}
static inline Glyph* find(GlyphCache* gc, u16 code) {
    Glyph* b;
    Glyph* e;
    Glyph* first;
    int half;
    Glyph* mid;
    int len;
    b = gc->buf;
    e = b + gc->count;
    first = b;
    len = e - b;
    while (len > 0) {
        half = len / 2;
        mid = first + half;
        if (mid->code < code) {
            first = mid + 1;
            len -= half + 1;
        } else {
            len = half;
        }
    }
    if (e == first || first->code != code) {
        first = gc->buf;
    }
    return first;
}

extern "C" void fn_8008B19C(f32 fx, f32 fy, f32 fz, f32 scale, C4 color, const u8* s) {
    WGPipe* gx = (WGPipe*)0xCC008000;
    Tex tex;
    int x;
    s16 y;
    s16 z;
    s16 w;
    s16 h;
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xd, 1);
    fn_80303200(0, 9, 1, 3, 0);
    fn_80303200(0, 0xd, 1, 0, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    fn_80021958(4, color);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021E20(0, 0xf, 0xf, 0xf, 10);
    fn_80021D18(0, 0, 0, 0, 1, 0);
    fn_80021E8C(0, 7, 4, 5, 7);
    fn_80021D9C(0, 0, 0, 0, 1, 0);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3c);
    fn_80021C74(0);
    fn_80306B24(0);
    x = fx;
    y = fy;
    z = fz;
    w = 24.0f * scale;
    h = 24.0f * scale;
    while ((s8)*s != 0) {
        u16 c;
        Glyph* g;
        if ((s8)*s == '\n') {
            x = fx;
            y += h;
            s++;
            continue;
        }
        if (fn_8031C044() != 1) {
            c = *s++;
        } else {
            BOOL sj = 0;
            if (fn_8031C044() == 1) sj = isSjis(s);
            if (!sj) {
                c = *s++;
            } else {
                c = *(const u16*)s;
                s += 2;
            }
        }
        g = find(&lbl_804CB5E8, c);
        fn_80305A40(&tex, g, 0x18, 0x18, 0, 0, 0, 0);
        fn_80022254(&tex, 0);
        fn_80304314(0x80, 0, 4);
        gx->s16 = x;
        gx->s16 = y;
        gx->s16 = z;
        gx->u8 = 0;
        gx->u8 = 0;
        gx->s16 = (s16)x + w;
        gx->s16 = y;
        gx->s16 = z;
        gx->u8 = 1;
        gx->u8 = 0;
        gx->s16 = (s16)x + w;
        gx->s16 = y + h;
        gx->s16 = z;
        gx->u8 = 1;
        gx->u8 = 1;
        gx->s16 = x;
        gx->s16 = y + h;
        gx->s16 = z;
        gx->u8 = 0;
        gx->u8 = 1;
        x += (int)((f32)g->w * scale);
    }
}
