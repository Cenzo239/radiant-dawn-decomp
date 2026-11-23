/* Camera offset limited by the map size, 8012F1F4. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern Map lbl_803EC898;
extern f32 lbl_804CA71C;
extern u8 lbl_804CB838;
extern f32 fn_8001EF30(f32, f32, f32, f32);
static inline int G(int v) { return v; }
Vec fn_8012F1F4(const Vec* p, f32 z) {
    f32 lim;
    f32 hy;
    f32 hx;
    f32 a;
    f32 limx;
    Vec r = {0.0f, 0.0f, 0.0f};
    if (lbl_804CB838 & 1) {
        return r;
    }
    lim = lbl_804CA71C;
    limx = lim;
    hy = 0.5f * (f32)lbl_803EC898.h;
    hx = 0.5f * (f32)lbl_803EC898.w;
    if (lim > hx) limx = hx;
    if (lim > hy) lim = hy;
    a = fn_8001EF30(limx / 2.0f, limx, 10.0f, z - 16.0f);
    lim = fn_8001EF30(lim / 2.0f, lim, 10.0f, z - 16.0f);
    r.x = -fn_8001EF30(0.0f, a, hx, p->x - hx);
    r.y = -fn_8001EF30(0.0f, lim, hy, p->y - hy);
    return r;
}
}
