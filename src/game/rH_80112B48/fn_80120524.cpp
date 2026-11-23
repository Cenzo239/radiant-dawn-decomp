/* Transform gauge cost over several levels, scaled by difficulty, 80120524. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8 fn_80126BA4(Unit*);
extern u8 fn_80126B0C(Unit*);
extern u8* fn_80060728(void*);
extern u8 lbl_803CAB38[];
extern void* lbl_804CA4E8;
extern const int lbl_804CA708;
extern f32 lbl_804CDCF0;
static inline const int& Min(const int& a, const int& b) { return b < a ? b : a; }
f32 fn_80120524(Unit* u, int x) {
    /*P*/
    f32 r;
    f32 m;
    f32 d;
    u8 g;
    u8 n;
    /*E*/
    if (x == 0) return 0.0f;
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        m = 1.5f;
    } else {
        m = 1.0f;
    }
    g = fn_80126BA4(u);
    n = 0;
    if (fn_80126B0C(u) != 0xff && 100 - fn_80126B0C(u) <= x) {
        n = (x + fn_80126B0C(u)) / 100;
    }
    d = 1.0f;
    switch (((u8*)fn_80060728(lbl_803CAB38))[0x11]) {
    case 0:
        d = 0.33333334f;
        break;
    case 1:
        d = 0.5f;
        break;
    case 2:
        d = 1.0f;
        break;
    }
    if (n == 0) {
        f32 t = x;
        r = t * (d * ((f32)g * m - 1.0f)) + t;
    } else {
        f32 t = 100 - fn_80126B0C(u);
        r = t * (d * ((f32)g * m - 1.0f)) + t;
        x -= 100 - fn_80126B0C(u);
        for (g++; x > 0; g++, x -= 100) {
            f32 t2 = Min(x, lbl_804CA708);
            r += t2 * (d * ((f32)g * m - 1.0f)) + t2;
        }
    }
    return r;
}
}
