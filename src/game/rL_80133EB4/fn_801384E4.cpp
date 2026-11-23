/* Minimap camera setup and map view rectangle scroll. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct Mini {
    f32 x, y, sx, sy;
    f32 w, h;
};
struct Cam {
    u8 pad0[0xD4];
    f32 xd4, xd8, xdc;
    f32 xe0, xe4, xe8;
    f32 xec, xf0, xf4;
};
struct MapSize { int w, h; u8 pad[0x20]; };
extern "C" {
extern Mini* lbl_804CB85C;
extern Cam* fn_8000F470(void);
extern void fn_8000F9E8(Cam*, f32, f32, f32, f32);
extern void fn_8000F9C8(Cam*, int, int, u16, u16);
extern void fn_800102AC(Cam*, f32, f32);
extern void fn_80011274(void);

void fn_801384E4(void*) {
    f32 x, y, z;
    z = 0.0f;
    x = lbl_804CB85C->x;
    y = lbl_804CB85C->y;
    f32 w = lbl_804CB85C->w;
    f32 h = lbl_804CB85C->h;
    f32 sx = lbl_804CB85C->sx;
    f32 sy = lbl_804CB85C->sy;
    Cam* c = fn_8000F470();
    c->xe0 = x;
    c->xe4 = y;
    c->xe8 = z;
    c->xec = 0.0f;
    c->xf0 = -1.0f;
    c->xf4 = 0.0f;
    c->xd4 = x;
    c->xd8 = y;
    c->xdc = z - 30.0f;
    fn_8000F9E8(c, 0.0f, 0.0f, w, h);
    fn_8000F9C8(c, 0, 0, (u16)w, (u16)h);
    fn_800102AC(c, sx, sy);
    fn_80011274();
}

extern u8 lbl_804CB84C;
extern s8 lbl_804CB84D;
extern s8 lbl_804CB84E;
extern s8 lbl_804CB84F;
extern s8 lbl_804CB850;
extern u8 lbl_804CB851;
extern u8 lbl_804CB852;
extern f32 lbl_804CB854;
extern f32 lbl_804CB858;
extern MapSize lbl_803EC898;
extern f32 fn_8001EBC8(f32, f32, f32, f32, int);

void fn_8013531C(void) {
    if (lbl_804CB84C) {
        int t = lbl_804CB852;
        int mw = lbl_803EC898.w;
        int mh = lbl_803EC898.h;
        if (t) {
            int x = lbl_804CB84D;
            int y = lbl_804CB84E;
            f32 x0 = (f32)x / (f32)mw;
            f32 y0 = (f32)y / (f32)mh;
            f32 x1 = (f32)(x + lbl_804CB84F) / (f32)mw;
            f32 y1 = (f32)(y + lbl_804CB850) / (f32)mh;
            int n = lbl_804CB851;
            f32 a = fn_8001EBC8(x1, x0, (f32)n, (f32)t, 2);
            f32 b = fn_8001EBC8(y1, y0, (f32)n, (f32)t, 2);
            t++;
            lbl_804CB854 = a;
            lbl_804CB858 = b;
            lbl_804CB852 = t;
            if (t > n) lbl_804CB852 = 0;
        } else {
            lbl_804CB854 = (f32)lbl_804CB84D / (f32)mw;
            lbl_804CB858 = (f32)lbl_804CB84E / (f32)mh;
        }
    }
}
}
