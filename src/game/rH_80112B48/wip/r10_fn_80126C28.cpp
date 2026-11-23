/* NOT MATCHING, not compiled. fn_80126C28: 2 words: add operand order. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern s16 fn_8010ECA0(void);
extern s16 fn_8010EC08(void);
extern void* lbl_804CA4E8; extern void* lbl_804CA4E4; extern void* lbl_804CA4E0;
#define BB(f,k) r = (int)f() + r + k;
u8 fn_80126C28(Unit* u) {
    int r = u->gauge;
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        s8 v = u->gauge;
        if (v >= 30) {
            r += fn_8010ECA0();
        } else {
            BOOL m = 0;
            if (v >= 15 && v < 30) {
                m = 1;
            }
            if (m) {
                r += fn_8010EC08();
            }
        }
    } else if (fn_8011B77C(u->skills, lbl_804CA4E4)) {
        BB(fn_8010ECA0, 0x28)
    } else if (fn_8011B77C(u->skills, lbl_804CA4E0)) {
        BB(fn_8010EC08, 0x14)
    }
    if (r > 0xff) {
        r = 0xff;
    }
    if (r < 0) {
        r = 0;
    }
    return r;
}
}
