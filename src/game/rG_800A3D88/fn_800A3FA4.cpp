/* fn_800A3FA4: exact (round m3). From equiv/fn_800A3FA4.cpp: both int-to-float conversions as named locals, then declaration order r, d, y, a, x, s. Self-contained (parent fn_800A3EFC.cpp with exported bodies removed). */
#include "game/rG_800A3D88/types.h"

extern "C" {

extern u8 lbl_804CB630;
extern const f32 lbl_804CD264;
extern const f32 lbl_804CD270;
extern const f32 lbl_804CD284;
extern const f32 lbl_804CD288;
extern const f32 lbl_804CD28C;
extern const f32 lbl_804CD298;
extern u8 lbl_80381E58[];
extern u8 lbl_80381E80[];
extern u8 lbl_80382100[];
extern u8 lbl_8038210C[];
extern u8 lbl_80382118[];
extern u8 lbl_80382138[];

void fn_80253EE4(void*, f32);
void* fn_800D0864(void*);
s32 fn_8017F990(s32, s32);
double fn_80295940(double);
f32 fn_800D3DA8(void*, s32);
void* fn_800D4228(void*);
void* fn_80081050(void*, void*);
void* fn_80083B84(void*);
void fn_80081A90(void*);
void fn_80006EE0(void*);
u32 fn_80089ED0();
void fn_8027E4B8(void*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A8208(void*);
#else
void* fn_800A8208(void*);
#endif
#if TARGET_PC
FE10_PROTO void fn_800A5F08(void*, void*, ptr32<const void>);
#else
void fn_800A5F08(void*, void*, void*);
#endif
void fn_800A5B84(void*, void*, void*);
void fn_802573EC(void*);

struct Target {
    u8 pad[0x40];
    f32 x, y;
};

struct WobbleProc {
    u8 pad[0x18];
    Target* target;
    u8 pad1c[0x30 - 0x1C];
    f32 x, y;
    s32 period;
    f32 amp;
};

class Obj3C {
public:
    u8 pad0[4];
    /* vptr at +4; first slot is vtable +8 */
    VP16(a) VP8(b) VP4(c) VP1(d) /* 0x08..0x78 */
    virtual void* getModel(); /* 0x7C */
};

struct Holder {
    u8 pad[0x3C];
    Obj3C* obj;
};

struct Arg3A {
    u8 pad[0x3A];
    u8 b;
};
s32 fn_800A3EFC(void* self, Holder* h, Arg3A* a);

void* fn_800A3F68();

void* fn_800A3F74();

void* fn_800A3F80();


struct Flags {
    u8 pad[0xC];
    u8 c, d;
};
void fn_800A3F8C(Flags* f, u8 v);

void fn_800A3F94(Flags* f, u8 m);

void fn_800A4048(WobbleProc* p);

void fn_800A4060(WobbleProc* p);


struct WobbleProc2 {
    u8 pad[0x38];
    s32 a;
    f32 b, c, d;
};
void fn_800A41AC(void* x, s32 a, s32 b);

void fn_800A4224(void* x, s32 a, s32 b);

void fn_800A4298(void* x, s32 a, s32 b);

void fn_800A4318(void* x, s32 a, s32 b);

void fn_800A439C(void* x, s32 a, s32 b);


} // extern "C"


#pragma use_lmw_stmw off
/* ---- from rG_800A3D88/wip/fn_800A3FA4.cpp ---- */
extern "C" {
void fn_800A3FA4(WobbleProc* p) {
    Target* t = p->target;
    f32 r;
    f32 d;
    f32 y;
    f32 a;
    f32 x;
    f32 s;
    r = (f32)fn_8017F990(0, p->period);
    d = (f32)p->period;
    s = fn_80295940(lbl_804CD270 * (r / d));
    a = p->amp * s;
    y = p->y + a;
    x = p->x;
    t->x = x;
    t->y = y;
}

}
