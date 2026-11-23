/* fn_801A4744 (0x980): unit map overview (unit markers on the minimap, models tinted by side colour).
 * Matched in round m28 from the r21 equiv: a declaration hill over the function-level locals (85 -> 19),
 * the frame drawn like fn_801A4068's Bg (`C4 c; C4 t;`, u32 copy, pointer to fn_801BC88C through a cast)
 * with the scale as an inline parameter, the model colour as `C4 m; C4 n;` with fields stored one by one and
 * a u32 copy, and s8 x102/x103 fields passed without casts.
 * Notes for a port:
 *   - `lum` is a u8 parameter (fn_801A4068.cpp already declares it so; fn_801A3068.cpp says int).
 *   - The colour temporaries only reproduce the original's stack copies; `mdl->s->col = {..}` is what they mean.
 *   - Struct names and fields are local guesses: MMap is the object at lbl_804CB964 (TDraw in fn_801A3068.cpp),
 *     MUnit the 0x3F0-byte unit of lbl_804CB810; use the shared definitions in a port.
 *   - fn_801BC88C takes the colour by pointer in fn_801A4068.cpp and by value here; the Frame call uses the
 *     pointer form through the BCP cast. */
/* fn_801A4744: draws the minimap panel at (x, y): a shaded backdrop quad, then for every unit id 1..0xFE that is
 * on the map and whose side is shown, either positions its small map model (units with flag 0x100 that have one
 * in the four model groups) or draws a four-quadrant side-coloured icon (tile 0x13 mirrored four ways), and last
 * the frame (tile 1). `lum` scales the colours (0..255). Names guessed. */
