/* Camera angles that look from one point to another, 8012F3A8. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern Vec fn_8012F1F4(Vec, f32);
extern void fn_80313484(const Vec*, const Vec*, Vec*);
extern f32 fn_80313508(const Vec*);
extern void fn_80313460(const Vec*, const Vec*, Vec*);
extern double fn_80295CF0(double);
extern f32 fn_80176A4C(f32, f32, f32, f32);
extern void fn_80312654(void*, int, f32);
extern void fn_80312DB4(void*, Vec*, Vec*);
Vec fn_8012F3A8(Vec* p, const Vec* q) {
    int i;
    f32 len;
    f32 ang;
    f32 yaw;
    u8 m[0x30];
    Vec d;
    Vec t;
    fn_80313484(p, q, &d);
    len = fn_80313508(&d);
    for (i = 0; i < 0x10; i++) {
        Vec o = fn_8012F1F4(*p, len);
        fn_80313460(p, &o, &o);
        fn_80313484(&o, q, &d);
        len = fn_80313508(&d);
    }
    ang = fn_80176A4C(0.0f, 0.0f, fn_80295CF0(d.x * d.x + d.y * d.y), d.z);
    yaw = 0.0f;
    if (yaw != ang) {
        t.x = 0.0f;
        t.y = 0.0f;
        t.z = -len;
        fn_80312654(m, 0x58, 0.017453292f * ang);
        fn_80312DB4(m, &t, &t);
        fn_80313460(&d, &t, &d);
        yaw = -fn_80176A4C(d.x, d.y, t.x, t.y);
    }
    {
    Vec r;
    r.x = yaw;
    r.y = ang;
    r.z = len;
    return r;
    }
}
}
