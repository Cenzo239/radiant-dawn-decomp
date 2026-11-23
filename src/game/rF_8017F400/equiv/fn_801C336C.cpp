/* r19: copied from wip/fn_801C336C.cpp; `sched` level (same instructions per basic block, order differs). */
#include "game/rF_8017F400/drawinl.h"
#pragma auto_inline off
extern "C" {
class IconFont {
public:
    u8 pad[0x44];
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void draw(int x, int y, int id);
};
struct Item { u8 pad[0x1E]; u8 x1E; u8 x1F; };
struct Slot { Item* x0; u8 p4; u8 x5_0 : 6; u8 b1 : 1; u8 b0 : 1; };
struct Pn { u8 p0[0x24]; f32 x24, x28; u8 p2C[0x18]; u8* x44; };
struct Pn2 { u8 p0[0x2C]; Slot* s; };
extern u8 lbl_803E7290[];
extern u8 lbl_803E72D8[];
extern char lbl_8036E118[];
extern const char* fn_80127A90(u8*);
extern int fn_8011B8A4(u8*);
extern void fn_801C3AB4(const char*, f32, f32, f32);
extern const char* fn_8011A054(Item*);

static inline void T1(int col, u8 a, int tile, u32 fl, f32 x, f32 y, f32 sc) { TileF(col, a, tile, fl, x, y, sc); }
static inline void T2(int col, u8 a, int tile, u32 fl, f32 x, f32 y, f32 sc) { T1(col, a, tile, fl, x, y, sc); }
static inline void S1(int col, u8 a, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) { Sprite(col, a, tile, fl, x, y, w, h); }
static inline void Row(f32 x0, f32 x1, f32 x2, f32 ry) {
    T2(1, 0xA0, 9, 0, 12.0f + x0, 19.0f + ry, 1.0f);
    S1(1, 0xA0, 0xA, 0, 3.0f + x1, 19.0f + ry, 171.0f, 8.0f);
    TileF(1, 0xA0, 0xB, 0, x2 + 171.0f, 19.0f + ry, 1.0f);
}
void fn_801C336C(Pn* p) {
/*P*/
    Slot* v;
    Pn* q;
    int ofs;
    int i;
    u8* u;
    f32 y0;
    f32 ry2;
    f32 sw;
    f32 h0;
    f32 x0;
    f32 xa;
    f32 x2;
    f32 ry;
    f32 x;
    f32 y;
    f32 x1;
    f32 ya;
/*E*/
    x = p->x24;
    y = p->x28;
    u = p->x44;
    SetScale(-1.0f);
    {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, 0x1C);
    u16 w = (*t)->x2;
    u16 h = (*t)->x0;
    if (fn_801D09F0()) sw = 0.764f * w; else sw = w;
    h0 = h;
    }
    Sprite(1, 0xFF, 0x1C, 0, (182.0f + x) - 0.5f * sw, 12.0f + y, sw, h0);
    {
    const char* s = fn_80127A90(u);
    fn_801C3AB4(s, 20.0f + x, 32.0f + y, fn_8011B8A4(u + 0x12C));
    }
    {
    x0 = 152.0f + x;
    y0 = 34.0f + y;
    x1 = 12.0f + x0;
    x2 = 3.0f + x1;
    for (i = 0; i < 6; i++) {
        ry = y0 + (f32)(i * 0x20);
        Row(x0, x1, x2, ry);
    }
    }
    SetScale(-1.0f);
    FontReset();
    {
    xa = 144.0f + x;
    ya = 34.0f + y;
    q = p;
    ofs = 0;
    for (i = 0; i < 6; i++, q = (Pn*)((u8*)q + 4)) {
        ry2 = ya + (f32)ofs;
        v = ((Pn2*)q)->s;
        if (v) {
            if (*((u8*)v + 5) & 1) {
                f32 ix;
                if (fn_801D09F0()) ix = 3.0f + xa; else ix = xa;
                ((IconFont*)lbl_803E7290)->draw((int)ix, (int)(2.0f + ry2), 0x59);
            }
            ((IconFont*)lbl_803E72D8)->draw((int)(25.0f + xa), (int)ry2, v->x0->x1F);
            FontReset();
            fn_800CB3A8(1.0f, 0.0f, 60.0f + xa, 2.0f + ry2, 1, 1, 0, fn_8011A054(v->x0));
            {
            int b = v->b1;
            if (b ? 0 : v->x0->x1E) {
                fn_800CB3A8(1.0f, 0.0f, 166.0f + xa, 2.0f + ry2, 1, 1, 0, lbl_8036E118 + 0x175, b ? 0 : v->x0->x1E);
            }
            }
            ofs += 0x20;
        }
    }
    }
    SetScale(2.0f);
}
}
