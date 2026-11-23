/* Camera work area set-up: two models with their four resources, then 4+4 child objects, then cleared rotations. */
#include "game/rH_80112B48/types.h"
extern "C" {
struct Obj {
    u32 flags;
    u8 pad4[0x40 - 4];
    void* p40;
    void* p44;
    void* p48;
    void* p4C;
    u8 pad50[0x9c - 0x50];
};
struct Quat { f32 x, y, z, w; };
struct CamW {
    u8 pad0[8];
    Obj a;
    Obj b;
    Obj c[4];
    Obj d[4];
    u8 pad620[0x658 - 0x620];
    f32 f658;
    f32 f65C;
    f32 f660[4];
    Quat q[4];
    int i6B0;
    u8 pad6B4[0x6d4 - 0x6b4];
    u8 b6D4;
    u8 b6D5;
};
extern CamW lbl_80413510;
extern void fn_80006E94(Obj*);
extern void* fn_8000EB68(const char*);
extern void* fn_80017F10(const char*);
extern void* fn_8000BD3C(const char*);
extern int fn_8023F9F4(const char*);
extern void* fn_8001D3B4(const char*);
extern void fn_80008F54(Obj*, int);
extern void fn_80006F20(Obj*);
extern void fn_80008F4C(Obj*, Obj*);
extern void fn_80008F20(Obj*, int);
extern void fn_80008F10(Obj*, int, int, int);
extern char lbl_80386008[], lbl_80385FF8[], lbl_80385FE8[], lbl_80385FD8[], lbl_80385FC8[];
extern char lbl_80385FB8[], lbl_80385FA8[], lbl_80385F98[], lbl_80385F88[], lbl_80385F78[];
void fn_80131AEC(void) {
    /*P*/
    int i;
    Obj* pc;
    Obj* pw;
    Obj* pd;
/*E*/
    fn_80006E94(&lbl_80413510.b);
    lbl_80413510.b.p40 = fn_8000EB68(lbl_80386008);
    lbl_80413510.b.p48 = fn_80017F10(lbl_80385FF8);
    lbl_80413510.b.p44 = fn_8000BD3C(lbl_80385FE8);
    if (fn_8023F9F4(lbl_80385FD8) != 0x40000) {
        lbl_80413510.b.p4C = fn_8001D3B4(lbl_80385FC8);
    }
    fn_80008F54(&lbl_80413510.b, 0x99);
    fn_80006F20(&lbl_80413510.b);
    fn_80006E94(&lbl_80413510.a);
    lbl_80413510.a.p40 = fn_8000EB68(lbl_80385FB8);
    lbl_80413510.a.p48 = fn_80017F10(lbl_80385FA8);
    lbl_80413510.a.p44 = fn_8000BD3C(lbl_80385F98);
    if (fn_8023F9F4(lbl_80385F88) != 0x40000) {
        lbl_80413510.a.p4C = fn_8001D3B4(lbl_80385F78);
    }
    fn_80008F54(&lbl_80413510.a, 0x99);
    fn_80006F20(&lbl_80413510.a);
    for (i = 0, pc = lbl_80413510.c, pd = lbl_80413510.d, pw = (Obj*)&lbl_80413510; i < 4; i++, pc++, pd++, pw++) {
        fn_80006E94(pc);
        fn_80008F54(pc, 0x99);
        fn_80008F4C(pc, &lbl_80413510.a);
        ((CamW*)pw)->c[0].flags |= 0x10000;
        fn_80006E94(pd);
        fn_80008F54(pd, 0x99);
        fn_80008F4C(pd, &lbl_80413510.a);
        fn_80008F20(pd, 0xf0);
        fn_80008F10(pd, 0x80, 0x20, 0x80);
        ((CamW*)pw)->d[0].flags |= 0x80010000;
    }
    lbl_80413510.f65C = 0.0f;
    lbl_80413510.f658 = 0.0f;
    for (i = 0; i < 4; i++) {
        lbl_80413510.f660[i] = 0.0f;
        lbl_80413510.q[i].x = 0.0f;
        lbl_80413510.q[i].y = 0.0f;
        lbl_80413510.q[i].z = 0.0f;
        lbl_80413510.q[i].w = 1.0f;
    }
    lbl_80413510.i6B0 = -2;
    lbl_80413510.b6D4 = 0;
    lbl_80413510.b6D5 = 1;
}
}
