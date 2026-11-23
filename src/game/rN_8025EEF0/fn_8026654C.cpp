/* Dictionary relation chart: pulsing frame */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };

extern "C" {

f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
void fn_801BCA5C(f32 v);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC c, int d, int e);

static inline GXC mk(const u8* p, u8 a) { GXC c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }

static inline void Corner(int x, int y, int rot, int alpha) {
        u16* d;
    u16 w;
    u16 h;
    u8* p;
    GXC c;
    void* tex;

    tex = *(void**)lbl_804CC008->m20;
    d = *fn_80006A0C(tex, 0);
    w = d[1];
    h = d[0];
    p = fn_800CD204(2);
    c.r = p[0];
    c.g = p[1];
    c.b = p[2];
    c.a = alpha;
    fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, w, h, tex, 0, c, 0x11, rot);
}

void fn_8026654C(void) {
    int alpha;
    int n;
    n = 0x18;
    if (lbl_804CC008->m48 == 0) {
        lbl_804CC008->m4A += 1;
        alpha = (int)fn_8017F68C(245.0f, 255.0f, lbl_804CC008->m4A, n, 0);
        if (lbl_804CC008->m4A >= 0x18) {
            lbl_804CC008->m48 = 1;
        }
    } else {
        lbl_804CC008->m4A -= 1;
        alpha = (int)fn_8017F68C(255.0f, 245.0f, n - lbl_804CC008->m4A, n, 0);
        if (lbl_804CC008->m4A <= 0) {
            lbl_804CC008->m48 = 0;
        }
    }
    fn_801BCA5C(-6.0f);
    Corner(0, 0, 0, alpha);
    Corner(304, 0, 1, alpha);
    Corner(0, 224, 2, alpha);
    Corner(304, 224, 3, alpha);
    fn_801BCA5C(6.0f);
}

}
