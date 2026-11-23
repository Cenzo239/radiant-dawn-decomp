/* fn_802170E8: draw callback: perspective projection + viewport for a widget's 3-D model
   (rect in a Sci), draws it with fn_8001A4DC, then restores the viewport. */
#include "game/rI_801DD7D4/types.h"
extern "C" {
void fn_80312E5C(f32* m, f32 fovy, f32 aspect, f32 n, f32 f);
void fn_80307D98(f32* m, int type);
void fn_803080BC(f32* vp);
void fn_80308090(f32 x, f32 y, f32 w, f32 h, f32 nz, f32 fz);
void fn_8001A4DC(void*);
struct Sci { s16 x, y, w, h; void* a8; };
void fn_802170E8(Sci* s) {
    f32 m[16];
    f32 vp[6];
    f32 x = s->x;
    f32 y = s->y;
    f32 w = s->w;
    f32 h = s->h;
    fn_80312E5C(m, 30.0f, w / h, 1.0f, 1000.0f);
    fn_80307D98(m, 0);
    fn_803080BC(vp);
    fn_80308090(x, y, w, h, vp[4], vp[5]);
    fn_8001A4DC(s->a8);
    fn_80308090(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
}
}
