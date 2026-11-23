/* Model viewport: debug camera from the controller, camera read-back */
#include "game/rN_8025EEF0/calls.h"

struct Vec3 { f32 x, y, z; };
struct Mtx34 { f32 m[3][4]; };
class Pad2 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30();
    virtual u32 v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual u32 v48();
    virtual void v4C();
    virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C();
    virtual int v70(); virtual int v74();
};
#define PAD ((Pad2*)lbl_804CB5B8)
struct Cam {
    u8 pad[0xD4];
    Vec3 eye;
    Vec3 at;
    Vec3 up;
    u8 pad_f8[0xC];
    f32 m104, m108, m10C;
    u8 pad110[0x30];
    f32 m140, m144, m148, m14C;
};
struct View {
    u8 pad[0x34];
    f32 x, y, z;
    f32 ax, ay, az;
    f32 ox, oy, oz;
    f32 fov, near0, far0, m64;
};

extern "C" {

extern char lbl_80373748[];
void fn_80312654(Mtx34* m, int axis, f32 a);
void fn_80312378(Mtx34* a, Mtx34* b, Mtx34* c);
void fn_80312DB4(Mtx34* a, Vec3* b, Vec3* c);
void fn_80313484(void* a, void* b, Vec3* c);
f32 fn_80313508(Vec3* a);
void fn_803134C4(Vec3* a, Vec3* b);
f32 fn_8031354C(Vec3* a, Vec3* b);
void fn_8031356C(Vec3* a, Vec3* b, Vec3* c);
f32 fn_80295A90(f32 a);
Cam* fn_8000F470(void);
#if TARGET_PC
FE10_PROTO void fn_8000F954(Cam* c, p32arg, int b);
#else
void fn_8000F954(Cam* c, int a, int b);
#endif
void fn_8000FA98(Cam* c);

void fn_8027DF84(View* o) {
    Mtx34 m0, m1, m2, m3;
    Vec3 d;
/*P*/
    Cam* c;
/*E*/
    *(int*)&d.x = 0;
    *(int*)&d.y = 0;
    *(int*)&d.z = 0;
    if (lbl_804CB5B8->v34() & 0x10) {
        o->near0 += (f32)PAD->v5C() / 1000.0f;
        o->fov += (f32)PAD->v54() / 100.0f;
        if (o->fov <= 1.0f) o->fov = 1.0f;
        if (o->fov >= 120.0f) o->fov = 120.0f;
        o->az += (f32)PAD->v70() / 100.0f;
        o->az -= (f32)PAD->v74() / 100.0f;
        if (lbl_804CB5B8->v48() & 0x1000) {
            o->x = 0.0f;
            o->y = 10.0f;
            o->z = 60.0f;
            o->ax = -3.0f;
            o->ay = 0.0f;
            o->az = 0.0f;
            o->fov = 36.0f;
            o->near0 = 1.3571428f;
            o->far0 = 2.0f;
            o->m64 = 2000.0f;
        }
    } else {
        o->ax += (f32)-PAD->v5C() / 32.0f;
        o->ay += (f32)-PAD->v58() / 32.0f;
        d.x += (f32)PAD->v50() / 64.0f;
        d.z -= (f32)PAD->v54() / 64.0f;
        d.y += (f32)PAD->v70() / 300.0f;
        d.y -= (f32)PAD->v74() / 300.0f;
    }
    fn_80312654(&m0, 0x58, 0.017453292f * o->ax);
    fn_80312654(&m1, 0x59, 0.017453292f * o->ay);
    fn_80312654(&m2, 0x5A, 0.017453292f * o->az);
    fn_80312378(&m1, &m0, &m3);
    fn_80312378(&m2, &m3, &m3);
    fn_80312DB4(&m3, &d, &d);
    o->x += d.x;
    o->y += d.y;
    o->z += d.z;
    c = fn_8000F470();
    c->m104 = 1.0f;
    c->m108 = 0.0f;
    c->m10C = 0.0f;
    c->up.x = 0.0f;
    c->up.y = 1.0f;
    c->up.z = 0.0f;
    c->at.x = 0.0f;
    c->at.y = 0.0f;
    c->at.z = -1.0f;
    c->eye.x = o->x + o->ox;
    c->eye.y = o->y + o->oy;
    c->eye.z = o->z + o->oz;
    fn_80312654(&m0, 0x58, 0.017453292f * o->ax);
    fn_80312654(&m1, 0x59, 0.017453292f * o->ay);
    fn_80312654(&m2, 0x5A, 0.017453292f * o->az);
    fn_80312378(&m1, &m0, &m3);
    fn_80312378(&m2, &m3, &m3);
    fn_80312DB4(&m3, &c->at, &c->at);
    fn_80312DB4(&m3, &c->up, &c->up);
    c->at.x += c->eye.x;
    c->at.y += c->eye.y;
    c->at.z += c->eye.z;
    c->m14C = o->fov;
    fn_8000F954(c, 0, 1);
    fn_8000FA98(c);
}

}
