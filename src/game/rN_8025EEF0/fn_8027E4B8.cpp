/* Model viewport: read the angles back from the camera */
#include "game/rN_8025EEF0/calls.h"

struct Vec3 { f32 x, y, z; };
struct Vi { int x, y, z; };
struct Mtx34 { f32 m[3][4]; };
struct Cam {
    u8 pad[0xD4];
    Vec3 eye;
    Vec3 at;
    u8 padEC[0x54];
    f32 m140, m144, m148, m14C;
};
struct View {
    u8 pad[0x34];
    f32 x, y, z;
    f32 ax, ay, az;
    f32 ox, oy, oz;
    f32 fov, near0, m60, m64;
};

extern "C" {

extern Vec3 lbl_80373748;
#define lbl_80373748x lbl_80373748
void fn_80312654(Mtx34* m, int axis, f32 a);
void fn_80312DB4(Mtx34* a, Vec3* b, Vec3* c);
void fn_80313484(void* a, void* b, Vec3* c);
f32 fn_80313508(Vec3* a);
void fn_803134C4(Vec3* a, Vec3* b);
f32 fn_8031354C(Vec3* a, Vec3* b);
void fn_8031356C(Vec3* a, Vec3* b, Vec3* c);
double fn_80295A90(double a);
Cam* fn_8000F470(void);
#if TARGET_PC
FE10_PROTO void fn_8000F954(Cam* c, p32arg, int b);
#else
void fn_8000F954(Cam* c, int a, int b);
#endif
void fn_8000FA98(Cam* c);

static inline f32 ang(Vec3* a, Vec3* b, Vec3* cr) {
    f32 r;
    fn_803134C4(a, a);
    fn_803134C4(b, b);
    r = fn_8031354C(a, b);
    if (r >= 0.9999f) {
        r = 0.0f;
    } else if (r <= -0.9999f) {
        r = 3.1415927f;
    } else {
        r = (f32)fn_80295A90(r);
    }
    fn_8031356C(a, b, cr);
    return r;
}

void fn_8027E4B8(View* o) {
    Cam* c = fn_8000F470();
    Vec3 k = lbl_80373748x;
    Vec3 res;
    Vec3 a, b, cr, d;
    Mtx34 m;
    *(int*)&res.x = 0;
    *(int*)&res.y = 0;
    *(int*)&res.z = 0;
    fn_80313484(&c->at, &c->eye, &d);
    a.y = k.y;
    a.z = k.z;
    b.y = d.y;
    b.z = d.z;
    a.x = 0.0f;
    b.x = 0.0f;
    if (fn_80313508(&a) > 0.0f && fn_80313508(&b) > 0.0f) {
        f32 r = ang(&a, &b, &cr);
        if (cr.x < 0.0f) r *= -1.0f;
        fn_80312654(&m, 0x78, -r);
        fn_80312DB4(&m, &d, &d);
        res.x = r;
    }
    a.x = k.x;
    a.z = k.z;
    b.x = d.x;
    b.z = d.z;
    a.y = 0.0f;
    b.y = 0.0f;
    if (fn_80313508(&a) > 0.0f && fn_80313508(&b) > 0.0f) {
        f32 r = ang(&a, &b, &cr);
        if (cr.y < 0.0f) r *= -1.0f;
        fn_80312654(&m, 0x79, -r);
        fn_80312DB4(&m, &d, &d);
        res.y = r;
    }
    o->ax = 57.29578f * res.x;
    o->ay = 57.29578f * res.y;
    o->az = 57.29578f * res.z;
    o->x = c->eye.x;
    o->y = c->eye.y;
    o->z = c->eye.z;
    o->fov = c->m14C;
    o->near0 = c->m148;
    o->m60 = c->m140;
    o->m64 = c->m144;
    fn_8000F954(c, 0, 1);
    fn_8000FA98(c);
}

}
