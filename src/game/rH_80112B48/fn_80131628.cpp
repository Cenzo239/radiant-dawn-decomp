/* Free camera update, mode 0: pitch and distance from the pad axes. */
#include "game/rH_80112B48/campad.h"
extern "C" {
void fn_80131628(Cam* c) {
    if (lbl_804CB5B8->v48() & 0x40) {
        c->mode = (c->mode + 1) & 3;
        c->f0C = c->v18(c->mode);
    }
    c->f08 -= (f32)lbl_804CB5B8->v5C() / 48.0f;
    if (c->f08 < 0.0f) c->f08 *= 0.5f;
    if (c->f08 > 50.0f) c->f08 = (50.0f + c->f08) / 2.0f;
    c->f04 -= (f32)lbl_804CB5B8->v58() / 48.0f;
    if (c->f04 < -45.0f) c->f04 = (c->f04 - 45.0f) / 2.0f;
    if (c->f04 > 45.0f) c->f04 = (45.0f + c->f04) / 2.0f;
    if (lbl_804CB5B8->v58() == 0) {
        f32 x = c->f04;
        if (x >= -5.0f && x <= 5.0f) c->f04 *= 0.9f;
    }
}
}
