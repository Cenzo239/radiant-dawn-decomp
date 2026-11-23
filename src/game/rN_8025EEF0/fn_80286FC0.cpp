/* Item preview model draw */
#include "game/rN_8025EEF0/prim2d.h"

struct Vec3 { f32 x, y, z; };
struct Mtx34 { f32 m[3][4]; };

extern "C" {

void fn_80312654(Mtx34* m, int axis, f32 a);
void fn_80312378(Mtx34* a, Mtx34* b, Mtx34* c);
void fn_80312954(Mtx34* a, Mtx34* b, f32 x, f32 y, f32 z);
void fn_803128E0(Mtx34* a, void* b, f32 x, f32 y, f32 z);
Vec3 fn_800FB178(void* a, f32 s);
void fn_80008F10(void* m, int r, int g, int b);
void fn_80008F20(void* m, int a);
void fn_80008F64(void* m, int a);
void fn_800081D4(void* m);
void fn_80007C58(void* m);
void fn_800F629C(void* a, void* m);
#if TARGET_PC
FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
void fn_80080910(void* f, void* m);
#endif
void fn_8001A4DC(void* p);
void fn_80287138(void);

void fn_80286FC0(void* const* p, f32 a, f32 b) {
    void* o;
    u8* mdl;
    Vec3 v;
    Mtx34 m2;
    Mtx34 m1;
    o = p[0];
    fn_80312654(&m1, 0x79, -0.5235988f);
    fn_80312654(&m2, 0x78, 3.6651914f);
    fn_80312378(&m2, &m1, &m2);
    fn_80312954(&m2, &m2, 4.0f, 4.0f, 4.0f);
    mdl = (u8*)p[1];
    v = fn_800FB178(*(void* volatile*)p, 1.0f);
    fn_803128E0(&m2, mdl + 0x10, a + v.x, b + v.y, 200.0f);
    fn_80008F10(mdl, 0x80, 0x80, 0x80);
    fn_80008F20(mdl, 0xFF);
    fn_80008F64(mdl, 0xFF);
    fn_800081D4(mdl);
    fn_80007C58(mdl);
    if (o != 0) {
        fn_800F629C(o, mdl);
    }
    fn_800800D4(0xB);
    fn_80080910(fn_8001A4DC, mdl);
    fn_80080308();
    fn_800800D4(0xB);
    fn_80080910(fn_80287138, 0);
    fn_80080308();
}

}
