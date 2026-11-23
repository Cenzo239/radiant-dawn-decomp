/* fn_801A4744 (0x980): functionally equal at `slots` level (tools/check_regs.py, round 21; 85 words differ).
 * New this round, written from the disassembly. Same instructions in the same order; saved registers are
 * numbered differently (the original has id r31, col r30, lum r29; ours lum r31 and the loop values lower), and
 * two pairs of 4-byte colour locals sit in each other's stack slots:
 *   - model colour: the initialiser `n` and its copy `m` (original n 0x34, m 0x38; ours n 0x38, m 0x34),
 *   - frame colour: `fc` and the by-value argument copy of Spr (original fc 0x8, copy 0xC; ours the reverse).
 * symcheck.py --anon flags 3 of 80 blocks, exactly these: block 61 "stack bytes differ at 0x34..0x3b" (n/m),
 * blocks 75 and 76 "stack bytes differ at 0x8..0xf" (fc/copy). All four slots are dead after the statement.
 * Notes for a port:
 *   - `lum` is a u8 parameter (fn_801A4068.cpp already declares it so; fn_801A3068.cpp says int). With int the
 *     grey backdrop call schedules its `li r6,0xFF` differently.
 *   - The colour temporaries (`n`, `m`, the block around the icon colour, withA) only reproduce the original's
 *     stack copies; `mdl->s->col = {..}` and `c = {..}` are what they mean. Tried for the n/m order: an inline
 *     holding both (right order, but both land below the icon temporaries), a by-value SetCol, an inline
 *     returning the colour (extra copy, hoists 0xFF), placement new (null check).
 *   - Struct names and fields are local guesses: MMap is the object at lbl_804CB964 (TDraw in fn_801A3068.cpp,
 *     same memory), MUnit the 0x3F0-byte unit of lbl_804CB810; use the shared definitions in a port.
 *   - fn_8007E174's first argument is a pointer here (the 0x20-byte view block from fn_80138DD4); other files
 *     pass 0 and declare it int.
 *   - fn_80138698 is called right after fn_8013B9A8 and may take its result in r3 (the matched definition is
 *     `f32 fn_80138698(void)`).
 *   - When a unit has the 0x100 flag but no model in the four groups, it falls through to the icon.
 */
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
    u8 p0[0xEC]; int xEC; u8 pF0[4]; Side* side; u8 pF8[0x102 - 0xF8]; u8 x102; u8 x103; u8 p104[8]; u32 x10C;
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
static inline void Frame(f32 x, f32 y) {
    u8* p = fn_800CD204(1);
    C4 fc;
    fc.r = p[0]; fc.g = p[1]; fc.b = p[2]; fc.a = 0xFF;
    Spr(1, fc, 0, x, y, 1.0f);
}
static inline C4 withA(C4 c, u8 a) { c.a = a; return c; }

void fn_801A4744(u8 lum, f32 x, f32 y) {
    u8 view[0x20];
    u8 vis[12];
    V3 pos;
    C4 c;
    int id;
    int col;
    TexH** tex;
    MUnit* u;
    int side;
    int px, py;
    int drawn;
    Mdl* mdl;
    int k, j;
    f32 sc;
    int ix, iy;
    int al;

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
        fn_801386AC(fn_8013B9A8(), (s8)u->x102, (s8)u->x103, &pos);
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
                    C4 n = {(c.r >> 1) * lum / 255, (c.g >> 1) * lum / 255, (c.b >> 1) * lum / 255,
                            0xFF - lbl_804CB964->x339};
                    C4 m = n;
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
    Frame(x, y);
    fn_801BCA5C(1.0f);
}
