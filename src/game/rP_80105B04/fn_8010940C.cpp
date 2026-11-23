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
void fn_801094F8(Opt* o, void* r) {
    fn_8024BCA0();
    fn_8008A43C(r, 8, o);
    o->x8 = fn_8008A1A0(r);
    o->x9 = fn_8008A1A0(r);
    o->xa = fn_8008A1A0(r);
    if ((s8)o->xa == 0) o->xa = 0x40;
    o->xb = fn_8008A1A0(r);
    o->xc = fn_8008A1A0(r);
    o->xd = fn_8008A1A0(r);
    o->xe = fn_8008A1A0(r);
    o->xf = fn_8008A1A0(r);
    o->x10 = fn_8008A1A0(r);
    o->x11 = fn_8008A1A0(r);
    o->x12 = fn_8008A1B4(r);
    o->x14 = fn_8008A1DC(r);
    o->x18 = fn_8008A1DC(r);
    o->x1c = fn_8008A1DC(r);
}
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
void fn_80109744(Opt* o) {
    o->xd = 100;
    o->xe = 100;
    o->xf = 100;
    o->x10 = 100;
    o->a3 = 1;
    o->b8 = 1;
    o->a20 = Sound();
}
void fn_8024DDF8(int v);
void fn_8007A84C(int v);
void fn_8007A83C(int v);
void fn_80250AB4(f32 v, f32 k);
void fn_80250B60(f32 v, f32 k);
void fn_80250C0C(f32 v, f32 k);
void fn_80250CB8(f32 v, f32 k);
void fn_8008D414(s8 a, s8 b, s8 c);
void fn_801097FC(Opt* o) {
    fn_80250AB4(o->xd / 100.0f, 0.0f);
    fn_80250B60(o->xf / 100.0f, 0.0f);
    fn_80250C0C(o->xe / 100.0f, 0.0f);
    fn_80250CB8(o->x10 / 100.0f, 0.0f);
    switch (o->a20) {
    case 2:
        fn_8024DDF8(2);
        break;
    case 1:
        fn_8024DDF8(0);
        break;
    case 0:
        fn_8024DDF8(3);
        break;
    default:
        fn_8024DDF8(0);
        break;
    }
    if (!o->b5) fn_8007A84C(1);
    else fn_8007A83C(1);
    fn_8008D414(o->xb, o->xc, o->xa);
    switch (o->b8) {
    case 2:
        fn_8007A84C(6);
        return;
    case 0:
        fn_8007A84C(6);
        fn_8007A83C(2);
        return;
    case 1:
        fn_8007A83C(6);
        return;
    }
}
}
