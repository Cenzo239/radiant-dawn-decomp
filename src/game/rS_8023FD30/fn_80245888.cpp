#include "game/rS_8023FD30/types.h"
/* Save block serializers: fields to and from a byte stream. */
extern "C" {
void fn_8008A5AC(void*, u8);
void fn_8008A5C0(void*, u16);
void fn_8008A5E4(void*, u32);
void fn_8008A628(void*, u64);
void fn_8008A780(void*, u32, void*);
u8 fn_8008A1A0(void*);
u16 fn_8008A1B4(void*);
u32 fn_8008A1DC(void*);
u64 fn_8008A22C(void*);
void fn_8008A43C(void*, u32, void*);
void fn_8010940C(void*, void*);
void fn_801094F8(void*, void*);
void* memset(void*, int, u32);
}
class SObj {
public:
    virtual void wr(void*);
    virtual void rd(void*);
};
struct SaveRoot {
    u64 magic;
    u32 date;
    u32 ver;
    u64 v10;
    u32 v18;
    SObj o1C;
    u8 pad20[8];
    SObj o28;
    u8 pad2C[0x183C - 0x2C];
    u8 a183C[0x60];
    SObj o189C;
    u8 pad18A0[0x10];
    SObj o18B0;
    u8 pad18B4[0x10];
    SObj o18C4;
    u8 pad18C8[8];
    SObj o18D0;
    u8 pad18D4[8];
    SObj o18DC;
    u8 pad18E0[8];
    u16 v18E8;
    u16 v18EA;
    u16 v18EC;
    u16 v18EE;
    s16 v18F0;
    u16 v18F2;
    s16 v18F4;
    u16 v18F6;
    u8 a18F8[0x2D0];
    u8 v1BC8;
    u8 v1BC9;
    u8 a1BCA[2];
    u32 v1BCC;
};
struct SaveSys {
    u64 magic;
    u32 date;
    u32 ver;
    u64 v10;
    u32 v18;
    u32 v1C;
    u64 v20;
    u64 v28;
    u8 v30[8];
    u16 v38;
    u16 v3A;
    SObj o3C;
    u32 pad40;
    u8 o44[0x70 - 0x44];
    u8 a70[0x1000];
};
static inline void pair16(void* st, u16 a, s16 b) {
    fn_8008A5C0(st, a);
    fn_8008A5C0(st, b);
}
extern "C" {
void fn_80245888(SaveRoot* s, void* st) {
    fn_8008A628(st, s->magic);
    fn_8008A5E4(st, s->date);
    s->ver = 7;
    fn_8008A5E4(st, 7);
    fn_8008A628(st, s->v10);
    fn_8008A5E4(st, s->v18);
    s->o1C.wr(st);
    s->o28.wr(st);
    fn_8008A780(st, 0x60, s->a183C);
    s->o189C.wr(st);
    s->o18B0.wr(st);
    s->o18C4.wr(st);
    s->o18D0.wr(st);
    s->o18DC.wr(st);
    fn_8008A5C0(st, s->v18E8);
    fn_8008A5C0(st, s->v18EA);
    fn_8008A5C0(st, s->v18EC);
    pair16(st, s->v18EE, s->v18F0);
    pair16(st, s->v18F2, s->v18F4);
    fn_8008A5C0(st, s->v18F6);
    fn_8008A780(st, 0x2D0, s->a18F8);
    fn_8008A5AC(st, s->v1BC8);
    fn_8008A5AC(st, s->v1BC9);
    fn_8008A780(st, 2, s->a1BCA);
    fn_8008A5E4(st, s->v1BCC);
}
void fn_80245A74(SaveRoot* s, void* st) {
    s->magic = fn_8008A22C(st);
    s->date = fn_8008A1DC(st);
    s->ver = fn_8008A1DC(st);
    s->v10 = fn_8008A22C(st);
    if (s->ver >= 6) {
        s->v18 = fn_8008A1DC(st);
    }
    s->o1C.rd(st);
    s->o28.rd(st);
    fn_8008A43C(st, 0x60, s->a183C);
    if (s->ver >= 5) {
        s->o189C.rd(st);
    }
    s->o18B0.rd(st);
    s->o18C4.rd(st);
    s->o18D0.rd(st);
    s->o18DC.rd(st);
    s->v18E8 = fn_8008A1B4(st);
    s->v18EA = fn_8008A1B4(st);
    s->v18EC = fn_8008A1B4(st);
    s->v18EE = fn_8008A1B4(st);
    s->v18F0 = fn_8008A1B4(st);
    s->v18F2 = fn_8008A1B4(st);
    s->v18F4 = fn_8008A1B4(st);
    s->v18F6 = fn_8008A1B4(st);
    fn_8008A43C(st, 0x2D0, s->a18F8);
    s->v1BC8 = fn_8008A1A0(st);
    s->v1BC9 = fn_8008A1A0(st);
    if (s->ver >= 7) {
        fn_8008A43C(st, 2, s->a1BCA);
        s->v1BCC = fn_8008A1DC(st);
    } else {
        memset(s->a1BCA, 0xFF, 2);
        s->v1BCC = -1;
    }
}
void fn_80245E44(SaveSys* s, void* st) {
    fn_8008A628(st, s->magic);
    fn_8008A5E4(st, s->date);
    s->ver = 0x11;
    fn_8008A5E4(st, 0x11);
    fn_8008A628(st, s->v10);
    fn_8008A5E4(st, s->v18);
    fn_8008A5E4(st, s->v1C);
    fn_8008A628(st, s->v20);
    fn_8008A628(st, s->v28);
    fn_8008A5AC(st, s->v30[0]);
    fn_8008A5AC(st, s->v30[1]);
    fn_8008A5AC(st, s->v30[2]);
    fn_8008A5AC(st, s->v30[3]);
    fn_8008A5AC(st, s->v30[4]);
    fn_8008A5AC(st, s->v30[5]);
    fn_8008A5AC(st, s->v30[6]);
    fn_8008A5AC(st, s->v30[7]);
    fn_8008A5C0(st, s->v38);
    fn_8008A5C0(st, s->v3A);
    s->o3C.wr(st);
    fn_8010940C(s->o44, st);
    fn_8008A780(st, 0x1000, s->a70);
}
void fn_80245F9C(SaveSys* s, void* st) {
    s->magic = fn_8008A22C(st);
    s->date = fn_8008A1DC(st);
    s->ver = fn_8008A1DC(st);
    s->v10 = fn_8008A22C(st);
    s->v18 = fn_8008A1DC(st);
    s->v1C = fn_8008A1DC(st);
    s->v20 = fn_8008A22C(st);
    s->v28 = fn_8008A22C(st);
    s->v30[0] = fn_8008A1A0(st);
    s->v30[1] = fn_8008A1A0(st);
    s->v30[2] = fn_8008A1A0(st);
    s->v30[3] = fn_8008A1A0(st);
    {
        u8 x = fn_8008A1A0(st);
        s->v30[4] = x;
        if (x < 1) {
            s->v30[4] = 1;
        }
    }
    s->v30[5] = fn_8008A1A0(st);
    s->v30[6] = fn_8008A1A0(st);
    s->v30[7] = fn_8008A1A0(st);
    s->v38 = fn_8008A1B4(st);
    s->v3A = fn_8008A1B4(st);
    s->o3C.rd(st);
    fn_801094F8(s->o44, st);
    fn_8008A43C(st, 0x1000, s->a70);
}

}
