#include "game/rG_800A3D88/types.h"

// Battle character: face the opponent and step back by a tuned distance.
extern "C" {
struct Vec { f32 x, y, z; };
struct ChrU { u8 p[0x44]; Vec m44; u8 p50[4]; u8 m54; u8 p55[3]; s16 m58; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
f32 fn_800A84A4(const char*);
s16 fn_8001E094(f32);
void fn_800B33F4(ChrU*, int);
void fn_800B2810(ChrU* c, int k, f32 v) {
    if (0.0f == v) {
        switch (k) {
        case 0:
            v = fn_800A84A4(STR(0x114));
            break;
        case 1:
            v = fn_800A84A4(STR(0x11F));
            break;
        case 2:
            v = fn_800A84A4(STR(0x12A));
            break;
        case 3:
            v = fn_800A84A4(STR(0x135));
            break;
        case 4:
            v = fn_800A84A4(STR(0x140));
            break;
        default:
            v = fn_800A84A4(STR(0x114));
            break;
        }
    }
    f32 m = -v;
    f32 a = 90.0f;
    if ((int)c->m54 == 1) {
        a *= -1.0f;
        m *= -1.0f;
    }
    c->m58 = fn_8001E094(a);
    fn_800B33F4(c, 1);
    c->m44.x = m;
    c->m44.y = 0.0f;
    c->m44.z = 0.0f;
    fn_800B33F4(c, 1);
}
}
