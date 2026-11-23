/* Free camera update, mode 1: snap rotation by 45 degrees with sounds, fade from an axis. */
#include "game/rH_80112B48/campad.h"
extern "C" {
struct Opt { u32 pad0 : 15; u32 b15 : 1; u32 b16 : 1; u32 pad1 : 15; };
extern u8 lbl_803CAB38[];
extern Opt* fn_80060728(void*);
extern void fn_80253EE4(const char*, f32);
extern void fn_8007E030(u8);
extern char lbl_80385F40[];
extern char lbl_80385F28[];
void fn_80131828(Cam* c) {
    u32 v;
    int a;
    if (lbl_804CB5B8->v48() & 0x40) {
        c->mode = (c->mode + 1) & 3;
        c->f0C = c->v18(c->mode);
    }
    v = lbl_804CB5B8->v48();
    if (fn_80060728(lbl_803CAB38)->b16) {
        if (v & 0x1000000) {
            v &= ~0x1000000;
            v |= 0x2000000;
        } else if (v & 0x2000000) {
            v &= ~0x2000000;
            v |= 0x1000000;
        }
    }
    if ((v & 0x1000000) && c->f04 < 45.0f) {
        c->f04 += 45.0f;
        fn_80253EE4(lbl_80385F40, 0.0f);
    }
    if ((v & 0x2000000) && c->f04 > -45.0f) {
        c->f04 -= 45.0f;
        fn_80253EE4(lbl_80385F28, 0.0f);
    }
    if (c->f04 > 45.0f) c->f04 = 45.0f;
    if (c->f04 < -45.0f) c->f04 = -45.0f;
    if (-22.5f < c->f04 && c->f04 < 22.5f) c->f04 = 0.0f;
    if (fn_80060728(lbl_803CAB38)->b15) {
        c->f08 += (f32)lbl_804CB5B8->v5C() / 32.0f;
    } else {
        c->f08 -= (f32)lbl_804CB5B8->v5C() / 32.0f;
    }
    if (c->f08 < 0.0f) c->f08 *= 0.5f;
    if (c->f08 > 50.0f) c->f08 = (50.0f + c->f08) / 2.0f;
    a = 255.0f - 1.7f * (f32)lbl_804CB5B8->v74();
    if (a > 0xff) a = 0xff;
    if (a < 0) a = 0;
    fn_8007E030(a);
}
}
