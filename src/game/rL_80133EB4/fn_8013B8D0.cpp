#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
struct Wx { u8 pad[0x31]; u8 x31; };
struct MA { u8 pad[0x18]; Wx* x18; };
class VO { public: u8 pad[0x6C]; virtual void v(Vec*); };
struct H44 { u8 pad[0x44]; VO* x44; };
struct Grid { s32 w, h; u8 pad[0x20000]; };
struct P14 { u8 pad[8]; f32 x8, xc; };
struct C5 { u8 pad[0x14]; P14* x14; };
struct Cm { f32 x0, x4, x8, xc, x10; };
extern "C" {
extern u8 lbl_804CB834;
extern void fn_80146BAC(Wx*, int);
extern void fn_80146B40(Wx*);
void fn_8013B8D0(MA* m) {
    Wx* w = m->x18;
    if (w) {
        int cur = lbl_804CB834;
        if (cur != w->x31) fn_80146BAC(w, cur);
        fn_80146B40(w);
    }
}
void fn_8013C0F8(H44* h) {
    Vec a = {0.0f, 0.0f, 0.0f};
    Vec b = {0.0f, 0.0f, 0.0f};
    VO* o = h->x44;
    o->v(&a);
}
}
