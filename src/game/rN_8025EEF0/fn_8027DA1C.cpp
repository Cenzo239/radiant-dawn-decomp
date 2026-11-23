/* Model viewport proc: place and draw the model */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

extern char lbl_80373720[];
f32 fn_800A7370(void* p, const char* s);
void fn_80312654(void* m, int axis, f32 a);
void fn_8031292C(void* m, f32 a, f32 b, f32 c);
void fn_803128AC(void* m, f32 a, f32 b, f32 c);
void fn_80312378(void* a, void* b, void* c);
void fn_80312344(void* a, void* b);
void fn_80008F20(void* m, int a);
void fn_800081D4(void* m);
void fn_80007DE8(void* m);
void fn_800B9884(void* p);
void fn_8001CD78(void* m);
void* fn_800B5784(void* p, int a);
void fn_800BFA4C(void* o);
#if TARGET_PC
FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
void fn_80080910(void* f, void* p);
#endif
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080508(C4* c);
void fn_8027D7CC(void* p);

static const C4 kc = {0, 0, 0, 0x40};

struct View {
    u8 pad[0x30];
    u8* mdl;
    u8 pad34[0x44];
    void* m78;
    u8 pad7C[0x28];
    s16 x, y, w, h, z;
    u8 aE;
    u8 fade;
};

static inline void col(C4 c) { fn_80080508(&c); }

void fn_8027DA1C(View* v) {
    u8 m[0x30];
    u8 ms[0x30];
    u8 mt[0x30];
    u8 mrx0[0x30];
    u8 mrx[0x30];
    u8 mry[0x30];
    u8 mrz[0x30];
    if (v->m78 != 0 && v->mdl != 0) {
    {
        const char* s = lbl_80373720;
        f32 px = (f32)(v->x + v->w / 2);
        f32 k = fn_800A7370(v->m78, s + 5);
        f32 d = (f32)v->h * k / 100.0f;
        f32 py = (f32)v->y + d;
        f32 pz = (f32)v->z;
        f32 rx = 10.0f;
        f32 ry = 3.6f * fn_800A7370(v->m78, s + 0xE);
        f32 rz = 0.0f;
        f32 sc = fn_800A7370(v->m78, s + 0x17);
        fn_80312654(mrx0, 0x78, 3.1415927f);
        fn_80312654(mrx, 0x78, 0.017453292f * rx);
        fn_80312654(mry, 0x79, 0.017453292f * ry);
        fn_80312654(mrz, 0x7A, 0.017453292f * rz);
        fn_8031292C(ms, sc, sc, sc);
        fn_803128AC(mt, px, py, pz);
        fn_80312378(mrx0, ms, m);
        fn_80312378(mrz, m, m);
        fn_80312378(mry, m, m);
        fn_80312378(mrx, m, m);
        fn_80312378(mt, m, m);
    }
    fn_80312344(m, v->mdl + 0x10);
    fn_80008F20(v->mdl, v->aE);
    fn_800081D4(v->mdl);
    fn_80007DE8(v->mdl);
    fn_800B9884(v);
    fn_8001CD78(v->mdl);
    {
        void* o = fn_800B5784(v, -1);
        if (o != 0) {
            fn_800BFA4C(o);
        }
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, v->z, 1.0f);
    fn_8007E174(0, 0x410);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(0xB);
    fn_80080910((void*)fn_8027D7CC, v);
    fn_80080308();
    if (v->fade != 0) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 900.0f, 1.0f);
        fn_8007E174(0, 0x12);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080388(v->x, v->y, v->w, v->h);
        col(kc);
        fn_80080308();
    }
    }
}

}
