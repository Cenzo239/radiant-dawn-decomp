/* Dictionary relation chart: background frame */
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };
struct DS { void* tex; int mode; int page; u8 padC[0xC]; s16 m18; };

extern "C" {

extern DS* lbl_804CC004;
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC* c, int d, int e);
void fn_801BCA5C(f32 v);

static inline void spr(int i, f32 x, f32 y, int ix, int iy) {
    GXC t0; GXC a0;
    u32 w; u32 h; void* tx;
    u16* d;
    const u8* p;
    tx = lbl_804CC004->tex;
    d = *fn_80006A0C(tx, i);
    w = d[1];
    h = d[0];
    p = fn_800CD204(1);
    t0.r = p[0]; t0.g = p[1]; t0.b = p[2]; t0.a = 0xFF;
    *(u32*)&a0 = *(u32*)&t0;
    fn_801BC88C(x, y, (int)(w + ix), (int)(h + iy), 0.0f, 0.0f, w, h, tx, i, &a0, 0x11, 0);
}

void fn_80265BCC(void) {
    spr(0, 0.0f, 0.0f, 0, 0);
    fn_801BCA5C(-0.5f);
    switch (lbl_804CC004->mode) {
    case 0:
        if (lbl_804CC004->m18 == 0) spr(1, 230.0f, 24.0f, 0xE6, 0x18);
        if (lbl_804CC004->m18 == 1) spr(2, 230.0f, 24.0f, 0xE6, 0x18);
        break;
    case 1:
        if (lbl_804CC004->m18 == 0 && lbl_804CC004->page < 7) spr(3, 230.0f, 256.0f, 0xE6, 0x100);
        break;
    }
    fn_801BCA5C(-0.5f);
    spr(4, 0.0f, 15.0f, 0, 0xF);
    fn_801BCA5C(1.0f);
}

}
