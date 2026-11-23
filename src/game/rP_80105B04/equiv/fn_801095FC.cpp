/* fn_801095FC: resets the options to their defaults. Level: sched. Only the
   prologue differs: the original saves LR (`stw r0,0x14(r1)`) before loading
   the constant 0x14 into r0, ours loads it into r4 first; independent lines.
   symcheck --anon: 14 blocks, 0 differ. Built with tools/equiv/mkself.py from
   fn_8010940C.cpp and the wip/near.cpp fragment. */
#include "game/rP_80105B04/rp.h"
/* User options record. */
struct Opt {
    u32 a0 : 2;
    u32 a2 : 1;
    u32 a3 : 2;
    u32 a5 : 1;
    u32 a6 : 1;
    u32 a7 : 1;
    u32 a8 : 2;
    u32 a10 : 1;
    u32 a11 : 1;
    u32 a12 : 2;
    u32 a14 : 5;
    u32 a19 : 1;
    u32 a20 : 2;
    u32 a22 : 1;
    u32 a23 : 1;
    u32 a24 : 1;
    u32 a25 : 2;
    u32 a27 : 1;
    u32 a28 : 1;
    u32 a29 : 1;
    u32 a30 : 2;
    u32 b0 : 4;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 2;
    u32 b8 : 2;
    u32 b10 : 22;
    u8 x8, x9, xa, xb, xc, xd, xe, xf, x10, x11;
    u16 x12;
    u32 x14, x18, x1c;
    u8 x20, x21, x22, x23;
    u32 x24, x28;
};
extern "C" {
void fn_8024BCA0();
void fn_8008A43C(void* r, int n, void* p);
void fn_8008A780(void* w, int n, void* p);
u8 fn_8008A1A0(void* r);
u16 fn_8008A1B4(void* r);
u32 fn_8008A1DC(void* r);
void fn_8008A5AC(void* w, int v);
void fn_8008A5C0(void* w, int v);
void fn_8008A5E4(void* w, int v);
u8 fn_80325A2C();

void fn_8010940C(Opt* o, void* w);
void fn_801094F8(Opt* o, void* r);

static inline int Sound() {
    switch (fn_80325A2C()) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 3: return 2;
    default: return 1;
    }
}
void fn_801095FC(Opt* o);
void fn_80109744(Opt* o);

void fn_8024DDF8(int v);
void fn_8007A84C(int v);
void fn_8007A83C(int v);
void fn_80250AB4(f32 v, f32 k);
void fn_80250B60(f32 v, f32 k);
void fn_80250C0C(f32 v, f32 k);
void fn_80250CB8(f32 v, f32 k);
void fn_8008D414(s8 a, s8 b, s8 c);
void fn_801097FC(Opt* o);

}

/* ---- from build/tmp/r21small/rP/frag_fn_801095FC.cpp ---- */
extern "C" {
extern "C" {
/* fn_801095FC: 12 of 82 words, or 5 with x9 written first: the constants 1 and 0x14 and the second word land in the wrong registers (want r5, r0, r6) */
void fn_801095FC(Opt* o) {
    o->a0 = 0;
    o->a3 = 1;
    o->a5 = 0;
    o->a8 = 0;
    o->a11 = 1;
    o->a12 = 1;
    o->a14 = 0;
    o->a19 = 1;
    o->a23 = 1;
    o->a24 = 1;
    o->a25 = 0;
    o->a27 = 1;
    o->a30 = 0;
    o->x9 = 0x14;
    o->b6 = 0;
    o->b5 = 1;
    o->b4 = 0;
    o->b8 = 1;
    o->a20 = Sound();
    o->xa = 0x40;
    o->xb = 0;
    o->xc = 0;
    o->xd = 100;
    o->xe = 100;
    o->xf = 100;
    o->x10 = 100;
    o->x11 = 0;
    o->x8 = 1;
    o->x20 = 0;
    o->x24 = 0;
    o->x21 = 0;
    o->x22 = 0;
    o->x28 = 0;
    o->x23 = 0;
    o->a28 = 0;
    o->a6 = 1;
    o->a7 = 0;
    o->x12 = 0;
    o->x14 = 0;
    o->x18 = 0;
    o->x1c = 0;
}
}
}
