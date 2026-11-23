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

s32 fn_800A3EFC(void* self, Holder* h, Arg3A* a) {
    lbl_804CB630 = a->b;
    if (h->obj->getModel()) {
        fn_80253EE4(h->obj->getModel(), lbl_804CD264);
    }
    return 5;
}

void* fn_800A3F68() { return fn_800D0864(lbl_80382100); }
void* fn_800A3F74() { return fn_800D0864(lbl_8038210C); }
void* fn_800A3F80() { return fn_800D0864(lbl_80382118); }

struct Flags {
    u8 pad[0xC];
    u8 c, d;
};

void fn_800A3F8C(Flags* f, u8 v) { f->c = v; }
void fn_800A3F94(Flags* f, u8 m) { f->d &= ~m; }

void fn_800A4048(WobbleProc* p) {
    Target* t = p->target;
    f32 y = p->y;
    t->x = p->x;
    t->y = y;
}

void fn_800A4060(WobbleProc* p) {
    Target* t = p->target;
    p->x = fn_800D3DA8(t, 0);
    p->y = fn_800D3DA8(t, 1);
}

struct WobbleProc2 {
    u8 pad[0x38];
    s32 a;
    f32 b, c, d;
};

void fn_800A41AC(void* x, s32 a, s32 b) {
    void* o = fn_800D4228(x);
    if (o != NULL) {
        WobbleProc2* p = (WobbleProc2*)fn_80081050(lbl_80381E58, o);
        p->a = a;
        p->b = -b;
    }
}

void fn_800A4224(void* x, s32 a, s32 b) {
    void* o = fn_800D4228(x);
    if (o != NULL) {
        WobbleProc2* p = (WobbleProc2*)fn_80081050(lbl_80381E58, o);
        p->a = a;
        p->b = b;
    }
}

void fn_800A4298(void* x, s32 a, s32 b) {
    void* o = fn_800D4228(x);
    if (o != NULL) {
        WobbleProc2* p = (WobbleProc2*)fn_80081050(lbl_80381E80, o);
        p->a = a;
        p->b = b;
        p->c = lbl_804CD284;
        p->d = lbl_804CD284;
    }
}

void fn_800A4318(void* x, s32 a, s32 b) {
    void* o = fn_800D4228(x);
    if (o != NULL) {
        WobbleProc2* p = (WobbleProc2*)fn_80081050(lbl_80381E80, o);
        p->a = a;
        p->b = b;
        p->c = lbl_804CD288;
        p->d = lbl_804CD264;
    }
}

void fn_800A439C(void* x, s32 a, s32 b) {
    void* o = fn_800D4228(x);
    if (o != NULL) {
        WobbleProc2* p = (WobbleProc2*)fn_80081050(lbl_80381E80, o);
        p->a = a;
        p->b = b;
        p->c = lbl_804CD284;
        p->d = lbl_804CD28C;
    }
}

} // extern "C"