#pragma auto_inline off
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct TexH { u16 x0, x2; } TexH;
typedef struct V3 { f32 x, y, z; } V3;
typedef struct MdlS { u8 p0[8]; s16 x8; u8 pA[0x18 - 0xA]; u32 x18; u8 p1C[0x64 - 0x1C]; C4 col; } MdlS;
typedef struct Mdl { u8 p0[0x30]; MdlS* s; } Mdl;
typedef struct Side { u8 p0[8]; u8 id; } Side;
typedef struct MUnit {
    u8 p0[0xEC]; int xEC; u8 pF0[4]; Side* side; u8 pF8[0x102 - 0xF8]; s8 x102; s8 x103; u8 p104[8]; u32 x10C;
    u8 p110[0x3F0 - 0x110];
} MUnit;
typedef struct MItem { u8 p0[0x14]; MUnit* u; Mdl* mdl; u8 p1C[8]; } MItem;       /* 0x24 */
typedef struct MGrp { u8 p0[0xC]; int n; MItem it[5]; } MGrp;                     /* 0xC4 */
typedef struct MMap {
    u8 p0[4]; u32 show; u8 p8[4]; void* arch; MGrp grp[4]; u8 p320[0x338 - 0x320]; u8 x338; u8 x339; u8 p33A[6];
    s16 x340; u8 p342[2]; f32 scale; u8 p348[0x358 - 0x348]; u16 w;
} MMap;
extern MMap* lbl_804CB964;
extern MUnit* lbl_804CB810;
extern void* fn_8013B9A8(void);
extern void fn_80138DD4(void* a, void* b);
extern f32 fn_80138698(void);
extern int fn_801386AC(void* a, int x, int y, V3* o);
extern void fn_801BCA5C(f32);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(void*, int);
extern void fn_800800D4(int);
extern void fn_8008031C(f32);
extern void fn_80080348(f32, f32, f32, f32);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_800804D4(int r, int g, int b, int a);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern void* fn_80006A0C(void*, int);
extern void fn_8010E41C(u8*, int);
extern int fn_800FADB8(MUnit*);
extern u8* fn_800CD204(int);
extern void fn_800E48AC(void*, f32, f32, f32);
extern void fn_800E4AD4(void*, f32);
extern void fn_801BC88C(void* a, int b, C4 c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
void fn_801A4744(u8 lum, f32 x, f32 y);
}
static inline MUnit* UnitOf(int id) {
    if ((u8)id) return &lbl_804CB810[(u8)id - 1];
    return 0;
}
static inline void Spr(int tile, C4 c, u32 fl, f32 x, f32 y, f32 sc) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB964->arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(lbl_804CB964->arch, tile, c, 0x11, fl, x, y, tw * sc + x, th * sc + y, 0.0f, 0.0f, tw, th);
}
static inline C4 mk(const u8* p, u8 a) { C4 c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
static inline void Grey(int v) { fn_800804D4(v, v, v, 0xFF); }
typedef void (*BCP)(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
static inline void FrameS(f32 x, f32 y, f32 sc) {
    C4 c;
    C4 t;
    u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF;
    TexH** q = (TexH**)fn_80006A0C(lbl_804CB964->arch, 1);
    f32 tw = (*q)->x2, th = (*q)->x0;
    *(u32*)&t = *(u32*)&c;
    ((BCP)fn_801BC88C)(lbl_804CB964->arch, 1, &t, 0x11, 0, x, y, tw * sc + x, th * sc + y, 0.0f, 0.0f, tw, th);
}
static inline C4 withA(C4 c, u8 a) { c.a = a; return c; }

void fn_801A4744(u8 lum, f32 x, f32 y) {
    C4 c;
    TexH** tex;
    int side;
    u8 vis[12];
    u8 view[0x20];
    int px, py;
    int ix, iy;
    int id;
    f32 sc;
    int k, j;
    Mdl* mdl;
    int col;
    MUnit* u;
    V3 pos;
    int al;
    int drawn;

    fn_80138DD4(fn_8013B9A8(), view);
    fn_801BCA5C(2.0f);
    fn_8007E154();
    fn_8007E174(view, 0x11);
    fn_8007E164();
    px = 156.0f + (16.0f + x) - (int)((u32)lbl_804CB964->w >> 1);
    py = 31.0f + y;
    fn_800800D4(1);
    fn_8008031C(0.0f);
    fn_80080348(px, py, 0.0f, 0.0f);
    fn_80080368(px + lbl_804CB964->w, py + 0x106, lbl_804CB964->w, 262.0f);
    Grey(lum);
    fn_80080578(0);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    tex = (TexH**)fn_80006A0C(lbl_804CB964->arch, 0x13);
    fn_8013B9A8();
    lbl_804CB964->scale = fn_80138698();
    fn_8010E41C(vis, 3);
    for (id = 1; id <= 0xFE; id++) {
        u = UnitOf(id);
        if (u->xEC == 0) continue;
        side = u->side->id;
        if (vis[side] == 0) continue;
        if (!(lbl_804CB964->show & 1) && side == 0) continue;
        if (!(lbl_804CB964->show & 2) && side == 3) continue;
        if (!(lbl_804CB964->show & 4) && side == 1) continue;
        if (!(lbl_804CB964->show & 8) && side == 2) continue;
        if (u->x10C & 0x10000DC) continue;
        if (fn_800FADB8(u)) continue;
        switch (side) {
        case 0: col = 7; break;
        case 3: col = 6; break;
        case 1: col = 3; break;
        case 2: col = 4; break;
        }
        fn_801386AC(fn_8013B9A8(), u->x102, u->x103, &pos);
        drawn = 0;
        if (u->x10C & 0x100) {
            mdl = 0;
            c = *(C4*)fn_800CD204(col);
            for (k = 0; k < 4; k++) {
                MGrp* g = &lbl_804CB964->grp[k];
                MItem* it = g->it;
                for (j = 0; j < g->n; j++, it++) {
                    if (u == it->u) {
                        mdl = it->mdl;
                        k = 4;
                        break;
                    }
                }
            }
            if (mdl != 0) {
                fn_800E48AC(mdl, px + pos.x, py + pos.y, 0.0f);
                mdl->s->x8 = 0x97;
                fn_800E4AD4(mdl, 0.008f * lbl_804CB964->scale);
                drawn = 1;
                {
                    C4 m;
                    C4 n;
                    n.r = (c.r >> 1) * lum / 255;
                    n.g = (c.g >> 1) * lum / 255;
                    n.b = (c.b >> 1) * lum / 255;
                    n.a = 0xFF - lbl_804CB964->x339;
                    *(u32*)&m = *(u32*)&n;
                    mdl->s->col = m;
                }
                mdl->s->x18 |= 0x1004;
            }
        }
        if (drawn) continue;
        sc = 0.7f * lbl_804CB964->scale / (*tex)->x2;
        c = *(C4*)fn_800CD204(col);
        {
            C4 n = {c.r * lum / 255, c.g * lum / 255, c.b * lum / 255, 0xFF};
            c = n;
        }
        ix = px + pos.x;
        iy = py + pos.y;
        al = lbl_804CB964->x340;
        Spr(0x13, withA(c, al), 2, ix - 0.7f * lbl_804CB964->scale, iy - 0.7f * lbl_804CB964->scale, sc);
        Spr(0x13, withA(c, al), 3, ix, iy - 0.7f * lbl_804CB964->scale, sc);
        Spr(0x13, withA(c, al), 0, ix - 0.7f * lbl_804CB964->scale, iy, sc);
        Spr(0x13, withA(c, al), 1, ix, iy, sc);
    }
    fn_801BCA5C(-2.0f);
    FrameS(x, y, 1.0f);
    fn_801BCA5C(1.0f);
}
