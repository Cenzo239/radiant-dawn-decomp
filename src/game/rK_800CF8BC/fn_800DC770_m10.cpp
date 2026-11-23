/* fn_800DC770: exact (round m10). Saves the camera state and the cursor position into lbl_803E8F78.
 * Lever: the two cursor floats are named locals read first (f32 x = cur.x; f32 y = cur.y;) and converted at
 * the stores; that gives lfs f0 (x8) / lfs f2 (y) / fctiwz f0,f2. Kept apart from fn_800DC770.cpp, which holds
 * the following functions. */
#include "game/rK_800CF8BC/types.h"
struct Cam {
    u8 pad0[4];
    f32 x4, x8, xC;
    f32 x10, x14;
    u8 pad18[0x20];
    Vec v38;
    Vec v44;
};
struct SavedCam {
    u8 valid;
    u8 pad1[3];
    f32 x4, x8, xC;
    Vec v;
    s16 tx;
    s16 ty;
};
struct CurData {
    u8 pad[0x93C];
    f32 x;
    f32 y;
};
extern SavedCam lbl_803E8F78;
extern CurData lbl_803CAB38;
extern "C" {
Cam* fn_8012FCD0();
int fn_800DC770() {
    Cam* c = fn_8012FCD0();
    if (c) {
        SavedCam* s = &lbl_803E8F78;
        s->x4 = c->x4;
        s->x8 = c->x8;
        s->xC = c->xC;
        {
            Vec t = c->v38;
            s->v = t;
            f32 x = lbl_803CAB38.x; f32 y = lbl_803CAB38.y;
            s->tx = x;
            s->ty = y;
            lbl_803E8F78.valid = 1;
        }
    }
    return 1;
}
}
