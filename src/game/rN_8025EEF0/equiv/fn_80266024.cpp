/* r20: `regs` (check_regs.py; r20/r21 of tile and t swapped, r19..r22 rotated in the logo block).
   Fixes against the wip draft:
   - fn_801BC88C is declared with its integer arguments first (as in rF: arch, tile, colour, 0x11, flags, floats) and
     the tile fallback is a ternary inside the call, `(u16)(tile == -1 ? t : tile)`; that puts `mr r3,tex` before the
     branch as in the original;
   - REAL BUG in the draft: the last call is fn_801BCA5C(1.0f), not 0.0f (lbl_804D00C0). */
/* Dictionary relation chart: tiled background */
#include "game/rN_8025EEF0/dict.h"

struct GXC { u8 r, g, b, a; };

extern "C" {

void fn_801BCA5C(f32 v);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(void* tex, int i, GXC* c, int d, int e, f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h);

static inline GXC mk(const u8* p) { GXC c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; return c; }

static inline void cell(void*& tex, int x, int y, int w, int h, int tile, int t) {
    tex = *(void**)lbl_804CC008->m20;
    u8* p = fn_800CD204(1);
    GXC c;
    GXC cc;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF;
    *(u32*)&cc = *(u32*)&c;
    GXC* q = &cc;
    fn_801BC88C(tex, (u16)(tile == -1 ? t : tile), q, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, w, h);
}

static inline void logo(void) {
/*P*/
    u16 w2;
    u16 h2;
    void* tex;
    u16* d;
/*E*/
    tex = *(void**)lbl_804CC008->m20;
    d = *fn_80006A0C(tex, 1);
    w2 = d[1];
    h2 = d[0];
    u8* p = fn_800CD204(1);
    GXC c;
    GXC c2;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF;
    *(u32*)&c2 = *(u32*)&c;
    fn_801BC88C(tex, 1, &c2, 0x11, 0, 1032.0f, 1160.0f, w2 + 0x408, h2 + 0x488, 0.0f, 0.0f, w2, h2);
}

void fn_80266024(void) {
/*P*/
    int i;
    int j;
    int px;
    int py;
    int w;
    int h;
    void* tex;
    int tile;
    int t;
/*E*/
    for (j = 0; j < 12; j++) {
        t = 3;
        if (j % 2 != 0) {
            t = 2;
        }
        for (i = 0; i < 12; i++) {
            px = i * 0x98;
            py = j * 0x70;
            w = 0x98;
            h = 0x70;
            tile = -1;
            if (i == 0 && j == 0) {
                tile = 4;
            } else if (i == 11 && j == 11) {
                tile = 5;
                px = 0x638;
                py = 0x498;
            } else if (i == 11 && j == 10) {
                h = 0x508 - py - h;
            } else if (i == 10 && j == 11) {
                w = 0x6D0 - px - w;
            }
            cell(tex, px, py, w, h, tile, t);
            { int n = 2; if (t == 2) n = 3; t = n; }
        }
    }
    fn_801BCA5C(-1.0f);
    logo();
    fn_801BCA5C(1.0f);
}

}
