#include "game/rI_801DD7D4/types.h"
struct Vec { f32 x, y, z; };
typedef f32 Mtx[3][4];
extern "C" {
f32* fn_8007E4C4(f32*);
void fn_80312344(const void*, Mtx);
void fn_80312DB4(const Mtx, const Vec*, Vec*);
f32 fn_8001EBC8(int, f32, f32, f32, f32);
void fn_8007E478(Mtx, f32);
}
class Sl {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual int v28(); virtual void v2C(); virtual void v30(f32, f32, f32, void*);
    int x4; int x8; u8 xc, xd; s16 xe, x10, x12, x14;
};
static inline BOOL has(Sl* o) { return o->x14 != 0; }
static inline void dec(Sl* o) { o->x14--; }
static inline f32 ez(f32 w, f32 t) { return fn_8001EBC8(2, 0.0f, w, 30.0f, t); }
static inline f32 ez2(s16 w, s16 t) { return fn_8001EBC8(2, 0.0f, w, 30.0f, t); }
static inline f32 ez3(int w, int t) { return fn_8001EBC8(2, 0.0f, w, 30.0f, t); }
extern "C" void fn_801DD844(Sl* o, void* a) {
    f32 sv;
    Vec v;
    Mtx m;
    if (((const Sl*)o)->x14 != 0) o->x14--;
    fn_80312344(fn_8007E4C4(&sv), m);
    v.x = o->xe;
    v.y = o->x10;
    v.z = o->x12;
    fn_80312DB4(m, &v, &v);
    {
    f32 x = v.x;
    f32 y = v.y;
    f32 z = v.z;
    if (o->x14 != 0 && o->xd) {
        s16 w = o->v28();
        f32 fw = w;
        int d = fn_8001EBC8(2, 0.0f, fw, 30.0f, o->x14);
        switch (o->x8) {
        case 0: x -= d; break;
        case 1: x += d; break;
        case 2: y -= d; break;
        case 3: y += d; break;
        }
    }
    if (o->xc) o->v30(x, y, z, a);
    }
    fn_8007E478(m, sv);
}
